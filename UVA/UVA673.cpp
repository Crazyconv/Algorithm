#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	string temp;
	scanf("%d", &T);
	getline(cin, temp);
	while(T--){
		stack<char> seq;
		getline(cin, temp);
		bool fail = false;
		for(int i = 0; i < temp.length(); i++){
			if(temp[i] == '[' || temp[i] == '(')
				seq.push(temp[i]);
			else if(temp[i] == ']'){
				if(!seq.empty() && seq.top() == '[')
					seq.pop();
				else{
					fail = true;
					break;
				}
			} else if(temp[i] == ')'){
				if(!seq.empty() && seq.top() == '(')
					seq.pop();
				else {
					fail = true;
					break;
				}
			} else if(temp[i] != ' '){
				fail = true;
				break;
			}
		}
		if(!seq.empty())
			fail = true;
		if(fail)
			printf("No\n");
		else
			printf("Yes\n");
	}
	return 0;
}