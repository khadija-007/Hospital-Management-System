#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "loginpage.h"
using namespace std;


LoginData showLoginPage(string role)
{
    sf::RenderWindow window(sf::VideoMode(700, 500), role + " Login");

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text title;
    title.setFont(font);
    title.setString(role + " LOGIN");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Blue);
    title.setPosition(220, 50);

    sf::RectangleShape idBox(sf::Vector2f(350, 50));
    idBox.setFillColor(sf::Color::White);
    idBox.setPosition(180, 160);

    sf::RectangleShape passBox(sf::Vector2f(350, 50));
    passBox.setFillColor(sf::Color::White);
    passBox.setPosition(180, 250);

    sf::RectangleShape loginButton(sf::Vector2f(180, 55));
    loginButton.setFillColor(sf::Color(0, 120, 255));
    loginButton.setPosition(270, 350);

    sf::Text idLabel, passLabel, loginText;
    idLabel.setFont(font);
    idLabel.setString("ID");
    idLabel.setCharacterSize(24);
    idLabel.setPosition(120, 170);

    passLabel.setFont(font);
    passLabel.setString("PASSWORD");
    passLabel.setCharacterSize(24);
    passLabel.setPosition(40, 260);

    loginText.setFont(font);
    loginText.setString("LOGIN");
    loginText.setCharacterSize(28);
    loginText.setFillColor(sf::Color::White);
    loginText.setPosition(315, 360);

    sf::Text idText, passText;
    idText.setFont(font);
    idText.setCharacterSize(24);
    idText.setFillColor(sf::Color::Black);
    idText.setPosition(190, 170);

    passText.setFont(font);
    passText.setCharacterSize(24);
    passText.setFillColor(sf::Color::Black);
    passText.setPosition(190, 260);

    char enteredID[50] = "";
    char enteredPassword[50] = "";

    int idIndex = 0;
    int passIndex = 0;

    bool typingID = true;
    bool typingPassword = false;

    LoginData data;
    data.success = true;
    sf::Cursor arrowCursor, textCursor, handCursor;
    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    textCursor.loadFromSystem(sf::Cursor::Text);
    handCursor.loadFromSystem(sf::Cursor::Hand);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                data.success = false;
                window.close();
            }

            if (event.type == sf::Event::TextEntered)
            {
                char ch = static_cast<char>(event.text.unicode);

                if (event.text.unicode == 8)
                {
                    if (typingID && idIndex > 0)
                        enteredID[--idIndex] = '\0';

                    if (typingPassword && passIndex > 0)
                        enteredPassword[--passIndex] = '\0';
                }
                else if (event.text.unicode < 128 && event.text.unicode != 13)
                {
                    if (typingID && idIndex < 49)
                        enteredID[idIndex++] = ch;

                    if (typingPassword && passIndex < 49)
                        enteredPassword[passIndex++] = ch;

                    enteredID[idIndex] = '\0';
                    enteredPassword[passIndex] = '\0';
                }

                idText.setString(enteredID);

                string hidden(passIndex, '*');
                passText.setString(hidden);
            }


            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (typingID)
                    {
                        typingID = false;
                        typingPassword = true;
                    }
                    else
                    {
                        typingID = true;
                        typingPassword = false;
                    }
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    strcpy_s(data.id, enteredID);
                    strcpy_s(data.password, enteredPassword);

                    window.close();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (idBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    typingID = true;
                    typingPassword = false;
                }
                else if (passBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    typingID = false;
                    typingPassword = true;
                }
                else if (loginButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    strcpy_s(data.id, enteredID);
                    strcpy_s(data.password, enteredPassword);
                    window.close();
                }
            }
        }

        // ================= OPTION 1: FOCUS HIGHLIGHT =================
        if (typingID)
        {
            idBox.setOutlineThickness(3);
            idBox.setOutlineColor(sf::Color::Cyan);

            passBox.setOutlineThickness(0);
        }
        else if (typingPassword)
        {
            passBox.setOutlineThickness(3);
            passBox.setOutlineColor(sf::Color::Cyan);

            idBox.setOutlineThickness(0);
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(mousePos.x, mousePos.y);

        if (idBox.getGlobalBounds().contains(mousePosF) ||
            passBox.getGlobalBounds().contains(mousePosF))
            window.setMouseCursor(textCursor);
        else if (loginButton.getGlobalBounds().contains(mousePosF))
            window.setMouseCursor(handCursor);
        else
            window.setMouseCursor(arrowCursor);

        window.clear(sf::Color(30, 30, 30));

        window.draw(title);

        window.draw(idBox);
        window.draw(passBox);
        window.draw(loginButton);

        window.draw(idLabel);
        window.draw(passLabel);
        window.draw(loginText);

        window.draw(idText);
        window.draw(passText);

        window.display();
    }

    return data;
}
