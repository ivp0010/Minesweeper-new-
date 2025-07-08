#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
using namespace std;
class graph
{
	public:
		
		graph(int size);
		void addEdge(int start, int dest);
		void printAdjList();
		vector<int>* getList(int x);
		bool validWalk(vector<int> &walk);
		void walkAnalysis(vector<int> &walk);
	private:
		
		vector<vector<int>> adjList;
};
#endif 
