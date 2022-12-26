#include <SFML/Graphics.hpp>
#include <array>

#include "path.hpp"
#include "enemy.hpp"
#include "utility.hpp"
#include "turret.hpp"
#include "level.hpp"
#include "core.hpp"

#include <iostream>
#include <cmath>

int main()
{
//     auto window = sf::RenderWindow{ {1280, 720 }, "KiDefend" };
//     sf::Texture box_text;
//     sf::Texture map_text;
//     sf::Texture turret_text;
//     sf::CircleShape rad;
//    // Game joc(100, 100, "test");
//     Turret test;
//     test.setScale(2, 2);
//     test.radious = 200;
//     rad.setPosition(200,200);
//     rad.setRadius(test.radious);
//     rad.setOrigin(test.radious, test.radious);
//     float target_x, target_y;
//     box_text.loadFromFile("./Resources/box2.png");
//     map_text.loadFromFile("./Resources/map.png");
//     turret_text.loadFromFile("./Resources/turret.png");
//     Enemy e;
//     Path path;
//     //sf::Sprite box;
//     sf::Sprite map;
//     //box.setTexture(box_text);
//     map.setTexture(map_text);
//     test.setTexture(turret_text);
//     e.setTexture(box_text);
//     //e.sprite = box;*
//     e.setPosition(0,80);
//     path.path.push(sf::Vector2f(1100, 80));
//     path.path.push(sf::Vector2f(1100, 600));
//     path.path.push(sf::Vector2f(160, 600));
//     path.path.push(sf::Vector2f(160, 230));
//     path.path.push(sf::Vector2f(950, 230));
//     path.path.push(sf::Vector2f(950, 430));
//     path.path.push(sf::Vector2f(350, 430));

//     test.setPosition(200, 200);
//     test.setOrigin(16,16);
//     e.setOrigin(16,16);
//     window.setFramerateLimit(144);
    Game joc(1280, 720, "KiDefend");

    while (joc.window->isOpen())
    {
        joc.run();
        //joc.run();
        // sf::Mouse mouse;
        // if(mouse.isButtonPressed(mouse.Left)) {
        //     if(rectular_collide(test, sf::Vector2f(mouse.getPosition(window)), 32)) {
        //         test.setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y);
        //         rad.setPosition(mouse.getPosition(window).x, mouse.getPosition(window).y);
        //     }
        // }
        // for (auto event = sf::Event{}; window.pollEvent(event);)
        // {
        //     if (event.type == sf::Event::Closed)
        //     {
        //         window.close();
        //     }
        // }
        // window.clear();
        // window.draw(map);
        // if(rectular_collide(e, test.getPosition(), test.radious)) { 
        //         test.setRotation(angle_between(test.getPosition(), e.getPosition()) * (180 / PI));
        // }
        // path.move_in_path(e);
        // if(e.getPosition().x > 349 && e.getPosition().x < 351 && e.getPosition().y > 429 && e.getPosition().y < 431) {
        //     e = Enemy();
        // }
        // window.draw(rad);
        // window.draw(e);
        // window.draw(test);
        // window.display();
    }
}