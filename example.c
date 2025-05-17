// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>

#include "da.h"

int
main(void)
{
    assert(offsetof(Da_Size, data) == offsetof(Da_Generic, data));
    assert(offsetof(Da_Size, size) == offsetof(Da_Generic, size));
    assert(offsetof(Da_Size, capacity) == offsetof(Da_Generic, capacity));

    const size_t limit = 17;
    {
        Da_Size arr = { 0 };
        for (size_t i = 0; i < limit; i++) {
            da_size_append(&arr, i);
            assert(arr.data[i] == i);
        }

        assert(arr.size == limit);
        assert(arr.data != NULL);
        assert(arr.size <= arr.capacity);
        da_destroy((Da_Generic *)&arr);
    }

    {
        Da_Int arr = { 0 };
        for (int i = 0; i < (int)limit; i++) {
            da_int_append(&arr, i);
            assert(arr.data[i] == i);
        }

        assert(arr.size == limit);
        assert(arr.data != NULL);
        assert(arr.size <= arr.capacity);
        da_destroy((Da_Generic *)&arr);
    }
}
