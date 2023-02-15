#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

char *(*my_strrchr)(const char *, int);

void init_strrchr(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strrchr = dlsym(handle, "strrchr");
}

Test(my_strrchr, strrchr_basic_1, .init = init_strrchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strrchr(str, 'W');

    cr_assert_eq(ptr, str + 6);
}

Test(my_strrchr, strrchr_basic_2, .init = init_strrchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strrchr(str, 'o');

    cr_assert_eq(ptr, str + 7);
}

Test(my_strrchr, strrchr_basic_3, .init = init_strrchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strrchr(str, 'H');

    cr_assert_eq(ptr, str);
}   

Test(my_strrchr, strrchr_not_found, .init = init_strrchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strrchr(str, 'z');

    cr_assert_null(ptr);
}

Test(my_strrchr, searching_null_term, .init = init_strrchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strrchr(str, '\0');

    cr_assert_eq(ptr, str + 13);
}

Test(my_strrchr, memory_tricks_1, .init = init_strrchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strrchr(str, 'o');

    cr_assert_eq(ptr, str + 7);
    cr_assert_eq(ptr, my_strrchr(str, 'o'));
}

Test(my_strrchr, memory_tricks_2, .init = init_strrchr, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_strrchr(str, 'o');

    strlen("sefjeshfi");
    cr_assert_eq(ptr, str + 7);
    cr_assert_eq(ptr, my_strrchr(str, 'o'));
    cr_assert_eq(ptr, my_strrchr(str, 'o'));
}
