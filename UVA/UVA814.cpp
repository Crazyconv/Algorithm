#define LOCAL

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
map<string, set<string> > MTAs;
map<string, set<string> > recpset;
map<string, vector<string> > recpvec;
vector<string> order_MTA;
vector<string> message;

void print_code(int code){
	cout << "     " << code << endl;
}

void from(string sender, string mta){
	cout << "     MAIL FROM:<" << sender << "@" << mta << ">" << endl;
}

void to(string receiver, string mta){
	cout << "     RCPT TO:<" << receiver << "@" << mta << ">" << endl;
}

void parse(const string& email, string& user, string& mta){
	int sender_length = 0;
	while(email[sender_length] != '@'){
		sender_length ++;
	}
	user = string(email, 0, sender_length);
	mta = string(email, sender_length+1, email.length() - sender_length - 1);
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	// read MTA list
	string temp, mta, user;
	int user_num;
	cin >> temp;
	while(temp != "*"){
		cin >> mta >> user_num;
		for(int i = 0; i < user_num; i++){
			cin >> user;
			MTAs[mta].insert(user);
		}
		cin >> temp;
	}

	// read message
	cin >> temp;
	while(temp != "*"){
		order_MTA.clear();
		recpvec.clear();
		recpset.clear();
		message.clear();
		string sender, sender_mta, receiver, receiver_mta;
		
		//read sender
		parse(temp, sender, sender_mta);

		//read receiver
		cin >> temp;
		while(temp != "*"){
			parse(temp, receiver, receiver_mta);
			if(!recpset.count(receiver_mta))
				order_MTA.push_back(receiver_mta);
			if(!(recpset.count(receiver_mta) && recpset[receiver_mta].count(receiver)))
				recpvec[receiver_mta].push_back(receiver);
			recpset[receiver_mta].insert(receiver);
			cin >> temp;
		}

		getline(cin, temp);
		while(temp[0] != '*'){
			message.push_back(temp);
			getline(cin, temp);
		}

		for(int i = 0; i < order_MTA.size(); i++){
			bool data = false;
			receiver_mta = order_MTA[i];
			cout << "Connection between " << sender_mta << " and " << receiver_mta << endl;
			cout << "     HELO " << sender_mta << endl;
			print_code(250);
			from(sender, sender_mta);
			print_code(250);
			for(int j = 0; j < recpvec[receiver_mta].size(); j++){
				receiver = recpvec[receiver_mta][j];
				to(receiver, receiver_mta);
				if(MTAs[receiver_mta].count(receiver)){
					data = true;
					print_code(250);
				} else {
					print_code(550);
				}
			}
			if(data){
				cout << "     DATA" << endl;
				print_code(354);
				for(int j = 1; j < message.size(); j++){
					cout << "     " << message[j] << endl;
				}
				cout << "     ." << endl;
				print_code(250);
			}
			cout << "     QUIT" << endl;
			print_code(221);
		}

		cin >> temp;
	}

	return 0;
}
