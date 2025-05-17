// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>
#include <assert.h>

#include "da.h"

typedef struct {
    size_t size, capacity;
    void *data;
} Array;

static bool
init_if_needed(Array *arr, size_t objsize)
{
    if (arr->data != NULL) {
        return true;
    }
    const size_t initial_capacity = 16;
    arr->data = calloc(initial_capacity, objsize);
    if (arr->data == NULL) {
        return false;
    }
    arr->capacity = initial_capacity;
    return true;
}

static bool
grow_if_needed(Array *arr, size_t objsize)
{
    assert(arr->data != NULL);
    assert(arr->capacity > 0);
    if (arr->capacity > arr->size) {
        return true;
    }
    const size_t new_capacity = arr->capacity * 2;
    void *data = realloc(arr->data, new_capacity * objsize);
    if (data == NULL) {
        return false;
    }
    arr->data = data;
    arr->capacity = new_capacity;
    return true;
}

bool da_size_append(Da_Size *arr, size_t val)
{
    assert(offsetof(Da_Size, data) == offsetof(Array, data));
    assert(offsetof(Da_Size, size) == offsetof(Array, size));
    assert(offsetof(Da_Size, capacity) == offsetof(Array, capacity));
    if (!init_if_needed((Array *)arr, sizeof(*arr->data)) ||
        !grow_if_needed((Array *)arr, sizeof(*arr->data))) {
            return false;
    }
    arr->data[arr->size] = val;
    arr->size++;
    return true;
}

bool da_str_append(Da_Str *arr, const char *val)
{
    (void)arr, (void)val;
    return true;
}
