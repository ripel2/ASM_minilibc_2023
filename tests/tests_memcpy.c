#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

void *(*my_memcpy)(void *, const void *, size_t);

void init_memcpy(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_memcpy = dlsym(handle, "memcpy");
}

Test(my_memcpy, memcpy_string_basic_1, .init = init_memcpy, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    my_memcpy(str, str2, 7);
    cr_assert_str_eq(str, "roujnob");
}

Test(my_memcpy, memcpy_string_basic_2, .init = init_memcpy, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    my_memcpy(str, str2, 3);
    cr_assert_str_eq(str, "roujour");
}

Test(my_memcpy, memcpy_string_add_ptr, .init = init_memcpy, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    my_memcpy(str + 2, str2, 3);
    cr_assert_str_eq(str, "borouur");
}

Test(my_memcpy, malloc_memory_1, .init = init_memcpy, .timeout = 2)
{
    char *str = strdup("AMOGUS");
    char *str2 = strdup("AMIGOS");

    my_memcpy(str2, str, 6);
    cr_assert_str_eq(str2, "AMOGUS");
    free(str);
    free(str2);
}

Test(my_memcpy, int_list_1, .init = init_memcpy, .timeout = 2)
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    my_memcpy(tab2, tab, sizeof(int) * 10);
    for (size_t c = 0; c < 10; c++) {
        cr_assert_eq(tab2[c], tab[c]);
    }
}

Test(my_memcpy, int_list_2, .init = init_memcpy, .timeout = 2)
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab2[] = {42, -42, 0, 0, 0, 0, 0, 0, 2, 1};

    my_memcpy(tab2 + 2, tab, sizeof(int) * 6);
    cr_assert_eq(tab2[0], 42);
    cr_assert_eq(tab2[1], -42);
    for (size_t c = 2; c < 8; c++) {
        cr_assert_eq(tab2[c], tab[c - 2]);
    }
}

Test(my_memcpy, int_list_malloc_1, .init = init_memcpy, .timeout = 2)
{
    int *tab = malloc(sizeof(int) * 10);
    int *tab2 = malloc(sizeof(int) * 10);

    for (size_t c = 0; c < 10; c++) {
        tab[c] = c;
        tab2[c] = 0;
    }
    my_memcpy(tab2, tab, sizeof(int) * 10);
    for (size_t c = 0; c < 10; c++) {
        cr_assert_eq(tab2[c], tab[c]);
    }
    free(tab);
    free(tab2);
}

Test(my_memcpy, malloc_memory_2, .init = init_memcpy, .timeout = 2)
{
    char *str = strdup("AMOGUS");
    char *str2 = strdup("AMIGOS");

    my_memcpy(str2 + 2, str, 2);
    cr_assert_str_eq(str2, "AMAMOS");
    free(str);
    free(str2);
}

Test(my_memcpy, unaligned_copy_1, .init = init_memcpy, .timeout = 2)
{
    int tab[] = {1, 2, 3, 4, 67107840, 6, 7, 8, 9, 10};
    int tab2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    my_memcpy(tab2 + 1, tab, sizeof(int) * 4 + 3);
    cr_assert_eq(tab2[0], 0);
    cr_assert_eq(tab2[1], 1);
    cr_assert_eq(tab2[2], 2);
    cr_assert_eq(tab2[3], 3);
    cr_assert_eq(tab2[4], 4);
    cr_assert_eq(tab2[5], 16776192);
}

Test(my_memcpy, unaligned_copy_2, .init = init_memcpy, .timeout = 2)
{
    int tab[] = {0xffffffff, 0x0000ffff, 0xffff, 0xf0f0f0f0};
    long long tab2[] = {0, 0};

    my_memcpy(tab2, tab, sizeof(int) * 4);
    cr_assert_eq(tab2[0], 0xffffffffffff);
    cr_assert_eq(tab2[1], 0xf0f0f0f00000ffff);
}
