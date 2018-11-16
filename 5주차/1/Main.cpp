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
#define m 987654321
#define sum(X, Y) (X + Y)
#define add(X, Y) (((X % m) + (Y % m)) % m)
#define sub(X, Y) (((X % m) - (Y % m) + m) % m)
#define mul(X, Y) (((uint64_t) (X % m) * (Y % m)) % m)
#define div(X, Y) (((X % m) / (Y % m)) % m)

uint64_t pow(uint64_t n, uint32_t k){
    if (k == 0) return 1;
    if (k == 1) return n % m;
    uint64_t a = pow(n, k >> 1);
    if (k & 1){
        return mul(n, mul(a, a));
    }
    return mul(a, a);
}
uint32_t pow2(uint64_t c, uint32_t k){
    uint64_t answer = c % m;

    for(int i = 1; i < k; i++){
        answer *= c % m;
        answer %= m;
    }
    return answer;
}

int main() {
    int n, j;
	uint32_t minA = UINT32_MAX, maxA = 0;
    uint64_t c;
    uint64_t cnt = 0;
    bool emptyrow = true;
    cin >> n;

    vector<uint8_t> I;

    for(int i = 0; i < n; i++){
        cin >> c;
        I.push_back(c);
    }

    cin >> c;

    sort(I.begin(), I.end());

    uint32_t** A = new uint32_t*[n+1];
    uint32_t** B = new uint32_t*[n+1];
    uint32_t yMax = c > I[n-1] ? c : I[n-1];

    for(int i = 0; i <= n ; i++){
        A[i] = new uint32_t[yMax];
        B[i] = new uint32_t[yMax];
    }
    
    A[0][0] = 1;
    for(int i = 0; i < n; i++){
        uint32_t current = I[i];
        for(int j = c-1; j >= current; j--){
            A[1][j] = add(A[1][j], A[0][j-current]);
            A[0][j] = add(A[0][j], A[1][j-current]);
        }
    }

    uint64_t v = pow2(c, n);

    for(int k = 1; k < c; k++){
        uint32_t tv = mul(A[0][k], pow2(c-k, n));
        v = add(v, tv);
        tv = mul(A[1][k], pow2(c-k, n));
        v = sub(v, tv);
    }

    cout << v;
}
