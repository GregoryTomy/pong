#include "Ball.hpp"
#include "Bat.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <sstream>

int main()
{
    // create a video mode object
    VideoMode vm(1920 / 2, 800);

    RenderWindow window(vm, "Pong", Style::Default);

    int score = 0;
    int lastScore = -1;
    int lastLives = 4;
    int lives = 3;

    Bat bat(1920 / 4, 800 - 20);
    Ball ball(1920 / 4, 0);

    // add ball later

    // HUD
    Text hud;

    Font font;
    font.loadFromFile("fonts/DS-DIGI.TTF");

    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    // Clock for timing everythin
    Clock clock;

    while (window.isOpen())
    {
        /*
        **************************************************
        * Handle player input
        **************************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // quit the game when the window is closed
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }

            if (Keyboard::isKeyPressed(Keyboard::Left)) { bat.moveLeft(); }
            else { bat.stopLeft(); }

            if (Keyboard::isKeyPressed(Keyboard::Right)) { bat.moveRight(); }
            else { bat.stopRight(); }
        }
        /*
        **************************************************
        * Update the bat, the ball and the HUD
        **************************************************
        */
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);

        // ball colision at the bottom of the screen
        // remember that the top right is 0,0 and the numbers increase in the
        // negative y direction as positive numbers and to the right on the x
        // axis as positive numbers
        if (ball.getPosition().top > window.getSize().y)
        {
            ball.reboundBottom();
            lives--;
            if (lives < 1)
            {
                lives = 3;
                score = 0;
            }
        }

        // ball collision top of the screen
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatorTop();
            score++;
        }

        // ball collision on either sides
        if (ball.getPosition().left < 0 ||
            ball.getPosition().left + ball.getPosition().width >
                window.getSize().x)
        {
            ball.reboundSides();
        }

        // ball hitting the bat
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            ball.reboundBatorTop();
        }

        if (lastScore != score || lastLives != lives)
        {

            std::stringstream ss;
            ss << "Score: " << score << "    Lives: " << lives;
            hud.setString(ss.str());
            lastScore = score;
        }

        /*
        **************************************************
        * Draw the bat, the ball, and the HUD
        **************************************************
        */
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }

    return 0;
}
