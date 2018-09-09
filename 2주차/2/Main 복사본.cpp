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

class Apple{
public:
    int sweet;
    bool valid;

    Apple(int _sweet){
        sweet = _sweet;
        valid = true;
    }

    bool operator<(const Apple& apple) const{
        return sweet > apple.sweet;
    }
};

int main() {
    queue<Apple*> que;
    priority_queue<Apple> minHeap;
	int n, m, s;

    cin >> n >> m;

    if (m == 1){
        for(int i = 0; i < n; i++){
            cin >> s;
            cout << s << " ";
        }
        return 0;
    }

    if (m == n){
        int minV = INT32_MAX;
        for(int i = 0; i < n; i++){
            cin >> s;
            minV = min(minV, s);
        }
        for(int i = 0; i < n; i++){
            cout << minV << " ";
        }
        return 0;
    }

    for(int i = 0 ; i < m; i++){
        cin >> s;
        Apple* appleptr = new Apple(s);
        que.push(appleptr);
        minHeap.push(*appleptr);
    }

    /*
    while(!minHeap.empty()){
        cout << minHeap.top().sweet << " ";
        minHeap.pop();
    }

    return 0;
    */

    for(int i = m; i < n; i++){
        while(!(minHeap.top().valid)){
            minHeap.pop();
        }

        cout << minHeap.top().valid << " ";

        (que.front())->valid = false;
        que.pop();

        cout << minHeap.top().valid << " ";

        cin >> s;
        Apple* appleptr = new Apple(s);
        que.push(appleptr);
        minHeap.push(*appleptr);
    }
}
