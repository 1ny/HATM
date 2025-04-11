#include <algorithm>
#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

const int MAXN = 20;
const int MAXM = 20;
const int MAXF = 400;
const int MAXP = MAXF * 6;

const int INF = 1e9 + 10;

int SpaceMap[MAXN + 10][MAXN + 10]; // ������ ������ ��鵵
int SpaceMapCellId[MAXN + 10][MAXN + 10]; // ��鵵�� �� ���� �����ϴ� �׷��� ������ ��ȣ�� �����ϴ� �迭
int TimeWall[6][MAXM + 10][MAXM + 10]; // �ð��� ���� �ܸ鵵
int TimeWallCellId[6][MAXM + 10][MAXM + 10]; // �ð��� ���� �ܸ鵵�� �� ���� �����ϴ� �׷��� ������ ��ȣ�� �����ϴ� �迭

// �ð� �̻� ���� ���� ������ ������ ����ü
struct AbnormalTimeEvent {
    // �ð� �̻� ������ �������� ���ȣ, ����ȣ, ����, Ȯ�� �ֱ�, �ð� �̻� ������ ���࿩�θ� ���ʷ� �����մϴ�
    int xpos, ypos, direction, cycle, alive;
};

AbnormalTimeEvent events[MAXF + 10];

// �׷����� ������ ��������Ʈ
vector<vector<int> > Graph;

// Ÿ�Ӹӽſ��� �ش� ��ȣ�� ������ �����ϴµ� �ʿ��� �ּ� �� Ƚ��
int dist[MAXP];

