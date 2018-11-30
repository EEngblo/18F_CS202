#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

typedef struct{
	uint64_t inin = 0;
	uint64_t inex = 0;
	uint64_t exin = 0;
	uint64_t exex = 0;
} Segment;


Segment* tree;

uint64_t MAX(uint64_t a, uint64_t b, uint64_t c = 0, uint64_t d = 0){
	a = a > b ? a : b;
	c = c > d ? c : d;
	a = a > c ? a : c;
	return a;
}

void update(int pos, int s, int e, int p, int v){
	// A[pos] := v
	// We are at node p which represents interval [s, e]
	if (s == e){
		tree[p].inin = (uint64_t) v;
		return;
	}

	int m = (s + e) / 2;
	//printf("%d %d %d %d %d\n",pos, s, e, p, v);
	if(pos <= m) update(pos, s, m, 2*p, v);
	else update(pos, m+1, e, 2*p+1, v);
	tree[p].inin = MAX(
					tree[2*p].inex + tree[2*p+1].inin,
					tree[2*p].inin + tree[2*p+1].exin,
					tree[2*p].inex + tree[2*p+1].exin
	);
	tree[p].inex = MAX(
					tree[2*p].inex + tree[2*p+1].inex,
					tree[2*p].inin + tree[2*p+1].exex,
					tree[2*p].inex + tree[2*p+1].exex
	);
	tree[p].exin = MAX(
					tree[2*p].exin + tree[2*p+1].exin,
					tree[2*p].exex + tree[2*p+1].exin,
					tree[2*p].exex + tree[2*p+1].inin
	);
	tree[p].exex = MAX(
					tree[2*p].exin + tree[2*p+1].exex,
					tree[2*p].exex + tree[2*p+1].exex,
					tree[2*p].exex + tree[2*p+1].inex
	);
	// update the node from the child node value
}


int main() {
	int n, m, n1;

	std::cin >> n >> m;

	int cnt = 2;
	n1 = n;

	while ((n1 = n1 >> 1) > 0)
		cnt++;

	tree = new Segment[1 << cnt];

	for(int i = 1; i <= n; i++){
		int val;
		std::cin >> val;

		update(i, 1, n, 1, val);
	}

	uint64_t answer = 0;
	for(int i = 0; i < m; i++){
		int j, m;
		std::cin >> j >> m;

		update(j, 1, n, 1, m);
		answer += MAX(tree[1].inin, tree[1].inex, tree[1].exin, tree[1].exex);
	}

	std::cout << answer;

	return 0;
}
