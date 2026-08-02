#include <random>

namespace baseplate {

    int RandomRangeI(int min, int max) {

        static std::mt19937 gen(std::random_device{}());

        std::uniform_int_distribution<> Distr(min, max);
        return Distr(gen);
    }
}