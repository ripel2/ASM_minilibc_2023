#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

char *(*my_strstr)(const char *, const char *);

void init_strstr(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strstr = dlsym(handle, "strstr");
}

Test(my_strstr, strstr_basic_1, .init = init_strstr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strstr(str, "World");

    cr_assert_eq(ptr, str + 6);
}

Test(my_strstr, strstr_basic_2, .init = init_strstr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strstr(str, "Hello");

    cr_assert_eq(ptr, str);
}

Test(my_strstr, strstr_not_found, .init = init_strstr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strstr(str, "z");

    cr_assert_null(ptr);
}

Test(my_strstr, searching_empty, .init = init_strstr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strstr(str, "");

    cr_assert_eq(ptr, str);
}

Test(my_strstr, searching_null_term, .init = init_strstr, .timeout = 2)
{
    char str[] = "Hello World !";
    // this is the same as searching for ""
    char *ptr = my_strstr(str, "\0");

    cr_assert_eq(ptr, str);
}

Test(my_strstr, searching_empty_in_empty, .init = init_strstr, .timeout = 2)
{
    char str[] = "";
    char *ptr = my_strstr(str, "");

    cr_assert_eq(ptr, str);
}

Test(my_strstr, mess_with_memory_1, .init = init_strstr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strstr(str, "World");

    strlen("test");
    memcpy(str, "test", 4);
    cr_assert_eq(ptr, str + 6);
    str[4] = ' ';
    cr_assert_eq(ptr, str + 6);
    str[2] = 'x';
    cr_assert_eq(ptr, str + 6);
    str[8] = strlen(str) * 0 + (int)'e';
    cr_assert_eq(ptr, str + 6);
}