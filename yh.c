//
// Created by yunhao on 18-3-15.
//

#include "yh.h"


void yh_wait(){
    int num;
    printf("enter 1:");
    scanf("%d", &num);
    if(num == 1)
        printf("ok\n");
}

void yh_print_s(u8* buf){
    printf("%s\n", buf);
}

void yh_write_file(u8* out_file, u8* buf, s32 len, s32 apped){
    if(apped == 0){
        s32 fd = open(out_file, O_RDWR | O_CREAT, 0666);
        write(fd, buf, len);
        close(fd);
    }
    else{
        printf("append mode\n");
        s32 fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0666);
        write(fd, buf, len);
        close(fd);
    }
}

void yh_read_file(u8* in_file, u8* buf, s32 len){
    s32 fd = open(in_file, O_RDWR | O_CREAT | O_EXCL, 0666);
    if(fd < 0){
        close(fd);
        fd = open(in_file, O_RDWR);
        read(fd, buf, len);
    }
    close(fd);
}

void yh_check_ifdef(){
    printf("for yes:\n");
#ifdef __linux__
    printf("__linux__ yes\n");
#endif
#ifdef AFL_LIB
    printf("AFL_LIB yes\n");
#endif
#ifdef HAVE_AFFINITY
    printf("HAVE_AFFINITY yes\n");
#endif
#ifdef __x86_64__
    printf("__x86_64__ yes\n");
#endif
#ifdef RLIMIT_AS
    printf("RLIMIT_AS yes\n");
#endif
#ifdef __APPLE__
    printf("__APPLE__ yes\n");
#endif
#ifdef IGNORE_FINDS
    printf("IGNORE_FINDS yes\n");
#endif
#ifdef __FreeBSD__
    printf("__FreeBSD__ yes\n");
#endif
#ifdef __OpenBSD__
    printf("__OpenBSD__ yes\n");
#endif
#ifdef SIMPLE_FILES
    printf("SIMPLE_FILES yes\n");
#endif
#ifdef __sun
    printf("__sun yes\n");
#endif

    printf("for no:\n");
#ifndef __linux__
    printf("__linux__ no\n");
#endif
#ifndef AFL_LIB
    printf("AFL_LIB no\n");
#endif
#ifndef HAVE_AFFINITY
    printf("HAVE_AFFINITY no\n");
#endif
#ifndef __x86_64__
    printf("__x86_64__ no\n");
#endif
#ifndef RLIMIT_AS
    printf("RLIMIT_AS no\n");
#endif
#ifndef __APPLE__
    printf("__APPLE__ no\n");
#endif
#ifndef IGNORE_FINDS
    printf("IGNORE_FINDS no\n");
#endif
#ifndef __FreeBSD__
    printf("__FreeBSD__ no\n");
#endif
#ifndef __OpenBSD__
    printf("__OpenBSD__ no\n");
#endif
#ifndef SIMPLE_FILES
    printf("SIMPLE_FILES no\n");
#endif
#ifndef __sun
    printf("__sun no\n");
#endif
}