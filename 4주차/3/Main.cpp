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

#define DEBUG 0
#define m 987654321
#define sum(X, Y) (X + Y)
#define add(X, Y) (((X % m) + (Y % m)) % m)
#define sub(X, Y) (((X % m) - (Y % m) + m) % m)
#define mul(X, Y) (((uint64_t) (X % m) * (Y % m)) % m)
#define div(X, Y) (((X % m) / (Y % m)) % m)

using namespace std;

uint32_t pow2(uint64_t c, uint32_t k){
    uint64_t answer = c % m;

    for(int i = 1; i < k; i++){
        answer *= c % m;
        answer %= m;
    }
    return answer;
}

uint64_t pow(uint64_t n, uint32_t k){
    if (k == 0) return 1;
    if (k == 1) return n % m;
    uint64_t a = pow(n, k >> 1);
    if (k & 1){
        return mul(n, mul(a, a));
    }
    return mul(a, a);
}

int main() {
    int n;
	uint32_t minA = UINT32_MAX, maxA = 0;
    uint64_t c;
    uint64_t cnt = 0;
    cin >> n;

    uint32_t* a = new uint32_t[n];

    for(int i = 0; i < n; i++){
        cin >> a[i];
        minA = minA > a[i] ? a[i] : minA;
        maxA = maxA < a[i] ? a[i] : maxA;
    }

    cin >> c;

    if (c <= minA){
        cout << pow(c, n) << endl;
        return 0;
    }

    uint64_t v = pow2(c, n);
    if (DEBUG) cout << "v: " << v << endl;
    uint64_t tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15, tmp16, tmp17, tmp18, tmp19, tmp20, tmp21;
    uint64_t tmpsum = 0;

    if (n >= 2){
        for(int i = 0; i < n; i++){
            if (c > a[i]){
                cnt++;
                tmpsum = add(tmpsum, pow(sub(c, a[i]), n));
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=2 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 3){
        for(int i = 0; i < n - 1; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;
                cnt++;
                tmpsum = add(tmpsum, pow(sub(c, tmp1), n));
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << "n=3 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 4){
        for(int i = 0; i < n - 2; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 1; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;
                    cnt++;
                    tmpsum = add(tmpsum, pow(sub(c, tmp2), n));
                }
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=4 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 5){
        for(int i = 0; i < n - 3; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 2; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 1; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        cnt++;
                        tmpsum = add(tmpsum, pow(sub(c, tmp3), n));
                    }
                }
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << "n=5 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 6){
        for(int i = 0; i < n - 4; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 3; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 2; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n - 1; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        
                        for(int a6 = a5 + 1; a6 < n; a6++){
                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;
                            cnt++;
                            tmpsum = add(tmpsum, pow(sub(c, tmp4), n));
                        }
                    }
                }
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=6 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 7){
        for(int i = 0; i < n - 5; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 4; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 3; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n - 2; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        
                        for(int a6 = a5 + 1; a6 < n - 1; a6++){
                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                            for(int a7 = a6 + 1; a7 < n; a7++){
                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;
                                cnt++;
                                tmpsum = add(tmpsum, pow(sub(c, tmp5), n));
                            }
                        }
                    }
                }
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << "n=7 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 8){
        for(int i = 0; i < n - 6; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 5; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 4; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n - 3; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        
                        for(int a6 = a5 + 1; a6 < n - 2; a6++){
                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                            for(int a7 = a6 + 1; a7 < n - 1; a7++){
                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                for(int a8 = a7 + 1; a8 < n; a8++){
                                    if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;
                                    cnt++;
                                    tmpsum = add(tmpsum, pow(sub(c, tmp6), n));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=8 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 9){
        for(int i = 0; i < n - 7; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 6; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 5; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n - 4; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        
                        for(int a6 = a5 + 1; a6 < n - 3; a6++){
                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                            for(int a7 = a6 + 1; a7 < n - 2; a7++){
                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                for(int a8 = a7 + 1; a8 < n - 1; a8++){
                                    if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                    for(int a9 = a8 + 1; a9 < n; a9++){
                                        if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                        cnt++;
                                        tmpsum = add(tmpsum, pow(sub(c, tmp7), n));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << "n=9 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 10){
        for(int i = 0; i < n - 8; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 7; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 6; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n - 5; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        
                        for(int a6 = a5 + 1; a6 < n - 4; a6++){
                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                            for(int a7 = a6 + 1; a7 < n - 3; a7++){
                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                for(int a8 = a7 + 1; a8 < n - 2; a8++){
                                    if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                    for(int a9 = a8 + 1; a9 < n - 1; a9++){
                                        if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                        
                                        for(int a10 = a9 + 1; a10 < n; a10++){
                                            if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;
                                            cnt++;
                                            tmpsum = add(tmpsum, pow(sub(c, tmp8), n));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=10 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 11){
        for(int i = 0; i < n - 9; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 8; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 7; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n - 6; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        
                        for(int a6 = a5 + 1; a6 < n - 5; a6++){
                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                            for(int a7 = a6 + 1; a7 < n - 4; a7++){
                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                for(int a8 = a7 + 1; a8 < n - 3; a8++){
                                    if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                    for(int a9 = a8 + 1; a9 < n - 2; a9++){
                                        if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                        
                                        for(int a10 = a9 + 1; a10 < n - 1; a10++){
                                            if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;

                                            for(int a11 = a10 + 1; a11 < n; a11++){
                                                if ((tmp9 = sum(tmp8, a[a11])) >= c) continue;
                                                cnt++;
                                                tmpsum = add(tmpsum, pow(sub(c, tmp9), n));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << "n=11 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 12){
        for(int i = 0; i < n - 10; i++){
            if (a[i] >= c) continue;
            for(int j = i + 1; j < n - 9; j++){
                if ((tmp1 = sum(a[i], a[j])) >= c) continue;

                for(int k = j + 1; k < n - 8; k++){
                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                    for(int a5 = k + 1; a5 < n - 7; a5++){
                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                        
                        for(int a6 = a5 + 1; a6 < n - 6; a6++){
                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                            for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                    if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                    for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                        if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                        
                                        for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                            if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;

                                            for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                if ((tmp9 = sum(tmp8, a[a11])) >= c) continue;
                                                
                                                for(int a12 = a11 + 1; a12 < n; a12++){
                                                    if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                    cnt++;
                                                    tmpsum = add(tmpsum, pow(sub(c, tmp10), n));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=12 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 13){
        for(int a14 = 0; a14 < n - 11; a14++){
            if (a[a14] >= c) continue;

            for(int a13 = a14 + 1; a13 < n - 10; a13++){
                if ((tmp12 = sum(a[a14], a[a13])) >= c) continue;

                for(int i = a13 + 1; i < n - 9; i++){
                    if ((tmp11 = sum(tmp12, a[i])) >= c) continue;

                    for(int j = i + 1; j < n - 8; j++){
                        if ((tmp1 = sum(tmp11, a[j])) >= c) continue;

                        for(int k = j + 1; k < n - 7; k++){
                            if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                            for(int a5 = k + 1; a5 < n - 6; a5++){
                                if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                
                                for(int a6 = a5 + 1; a6 < n - 5; a6++){
                                    if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                                    for(int a7 = a6 + 1; a7 < n - 4; a7++){
                                        if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                        for(int a8 = a7 + 1; a8 < n - 3; a8++){
                                            if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                            for(int a9 = a8 + 1; a9 < n - 2; a9++){
                                                if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                
                                                for(int a10 = a9 + 1; a10 < n - 1; a10++){
                                                    if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;

                                                    for(int a11 = a10 + 1; a11 < n; a11++){
                                                        if ((tmp9 = sum(tmp8, a[a11])) >= c) continue;
                                                        cnt++;
                                                        tmpsum = add(tmpsum, pow(sub(c, tmp9), n));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << endl << "n=13 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 14){
        for(int a14 = 0; a14 < n - 12; a14++){
            if (a[a14] >= c) continue;

            for(int a13 = a14 + 1; a13 < n - 11; a13++){
                if ((tmp12 = sum(a[a14], a[a13])) >= c) continue;

                for(int i = a13 + 1; i < n - 10; i++){
                    if ((tmp11 = sum(tmp12, a[i])) >= c) continue;

                    for(int j = i + 1; j < n - 9; j++){
                        if ((tmp1 = sum(tmp11, a[j])) >= c) continue;

                        for(int k = j + 1; k < n - 8; k++){
                            if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                            for(int a5 = k + 1; a5 < n - 7; a5++){
                                if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                
                                for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                    if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                                    for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                        if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                        for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                            if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                            for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                
                                                for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                    if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;

                                                    for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                        if ((tmp9 = sum(tmp8, a[a11])) >= c) continue;
                                                        
                                                        for(int a12 = a11 + 1; a12 < n; a12++){
                                                            if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                            cnt++;
                                                            tmpsum = add(tmpsum, pow(sub(c, tmp10), n));
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=14 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 15){
        for(int a15 = 0; a15 < n - 13; a15++){
            if (a[a15] >= c) continue;

            for(int a14 = a15 + 1; a14 < n - 12; a14++){
                if ((tmp13 = sum(a[a15], a[a14])) >= c) continue;

                for(int a13 = a14 + 1; a13 < n - 11; a13++){
                    if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;

                    for(int i = a13 + 1; i < n - 10; i++){
                        if ((tmp11 = sum(tmp12, a[i])) >= c) continue;

                        for(int j = i + 1; j < n - 9; j++){
                            if ((tmp1 = sum(tmp11, a[j])) >= c) continue;

                            for(int k = j + 1; k < n - 8; k++){
                                if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                                for(int a5 = k + 1; a5 < n - 7; a5++){
                                    if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                    
                                    for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                        if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                                        for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                            if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                            for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                                for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                    if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                    
                                                    for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                        if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;

                                                        for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                            if ((tmp9 = sum(tmp8, a[a11])) >= c) continue;
                                                            
                                                            for(int a12 = a11 + 1; a12 < n; a12++){
                                                                if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                cnt++;
                                                                tmpsum = add(tmpsum, pow(sub(c, tmp10), n));
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << "n=15 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 16){
        for(int a16 = 0; a16 < n - 14; a16++){
            if ((tmp15 = a[a16]) >= c) continue;

            for(int a15 = a16 + 1; a15 < n - 13; a15++){
                if ((tmp14 = sum(tmp15, a[a15])) >= c) continue;

                for(int a14 = a15 + 1; a14 < n - 12; a14++){
                    if ((tmp13 = sum(tmp14, a[a14])) >= c) continue;

                    for(int a13 = a14 + 1; a13 < n - 11; a13++){
                        if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;

                        for(int i = a13 + 1; i < n - 10; i++){
                            if ((tmp11 = sum(tmp12, a[i])) >= c) continue;

                            for(int j = i + 1; j < n - 9; j++){
                                if ((tmp1 = sum(tmp11, a[j])) >= c) continue;

                                for(int k = j + 1; k < n - 8; k++){
                                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;

                                    for(int a5 = k + 1; a5 < n - 7; a5++){
                                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                        
                                        for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;

                                            for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;

                                                for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                    if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;

                                                    for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                        if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                        
                                                        for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                            if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;

                                                            for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                                if ((tmp9 = sum(tmp8, a[a11])) >= c) continue;
                                                                
                                                                for(int a12 = a11 + 1; a12 < n; a12++){
                                                                    if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                    cnt++;
                                                                    tmpsum = add(tmpsum, pow(sub(c, tmp10), n));
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = sub(v, tmpsum);
    if (DEBUG) cout << "n=16 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 17){
        for(int a17 = 0; a17 < n - 15; a17++){
            if ((tmp16 = a[a17]) >= c) continue;

            for(int a16 = a17 + 1; a16 < n - 14; a16++){
                if ((tmp15 = sum(tmp16, a[a16])) >= c) continue;
                for(int a15 = a16 + 1; a15 < n - 13; a15++){
                    if ((tmp14 = sum(tmp15, a[a15])) >= c) continue;
                    for(int a14 = a15 + 1; a14 < n - 12; a14++){
                        if ((tmp13 = sum(tmp14, a[a14])) >= c) continue;
                        for(int a13 = a14 + 1; a13 < n - 11; a13++){
                            if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;
                            for(int i = a13 + 1; i < n - 10; i++){
                                if ((tmp11 = sum(tmp12, a[i])) >= c) continue;
                                for(int j = i + 1; j < n - 9; j++){
                                    if ((tmp1 = sum(tmp11, a[j])) >= c) continue;
                                    for(int k = j + 1; k < n - 8; k++){
                                        if ((tmp2 = sum(tmp1, a[k])) >= c) continue;
                                        for(int a5 = k + 1; a5 < n - 7; a5++){
                                            if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                            for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                                if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;
                                                for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                                    if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;
                                                    for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                        if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;
                                                        for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                            if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                            for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                                if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;
                                                                for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                                    if ((tmp9 = sum(tmp8, a[a11])) >= c) continue; 
                                                                    for(int a12 = a11 + 1; a12 < n; a12++){
                                                                        if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                        cnt++;
                                                                        tmpsum = add(tmpsum, pow(sub(c, tmp10), n));
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    v = add(v, tmpsum);
    if (DEBUG) cout << "n=17 a: " << tmpsum << " cnt: " << cnt << endl;
    cnt = tmpsum = 0;
    if (n >= 18){
        for(int a18 = 0; a18 < n - 16; a18++){
            if ((tmp17 = a[a18]) >= c) continue;

            for(int a17 = a18 + 1; a17 < n - 15; a17++){
                if ((tmp16 = sum(tmp17, a[a17])) >= c) continue;
                for(int a16 = a17 + 1; a16 < n - 14; a16++){
                    if ((tmp15 = sum(tmp16, a[a16])) >= c) continue;
                    for(int a15 = a16 + 1; a15 < n - 13; a15++){
                        if ((tmp14 = sum(tmp15, a[a15])) >= c) continue;
                        for(int a14 = a15 + 1; a14 < n - 12; a14++){
                            if ((tmp13 = sum(tmp14, a[a14])) >= c) continue;
                            for(int a13 = a14 + 1; a13 < n - 11; a13++){
                                if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;
                                for(int i = a13 + 1; i < n - 10; i++){
                                    if ((tmp11 = sum(tmp12, a[i])) >= c) continue;
                                    for(int j = i + 1; j < n - 9; j++){
                                        if ((tmp1 = sum(tmp11, a[j])) >= c) continue;
                                        for(int k = j + 1; k < n - 8; k++){
                                            if ((tmp2 = sum(tmp1, a[k])) >= c) continue;
                                            for(int a5 = k + 1; a5 < n - 7; a5++){
                                                if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                                for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                                    if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;
                                                    for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                                        if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;
                                                        for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                            if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;
                                                            for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                                if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                                for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                                    if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;
                                                                    for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                                        if ((tmp9 = sum(tmp8, a[a11])) >= c) continue; 
                                                                        for(int a12 = a11 + 1; a12 < n; a12++){
                                                                            if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                        
                                                                            v = sub(v, pow(sub(c, tmp10), n));
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (n >= 19){
        for(int a19 = 0; a19 < n - 17; a19++){
            if ((tmp18 = a[a19]) >= c) continue;

            for(int a18 = a19 + 1; a18 < n - 16; a18++){
                if ((tmp17 = sum(tmp18, a[a18])) >= c) continue;
                for(int a17 = a18 + 1; a17 < n - 15; a17++){
                    if ((tmp16 = sum(tmp17, a[a17])) >= c) continue;
                    for(int a16 = a17 + 1; a16 < n - 14; a16++){
                        if ((tmp15 = sum(tmp16, a[a16])) >= c) continue;
                        for(int a15 = a16 + 1; a15 < n - 13; a15++){
                            if ((tmp14 = sum(tmp15, a[a15])) >= c) continue;
                            for(int a14 = a15 + 1; a14 < n - 12; a14++){
                                if ((tmp13 = sum(tmp14, a[a14])) >= c) continue;
                                for(int a13 = a14 + 1; a13 < n - 11; a13++){
                                    if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;
                                    for(int i = a13 + 1; i < n - 10; i++){
                                        if ((tmp11 = sum(tmp12, a[i])) >= c) continue;
                                        for(int j = i + 1; j < n - 9; j++){
                                            if ((tmp1 = sum(tmp11, a[j])) >= c) continue;
                                            for(int k = j + 1; k < n - 8; k++){
                                                if ((tmp2 = sum(tmp1, a[k])) >= c) continue;
                                                for(int a5 = k + 1; a5 < n - 7; a5++){
                                                    if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                                    for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                                        if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;
                                                        for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                                            if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;
                                                            for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                                if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;
                                                                for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                                    if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                                    for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                                        if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;
                                                                        for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                                            if ((tmp9 = sum(tmp8, a[a11])) >= c) continue; 
                                                                            for(int a12 = a11 + 1; a12 < n; a12++){
                                                                                if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                            
                                                                                v = add(v, pow(sub(c, tmp10), n));
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (n >= 20){
        for(int a20 = 0; a20 < n - 18; a20++){
            if ((tmp19 = a[a20]) >= c) continue;

            for(int a19 = a20 + 1; a19 < n - 17; a19++){
                if ((tmp18 = sum(tmp19, a[a19])) >= c) continue;
                for(int a18 = a19 + 1; a18 < n - 16; a18++){
                    if ((tmp17 = sum(tmp18, a[a18])) >= c) continue;
                    for(int a17 = a18 + 1; a17 < n - 15; a17++){
                        if ((tmp16 = sum(tmp17, a[a17])) >= c) continue;
                        for(int a16 = a17 + 1; a16 < n - 14; a16++){
                            if ((tmp15 = sum(tmp16, a[a16])) >= c) continue;
                            for(int a15 = a16 + 1; a15 < n - 13; a15++){
                                if ((tmp14 = sum(tmp15, a[a15])) >= c) continue;
                                for(int a14 = a15 + 1; a14 < n - 12; a14++){
                                    if ((tmp13 = sum(tmp14, a[a14])) >= c) continue;
                                    for(int a13 = a14 + 1; a13 < n - 11; a13++){
                                        if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;
                                        for(int i = a13 + 1; i < n - 10; i++){
                                            if ((tmp11 = sum(tmp12, a[i])) >= c) continue;
                                            for(int j = i + 1; j < n - 9; j++){
                                                if ((tmp1 = sum(tmp11, a[j])) >= c) continue;
                                                for(int k = j + 1; k < n - 8; k++){
                                                    if ((tmp2 = sum(tmp1, a[k])) >= c) continue;
                                                    for(int a5 = k + 1; a5 < n - 7; a5++){
                                                        if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                                        for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                                            if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;
                                                            for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                                                if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;
                                                                for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                                    if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;
                                                                    for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                                        if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                                        for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                                            if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;
                                                                            for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                                                if ((tmp9 = sum(tmp8, a[a11])) >= c) continue; 
                                                                                for(int a12 = a11 + 1; a12 < n; a12++){
                                                                                    if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                                
                                                                                    v = sub(v, pow(sub(c, tmp10), n));
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (n >= 21){
        for(int a21 = 0; a21 < n - 19; a21++){
            if ((tmp20 = a[a21]) >= c) continue;

            for(int a20 = a21 + 1; a20 < n - 18; a20++){
                if ((tmp19 = sum(tmp20, a[a20])) >= c) continue;
                for(int a19 = a20 + 1; a19 < n - 17; a19++){
                    if ((tmp18 = sum(tmp19, a[a19])) >= c) continue;
                    for(int a18 = a19 + 1; a18 < n - 16; a18++){
                        if ((tmp17 = sum(tmp18, a[a18])) >= c) continue;
                        for(int a17 = a18 + 1; a17 < n - 15; a17++){
                            if ((tmp16 = sum(tmp17, a[a17])) >= c) continue;
                            for(int a16 = a17 + 1; a16 < n - 14; a16++){
                                if ((tmp15 = sum(tmp16, a[a16])) >= c) continue;
                                for(int a15 = a16 + 1; a15 < n - 13; a15++){
                                    if ((tmp14 = sum(tmp15, a[a15])) >= c) continue;
                                    for(int a14 = a15 + 1; a14 < n - 12; a14++){
                                        if ((tmp13 = sum(tmp14, a[a14])) >= c) continue;
                                        for(int a13 = a14 + 1; a13 < n - 11; a13++){
                                            if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;
                                            for(int i = a13 + 1; i < n - 10; i++){
                                                if ((tmp11 = sum(tmp12, a[i])) >= c) continue;
                                                for(int j = i + 1; j < n - 9; j++){
                                                    if ((tmp1 = sum(tmp11, a[j])) >= c) continue;
                                                    for(int k = j + 1; k < n - 8; k++){
                                                        if ((tmp2 = sum(tmp1, a[k])) >= c) continue;
                                                        for(int a5 = k + 1; a5 < n - 7; a5++){
                                                            if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                                            for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                                                if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;
                                                                for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                                                    if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;
                                                                    for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                                        if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;
                                                                        for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                                            if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                                            for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                                                if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;
                                                                                for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                                                    if ((tmp9 = sum(tmp8, a[a11])) >= c) continue; 
                                                                                    for(int a12 = a11 + 1; a12 < n; a12++){
                                                                                        if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                                    
                                                                                        v = add(v, pow(sub(c, tmp10), n));
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (n >= 22){
        for(int a22 = 0; a22 < n - 20; a22++){
            if ((tmp21 = a[a22]) >= c) continue;

            for(int a21 = a22+ 1; a21 < n - 19; a21++){
                if ((tmp20 = sum(tmp21, a[a21])) >= c) continue;

                for(int a20 = a21 + 1; a20 < n - 18; a20++){
                    if ((tmp19 = sum(tmp20, a[a20])) >= c) continue;
                    for(int a19 = a20 + 1; a19 < n - 17; a19++){
                        if ((tmp18 = sum(tmp19, a[a19])) >= c) continue;
                        for(int a18 = a19 + 1; a18 < n - 16; a18++){
                            if ((tmp17 = sum(tmp18, a[a18])) >= c) continue;
                            for(int a17 = a18 + 1; a17 < n - 15; a17++){
                                if ((tmp16 = sum(tmp17, a[a17])) >= c) continue;
                                for(int a16 = a17 + 1; a16 < n - 14; a16++){
                                    if ((tmp15 = sum(tmp16, a[a16])) >= c) continue;
                                    for(int a15 = a16 + 1; a15 < n - 13; a15++){
                                        if ((tmp14 = sum(tmp15, a[a15])) >= c) continue;
                                        for(int a14 = a15 + 1; a14 < n - 12; a14++){
                                            if ((tmp13 = sum(tmp14, a[a14])) >= c) continue;
                                            for(int a13 = a14 + 1; a13 < n - 11; a13++){
                                                if ((tmp12 = sum(tmp13, a[a13])) >= c) continue;
                                                for(int i = a13 + 1; i < n - 10; i++){
                                                    if ((tmp11 = sum(tmp12, a[i])) >= c) continue;
                                                    for(int j = i + 1; j < n - 9; j++){
                                                        if ((tmp1 = sum(tmp11, a[j])) >= c) continue;
                                                        for(int k = j + 1; k < n - 8; k++){
                                                            if ((tmp2 = sum(tmp1, a[k])) >= c) continue;
                                                            for(int a5 = k + 1; a5 < n - 7; a5++){
                                                                if ((tmp3 = sum(tmp2, a[a5])) >= c) continue;
                                                                for(int a6 = a5 + 1; a6 < n - 6; a6++){
                                                                    if ((tmp4 = sum(tmp3, a[a6])) >= c) continue;
                                                                    for(int a7 = a6 + 1; a7 < n - 5; a7++){
                                                                        if ((tmp5 = sum(tmp4, a[a7])) >= c) continue;;
                                                                        for(int a8 = a7 + 1; a8 < n - 4; a8++){
                                                                            if ((tmp6 = sum(tmp5, a[a8])) >= c) continue;
                                                                            for(int a9 = a8 + 1; a9 < n - 3; a9++){
                                                                                if ((tmp7 = sum(tmp6, a[a9])) >= c) continue;
                                                                                for(int a10 = a9 + 1; a10 < n - 2; a10++){
                                                                                    if ((tmp8 = sum(tmp7, a[a10])) >= c) continue;
                                                                                    for(int a11 = a10 + 1; a11 < n - 1; a11++){
                                                                                        if ((tmp9 = sum(tmp8, a[a11])) >= c) continue; 
                                                                                        for(int a12 = a11 + 1; a12 < n; a12++){
                                                                                            if ((tmp10 = sum(tmp9, a[a12])) >= c) continue;
                                                                                        
                                                                                            v = sub(v, pow(sub(c, tmp10), n));
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << v;
}
