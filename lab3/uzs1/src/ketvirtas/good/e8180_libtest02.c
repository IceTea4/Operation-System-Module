#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include "e8180_testlib02.h"

int main() {
    void *lib_handle;
    int (*vp_testlib)(int);
    char *error;

    lib_handle = dlopen("./libloginas02a.so", RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Nepavyko atidaryti bibliotekos: %s\n", dlerror());
        return 1;
    }

    void *func_ptr = dlsym(lib_handle, "vp_testlib");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Klaida ieskant funkcijos: %s\n", error);
        dlclose(lib_handle);
        return 1;
    }

    memcpy(&vp_testlib, &func_ptr, sizeof(func_ptr));

    int result = vp_testlib(10);
    printf("Funkcijos rezultatas: %d\n", result);

    dlclose(lib_handle);

    return 0;
}
