// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#ifndef DA_H_INCLUDED
#define DA_H_INCLUDED

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#define Da(type) Da_##type

#define da__implement_append(type)                                                       \
bool da_append_##type(Da(type) *arr, type val)                                           \
{                                                                                        \
	if (!da__init_if_needed((void **)&arr->data, &arr->capacity, sizeof(type)) ||             \
	    !da__grow_if_needed((void **)&arr->data, &arr->capacity, arr->size, sizeof(type))) {  \
		    return false;                                                        \
	}                                                                                \
	arr->data[arr->size] = val;                                                      \
	arr->size++;                                                                     \
	return true;                                                                     \
}

#define da_implement(type)       \
typedef struct {                 \
	size_t size, capacity;   \
	type *data;              \
} Da(type);                      \
da__implement_append(type)

#define da_append(type, arr, val) da_append_##type(arr, val)

bool da__init_if_needed(void **data, size_t *capacity, size_t objsize);
bool da__grow_if_needed(void **data, size_t *capacity, size_t size, size_t objsize);

#endif // DA_H_INCLUDED
