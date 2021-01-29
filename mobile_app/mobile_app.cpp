#include <SFML/Graphics.hpp>
#include <iostream>

// only one of them
#define windows
//#define android


sf::Font font;


class Lable {
protected:
	sf::Text TXT;
public:
	Lable() {
		TXT.setFont(font);
		TXT.setFillColor(sf::Color::Black);
		TXT.setOutlineColor(sf::Color::Blue);
		TXT.setOutlineThickness(1.f);
	}
	Lable(std::string text, sf::Vector2f pos, int size = 30) : Lable() {
		TXT.setCharacterSize(size);
		TXT.setPosition(pos);
		TXT.setString(text);
	}
	sf::Text operator+() {
		return TXT;
	}
};

class Button : Lable {
	Lable lable;
	sf::RectangleShape BOX;
public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string text = "") {
		lable = Lable(text, pos);

		BOX.setFillColor(sf::Color(230, 230, 230));
		BOX.setOutlineColor(sf::Color::Black);
		BOX.setPosition(pos);
		BOX.setSize(size);
	}
	bool isSelected(sf::Vector2i mouse) {
		if (mouse.x > BOX.getPosition().x
			&& mouse.x < BOX.getSize().x + BOX.getPosition().x
			&& mouse.y > BOX.getPosition().y
			&& mouse.y < BOX.getSize().y + BOX.getPosition().y)
			return true;
		return false;
	}
	void draw(sf::RenderWindow& window) {
		window.draw(BOX);
		window.draw(+lable);
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


bool lol = true;
int main() {
	font.loadFromFile("Century Gothic Regular.ttf");

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "mobile"/*, sf::Style::Fullscreen, settings*/);

	sf::Vector2f center{ (float)window.getSize().x / 2, (float)window.getSize().y / 2 };
	//Lable ip_lable("IP input", center, 40);
	Button button(center, { 100, 100 }, "button");
	auto circle = make_circle();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
#ifdef windows
			if (event.type == event.KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
#endif // windows
#ifdef windows
			if (event.type == event.MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
#endif // windows
#ifdef android
					if (event.type == sf::Event::TouchBegan)
#endif // android
						sf::Vector2i pos = 
#ifdef android
						event.touch
#endif // android
#ifdef windows
						sf::Mouse::getPosition()
#endif // windows
						- window.getPosition();
					if (button.isSelected(pos))
						lol = !lol;
				}
			}

			//			if (
			//#ifdef windows
			//				event.type == sf::Event::MouseMoved
			//#endif // windows
			//#ifdef android
			//				event.type == sf::Event::TouchMoved || event.type == sf::Event::TouchBegan
			//#endif // android
			//				) {
			//				circle.setPosition(event.mouseMove.x - circle.getRadius(), event.mouseMove.y - circle.getRadius());
			//			}

		}
		if (lol == true)
			window.clear(sf::Color(255, 255, 255));
		else
			window.clear(sf::Color(0, 0, 0));
		button.draw(window);
		//window.draw(+ip_lable);
		//window.draw(circle);
		window.display();
		sf::sleep(sf::milliseconds(10));
	}
}

