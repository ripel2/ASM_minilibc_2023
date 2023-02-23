#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

int (*my_ffs)(int);

void init_ffs(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_ffs = dlsym(handle, "ffs");
}

Test(my_ffs, ffs_basic_1, .init = init_ffs, .timeout = 2)
{
    for (int v = 0; v < 100; v++) {
        if (my_ffs(v) != ffs(v)) {
            printf("v = %d, my_ffs = %d, ffs = %d\n", v, my_ffs(v), ffs(v));
            cr_assert_eq(my_ffs(v), ffs(v));
        }
    }
}

Test(my_ffs, ffs_basic_2, .init = init_ffs, .timeout = 2)
{
    for (int v = 65535; v < 65535 + 100; v++) {
        if (my_ffs(v) != ffs(v)) {
            printf("v = %d, my_ffs = %d, ffs = %d\n", v, my_ffs(v), ffs(v));
            cr_assert_eq(my_ffs(v), ffs(v));
        }
    }
}

Test(my_ffs, ffs_basic_3, .init = init_ffs, .timeout = 2)
{
    for (int v = 0; v < 100; v++) {
        if (my_ffs(__INT_MAX__+ 50 - v / 2) != ffs(__INT_MAX__ + 50 - v / 2)) {
            printf("v = %d, my_ffs = %d, ffs = %d\n", v, my_ffs(__INT_MAX__ + 50 - v / 2), ffs(__INT_MAX__ + 50 - v / 2));
            cr_assert_eq(my_ffs(__INT_MAX__ + 50 - v / 2), ffs(__INT_MAX__ + 50 - v / 2));
        }
    }
}
