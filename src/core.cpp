#include <iostream>

#include "core.hpp"
#include "utility.hpp"

Game::Game(int width, int height, std::string name) {
    window = new sf::RenderWindow( {1280, 720} , "KiDefend");
    health = 50;
    money = 0;
    wave_timer.restart();
    enemy_timer.restart();
    levels[current_level_number - 1].load_level(1);
    for(int i = 0; i < 3; i++) {
        std::string path = "./Resources/enemy" + std::to_string(i) + ".png";
        enemies_tex[i].loadFromFile(path);
    }
    turret_tex[0].loadFromFile("./Resources/turret.png");
    maps_tex[current_level_number - 1].loadFromFile("./Resources/map1.png");
    map_sprite.setTexture(maps_tex[current_level_number - 1]);
    current_wave = levels[current_level_number - 1].waves.front();
    current_wave.wave_num = 1;
    current_level = levels[current_level_number - 1];
    shop_tex.loadFromFile("./Resources/shop.png");
    shop_sprite.setTexture(shop_tex);
    shop_sprite.setPosition(1020, 0);
}

void Game::run() {
    
    sf::Time time_between_enemy_spawn = sf::seconds(1);
    sf::Time time_between_waves_spawn = sf::seconds(20);

    if(wave_timer.getElapsedTime() > time_between_waves_spawn) { 
        //a new wave appears
        //return std::cout << "Wave " << current_wave.wave_num << " spawn~\n"; 
        wave_timer.restart();
        current_level.waves.pop();
        current_wave = current_level.waves.front();
    }

    if(!current_wave.enemies.empty()) { //while there are enemies to spawn 
            if(enemy_timer.getElapsedTime() > time_between_enemy_spawn) {
                // //std::cout << "Enemy spawn~ " << current_wave.enemies.size() << "";
                // switch(current_wave.enemies.front().type) {
                //     case EnemyType::Zombie: 
                //         std::cout<< "Z\n";
                //         break;
                //     case EnemyType::Alien: 
                //         std::cout<< "A\n";
                //         break;
                //     case EnemyType::Monster: 
                //         std::cout<< "M\n";
                //         break;
                //}
                enemies.push_back(spawn_enemy(current_wave.enemies.front().type, current_level.path.path.front()));
                enemy_timer.restart();
                current_wave.enemies.pop();
            }   
    }
    
    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if(event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                auto poz = sf::Mouse::getPosition(*window);
                if(rectular_collide((sf::Vector2f)poz, sf::Vector2f(1045, 90), sf::Vector2f(217, 77))) {
                //std::cout << "\n SPAWN at " << poz.x << " " << poz.y << "\n\n";
                    turrets.push_back(spawn_turret(TurretType::Gun, (sf::Vector2f)poz));
                    dragging = 1;
                }
                
            }  
        }
        if(event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                dragging = 0;
            }  
        }
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }


    if(dragging) {
        auto poz = sf::Mouse::getPosition(*window);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(!turrets.empty()) {
                turrets.back()->setPosition((sf::Vector2f)poz);
            }
        }
    }
    
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(217, 77));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(1045, 90);
    
    window->clear();
    window->draw(map_sprite);
    window->draw(shop_sprite);
    window->draw(rect);
    for(auto turret : turrets) {
        Enemy* enemy_short;
        float min_dist = 9999999;
        for(auto enemy : enemies) {
            if(rectular_collide(turret->getPosition(), enemy->getPosition(), sf::Vector2f(turret->radious, turret->radious))) {
                auto dist = distance(turret->getPosition(), enemy->getPosition());
                if(dist < min_dist) {
                    min_dist = dist;
                    enemy_short = enemy;
                }
            }
        }
        if(!enemies.empty()) {
            if(rectular_collide(turret->getPosition(), enemy_short->getPosition(), sf::Vector2f(turret->radious, turret->radious)))
                turret->setRotation(angle_between(turret->getPosition(), enemy_short->getPosition()) * (180 / PI));
        }
        window->draw(*turret);
    }
    for(auto enemy : enemies) {
        current_level.path.move_in_path(*enemy);
        window->draw(*enemy);
        if(rectular_collide((*enemy).getPosition(), current_level.path.path.back(), sf::Vector2f(30, 30))) {
            kill_enemy(enemy);
            break;
        }
    }
    //Font: MV Boli
    window->display();
}

void Game::spawn_wave() {

}

Enemy* Game::spawn_enemy(EnemyType type, sf::Vector2f pos) {
    Enemy* enemy = new Enemy(type);
    enemy->setPosition(pos);
    enemy->setOrigin(16, 16);
    enemy->setRotation(0);
    switch (type)
    {
    case EnemyType::Zombie:
        enemy->setTexture(enemies_tex[0]);
        break;
    case EnemyType::Alien:
        enemy->setTexture(enemies_tex[1]);
        break;
    case EnemyType::Monster:
        enemy->setTexture(enemies_tex[2]);
        break;    
    default:
        break;
    }

    return enemy;
}

void Game::kill_enemy(Enemy* enemy) {
    //enemies.pop_back();
    auto it = enemies.begin();
    while (it != enemies.end()) {
        if (*it == enemy) {
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }
    delete enemy;
    enemy = nullptr;
}

Turret* Game::spawn_turret(TurretType type, sf::Vector2f pos) {
    Turret* turret = new Turret;
    turret->setPosition(pos);
    turret->setOrigin(16, 16);
    turret->setRotation(0);
    turret->setScale(2, 2);
    switch(type) {
        case TurretType::Gun:
            turret->setTexture(turret_tex[0]);
            break;
        case TurretType::Rocket:
            turret->setTexture(turret_tex[1]);
            break;
        default:
            break;
    }
    return turret;

}