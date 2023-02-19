#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>

size_t (*my_strcspn)(const char *, const char *);

void init_strcspn(void)
{
    void *handle = dlopen("./libasm.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    my_strcspn = dlsym(handle, "strcspn");
}

Test(my_strcspn, strcspn_basic_1, .init = init_strcspn, .timeout = 2)
{
    char str[] = "je veux une chocolatine";

    cr_assert_eq(my_strcspn(str, "pain"), 9);
}

Test(my_strcspn, strcspn_basic_2, .init = init_strcspn, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    cr_assert_eq(my_strcspn(str, "jul"), 0);
}

Test(my_strcspn, strcspn_basic_3, .init = init_strcspn, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    cr_assert_eq(my_strcspn(str, "vvsvsvsvs"), 3);
}

Test(my_strcspn, strcspn_basic_4, .init = init_strcspn, .timeout = 2)
{
    char str[] = "je veux un pain au chocolat";

    cr_assert_eq(my_strcspn(str, "zr"), strlen(str));
}
