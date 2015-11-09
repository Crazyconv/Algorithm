#define LOCAL

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <set>

using namespace std;

void permute(set<int> vertices[], int visit[], int *seq, int num, int cur, int bw, int *bestseq, int &best){
	if(cur == num){
		memcpy(bestseq, seq, sizeof(int)*num);
		best = bw;
		return;
	} 
	for(int i = 0; i < 26; i++){
		if(!visit[i] && !vertices[i].empty()){
			int temp_bw = bw, hit = 0;
			int ok = 1;
			for(int j = 0; j < cur; j++){
				if(vertices[i].count(seq[j])){
					hit++;
					if(cur-j >= best){
						ok = 0;
						break;
					}
					if(temp_bw < cur-j)
						temp_bw = cur-j;
				}
			}
			if(ok && vertices[i].size()-hit < best){
				seq[cur] = i;
				visit[i] = 1;
				permute(vertices, visit, seq, num, cur+1, temp_bw, bestseq, best);
				visit[i] = 0;
				if(bw >= best)
					break;
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	string line;
	while(getline(cin, line) && line[0]!='#'){
		set<int> vertices[26];
		int visit[26] = {0};
		int num=0, p=0, q=0, i=0, len=line.length();
		while(i<len){
			while(i<len && line[i]!=':')
				i++;
			p = i;
			while(i<len && line[i]!=';')
				i++;
			q = i;
			// printf("%d %d\n", p, q);
			for(int j=p+1; j<q; j++){
				vertices[line[p-1]-'A'].insert(line[j]-'A');
				vertices[line[j]-'A'].insert(line[p-1]-'A');
			}
		}
		for(i = 0; i < 26; i++){
			if(!vertices[i].empty())
				num++;
		}
		// for(i=0; i<26; i++){
		// 	if(!vertices[i].empty()){
		// 		printf("%c: ", i+'A');
		// 		for(set<int>::iterator it = vertices[i].begin(); it != vertices[i].end(); it++)
		// 			printf("%c", *it+'A');
		// 		printf("\n");
		// 	}
		// }

		int seq[num], bestseq[num];
		int best = 1000000;
		permute(vertices, visit, seq, num, 0, 0, bestseq, best);
		for(i = 0; i < num; i ++){
			printf("%c ", bestseq[i]+'A');
		}
		printf("-> %d\n", best);
	}
	return 0;
}


