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
	int n, a, b;
    bool first = true;

    map<int,int> A;
    map<int,int>::iterator max, min;

    cin >> n;

    for(int i = 0 ; i < n; i++){
        cin >> a >> b;
    
        switch(a){
            case 1: // push
                A[b]++;
                max = A.end();
                --max;
                min = A.begin();
                break;

            case 2: // pop
                if (A.empty()){
                    break;
                }

                if(b > 0){ // max
                    if(--(max->second) == 0){
                        A.erase(max);
                        --max;
                    }
                } else { // min
                    if(--(min->second) == 0){
                        A.erase(min);
                        ++min;
                    }
                }
                break;

            case 3:
                if (first){
                    first = false;
                } else {
                    cout << " ";
                }

                if (A.empty()){
                    cout << "EMPTY";
                    break;
                }

                if(b > 0){ // max
                    cout << max->first;
                } else { // min
                    cout << min->first;
                }
                break;
        }
        //fprintf(stderr,"\n max : %d, min : %d\n", *(--A.end()), *(A.begin()));
    }
}
