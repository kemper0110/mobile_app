#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Forms.h"
// only one of them
#define windows
//#define android


sf::Font font;


class Lable {
protected:
	sf::Text TXT;
	Lable() {}

public:

	Lable(std::string text, sf::Vector2f pos, int size = 30) {
		TXT.setFont(font);
		TXT.setCharacterSize(size);
		TXT.setFillColor(sf::Color::Black);
		TXT.setOutlineColor(sf::Color::Blue);
		TXT.setOutlineThickness(1.f);
		TXT.setPosition(pos);
		TXT.setString(text);
	}
	sf::Text operator()(){
		return TXT;
	}
};

class Button : Lable{
	Lable lable;
public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string text = "") {
		lable = Lable(text, pos);

	}
};


sf::CircleShape make_circle() {
	sf::CircleShape c(50);
	c.setFillColor(sf::Color::Red);
	c.setOutlineColor(sf::Color::Green);
	c.setOutlineThickness(3);
	c.setPosition(0, 0);
	return c;
}

int main(){
	font.loadFromFile("Century Gothic Regular.ttf");

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "mobile", sf::Style::Fullscreen, settings);

	Lable ip_lable("IP input", { (float)window.getSize().x / 2, (float)window.getSize().y / 2 }, 40);
	auto circle = make_circle();

	while (1) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
#ifdef windows
			if (event.type == sf::Event::KeyPressed) {
				if (event.KeyPressed == sf::Keyboard::Escape) {
					window.close();
					return 0;
				}
			}
#endif // windows
			if (
#ifdef windows
				event.type == sf::Event::MouseMoved
#endif // windows
#ifdef android
				event.type == sf::Event::TouchMoved || event.type == sf::Event::TouchBegan
#endif // android
				) {
				circle.setPosition(event.mouseMove.x - circle.getRadius(), event.mouseMove.y - circle.getRadius());
			}
	
		}
		window.clear(sf::Color(255, 255, 255));
		window.draw(ip_lable());
		window.draw(circle);
		window.display();
		sf::sleep(sf::milliseconds(10));
	}
}

