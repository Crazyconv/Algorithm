#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int t_left[26], t_right[26];
string preord, inord;

void printtree(int root){
	if(root == -1)
		return;
	printtree(t_left[root]);
	printtree(t_right[root]);
	printf("%c", root+'A');
}

int findroot(char ch, int IS, int IE){
	for(int i = IS; i <= IE; i++){
		if(inord[i] == ch)
			return i;
	}
	return -1;
}

int build(int PS, int PE, int IS, int IE){
	if(PS > PE)
		return -1;
	int root = preord[PS] - 'A';
	int det = findroot(preord[PS], IS, IE);
	t_left[root] = build(PS+1, det-IS+PS, IS, det-1);
	t_right[root] = build(det-IS+PS+1, PE, det+1, IE);
	return root;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	string line;
	int root;
	while(getline(cin, line)){
		stringstream ss(line);
		ss >> preord >> inord;
		root = build(0, preord.length() - 1, 0, preord.length() - 1);
		printtree(root);
		printf("\n");
	}
	return 0;
}