#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	vector<string> lines[1000];
	int maxlength[180];

	string line, word;
	int line_num = 0, word_num = 0;
	while(getline(cin, line)){
		stringstream ss(line);
		word_num = 0;
		while(ss >> word){
			if(maxlength[word_num] < word.length())
				maxlength[word_num] = word.length();
			lines[line_num].push_back(word);
			word_num ++;
		}
		line_num++;
	}

	char format[20];
	for(int i = 0; i < line_num; i++){
		for(int j = 0; j < lines[i].size(); j++){
			cout << lines[i][j];
			if(j != lines[i].size() - 1)
				for(int k = 0; k <= maxlength[j] - lines[i][j].length(); k++)
					cout << " ";
			else
				cout << endl;
		}
	}

	return 0;
}