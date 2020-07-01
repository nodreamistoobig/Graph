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
	while (graph1.begin()!= graph1.end()) //пока есть несоединенные в отдельные графы вершины, продолжаем их искать 
		breadthSearch(graph1); //метод поиска в ширину
	graph2 = graph;
	cout << "depthSearch" << endl;
	while (graph2.begin() != graph2.end()) 
		depthSearch(graph2); 	//метод поиска в глубину
}

void breadthSearch(Graph& graph) {
	queue<Node*> q; 			//создаем очередь из вершин, которые нужно посетить
	q.push(*graph.begin());			
	set<Node*> visited;			//создаем набор уже посещенных вершин

	while (!q.empty()) {

		Node* next = q.front(); q.pop(); //берем первый элемент на рассмотрение и удаляем его из очереди 
		visited.insert(next);		//помечаем его, как посещенный
		for (node_iterator it = next->neighbours.begin(); it != next->neighbours.end(); it++) //ищем всех соседей этого элемента
			if (visited.find(*it) == visited.end())  //если мы ещё не посещали этого соседа
				q.push(*it);			//помещаем его в очередь
	}
	for (node_iterator v = visited.begin(); v != visited.end(); v++) {
		for (int n = 0; n < 50; n++) {
			if (nodes[n].getName() == (*v)->getName()) {
				graph.removeNode(&nodes[n]);		//удаляем из графа все посещенные вершины
			}
		}
		cout << (*v)->getName() << " ";				//выводим вершины, которые вошли в единый граф
	}
	cout << endl;
}

void depthSearch(Graph& graph) {
	set<Node*> visited;
	
	Node* next = *graph.begin(); 	
	visited.insert(next);		//вносим в посещенные вершины первый узел графа
	for (node_iterator it = next->neighbours.begin(); it != next->neighbours.end(); it++) {
		visitInsert(it, visited);			//проходимся по всем его соседям и вносим их в посещенные вершины
	}

	for (node_iterator v = visited.begin(); v != visited.end(); v++) {
		cout << (*v)->getName() << " ";			//выводим вершины, которые вошли в единый граф
		for (int n = 0; n < 50; n++) {
			if (nodes[n].getName() == (*v)->getName()) {
				graph.removeNode(&nodes[n]);		//удаляем из графа все посещенные вершины
			}
		}
	}
	cout << endl;
}

void visitInsert(node_iterator it, set<Node*>& visited) {
	visited.insert(*it);			//вставляем в посещенные вершины первого соседа
	for (node_iterator n = (*it)->neighbours.begin(); n != (*it)->neighbours.end(); n++) { //перебираем всех его соседей
		int vis = 0;
		for (node_iterator v = visited.begin(); v != visited.end(); v++) 
			if ((*n)->getName() == (*v)->getName()) 
				vis++;				//проверяем, посещали ли мы уже эту вершину (соседей этого соседа)
		if (vis == 0)
			visitInsert(n, visited);		//если нет, проверяем всех его соседей
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
		in >> name_a >> name_b;

		int foundA=-1, foundB=-1; 

		for (int n = 0; n < 50; n++) {
			if (nodes[n].getName() == name_a) 
				foundA = n;			//если  вершина с таким именем существует запоминаем её
			else if (nodes[n].getName() == name_b) 
				foundB = n;
		}

		
		if (foundA==-1) {					//если первая вершина еще не существует
			nodes[i].setName(name_a); 			//создаём её
			graph.addNode(&nodes[i]);			//дбавляем в граф
			i++;	
			if (foundB==-1)					//если вторая вершина еще не существует
			{
				nodes[i].setName(name_b);		//создаем её
				graph.addNode(&nodes[i]);
				graph.addEdge(&nodes[i-1], &nodes[i]);	//соединяем вершины
				i++;
			}
			else {							//если вторая вершина существует, а первая - нет					
				graph.addEdge(&nodes[i - 1], &nodes[foundB]);	//соединяем вершины, используя ту, что запомнили ранее
				foundB = -1;
			}
		}
		else if (foundB==-1)						//то же самое, если первая существует, а вторая - нет
		{
			nodes[i].setName(name_b);	
			graph.addNode(&nodes[i]);
			graph.addEdge(&nodes[foundA], &nodes[i]);			
			i++;
			foundA = -1;
		}
		else 								//если обе существуют
			graph.addEdge(&nodes[foundA], &nodes[foundB]);		
	}
	return true;
}
