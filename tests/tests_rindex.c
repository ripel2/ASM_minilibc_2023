#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

char *(*my_rindex)(const char *, int);

void init_rindex(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_rindex = dlsym(handle, "rindex");
}

Test(my_rindex, rindex_basic_1, .init = init_rindex, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_rindex(str, 'W');

    cr_assert_eq(ptr, str + 6);
}

Test(my_rindex, rindex_basic_2, .init = init_rindex, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_rindex(str, 'o');

    cr_assert_eq(ptr, str + 7);
}

Test(my_rindex, rindex_basic_3, .init = init_rindex, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_rindex(str, 'H');

    cr_assert_eq(ptr, str);
}   

Test(my_rindex, rindex_not_found, .init = init_rindex, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_rindex(str, 'z');

    cr_assert_null(ptr);
}

Test(my_rindex, searching_null_term, .init = init_rindex, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_rindex(str, '\0');

    cr_assert_eq(ptr, str + 13);
}

Test(my_rindex, memory_tricks_1, .init = init_rindex, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_rindex(str, 'o');

    cr_assert_eq(ptr, str + 7);
    cr_assert_eq(ptr, my_rindex(str, 'o'));
}

Test(my_rindex, memory_tricks_2, .init = init_rindex, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_rindex(str, 'o');

    strlen("sefjeshfi");
    cr_assert_eq(ptr, str + 7);
    cr_assert_eq(ptr, my_rindex(str, 'o'));
    cr_assert_eq(ptr, my_rindex(str, 'o'));
}
