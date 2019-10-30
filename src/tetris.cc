#include <iostream>
#include <SFML/Graphics.hpp>
#include "screen.h"

using namespace std;

int main()
{
    int sleep{};
    char bot;
    bool fast;
    cout << "Choose player or bot (p/b): ";
    cin >> bot;
    if (bot == 'b')
    {
	int temp{};
	cout << "Choose bot speed: ";
	cin >> sleep;
	cout << "Fast or not (0/1): ";
	cin >> temp;
	fast = temp == 0;	
    }
    sf::RenderWindow window{sf::VideoMode(850,1100), "Tetris"};
    Screen c{sleep, fast};
    while (window.isOpen())
    {
	sf::Event event;
	while (window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
	    c.Move(false);
	    std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
	    c.Move(true);
	    std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
	    std::this_thread::sleep_for (std::chrono::milliseconds(500));
	    c.Down();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
	    std::this_thread::sleep_for (std::chrono::milliseconds(300));
	    c.rotate();
	}
    window.clear(sf::Color(0,255,255));
    c.Draw(window);
    window.display();
    }

    
    return 0;
}
