/*
 * apicheck.h
 * Copyright (C) 2017 Adrian Perez <aperez@igalia.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef APICHECK_H
#define APICHECK_H

#include <stdlib.h>
#include <stdio.h>

#ifndef API_CHECK_OUTPUT_FILE
#define API_CHECK_OUTPUT_FILE stderr
#endif /* !API_CHECK_OUTPUT_FILE */

#ifndef API_CHECK_SHOULD_ABORT
#define API_CHECK_SHOULD_ABORT 0
#endif /* !API_CHECK_SHOULD_ABORT */

#define api_check_return_val(expr, val) do { \
        if (!(expr)) { \
            fprintf (API_CHECK_OUTPUT_FILE, \
                     "API check '%s' failed at %s (%s:%d)\n", \
                     #expr, __func__, __FILE__, __LINE__); \
            fflush (API_CHECK_OUTPUT_FILE); \
            if (API_CHECK_SHOULD_ABORT) \
                abort (); \
            return val; \
        } \
    } while (0)

#define api_check_return(expr) api_check_return_val(expr,)

#endif /* !APICHECK_H */
