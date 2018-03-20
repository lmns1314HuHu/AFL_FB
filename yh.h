//
// Created by yunhao on 18-3-15.
//

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "types.h"
#include <sys/file.h>

void yh_wait();

void yh_print_s(u8* buf);

void yh_check_ifdef();

void yh_fprintf_str(u8* out_file, u8* mode, char* context);

void yh_mark_start();

void yh_mark_end();

void yh_check_bits_u64(u64 num);
void yh_check_bits_u32(u32 num);
void yh_check_bits_u16(u16 num);
void yh_check_bits_u8(u8 num);
void yh_check_bits_s64(s64 num);
void yh_check_bits_s32(s32 num);
void yh_check_bits_s16(s16 num);
void yh_check_bits_s8(s8 num);

void yh_change_binary_to_ascii(u8* in_file, u8* out_file);

void yh_change_binary_to_bits(u8* in_file, u8* out_file);

void yh_warn();

void yh_print_tb_to_file(void *trace_bits, u8* out_file);

//void yh_write_file(u8* out_file, u8* buf, s32 len, s32 apped);

//void yh_read_file(u8* in_file, u8* buf, s32 len);