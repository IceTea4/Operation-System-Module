#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Naudojimas: %s <bibliotekos_kelias> <funkcijos_pavadinimas>\n", argv[0]);
        return 1;
    }

    void *lib_handle;
    char *error;

    lib_handle = dlopen(argv[1], RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Nepavyko užkrauti bibliotekos: %s\n", dlerror());
        return 1;
    }

    void (*func_ptr)();
    func_ptr = (void (*)())dlsym(lib_handle, argv[2]);
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Klaida ieškant funkcijos: %s\n", error);
        dlclose(lib_handle);
        return 1;
    }

    (*func_ptr)();

    dlclose(lib_handle);

    return 0;
}
