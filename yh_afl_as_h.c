/* this file is not .c file, is similarly a copy of afl_as.h file
 * this file is readable to read the instrumented code.
 * the code is hybird. assemble code with AT&T, c code(like #define)
 * there may have some syntax error, not care about it, this file is
 * just for reading the instrumented code.
 * */

#ifndef _HAVE_AFL_AS_H
#define _HAVE_AFL_AS_H

#include "config.h"
#include "types.h"


static const u8* trampoline_fmt_64 =

/* --- AFL TRAMPOLINE (64-BIT) --- */

.align 4

leaq -(128+24)(%rsp), %rsp
        movq %rdx,  0(%rsp)
movq %rcx,  8(%rsp)
movq %rax, 16(%rsp)
movq $0x%08x, %rcx
        call __afl_maybe_log
        movq 16(%rsp), %rax
        movq  8(%rsp), %rcx
        movq  0(%rsp), %rdx
        leaq (128+24)(%rsp), %rsp

/* --- END --- */
;





#ifdef __APPLE__
define CALL_L64(str)		"call _" str "
#else
define CALL_L64(str)		"call " str "@PLT
#endif /* ^__APPLE__ */

static const u8* main_payload_64 =


/* --- AFL MAIN PAYLOAD (64-BIT) --- */

.text
.att_syntax
.code64
.align 8




__afl_maybe_log:

#if defined(__OpenBSD__)  || (defined(__FreeBSD__) && (__FreeBSD__ < 9))
        .byte 0x9f /* lahf */
#else
        lahf
#endif /* ^__OpenBSD__, etc */
seto  %al

/* Check if SHM region is already mapped. */

        movq  __afl_area_ptr(%rip), %rdx
        testq %rdx, %rdx
        je    __afl_setup




        __afl_store:

/* Calculate and store hit for the code location specified in rcx. */

#ifndef COVERAGE_ONLY
xorq __afl_prev_loc(%rip), %rcx
        xorq %rcx, __afl_prev_loc(%rip)
shrq $1, __afl_prev_loc(%rip)
#endif /* ^!COVERAGE_ONLY */

#ifdef SKIP_COUNTS
orb  $1, (%rdx, %rcx, 1)
#else
incb (%rdx, %rcx, 1)
#endif /* ^SKIP_COUNTS */




__afl_return:

        addb $127, %al
#if defined(__OpenBSD__)  || (defined(__FreeBSD__) && (__FreeBSD__ < 9))
.byte 0x9e /* sahf */
#else
        sahf
#endif /* ^__OpenBSD__, etc */
ret

.align 8




__afl_setup:

/* Do not retry setup if we had previous failures. */

        cmpb $0, __afl_setup_failure(%rip)
jne __afl_return

/* Check out if we have a global pointer on file. */

#ifndef __APPLE__
movq  __afl_global_area_ptr@GOTPCREL(%rip), %rdx
        movq  (%rdx), %rdx
#else
movq  __afl_global_area_ptr(%rip), %rdx
#endif /* !^__APPLE__ */
        testq %rdx, %rdx
        je    __afl_setup_first

        movq %rdx, __afl_area_ptr(%rip)
jmp  __afl_store




__afl_setup_first:

/* Save everything that is not yet saved and that may be touched by
   getenv() and several other libcalls we'll be relying on. */

        leaq -352(%rsp), %rsp

        movq %rax,   0(%rsp)
movq %rcx,   8(%rsp)
movq %rdi,  16(%rsp)
movq %rsi,  32(%rsp)
movq %r8,   40(%rsp)
movq %r9,   48(%rsp)
movq %r10,  56(%rsp)
movq %r11,  64(%rsp)

