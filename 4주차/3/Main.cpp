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

using namespace std;

typedef struct _ComputerOrTask {
    int32_t r;
    int32_t price;
    int32_t core; 
    bool isComputer;
} ComputerOrTask;

vector<ComputerOrTask> A;

bool compareComputer(const ComputerOrTask& a, const ComputerOrTask& b){
    if (a.r == b.r){
        return a.isComputer < b.isComputer;
    }
    return a.r < b.r;
}

int main() {
    int N, M;
	uint32_t maxCore = 0, currentcore, currentr, currentprice;
    int64_t currentrevenue;
    ComputerOrTask currentComputerOrTask;
    
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> currentcore >> currentr >> currentprice;
        currentComputerOrTask.core = currentcore;
        currentComputerOrTask.r = currentr;
        currentComputerOrTask.price = currentprice;
        currentComputerOrTask.isComputer = true;
        A.push_back(currentComputerOrTask);
    }

    cin >> M;

    for(int i = 0; i < M; i++){
        cin >> currentcore >> currentr >> currentprice;
        currentComputerOrTask.core = currentcore;
        currentComputerOrTask.r = currentr;
        currentComputerOrTask.price = currentprice;
        currentComputerOrTask.isComputer = false;
        A.push_back(currentComputerOrTask);
        maxCore += currentcore;
    }

    // currentrevenue 정렬해야 함
    sort(A.begin(), A.end(), compareComputer);

    int64_t* revenue = new int64_t[maxCore+1];
    
    int64_t min64 = numeric_limits<int64_t>::min();

    for(int i = 1; i <= maxCore; i++){
        revenue[i] = min64;
    }
    revenue[0] = 0;

    for (vector<ComputerOrTask>::iterator it = A.begin() ; it != A.end(); ++it){
        //cout << it->price << " " << it->r << endl;
        if (it->isComputer){ // 컴퓨터는 필요한 코어 수를 감소시킬 것 -> 증가하는 방향으로
            for(int i = 1; i <= maxCore; i++){
                // 필요한 코어 수가 0 이하일 때는 굳이 컴퓨터를 살 이유가 없다

                if(revenue[i] > min64){
                    currentrevenue = revenue[i] - it->price;
                    currentcore = it->core > i ? 0 : i - it->core;
                    // 필요한 코어 수는 0 이상이어야만 함

                    revenue[currentcore] = revenue[currentcore] > currentrevenue
                        ? revenue[currentcore]
                        : currentrevenue;
                    // 이 상태에서의 수익 값 업데이트
                }
            }


        } else { // 일은 필요한 코어 수를 증가시킬 것 -> 감소하는 방향으로
            for(int i = maxCore; i >= 0; i--){
                if(revenue[i] > min64){
                    // 일을 하면 수익은 증가하지만 필요한 코어 수도 증가할 것이다
                    currentrevenue = revenue[i] + it->price;
                    currentcore = i + it->core;

                    // 어쨋던 증가한 수익 업데이트
                    revenue[currentcore] = revenue[currentcore] > currentrevenue
                        ? revenue[currentcore]
                        : currentrevenue;
                }
            }
        }
    }
    // 더이상 코어가 새로 필요하지 않은 상태에서의 수익 값이 답이다
    cout << revenue[0];
}
