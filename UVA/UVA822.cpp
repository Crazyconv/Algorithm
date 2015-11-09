#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Topic{
	int id, n_remain, n_available, t_available, t_need, interval, n_remain_sche;
	Topic(){} 
	Topic(int id, int n_remain, int t_available, int t_need, int interval):
	id(id), n_remain(n_remain), t_available(t_available), t_need(t_need), interval(interval){
		n_available = 0;
		n_remain_sche = n_remain;
	}
};

struct Person{
	int seq, t_start, t_available, is_assigned, topic_assigned;
	vector<int> skills;
	Person(int seq, vector<int> skills): seq(seq), skills(skills){
		t_start = 0;
		t_available = 0;
		is_assigned = false;
		topic_assigned = -1;
	}
	bool operator < (const Person& p) const{
		if(this->t_start != p.t_start)
			return this->t_start < p.t_start;
		return this->seq < p.seq;
	}
};

void update(int &time1, const int time2){
	if(time1 == -1 || time1 > time2){
		time1 = time2;
		
	}
}

void remove_t(vector<int> &skills, const int n){
	vector<int>::iterator i;
	for(i = skills.begin(); i != skills.end(); i++){
		if(*i == n)
			break;
	}
	skills.erase(i);
}

void remove_p(vector<Person> &persons, const int n){
	vector<Person>::iterator i;
	for(i = persons.begin(); i != persons.end(); i++){
		if(i->seq == n)
			break;
	}
	persons.erase(i);
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int n;
	int s = 0;
	while(scanf("%d", &n) && n){
		s++;
		map<int, Topic> topics;
		vector<Person> persons;
		int tid, remain, start, need, interval, nt, pid;
		while(n--){
			scanf("%d %d %d %d %d", &tid, &remain, &start, &need, &interval);
			Topic t(tid, remain, start, need, interval);
			topics[tid] = t;
		}
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d %d", &pid, &nt);
			vector<int> skills;
			for(int j = 0; j < nt; j++){
				scanf("%d", &tid);
				skills.push_back(tid);
			}
			Person p(i, skills);
			persons.push_back(p);
		}
		int c_time = 0, next_time;
		nt = 20000;
		while(1){
			next_time = -1;
			for(map<int, Topic>::iterator i = topics.begin(); i != topics.end(); i++){
				Topic &t = i->second;
				while(c_time >= t.t_available && t.n_remain_sche > 0){
					t.n_remain_sche --;
					t.n_available ++;
					t.t_available += t.interval;
				}
			}
			sort(persons.begin(), persons.end());
			for(vector<Person>::iterator i = persons.begin(); i != persons.end(); i++){
				Person &p = *i;
				if(p.t_available <= c_time){
					p.is_assigned = false;
					for(int j = 0; j < p.skills.size(); j++){
						tid = p.skills[j];
						if(topics.count(tid) && topics[tid].n_available > 0){
							p.is_assigned = true;
							p.topic_assigned = tid;
							p.t_start = c_time;
							p.t_available = p.t_start + topics[tid].t_need;
							topics[tid].n_remain--;
							topics[tid].n_available--;
							break;
						}
					}
				}
			}
			vector<int> todelete, todelete_p;
			for(map<int, Topic>::iterator i = topics.begin(); i != topics.end(); i++){
				Topic &t = i->second;
				if(!t.n_remain)
					todelete.push_back(t.id);
			}
			for(int i = 0; i < todelete.size(); i++){
				topics.erase(todelete[i]);
			}
			if(topics.empty())
				break;
			for(vector<Person>::iterator i = persons.begin(); i != persons.end(); i++){
				Person &p = *i;
				if(p.is_assigned){
					update(next_time, p.t_available);
				}else{
					todelete.clear();
					for(int j = 0; j < p.skills.size(); j++){
						if(topics.count(p.skills[j]))
							update(next_time, topics[p.skills[j]].t_available);
						else
							todelete.push_back(p.skills[j]);
					}
					for(int j = 0; j < todelete.size(); j++){
						remove_t(p.skills, todelete[j]);
					}
					if(p.skills.empty())
						todelete_p.push_back(p.seq);
				}
			}
			for(int i = 0; i < todelete_p.size(); i++){
				remove_p(persons, todelete_p[i]);
			}
			c_time = next_time;
		}
		for(vector<Person>::iterator i = persons.begin(); i != persons.end(); i++){
			Person &p = *i;
			if(p.is_assigned)
				if(p.t_available > c_time)
					c_time = p.t_available;
		}
		printf("Scenario %d: All requests are serviced within %d minutes.\n", s, c_time);
	}
	return 0;
}
