#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

int (*my_strlen)(const char *);

void init(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strlen = dlsym(handle, "strlen");
}

Test(my_strlen, basic_1, .init = init, .timeout = 2)
{
    cr_assert_eq(my_strlen("Coucou"), 6);
}

Test(my_strlen, basic_2, .init = init, .timeout = 2)
{
    cr_assert_eq(my_strlen("Les batards ils ont fume Pop Simoke"), 35);
}

Test(my_strlen, empty, .init = init, .timeout = 2)
{
    cr_assert_eq(my_strlen(""), 0);
}
