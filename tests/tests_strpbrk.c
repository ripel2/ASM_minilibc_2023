#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

char *(*my_strpbrk)(const char *, const char *);

void init_strpbrk(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strpbrk = dlsym(handle, "strpbrk");
}

Test(my_strpbrk, strpbrk_basic_1, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "je veux une chocolatine";

    cr_assert_str_eq(my_strpbrk(str, "pain"), "ne chocolatine");
    cr_assert_eq(my_strpbrk(str, "pain"), str + 9);
}

Test(my_strpbrk, strpbrk_basic_2, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    cr_assert_null(my_strpbrk(str, "z"));
}

Test(my_strpbrk, strpbrk_basic_3, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    cr_assert_null(my_strpbrk(str, ""));
}

Test(my_strpbrk, strpbrk_basic_4, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "je veux un pain au raisins";

    cr_assert_str_eq(my_strpbrk(str, " pain"), " veux un pain au raisins");
}

Test(my_strpbrk, strpbrk_basic_5, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    cr_assert_str_eq(my_strpbrk(str, "j"), "je veux un pain au chocolat");
    cr_assert_eq(my_strpbrk(str, "j"), str);
}

Test(my_strpbrk, empty_string_1, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "";

    cr_assert_null(my_strpbrk(str, "pugo"));
}

Test(my_strpbrk, empty_string_2, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "";

    cr_assert_null(my_strpbrk(str, ""));
}

Test(my_strpbrk, mess_with_memory_1, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    strlen(str);
    memset(str, 'a', 10);
    cr_assert_str_eq(my_strpbrk(str, "pirogue"), "pain au chocolat");
    cr_assert_eq(my_strpbrk(str, "pirogue"), str + 11);
}

Test(my_strpbrk, mess_with_memory_2, .init = init_strpbrk, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    strlen(str);
    memset(str, 'a', 10);
    cr_assert_null(my_strpbrk(str, "zzzzzz"));
}
