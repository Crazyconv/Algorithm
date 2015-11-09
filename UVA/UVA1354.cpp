#define LOCAL

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


#define maxn (1<<6)

struct Tree{
	double L, R;
	Tree(): L(0), R(0){}
};

double sum[maxn]; 
int visit[maxn];
vector<Tree> tree[maxn];
double r;

void dfs(int subset){
	if(visit[subset])
		return;
	visit[subset] = 1;
	bool havechildren = false;
	for(int left = (subset-1)&subset; left; left = (left-1)&subset){
		havechildren = true;
		int right = left^subset;
		dfs(left); dfs(right);

		double dleft = sum[right] / sum[subset];
		double dright = sum[left] / sum[subset]; 
		for(int i = 0; i < tree[left].size(); i++){
			for(int j = 0; j < tree[right].size(); j++){
				Tree t;
				t.L = max(tree[left][i].L + dleft, tree[right][j].L - dright);
				t.R = max(tree[left][i].R - dleft, tree[right][j].R + dright);
				if(t.L + t.R < r)
					tree[subset].push_back(t);
			}
		}
	}
	if(!havechildren)
		tree[subset].push_back(Tree());
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%lf%d", &r, &n);
		int weight[n];
		for(int i = 0; i < n; i++){
			scanf("%d", weight+i);
		}

		// calculate the sum of all subset
		for(int i = 0; i < (1<<n); i++){
			sum[i] = 0;
			tree[i].clear();
			for(int j = 0; j < n; j++){
				if(i&(1<<j))
					sum[i] += weight[j];
			}
		}

		memset(visit, 0, sizeof(visit));
		int root = (1<<n) - 1;
		dfs(root);
		double ans = 0;
		bool find = false;
		for(int i = 0; i < tree[root].size(); i++){
			find = true;
			double temp = tree[root][i].L + tree[root][i].R;
			if(temp > ans)
				ans = temp;
		}
		if(find)
			printf("%.10lf\n", ans);
		else
			printf("-1\n");
	}
	return 0;
}