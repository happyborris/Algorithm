#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void bfs(int start, vector<int> graph[], bool check[]) {
    queue<int> q;
    q.push(start);
    check[start] = true;
    cout << start << " ";

    while(!q.empty()) {
        int current_node = q.front();
        q.pop();

        for(int i = 0; i < graph[current_node].size(); i++) {
            int next_node = graph[current_node][i];
            if(!check[next_node]) {
                check[next_node] = true;
                cout << next_node << " ";
                q.push(next_node);
            }
        }
    }
}

int main(void) {
    int n, m, start;
    cout << "node edge startNodeNum" << endl;
    cin >> n >> m >> start;

    bool check[n+1];
    fill(check, check+n+1, false);

    vector<int> graph[n+1];

    cout << "make edge" << endl;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 0; i <= n; i++) 
        sort(graph[i].begin(), graph[i].end());

    cout << "here is the sequence of searched node : ";
    bfs(start, graph, check);

    return 0;
}