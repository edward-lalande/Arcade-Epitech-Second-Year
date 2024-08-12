/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Launcher
*/

#include <SFML/Audio.hpp>

#include "SFML.hpp"

sf::RectangleShape Arcade::SFML::create(double width, double height, double x, double y)
{
    sf::RectangleShape rectangle;
    sf::Vector2f position = {(float)(x + 300.0), (float)(y + 300.0)};
    sf::Vector2f size = {(float)width, (float)height};

    rectangle.setPosition(position);
    rectangle.setSize(size);
    rectangle.setFillColor(sf::Color::White);

    return rectangle;
}

void Arcade::SFML::launcher()
{
    sf::CircleShape circle;
    sf::SoundBuffer buffer;
    sf::Sound sound;

    buffer.loadFromFile("Assets/LauncherSound.ogg");
    sound.setBuffer(buffer);
    sound.play();

    circle.setFillColor(sf::Color::White);
    circle.setPosition((sf::Vector2f){960, 540});
    circle.setRadius(1200);
    circle.setOrigin({700, 700});

    for (std::size_t i = 1200; i > 0; i--) {
        _window.clear();
        circle.setRadius(i);
        circle.setOrigin({(float)i, (float)i});
        _window.draw(circle);
        _window.display();
    }

    for (std::size_t i = 0; i < _launcher.size(); i++) {
        _window.clear();
        for (std::size_t j = 0; j < i; j++) {
            _window.draw(_launcher[j]);
        }
        _window.display();
        usleep(30000);
    }

    sleep(1);
    _window.clear();
    _window.display();
    sleep(1);
    sound.stop();
    sleep(0.5);

}

