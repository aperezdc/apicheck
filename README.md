apicheck.h
==========

Standalone, header-only implementation of GLib's
[g_return_if_fail()](https://developer.gnome.org/glib/unstable/glib-Warnings-and-Assertions.html#g-return-if-fail)
and
[g_return_val_if_fail()](https://developer.gnome.org/glib/unstable/glib-Warnings-and-Assertions.html#g-return-val-if-fail).


Installation
------------

Using [clib](https://github.com/clibs/clib):

```sh
clib install aperezdc/apicheck --save
```


Usage
-----

The `api_check_return(expr)` macro checks whether an expression evaluates to
a “truthy” value, otherwise it will `return` from the enclosing function:

```c
void init_parser(struct parser *p)
{
  /* Checks whether 'p' is non-null. */
  api_check_return(p);
  /* ... */
}
```

The `api_check_return_val(expr, val)` macro works similarly, but if the check
failed, it will `return` the specified value from the enclosing function:

```c
FILE* open_file(const char *path)
{
  /* Checks whether 'path' is non-null, and it is different from "-". */
  api_check_return_val(path, NULL);
  api_check_return_val(strcmp(path, "-") != 0, NULL);
  /* ... */
}
```

When a check fails, a message indicating the failure is printed (to `stderr`
by default, see [customization](#customization) below):

```
API check 'path' failed at open_file (example.c:42)
```


Customization
-------------

### Aborting on Failures

If the macro `API_CHECK_SHOULD_ABORT` is defined to a non-zero value (e.g.
with `-DAPI_CHECK_SHOULD_ABORT=1`), then `abort()` will be called whenever
a check fails. This can be useful during development and/or for debug
builds.


### Disabling at Build-Time

If the macro `API_CHECK_DISABLE` is defined to a non-zero value (e.g. with
`-DAPI_CHECK_DISABLE=1`) then API checks are not compiled in. This can be
interesting for release builds.


### Setting the Output File

It is possible to log check failures to a location other than `stderr`. You
can define the macro `API_CHECK_OUTPUT_FILE` to an expression which evaluates
to a `FILE*`. The macro is expanded once for each use of `api_check_return()` /
`api_check_return_val()`, and if the value is `NULL` the standard error output
is used as fall-back, to ensure that no messages are silently discarded.

For example, the following would send the output to an `apicheck.log` file,
and if the file cannot be open during the startup of the program, standard
error will still be used:

```c
/*
 * Build with -DAPI_CHECK_OUTPUT_FILE=apicheck_log_file
 */

FILE* apicheck_log_file = NULL;

int main(int argc, char *argv[])
{
  apicheck_log_file = fopen("apicheck.log", "w");
  /* ... */
}
```
