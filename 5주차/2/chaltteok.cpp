#include <cstdio>
#include <vector>
#include <cstdlib>

#define DEBUG 0

int count = 0;


int pack(std::vector<int> &M) {
    count++;
    printf("? %d", (int)M.size());
    for(int &x : M) printf(" %d", x);
    puts("");
    fflush(stdout);
    int ret; scanf("%d", &ret);
    if(ret == -202) exit(0);
    return ret;
}

void report(std::vector<int> &M) {
    printf("!");
    for(int &x : M) printf(" %d", x);
    puts("");
    fflush(stdout);
}

int** chaltteok;


int bsearch(std::vector<int> &_q, int pivot){
    // q에는 pivot과 붙어있는지 검사할 후보 수
    // answer에는 찾은 답들 저장
    // pivot은 붙어있는 두 수를 찾고자 하는 기준 수
    std::vector<int> small, large;
    std::vector<int> q(_q);
    int cnt = 0;

    if(q.size() == 1){
        return q[0];
    } else if(q.size() == 2){
        small.push_back(pivot);
        small.push_back(q[0]);

        if(pack(small) == 1)
            return q[0];
        else
            return q[1];
    }
    
    int size = q.size() >> 1;
    int lInclude = 0, lExclude = 0;

    for(int i = 0; i < size; i++){
        small.push_back(q.front());
        q.erase(q.begin());
    }

    while(q.size() != 0){
        large.push_back(q.front());
        q.erase(q.begin());
    }

    large.push_back(pivot);
    small.push_back(pivot);
    
    if((lInclude = pack(large)) < large.size()){ // large쪽에 붙어있는 아이들이 하나 이상 존재
        large.pop_back();
        if((lExclude = pack(large)) >= lInclude){ // large쪽에서 pivot을 뺏더니 덩어리 수 같거나 증가 -> pivot과 이웃한 떡 존재
            return bsearch(large, pivot);
        }
    }
    // large 쪽에 pivot과 붙어 있는 떡이 없다면 small 쪽 조사
    small.pop_back();
    return bsearch(small, pivot);
}

int main() {
    int N; scanf("%d", &N);
    std::vector<int> sel, ans;
    int startPoint;
    
    chaltteok = new int*[N+1];
    for(int i = 0; i <= N; i++){
        chaltteok[i] = new int[N+1];
    }
    if(N == 1){
        ans.push_back(1);
        report(ans);
        return 0;

    } else {
        std::vector<int> all;

        for(int i = 1; i <= N; i++){
            all.push_back(i);
        }
        for(int i = 1; i <= N; i++){
            all.erase(all.begin());
            int resp = pack(all);
            if (resp == 1){
                startPoint = i;
                ans.push_back(i);
                break;
            }
            all.push_back(i);
        }

        while(ans.size() != N){
            std::vector<int> candidate;

            for(int i = 1; i <= N; i++){
                if(i != startPoint && chaltteok[startPoint][i] == 0){
                    candidate.push_back(i);
                }
            }

            int newPoint = bsearch(candidate, startPoint);
            ans.push_back(newPoint);

            chaltteok[newPoint][startPoint] = 1;

            startPoint = newPoint;
        }

    }

    //fprintf(stderr, "%d\n", count);
    report(ans);
    return 0;
}
