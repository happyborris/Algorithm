#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

void dfs(int start, vector<int> graph[], bool check[]) {
    cout << start << " ";
    check[start] = true;

    for(int i = 0; i < graph[start].size(); i++) {
        int next = graph[start][i];
        if(!check[next])
            dfs(next, graph, check);
    }
}

int main(void) {
    int n, m, start;
    cout << "node edge startNode" << endl;
    cin >> n >> m >> start;

    bool check[n+1];
    fill(check, check+n+1, false);

    vector<int> graph[n+1];

    cout << "decide edge" << endl;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end());
    }

    clock_t startt = clock();
    cout << "here is the sequence of searched node : ";
    dfs(start, graph, check);
    clock_t end = clock();
    double performanceTime = (double)(end - startt) / 1000;
    cout << performanceTime << endl;

    return 0;
}