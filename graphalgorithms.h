#ifndef graphalgorithms
#define graphalgorithms
#include "includes.h"

using namespace std;
typedef pair<llint, llint> pllint;
struct Graph {
	vector< vector< pair < llint, llint > > > adjList;
	vector < bool >	visited;
	vector < llint > dist;
	vector < llint > path;
	void init(llint size) {
		this->clean(size);
		adjList.clear();
		adjList.resize(size);
	}
	void clean(llint size) {
		this->dist.clear();
		this->dist.resize(size, INF);
		this->visited.clear();
		this->visited.resize(size, false);
		this->path.clear();
		this->path.resize(size, -1);
	}
	void build(llint e, bool directed=false) {
		while(e--) {
			llint u, v, w;
			cin >> u >> v >> w;
			this->adjList[u].push_back({w, v});
			if(!directed) {
				this->adjList[v].push_back({w, u});
			}
		}
	}
	llint dijkstra(llint source, llint target, bool is_fordFulkerson=false) {
		this->clean(this->adjList.size());
		priority_queue< pllint > pq;
		pq.push({0, source});
		dist[source] = 0;
		visited[source] = true;
		while(!pq.empty()) {
			pllint edge = pq.top();
			pq.pop();
			llint u = edge.se;
			for(auto v : this->adjList[u]) {
				
				if(!this->visited[v.se] && v.fi > 0) {
					llint w = v.fi;
					this->path[v.se] = u;
					this->dist[v.se] = (is_fordFulkerson ? 0 : this->dist[u]) + w;
					this->visited[v.se] = true;
					pq.push(v);
				}
			}
		}
		return dist[target];
	}

	void process(llint source, priority_queue< pair < llint, llint > > &pq) {
		this->visited[source] = true;
		for(auto v : this->adjList[source]) {
			pllint edge = v;
			edge.fi *= -1;
			if(!visited[v.se]) {
				pq.push(edge);
			}
		}
	}
	llint prim(llint source) {
		this->clean(this->adjList.size());
		llint cost = 0;
		priority_queue< pair < llint, llint > > pq;
		this->path.push_back(source);
		process(source, pq);
		while(!pq.empty()) {
			llint u = pq.top().se;
			llint w = pq.top().fi;
			pq.pop();
			if(!visited[u]) {
				this->path.push_back(u);
				process(u, pq);
				cost += (w * -1);
			}
		}
		return cost;
	}

	llint fordFulkerson(llint S, llint T) {
		llint maxFlow = 0;
		this->clean(this->adjList.size());
		while(this->dijkstra(S, T, true) != INF) {
			llint pathFlow = INF;
			for(auto d : this->dist) {
				if(d) {
					pathFlow = min(pathFlow, d);
				}
			}
			maxFlow += pathFlow;
			llint u = T;
			while(u != S) {
				llint v = -1;
				llint qntE = this->adjList.size();
				for(int idx = 0; idx < qntE; idx++) {
					if(this->adjList[this->path[u]][idx].se == u) {
						v = idx;
						break;
					}
				}
				this->adjList[this->path[u]][v].fi -= pathFlow;
				u = this->path[u];
			}		
		}
		return maxFlow;
	}
	void printAdjList() {
		for(llint idx = 0, end = adjList.size(); idx < end; idx += 1) {
			cout << idx << ": ";
			for(auto x : adjList[idx]) {
				cout << " ( " << x.fi << ", " << x.se << " ) -> ";
			}
			cout << endl;
		}
	}

	void printDist(llint source = 0) {
		cout << "source = " << source << endl;
		for(llint idx = 0, end = dist.size(); idx < end; idx += 1) {
			cout << "[ " << idx << " ] ==> " << dist[idx] << endl;
		}
	}

	void printPath() {
		for(auto x : this->path) {
			cout << x << " -> ";
		}
		cout << endl;
	}
};

#endif