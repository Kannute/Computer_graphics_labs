#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"
#include "DrawFunctions.h"
#include <iostream>


class Menu : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;

	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
	{
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}

public:
	Menu()
	{
		font.loadFromMemory(font_data, font_data_size);
		text = new sf::Text;
		text->setFont(font);
		text->setCharacterSize(12);
		text->setFillColor(sf::Color::White);

		rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
		rectangle->setFillColor(sf::Color::Transparent);
		rectangle->setOutlineColor(sf::Color::White);
		rectangle->setOutlineThickness(1.0f);
		rectangle->setPosition(2, 62);

		unsigned int x, y;
		colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
		for (x = 0; x < 255; x++)
			for (y = 0; y < 30; y++)
			{
				draw_to_color_pixels(x, y, x, 255, 0);
				draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
				draw_to_color_pixels(x + 510, y, 255, 0, x);
				draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
				draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
				draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
			}

		colors_texture = new sf::Texture();
		colors_texture->create(colors_size_x, colors_size_y);
		colors_texture->update(colors_pixels);

		colors_sprite = new sf::Sprite();
		colors_sprite->setTexture(*colors_texture);
		colors_sprite->setPosition(1, 1);
	}

	void outtextxy(sf::RenderTarget& target, float x, float y, wchar_t *str) const
	{
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		outtextxy(target, 5, 600, const_cast<wchar_t*>(L"f - choose a color"));
		outtextxy(target, 5, 615, const_cast<wchar_t*>(L"b - choose a filling color"));
		outtextxy(target, 5, 630, const_cast<wchar_t*>(L"l - draw a line"));

		outtextxy(target, 200, 600, const_cast<wchar_t*>(L"r - draw a rectangle"));
		outtextxy(target, 200, 615, const_cast<wchar_t*>(L"a - draw a filled rectangle"));
		outtextxy(target, 200, 630, const_cast<wchar_t*>(L"c - draw a circle"));

		outtextxy(target, 470, 600, const_cast<wchar_t*>(L"w - save to file"));
		outtextxy(target, 470, 615, const_cast<wchar_t*>(L"o - read from file"));
		outtextxy(target, 470, 630, const_cast<wchar_t*>(L"Esc - exit"));

		outtextxy(target, 650, 615, const_cast<wchar_t*>(L"Current:"));

		target.draw(*rectangle);
		target.draw(*colors_sprite);

	}
};

