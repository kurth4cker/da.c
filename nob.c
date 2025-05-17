// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdarg.h>
#include <stdlib.h>

#define NOB_EXPERIMENTAL_DELETE_OLD
#define NOB_IMPLEMENTATION
#include "nob.h"

typedef struct {
    size_t size;
    const char *const *data;
} Str_Array;

static void
add_cc_from_env_or(Nob_Cmd *cmd, const char *default_cc)
{
    static const char *cc = NULL;
    if (cc == NULL) {
        cc = getenv("CC");
    }
    if (cc == NULL) {
        cc = default_cc;
    }
    nob_cmd_append(cmd, cc);
}

#define compile(cmd, output, ...) _compile(cmd, output, __VA_ARGS__, NULL)
static void
_compile(Nob_Cmd *cmd, const char *output, ...)
{
    add_cc_from_env_or(cmd, "cc");
    nob_cmd_append(cmd, "-std=c99", "-pedantic",
                   "-g",
                   "-Wall", "-Wextra",
                   "-Werror");
    nob_cc_output(cmd, output);

    va_list ap;
    va_start(ap, output);
    for (;;) {
        const char *arg = va_arg(ap, const char *);
        if (arg == NULL) {
            break;
        }
        nob_cc_inputs(cmd, arg);
    }
    va_end(ap);
    if (!nob_cmd_run_sync_and_reset(cmd)) {
        exit(EXIT_FAILURE);
    }
}

#define run(cmd, ...) _run(cmd, __VA_ARGS__, NULL)
static void
_run(Nob_Cmd *cmd, ...)
{
    va_list ap;
    va_start(ap, cmd);
    const char *progname = va_arg(ap, const char *);
    if (progname == NULL) {
        fprintf(stderr, "[ERROR] run should be called with at least two argument: cmd and program\n");
        exit(EXIT_FAILURE);
    }
    nob_cmd_append(cmd, progname);
    for (;;) {
        const char *arg = va_arg(ap, const char *);
        if (arg == NULL) {
            break;
        }
        nob_cmd_append(cmd, arg);
    }
    va_end(ap);
    if (!nob_cmd_run_sync_and_reset(cmd)) {
        exit(EXIT_FAILURE);
    }
}

int
main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    Nob_Cmd cmd = { 0 };
    compile(&cmd, "example","da.c", "example.c");
    compile(&cmd, "test-multiword-types", "da.c", "test-multiword-types.c");

	run(&cmd, "./example");
	run(&cmd, "./test-multiword-types");
}
