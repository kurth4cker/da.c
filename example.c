// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>

#include "da.h"

int
main(void)
{
    Da_Size arr = { 0 };
    for (size_t i = 0; i < 17; i++) {
        da_size_append(&arr, i);
        assert(arr.data[i] == i);
    }

    assert(arr.size == 17);
    assert(arr.data != NULL);
    assert(arr.size <= arr.capacity);
    for (size_t i = 0; i < arr.size; i++) {
        printf("%zu\n", arr.data[i]);
    }
}
