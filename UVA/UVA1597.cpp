#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cctype>
#include <sstream>
#include <set>

using namespace std;

typedef map<string, map<int, set<int> > > Bulket;

struct IDD{
	int first;
	int second;
	IDD(){}
	IDD(int first, int second): first(first), second(second){}
	bool operator < (const IDD& id) const{
		if(this->first != id.first)
			return this->first < id.first;
		return this->second < id.second;
	}

	IDD operator = (const IDD& id) const{
		IDD m (id.first, id.second);
		return m;
	}
};

string error_m = "Sorry, I found nothing.\n";
string euqal_del = "==========\n";
string dash_del = "----------\n";

set<IDD> sunion(set<IDD> &s1, set<IDD> &s2){
	set<IDD> s(s1);
	for(set<IDD>::iterator i = s2.begin(); i != s2.end(); i++){
			s.insert(*i);
	}
	return s;
}

void process(string &line){
	for(int i = 0; i < line.length(); i ++){
		if(isalpha(line[i])){
			line[i] = tolower(line[i]);
		} else {
			line[i] = ' ';
		}
	}
}

set<IDD> check(const string &item, Bulket &bulket, vector<string> doc[], bool print){
	set<IDD> matches;
	map<int, set<int> > match_doc = bulket[item];
	bool first = true;
	for(map<int, set<int> >::iterator i = match_doc.begin(); i != match_doc.end(); i++){
		int did = i->first;
		set<int> lids = i->second;
		if(print){
			if(first)
				first = false;
			else
				cout << dash_del;
		}
		for(set<int>::iterator j = lids.begin(); j != lids.end(); j++){
			if(print){
				cout << doc[did][*j] << endl;
			} else {
				IDD m(did, *j);
				matches.insert(m);
			}
		}
	}
	return matches;
}

void printresult(const set<IDD>& matches, vector<string> doc[]){
	if(matches.size()==0)
		cout << error_m;
	else{
		int did = (matches.begin())->first;
		int c_did;
		for(set<IDD>::iterator i = matches.begin(); i != matches.end(); i++){
			c_did = i->first;
			if(c_did != did){
				cout << dash_del;
				did = c_did;
			}
			cout << doc[c_did][i->second] << endl;
		}
	}
}
void printresult_2(int did, const set<int> s1, const set<int> s2, vector<string> doc[], bool first){
	set<int> s(s1);
	for(set<int>::iterator i = s2.begin(); i != s2.end(); i++){
			s.insert(*i);
	}
	if(!first)
		cout << dash_del;
	for(set<int>::iterator i = s.begin(); i != s.end(); i++){
		cout << doc[did][*i] << endl;
	}
}
int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int dn, tn;
	scanf("%d", &dn);
	vector<string> doc[102];
	Bulket bulket;

	string line, term, temp;
	int li = 0;
	getline(cin, line);
	for(int di = 0; di < dn; di ++){
		li = 0;
		while(getline(cin, line) && line != "**********"){
			doc[di].push_back(line);
			process(line);
			stringstream ss(line);
			while(ss >> term){
				bulket[term][di].insert(li);
			}
			li++;
		}
	}

	// search
	scanf("%d", &tn);
	getline(cin, line);
	for(int i = 0; i < tn; i++){
		getline(cin, line);
		stringstream ss(line);
		if(line.find("T") != string::npos){
			ss >> temp >> term;
			bool notfound = (!bulket.count(term));
			bool first = true;
			int foundnum = 0;
			for(int j = 0; j < dn; j++){
				if(notfound || !bulket[term].count(j)){
					if(first)
						first = false;
					else
						cout << dash_del;
					for(int k = 0; k < doc[j].size(); k++)
						cout << doc[j][k] << endl;
				} else {
					foundnum ++;
				}
			}
			if(foundnum == dn)
				cout << error_m;
		} else if (line.find("A") != string::npos){
			string term2;
			ss >> term >> temp >> term2;
			bool found = false;
			bool first = true;
			if(bulket.count(term) && bulket.count(term2)){
				for(map<int, set<int> >::iterator mi = bulket[term].begin();
					mi != bulket[term].end(); mi++){
					if(bulket[term2].count(mi->first)){
						printresult_2(mi->first, mi->second, bulket[term2][mi->first], doc, first);
						found = true;
						first = false;
					}
				}
				if(!found)
					cout << error_m;
			} else{
				cout << error_m;
			}
		} else if(line.find('O') != string::npos){
			set<IDD> matches_1, matches_2;
			ss >> term >> temp;
			if(bulket.count(term)){
				matches_1 = check(term, bulket, doc, false);
			}
			ss >> term;
			if(bulket.count(term)){
				matches_2 = check(term, bulket, doc, false);
			}
			set<IDD> matches = sunion(matches_1, matches_2);
			printresult(matches, doc);
		} else {
			ss >> term;
			if(bulket.count(term)){
				check(term, bulket, doc, true);
			} else {
				cout << error_m;
			}
		}
		cout << euqal_del;
	}
	return 0;
}