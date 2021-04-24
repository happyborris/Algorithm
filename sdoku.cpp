#include <iostream>

using namespace std;

int board[9][9] = {0, };
bool row[9][10] = {false, };
bool col[9][10] = {false, };
bool square[9][10] = {false, };

void ansCheck(int ans[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(!ans[i][j]) return;
        }
    }
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    exit(0);
}

int getSquareIndex(int r, int c) {
    return (r / 3) * 3 + c / 3;
}

void backtrack(int before[9][9], int r, int c, int value) {
    int cur_board[9][9] = {0, };
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cur_board[i][j] = before[i][j];
        }
    }
    cur_board[r][c] = value;
    ansCheck(cur_board); // 값 넣고 정답 검사.
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(!cur_board[i][j]) {
                int squareIndex = getSquareIndex(i, j);
                for(int k = 1; k < 10; k++) {
                    if(!row[i][k] && !col[j][k] && !square[squareIndex][k]) {
                        row[i][k] = true;
                        col[j][k] = true;
                        square[getSquareIndex(i, j)][k] = true;
                        backtrack(cur_board, i, j, k);
                        row[i][k] = false;
                        col[j][k] = false;
                        square[getSquareIndex(i, j)][k] = false;
                    }
                }
                return; // 모든 숫자를 대입해도 유망하지 않으면 버림.
            }
        }
    }
}

int main() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cin >> board[i][j];
            // row, col, square 값 넣기
            if(board[i][j]) {
                row[i][board[i][j]] = true;
                col[j][board[i][j]] = true;
                int squareIndex = getSquareIndex(i, j);
                square[squareIndex][board[i][j]] = true;
            }
        }
    }
    ansCheck(board); // input이 정답일 경우 바로 출력.
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(!board[i][j]) {
                int squareIndex = getSquareIndex(i, j);
                for(int k = 1; k < 10; k++) {
                    if(!row[i][k] && !col[j][k] && !square[squareIndex][k]){
                        row[i][k] = true;
                        col[j][k] = true;
                        square[getSquareIndex(i, j)][k] = true;
                        backtrack(board, i, j, k);
                        row[i][k] = false;
                        col[j][k] = false;
                        square[getSquareIndex(i, j)][k] = false;
                    }
                }
                // input은 항상 정답이 있는 것으로 들어오기 때문에, 초기 상태는 항상 유망하므로 return 생략.
            }
        }
    }

    return 0;
}