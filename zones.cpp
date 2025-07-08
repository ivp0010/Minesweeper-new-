#include "zones.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

zones::zones(int size)
{
	switch(size)
	{
		case 81:
		{
			float x1 = 0.f;
			float x2 = 0.f;
			float y1 = 100.f;
			float y2 = 100.f;

			for(int i = 0; i < 9; i++)
			{
				for(int j = 0; j < 9; j++)
				{
		
					sf::Vector2f x(x1, x2);
					sf::Vector2f y(y1, y2);
					float left = std::min(x.x, y.x);
					float top = std::min(x.y, y.y);
					float width = std::abs(y.x - x.x);
					float height = std::abs(y.y - x.y);
					sf::FloatRect* newRect = new sf::FloatRect(left, top, width, height);
					zone.push_back(newRect);
					x1 += 100.f;
					y1 += 100.f;
				}
	
				x1 = 0.f;
				x2 += 100.f;
				y1 = 100.f;
				y2 += 100.f;
			}
		break;
		}
		case 256:
		{
			float x1 = 0.f;
			float x2 = 0.f;
			float y1 = 56.25f;
			float y2 = 56.25f;

			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 16; j++)
				{
					sf::Vector2f x(x1, x2);
					sf::Vector2f y(y1, y2);
					float left = std::min(x.x, y.x);
					float top = std::min(x.y, y.y);
					float width = std::abs(y.x - x.x);
					float height = std::abs(y.y - x.y);
					sf::FloatRect* newRect = new sf::FloatRect(left, top, width, height);
					zone.push_back(newRect);
					x1 += 56.25f;
					y1 += 56.25f;
				}
				
				x1 = 0.f;
				x2 += 56.25f;
				y1 = 56.25f;
				y2 += 56.25f;
			}
		break;
		}
		case 480:
		{
			
			float x1 = 0.f;
			float x2 = 0.f;
			float y1 = 50.f;
			float y2 = 50.f;
			
			for(int i = 0; i < 16; i++)
			{
				for(int j = 0; j < 30; j++)
				{
					sf::Vector2f x(x1, x2);
					sf::Vector2f y(y1, y2);
					float left = std::min(x.x, y.x);
					float top = std::min(x.y, y.y);
					float width = std::abs(y.x - x.x);
					float height = std::abs(y.y - x.y);
					sf::FloatRect* newRect = new sf::FloatRect(left, top, width, height);
					zone.push_back(newRect);
					x1 += 50.f;
					y1 += 50.f;
				}
				
				x1 = 0.f;
				x2 += 50.f;
				y1 = 50.f;
				y2 += 50.f;
			}
		
		break;
		}

	}
}

sf::FloatRect zones::getZones(int x)
{
	return *(zone[x]);
}

int zones::getNumZones()
{
	return zone.size();
}
