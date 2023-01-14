#pragma once
#include <queue>
#include "enemy.hpp"

class Enemy;

struct Wave {
    int wave_num;
    std::queue<Enemy> enemies;
};