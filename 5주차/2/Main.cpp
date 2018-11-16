#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <functional>
#include <set>
#include <string>

using namespace std;

#define DEBUG 0
#define PRICE(i,j,k) ((((i*j + j*k + k*i)^(17*i + 23*j + 29*k)) % 99) + 1)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n, h, q, x1, x2, y1, y2, z1, z2, current;

    cin >> m >> n >> h >> q;

    uint32_t** Q = new uint32_t*[q];
    uint32_t*** tomato = new uint32_t**[h+1];

    for(int i = 0; i < q; i++){
        Q[i] = new uint32_t[6];
        for(int j = 0; j < 6; j++){
            cin >> Q[i][j];
        }
    }

    for(int i = 0; i <= h; i++){
        tomato[i] = new uint32_t*[n+1];
        for(int j = 0; j <= n; j++){
            tomato[i][j] = new uint32_t[m+1];
            for(int k = 0; k <= m; k++){
                if(i == 0 || j  == 0 || k == 0) continue;
                current = PRICE(i,j,k);
                tomato[i][j][k] = current + tomato[i-1][j][k] + tomato[i][j-1][k] + tomato[i][j][k-1];
                tomato[i][j][k] -= tomato[i][j-1][k-1] + tomato[i-1][j][k-1] + tomato[i-1][j-1][k]; // 중복 뺌
                tomato[i][j][k] += tomato[i-1][j-1][k-1]; // 중복해서 빼진 것 다시 더함
            }
        }
    }

    uint64_t profit, bottom;
    uint32_t* o;
    for(int i = 0; i < q; i++){
        o = Q[i];
        profit = tomato[o[5]][o[4]][o[3]];
        profit += tomato[o[5]][o[1] - 1][o[0] - 1]; // 중복해서 빼'질' 것 미리 더함 -> 오버플로우 방지
        profit -= tomato[o[5]][o[4]][o[0] - 1]; // 중복을 뺌
        profit -= tomato[o[5]][o[1] - 1][o[3]];
        bottom = tomato[o[2] - 1][o[4]][o[3]]; // 아래층에도 똑같은 것 적용
        bottom += tomato[o[2] - 1][o[1] - 1][o[0] - 1]; 
        bottom -= tomato[o[2] - 1][o[4]][o[0] - 1];
        bottom -= tomato[o[2] - 1][o[1] - 1][o[3]];
    
        profit -= bottom; 

        cout << profit << "\n";
    }
}
