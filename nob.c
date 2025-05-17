// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#define NOB_EXPERIMENTAL_DELETE_OLD
#define NOB_IMPLEMENTATION
#include "nob.h"

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

int
main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    Nob_Cmd cmd = { 0 };
    add_cc_from_env_or(&cmd, "cc");
    nob_cmd_append(&cmd, "-std=c99", "-pedantic",
                   "-g",
                   "-Wall", "-Wextra",
                   "-Werror");
    nob_cc_output(&cmd, "example");
    nob_cc_inputs(&cmd, "da.c", "example.c");
    if (!nob_cmd_run_sync_and_reset(&cmd)) {
        exit(EXIT_FAILURE);
    }
    nob_cmd_append(&cmd, "./example");
    if (!nob_cmd_run_sync_and_reset(&cmd)) {
        exit(EXIT_FAILURE);
    }

    add_cc_from_env_or(&cmd, "cc");
    nob_cmd_append(&cmd, "-std=c99", "-pedantic",
                   "-g",
                   "-Wall", "-Wextra",
                   "-Werror");
    nob_cc_output(&cmd, "test-multiword-types");
    nob_cc_inputs(&cmd, "da.c", "test-multiword-types.c");
    if (!nob_cmd_run_sync_and_reset(&cmd)) {
        exit(EXIT_FAILURE);
    }
    nob_cmd_append(&cmd, "./test-multiword-types");
    if (!nob_cmd_run_sync_and_reset(&cmd)) {
        exit(EXIT_FAILURE);
    }
}
