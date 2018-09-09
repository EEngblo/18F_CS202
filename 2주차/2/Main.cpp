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

int main() {
    queue<int> que; // 관심 대상
    map<int, int> apples; // 최소값 찾기 위한 map; 1번 문제 응용
    map<int, int>::iterator minSweet; // 최소값 가리킬 포인터
	int n, m, s;
    int* moreApples; // 원형 큐를 구현하기 위한 처음 m개의 당도 담을 배열

    cin >> n >> m;

    if (m == 1){ // m == 1인 경우 당도 읽자 마자 그대로 출력
        for(int i = 0; i < n; i++){
            cin >> s;
            cout << s << " ";
        }
        return 0;
    }

    if (m == n){ // m == n인 경우 최소값 조사해서 그 값 출력
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

    // 원형 큐 구현을 위해서 처음 m개의 당도를 배열에 따로 저장
    moreApples = (int*) malloc(m * sizeof(int));

    // 처음 m개 담기
    for(int i = 0 ; i < m; i++){
        cin >> s;
        que.push(s); // 큐에는 항상 m개의 사과만 담기도록 할 것임
        apples[s]++; // map의 key는 당도, value는 그 당도에 해당하는 유효한 사과 수
        moreApples[i] = s;
    }

    // 사과 삭제가 O(nlogn)이고
    // map에 새로 추가하는 작업이 O(logn) * n이므로 시간복잡도는 O(nlogn)
    for(int i = 0; i < n - m; i++){
        minSweet = apples.begin();

        // 유효하지 않은 사과들은 제거해야 함
        // 최대 n번의 사과를 삭제하게 되므로 O(nlogn)
        while(!(minSweet->second)) { // 최소 당도이지만 유효한 사과가 없으면
            apples.erase(minSweet); // 그 당도 node를 삭제
            minSweet++; // 다음 최소 당도 node에 대해 조사
        }

        cout << minSweet->first << " "; // 최소 당도(만족도) 출력

        // 큐에 새로운 사과 추가할 준비
        apples[que.front()]--; // 범위 밖으로 벗어난 사과를 map에서 무효화
        que.pop(); // 범위 밖으로 벗어난 사과를 큐에서 제거

        cin >> s;
        que.push(s); // 큐에 새로운 사과 추가
        apples[s]++; // map에 새로운 사과 추가
    }

    // 배열에 따로 빼 둔 사과들에 대해서도 마찬가지 방법 수행
    for(int i = 0; i < m; i++){
        minSweet = apples.begin();

        while(!(minSweet->second)) {
            apples.erase(minSweet);
            minSweet++;
        }

        cout << minSweet->first << " ";

        apples[que.front()]--;
        que.pop();

        que.push(moreApples[i]);
        apples[moreApples[i]]++;
    }
}
