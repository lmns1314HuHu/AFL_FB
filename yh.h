//
// Created by yunhao on 18-3-15.
//

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/file.h>
#include <string.h>
#include "types.h"

void yh_wait();

void yh_print_s(u8* buf);

void yh_write_file(u8* out_file, u8* buf, s32 len, s32 apped);

void yh_read_file(u8* in_file, u8* buf, s32 len);

void yh_check_ifdef();

