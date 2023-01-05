#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

#include "game_object.hpp"

enum class EnemyType {
    Popped, Red, Blue, Green, Yellow, Pink, Black, Lead
};

class Enemy : public GameObject {
protected:
    int health;
    float speed;
    EnemyType type;
    int path_indx;
public:
    Enemy(EnemyType type);
    Enemy(const Enemy& other);
    void take_damage();

    int get_health() {return health;}
    void set_health(int health) {this->health = health;}

    float get_speed() {return speed;}
    void set_speed(float speed) {this->speed = speed;}

    EnemyType get_type() {return type;}
    void set_type(EnemyType type) {this->type = type;}

    int get_path_indx() {return path_indx;}
    void set_path_indx(int path_indx) {this->path_indx = path_indx;}     
};

struct Wave {
    int wave_num;
    std::queue<Enemy> enemies;
};