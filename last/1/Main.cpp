#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

typedef struct{
	int Min = 1000000001;
	long long  Sum = 0;
} Segment;


Segment* tree;

void update(int pos, int s, int e, int p, int v){
	// A[pos] := v
	// We are at node p which represents interval [s, e]
	if (s == e){
		tree[p].Min = v;
		tree[p].Sum = v;
		return;
	}

	int m = (s + e) / 2;
	//printf("%d %d %d %d %d\n",pos, s, e, p, v);
	if(pos <= m) update(pos, s, m, 2*p, v);
	else update(pos, m+1, e, 2*p+1, v);
	tree[p].Min = tree[2*p].Min < tree[2*p+1].Min ? tree[2*p].Min : tree[2*p+1].Min;
	tree[p].Sum = tree[2*p].Sum + tree[2*p+1].Sum;
	// update the node from the child node value
}

Segment query(int s, int e, int ps, int pe, int p){
	// We want the result of interval [s, e]
	// We are at node p, which represents interval [ps, pe]
	if (e < ps || pe < s){
		Segment current;
		return current;
	} // does not intersect
	if (s <= ps && pe <= e) return tree[p]; // fully contained

	int pm = (ps + pe) / 2;
	auto l = query(s, e, ps, pm, 2*p);
	auto r = query(s, e, pm+1, pe, 2*p+1);

	Segment current;
	current.Min = l.Min < r.Min ? l.Min : r.Min;
	current.Sum = l.Sum + r.Sum;

	return current;
}

int main() {
	int n, q, n1;

	std::cin >> n >> q;

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



	Segment answer;

	for(int i = 0; i < q; i++){
		int a, l, r;
		std::cin >> a >> l >> r;

		switch(a){
			case 1:
				update(l, 1, n, 1, r);
				break;
			case 2:
				answer = query(l, r, 1, n, 1);
				printf("%d\n", answer.Min);
				break;
			case 3:
				answer = query(l, r, 1, n, 1);
				printf("%lld\n", answer.Sum);
				break;
		}
	}

	return 0;
}
