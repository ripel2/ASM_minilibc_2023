#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

char *(*my_strchr)(const char *, int);

void init_strchr(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strchr = dlsym(handle, "strchr");
}

Test(my_strchr, strchr_basic_1, .init = init_strchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strchr(str, 'W');

    cr_assert_eq(ptr, str + 6);
}

Test(my_strchr, strchr_basic_2, .init = init_strchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strchr(str, 'o');

    cr_assert_eq(ptr, str + 4);
}

Test(my_strchr, strchr_basic_3, .init = init_strchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strchr(str, 'H');

    cr_assert_eq(ptr, str);
}

Test(my_strchr, strchr_not_found, .init = init_strchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strchr(str, 'z');

    cr_assert_null(ptr);
}

Test(my_strchr, searching_null_term, .init = init_strchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strchr(str, '\0');

    cr_assert_eq(ptr, str + 13);
}

Test(my_strchr, memory_tricks_1, .init = init_strchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strchr(str, 'W');

    cr_assert_eq(ptr, str + 6);
    cr_assert_eq(ptr[0], 'W');
    cr_assert_eq(ptr[1], 'o');
    cr_assert_eq(ptr[2], 'r');
    cr_assert_eq(ptr[3], 'l');
    cr_assert_eq(ptr[4], 'd');
    cr_assert_eq(ptr[5], ' ');
    cr_assert_eq(ptr[6], '!');
    cr_assert_eq(ptr[7], '\0');
}

Test(my_strchr, memory_tricks_2, .init = init_strchr, .timeout = 2)
{
    char str[] = "Hello World !";
    strlen(str);
    memcpy(str + 6, "World !", 7);
    strlen("Just messing with the memory");
    char *ptr = my_strchr(str, 'W');

    cr_assert_eq(ptr, str + 6);
    cr_assert_eq(ptr[0], 'W');
    cr_assert_eq(ptr[1], 'o');
    cr_assert_eq(ptr[2], 'r');
    cr_assert_eq(ptr[3], 'l');
    cr_assert_eq(ptr[4], 'd');
    cr_assert_eq(ptr[5], ' ');
    cr_assert_eq(ptr[6], '!');
    cr_assert_eq(ptr[7], '\0');
}
