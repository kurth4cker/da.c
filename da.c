// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>
#include <assert.h>

#include "da.h"

bool da_init_if_needed(Da_Generic *arr, size_t objsize)
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

bool da_grow_if_needed(Da_Generic *arr, size_t objsize)
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

void da_destroy(Da_Generic *arr)
{
    arr->capacity = 0;
    if (arr->data != NULL) {
        free(arr->data);
    }
}

bool da_int_append(Da_Int *arr, int val)
{
    if (!da_init_if_needed((Da_Generic *)arr, sizeof(*arr->data)) ||
        !da_grow_if_needed((Da_Generic *)arr, sizeof(*arr->data))) {
            return false;
    }
    arr->data[arr->size] = val;
    arr->size++;
    return true;
}

bool da_double_append(Da_Double *arr, double val)
{
    if (!da_init_if_needed((Da_Generic *)arr, sizeof(*arr->data)) ||
        !da_grow_if_needed((Da_Generic *)arr, sizeof(*arr->data))) {
            return false;
    }
    arr->data[arr->size] = val;
    arr->size++;
    return true;
}

bool da_size_append(Da_Size *arr, size_t val)
{
    if (!da_init_if_needed((Da_Generic *)arr, sizeof(*arr->data)) ||
        !da_grow_if_needed((Da_Generic *)arr, sizeof(*arr->data))) {
            return false;
    }
    arr->data[arr->size] = val;
    arr->size++;
    return true;
}

bool da_str_append(Da_Str *arr, const char *val)
{
    if (!da_init_if_needed((Da_Generic *)arr, sizeof(*arr->data)) ||
        !da_grow_if_needed((Da_Generic *)arr, sizeof(*arr->data))) {
            return false;
    }
    arr->data[arr->size] = val;
    arr->size++;
    return true;
}