// �׷��� ���� �Լ�
void build_graph(int N, int M) {
    int cnt = 0;

    // �� ���� ���� ������ ��ȣ�� ���ʷ� �ο��մϴ�
    // ��鵵 �� �ð��� ���� �ƴ� �κ��� ������ ��ȸ�� ��,
    // �ܸ鵵�� ���ϴ� ������ �ܸ鵵�� ���� -> ���� -> ���� -> ���� -> ���� ������ ������ ��ȸ�ϸ鼭 ��ȣ�� �ο��մϴ�
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (SpaceMap[i][j] != 3) { // �ð��� ���� �ִ� ���� �ƴ� ��쿡�� ��ȣ�� �ο��մϴ�
                cnt++;
                SpaceMapCellId[i][j] = cnt;
            }
        }
    }

    // �ܸ鵵�� ����, ����, ����, ����, ���� ������ ��ȸ�ϸ� ���� ��ȣ�� �ο��մϴ�
    for (int t = 0; t < 5; t++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                cnt++;
                TimeWallCellId[t][i][j] = cnt;
            }
        }
    }

    // �ο��� ��ȣ�� ������� ������ �׷���
    // ������ ��ȣ�� �����Ǵ� ���� ������ ���� ��ȣ�� ������ ������ �������� �����մϴ�
    // �ִ� 4���� ������ ����� �� �ֽ��ϴ�
    // ��鵵(�ܸ鵵)����, ���������� ������ ��� 0, �Ʒ������� ������ ��� 1, �������� ������ ��� 2, �������� ������ ��� 3�� �ε����� �����մϴ�
    Graph = vector<vector<int> >(cnt + 1, vector<int>(4, -1));

    // ������ �߰��ϴ� �۾��� ���� ����� dx, dy �迭
    // ��, ��, ��, ���� �����Ǵ� ������ ä���� �ֽ��ϴ�
    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { 1, 0, -1, 0 };

    // ��鵵�� ���ϴ� ���� �����Ǵ� ��ȣ�� ���� �ֿ� ���� ������ �߰��մϴ�
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (SpaceMap[i][j] != 3) { // ���� ���� ��ֹ��� ���� ���

                int idx = SpaceMapCellId[i][j];

                // ��, ��, ��, �� ������ ������ ������ Ž���մϴ�
                for (int dd = 0; dd < 4; dd++) {
                    int nx = i + dx[dd];
                    int ny = j + dy[dd];

                    // ������ ����� �Ѿ�ϴ�
                    if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
                    // ���� ��ֹ��� �ִ� ��� �Ѿ�ϴ�
                    if (SpaceMap[nx][ny] == 3) continue;

                    // �׷��� ���� ���, �̾��ݴϴ�
                    Graph[idx][dd] = SpaceMapCellId[nx][ny];
                }
            }
        }
    }

    // �ܸ鵵�� ����, ����, ����, ���ʿ� �ִ� ������ ������ ���
    // �����Ǵ� ��ȣ�� �������� �̾��ݴϴ�
    for (int t = 0; t < 4; t++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {

                int idx = TimeWallCellId[t][i][j];

                // ���� ����ϰ� 4���� Ž��
                for (int dd = 0; dd < 4; dd++) {
                    int nx = i + dx[dd];
                    int ny = j + dy[dd];

                    // �� ������ �Ѿ�� ��� ���
                    if (nx < 0 || nx >= M) continue;

                    // �� ��ȣ�� 0���� �۾��� ���, �ð��������� �ϳ� �տ� �ִ� �ܸ鵵�� ���� ������ ���� ���� �����մϴ�
                    if (ny < 0) {
                        Graph[idx][dd] = TimeWallCellId[(t + 1) % 4][nx][M - 1];
                    }
                    // �� ��ȣ�� M-1���� Ŀ�� ���, �ݽð��������� �ϳ� �տ� �ִ� �ܸ鵵�� ���� ���� ���� ���� �����մϴ�
                    else if (ny >= M) {
                        Graph[idx][dd] = TimeWallCellId[(t + 3) % 4][nx][0];
                    }
                    // �� ���� ��� ��鵵�� ���ó�� �̾��ݴϴ�
                    else {
                        Graph[idx][dd] = TimeWallCellId[t][nx][ny];
                    }

                }
            }

        }
    }

    // ���� �ܸ鵵�� ���ϴ� ���鿡 �����Ǵ� ��ȣ�� ���� �ֿ� ���� ������ �߰��մϴ�
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {

            int idx = TimeWallCellId[4][i][j];

            for (int dd = 0; dd < 4; dd++) {
                int nx = i + dx[dd];
                int ny = j + dy[dd];
                // ������ ��� ��� �Ѿ�ϴ�
                if (nx < 0 || ny < 0 || nx >= M || ny >= M) continue;
                // �׷��� ���� ��� �̾��ݴϴ�
                Graph[idx][dd] = TimeWallCellId[4][nx][ny];
            }
        }
    }

    // ���� �ܸ鵵�� ������ ����, ����, ����, ���� �ܸ鵵�� ���鿡 ����
    // �����Ǵ� ��ȣ�� ������ �մ� ������ �߰��մϴ�

    // ���� �ܸ鵵�� ������ ������ ���
    for (int i = 0; i < M; i++) {
        int idx = TimeWallCellId[4][i][M - 1]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        int idy = TimeWallCellId[0][0][M - 1 - i]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        Graph[idx][0] = idy;
        Graph[idy][3] = idx;
    }
    // ���� �ܸ鵵�� ������ ������ ���
    for (int i = 0; i < M; i++) {
        int idx = TimeWallCellId[4][M - 1][i]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        int idy = TimeWallCellId[1][0][i]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        Graph[idx][1] = idy;
        Graph[idy][3] = idx;
    }
    // ���� �ܸ鵵�� ������ ������ ���
    for (int i = 0; i < M; i++) {
        int idx = TimeWallCellId[4][i][0]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        int idy = TimeWallCellId[2][0][i]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        Graph[idx][2] = idy;
        Graph[idy][3] = idx;
    }
    // ���� �ܸ鵵�� ������ ������ ���
    for (int i = 0; i < M; i++) {
        int idx = TimeWallCellId[4][0][i]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        int idy = TimeWallCellId[3][0][M - 1 - i]; // ������ ���� �ܸ鵵�� ���� ��ȣ
        Graph[idx][3] = idy;
        Graph[idy][3] = idx;
    }

    // ��鵵���� �ð��� ���� �����ϴ� ���� �� ��ȣ, �� ��ȣ
    int timewallStartx = -1;
    int timewallStarty = -1;

    // ��鵵���� �ð��� ���� �����ϴ� ���� ��ġ�� Ž��
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (SpaceMap[i][j] == 3) {
                timewallStartx = i;
                timewallStarty = j;
                break;
            }
        }
        if (timewallStartx != -1) break;
    }

    // ��鵵�� �����ϴ� �ܸ鵵 ���鿡 �����Ǵ� ��ȣ�� ������ �մ� ���� �߰�
    // ���� �ܸ鵵�� ���
    if (timewallStarty + M < N) {
        for (int i = 0; i < M; i++) {
            int idx = TimeWallCellId[0][M - 1][i];
            int idy = SpaceMapCellId[timewallStartx + (M - 1) - i][timewallStarty + M];
            Graph[idx][1] = idy;
            Graph[idy][2] = idx;
        }
    }
    // ���� �ܸ鵵�� ���
    if (timewallStartx + M < N) {
        for (int i = 0; i < M; i++) {
            int idx = TimeWallCellId[1][M - 1][i];
            int idy = SpaceMapCellId[timewallStartx + M][timewallStarty + i];
            Graph[idx][1] = idy;
            Graph[idy][3] = idx;
        }
    }
    // ���� �ܸ鵵�� ���
    if (timewallStarty > 0) {
        for (int i = 0; i < M; i++) {
            int idx = TimeWallCellId[2][M - 1][i];
            int idy = SpaceMapCellId[timewallStartx + i][timewallStarty - 1];
            Graph[idx][1] = idy;
            Graph[idy][0] = idx;
        }
    }
    // ���� �ܸ鵵�� ���
    if (timewallStartx > 0) {
        for (int i = 0; i < M; i++) {
            int idx = TimeWallCellId[3][M - 1][i];
            int idy = SpaceMapCellId[timewallStartx - 1][timewallStarty + (M - 1) - i];
            Graph[idx][1] = idy;
            Graph[idy][1] = idx;
        }
    }

    return;
}

