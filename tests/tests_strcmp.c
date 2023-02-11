#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

int (*my_strcmp)(const char *, const char *);

void init_strcmp(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strcmp = dlsym(handle, "strcmp");
}

Test(my_strcmp, strcmp_basic_1, .init = init_strcmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "bonjour";

    cr_assert_eq(my_strcmp(str, str2), 0);
}

Test(my_strcmp, not_same_length, .init = init_strcmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "bonjour2";

    cr_assert_lt(my_strcmp(str, str2), 0);
}

Test(my_strcmp, not_same_length_2, .init = init_strcmp, .timeout = 2)
{
    char str[] = "bonjour2";
    char str2[] = "bonjour";

    cr_assert_gt(my_strcmp(str, str2), 0);
}

Test(my_strcmp, diff_char_1, .init = init_strcmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "bonjouz";

    cr_assert_lt(my_strcmp(str, str2), 0);
}

Test(my_strcmp, diff_char_2, .init = init_strcmp, .timeout = 2)
{
    char str[] = "bonjouz";
    char str2[] = "bonjour";

    cr_assert_gt(my_strcmp(str, str2), 0);
}

Test(my_strcmp, against_empty_1, .init = init_strcmp, .timeout = 2)
{
    char str[] = "bonjour";
    char str2[] = "";

    cr_assert_gt(my_strcmp(str, str2), 0);
}

Test(my_strcmp, against_empty_2, .init = init_strcmp, .timeout = 2)
{
    char str[] = "";
    char str2[] = "bonjour";

    cr_assert_lt(my_strcmp(str, str2), 0);
}


Test(my_strcmp, both_empty, .init = init_strcmp, .timeout = 2)
{
    char str[] = "";
    char str2[] = "";

    cr_assert_eq(my_strcmp(str, str2), 0);
}

Test(my_strcmp, mess_with_memory_1, .init = init_strcmp, .timeout = 2)
{
    char *str = strdup("bonjour");
    char str2[] = "bonjour";

    str[0] = 'a';
    cr_assert_lt(my_strcmp(str, str2), 0);
}

Test(my_strcmp, mess_with_memory_2, .init = init_strcmp, .timeout = 2)
{
    char str[] = "bonjour";
    char *str2 = strdup("bonjour");

    str2[0] = 'a';
    cr_assert_gt(my_strcmp(str, str2), 0);
}

Test(my_strcmp, mess_with_memory_3, .init = init_strcmp, .timeout = 2)
{
    char *str = strdup("bonjour");
    char *str2 = strdup("bonjour");

    strlen("sfekzjfzejfioz");
    memset(str + 2, 'a', 4);
    str[0] = 'a';
    str2[0] = 'b';
    str[3] = 'c';
    str2[3] = 'd';
    cr_assert_lt(my_strcmp(str, str2), 0);
}