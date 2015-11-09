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
	int remaining, next_start_time, needed_time, interval;
	Topic(int remaining, next_start_time, needed_time, interval):
		remaining(remaining), next_start_time(next_start_time),
		needed_time(needed_time), interval(interval){}
};

struct Person{
	int id, seq, last_start_time, expected_end_time;
	vector<int> fields;
	Person(int id, int seq, vector<int> fields): id(id), seq(seq), fields(fields){
		last_start_time = 0;
		expected_end_time = 0;
	}
	bool operator < (const Person& p) const{
		return this->expected_end_time < p.expected_end_time;
	}
};

void get_request(map<int, Topic>& topics, int &c_time, list<int>& available_request){
	int s_time = c_time;
	for(auto const &m1: topics){
		if(m1.second.next_start_time <= c_time){
			available_request.push_back(m1.first);
		} else if (m1.second.next_start_time <= s_time){
			s_time = m1.second.next_start_time;
		}
	}
	if(available_request.empty())
		c_time = s_time;
}

void get_person(map<int, Person>& persons, int &c_time, list<int>& available_person){
	int s_time = c_time;
	for(auto const &m1: persons){
		if(m1.second.expected_end_time <= c_time){
			available_person.push_back(m1.first);
		} else if (m1.second.expected_end_time <= s_time){
			s_time = m1.second.expected_end_time;
		}
	}
	if(available_person.empty())
		c_time = s_time;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	int n_topic, n_person;
	int t_id, n_quest, start_time, needed_time, interval;
	int p_id;
	map<int, Topic> topics;
	map<int, Person> persons;
	while(scanf("%d", &n_topic) && n_topic){
		for(int i = 0; i < n_topic; i++){
			scanf("%d %d %d %d %d", &t_id, &n_quest, 
				&start_time, &needed_time, &interval);
			Topic t(n_quest, start_time, needed_time, interval);
			topics[t_id] = t;
		}
		scanf("%d", &n_person);
		for(int i = 0; i < n_person; i++){
			scanf("%d %d", &p_id, n_quest);
			vector<int> skills;
			for(int j = 0; j < n_quest; j++){
				scanf("%d", &t_id);
				skills.push_back(t_id);
			}
			Person p(p_id, i, skills);
			persons[p_id] = p;
		}

		//process
		int c_time = 0;
		while(!topics.empty()){
			int temp_time = c_time;
			list<int> available_request;
			list<int> available_person;
			get_request(topics, c_time, available_request);
			get_person(persons, temp_time, available_person);
			if(c_time < temp_time){
				c_time = temp_time;
				available_request.clear();
				get_request(topics, c_time, available_request);
			} else if(c_time > temp_time){
				available_person.clear();
				get_person(persons, c_time, available_person);
			}

			while(!available_person.empty()){
				Person p1 = persons[available_person.front()];
				vector<Person> temp_persons;
				for(auto &i: available_person){
					if(i.fields.)
				}
			}
			// update c_time
		}
	}
	return 0;
}

// time = 0;
next_available_time
for each topic:
	while(next_available_time < time){
		available_num ++;
		nexe_available_time + interval;
	}
	for each worker:
		if(nexe_available_time <= time)
			for each job in the priority list:
				if(job.available_num > 0){
					job.available_num --;
					worker.next_available_time = time + need_time;
				}
