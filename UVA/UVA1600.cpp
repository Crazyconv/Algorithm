#define LOCAL

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <utility>

using namespace std;

struct Vir_Sq{
	int row, col, n_obs;
	Vir_Sq(int r, int c, int n): row(r), col(c), n_obs(n){}
};

int mo[4][2] = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	while(T--){
		int m, n, k;
		scanf("%d %d %d", &m, &n, &k);
		int s[m][n], d[m][n][k+1];
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &s[i][j]);
			}
		}

		memset(d, -1, sizeof(d));
		d[0][0][0] = 0;
		queue<Vir_Sq> squares;
		Vir_Sq vs0(0,0,0);
		squares.push(vs0);
		while(!squares.empty()){
			bool innerfind = false;
			vs0 = squares.front();
			squares.pop();
			for(int i = 0; i < 4; i++){
				int row = vs0.row + mo[i][0], col = vs0.col + mo[i][1];
				if(row >= 0 && row < m && col >= 0 && col < n){
					if(s[row][col]){
						//obs
						if(vs0.n_obs < k){
							if(d[row][col][vs0.n_obs + 1] == -1){
								d[row][col][vs0.n_obs + 1] = d[vs0.row][vs0.col][vs0.n_obs] + 1;
								Vir_Sq vs1(row, col, vs0.n_obs+1);
								squares.push(vs1);
							}
						}
					} else {
						//free
						if(d[row][col][0] == -1){
							d[row][col][0] = d[vs0.row][vs0.col][vs0.n_obs] + 1;
							if(row == m-1 && col == n-1){
								innerfind = true;
								break;
							}else{
								Vir_Sq vs1(row, col, 0);
								squares.push(vs1);
							}
						}
					}

				}
			}
			if(innerfind)
				break;
		}
		printf("%d\n", d[m-1][n-1][0]);
	}
	return 0;
}