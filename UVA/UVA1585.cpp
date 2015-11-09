#include <iostream>
using namespace std;
int main(){
	int T;
	cin >> T;
	for(int i = 0; i < T; i++){
		string score_s;
		cin >> score_s;
		int score = 0;
		int x_num = 1;
		for(int j = 0; j < score_s.length(); j++){
			if(score_s[j] == 'o' || score_s[j] == 'O'){
				score += x_num;
				x_num ++;
			} else {
				x_num = 1;
			}
		}
		cout << score << endl;
	}
	return 0;
}