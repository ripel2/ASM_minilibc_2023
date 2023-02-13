#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

int (*my_strncmp)(const char *, const char *, unsigned long);

void init_strncmp(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strncmp = strncmp;
}

Test(my_strncmp, strncmp_basic_1, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "au revoir";

    cr_assert_eq(my_strncmp(str, str2, 9), 0);
}

Test(my_strncmp, strncmp_basic_2, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "au revoir";

    cr_assert_eq(my_strncmp(str, str2, 3), 0);
}

Test(my_strncmp, strncmp_basic_3, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "au revoir";

    cr_assert_eq(my_strncmp(str, str2, 0), 0);
}

Test(my_strncmp, strcnp_basic_4, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "bonjour";

    cr_assert_lt(my_strncmp(str, str2, 9), 0);
}

Test(my_strncmp, strncmp_basic_5, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "bonjour";

    cr_assert_lt(my_strncmp(str, str2, 3), 0);
}

Test(my_strncmp, strncmp_basic_6, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "bonjour";

    cr_assert_gt(my_strncmp(str2, str, 9), 0);
}

Test(my_strncmp, strncmp_basic_7, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "bonjour";

    cr_assert_gt(my_strncmp(str2, str, 3), 0);
}

Test(my_strncmp, against_empty_1, .init = init_strncmp, .timeout = 2)
{
    char str[] = "au revoir";
    char str2[] = "";

    cr_assert_gt(my_strncmp(str, str2, 9), 0);
}

Test(my_strncmp, against_empty_2, .init = init_strncmp, .timeout = 2)
{
    char str[] = "";
    char str2[] = "au revoir";

    cr_assert_lt(my_strncmp(str, str2, 9), 0);
}

Test(my_strncmp, both_empty, .init = init_strncmp, .timeout = 2)
{
    char str[] = "";
    char str2[] = "";

    cr_assert_eq(my_strncmp(str, str2, 42), 0);
}

Test(my_strncmp, both_empty_2, .init = init_strncmp, .timeout = 2)
{
    char str[] = "";
    char str2[] = "";

    cr_assert_eq(my_strncmp(str, str2, 0), 0);
}

Test(my_strcnp, mess_with_memory_1, .init = init_strncmp, .timeout = 2)
{
    char *str = strdup("au revoir");
    char *str2 = strdup("au revoir");

    strlen("slap");
    memset(str + 4, 'o', 2);
    cr_assert_eq(my_strncmp(str, str2, 3), 0);
    str[0] = 'b';
    str[1] = 'o';
    cr_assert_gt(my_strncmp(str, str2, 3), 0);
}
