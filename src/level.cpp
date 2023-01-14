#include "level.hpp"
#include <fstream>

void Level::load_level(int level_num) {
    this->level_num = level_num;
    std::string level_path = "./Resources/LevelData" + std::to_string(level_num) + ".txt";
    std::ifstream fin(level_path);
    
    int enemy_num;
    fin >> wave_num;
    waves.push(Wave());
    for(int k = 0; k < wave_num; k++) {
        Wave wave;
        fin >> wave.wave_num >> enemy_num;
        nr_of_enemies += enemy_num;
        for(int i = 0; i < enemy_num; i++) {
            int type_num = 0;
            fin >> type_num;
            EnemyType type;
            switch (type_num)
            {
            case 1:
                type = EnemyType::Red;
                break;
            case 2:
                type = EnemyType::Blue;
                break;
            case 3:
                type = EnemyType::Green;
                break;
            case 4:
                type = EnemyType::Yellow;
                break;
            case 5:
                type = EnemyType::Pink;
                break;
            case 6:
                type = EnemyType::Black;
                break;
            case 7:
                type = EnemyType::Lead;
                break;
            default:
                break;
            }
            Enemy e(type, sf::Vector2f(0, 0));
            wave.enemies.push(e);
        }
        waves.push(wave);
    }

    int point_x, point_y;
    path = new Path;
    while(fin >> point_x >> point_y) {
        path->path.push_back(sf::Vector2f(point_x, point_y));
    }
}