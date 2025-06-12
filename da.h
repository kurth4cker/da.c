// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#ifndef DA_H_INCLUDED
#define DA_H_INCLUDED

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define da_define_struct(Array_Type, Type)     \
    typedef struct {                           \
        size_t size, capacity;                 \
        Type *data;                            \
    } Array_Type

#define da_declare_append(Array_Type, Type, Name) \
    bool da_append_##Name(Array_Type *arr, Type val)

// Pre defined array types. Order of values should be same. size, capacity and
// data. Names does not matter.
da_define_struct(Da_Int, int);
da_define_struct(Da_Double, double);
da_define_struct(Da_Size, size_t);
da_define_struct(Da_Str, const char *);

// append given value to the end of array, initializes if necessary, grows if necessary.
// bool da_append_int(Da_Int *arr, int val);
da_declare_append(Da_Int, int, int);
da_declare_append(Da_Double, double, double);
da_declare_append(Da_Size, size_t, size);
da_declare_append(Da_Str, const char *, str);


// You can create your own dynamic arrays with this helper functions.
// See da.c for example implementations. You can also take a look at example.c.
#define da_init_if_needed(arr)    da_generic_init_if_needed((Da_Generic *)(arr), sizeof(*(arr)->data))
#define da_grow_if_needed(arr)    da_generic_grow_if_needed((Da_Generic *)(arr), sizeof(*(arr)->data))
#define da_destroy(arr)          \
    do {                         \
        free((arr)->data);       \
        (arr)->capacity = 0;     \
    } while (0)

da_define_struct(Da_Generic, void);

bool da_generic_init_if_needed(Da_Generic *arr, size_t objsize);
bool da_generic_grow_if_needed(Da_Generic *arr, size_t objsize);
void da_generic_destroy(Da_Generic *arr);

#endif // DA_H_INCLUDED
