#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

char *(*my_memfrob)(char *, size_t);

void init_memfrob(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_memfrob = dlsym(handle, "memfrob");
}

Test(my_memfrob, memfrob_basic_1, .init = init_memfrob, .timeout = 2)
{
    char str[] = "frog";
    char expected[] = {'f' ^ 42, 'r' ^ 42, 'o' ^ 42, 'g' ^ 42, '\0'};

    my_memfrob(str, 4);
    cr_assert_str_eq(str, expected);
    my_memfrob(str, 4);
    cr_assert_str_eq(str, "frog");
}
