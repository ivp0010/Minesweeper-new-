#include "cellManager.h"

cellManager::cellManager(int size)
{
	gameOver = false;
	connect = new graph(size);
	int directions[8][2] = {{0,  1}, { 0, -1}, { 1,  0}, {-1,  0}, { 1,  1}, {-1,  1}, { 1, -1}, {-1, -1}};
	
	for(int i = 0; i < size; i++)
	{
		cords temp = get_cords(i, size);
		for(int j = 0; j < 8; j++)
		{
			int nx = temp.x + directions[j][0];
			int ny = temp.y + directions[j][1];
			int idx = check_index(nx, ny, size);
			if(idx != -1)
			{
				connect->addEdge(i, idx);
			}
		}
	}
		connect->printAdjList();
}

int cellManager::check_index(int nx, int ny, int size)
{
	switch(size)
	{
		case 81:
		{
			int index = ny * 9 + nx;
			if(index > 80 || index < 0)
			{
				return -1;
			}
			else
			{
				return index;
			}
		}
		case 256:
		{
			int index = ny * 16 + nx;
			if(index > 255 || index < 0)
			{
				return -1;
			}
			else
			{
				return index;
			}	
		}
		case 480:
		{
			int index = ny * 30 + nx;
			if(index > 479 || index < 0)
			{
				return -1;
			}
			else
			{
				return index;
			}
		}
	}
return -1;
}

cords cellManager::get_cords(int index, int size)
{
	switch(size)
	{
		case 81:
		{
			int x = index % 9;
			int y = index / 9;
			return (cords){.x = x, .y = y};
		}
		case 256:
		{
			int x = index % 16;
			int y = index / 16;
			return (cords){.x = x, .y = y};
		}
		case 480:
		{
			int x = index % 30;
			int y = index / 30;
			return (cords){.x = x, .y = y};
		}	
	}
return (cords){.x = -1, .y = -1};
}

void cellManager::draw_assets(sf::RenderWindow &window)
{

}

void cellManager::check_cell(int index, char type)
{

}

void cellManager::start_break(int index, std::vector<int> &seen)
{

}

void cellManager::set_flag(int index)
{

}

bool cellManager::get_game_state()
{

}

void cellManager::draw_bomb(int index, sf::RenderWindow &window)
{

}

void cellManager::break_block(int index)
{

}
