#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void dfs(int start, vector<int> graph[], bool check[]) {
    stack<int> s;
    s.push(start);
    cout << start << " ";
    check[start] = true;

    while(!s.empty()) {
        int current_node = s.top();
        s.pop();

        for(int i = 0; i < graph[current_node].size(); i++) {
            int next_node = graph[current_node][i];
            if(!check[next_node]) {
                check[next_node] = true;
                cout << next_node << " ";
                s.push(current_node);
                s.push(next_node);
                break;
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

    for(int i = 1; i <= n; i++) 
        sort(graph[i].begin(), graph[i].end());

    clock_t startt = clock();
    cout << "here is the sequence of searched node : ";
    dfs(start, graph, check);
    clock_t end = clock();
    double performanceTime = (double)(end - startt) / 1000;
    cout << performanceTime << endl;

    return 0;
}