#ifndef graphalgorithms
#define graphalgorithms
#include "includes.h"

using namespace std;
typedef pair<llint, llint> pllint;
struct Graph {
	vector< vector< pair < llint, llint > > > adjList;
	vector < bool >	visited;
	vector < llint > dist, path, pairU, pairV;
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
		this->pairU.clear();
		this->pairU.resize(size, 0);
		this->pairV.clear();
		this->pairV.resize(size, 0);
	}
	void build(llint e, bool has_weight, bool directed=false) {
		while(e--) {
			llint u, v, w;
			cin >> u >> v;
			if(has_weight) {
				cin >> w;
			} else {
				w = 1;
			}
			this->adjList[u].push_back({w, v});
			if(!directed) {
				this->adjList[v].push_back({w, u});
			}
		}
	}
	llint dijkstra(llint source, llint target, bool is_fordFulkerson=false) {
		this->clean(this->adjList.size());
		this->path.resize(this->adjList.size(), -1);
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
		this->path.resize(this->adjList.size(), -1);
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

	bool dfs(llint source) {
		if(source == 0) {
			return true;
		}
		for(auto edge : this->adjList[source]) {
			llint v = edge.se;
			if(this->dist[this->pairV[v]] == dist[source] + 1) {
				pairV[v] = source;
				pairU[source] = v;
				return true;
			}
		}
		dist[source] = INF;
		return false;
	}

	bool bfs() {
		queue<llint> q;
		llint m = (llint)adjList.size();
		for(llint u = 1; u < m; u++) {
			if(pairU[u] == 0) {
				dist[u] = 0;
				q.push(u);
			} else {
				dist[u] = INF;
			}
		}
		dist[0] = INF;
		while(!q.empty()) {
			llint u = q.front();
			q.pop();
			if(dist[u] >= dist[0]) {
				continue;
			}
			for(llint idx = 0; idx < (llint)adjList[u].size(); idx++) {
				llint v  = adjList[u][idx].se;
				if(dist[pairV[v]] == INF) {
					dist[pairV[v]] = dist[u] + 1;
					q.push(pairV[v]);
				}
			}
		}
		return (dist[0] != INF);
	}

	llint hopcroftKarp() {
		this->clean(this->adjList.size());
		llint result = 0;
		llint m = this->adjList.size();
		while(this->bfs()) {
			for(int u = 1; u < m; u++) {
				result += ((pairU[u] == 0 && dfs(u)) ? 1 : 0);
			}
		}
		return result;
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
	void printPairs() {
		cout << "PairU" << endl;
		for(llint idx = 1; idx < pairU.size(); idx += 1) {
			cout << idx << ": " << pairU[idx] << endl;
		}
		cout << "PairV: " << endl;
		for(llint idx = 1; idx < pairV.size(); idx += 1) {
			cout << idx << ": " << pairV[idx] << endl;
		}
	}
};

#endif