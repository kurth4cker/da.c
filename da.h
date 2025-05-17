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
bool da_int_init(Da_Int *arr);

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

#endif // DA_H_INCLUDED
