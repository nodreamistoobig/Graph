#include <iostream>
#include <set>
#include "Nodes.h"

using namespace std;

void Graph::addNode(Node* node) {
	nodes.insert(node);
}

void Graph::removeNode(Node* node) {
	nodes.erase(node);
	for (set<Node*>::iterator it = nodes.begin();it != nodes.end(); it++)
		(*it)->removeNeighbour(node);
}

void Graph::addEdge(Node* begin, Node* end) {
	if (nodes.find(begin) == nodes.end())
		return;
	if (nodes.find(end) == nodes.end())
		return;
	begin->addNeighbour(end);
	end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
	begin->removeNeighbour(end);
	end->removeNeighbour(begin);
}

void Node::addNeighbour(Node* neighbour) {
	neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
	//delete neighbour;
}