int main()
{
	// tworze okno
	sf::RenderWindow window(sf::VideoMode(800, 650), "Kacper Luka PGK - Lab01", sf::Style::Titlebar | sf::Style::Close);

	// ustawiam limit klatek na sekunde
	window.setFramerateLimit(60);
    // tworze obiekty event i menu
	sf::Event event;

	Menu menu;


	// tworze font, tekst oraz tekst oznajmiajacy o bledzie
	sf::Font font;

	if (!font.loadFromMemory(font_data, font_data_size))
	{
		window.close();

	}

	sf::Text *text, *error_text;
	text = new sf::Text;
	error_text = new sf::Text;

	text->setFont(font);
	error_text->setFont(font);
    // ustawiam rozmiar oraz kolor tekstow
	text->setCharacterSize(15);
	error_text->setCharacterSize(15);

	text->setFillColor(sf::Color::White);
	error_text->setFillColor(sf::Color::Red);


	// ustawiam kolory
	sf::Color main_colour = sf::Color(0, 0, 0, 0);
	sf::Color fill_colour = sf::Color(0, 0, 0, 0);

	// przechowuje zaakceptowany stan obrazu
	sf::Texture accepted_frame;
	accepted_frame.create(800, 650);

	// przechowuje tymczasowy stan obrazu
	sf::Texture real_time;
	real_time.create(800, 650);

	// sprite uzywany do wyswietlenia zaakceptowanego stanu obrazu
	sf::Sprite sprite;
	sprite.setTexture(accepted_frame);

	// przechowuje palete kolorow

	sf::Image palette, saved_cropped;
	palette.create(765, 60);
	saved_cropped.create(796, 536);


	// flaga mowiaca ktora operacje program ma wykonac
	char selection = ' ';

	// flaga flag mowi nam, czy przycisk myszy jest wcisniety
	// flaga error oznajmia o bledach odczytu lub zapisu
	bool flag = false, error = false;

	// poczatkowe punkty uzywane przy rysowaniu figur i linii
	int start_x = 0, start_y = 0;



	// tablica klasy Vertex uzywana do rysowania linii
	sf::Vertex line[5];

	// obiekt uzywany przy rysowaniu prostokatow
	sf::RectangleShape rectangle;

	// obiekty uzywane do wyswietlania prostokatow wyboru koloru
	sf::RectangleShape colour_rect, fillcolour_rect;

	// obiekt uzywany przy rysowaniu okregu
	sf::CircleShape circle;

	// zmienna okreslajaca grubosc obramowania
	float outline_size = 1.0f;

	// zmienna okreslajaca wypelnienie lub jego brak
	bool fill = 0;

	//ustawiam poczatkowego wygladu prostokatow zmiany kolorow
	colour_rect.setPosition(sf::Vector2f(767, 1));
	colour_rect.setSize(sf::Vector2f(35, 29));
	colour_rect.setOutlineColor(sf::Color::White);
	colour_rect.setOutlineThickness(outline_size);

	fillcolour_rect.setPosition(sf::Vector2f(767, 31));
	fillcolour_rect.setSize(sf::Vector2f(35, 29));
	fillcolour_rect.setOutlineColor(sf::Color::White);
	fillcolour_rect.setOutlineThickness(outline_size);

	// wypisanie menu
	window.draw(menu);
	real_time.update(window);

	// ustawiam palety kolorow
	palette = real_time.copyToImage();

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		colour_rect.setFillColor(main_colour);
		fillcolour_rect.setFillColor(fill_colour);

		while (window.pollEvent(event))
		{
			// procedura w przypadku proby zamkniecia okna
			if (event.type == sf::Event::Closed) window.close();

			// procedura w przypadku nacisniecia klawisza na klawiaturze
			if (event.type == sf::Event::KeyPressed)
			{
				error = 0;
				// odczyt od usera
				switch (event.key.code)
				{
					// f - wybór koloru rysowania
					case (sf::Keyboard::F):
					{
						selection = 'f';
						//std::cout << 'f' << std::endl;
						break;
					}

					// b - wybór koloru wypelniania
					case (sf::Keyboard::B):
					{
						selection = 'b';
						//std::cout << 'b' << std::endl;
						break;
					}

					// l - rysowanie linii
					case (sf::Keyboard::L):
					{
						selection = 'l';
						//std::cout << 'l' << std::endl;
						break;
					}

					// b - rysowanie prostokata
					case (sf::Keyboard::R):
					{
						selection = 'r';
						//std::cout << 'r' << std::endl;
						break;
					}

					// a - rysowanie prostokata (wypelnionego)
					case (sf::Keyboard::A):
					{
						selection = 'a';
						//std::cout << 'a' << std::endl;
						break;
					}

					// c - rysowanie okregu
					case (sf::Keyboard::C):
					{
						selection = 'c';
						//std::cout << 'c' << std::endl;
						break;
					}

					// w - zapis do pliku
					case (sf::Keyboard::W):
					{
						selection = 'w';
						//std::cout << 'w' << std::endl;
						error = 0;

						if (!accepted_frame.copyToImage().saveToFile("savefile.jpg"))
						{
							error = 1;
							error_text->setPosition(680, 630);
							error_text->setString("write error");
						}
						break;
					}

					// o - odczyt z pliku
					case (sf::Keyboard::O):
					{
						selection = 'o';
						error = 0;

						if (!accepted_frame.loadFromFile("savefile.jpg"))
						{
							error = 1;
							error_text->setPosition(680, 630);
							error_text->setString("read error");
						}
						break;
					}

					// escape - wyjscie z aplikacji
					case (sf::Keyboard::Escape):
					{
						window.close();
						std::cout << "Program closed" << std::endl;
						break;
					}

					// inny przycisk - wyswietlenie informacje o bledzie
					default:
					{
						error = 1;
						error_text->setPosition(680, 630);
						error_text->setString("Wrong letter!");
					}
				}

			}

			// procedura w przypadku nacisniecia przycisku myszki
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				//sprawdzam czy naciskamy w dobrym miejscu
				if (isonWorkspace(window)) flag = true;

				start_x = sf::Mouse::getPosition(window).x;
				start_y = sf::Mouse::getPosition(window).y;

				//w przypadku wybrania koloru
				switch (selection)
				{
				case 'f':
					if ((sf::Mouse::getPosition(window).y <= 60) && (sf::Mouse::getPosition(window).x <= 765))
						main_colour = palette.getPixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					break;

				case 'b':
					if ((sf::Mouse::getPosition(window).y <= 60) && (sf::Mouse::getPosition(window).x <= 765))
						fill_colour = palette.getPixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					break;
				}
			}

			// procedura w przypadku puszczenia przycisku myszki
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				flag = false;

				// zapisuje aktualny stan ekranu
				accepted_frame.update(real_time.copyToImage());
			}
		}

		//Draw BEGIN

		window.draw(sprite);

		if (flag)
		{
			switch (selection)
			{
			case 'l':
				drawLine(line, start_x, start_y, main_colour, fill_colour, window);
				break;

			case 'r':
				fill = 0;
				drawRectangle(rectangle, start_x, start_y, outline_size, main_colour, fill_colour, window, fill);
				break;

			case 'a':
				fill = 1;
				drawRectangle(rectangle, start_x, start_y, outline_size, main_colour, fill_colour, window, fill);
				break;

			case 'c':
				drawCircle(circle, start_x, start_y, outline_size, main_colour, fill_colour, window);
				break;
			}
		}
		real_time.update(window);

		//wypisanie prostokatow wyboru koloru
		window.draw(colour_rect);
		window.draw(fillcolour_rect);

		//wypisanie menu
		window.draw(menu);

		//wypisanie wybranej przez nas komendy
		text->setPosition(650, 630);
		text->setString(selection);
		window.draw(*text);

		//wypisanie informacji o bledzie (jesli istnieje)
		if (error == 1 ) window.draw(*error_text);

		window.display();

		//Draw END

	}
	return 0;
}
