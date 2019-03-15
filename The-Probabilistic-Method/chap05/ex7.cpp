#include <bits/stdc++.h>

using namespace std;

const int m = 10000;
const int n = 10 * m;

bool x[n + 1];
int sigma[31][n + 1];
int clause[31][11][m];

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

void init() {
    srand(time(0));
    for (int i = 1; i <= 30; ++i) {
        for (int j = 1; j <= n; ++j)
            sigma[i][j] = j;
        // Knuth Shuffle
        for (int j = 1; j <= n; ++j)
            swap(sigma[i][j], sigma[i][j + rand() % (n + 1 - j)]);
    }
    // initialize negation
    for (int i = 1; i <= 30; ++i)
        for (int k = 1; k <= 10; ++k)
            for (int j = 0; j < m; ++j)
                clause[i][k][j] = rand() & 1;
    // inital assignment
    for (int i = 1; i <= n; ++i)
        x[i] = rand() & 1;
}

pair<int, int> check() {
    for (int i = 1; i <= 30; ++i)
        for (int j = 0; j < m; ++j) {
            bool f = 0;
            for (int k = 1; k <= 10; ++k)
                f |= x[sigma[i][10 * j + k]] ^ clause[i][k][j];
            if (!f)
                return make_pair(i, j);
        }
    return make_pair(0, 0);
}

int main() {
    init();

    int cnt = 0;
    pair<int, int> badclause;
    while ((badclause = check()) != make_pair(0, 0)) {
        int i = badclause.first;
        int t = badclause.second;
        for (int l = 1; l <= 10; ++l)
            x[sigma[i][10 * t + l]] = rand() & 1;
        cnt += 1;
    }

    printf("Solution found in %d round\n", cnt);
}
