#include <iostream>

using namespace std;

int N, map[16][16], cnt = 0;

pair<int, int> moveDir[3] = {{0, 1}, {1, 0}, {1, 1}};

void print_map() {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void dfs(int r, int c, int dir) {
    if(r == N-1 && c == N-1) {
        cnt++;
        return;
    }

    for(int i = 0; i < 3; i++) {
        if((i == 0 && dir == 1) || (i == 1 && dir == 0)) continue;
        int next_r = r + moveDir[i].first;
        int next_c = c + moveDir[i].second;
        if(next_r >= N || next_c >= N || map[next_r][next_c]) continue;
        if(i == 2 && (map[r][next_c] || map[next_r][c])) continue;
        dfs(next_r, next_c, i);
    }
}

int main() {
    cin >> N;
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            map[i][j] = 1;
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    dfs(0, 1, 0);
    cout << cnt;
    return 0;
}