movq %xmm0,  96(%rsp)
movq %xmm1,  112(%rsp)
movq %xmm2,  128(%rsp)
movq %xmm3,  144(%rsp)
movq %xmm4,  160(%rsp)
movq %xmm5,  176(%rsp)
movq %xmm6,  192(%rsp)
movq %xmm7,  208(%rsp)
movq %xmm8,  224(%rsp)
movq %xmm9,  240(%rsp)
movq %xmm10, 256(%rsp)
movq %xmm11, 272(%rsp)
movq %xmm12, 288(%rsp)
movq %xmm13, 304(%rsp)
movq %xmm14, 320(%rsp)
movq %xmm15, 336(%rsp)

/* Map SHM, jumping to __afl_setup_abort if something goes wrong. */

/* The 64-bit ABI requires 16-byte stack alignment. We'll keep the
   original stack ptr in the callee-saved r12. */

pushq %r12
        movq  %rsp, %r12
        subq  $16, %rsp
        andq  $0xfffffffffffffff0, %rsp

        leaq .AFL_SHM_ENV(%rip), %rdi
        CALL_L64("getenv")

testq %rax, %rax
        je    __afl_setup_abort

        movq  %rax, %rdi
        CALL_L64("atoi")

xorq %rdx, %rdx   /* shmat flags    */
        xorq %rsi, %rsi   /* requested addr */
        movq %rax, %rdi   /* SHM ID         */
        CALL_L64("shmat")

cmpq $-1, %rax
        je   __afl_setup_abort

/* Store the address of the SHM region. */

        movq %rax, %rdx
        movq %rax, __afl_area_ptr(%rip)

#ifdef __APPLE__
movq %rax, __afl_global_area_ptr(%rip)
#else
movq __afl_global_area_ptr@GOTPCREL(%rip), %rdx
        movq %rax, (%rdx)
#endif /* ^__APPLE__ */
movq %rax, %rdx




        __afl_forkserver:

/* Enter the fork server mode to avoid the overhead of execve() calls. We
   push rdx (area ptr) twice to keep stack alignment neat. */

pushq %rdx
        pushq %rdx

/* Phone home and tell the parent that we're OK. (Note that signals with
   no SA_RESTART will mess it up). If this fails, assume that the fd is
   closed because we were execve()d from an instrumented binary, or because
   the parent doesn't want to use the fork server. */

        movq $4, %rdx               /* length    */
        leaq __afl_temp(%rip), %rsi /* data      */
        movq $" STRINGIFY((FORKSRV_FD + 1)) ", %rdi       /* file desc */
        CALL_L64("write")

cmpq $4, %rax
        jne  __afl_fork_resume




        __afl_fork_wait_loop:

/* Wait for parent by reading from the pipe. Abort if read fails. */

movq $4, %rdx               /* length    */
        leaq __afl_temp(%rip), %rsi /* data      */
        movq $" STRINGIFY(FORKSRV_FD) ", %rdi             /* file desc */
        CALL_L64("read")
cmpq $4, %rax
        jne  __afl_die

/* Once woken up, create a clone of our process. This is an excellent use
   case for syscall(__NR_clone, 0, CLONE_PARENT), but glibc boneheadedly
   caches getpid() results and offers no way to update the value, breaking
   abort(), raise(), and a bunch of other things :-( */

        CALL_L64("fork")
cmpq $0, %rax
        jl   __afl_die
        je   __afl_fork_resume

/* In parent process: write PID to pipe, then wait for child. */

        movl %eax, __afl_fork_pid(%rip)

movq $4, %rdx                   /* length    */
        leaq __afl_fork_pid(%rip), %rsi /* data      */
        movq $" STRINGIFY((FORKSRV_FD + 1)) ", %rdi             /* file desc */
        CALL_L64("write")

movq $0, %rdx                   /* no flags  */
        leaq __afl_temp(%rip), %rsi     /* status    */
        movq __afl_fork_pid(%rip), %rdi /* PID       */
        CALL_L64("waitpid")
cmpq $0, %rax
        jle  __afl_die

/* Relay wait status to pipe, then loop back. */

        movq $4, %rdx               /* length    */
        leaq __afl_temp(%rip), %rsi /* data      */
        movq $" STRINGIFY((FORKSRV_FD + 1)) ", %rdi         /* file desc */
        CALL_L64("write")

