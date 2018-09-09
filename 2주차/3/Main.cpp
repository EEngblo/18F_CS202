#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <tuple>
#include <functional>
#include <set>
#include <string>

#define DEBUG 0

using namespace std;

typedef struct _rectangle {
    int x1;
    int x2;
    int y1;
    int y2;
} Rectangle;

typedef struct _line {
    int y1;
    int y2;
} Line;

bool rectagleCompare(Rectangle a, Rectangle b) {
    if (a.x1 >= 0 && a.x1 != b.x1) {
        return a.x1 < b.x1;
    }
    if (a.x2 >= 0 && a.x2 != b.x2) {
        return a.x2 < b.x2;
    }
    if (a.y1 >= 0 && a.y1 != b.y2) {
        return a.y1 < b.y1;
    }
    return a.y2 < b.y2;
}

vector<Rectangle> xStart, xEnd;
vector<Rectangle>::iterator xStartIter, xEndIter;
vector<int> xAll;
multimap<int, Line> activeRectangles;

int main() {
    int n, x1, x2, y1, y2, i;
    int deltaX = 0;
    int oldX;
    int height = 0;
    int newHeight = 0;
    int linecnt, newLinecnt;
    uint64_t size = 0;
    bool haveChanged;

    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> x1 >> x2 >> y1 >> y2;

        // 입력받은 사각형들을 각각 벡터에 넣고
        xStart.push_back(Rectangle{x1, x2, y1, y2});
        xEnd.push_back(Rectangle{-1, x2, y1, y2});
        xAll.push_back(x1);
        xAll.push_back(x2);
    }

    // 각각의 벡터를 x1에 대해 오름차순, x2에 대해 오름차순으로 정렬한다
    sort(xStart.begin(), xStart.end(), rectagleCompare);
    sort(xEnd.begin(), xEnd.end(), rectagleCompare);
    sort(xAll.begin(), xAll.end());
    vector<int>::iterator it = unique(xAll.begin(), xAll.end());
    xAll.resize(distance(xAll.begin(), it));
    
#if DEBUG
    if(DEBUG) fprintf(stderr, "정렬 완료\n");

    if(DEBUG) {
    for (auto &Rectangl : xStart) {
       cout << Rectangl.x1 << " " << Rectangl.x2 << " " << Rectangl.y1 << " " << Rectangl.y2 << endl;
    }
    for (auto &Rectangl : xEnd) {
       cout << Rectangl.x1 << " " << Rectangl.x2 << " " << Rectangl.y1 << " " << Rectangl.y2 << endl;
    }
    }
#endif
    

    xStartIter = xStart.begin();
    xEndIter = xEnd.begin();
    i = xStartIter->x1;

    // 가장 작은 x1부터 가장 큰 x2(=maxX)까지 x = i인 직선들에 대해 사각형과의 겹치는 높이 조사
    for(it = xAll.begin(); it != xAll.end(); it++) {
        deltaX = *it - i;
        i = *it;

        // 넓이 더하기 =======================================
        
#if DEBUG
        if(DEBUG) fprintf(stderr, "x=%d 현재 넓이 %lld + %lld | deltaX = %d, height = %d\n", i, size, (uint64_t) height * (uint64_t) deltaX, deltaX, height);
#endif
        size += (uint64_t) height * (uint64_t) deltaX; // add size

        while(xStartIter != xStart.end() && xStartIter->x1 == i){ // 새로운 사각형 추가
#if DEBUG
            if(DEBUG) fprintf(stderr, "x=%d 사각형 시작 %d->%d\n", i, xStartIter->y1, xStartIter->y2);
#endif
            activeRectangles.insert(
                pair<int, Line>(
                    xStartIter->x2,
                    Line{xStartIter->y1, xStartIter->y2}
                )
            );
            xStartIter++;
        }
        while(xEndIter != xEnd.end() && xEndIter->x2 == i){ // 기존 사각형 제거
#if DEBUG
            if(DEBUG) fprintf(stderr, "x=%d 사각형 마지막\n", i);
#endif
            activeRectangles.erase(i);
            xEndIter++;
        }/*
        if(xEndIter != xEnd.end() && xEndIter->x2 == i){ // 기존 사각형의 마지막
            if(DEBUG) fprintf(stderr, "x=%d 사각형 마지막\n", i);
            haveChanged = true;
        }*/

        // 사각형에 변화 생기면 높이 다시 계산하고 지금까지의 넓이 더함
#if DEBUG
        if(DEBUG) fprintf(stderr, "x=%d 에서 검사중\n", i);
#endif
        // 높이 다시 계산 ===================================
        priority_queue<int> yStart; // values should be negated
        priority_queue<int> yEnd; // values should be negated
        height = 0;
        linecnt = 0;
        newLinecnt = 0;
        int fragmentStart;

        // 현재 x값에 해당하는 사각형들의 y값들을 정렬
        for(multimap<int, Line>::iterator it=activeRectangles.begin(); it!=activeRectangles.end(); ++it){
            if(DEBUG) {
                cout << it->first << " " << it->second.y1 << " " << it->second.y2 << endl;
            }
            yStart.push(-(it->second.y1));
            yEnd.push(-(it->second.y2));
        }

        // 모든 사각형에 대해서 검사
        while(!(yStart.empty() && yEnd.empty())){
#if DEBUG
            if(DEBUG) fprintf(stderr, "x=%d 에서 yStart=%d, yEnd=%d\n", i, yStart.top(), yEnd.top());
#endif
            if(!yStart.empty() && yStart.top() > yEnd.top()){
                newLinecnt++;
                if (linecnt == 0)
                    fragmentStart = yStart.top();
                yStart.pop();
            } else {
                newLinecnt--;
                if (newLinecnt == 0)
                    height += fragmentStart - yEnd.top();
                yEnd.pop();
            }
            linecnt = newLinecnt;
        }

    }

    cout << size;
}
