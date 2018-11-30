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

using namespace std;

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
		youToLeftSeo[i] = sail(i,N);
		seoToRightYou[i] = sail(N,i);
	}

	for(int i = 1; i < N; i++){
		if (youToLeftSeo[i] == -1){
			answer.push_back(make_pair(i,1));
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
			answer.push_back(make_pair(N,i));
			you[N] += 1;
			seo[i] = 1;
			if (seoToRightYou[i-1] != -1){
				seo[i] += seoToRightYou[i-1];
			}
		} else if (seoToRightYou[i-1] != -1){
			seo[i] = seoToRightYou[i-1] - seoToRightYou[i];
		}
	}

	for(int i = 1; i <= N; i++){
		cerr << you[i] << " ";
	}
	cout << endl;
	for(int i = 1; i <= N; i++){
		cerr << seo[i] << " ";
	}
	cout << endl;
	
	
	for(int i = 1; i <= N; i++) {
		if(sail(i, i) == -1) {
			answer.push_back(std::make_pair(i, i));
		}
	}
	report(answer);

	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	/* IMPLEMENT HERE */
	
	return 0;
}