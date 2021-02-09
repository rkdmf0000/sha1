
#include "hash_enc.h"

int main() {
    hash_enc test_instance;
    char test1[10] = "123456789";
    char test2[400] = "123456789";
    char test3[5] = "1269";
    char test4[13] = "갱냄스떨";
    //std::string test4 = "hello world";

    test_instance.init();
    test_instance.update(test4, sizeof(test4));
    //test_instance.flush();
    void *results = nullptr;
    test_instance.flush(results);
    std::cout << test_instance.getResult() << '\n';
    return 0;
};
