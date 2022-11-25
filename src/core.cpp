#include "core.hpp"
#include <iostream>

void Game::load_sprite(sf::Sprite& obj, std::pair<int, int> index) {
    obj.setTexture(sprite_matrix);
    obj.setTextureRect(sf::IntRect(index.first, index.second, 32 , 32));
}

Game::Game(int width, int height, std::string name) {
    window = new sf::RenderWindow( {1280, 720} , "KiDefend");
    health = 50;
    money = 0;
    wave_timer.restart();
    enemy_timer.restart();
    levels[current_level].load_level(1);
}

void Game::run() {
    Wave wave = levels[current_level].waves.front();
    sf::Time time_between_enemy_spawn = sf::seconds(1);
    sf::Time time_between_waves_spawn = sf::seconds(20);
   
    if(wave_timer.getElapsedTime() > time_between_waves_spawn) { 
        //a new wave appears
        std::cout << "Wave " << wave.wave_num << " spawn~\n";
        while(!wave.enemies.empty()) { //while there are enemies to spawn 
            if(enemy_timer.getElapsedTime() > time_between_enemy_spawn) {
                std::cout << "Enemy spawn~ \n";
                enemy_timer.restart();
                wave.enemies.pop();
            }   
        }
        wave_timer.restart();
        levels[current_level].waves.pop();

        window->clear();
        window->display();
    }
}

void Game::spawn_wave() {


}