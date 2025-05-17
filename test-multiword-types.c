// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>

#include "da.h"

int
main(void)
{
    Da_Str arr = { 0 };
    da_str_append(&arr, "hello");
    da_str_append(&arr, "world");

    for (size_t i = 0; i < arr.size; i++) {
        printf("%s\n", arr.data[i]);
    }
}
