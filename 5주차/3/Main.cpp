#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int sail(int a, int b) {
	std::cout << "? " << a << " " << b << std::endl << std::flush;
	int v; std::cin >> v;
	if(v == -202) {
		exit(0);
	}
	return v;
}

void report(std::vector<std::pair<int, int>> bridges) {
	std::cout << "!" << std::endl << std::flush;
	std::cout << bridges.size() << std::endl << std::flush;
	for(size_t i = 0; i < bridges.size(); i++) {
		std::cout << bridges[i].first << " " << bridges[i].second << std::endl << std::flush;
	}
}

int main() {
	int N;
	std::cin >> N;
	if(N < 0) {
		/* this means your code is already wrong, exit immediately */
		return 0;
	}
    
	std::vector<std::pair<int, int>> answer;
	int* youToLeftSeo = new int[N];
	int* seoToRightYou = new int[N];
	int* you = new int[N];
	int* seo = new int[N];

	for(int i = 1; i <= N; i++){
		youToLeftSeo[i] = sail(i,1);
		seoToRightYou[i] = sail(N,i);
	}

	for(int i = 1; i < N; i++){
		if (youToLeftSeo[i] == -1){
			seo[1] += 1;
			you[i] = 1;
			if (youToLeftSeo[i+1] != -1){
				you[i] += youToLeftSeo[i+1];
			}
		} else if (youToLeftSeo[i+1] != -1){
			you[i] = youToLeftSeo[i+1] - youToLeftSeo[i];
		}
	}
    

	for(int i = N; i > 1; i--){
		if (seoToRightYou[i] == -1){
			//if(i == N) answer.push_back(std::make_pair(N,i)); // 마지막 종료 조건 때문에 이 경우 체크 못 하기 때문
			you[N] += 1;
			seo[i] = 1;
			if (seoToRightYou[i-1] != -1){
				seo[i] += seoToRightYou[i-1];
			}
		} else if (seoToRightYou[i-1] != -1){
			seo[i] = seoToRightYou[i-1] - seoToRightYou[i];
		}
	}

    if(youToLeftSeo[N] == -1 && seoToRightYou[1] == -1){
        seo[1] += 1;
        you[N] += 1;
    }
	
    int sp = 1, yp = 1;
    while(sp <= N || yp <= N){
        while(you[yp] == 0) yp++;
        while(seo[sp] == 0) sp++;

        if(sp <= N && yp <= N) {
            answer.push_back(std::make_pair(yp,sp));
            //std::cerr << yp << " " << sp << std::endl;
        }
        you[yp]--; seo[sp]--;
    }

	report(answer);
	
	return 0;
}