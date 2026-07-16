#include <random>

int BSPLT_RandomI(int min, int max) {

    static std::mt19937 Gen(std::random_device{}());

    std::uniform_int_distribution<> Distr(min, max);
    return Distr(Gen);
}