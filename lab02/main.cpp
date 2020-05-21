#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Burrito.h"
#include <iostream>
#include <sstream>
int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Kacper £uka - Lab02", sf::Style::Titlebar | sf::Style::Close);


    sf::Clock clock;

    unsigned int FPS = 0 , frame_counter = 0;

    //wczytuje czcionke
    sf::Font font;
    font.loadFromFile("./arial.ttf");
    if (!font.loadFromFile("arial.ttf"))
    {
    std::cout << "Blad we wczytywaniu czcionki\n" << std::endl;
    return -1;
    }
    //przygotowywuje teksty do wypisania na ekran

    sf::Text _rgb;
    sf::Text _hsl;
    sf::Text _hsv;
    sf::Text _cmy;
    sf::Text _fps;


    _rgb.setFont(font);
    _cmy.setFont(font);
    _hsl.setFont(font);
    _hsv.setFont(font);
    _fps.setFont(font);


    _rgb.setString(L"RGB");
    _cmy.setString(L"CMY");
    _hsl.setString(L"HSL");
    _hsv.setString(L"HSV");
    _fps.setString(L"FPS");


    _rgb.setCharacterSize(20);
    _cmy.setCharacterSize(20);
    _hsl.setCharacterSize(20);
    _hsv.setCharacterSize(20);
    _fps.setCharacterSize(20);


    _rgb.setColor(sf::Color::Black);
    _cmy.setColor(sf::Color::Black);
    _hsl.setColor(sf::Color::Black);
    _hsv.setColor(sf::Color::Black);
    _fps.setColor(sf::Color::Red);

    _rgb.setStyle(sf::Text::Bold);
    _cmy.setStyle(sf::Text::Bold);
    _hsl.setStyle(sf::Text::Bold);
    _hsv.setStyle(sf::Text::Bold);
    _fps.setStyle(sf::Text::Bold | sf::Text::Underlined);

    _hsl.move(20.f, 10.f);
    _cmy.move(20.f, 280.f);
    _rgb.move(280.f, 280.f);
    _hsv.move(280.f, 10.f);
    _fps.move(600.f, 400.f);
    Burrito burrito;
    sf::Event event;

    //inicjalizacja
    clock.restart().asSeconds();
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    burrito.changeColors(event.mouseButton.x,event.mouseButton.y);
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (event.type == sf::Event::MouseMoved)
                {
                    burrito.changeColors(event.mouseMove.x,event.mouseMove.y);
                }
            }
        }
        //tu wyrysowaæ wszystko na ekran
        window.clear(sf::Color::White);
        window.draw(burrito);

        window.draw(_cmy);
        window.draw(_hsl);
        window.draw(_hsv);
        window.draw(_rgb);

        std::stringstream s;
        s << FPS;
        _fps.setString(s.str());
        window.draw(_fps);

        //tu wypisaæ na ekran wartoœæ FPS
        //std::cout<<"FPS: "<<FPS<<std::endl;
        if (clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
            clock.restart();
            frame_counter = 0;
        }
        frame_counter++;
        window.display();
    }
    return  0;
}

