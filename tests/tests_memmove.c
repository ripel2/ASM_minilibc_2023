#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

void *(*my_memmove)(void *, const void *, size_t);

void init_memmove(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_memmove = memmove;
}

Test(my_memmove, specific_memmove_1, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    my_memmove(str, str + 3, 4);
    cr_assert_str_eq(str, "jourour");
}

Test(my_memmove, specific_memmove_2, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";

    my_memmove(str + 3, str, 4);
    cr_assert_str_eq(str, "bonbonj");
}

Test(my_memmove, specific_memmove_3, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";

    my_memmove(str + 3, str + 3, 4);
    cr_assert_str_eq(str, "bonjour");
}

Test(my_memmove, specific_memmove_4, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";

    my_memmove(str, str, 7);
    cr_assert_str_eq(str, "bonjour");
}

Test(my_memmove, specific_memmove_5, .init = init_memmove, .timeout = 2)
{
    char *str = strdup("au revoir");

    my_memmove(str + 3, str, 9);
    cr_assert_str_eq(str, "au au revoir");
    free(str);
}

Test(my_memmove, specific_memmove_6, .init = init_memmove, .timeout = 2)
{
    char *str = strdup("au revoir");

    my_memmove(str, str + 3, 9);
    cr_assert_str_eq(str, "revoir");
    free(str);
}

Test(my_memmove, edge_case_1, .init = init_memmove, .timeout = 2)
{
    char str[] = "hello, world!";

    my_memmove(str + 6, str, 7);
    cr_assert_str_eq(str, "hello,hello, ");
}

Test(my_memmove, edge_case_2, .init = init_memmove, .timeout = 2)
{
    char str[] = "hello, world!";

    my_memmove(str, str + 6, 7);
    cr_assert_str_eq(str, " world!world!");
}

Test(my_memmove, edge_case_3, .init = init_memmove, .timeout = 2)
{
    char str[] = "hello, world!";

    my_memmove(str + 1, str, 7);
    cr_assert_str_eq(str, "hhello, orld!");
}

Test(my_memmove, edge_case_4, .init = init_memmove, .timeout = 2)
{
    char str[] = "hello, world!";

    my_memmove(str + 2, str + 1, 7);
    cr_assert_str_eq(str, "heello, wrld!");
}

Test(my_memmove, return_1, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    cr_assert_eq(my_memmove(str, str2, 3), str);
    cr_assert_str_eq(str, "roujour");
}

Test(my_memmove, return_2, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    cr_assert_eq(my_memmove(str + 2, str2, 3), str + 2);
    cr_assert_str_eq(str, "borouur");
}

Test(my_memmove, return_3, .init = init_memmove, .timeout = 2)
{
    char *str = strdup("bonjour");

    cr_assert_eq(my_memmove(str, str + 3, 4), str);
    cr_assert_str_eq(str, "jourour");
}

Test(my_memmove, memmove_string_basic_1, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    my_memmove(str, str2, 7);
    cr_assert_str_eq(str, "roujnob");
}

Test(my_memmove, memmove_string_basic_2, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    my_memmove(str, str2, 3);
    cr_assert_str_eq(str, "roujour");
}

Test(my_memmove, check_return_value_1, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    cr_assert_eq(my_memmove(str, str2, 3), str);
}

Test(my_memmove, check_return_value_2, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    cr_assert_eq(my_memmove(str + 2, str2, 3), str + 2);
}

Test(my_memmove, check_return_value_3, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    strlen(str) + 3 - 4;
    cr_assert_eq(my_memmove(str + 2, str2, 3), str + 2);
}

Test(my_memmove, memmove_string_add_ptr, .init = init_memmove, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "roujnob";

    my_memmove(str + 2, str2, 3);
    cr_assert_str_eq(str, "borouur");
}

Test(my_memmove, malloc_memory_1, .init = init_memmove, .timeout = 2)
{
    char *str = strdup("AMOGUS");
    char *str2 = strdup("AMIGOS");

    my_memmove(str2, str, 6);
    cr_assert_str_eq(str2, "AMOGUS");
    free(str);
    free(str2);
}

Test(my_memmove, int_list_1, .init = init_memmove, .timeout = 2)
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    my_memmove(tab2, tab, sizeof(int) * 10);
    for (size_t c = 0; c < 10; c++) {
        cr_assert_eq(tab2[c], tab[c]);
    }
}

Test(my_memmove, int_list_2, .init = init_memmove, .timeout = 2)
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab2[] = {42, -42, 0, 0, 0, 0, 0, 0, 2, 1};

    my_memmove(tab2 + 2, tab, sizeof(int) * 6);
    cr_assert_eq(tab2[0], 42);
    cr_assert_eq(tab2[1], -42);
    for (size_t c = 2; c < 8; c++) {
        cr_assert_eq(tab2[c], tab[c - 2]);
    }
}

Test(my_memmove, int_list_malloc_1, .init = init_memmove, .timeout = 2)
{
    int *tab = malloc(sizeof(int) * 10);
    int *tab2 = malloc(sizeof(int) * 10);

    for (size_t c = 0; c < 10; c++) {
        tab[c] = c;
        tab2[c] = 0;
    }
    my_memmove(tab2, tab, sizeof(int) * 10);
    for (size_t c = 0; c < 10; c++) {
        cr_assert_eq(tab2[c], tab[c]);
    }
    free(tab);
    free(tab2);
}

Test(my_memmove, malloc_memory_2, .init = init_memmove, .timeout = 2)
{
    char *str = strdup("AMOGUS");
    char *str2 = strdup("AMIGOS");

    my_memmove(str2 + 2, str, 2);
    cr_assert_str_eq(str2, "AMAMOS");
    free(str);
    free(str2);
}

Test(my_memmove, unaligned_copy_1, .init = init_memmove, .timeout = 2)
{
    int tab[] = {1, 2, 3, 4, 67107840, 6, 7, 8, 9, 10};
    int tab2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    my_memmove(tab2 + 1, tab, sizeof(int) * 4 + 3);
    cr_assert_eq(tab2[0], 0);
    cr_assert_eq(tab2[1], 1);
    cr_assert_eq(tab2[2], 2);
    cr_assert_eq(tab2[3], 3);
    cr_assert_eq(tab2[4], 4);
    cr_assert_eq(tab2[5], 16776192);
}

Test(my_memmove, unaligned_copy_2, .init = init_memmove, .timeout = 2)
{
    int tab[] = {0xffffffff, 0x0000ffff, 0xffff, 0xf0f0f0f0};
    long long tab2[] = {0, 0};

    my_memmove(tab2, tab, sizeof(int) * 4);
    cr_assert_eq(tab2[0], 0xffffffffffff);
    cr_assert_eq(tab2[1], 0xf0f0f0f00000ffff);
}
