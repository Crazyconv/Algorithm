#define LOCAL

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cctype>
#include <cmath>
using namespace std;

struct player{
	char name[21];
	int score[4];
	int round_num;
	int total;
	bool amateur;
};

vector<player> player_v;

bool isamateur(char name[], int length){
	for(int i = length-1; i >= 0; i--){
		if(!isspace(name[i])){
			if(name[i] == '*')
				return true;
			else
				return false;
		}
	}
	return false;
}

void print_player(player p){
	printf("%s", p.name);
	for(int i = 0; i < p.round_num; i++){
		printf("%3d", p.score[i]);
	}
	printf(" %3d", p.total);
	printf("\n");
}

void print_player_vector(vector<player> player_v, int num){
	for(int i = 0; i < num; i++){
		print_player(player_v[i]);
	}
}

bool cmp1(const player& p1, const player& p2){
	if(p1.round_num < 2)
		return false;
	if(p2.round_num < 2)
		return true;
	if(p1.total < p2.total)
		return true;
	else
		return false;
}

bool cmp2(const player& p1, const player& p2){
	if(p1.round_num != p2.round_num)
		return p1.round_num > p2.round_num;
	if(p1.total != p2.total)
		return p1.total < p2.total;
	else
		return strcmp(p1.name, p2.name)<0;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output2.out", "w", stdout);
#endif
	int case_num;
	scanf("%d", &case_num);
	while(case_num--){
		printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
		printf("-----------------------------------------------------------------------\n");
		
		player_v.clear();
		double prize;
		double partition[70];
		int player_num;
		int eligible_num = 0;

		scanf("%lf", &prize);
		for(int i = 0; i < 70; i++){
			scanf("%lf", partition+i);
		}
		scanf("%d", &player_num);
		getchar();

		for(int i = 0; i < player_num; i ++){
			player p;
			p.amateur = false;

			char line[100];
			fgets(line, 100, stdin);
			for(int k = 0; k < 20; k++){
				p.name[k] = line[k];
			}
			p.name[20] = '\0';
			p.amateur = isamateur(p.name, 20);
			// scores
			int round_num = 0;
			while(round_num < 4){
				char T[5];
				for(int k = 0; k < 3; k++){
					T[k] = line[round_num * 3 + 20 + k];
				}
				T[3] = '\0';
				if(!sscanf(T, "%d", &(p.score[round_num]))){
					break;
				}
				round_num ++;
			}

			// total and round
			p.round_num = round_num;
			p.total = 0;

			// calculate only the first two round
			if(round_num >= 2)
				eligible_num ++;

			for(int k = 0; k < round_num && k < 2; k++){
				p.total += p.score[k];
			}

			player_v.push_back(p);
		}

		sort(player_v.begin(), player_v.end(), cmp1);
		// print_player_vector(player_v, player_v.size());
		// printf("\n");

		int cut_num;
		if(eligible_num > 70){
			cut_num = 70;
			while(cut_num < eligible_num){
				if(player_v[cut_num - 1].total == player_v[cut_num].total)
					cut_num++;
				else
					break;
			}
		} else{
			cut_num = eligible_num;
		}

		for(int i = 0; i < cut_num; i++){
			if(player_v[i].round_num > 2)
				player_v[i].total += player_v[i].score[2];
			if(player_v[i].round_num > 3)
				player_v[i].total += player_v[i].score[3];
		}

		sort(player_v.begin(), player_v.begin()+cut_num, cmp2);
		// print_player_vector(player_v, cut_num);

		// irank: current/next internal ranking
		// itie: number of tie in this irank
		// index: current external ranking
		// otie: number of tie in external
		int irank = 0, itie = 0, index=0, otie = 0;
		double subprize = -1.0;
		while(index < cut_num){
			// when total == 0, break; print in the outer 
			if(player_v[index].round_num != 4)
				break;

			otie = 1;
			itie = (player_v[index].amateur)? 0:1;
			while(index+otie < cut_num && player_v[index].total == player_v[index+otie].total){
				if(!player_v[index+otie].amateur)
					itie ++;
				otie++;
			}

			if(itie == 0)
				subprize = -1.0;
			else{
				subprize = 0.0;
				for(int i = irank; i < irank + itie && i < 70; i++){
					subprize += partition[i];
				}
				subprize /= itie;
			}
			for(int i = index; i < index + otie; i++){
				char rankstring[10] = {0};
				printf("%s ", player_v[i].name);
				if(itie > 1 && !player_v[i].amateur && irank < 70){
					sprintf(rankstring, "%dT", index+1);
					printf("%-10s", rankstring);
				} else {
					printf("%-10d", index+1);
				}
				printf("%-5d%-5d%-5d%-5d", player_v[i].score[0], player_v[i].score[1],
					player_v[i].score[2], player_v[i].score[3]);
				if(player_v[i].amateur || irank >= 70)
					printf("%d\n", player_v[i].total);
				else
					printf("%-10d$%9.2lf\n", player_v[i].total, subprize * prize / 100);
			}
			irank += itie;
			index += otie;
		}
		for(int i = index; i < cut_num; i++){
			printf("%s ", player_v[i].name);
			printf("          ");
			for(int k = 0; k < 4; k++){
				if(k < player_v[i].round_num)
					printf("%-5d", player_v[i].score[k]);
				else
					printf("     ");
			}
			printf("DQ\n");
		}


		if(case_num){
			printf("\n");
		}
	}
	return 0;
}

