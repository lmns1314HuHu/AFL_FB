//
// Created by yunhao on 18-3-15.
//

#include "yh.h"


void yh_wait(){
    int num;
    printf("enter 1 to continue, enter 2 to exit program:");
    scanf("%d", &num);
    if(num == 1)
        printf("continue\n");
    else if(num == 2){
        printf("exit\n");
        exit(0);
    }
    else yh_wait();
}

void yh_print_s(u8* buf){
    printf("%s\n", buf);
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

void yh_fprintf_str(u8* out_file, u8* mode, char* context){
    FILE *out = fopen(out_file, mode);
    if(out == NULL){
        printf("create new one");
        yh_wait();
        out = fopen(out_file, "w");
        fclose(out);
        out = fopen(out_file, mode);
    }
    fprintf(out, context, NULL);
    fclose(out);
}

void yh_mark_start(){
    printf("yh mark start point\n");
}

void yh_mark_end(){
    printf("yh mark end point\n");
}

void yh_check_bits_u64(u64 num){
    int i = 64;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}
void yh_check_bits_u32(u32 num){
    int i = 32;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}
void yh_check_bits_u16(u16 num){
    int i = 16;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}
void yh_check_bits_u8(u8 num){
    int i = 8;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}

void yh_check_bits_s64(s64 num){
    int i = 64;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}
void yh_check_bits_s32(s32 num){
    int i = 32;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}
void yh_check_bits_s16(s16 num){
    int i = 16;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}
void yh_check_bits_s8(s8 num){
    int i = 8;
    int stk[100];
    memset(stk, -1, sizeof(stk));
    int cur = 0;
    while(i--){
        stk[cur++] = num & 1;
        num >>= 1;
    }
    int cnt = 0;
    while(cur){
        printf("%d", stk[cur-1]);
        cur--;
        cnt++;
        if(cnt == 8){
            printf(" ");
            cnt = 0;
        }
    }
    printf("\n");
}

void yh_change_binary_to_ascii(u8* in_file, u8* out_file){
    FILE* in = fopen(in_file, "rb");
    FILE* out = fopen(out_file, "w");
    char buf[10];
    int actual_size = 0;
    while(actual_size = fread(buf, 1, 8, in)){
        int i = 0;
        for (; i < actual_size; i++){
            fprintf(out, "%c", buf[i]);
        }
    }
    fclose(out);
    fclose(in);
}

void yh_change_binary_to_bits(u8* in_file, u8* out_file){
    FILE* in = fopen(in_file, "rb");
    FILE* out = fopen(out_file, "w");
    char buf[10];
    int actual_size = 0;
    while(actual_size = fread(buf, 1, 8, in)){
        int i = 0;
        for (; i < actual_size; i++){
            int j = 8;
            int stk[10];
            int cur = 0;
            while(j--){
                stk[cur++] = buf[i] & 1;
                buf[i] >>= 1;
            }
            while(cur){
                fprintf(out, "%d", stk[cur - 1]);
                cur--;
            }
            fprintf(out, " ");
        }
        fprintf(out, "\n");
    }
    fclose(in);
    fclose(out);
}

void yh_warn(){
    printf("==================warn==================\n");
}

void yh_print_tb_to_file(void *trace_bits, u8* out_file){
    u16* tb = (u16*) trace_bits;
//    FILE* out = fopen(out_file, "w");
    int cnt = 0;
    for(int i = 0; i < 32768; i++){
        if((int)tb[i] != 65535)
            printf("%4d ", tb[i]);
        cnt++;
        if(cnt == 256){
            cnt = 0;
//            fprintf(out, "\n");
        }
    }
//    fclose(out);
}

void yh_copy_array(u8* array, u8* array_copy, int len){
    memcpy(array_copy, array, len);
}

void yh_check_diff(u8* array, u8* array_copy, int len){
    int flag = 0;
    for (int i = 0; i < len; i++){
        if(array[i] != array_copy[i]){
            flag = 1;
            break;
        }
    }
    if(flag){
        printf("is changed by something!\n");
    }
    else{
        printf("is virgin!\n");
    }
}

//void yh_write_file(u8* out_file, u8* buf, s32 len, s32 apped){
//    if(apped == 0){
//        s32 fd = open(out_file, O_RDWR | O_CREAT, 0666);
//        write(fd, buf, len);
//        close(fd);
//    }
//    else{
//        printf("append mode\n");
//        s32 fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0666);
//        write(fd, buf, len);
//        close(fd);
//    }
//}

//void yh_read_file(u8* in_file, u8* buf, s32 len){
//    s32 fd = open(in_file, O_RDWR | O_CREAT | O_EXCL, 0666);
//    if(fd < 0){
//        close(fd);
//        fd = open(in_file, O_RDWR);
//        read(fd, buf, len);
//    }
//    close(fd);
//}