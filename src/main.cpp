#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.h"
#include <iostream>
#include <thread>
void runPrototype() {
    std::cout << "Welcome, adventurer, to Dogoo\n";
    std::cout << "Please, inform us of your name\n";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "Very well, your name is " << name << "\n";
}

int main()
{
    std::thread test(runPrototype);
	sf::RenderWindow window(sf::VideoMode(672,544), "Teste");
    sf::Texture texture;
    if(!texture.loadFromFile("resources/map21x17.png")) {
        return -1;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
	while (window.isOpen()) {
	    sf::Event event;
	 	while (window.pollEvent(event)) {
	 		if (event.type == sf::Event::Closed)
 			    window.close();
 	    }
 	    window.clear(sf::Color::Black);
        window.draw(sprite);
	    window.display(); 
    }
    test.join();
	
    
    

	return 0;
}