jmp  __afl_fork_wait_loop




__afl_fork_resume:

/* In child process: close fds, resume execution. */

        movq $" STRINGIFY(FORKSRV_FD) ", %rdi
        CALL_L64("close")

movq $" STRINGIFY((FORKSRV_FD + 1)) ", %rdi
        CALL_L64("close")

popq %rdx
        popq %rdx

        movq %r12, %rsp
        popq %r12

        movq  0(%rsp), %rax
        movq  8(%rsp), %rcx
        movq 16(%rsp), %rdi
        movq 32(%rsp), %rsi
        movq 40(%rsp), %r8
        movq 48(%rsp), %r9
        movq 56(%rsp), %r10
        movq 64(%rsp), %r11

        movq  96(%rsp), %xmm0
        movq 112(%rsp), %xmm1
        movq 128(%rsp), %xmm2
        movq 144(%rsp), %xmm3
        movq 160(%rsp), %xmm4
        movq 176(%rsp), %xmm5
        movq 192(%rsp), %xmm6
        movq 208(%rsp), %xmm7
        movq 224(%rsp), %xmm8
        movq 240(%rsp), %xmm9
        movq 256(%rsp), %xmm10
        movq 272(%rsp), %xmm11
        movq 288(%rsp), %xmm12
        movq 304(%rsp), %xmm13
        movq 320(%rsp), %xmm14
        movq 336(%rsp), %xmm15

        leaq 352(%rsp), %rsp

        jmp  __afl_store




        __afl_die:

xorq %rax, %rax
        CALL_L64("_exit")




__afl_setup_abort:

/* Record setup failure so that we don't keep calling
   shmget() / shmat() over and over again. */

        incb __afl_setup_failure(%rip)

movq %r12, %rsp
        popq %r12

        movq  0(%rsp), %rax
        movq  8(%rsp), %rcx
        movq 16(%rsp), %rdi
        movq 32(%rsp), %rsi
        movq 40(%rsp), %r8
        movq 48(%rsp), %r9
        movq 56(%rsp), %r10
        movq 64(%rsp), %r11

        movq  96(%rsp), %xmm0
        movq 112(%rsp), %xmm1
        movq 128(%rsp), %xmm2
        movq 144(%rsp), %xmm3
        movq 160(%rsp), %xmm4
        movq 176(%rsp), %xmm5
        movq 192(%rsp), %xmm6
        movq 208(%rsp), %xmm7
        movq 224(%rsp), %xmm8
        movq 240(%rsp), %xmm9
        movq 256(%rsp), %xmm10
        movq 272(%rsp), %xmm11
        movq 288(%rsp), %xmm12
        movq 304(%rsp), %xmm13
        movq 320(%rsp), %xmm14
        movq 336(%rsp), %xmm15

        leaq 352(%rsp), %rsp

        jmp __afl_return

.AFL_VARS:


#ifdef __APPLE__

.comm   __afl_area_ptr, 8
#ifndef COVERAGE_ONLY
    .comm   __afl_prev_loc, 8
#endif /* !COVERAGE_ONLY */
    .comm   __afl_fork_pid, 4
    .comm   __afl_temp, 4
    .comm   __afl_setup_failure, 1

#else

.lcomm   __afl_area_ptr, 8
#ifndef COVERAGE_ONLY
.lcomm   __afl_prev_loc, 8
#endif /* !COVERAGE_ONLY */
.lcomm   __afl_fork_pid, 4
.lcomm   __afl_temp, 4
.lcomm   __afl_setup_failure, 1

#endif /* ^__APPLE__ */

.comm    __afl_global_area_ptr, 8, 8

.AFL_SHM_ENV:
.asciz \"" SHM_ENV_VAR "\"

/* --- END --- */
;

#endif /* !_HAVE_AFL_AS_H */