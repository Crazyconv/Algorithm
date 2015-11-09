#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cstring>
#include <cstdlib>

using namespace std;

struct info{
	int length;
	map<int, int> values;
	info(int length): length(length){}
	info(){}
};

void parse_d(const string& line, map<string, info> &arrays){
	size_t left = line.find("[");
	size_t right = line.find("]");
	string key = line.substr(0, left);
	string value_s = line.substr(left+1, right - left - 1);
	int value = atoi(value_s.c_str());
	info in(value);
	arrays[key] = in;
}

bool parse_a(const string& line, map<string, info> &arrays){
	size_t last = string::npos;
	size_t found;
	int assignment;
	bool rightmost = true;
	string item;
	bool end = false;
	while(1){
		found = line.rfind("=", last);
		if(found == string::npos){
			item = line.substr(0, last + 1);
			end = true;
		}
		if(last == string::npos)
			item = line.substr(found+1);
		else
			item = line.substr(found+1, last - found);
		// the rightmost may be a number
		if(isdigit(item[0])){
			assignment = atoi(item.c_str());
			rightmost = false;
		} else {
			stack<string> keystack;
			size_t start = 0, innerfound, temp;
			int nextindex = -2;
			string key;
			while((innerfound = item.find("[", start)) != string::npos){
				keystack.push(item.substr(start, innerfound - start));
				start = innerfound + 1;
			}
			while(!keystack.empty()){
				key = keystack.top();
				keystack.pop();
				if(nextindex == -2){
					// innermost
					temp = item.find("]", start);
					nextindex = atoi((item.substr(start, temp - start)).c_str());
				}
				if(nextindex >= arrays[key].length)
					return false;
				if(keystack.empty() && !rightmost){
					arrays[key].values[nextindex] = assignment;
				} else if(arrays[key].values.count(nextindex))
					nextindex = arrays[key].values[nextindex];
				else{
					return false;
				}
			}
			if(rightmost){
				rightmost = false;
				assignment = nextindex;
			}
		}

		last = found - 1;
		if(end)
			break;
	}
	return true;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	string line;
	while(cin >> line && line[0]!='.'){
		bool bug = false;
		int bugline = 0;
		map<string, info> arrays;
		size_t found;
		while(1){
			if(line[0]=='.'){
				if(bug)
					printf("%d\n", bugline);
				else
					printf("0\n");
				break;
			}else{
				if(!bug){
					found = line.find("=");
					if(found == string::npos){
						parse_d(line, arrays);
					} else {
						if(!parse_a(line, arrays)){
							bug = true;
						}
					}
					bugline ++;
				}
				cin >> line;
			}
		}
	}
	return 0;
}