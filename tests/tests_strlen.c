#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

int (*my_strlen)(const char *);

void init_strlen(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strlen = dlsym(handle, "strlen");
}

Test(my_strlen, basic_1, .init = init_strlen, .timeout = 2)
{
    cr_assert_eq(my_strlen("Coucou"), 6);
}

Test(my_strlen, basic_2, .init = init_strlen, .timeout = 2)
{
    cr_assert_eq(my_strlen("Les batards ils ont fume Pop Simoke"), 35);
}

Test(my_strlen, empty, .init = init_strlen, .timeout = 2)
{
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strlen, memory_trick_1, .init = init_strlen, .timeout = 2)
{
    int result1 = strlen("Coucou");
    int result2 = my_strlen("Coucou");
    int result3 = strlen("Coucou");

    cr_assert_eq(result2, 6);
    cr_assert_eq(result1, result2);
    cr_assert_eq(result2, result3);
}

Test(my_strlen, memory_trick_2, .init = init_strlen, .timeout = 2)
{
    int result1 = strlen("Phrase longue numero une");
    int result2 = my_strlen("\n\012\034\056\076\011\a\r%sabcd");
    int result3 = strlen("un petit crash ?");

    cr_assert_eq(result2, 14);
}
