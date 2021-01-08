#include "graphalgorithms.h"

using namespace std;

int main(int argc, char const *argv[]) {
	Graph g;
	int v, e;
	cin >> v;
	cin >> e;
	g.init(v);
	g.build(e, true);
	cout << "Lista de adjacencia do grafo criado: " << endl;
	g.printAdjList();

	cout << g.dijkstra(0, 3) << endl;
	g.printDist();
	// cout << g.prim(0) << endl;
	g.printPath();
	cout << "Fluxo máximo para o grafo: " << g.fordFulkerson(0, 3) << endl;
	return 0;
}