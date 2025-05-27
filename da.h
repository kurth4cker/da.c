// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#ifndef DA_H_INCLUDED
#define DA_H_INCLUDED

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

// Pre defined array types. Order of values should be same. size, capacity and
// data. Names does not matter.
typedef struct da_int {
    size_t size, capacity;
    int *data;
} Da_Int;
typedef struct da_double {
    size_t size, capacity;
    double *data;
} Da_Double;
typedef struct da_size {
    size_t size, capacity;
    size_t *data;
} Da_Size;
typedef struct da_str {
    size_t size, capacity;
    const char **data;
} Da_Str;

// append given value to the end of array, initializes if necessary, grows if necessary.
bool da_int_append(Da_Int *arr, int val);
bool da_double_append(Da_Double *arr, double val);
bool da_size_append(Da_Size *arr, size_t val);
bool da_str_append(Da_Str *arr, const char *val);

// You can create your own dynamic arrays with this helper functions.
// See da.c for example implementations. You can also take a look at example.c.
#define da_init_if_needed(arr)    da_init_generic_if_needed((Da_Generic *)(arr), sizeof(*(arr)->data))
#define da_grow_if_needed(arr)    da_grow_generic_if_needed((Da_Generic *)(arr), sizeof(*(arr)->data))
#define da_destroy(arr)           da_destroy_generic((Da_Generic *)(arr))

typedef struct {
    size_t size, capacity;
    void *data;
} Da_Generic;

bool da_init_generic_if_needed(Da_Generic *arr, size_t objsize);
bool da_grow_generic_if_needed(Da_Generic *arr, size_t objsize);
void da_destroy_generic(Da_Generic *arr);

#endif // DA_H_INCLUDED