int main() {
    int N, M, E; // ������ ������ �� ���� ����, �ð��� �� �� ���� ����, �ð� �̻� ������ ����

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> E;

    // ������ ��鵵 �Է�
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> SpaceMap[i][j];
        }
    }

    // �ð��� ���� ���� �ܸ鵵 �Է�
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> TimeWall[0][i][j];
        }
    }

    // �ð��� ���� ���� �ܸ鵵 �Է�
    // ������ ���Ǹ� ���ؼ� TimeWall[2][][]�� ���� �ܸ鵵 ���� ����
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> TimeWall[2][i][j];
        }
    }

    // �ð��� ���� ���� �ܸ鵵 �Է�
    // ������ ���Ǹ� ���ؼ� TimeWall[1][][]�� ���� �ܸ鵵 ���� ����
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> TimeWall[1][i][j];
        }
    }

    // �ð��� ���� ���� �ܸ鵵 �Է�
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> TimeWall[3][i][j];
        }
    }

    // �ð��� ���� ���� �ܸ鵵 �Է�
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> TimeWall[4][i][j];
        }
    }

    // �ð� �̻� ���� ���� ���� �Է�
    for (int i = 1; i <= E; i++) {
        cin >> events[i].xpos >> events[i].ypos >> events[i].direction >> events[i].cycle;
        if (events[i].direction == 1) events[i].direction = 2;
        else if (events[i].direction == 2) events[i].direction = 1;

        events[i].alive = 1;
    }

    // ������ ��Ȳ�� �����Ǵ� �׷��� ����
    build_graph(N, M);


    // ������ �׷����� ������ ������
    // N*N - M*M + 5*M*M = N*N + 4*M*M ��
    // -1�� �迭�� ���� �ʱ�ȭ�Ѵ�.
    fill(dist, dist + (N * N) + 4 * (M * M) + 1, -1);

    // ��ֹ��� ��� ������ �� �����Ƿ� �̸� ���� ū ������ �����մϴ�
    // ��鵵�� �ִ� ��ֹ��� ���
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (SpaceMap[i][j] == 3) continue;
            if (SpaceMap[i][j] == 1) {
                int idx = SpaceMapCellId[i][j];
                dist[idx] = INF;
            }
        }
    }

    // ��鵵���� �ð� �̻� ������ �������� ���� �Ұ����ϹǷ� ��ֹ��� ���� ó���մϴ�
    for (int i = 1; i <= E; i++) {
        int x = events[i].xpos;
        int y = events[i].ypos;
        int idx = SpaceMapCellId[x][y];
        dist[idx] = INF;
    }

    // �ܸ鵵 ���� �ִ� ��ֹ��� ��� ���� �Ȱ��� ó���մϴ�
    for (int t = 0; t < 5; t++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                if (TimeWall[t][i][j] == 1) {
                    int idx = TimeWallCellId[t][i][j];
                    dist[idx] = INF;
                }
            }
        }
    }

    // BFS�� ������ ť
    queue<int> que;

    int cell_start = -1;
    int cell_end = -1;

    // Ż�ⱸ ��ġ Ž��
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (SpaceMap[i][j] == 4) {
                cell_end = SpaceMapCellId[i][j];
                break;
            }
        }
    }

    // Ÿ�Ӹӽ��� ������ Ž��
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (TimeWall[4][i][j] == 2) {
                cell_start = TimeWallCellId[4][i][j];
                break;
            }
        }
    }

    que.push(cell_start);
    dist[cell_start] = 0;

    for (int runs = 1;; runs++) {

        // ���� �Ͽ� Ȯ���ϴ� �̻������� ������ ������ �޴� ���� ������Ʈ�մϴ�
        for (int i = 1; i <= E; i++) {
            if (!events[i].alive) continue; // �� �̻� Ȯ������ �ʴ� �̻� �����̸� �Ѿ�ϴ�
            if (runs % events[i].cycle) continue; // ���� �Ͽ� Ȯ������ ������ �Ѿ�ϴ�

            int nx = events[i].xpos, ny = events[i].ypos; // �̻� ������ ������

            // �̻������� ���⿡ ���� ������ �޴� ���� ��ǥ�� ���մϴ�
            if (events[i].direction == 0) {
                ny += (runs / events[i].cycle);
            }
            else if (events[i].direction == 1) {
                nx += (runs / events[i].cycle);
            }
            else if (events[i].direction == 2) {
                ny -= (runs / events[i].cycle);
            }
            else {
                nx -= (runs / events[i].cycle);
            }

            if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
                events[i].alive = 0;
                continue;
            }

            // �̻������� ��ֹ��̳� Ż�ⱸ, �ð��� ���� ���� ���, Ȯ������ �ʽ��ϴ�
            if (SpaceMap[nx][ny]) {
                events[i].alive = 0;
                continue;
            }

            // �����Ǵ� ���� ��ȣ�� ���� Ÿ�Ӹӽ��� ������ �� �����ϴ�
            int idx = SpaceMapCellId[nx][ny];
            dist[idx] = INF;
        }

        // �̹��Ͽ� ���� ������ ������ ��ȣ�� ������ ����
        vector<int> next_cells;

        // �̹��Ͽ� ���� ������ ������ ã���ϴ�
        while (!que.empty()) {
            int idx = que.front();
            que.pop();

            for (int i = 0; i < 4; i++) {
                int idy = Graph[idx][i];
                if (idy == -1) continue; // �ش� �������� �̵������� ���� ���� ��� ����մϴ�
                if (dist[idy] != -1) continue; // �̹� �ּ� ���� ���� ����� ���� ��� ����մϴ�
                dist[idy] = runs;
                next_cells.push_back(idy); // �̹��� ���� ���� ������ ���� ��ȣ�� �߰��մϴ�
            }
        }

        // ���� ���� ������ ������ ������ �����մϴ�
        if (!(int)next_cells.size()) {
            break;
        }

        // ���� ���� ������ ���鿡 �����ϴ� ��ȣ�� ť�� �߰��մϴ�
        for (int i = 0; i < (int)next_cells.size(); i++) {
            que.push(next_cells[i]);
        }

        // Ż�ⱸ�� ���� ���� �ʿ��� �ּ� �ϼ��� ���ߴٸ�, �����մϴ�.
        if (dist[cell_end] != -1) {
            break;
        }
    }

    // ������ ����մϴ�.
    // �Ұ����ϸ� -1�� ��µ˴ϴ�
    cout << dist[cell_end] << "\n";

    return 0;
}
