#include <iostream>

using namespace std;

int N, map[16][16] = {1, }, cnt = 0;

enum status {horizon, vertical, diagonal};

struct pipe {
    pair<int, int> left = {0, 0};
    pair<int, int> right = {0, 1};
    status stat = horizon;
    pipe(pair<int, int> left, pair<int, int> right, status st) : left(left), right(right), stat(st) {};
};

pipe move_right(pipe cur_pipe) {
    cur_pipe.left.second++;
    cur_pipe.right.second++;
    cur_pipe.stat = horizon;
    return cur_pipe;
}

pipe move_down(pipe cur_pipe) {
    cur_pipe.left.first++;
    cur_pipe.right.first++;
    cur_pipe.stat = vertical;
    return cur_pipe;
}

pipe move_diagonal(pipe cur_pipe) {
    cur_pipe.left.first++;
    cur_pipe.right.first++;
    cur_pipe.left.second++;
    cur_pipe.right.second++;
    cur_pipe.stat = diagonal;
    return cur_pipe;
}

void dfs(pipe cur_pipe) {
    if(cur_pipe.right.first == N-1 && cur_pipe.right.second == N-1){
        cnt++;
        return;
    }
    switch(cur_pipe.stat) {
        case horizon :
            if(cur_pipe.right.second+1 < N && !map[cur_pipe.right.first][cur_pipe.right.second+1]) dfs(move_right(cur_pipe));
            if(cur_pipe.right.second+1 < N && cur_pipe.right.first+1 < N
            && !map[cur_pipe.right.first][cur_pipe.right.second+1]
            &&!map[cur_pipe.right.first+1][cur_pipe.right.second+1]
            &&!map[cur_pipe.right.first+1][cur_pipe.right.second]) dfs(move_diagonal(cur_pipe));
            break;
        case vertical :
            if(cur_pipe.right.first+1 < N && !map[cur_pipe.right.first+1][cur_pipe.right.second]) dfs(move_down(cur_pipe));
            if(cur_pipe.right.first+1 < N && cur_pipe.right.second+1 < N
            &&!map[cur_pipe.right.first+1][cur_pipe.right.second]
            &&!map[cur_pipe.right.first+1][cur_pipe.right.second+1]
            &&!map[cur_pipe.right.first][cur_pipe.right.second+1]) dfs(move_diagonal(cur_pipe));
            break;
        default :
            if(cur_pipe.right.second+1 < N && !map[cur_pipe.right.first][cur_pipe.right.second+1]) dfs(move_right(cur_pipe));
            if(cur_pipe.right.first+1 < N && !map[cur_pipe.right.first+1][cur_pipe.right.second]) dfs(move_down(cur_pipe));
            if(cur_pipe.right.first+1 < N && cur_pipe.right.second+1 < N
            &&!map[cur_pipe.right.first][cur_pipe.right.second+1]
            &&!map[cur_pipe.right.first+1][cur_pipe.right.second+1]
            &&!map[cur_pipe.right.first+1][cur_pipe.right.second]) dfs(move_diagonal(cur_pipe));
            break;
    }
}

int main() {
    cin >> N;
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            map[i][j] = 1;
        }
    }
    pipe start_pipe = pipe({0,0}, {0,1}, horizon);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    dfs(start_pipe);
    cout << cnt;
}