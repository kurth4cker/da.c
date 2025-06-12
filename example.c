// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "da.h"

typedef struct {
    const char *name;
    const char *language;
} Project;

static inline Project project(const char *name, const char *language)
{
    Project p = {
        .name = name,
        .language = language,
    };
    return p;
}

da_define_struct(Project_Array, Project);

static bool append_project(Project_Array *arr, Project val)
{
    if (!da_init_if_needed(arr) || !da_grow_if_needed(arr)) {
        return false;
    }
    arr->data[arr->size] = val;
    arr->size++;
    return true;
}

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
            da_append_size(&arr, i);
            assert(arr.data[i] == i);
        }

        assert(arr.size == limit);
        assert(arr.data != NULL);
        assert(arr.size <= arr.capacity);

        da_destroy(&arr);
    }

    {
        Da_Double arr = { 0 };
        for (size_t i = 0; i < limit; i++) {
            da_append_double(&arr, i / 10.0);
        }

        assert(arr.size == limit);
        assert(arr.data != NULL);
        assert(arr.size <= arr.capacity);
        // destroy array
        da_destroy(&arr);
    }

    {
        Da_Int arr = { 0 };
        for (int i = 0; i < (int)limit; i++) {
            da_append_int(&arr, i);
            assert(arr.data[i] == i);
        }

        assert(arr.size == limit);
        assert(arr.data != NULL);
        assert(arr.size <= arr.capacity);

        da_destroy(&arr);
    }

    {
        Da_Str arr = { 0 };
        da_append_str(&arr, "hello");
        da_append_str(&arr, "world");

        assert(arr.data != NULL);
        assert(arr.capacity > arr.size);
        assert(arr.size == 2);
        assert(strcmp(arr.data[0], "hello") == 0);
        assert(strcmp(arr.data[1], "world") == 0);

        da_destroy(&arr);
    }

    {
        Project_Array arr = { 0 };
        append_project(&arr, project("da.c", "C"));
        append_project(&arr, project("sample-go", "Go"));

        assert(arr.data != NULL);
        assert(arr.capacity > arr.size);
        assert(arr.size == 2);
        assert(strcmp(arr.data[1].name, "sample-go") == 0);

        da_destroy(&arr);
    }

    {
        Da_Generic arr = { 0 };
        for (size_t i = 0; i < limit; i++) {
            da_generic_append(&arr, &i, sizeof(i));
        }

        assert(arr.size == limit);
        assert(arr.data != NULL);
        assert(arr.size <= arr.capacity);

        da_destroy(&arr);
    }
}
