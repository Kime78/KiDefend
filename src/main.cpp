#include <SFML/Graphics.hpp>
#include <array>

#include "path.hpp"
#include "enemy.hpp"
#include <iostream>

int main()
{
    auto window = sf::RenderWindow{ {1280, 720 }, "KiTris" };
    sf::Texture box_text;
    sf::Texture map_text;
    float target_x, target_y;
    box_text.loadFromFile("./Resources/box.png");
    map_text.loadFromFile("./Resources/map.png");
    Enemy e;
    Path path;
    sf::Sprite box;
    sf::Sprite map;
    box.setTexture(box_text);
    map.setTexture(map_text);
    e.sprite = box;
    e.sprite.setPosition(0,70);
    path.path.push(sf::Vector2f(1100, 70));
    path.path.push(sf::Vector2f(1100, 600));
    path.path.push(sf::Vector2f(160, 600));
    path.path.push(sf::Vector2f(160, 230));
    path.path.push(sf::Vector2f(950, 230));
    path.path.push(sf::Vector2f(950, 430));
    path.path.push(sf::Vector2f(350, 430));
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(map);
        
        path.move_in_path(e, 1);
        std::cout << e.sprite.getPosition().x << " " <<e.sprite.getPosition().y << '\n';
        if(e.sprite.getPosition().x > 349 && e.sprite.getPosition().x < 351 && e.sprite.getPosition().y > 429 && e.sprite.getPosition().y < 431) {
            e.sprite = sf::Sprite();
        }
        window.draw(e.sprite);
        window.display();
    }
}