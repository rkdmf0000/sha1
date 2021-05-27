#include "hash_enc.h"
#include <cstring>


int main(int argc, char* argv[]) {

    hash_enc _instance;
    _instance.init();

    unsigned int seed_point(0);
    unsigned int seedmap[5] = {0x00000000};
    int index(0);
    bool flag_seed(false), flag_value(false);
    for (index=1;index<argc;++index) {

        unsigned int size = std::strlen(argv[index]);


        if (flag_seed && (unsigned int)argv[index][0] == 45 && ((unsigned int)argv[index][1] == 115 || (unsigned int)argv[index][1] == 118)) {
            flag_seed = false;
            flag_value = false;
        };


        if (flag_seed) {

            unsigned int cal(0);
            unsigned int cidx(0);
            for(cidx=0;cidx<size;++cidx) {
                cal += (unsigned int)argv[index][cidx];
                cal &= 0xffffffff;
            };
            seedmap[seed_point] = cal;

             _instance.seed(seedmap);

            ++seed_point;
            if (seed_point == 5)
                seed_point = 0;
        } else if (flag_value) {
            _instance.update(argv[index], size);
        };


        //is seed sets
        if ((unsigned int)argv[index][0] == 45 && (unsigned int)argv[index][1] == 115) {
            flag_seed = true;
        }

        //is value sets
        if ((unsigned int)argv[index][0] == 45 && (unsigned int)argv[index][1] == 118) {
            flag_value = true;
        };

    };

    _instance.flush();
    std::cout << _instance.getResult();

    return 0;
};


