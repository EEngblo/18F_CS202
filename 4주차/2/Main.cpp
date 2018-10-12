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

#define m 987654321
#define sum(X, Y) (((X % m) + (Y % m)) % m)
#define sub(X, Y) (((X % m) - (Y % m) + m) % m)
#define mul(X, Y) (((uint64_t) (X % m) * (Y % m)) % m)
#define div(X, Y) (((X % m) / (Y % m)) % m)

using namespace std;

uint32_t pow(uint32_t n, uint32_t k){
    if (k == 0) return 1;
    if (k == 1) return n % m;
    uint32_t a = pow(n, k >> 1);
    if (k & 1){
        return mul(n, mul(a, a));
    }
    return mul(a, a);
}

int main() {
	uint32_t n, answer, cnt = 0, sum = 0, minA = UINT32_MAX, maxA = 0;
    int i, j;
    cin >> n;
    uint32_t* A = (uint32_t *) malloc(n*sizeof(uint32_t));

    for(i = 0 ; i < n; i++){
        cin >> A[i];
        cnt++;
        sum += A[i];
        minA = minA > A[i] ? A[i] : minA;
        maxA = maxA < A[i] ? A[i] : maxA;
    }

    // 각 구역 내에서의 공사 순서에 대한 경우의 수
    answer = pow(2, sum - cnt);
    sum = sum - minA + 2;

    if (n == 1){
        cout << answer;
        return 0;
    }

    // 이제부터 줄 서기 문제로 다룸
    // 첫 구역의 공사 순서대로 줄을 서 있다고 가정 후,
    // 다음 구역의 공사 순서에 따라서 첫 구역의 공사 순서 사이의 빈 칸에 섬
    uint32_t** B = new uint32_t*[maxA + 1];

    // i 명의 사람을 1곳에 배치하는 경우의 수
    for(i = 0; i <= maxA; i++){
        B[i] = new uint32_t[sum];
        B[i][1] = 1;
    }

    // 1명의 사람을 i곳에 배치하는 경우의 수
    for(j = 1; j < sum; j++){
        B[1][j] = j;
    }

    // i명의 사람을 j곳에 배치하는 경우의 수
    for(i = 2; i <= maxA; i++){
        for(j = 2; j < sum; j++){
            B[i][j] = sum(B[i-1][j], B[i][j-1]);
        }
    }

    // 각 경우의 수의 곱
    sum = A[0] + 1;
    for(i = 1; i < cnt; i++){
        answer = mul(answer, B[A[i]][sum]);
        sum += A[i];
    }    

    cout << answer;
}
