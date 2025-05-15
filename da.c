// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>
#include <assert.h>

#include "da.h"

bool da__init_if_needed(void **data, size_t *capacity, size_t objsize)
{
	assert(data != NULL);
	if (*data != NULL) {
		return true;
	}
	const size_t initial_capacity = 16;
	void *ptr = malloc(objsize * initial_capacity);
	if (ptr == NULL) {
		return false;
	}
	*data = ptr;
	*capacity = initial_capacity;
	return true;
}

bool da__grow_if_needed(void **data, size_t *capacity, size_t size, size_t objsize)
{
	assert(data != NULL);
	assert(*data != NULL);
	if (*capacity > size) {
		return true;
	}
	const size_t new_capacity = 2 * *capacity;
	void *ptr = realloc(*data, new_capacity * objsize);
	if (ptr == NULL) {
		return false;
	}
	*data = ptr;
	*capacity = new_capacity;
	return true;
}
