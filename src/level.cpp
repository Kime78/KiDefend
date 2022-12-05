#include "level.hpp"
#include <fstream>

void Level::load_level(int level_num) {
    this->level_num = level_num;
    std::string level_path = "./Resources/LevelData" + std::to_string(level_num) + ".txt";
    std::ifstream fin(level_path);
    
    int enemy_num, waves_num;
    fin >> waves_num;
    for(int k = 0; k < waves_num; k++) {
        Wave wave;
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
        waves.push(wave);
    }

    int point_x, point_y;

    while(fin >> point_x >> point_y) {
        path.path.push_back(sf::Vector2f(point_x, point_y));
    }
}