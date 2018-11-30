#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define M true

typedef struct{
	int y;
	int x;
} Point;


typedef struct{
	Point start;
	Point end;
	uint64_t distance = UINT64_MAX;
} Path;

typedef struct{
	Path s; // no start
	Path m; // no middle point
	Path e; // no end point
	Path f; // full
} Segment;




Path mergePath(Path a, Path b, bool isMiddle = false){
	Path path;
	if(isMiddle && (a.distance == UINT64_MAX || b.distance == UINT64_MAX))
		return path;
	
	if(a.distance == UINT64_MAX && b.distance == UINT64_MAX)
		return path;

	if(a.distance == UINT64_MAX)
		return b;

	if(b.distance == UINT64_MAX)
		return a;

	path.start.x = a.start.x;
	path.start.y = a.start.y;
	path.end.x = b.end.x;
	path.end.y = b.end.y;

	int dx = a.end.x - b.start.x;
	dx = dx > 0 ? dx : -dx;
	int dy = a.end.y - b.start.y;
	dy = dy > 0 ? dy : -dy;

	path.distance = dx + dy + a.distance + b.distance;
	return path;
}

Path minPath(Path a, Path b){
	Path answer = a.distance > b.distance
					? b
					: a;
	return answer;
}

Segment* tree;

void update(int pos, int s, int e, int p, Point v){
	// A[pos] := v
	// We are at node p which represents interval [s, e]
	if (s == e){
		tree[p].f.start = v;
		tree[p].f.end = v;
		tree[p].f.distance = 0;
		return;
	}

	int m = (s + e) / 2;
	//
	if(pos <= m) update(pos, s, m, 2*p, v);
	else update(pos, m+1, e, 2*p+1, v);

	tree[p].s = mergePath(tree[2*p].s, tree[2*p+1].f);
	tree[p].m = minPath( minPath(
					mergePath(tree[2*p].e, tree[2*p+1].f, M),
					mergePath(tree[2*p].f, tree[2*p+1].s, M)), minPath(
					mergePath(tree[2*p].f, tree[2*p+1].m, M),
					mergePath(tree[2*p].m, tree[2*p+1].f, M)));
	tree[p].e = mergePath(tree[2*p].f, tree[2*p+1].e);
	tree[p].f = mergePath(tree[2*p].f, tree[2*p+1].f);
	// update the node from the child node value
	/*printf("[%d] %lu %lu %lu %lu, s: %d %d\n", 2*p, tree[2*p].s.distance, tree[2*p].m.distance, tree[2*p].e.distance, tree[2*p].f.distance, tree[2*p].s.end.x, tree[2*p].s.end.y);
	printf("[%d] %lu %lu %lu %lu, f: %d %d\n", 2*p+1, tree[2*p+1].s.distance, tree[2*p+1].m.distance, tree[2*p+1].e.distance, tree[2*p+1].f.distance, tree[2*p+1].f.start.x, tree[2*p+1].f.start.y);
	printf("[%d] %lu %lu %lu %lu\n", p, tree[p].s.distance, tree[p].m.distance, tree[p].e.distance, tree[p].f.distance);
	printf("===\n");*/
}

Segment query(int s, int e, int ps, int pe, int p){
	// We want the result of interval [s, e]
	// We are at node p, which represents interval [ps, pe]
	if (e < ps || pe < s){
		Segment current;
		return current;
	} // does not intersect
	if (s <= ps && pe <= e){
		return tree[p]; // fully contained
	}
	int pm = (ps + pe) / 2;
	auto l = query(s, e, ps, pm, 2*p);
	auto r = query(s, e, pm+1, pe, 2*p+1);

	if (e <= pm) // half contained
		return l;
	if (s >= pm+1) // half contained
		return r;

	Segment current;
	current.s = mergePath(l.s, r.f);
	current.m = minPath( minPath(
					mergePath(l.e, r.f, M),
					mergePath(l.f, r.s, M)), minPath(
					mergePath(l.f, r.m, M),
					mergePath(l.m, r.f, M)));
	current.e = mergePath(l.f, r.e);
	current.f = mergePath(l.f, r.f);

	return current;
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
		Point p;
		std::cin >> p.x >> p.y;

		update(i, 1, n, 1, p);
	}



	Segment answer;

	for(int i = 0; i < m; i++){
		int I, J;
		Point p;
		char o;
		std::cin >> o;

		if(o == 'Q'){
			std::cin >> I >> J;
			answer = query(I, J, 1, n, 1);
			Path path = minPath(answer.f, answer.m);
			std::cout << path.distance << std::endl;
		} else {
			std::cin >> I >> p.x >> p.y;
			update(I, 1, n, 1, p);
		}
	}

	return 0;
}
