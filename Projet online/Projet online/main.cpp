#include <SFML/Graphics.hpp>
#include "constants.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML works!");

    sf::Sprite sprite[3][3];
    int map[3][3];

    sf::Texture red_circle;
    if (!red_circle.loadFromFile("redcircle.png"))
    {
        // erreur...
    }

    sf::Texture red_cross;
    if (!red_cross.loadFromFile("redcross.png"))
    {
        // erreur...
    }

    int player_turn = 0;
    int victory = 0;

    sf::RectangleShape line1(sf::Vector2f(WINDOW_SIZE, 10.f));
    line1.setPosition(WINDOW_SIZE / 3, 0.f);
    line1.rotate(90);

    sf::RectangleShape line2(sf::Vector2f(WINDOW_SIZE, 10.f));
    line2.setPosition(WINDOW_SIZE - WINDOW_SIZE / 3, 0.f);
    line2.rotate(90);

    sf::RectangleShape line3(sf::Vector2f(WINDOW_SIZE, 10.f));
    line3.setPosition(0.f, WINDOW_SIZE / 3);

    sf::RectangleShape line4(sf::Vector2f(WINDOW_SIZE, 10.f));
    line4.setPosition(0.f, WINDOW_SIZE - WINDOW_SIZE / 3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                if (map[(localPosition.y - localPosition.y % 400) / 400][(localPosition.x - localPosition.x % 400) / 400] == 1 || map[(localPosition.y - localPosition.y % 400) / 400][(localPosition.x - localPosition.x % 400) / 400] == 2)
                    continue;
                else if (player_turn == 0) {
                    sprite[(localPosition.y - localPosition.y % 400) / 400][(localPosition.x - localPosition.x % 400) / 400].setTexture(red_cross);
                    map[(localPosition.y - localPosition.y % 400) / 400][(localPosition.x - localPosition.x % 400) / 400] = 1;
                    player_turn = 1;
                }
                else if (player_turn == 1) {
                    sprite[(localPosition.y - localPosition.y % 400) / 400][(localPosition.x - localPosition.x % 400) / 400].setTexture(red_circle);
                    map[(localPosition.y - localPosition.y % 400) / 400][(localPosition.x - localPosition.x % 400) / 400] = 2;
                    player_turn = 0;
                }
            }
        }

        for (int line = 0; line < 3; line++) {
            for (int column = 0; column < 3; column++) {
                if (map[line][column] == 1 || map[line][column] == 2) {
                    if (map[line + 1][column] == map[line][column] && map[line + 2][column] == map[line][column])
                        victory = 1;
                    if (map[line][column + 1] == map[line][column] && map[line][column + 2] == map[line][column])
                        victory = 1;
                    if (map[line + 1][column + 1] == map[line][column] && map[line + 2][column + 2] == map[line][column])
                        victory = 1;
                    if (map[line + 1][column - 1] == map[line][column] && map[line + 2][column - 2] == map[line][column])
                        victory = 1;
                }
            }
        }

        if (victory != 0)
            break;

        window.clear();

        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);

        for (int line = 0; line < 3; line++) {
            for (int column = 0; column < 3; column++) {
                sprite[line][column].setPosition(column * 400, line * 400);
                window.draw(sprite[line][column]);
            }
        }

        window.display();
    }

    return 0;
}