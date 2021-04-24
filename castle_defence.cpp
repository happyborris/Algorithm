#include <iostream>
#include <vector>

using namespace std;

struct arch{
    int y;
    int x;
    arch(int y, int x) : y(y), x(x){};
};

int N, M, D, max_num = 0, cnt = 0;
vector<vector<int>> map;
vector<arch> arch_pos;
int visit[15][15] = {0, };

void solve() {
    vector<arch> cur_pos = arch_pos;
    vector<vector<int>> cur_map = map;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 3; j ++) {
            for(int d = 1; d <= D; d++) {
                bool endFlag = false; // 사격에 성공하면 탐색 중지를 위한 flag.
                // 궁수로부터의 상대 위치 dy, dx
                int dy = -1;
                int dx = -(d-1);

                for(int k = 1; k < 2*d; k++) {
                    // dy, dx로 사격 가능한 index 탐색
                    int ny = cur_pos[j].y + dy;
                    int nx = cur_pos[j].x + dx;

                    // 다음 dy, dx 설정
                    if(k >= d) dy++;
                    else dy--;
                    dx++;

                    // map 범위 밖으로 벗어나는 경우 제외
                    if(nx < 0 || ny < 0 || nx > M) continue;

                    // 적이 있을 경우, 위치 저장 후 탐색 종료
                    if(cur_map[ny][nx] == 1) {
                        visit[ny][nx] = 1;
                        endFlag = true;
                        break;
                    }
                }
                if(endFlag) break;
            }
            cur_pos[j].y--; // 적을 내리는 대신, 궁수들을 한칸 위로 올림.
        }
        // 죽은 적의 수 카운트, visit 초기화
        for(int r = 0; r < N; r++) {
            for(int c = 0; c < M; c++) {
                if(visit[r][c]) {
                    cur_map[r][c] = 0;
                    cnt++;
                    visit[r][c] = 0;
                }
            }
        }
    }
}

int main() {
    cin >> N >> M >> D;

    map = vector<vector<int>> (N+1, vector<int> (M, 0)); // 0으로 초기화
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            int k;
            cin >> k;
            map[i][j] = k;
        }
    }

    for(int i = 0; i < M-2; i++) {
        arch_pos.push_back(arch(N, i));
        for(int j = i+1; j < M-1; j++) {
            arch_pos.push_back(arch(N, j));
            for(int k = j+1; k < M; k++) {
                arch_pos.push_back(arch(N, k));
                solve();
                max_num = max(max_num, cnt);
                cnt = 0;
                arch_pos.pop_back();
            }
            arch_pos.pop_back();
        }
        arch_pos.pop_back();
    }

    cout << max_num;
}