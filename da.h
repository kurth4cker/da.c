// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#ifndef DA_H_INCLUDED
#define DA_H_INCLUDED

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t size, capacity;
    int *data;
} Da_Int;
bool da_int_append(Da_Int *arr, int val);

typedef struct {
    size_t size, capacity;
    double *data;
} Da_Double;
bool da_double_append(Da_Double *arr, double val);

typedef struct {
    size_t size, capacity;
    size_t *data;
} Da_Size;
bool da_size_append(Da_Size *arr, size_t val);

typedef struct {
    size_t size, capacity;
    const char **data;
} Da_Str;
bool da_str_append(Da_Str *arr, const char *val);

#define da_init_if_needed(arr) da_init_generic_if_needed((Da_Generic *)(arr), sizeof(*(arr)->data))
#define da_grow_if_needed(arr) da_grow_generic_if_needed((Da_Generic *)(arr), sizeof(*(arr)->data))
#define da_destroy(arr) da_destroy_generic((Da_Generic *)(arr))

typedef struct {
    size_t size, capacity;
    void *data;
} Da_Generic;

bool da_init_generic_if_needed(Da_Generic *arr, size_t objsize);
bool da_grow_generic_if_needed(Da_Generic *arr, size_t objsize);
void da_destroy_generic(Da_Generic *arr);

#endif // DA_H_INCLUDED
