#ifndef ZONES_H
#define ZONES_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class zones
{

	public:

		zones(int size);
		sf::FloatRect getZones(int x);
		int getNumZones();

	private:
		
		std::vector<sf::FloatRect*> zone;
};

#endif
