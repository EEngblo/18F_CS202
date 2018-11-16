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

typedef struct _Computer {
    int32_t r;
    int32_t price;
    int32_t core; 
    float efficient;
} Computer;

typedef struct _Task {
    int32_t r;
    int32_t price;
    int32_t core; 
    float efficient;
} Task;


int main() {
    int N, M;
	uint32_t core = 0, currentcore;
    int64_t profit = 0;
    
    cin >> N;

    Computer* computers = new Computer[N];
    for(int i = 0; i < N; i++){
        cin >> computers[i].core >> computers[i].r >> computers[i].price;
        computers[i].efficient = (float) computers[i].price / (float) computers[i].core;
        profit -= computers[i].price;
        core += computers[i].core;
    }

    cin >> M;

    Task* tasks = new Task[M];
    for(int i = 0; i < M; i++){
        cin >> tasks[i].core >> tasks[i].r >> tasks[i].price;
        tasks[i].efficient = (float) tasks[i].price / (float) tasks[i].core;
    }

    int64_t* revenue = new int64_t[core+1];
    int64_t currentrevenue;
    for(int i = 0; i < core; i++){
        revenue[i] = -1;
    }
    revenue[core] = 0;

    for(int i = 0; i < N; i++){
        currentcore = computers[i].core;
        for(int j = currentcore; j <= core; j++){
            if(revenue[j] >= 0){
                currentrevenue = revenue[j] + computers[i].price;
                revenue[j-currentcore] = revenue[j-currentcore] > currentrevenue
                    ? revenue[j-currentcore]
                    : currentrevenue;
                if(DEBUG) cout << i << " i:j " << j << " is " << revenue[j] << "and " << revenue[j-currentcore] << endl;
            }
        }
    }

    for(int i = 0; i < M; i++){
        currentcore = tasks[i].core;
        for(int j = currentcore; j <= core; j++){
            if(revenue[j] >= 0){
                currentrevenue = revenue[j] + tasks[i].price;
                revenue[j-currentcore] = revenue[j-currentcore] > currentrevenue
                    ? revenue[j-currentcore]
                    : revenue[j] + tasks[i].price; 
                if(DEBUG) cout << i << " i:j " << j << " is " << revenue[j] << "and " << revenue[j-currentcore] << endl;
            }
        }
    }

    int64_t maxRevenue = -1;
    for(int i = 0; i <= core; i++){
        maxRevenue = revenue[i] > maxRevenue ? revenue[i] : maxRevenue;
        if(DEBUG) cout << revenue[i] << " ";
    }

    if(DEBUG) cout << endl << maxRevenue << " " << profit << endl;
    cout << maxRevenue + profit;
}
