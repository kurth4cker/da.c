// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "da.h"

int
main(void)
{
    Da_Str arr = { 0 };
    da_str_append(&arr, "hello");
    da_str_append(&arr, "world");

    assert(arr.data != NULL);
    assert(arr.capacity > arr.size);
    assert(arr.size == 2);
    assert(strcmp(arr.data[0], "hello") == 0);
    assert(strcmp(arr.data[1], "world") == 0);
}
