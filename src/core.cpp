#include <iostream>
#include <math.h>

#include "core.hpp"
#include "utility.hpp"
#include "game_object.hpp"
#include "button.hpp"


Game::Game(int width, int height, std::string name) {
    window = new sf::RenderWindow( {1280, 720} , "KiDefend");
    
    GameObject::window = window;

    health = 50;
    money = 1000;
    Enemy::game_health = &health;
    wave_timer.restart();
    enemy_timer.restart();

    window->setFramerateLimit(60); 

    try {
        for(int i = 0; i < 7; i++) {
            safe_load_texture(enemies_tex[i], "./Resources/enemy" + std::to_string(i) + ".png");
        }
        for(int i = 0; i < 2; i++) {
            safe_load_texture(buttons_tex[i], "./Resources/button" + std::to_string(i) + ".png");
        }
        for(int i = 0; i < 2; i++) {
            safe_load_texture(turret_tex[i], "./Resources/turret" + std::to_string(i) + ".png");
        }

        safe_load_texture(bullet_tex[0], "./Resources/bullet.png");
        safe_load_texture(maps_tex[current_level_number - 1], "./Resources/map1.png");
        safe_load_texture(shop_tex, "./Resources/shop.png");
        font.loadFromFile("./Resources/mvboli.ttf");
    }
    catch (Error e) {
        std::cout << e.name;
    }
    
    Enemy::textures = &enemies_tex;
    Turret::textures = &turret_tex;
    Bullet::textures = &bullet_tex;
    IButton::textures = &buttons_tex;

    levels[current_level_number - 1].load_level(1);
    map_sprite.setTexture(maps_tex[current_level_number - 1]);
    current_wave = levels[current_level_number - 1].waves.front();
    current_wave.wave_num = 1;
    current_level = levels[current_level_number - 1];
    Enemy::current_level = &current_level;
    shop_sprite.setTexture(shop_tex);
    shop_sprite.setPosition(1020, 0);

    IButton::text_font = &font;
    ShopButton::dragging = &dragging;
    ShopButton::game_money = &money;
    Bullet::game_money = &money;

    hp_text.setFont(font);
    hp_text.setFillColor(sf::Color::Black);
    hp_text.setCharacterSize(24);

    money_text.setFont(font);
    money_text.setFillColor(sf::Color::Black);
    money_text.setCharacterSize(24);
    money_text.setPosition(sf::Vector2f(900, 0));

    wave_text.setFont(font); 
    wave_text.setFillColor(sf::Color::Black);
    wave_text.setCharacterSize(24);
    wave_text.setPosition(sf::Vector2f(450, 0));

    win_text.setFont(font); 
    win_text.setFillColor(sf::Color::Black);
    win_text.setCharacterSize(200);
    win_text.setPosition(sf::Vector2f(70, 160));

    lose_text.setFont(font); 
    lose_text.setFillColor(sf::Color::Black);
    lose_text.setCharacterSize(200);
    lose_text.setPosition(sf::Vector2f(70, 160));
    GameObject::objects = &objects;
    
    dragging = 0;
    //ShopButton butt1(buttons_tex[0], sf::Vector2f(1045, 90), sf::Vector2i(217, 77), TurretType::Gun, 350.0);
    objects.add(std::make_unique<ShopButton>(buttons_tex[0], sf::Vector2f(1045, 90), sf::Vector2i(217, 77), TurretType::Gun, 300));
    objects.add(std::make_unique<ShopButton>(buttons_tex[1], sf::Vector2f(1045, 182), sf::Vector2i(217, 77), TurretType::MultiBarrelGun, 450));
}

void Game::run() {
    //ShopButton test(shop_tex, sf::Vector2f(0, 0), sf::Vector2i(50, 50));

    sf::Time time_between_enemy_spawn = sf::seconds(0.35);
    sf::Time time_between_waves_spawn = sf::seconds(15);


    if(current_wave.enemies.empty()) { 
        if(current_level.waves.empty() == false) {
            if(wave_timer.getElapsedTime() > time_between_waves_spawn) { 
                //a new wave appears
                wave_timer.restart();
                
                current_level.waves.pop();
                if(current_level.waves.empty() == false) { //idk why this secondary seamingly redundat check is needed 
                    current_wave_num++;
                    current_wave = current_level.waves.front();
                }
            }
        }
    }

    if(!current_wave.enemies.empty()) { //while there are enemies to spawn 
        if(enemy_timer.getElapsedTime() > time_between_enemy_spawn) {
            objects.add(std::make_unique<Enemy>(current_wave.enemies.front().get_type(), current_level.path->path.front()));
            enemy_timer.restart();
            current_wave.enemies.pop();
        }   
    }
    
    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        IButton::event = &event;
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
            ShopButton::ptr_to_turr->setPosition((sf::Vector2f)poz);
        }
    }

    if(health >= 0) {
        hp_text.setString(std::to_string(health) + " <3");
    }
    money_text.setString("$ " + std::to_string(money));
    wave_text.setString("Waves: " + std::to_string(current_wave_num) + " / " + std::to_string(current_level.wave_num));
    win_text.setString("You Win!");
    lose_text.setString("You Lost");

    sf::Sprite rect;
    rect.setPosition(1045, 90);
    rect.setTexture(buttons_tex[0]);
    window->clear();
    window->draw(map_sprite);
    
    window->draw(rect);
    window->draw(shop_sprite);
    
    objects.iterate([](GameObject& obj){
        obj.update();
    });
    objects.iterate([](GameObject& obj){
        obj.draw();
    });
    window->draw(hp_text);
    window->draw(money_text);
    window->draw(wave_text);
    if(health <= 0) {
        window->draw(lose_text);
        health = 0;
    }
    // else if(current_level.nr_of_enemies) {
    //     window->draw(win_text);
    // }

    window->display();
}

void Game::spawn_wave() {

}
