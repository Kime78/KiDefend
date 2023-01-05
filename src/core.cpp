#include <iostream>
#include <math.h>

#include "core.hpp"
#include "utility.hpp"
#include "game_object.hpp"
#include "button.hpp"

Game::Game(int width, int height, std::string name) {
    window = new sf::RenderWindow( {1280, 720} , "KiDefend");
    IButton::window = window;
    health = 50;
    money = 1000;
    wave_timer.restart();
    enemy_timer.restart();
    window->setFramerateLimit(60); 
    levels[current_level_number - 1].load_level(1);
    for(int i = 0; i < 7; i++) {
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

    font.loadFromFile("./Resources/mvboli.ttf");

    hp_text.setFont(font);
    hp_text.setFillColor(sf::Color::Black);
    hp_text.setCharacterSize(24);

    money_text.setFont(font);
    money_text.setFillColor(sf::Color::Black);
    money_text.setCharacterSize(24);
    money_text.setPosition(sf::Vector2f(900, 0));
}

void Game::run() {
    ShopButton test(shop_tex, sf::Vector2f(0, 0), sf::Vector2i(50, 50));

    sf::Time time_between_enemy_spawn = sf::seconds(1);
    sf::Time time_between_waves_spawn = sf::seconds(20);

    if(wave_timer.getElapsedTime() > time_between_waves_spawn) { 
        //a new wave appears
        wave_timer.restart();
        current_level.waves.pop();
        current_wave = current_level.waves.front();
    }

    if(!current_wave.enemies.empty()) { //while there are enemies to spawn 
            if(enemy_timer.getElapsedTime() > time_between_enemy_spawn) {
                enemies.push_back(spawn_enemy(current_wave.enemies.front().get_type(), current_level.path.path.front()));
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
                    if(money >= 500) { //turret cost maw 
                        turrets.push_back(spawn_turret(TurretType::Gun, (sf::Vector2f)poz));
                        money -= turrets.back()->cost;
                        dragging = 1;
                    }
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

    hp_text.setString(std::to_string(health) + " <3");
    money_text.setString(std::to_string(money) + " $");

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(217, 77));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(1045, 90);
    
    window->clear();
    window->draw(map_sprite);
    window->draw(shop_sprite);
    window->draw(rect);
    Enemy* enemy_short = nullptr;
    for(auto turret : turrets) {
        float min_dist = INFINITY;
        for(auto enemy : enemies) {
            if(circular_collide(turret->getPosition(), enemy->getPosition(), turret->radious)) {
                auto dist = distance(turret->getPosition(), enemy->getPosition());
                if(dist < min_dist) {
                    min_dist = dist;
                    enemy_short = enemy;
                }
            }
        }
        if(enemy_short != nullptr) {
            if(circular_collide(turret->getPosition(), enemy_short->getPosition(), turret->radious)) {
                turret->setRotation(angle_between(turret->getPosition(), enemy_short->getPosition()) * (180 / PI));
                if(turret->atack_timer.getElapsedTime() > turret->attack_cooldown) {
                    bullets.push_back(spawn_bullet(turret->getPosition(), angle_between(turret->getPosition(), enemy_short->getPosition()), 50));
                    turret->atack_timer.restart();
                }
            }
        }
        window->draw(*turret);
    }

    for(auto enemy : enemies) {
        current_level.path.move_in_path(*enemy);
        window->draw(*enemy);
        if(rectular_collide((*enemy).getPosition(), current_level.path.path.back(), sf::Vector2f(30, 30))) {
            kill_enemy(enemy);
            health -= enemy->get_health();
        }
    }

    for(auto bullet: bullets) {
        window->draw(*bullet);

        //to be put in  a func
        float vx = bullet->speed * cos(bullet->angle);
        float vy = bullet->speed * sin(bullet->angle);
        bullet->setPosition(bullet->getPosition().x - vx, bullet->getPosition().y - vy);

        for(auto enemy : enemies) {
            if(enemy != nullptr) {
                sf::Vector2f test = enemy->getPosition() - enemy->getOrigin();
                //std::cout << enemy->getOrigin().x << " " << enemy->getOrigin().y << "\t" << enemy->getPosition().x << " " << enemy->getPosition().y << '\t';
                //std::cout << test.x << " " << test.y << '\n';
                if(circular_collide(enemy->getPosition(), bullet->getPosition(), 32)) {
                    enemy->take_damage();
                    if(enemy->get_health() != 0) {
                        //to tidy this up
                        Enemy e(enemy->get_type());
                        e.setPosition(enemy->getPosition());
                        e.set_path_indx(enemy->get_path_indx());
                        enemies.push_back(spawn_enemy(e));
                    }
                    kill_enemy(enemy);
                    delete_bullet(bullet);
                }
            }
        }
    }
    window->draw(hp_text);
    window->draw(money_text);

    window->display();
}

void Game::spawn_wave() {

}

Enemy* Game::spawn_enemy(EnemyType type, sf::Vector2f pos) {
    Enemy* enemy = new Enemy(type);
    enemy->setPosition(pos);
    switch (type)
    {
    case EnemyType::Red:
        enemy->setTexture(enemies_tex[0]);
        break;
    case EnemyType::Blue:
        enemy->setTexture(enemies_tex[1]);
        break;
    case EnemyType::Green:
        enemy->setTexture(enemies_tex[2]);
        break;
    case EnemyType::Yellow:
        enemy->setTexture(enemies_tex[3]);
        break;
    case EnemyType::Pink:
        enemy->setTexture(enemies_tex[4]);
        break;
    case EnemyType::Black:
        enemy->setTexture(enemies_tex[5]);
        break;   
    case EnemyType::Lead:
        enemy->setTexture(enemies_tex[6]);
        break;     
    default:
        break;
    }

    return enemy;
}

Enemy* Game::spawn_enemy(const Enemy& other) {
    Enemy* enemy = new Enemy(other);
    switch (enemy->get_type())
    {
    case EnemyType::Red:
        enemy->setTexture(enemies_tex[0]);
        break;
    case EnemyType::Blue:
        enemy->setTexture(enemies_tex[1]);
        break;
    case EnemyType::Green:
        enemy->setTexture(enemies_tex[2]);
        break;
    case EnemyType::Yellow:
        enemy->setTexture(enemies_tex[3]);
        break;
    case EnemyType::Pink:
        enemy->setTexture(enemies_tex[4]);
        break;
    case EnemyType::Black:
        enemy->setTexture(enemies_tex[5]);
        break;   
    case EnemyType::Lead:
        enemy->setTexture(enemies_tex[6]);
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
    Turret* turret = new Turret(type);
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

Bullet* Game::spawn_bullet(sf::Vector2f pos, float angle, float speed) {
    Bullet* bullet = new Bullet;
    bullet->setPosition(pos);
    bullet->angle = angle;
    bullet->speed = speed;
    bullet->setFillColor(sf::Color::Black);
    bullet->setRadius(5);

    return bullet;
}

void Game::delete_bullet(Bullet* bullet) {
    auto it = bullets.begin();
    while (it != bullets.end()) {
        if (*it == bullet) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
    delete bullet;
    bullet = nullptr;
 
}
