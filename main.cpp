#include "hash_enc.h"

int main(int argc, char* argv[]) {
    unsigned int index(0);
    char t[argc];
    for (index=0;index<argc;++index) t[index] = *argv[index];
    hash_enc _instance;
    _instance.init();
    _instance.update(t, argc);
    _instance.flush();
    std::cout << _instance.getResult();
    return 0;
};
