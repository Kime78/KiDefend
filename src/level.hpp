#pragma once

#include "path.hpp"
#include "wave.hpp"

struct Path;

struct Level {
    Path* path;
    int level_num;
    int wave_num;
    int nr_of_enemies;
    std::queue<Wave> waves;


    void load_level(int level_num);
};
