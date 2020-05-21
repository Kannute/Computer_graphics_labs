#pragma once

// rysowanie linii
void drawLine(sf::Vertex *line, const int &start_x, const int &start_y, const sf::Color &main_colour, const sf::Color &fill_colour, sf::RenderWindow &window)
{
	line[0].position = sf::Vector2f(static_cast<float> (start_x), static_cast<float> (start_y));
	line[0].color = main_colour;
	line[1].position = sf::Vector2f(static_cast<float> (sf::Mouse::getPosition(window).x), static_cast<float> (sf::Mouse::getPosition(window).y));
	line[1].color = fill_colour;

	window.draw(line, 5, sf::Lines);
}
// rysowanie prostokata (pustego lub wypelnionego)
void drawRectangle(sf::RectangleShape rectangle, const int &start_x, const int &start_y, const float &outline_size, const sf::Color &main_colour, const sf::Color &fill_colour, sf::RenderWindow &window, const bool &fill)
{

	rectangle.setSize(sf::Vector2f(static_cast<float> (sf::Mouse::getPosition(window).x - start_x), static_cast<float> (sf::Mouse::getPosition(window).y - start_y)));

	if (fill == 0) rectangle.setFillColor(sf::Color::Transparent);

	else rectangle.setFillColor(fill_colour);

	rectangle.setOutlineColor(main_colour);
	rectangle.setOutlineThickness(outline_size);
	rectangle.setPosition(static_cast<float> (start_x), static_cast<float> (start_y));
	window.draw(rectangle);
}
// rysowanie okregu
void drawCircle(sf::CircleShape circle, const int &start_x, const int &start_y, const float &outline_size, const sf::Color &main_colour, const sf::Color &fill_colour, sf::RenderWindow &window)
{
	float radius = (sqrt(static_cast<float> (pow(sf::Mouse::getPosition(window).x - start_x, 2) + pow(sf::Mouse::getPosition(window).y - start_y, 2))) / 2);
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(main_colour);
	circle.setOutlineThickness(outline_size);
	circle.setPosition(start_x + (sf::Mouse::getPosition(window).x - start_x) / 2 - radius, start_y + (sf::Mouse::getPosition(window).y - start_y) / 2 - radius);
	circle.setRotation(atan2f(sf::Mouse::getPosition(window).x - start_x, sf::Mouse::getPosition(window).y - start_y));
	window.draw(circle);
}
// sprawdzam czy kursor znajduje sie w oknie
bool isonWorkspace(sf::RenderWindow &window)
{
	if (sf::Mouse::getPosition(window).y >= 61 && sf::Mouse::getPosition(window).y <= 600)
		return true;

	else
		return false;
}
