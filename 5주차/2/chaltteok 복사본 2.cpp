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

void mark(std::vector<int> &M, int val = 2){
    for(int i = 0; i < M.size() - 1; i++){
        for(int j = i+1; j < M.size(); j++){
            if(chaltteok[M[i]][M[j]] == 0){
                chaltteok[M[i]][M[j]] = val;
                chaltteok[M[j]][M[i]] = val;
            }
        }
    }
}

bool haveToDo(std::vector<int> &M, int val = 2){
    for(int i = 0; i < M.size() - 1; i++){
        for(int j = i+1; j < M.size(); j++){
            if(chaltteok[M[i]][M[j]] == 0){
                return true;
            }
        }
    }
    return false;
}

std::vector<int> answer;

int bsearch(std::vector<int> &_q, int pivot){
    // q에는 pivot과 붙어있는지 검사할 후보 수
    // answer에는 찾은 답들 저장
    // pivot은 붙어있는 두 수를 찾고자 하는 기준 수
    std::vector<int> small, large;
    std::vector<int> q(_q);
    int cnt = 0;

    if(q.size() == 1){
        answer.push_back(q[0]);
        if(DEBUG) fprintf(stderr,"!!!!!!! %d -> %d\n",pivot,q[0]);
        return 1;
    } else if(q.size() == 2){
        small.push_back(pivot);
        small.push_back(q[0]);
        bool a = true;
        if(pack(small) == 1){
            cnt++;
            if(DEBUG) fprintf(stderr,"!!!!!!! %d -> %d\n",pivot,q[0]);
            answer.push_back(q[0]);
            a &= false;
        } else {
            cnt++;
            if(DEBUG) fprintf(stderr,"!!!!!!! %d -> %d\n",pivot,q[1]);
            answer.push_back(q[1]);
            a &= false;
        }
        /*
        large.push_back(pivot);
        large.push_back(q[1]);
        if(pack(large) == 1){
            cnt++;
            if(DEBUG) fprintf(stderr,"!!!!!!! %d -> %d\n",pivot,q[1]);
            answer.push_back(q[1]);
            a &= false;
        }*/
        return cnt;
    }
    
    int size = q.size() >> 1;
    int lInclude = 0, lExclude = 0, sInclude = 0, sExclude = 0;
    

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
    
    if((large.size() > 1) && (answer.size() < 2) && (lInclude = pack(large)) < large.size()){ // large쪽에 붙어있는 아이들이 하나 이상 존재
        large.pop_back();
        if(lInclude == 1){
            cnt += large.size();
            while(large.size() != 0){
                answer.push_back(large.back());
                large.pop_back();
            }
        } else if((lExclude = pack(large)) > lInclude){ // large쪽에서 pivot을 뺏더니 덩어리 수 증가 -> pivot과 이웃한 떡 두 개 존재
            if(DEBUG) fprintf(stderr, "[%d-%d] large: %d~%d, lsize=%d, lInclude= %d, lExclude= %d\n",pivot,size,large.front(),large.back(),large.size(),lInclude,lExclude);
            cnt += bsearch(large, pivot);
            return cnt;
        } else if(lExclude == lInclude){         // large쪽에서 pivot을 뺏더니 덩어리 수 동일 -> pivot과 이웃한 떡 하나 존재
            if(DEBUG) fprintf(stderr, "[%d-%d] large: %d~%d, lsize=%d, lInclude= %d, lExclude= %d\n",pivot,size,large.front(),large.back(),large.size(),lInclude,lExclude);
            cnt += bsearch(large, pivot);
        }
    }
    if((small.size() > 1) && (answer.size() < 2) && ((sInclude = pack(small)) < small.size())){ // 아직 다 못 찾았고 small쪽에 붙어 있는 아이들이 하나 이상 존재
        small.pop_back();
        if(sInclude == 1){
            cnt += small.size();
            while(small.size() != 0){
                answer.push_back(small.back());
                small.pop_back();
            }
        } else if((sExclude = pack(small)) >= sInclude){
            if(DEBUG) fprintf(stderr, "[%d-%d] small: %d~%d, ssize=%d, sInclude= %d, sExclude= %d\n",pivot,size,small.front(),small.back(),small.size(),sInclude,sExclude);
            cnt += bsearch(small, pivot);
        }
    }
    return cnt;
}

