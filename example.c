// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>

#include "da.h"

int
main(void)
{
    Da_Size arr = { 0 };
    const size_t limit = 17;
    for (size_t i = 0; i < limit; i++) {
        da_size_append(&arr, i);
        assert(arr.data[i] == i);
    }

    assert(arr.size == limit);
    assert(arr.data != NULL);
    assert(arr.size <= arr.capacity);
}
