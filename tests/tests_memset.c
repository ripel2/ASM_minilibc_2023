#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

void *(*my_memset)(void *, int, size_t);

void init_memset(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_memset = dlsym(handle, "memset");
}

Test(my_memset, memset_string_basic_1, .init = init_memset, .timeout = 2)
{
    char str[] = "Hello World !";

    my_memset(str, 'a', 5);
    cr_assert_str_eq(str, "aaaaa World !");
}

Test(my_memset, memset_string_basic_2, .init = init_memset, .timeout = 2)
{
    char str[] = "AAAAAA";

    my_memset(str, 'B', 6);
    cr_assert_str_eq(str, "BBBBBB");
}

Test(my_memset, memset_nothing, .init = init_memset, .timeout = 2)
{
    char str[] = "Hello World !";

    my_memset(str, 'a', 0);
    cr_assert_str_eq(str, "Hello World !");
}

Test(my_memset, memset_nothing_on_null, .init = init_memset, .timeout = 2)
{
    char *str = NULL;

    my_memset(str, 'o', 0);
    cr_assert_null(str);
}

Test(my_memset, modified_ptr_1, .init = init_memset, .timeout = 2)
{
    char str[] = "Hello World !";
    char *ptr = my_memset(str, 'a', 5);

    cr_assert_eq(ptr, str);
    cr_assert_str_eq(str, "aaaaa World !");
}

Test(my_memset, modified_ptr_2, .init = init_memset, .timeout = 2)
{
    char str[] = "Quand l'imposteur est suspect";
    char *ptr = my_memset(str + 8, 'o', 9);

    cr_assert_eq(ptr, str + 8);
    cr_assert_str_eq(str, "Quand l'ooooooooo est suspect");
}

Test(my_memset, int_list_1, .init = init_memset, .timeout = 2)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    my_memset(list, 0, 10 * sizeof(int));
    cr_assert_eq(list[0], 0);
    cr_assert_eq(list[1], 0);
    cr_assert_eq(list[2], 0);
    cr_assert_eq(list[3], 0);
    cr_assert_eq(list[4], 0);
    cr_assert_eq(list[5], 0);
    cr_assert_eq(list[6], 0);
    cr_assert_eq(list[7], 0);
    cr_assert_eq(list[8], 0);
    cr_assert_eq(list[9], 0);
}

Test(my_memset, int_list_2, .init = init_memset, .timeout = 2)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    my_memset(list, 0, 5 * sizeof(int));
    cr_assert_eq(list[0], 0);
    cr_assert_eq(list[1], 0);
    cr_assert_eq(list[2], 0);
    cr_assert_eq(list[3], 0);
    cr_assert_eq(list[4], 0);
    cr_assert_eq(list[5], 6);
    cr_assert_eq(list[6], 7);
    cr_assert_eq(list[7], 8);
    cr_assert_eq(list[8], 9);
    cr_assert_eq(list[9], 10);
}

Test(my_memset, int_list_3, .init = init_memset, .timeout = 2)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    my_memset(list + 2, 0, 3 * sizeof(int));
    cr_assert_eq(list[0], 1);
    cr_assert_eq(list[1], 2);
    cr_assert_eq(list[2], 0);
    cr_assert_eq(list[3], 0);
    cr_assert_eq(list[4], 0);
    cr_assert_eq(list[5], 6);
    cr_assert_eq(list[6], 7);
    cr_assert_eq(list[7], 8);
    cr_assert_eq(list[8], 9);
    cr_assert_eq(list[9], 10);
}

Test(my_memset, int_list_empty, .init = init_memset, .timeout = 2)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    my_memset(list, 0, 0);
    cr_assert_eq(list[0], 1);
    cr_assert_eq(list[1], 2);
    cr_assert_eq(list[2], 3);
    cr_assert_eq(list[3], 4);
    cr_assert_eq(list[4], 5);
    cr_assert_eq(list[5], 6);
    cr_assert_eq(list[6], 7);
    cr_assert_eq(list[7], 8);
    cr_assert_eq(list[8], 9);
    cr_assert_eq(list[9], 10);
}

Test(my_memset, unaligned_set_1, .init = init_memset, .timeout = 2)
{
    long long list[] = {0xffffffffffff, 0xffff0000ffff, 0xf0f0f0f0, 0x0f0f0f0f, 0x12345678, 0x87654321};

    my_memset(list, 0xff, 3 * sizeof(long long int));
    cr_assert_eq(list[0], 0xffffffffffffffff);
    cr_assert_eq(list[1], 0xffffffffffffffff);
    cr_assert_eq(list[2], 0xffffffffffffffff);
    cr_assert_eq(list[3], 0x0f0f0f0f);
    cr_assert_eq(list[4], 0x12345678);
    cr_assert_eq(list[5], 0x87654321);
}

Test(my_memset, unaligned_set_2, .init = init_memset, .timeout = 2)
{
    short list[] = {0xffff, 0x0000, 0xf0f0, 0x0f0f, 0x1234, 0x5678, 0x8765, 0x4321};

    my_memset(list, 0xff, 3 * sizeof(short));
    cr_assert_eq(list[0], 0xffffffff);
    cr_assert_eq(list[1], 0xffffffff);
    cr_assert_eq(list[2], 0xffffffff);
    cr_assert_eq(list[3], 0x0f0f);
    cr_assert_eq(list[4], 0x1234);
    cr_assert_eq(list[5], 0x5678);
    cr_assert_eq(list[6], 0xffff8765);
    cr_assert_eq(list[7], 0x4321);
}