int main() {
    int N; scanf("%d", &N);
    std::vector<int> sel, ans;
    
    chaltteok = new int*[N+1];
    for(int i = 0; i <= N; i++){
        chaltteok[i] = new int[N+1];
    }
    if(N == 1){
        ans.push_back(1);
        report(ans);
        return 0;

    } else if (N <= 200) {
        std::vector<int> query;

        for(int i = 1; i < N; i++){
            query.clear();
            query.push_back(i);
            for(int j = i+1; j <= N; j++){
                query.push_back(j);
                if(chaltteok[i][0] == 2) break;

                if(chaltteok[j][0] == 2){
                    chaltteok[i][j] = 2;
                    chaltteok[j][i] = chaltteok[i][j];
                    query.pop_back();
                    continue;

                } else {
                    chaltteok[i][j] = pack(query) == 1
                                        ? 1  // 연결됨 (0:= 아직 모름)
                                        : 2; // 연결 안 됨
                }
                chaltteok[j][i] = chaltteok[i][j];
                if (chaltteok[i][j] == 1) {
                    chaltteok[i][0]++;
                    chaltteok[j][0]++;
                }
                query.pop_back();
            }
        }
        
    } else {
        for(int i = 1; i < N; i++){
            if(chaltteok[i][0] == 2) continue;

            std::vector<int> candidate;
            
            answer.clear();

            for(int j = i+1; j <= N; j++){
                if(chaltteok[i][j] == 1){
                    answer.push_back(j);
                } else if(chaltteok[i][j] == 0){
                    candidate.push_back(j);
                }
            }
            int prevcount = count;
            if(DEBUG) fprintf(stderr, "%d\n", i);
            if(DEBUG) fprintf(stderr, "%d: %d found ", i, bsearch(candidate, i));
            else bsearch(candidate, i);
            if(DEBUG) fprintf(stderr, "%d\n", answer.size());

            fprintf(stderr, "[%d] %d query size %d -> %d\n",i,count-prevcount, candidate.size(), chaltteok[200][0]);
            
  
            // 찾은 이웃들을 추가
            for(int j = 0; j < answer.size(); j++){
                if(chaltteok[i][answer[j]] == 0){
                    chaltteok[i][answer[j]] = 1;
                    chaltteok[i][0]++;
                }
                if(chaltteok[answer[j]][i] == 0){
                    chaltteok[answer[j]][i] = 1;
                    chaltteok[answer[j]][0]++;
                }
            }
            for(int j = i+1; j <= N; j++){
                if(chaltteok[i][j] == 0){
                    chaltteok[i][j] = 2;
                    chaltteok[j][i] = 2;
                }
            }
        }
    }

    int start;
    for(start = 1; start <= N; start++){
        if(DEBUG) fprintf(stderr, "%d -> %d\n", start,chaltteok[start][0]);
        if(chaltteok[start][0] == 1){
            chaltteok[start][0] = 0;
            ans.push_back(start);
            if(DEBUG) fprintf(stderr, "%d ",start);
            break;
        }
    }
    for(int i = start; chaltteok[i][0] != 1;){
        for(int j = 1; j <= N; j++){
            if(chaltteok[i][j] == 1){
                chaltteok[i][j] = 0;
                chaltteok[j][i] = 0;
                ans.push_back(j);
                if(DEBUG) fprintf(stderr, "%d ",j);
                i = j;
                break;
            }
        }
    }


    fprintf(stderr, "%d\n", count);
    report(ans);
    return 0;
}
