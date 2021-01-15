#include "graphalgorithms.h"

using namespace std;

int main(int argc, char const *argv[]) {
	Graph g;
	llint v, e;
	bool error = false;
	if(argc < 2) {
		error = true;
	}
	if(!error && !strcmp(argv[1], "fordfulkerson")) {
		cin >> v;
		cin >> e;
		g.init(v);
		g.build(e, true, true);
		cout << "Lista de adjacencia do grafo criado: " << endl;
		g.printAdjList();
		cout << "Fluxo máximo para o grafo: " << g.fordFulkerson(0, g.adjList.size() - 1) << endl;	
	} else if(!error && !strcmp(argv[1], "dijkstra")) {
		cin >> v;
		cin >> e;
		g.init(v);
		g.build(e, true, true);
		cout << "Lista de adjacencia do grafo criado: " << endl;
		g.printAdjList();
		cout << "Custo do caminho mínimo: " << g.dijkstra(0, g.adjList.size() - 1) << endl;
		cout << "Distancias de " << 0 << " a " << (g.adjList.size() - 1) << endl;
		g.printDist();
	} else if(!error && !strcmp(argv[1], "prim")) {
		cin >> v;
		cin >> e;
		g.init(v);
		g.build(e, true, true);
		cout << "Lista de adjacencia do grafo criado: " << endl;
		g.printAdjList();
		cout << "Custo da arvore geradora minima a partir de 0: " << g.prim(0) << endl;
		g.printPath();
	} else if(!error && !strcmp(argv[1], "hopcroftKarp")) {
		cin >> v >> e;
		g.init(v + 1);
		g.build(e, false, true);
		cout << "Tamanho do maior emparelhamento: " << g.hopcroftKarp() << endl;
	} else if(!error && !strcmp(argv[1], "help")) {
		cout << "Para compilar execute: " << endl << "make" << endl;
		cout << "Para executar execute: " << endl << "./exec.out [algoritmo desejado] < [entrada válida para o algoritmo]" << endl;
		cout << "Os algoritmos desejados podem ser: " << endl << "  - fordfulkerson" << endl << "  - dijkstra" << endl << "  - prim" << endl << "  - hopcroftKarp" << endl;
	} else {
		cout << "argumentos inválidos!!" << endl << "para ajuda execute: ./exec.out help" << endl;
	}
	
	return 0;
}