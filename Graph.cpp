#include <iostream>
#include <fstream>
#include <queue>
#include "Nodes.h"

using namespace std;

bool readNodes(const char* filename, Graph& graph);
void breadthSearch(Graph& nodes);
void depthSearch(Graph& nodes);
void visitInsert(node_iterator it, set<Node*>& visited);
Node nodes[50];

int main()
{
	Graph graph, graph1, graph2;	
	readNodes("TestGraph.txt", graph);
	graph1 = graph;
	cout << "breadthSearch" << endl;
	while (graph1.begin()!= graph1.end()) { breadthSearch(graph1); }
	graph2 = graph;
	cout << "depthSearch" << endl;
	while (graph2.begin() != graph2.end()) { depthSearch(graph2); }
	

	
}

void breadthSearch(Graph& graph) {
	queue<Node*> q; 
	q.push(*graph.begin());
	set<Node*> visited;

	while (!q.empty()) {

		Node* next = q.front(); q.pop();
		visited.insert(next);
		for (node_iterator it = next->neighbours.begin(); it != next->neighbours.end(); it++)
			if (visited.find(*it) == visited.end())
				q.push(*it);
	}
	for (node_iterator v = visited.begin(); v != visited.end(); v++) {
		for (int n = 0; n < 50; n++) {
			if (nodes[n].getName() == (*v)->getName()) {
				graph.removeNode(&nodes[n]);
			}
		}
		cout << (*v)->getName() << " ";
	}
	cout << endl;
}

void depthSearch(Graph& graph) {
	set<Node*> visited;
	
	Node* next = *graph.begin(); 
	visited.insert(next);
	for (node_iterator it = next->neighbours.begin(); it != next->neighbours.end(); it++) {
		visitInsert(it, visited);
	}

	for (node_iterator v = visited.begin(); v != visited.end(); v++) {
		cout << (*v)->getName() << " ";
		for (int n = 0; n < 50; n++) {
			if (nodes[n].getName() == (*v)->getName()) {
				graph.removeNode(&nodes[n]);
			}
		}
	}
	cout << endl;
}

void visitInsert(node_iterator it, set<Node*>& visited) {
	visited.insert(*it);
	for (node_iterator n = (*it)->neighbours.begin(); n != (*it)->neighbours.end(); n++) {
		int vis = 0;
		for (node_iterator v = visited.begin(); v != visited.end(); v++) {
			if ((*n)->getName() == (*v)->getName()) {
				vis++;
			}  
		}
		if (vis == 0)
			visitInsert(n, visited);
	}
}

bool readNodes(const char* filename, Graph& graph)
{
	ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Can't open the file.";
		return false;
	}
	string x, y;
	in >> x >> y; 
	int name_a, name_b;  
	int i = 0;
	while (!in.eof()) { 
		Node* node_a = 0; 
		Node* node_b = 0;
		in >> name_a >> name_b;
		//cout << "name_a=" << name_a << " name_b=" << name_b <<endl<<"   ";   

		int foundA=-1, foundB=-1; 

		for (int n = 0; n < 50; n++) {
			if (nodes[n].getName() == name_a) {
				foundA = n;
				//cout << "name_a already exist" << endl << "   ";
			}
			else if (nodes[n].getName() == name_b) {
				foundB = n;
				//cout << "name_b already exist" << endl << "   ";
			}
		}

		
		if (foundA==-1) {					
			nodes[i].setName(name_a); 
			graph.addNode(&nodes[i]);		
			i++;	
			//cout << " Creat nb1 ";
			if (foundB==-1)				
			{
				nodes[i].setName(name_b);
				graph.addNode(&nodes[i]);
				//cout << " Creat nb2 ";
				graph.addEdge(&nodes[i-1], &nodes[i]);		
				//cout << " Creat EDGE workable " << endl;
				i++;
			}
			else {								
				graph.addEdge(&nodes[i - 1], &nodes[foundB]);	
				//cout<< "Existed Link = "<< nodes[foundB].getName();
				//cout << " Creat EDGE unworkable?" << endl;
				foundB = -1;
			}
		}
		else if (foundB==-1)		
		{
			nodes[i].setName(name_b);	
			graph.addNode(&nodes[i]);
			//cout << " Creat nb2. Existed Link = "<< nodes[foundA].getName();
			graph.addEdge(&nodes[foundA], &nodes[i]);			
			i++;
			foundA = -1;
			//cout << " Creat EDGE unworkable?" << endl;
		}
		else {				
			graph.addEdge(&nodes[foundA], &nodes[foundB]);		
			//cout << "Existed Links  = "<< nodes[foundA].getName()<<", "<< nodes[foundA].getName() <<" Creat EDGE unworkable?" << endl;
		}
	}
	return true;
}
