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

// n C r = (n-1) C (r-1) + (n-1) C r // 2차원 배열 이용해서 DP
// binom[n][r] = binom[n-1][r-1] + binom[n-1][r]
uint32_t binom(uint32_t n, uint32_t r){
    uint32_t** binom = (uint32_t **) calloc((n+1)*(r+1), sizeof(uint32_t));
    for (int i = 0; i <= r; i++) binom[0][i] = 0;
    for (int i = 1; i <= n; i++){
        binom[i][0] = i;
        for (int j = 1; j <= r; j++){
            binom[i][j] = sum(binom[i-1][j], binom[i-1][j-1]);
        }
    }
    return binom[n][r];
}


// use mtrx
uint32_t* matmul(uint32_t* A, uint32_t* B, uint32_t size){
    uint32_t* C = (uint32_t *) calloc(size*size, sizeof(uint32_t));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){
                *(C + size*i + j) = sum(mul(*(A + size*i + k), *(B + size*k + j)), *(C + size*i + j));
            }
        }
    }
    return C;
}

uint32_t* matsum(uint32_t* A, uint32_t* B, uint32_t size){
    uint32_t* C = (uint32_t *) malloc(size*size*sizeof(uint32_t));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //cout << *(A + size*i + j) << " " << *(B + size*i + j) << endl;
            *(C + size*i + j) = sum(*(A + size*i + j), *(B + size*i + j));
        }
    }
    return C;
}

uint32_t pow(uint32_t n, uint64_t k){
    if (k == 1) return n % m;
    uint32_t a = pow(n, k >> 1);
    if (k & 1){
        return mul(n, mul(a, a));
    }
    return mul(a, a);
}

uint32_t* matpow(uint32_t* n, uint64_t k, uint32_t size){
    if (k == 1) {
        for(int i = 0; i < size ; i++){
            for(int j = 0; j < size; j++){
                *(n + size*i + j) %= m;
            }
        }
        return n;
    }
    uint32_t* a = matpow(n, k >> 1, size);
    if (k & 1){
        return matmul(n, matmul(a, a, size), size);
    }
    return matmul(a, a, size);
}

uint32_t powsum(uint32_t n, uint64_t k){
    uint32_t answer;
    if (k == 0) answer = 1;
    else if (k == 1) answer = n + 1;
    else if (k & 1) {
        uint32_t a = sum(1, pow(n, (k+1) >> 1));
        uint32_t b = powsum(n, (uint64_t) k>> 1);
        answer = mul(a, b);
    }
    else {
        uint32_t a = pow(n, k);
        uint32_t b = powsum(n, (k -1));
        answer = sum(a, b);
    }
    return answer;
}

uint32_t* powsum(uint32_t* n, uint64_t k, uint32_t size){
    uint32_t* C = (uint32_t *) malloc(size*size*sizeof(uint32_t));
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            *(C + size*i + j) = 
                i == j ? 1
                        : 0;
        }
    }
    if (k == 0) {
        return C;
    }
    else if (k == 1) {
        uint32_t* answer = matsum(C, n, size);
        free(C);
        return answer;
    }
    else if (k & 1) {
        uint32_t* a = matsum(C, matpow(n, (k+1) >> 1, size), size);
        uint32_t* b = powsum(n, (uint64_t) k>> 1, size);
        free(C);
        C = matmul(a, b, size);
    }
    else {
        uint32_t* a = matpow(n, k, size);
        uint32_t* b = powsum(n, (k -1), size);
        free(C);
        C = matsum(a, b, size);
    }
    return C;
}

int main() {
	uint32_t n;
    uint64_t k;

    cin >> n >> k;
    uint32_t* A = (uint32_t *) malloc(n*n*sizeof(uint32_t));

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> *(A + n*i + j);
        }
    }

    A = powsum(A, k, n);
    //A = matmul(A, A, n);

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << *(A + n*i + j) << " ";
        }
        cout << endl;
    }
}
