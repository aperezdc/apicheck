/*
 * example.c
 * Copyright (C) 2017 Adrian Perez <aperez@igalia.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "apicheck.h"

static void
f1 (void *nonnull)
{
    api_check_return (nonnull);
}

static int
f2 (void *nonnull)
{
    api_check_return_val (nonnull, 0);
    return 1;
}

int
main (int argc, char *argv[])
{
    f1 (NULL);
    return f2 (NULL);
}
