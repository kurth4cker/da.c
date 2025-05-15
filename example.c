// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>

#include "da.h"

da_implement(size_t)

int
main(void)
{
	Da(size_t) arr = { 0 };
	for (size_t i = 0; i < 17; i++) {
		da_append(size_t, &arr, i);
	}

	for (size_t i = 0; i < arr.size; i++) {
		assert(arr.data[i] == i);
		printf("%zu\n", arr.data[i]);
	}
}
