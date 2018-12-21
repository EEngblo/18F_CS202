#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

char weigh(int x, int y) {
	std::cout << "? " << x << " " << y << std::endl << std::flush;
	std::string s; std::cin >> s;
	if(s == "-202") {
		exit(0);
	}
	return s[0];
}

void report(std::vector<int> minPos, std::vector<int> maxPos) {
	std::cout << "!" << std::endl;
	std::cout << minPos.size();
	for(size_t i = 0; i < minPos.size(); i++) 
		std::cout << " " << minPos[i];
	std::cout << std::endl << maxPos.size();
	for(size_t i = 0; i < maxPos.size(); i++) 
		std::cout << " " << maxPos[i];
	std::cout << std::endl << std::flush;
}

int main() {
	int T; std::cin >> T;
	for(int test_case_id = 1; test_case_id <= T; test_case_id++) {		
		int N;
		std::cin >> N;
		if(N < 0) {
			/* this means your code is already wrong, exit immediately */
			return 0;
		}

		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		/* IMPLEMENT HERE */
		// Below is an example solution that requires N(N-1) weighings.
		// Don't forget to initialize all global variables.

		std::vector<int> minPos, maxPos, tempPos;
		char resp;

        if(N & 1){
            minPos.push_back(N);
			maxPos.push_back(N);
			N -= 1;
        } else {
			resp = weigh(N, N-1);
			if(resp == '>'){
				maxPos.push_back(N);
				minPos.push_back(N-1);
			} else if(resp == '<'){
				maxPos.push_back(N-1);
				minPos.push_back(N);
			} else {
				maxPos.push_back(N);
				maxPos.push_back(N-1);
				minPos.push_back(N);
				minPos.push_back(N-1);
			}

			N -= 2;
        }     

		for(int n = 2; n <= N; n+=2){
			resp = weigh(n, n-1);
			if(resp == '>'){
				resp = weigh(n, maxPos[0]);
				if(resp == '>'){
					maxPos.clear();
					maxPos.push_back(n);
				} else if(resp == '='){
					maxPos.push_back(n);
				}

				resp = weigh(n-1, minPos[0]);
				if(resp == '<'){
					minPos.clear();
					minPos.push_back(n-1);
				} else if (resp == '='){
					minPos.push_back(n-1);
				}
				
			} else if(resp == '<'){
				resp = weigh(n-1, maxPos[0]);
				if(resp == '>'){
					maxPos.clear();
					maxPos.push_back(n-1);
				} else if(resp == '='){
					maxPos.push_back(n-1);
				}

				resp = weigh(n, minPos[0]);
				if(resp == '<'){
					minPos.clear();
					minPos.push_back(n);
				} else if (resp == '='){
					minPos.push_back(n);
				}
			} else {
				resp = weigh(n-1, maxPos[0]);
				if(resp == '>'){
					maxPos.clear();
					maxPos.push_back(n-1);
					maxPos.push_back(n);
				} else if(resp == '='){
					maxPos.push_back(n-1);
					maxPos.push_back(n);
				}

				resp = weigh(n, minPos[0]);
				if(resp == '<'){
					minPos.clear();
					minPos.push_back(n-1);
					minPos.push_back(n);
				} else if (resp == '='){
					minPos.push_back(n-1);
					minPos.push_back(n);
				}
			}
		}

		report(minPos, maxPos);
		/* IMPLEMENT HERE */

		/* IMPLEMENT HERE */

	}
	return 0;
}
