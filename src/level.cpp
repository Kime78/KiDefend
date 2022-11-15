#include "level.hpp"
#include <fstream>

void Level::load_level() {
    std::ifstream fin("./Resources/LevelData" + std::to_string(level_num) + ".txt");
    Wave wave;

    int enemy_num;
    fin >> wave.wave_num >> enemy_num;
    for(int i = 0; i < enemy_num; i++) {
        Enemy e;
        int type;
        fin >> type;
        switch (type)
        {
        case 1:
            e.type = EnemyType::Zombie;
            break;
        case 2:
            e.type = EnemyType::Alien;
            break;
        case 3:
            e.type = EnemyType::Monster;
            break;
        default:
            break;
        }
        wave.enemies.push(e);
    }    
}