#include "graph.h"
#include <iostream>
#include <vector>
using namespace std;

                
graph::graph(int size)
{
	adjList.resize(size);
}

void graph::addEdge(int start, int dest)
{
	adjList[start].push_back(dest);
}

vector<int>* graph::getList(int x)
{
	vector<int>* vec = new vector<int>();
	for(auto t : adjList[x])
	{
		vec->push_back(t);
	}
	return vec;
}

void graph::printAdjList()
{
	for(int i = 0; i < adjList.size(); i++)
	{
		cout << i << ": ";
		for(auto x : adjList[i])
		{
			cout << x << " ";
		}
		cout << endl;
	}
}

bool graph::validWalk(vector<int> &walk)
{
	bool valid;
	for(int i = 0; i < walk.size() - 1; i++)
	{
		valid = false;
		for(auto x : adjList[walk[i]])
		{
			if(x == walk[i + 1])
			{
				valid = true;
			}
		}

		if(!valid){return false;}
	}
	return true;
}

void graph::walkAnalysis(vector<int> &walk)
{
	bool closed = false;
	bool trail = false;
	bool path = false;
	bool circuit = false;
	bool cycle = false;

	if(walk[0] == walk[walk.size() - 1])
	{
		closed = true;
	}
	
	bool repeated;

	for(int i = 0; i < walk.size() - 1; i++)
	{
		repeated = false;

		for(int j = i + 1; j < walk.size(); j++)
		{
			if(walk[i] == walk[j] && walk[i + 1] == walk[j + 1])
			{
				repeated = true;
				break;
			}
			else if(walk[i] == walk[j + 1] && walk[i + 1] == walk[j])
			{
				repeated = true;
				break;
			}
		}
		if(repeated){break;}
	}

	if(!repeated){trail = true;}
	
	if(trail && closed)
	{
		circuit = true;
	}

	if(trail)
	{
		for(int i = 0; i < walk.size(); i++)
		{
			repeated = false;
			for(int j = 0; j < walk.size(); j++)
			{
				if(j == i){continue;}
				if(walk[i] == walk[j])
				{
					repeated = true;
					break;
				}
			}
			if(repeated){break;}
		}
		if(!repeated){path = true;}
	}

	if(circuit)
	{
		for(int i = 0; i < walk.size() - 1; i++)
		{	
			if(walk[0] != walk[walk.size() - 1]);
			repeated = false;
                        for(int j = 0; j < walk.size() - 1; j++)
                        {
                                if(j == i){continue;}
                                if(walk[i] == walk[j])
                                {
                                        repeated = true;
                                        break;
                                }
                        }
                        if(repeated){break;}
		}
		if(!repeated){cycle = true;}
	}

	cout << "The walk sequence <";
	for(int i = 0; i < walk.size(); i++)
	{
		cout << walk[i];
		if(i != walk.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "> has the following properties: " << endl;

	if(closed)
	{
		cout << "CLOSED" << endl;
	}
	else
	{
		cout << "OPEN" << endl;
	}

	if(trail)
	{
		cout << "TRAIL" << endl;
	}

	if(path)
	{
		cout << "PATH" << endl;
	}

	if(circuit)
	{
		cout << "CIRCUIT" << endl;
	}

	if(cycle)
	{
		cout << "CYCLE" << endl;
	}
}
