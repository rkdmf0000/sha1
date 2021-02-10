#include "hash_enc.h"
#include <cstring>

int main(int argc, char* argv[]) {
    hash_enc _instance;
    _instance.init();
    unsigned int index(0);
    for (index=0;index<argc;++index) {
        unsigned int size = std::strlen(argv[index]);
        _instance.update(argv[index], size);
    };
    _instance.flush();
    std::cout << _instance.getResult();
    return 0;
};
