#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

int (*my_strcasecmp)(const char *, const char *);

void init_strcasecmp(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strcasecmp = dlsym(handle, "strcasecmp");
}

Test(my_strcasecmp, strcasecmp_basic_1, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "bonjour";

    cr_assert_eq(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, not_same_length, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "bonjour2";

    cr_assert_lt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, not_same_length_2, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour2";
    char str2[] = "bonjour";

    cr_assert_gt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, diff_char_1, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "bonjouz";

    cr_assert_lt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, diff_char_2, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjouz";
    char str2[] = "bonjour";

    cr_assert_gt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, against_empty_1, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "";

    cr_assert_gt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, against_empty_2, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "";
    char str2[] = "bonjour";

    cr_assert_lt(my_strcasecmp(str, str2), 0);
}


Test(my_strcasecmp, both_empty, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "";
    char str2[] = "";

    cr_assert_eq(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, mess_with_memory_1, .init = init_strcasecmp, .timeout = 2)
{
    char *str = strdup("bonjour");
    char str2[] = "bonjour";

    str[0] = 'a';
    cr_assert_lt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, mess_with_memory_2, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour";
    char *str2 = strdup("bonjour");

    str2[0] = 'a';
    cr_assert_gt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, mess_with_memory_3, .init = init_strcasecmp, .timeout = 2)
{
    char *str = strdup("bonjour");
    char *str2 = strdup("bonjour");

    strlen("sfekzjfzejfioz");
    memset(str + 2, 'a', 4);
    str[0] = 'a';
    str2[0] = 'b';
    str[3] = 'c';
    str2[3] = 'd';
    cr_assert_lt(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, strcasecmp_case_1, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "Bonjour";

    cr_assert_eq(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, strcasecmp_case_2, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "Bonjour";
    char str2[] = "bonjour";

    cr_assert_eq(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, strcasecmp_case_3, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "bOnjour";

    cr_assert_eq(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, strcasecmp_case_4, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "aOnjour";
    char str2[] = "AOnjour";

    cr_assert_eq(my_strcasecmp(str, str2), 0);
}

Test(my_strcasecmp, strcasecmp_case_5, .init = init_strcasecmp, .timeout = 2)
{
    char str[] = "zonjour";
    char str2[] = "ZonjouR";

    cr_assert_eq(my_strcasecmp(str, str2), 0);
}