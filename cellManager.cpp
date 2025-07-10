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
}

void cellManager::init_cells(int firstClick, int size)
{
	std::vector<bool> isBomb;
	int numBombs;
	switch(size)
	{
		case 81: {numBombs = 10; break;}
		case 256: {numBombs = 40; break;}
		case 480: {numBombs = 99; break;}
	}

	for(int i = 0; i < numBombs; i++)
	{
		isBomb.push_back(true);
	}
	for(int i = numBombs; i < size; i++)
	{
		isBomb.push_back(false);
	}
	
	std::vector<int>* adjIdx = connect->getList(firstClick);
	

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(isBomb.begin(), isBomb.end(), std::default_random_engine(seed));
		
	isBomb[firstClick] = 0;
	for(int i = 0; i < adjIdx->size(); i++)
	{
		int idx = adjIdx->at(i);
		isBomb[idx] = false;
	}
	
	

	for(int i = 0; i < size; i++)
	{
		if(isBomb[i] == true)
		{
			cell* newCell = new cell('b');
			store.push_back(newCell);
		}
		else
		{	
			cell* newCell = new cell('n');
			store.push_back(newCell);
		}
	}
	isBomb.clear();

	for(int i = 0; i < store.size(); i++)
	{
		std::vector<int>* adjIdx = connect->getList(i);
		int bombCount = 0;
		for(int j = 0; j < adjIdx->size(); j++)
		{
			int a = adjIdx->at(j);
			if(store[a]->get_type() == 'b')
			{
				bombCount++;
			}
		}
		store[i]->init(bombCount, i, store.size());
	}
	
}

int cellManager::check_index(int nx, int ny, int size)
{
	int width, height;

	switch(size)
	{
		case 81: {width = 9; height = 9; break;}
		case 256: {width = 16; height = 16; break;}
		case 480: {width = 30; height = 16; break;}
		default: {return -1;}
	}

	if(nx < 0 || ny < 0 || nx >= width || ny >= height)
	{
		return -1;
	}


	return ny * width + nx;
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
		default:
		{
			return (cords){.x = 0, .y = 0};
		}
	}
}

void cellManager::draw_assets(sf::RenderWindow &window)
{
	for(int i = 0; i < store.size(); i++)
	{
		if(store[i]->get_broken() == true)
		{
			window.draw(store[i]->get_block());
			window.draw(store[i]->get_num());
		}
		else if(store[i]->get_flag_set() == true)
		{
			window.draw(store[i]->get_flag());
		}
	}
}

void cellManager::check_cell(int index, char type)
{
	switch(type)
	{
		case 'l':
		{
			if(store[index]->get_type() == 'b')
			{
				gameOver = true;
				store[index]->set_bomb();
				bombIndex = index;
				return;
			}
			
			else if(store[index]->get_num_adj_bomb() > 0)
			{
				store[index]->start_break();
			}
			else
			{
				std::vector<int> seen;
				start_break(index, seen);
				seen.clear();
			}
		break;
		}
		case 'r':
		{
			store[index]->set_flag();
		break;
		}
	}
}

void cellManager::start_break(int index, std::vector<int> &seen)
{
	std::vector<int>* vec = connect->getList(index);
	for(int i = 0; i < vec->size(); i++)
	{	
		int index = vec->at(i);
	
  		if(std::find(seen.begin(), seen.end(), index) != seen.end())
            	continue;

		seen.push_back(index);
		store[index]->start_break();
		if(store[index]->get_num_adj_bomb() == 0 && store[index]->get_type() != 'b')
		{
			start_break(index, seen);
		}
	}
}

bool cellManager::get_game_state()
{
	return gameOver;
}

void cellManager::draw_bomb(sf::RenderWindow &window)
{
	window.draw(store[bombIndex]->get_bomb());
}

void cellManager::break_block(int index)
{

}

void cellManager::show_bombs(sf::RenderWindow &window)
{
	for(int i = 0; i < store.size(); i++)
	{
		if(store[i]->get_type() == 'b')
		{
			store[i]->reveal();
			window.draw(store[i]->get_bomb());
		}
	}
}
