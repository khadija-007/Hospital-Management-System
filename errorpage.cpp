#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

sf::SoundBuffer generateBeep(int sampleRate = 44100, float freq = 523.f, float duration = 0.4f)
{
    int sampleCount = static_cast<int>(sampleRate * duration);
    std::vector<sf::Int16> samples(sampleCount);

    for (int i = 0; i < sampleCount; ++i)
    {
        float t = static_cast<float>(i) / sampleRate;
        float envelope = 1.0f - (t / duration); 
        samples[i] = static_cast<sf::Int16>(32767 * envelope * std::sin(2 * M_PI * freq * t));
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), samples.size(), 1, sampleRate);
    return buffer;
}
sf::SoundBuffer generateErrorSound(int sampleRate = 44100, float freq = 220.f, float duration = 0.4f)
{
    int sampleCount = static_cast<int>(sampleRate * duration);
    std::vector<sf::Int16> samples(sampleCount);

    for (int i = 0; i < sampleCount; ++i)
    {
        float t = static_cast<float>(i) / sampleRate;
        float envelope = 1.0f - (t / duration);

        float wave = std::sin(2 * M_PI * freq * t) >= 0 ? 1.f : -1.f;
        samples[i] = static_cast<sf::Int16>(32767 * envelope * wave);
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), samples.size(), 1, sampleRate);
    return buffer;
}
void showErrorWindow(string message)
{
    sf::RenderWindow window(
        sf::VideoMode(600, 300),
        "Error",
        sf::Style::Titlebar | sf::Style::Close
    );
    sf::SoundBuffer buffer = generateErrorSound(); 
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text errorText;
    errorText.setFont(font);
    errorText.setString(message);
    errorText.setCharacterSize(28);
    errorText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = errorText.getLocalBounds();

    errorText.setOrigin(
        textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f
    );

    errorText.setPosition(300, 100);

    sf::RectangleShape button(sf::Vector2f(220, 60));

    button.setPosition(190, 190);

    button.setFillColor(sf::Color(180, 50, 50));

    sf::Text buttonText;

    buttonText.setFont(font);
    buttonText.setString("BACK");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    sf::FloatRect btnBounds = buttonText.getLocalBounds();

    buttonText.setOrigin(
        btnBounds.left + btnBounds.width / 2.f,
        btnBounds.top + btnBounds.height / 2.f
    );

    buttonText.setPosition(
        button.getPosition().x + button.getSize().x / 2.f,
        button.getPosition().y + button.getSize().y / 2.f
    );

    sf::Cursor arrow, hand;

    arrow.loadFromSystem(sf::Cursor::Arrow);
    hand.loadFromSystem(sf::Cursor::Hand);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(
                    event.mouseButton.x,
                    event.mouseButton.y
                );

                if (button.getGlobalBounds().contains(mouse))
                {
                    window.close();
                }
            }
        }

        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (button.getGlobalBounds().contains(mouse))
        {
            button.setFillColor(sf::Color(220, 70, 70));
            window.setMouseCursor(hand);
        }
        else
        {
            button.setFillColor(sf::Color(180, 50, 50));
            window.setMouseCursor(arrow);
        }

        window.clear(sf::Color(35, 35, 35));

        window.draw(errorText);

        window.draw(button);
        window.draw(buttonText);

        window.display();
    }
}



void showSuccessWindow(string message)
{

    sf::SoundBuffer buffer = generateBeep(); 
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
   
     sf::RenderWindow window(sf::VideoMode(600, 300),
    "Success",
    sf::Style::Titlebar | sf::Style::Close
    );

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);

    sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );

    text.setPosition(300, 120);

    sf::RectangleShape button(sf::Vector2f(200, 60));
    button.setPosition(200, 200);
    button.setFillColor(sf::Color(50, 180, 50));

    sf::Text btnText;
    btnText.setFont(font);
    btnText.setString("OK");
    btnText.setCharacterSize(24);
    btnText.setFillColor(sf::Color::White);

    sf::FloatRect b = btnText.getLocalBounds();

    btnText.setOrigin(
        b.left + b.width / 2.f,
        b.top + b.height / 2.f
    );

    btnText.setPosition(
        button.getPosition().x + 100,
        button.getPosition().y + 30
    );

    sf::Cursor arrow, hand;
    arrow.loadFromSystem(sf::Cursor::Arrow);
    hand.loadFromSystem(sf::Cursor::Hand);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (button.getGlobalBounds().contains(mouse))
                    window.close();
            }
        }

        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (button.getGlobalBounds().contains(mouse))
        {
            window.setMouseCursor(hand);
        }
        else
        {
            window.setMouseCursor(arrow);
        }

        window.clear(sf::Color(30, 30, 30));

        window.draw(text);
        window.draw(button);
        window.draw(btnText);

        window.display();
    }
}