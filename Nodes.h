#include <iostream>
#include <set>

using namespace std;


class Node {
	int name;
	
	void addNeighbour(Node* neighbour);
	void removeNeighbour(Node* neighbour);
public:
	set<Node*> neighbours;
	Node(const int& aname) : name(aname) {}
	Node() : name(-1) {}
	const int& getName() const { return name; }
	void setName(int aname)  { name = aname; }
	//node_iterator nb_begin() const {return neighbours.begin(); }
	//node_iterator nb_end() const {return neighbours.end(); }
	friend class Graph;
};

typedef set<Node*>::const_iterator node_iterator;

class Graph {
	set<Node*> nodes;
public:
	void addNode(Node* node);
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end);
	void removeEdge(Node* begin, Node* end);
	node_iterator begin() const { return nodes.begin();}
	node_iterator end() const { return nodes.end(); }
};

