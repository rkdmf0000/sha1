#include "hash_enc.h"

int main(int argc, char* argv[]) {
    hash_enc _instance;
    _instance.init();
    _instance.update(argv, sizeof(argc));
    _instance.flush();
    std::cout << _instance.getResult();
    return 0;
};
