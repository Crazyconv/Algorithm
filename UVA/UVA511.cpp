#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <map>
#include <sstream>
#include <set>

using namespace std;

const string err_detail = "no map at that detail level; using";
const string err_unknown = "unknown location";
const string err_location = "no map contains that location";

bool is_equal(double a, double b){
	if(fabs(a - b) <= 1E-6)
		return true;
	return false;
}

struct MAP{
	string name;
	double s_x, s_y, b_x, b_y;
	double relative_ratio, area;
	double relative_x, relative_y;
	double center_distance, right_low_distance;
	MAP(string name, double x1, double y1, double x2, double y2){
		this->name = name;
		s_x = (x1 > x2)? x2: x1;
		b_x = (x1 > x2)? x1: x2;
		s_y = (y1 > y2)? y2: y1;
		b_y = (y1 > y2)? y1: y2;
		relative_ratio = fabs((b_y - s_y) / (b_x - s_x) - 0.75);
		area = (b_y - s_y) * (b_x - s_x);
	}
	void relate_location(double x, double y){
		center_distance = pow(2 * x - s_x - b_x, 2) + pow(2 * y - s_y - b_y, 2);
		right_low_distance = pow(x - b_x, 2) + pow(y - s_y, 2);
	}
	bool operator < (const MAP& m) const{
		if(!is_equal(this->area, m.area))
			return this->area > m.area;
		if(!is_equal(this->center_distance, m.center_distance))
			return this->center_distance < m.center_distance;
		if(!is_equal(this->relative_ratio, m.relative_ratio))
			return this->relative_ratio < m.relative_ratio;
		if(!is_equal(this->right_low_distance, m.right_low_distance))
			return this->right_low_distance > m.right_low_distance;
		return this->s_x < m.s_x;
	}
	bool cover(const double x, const double y){
		return (s_x <= x && b_x >= x && s_y <= y && b_y >= y);
	}
};

bool is_euqal_MAP(const MAP& m1, const MAP& m2){
	if(is_equal(m1.area, m2.area))
		return true;
	else
		return false;
}

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	// assume MAPS -> LOCATIONS -> REQUESTS -> END
	string line, name;
	vector<MAP> maps;
	map<string, vector<MAP> > locations;
	double x1, y1, x2, y2;
	while(1){
		getline(cin, line);
		stringstream ss(line);
		if(ss >> name){
			if(name == "MAPS")
				break;
		}
	}
	while(1){
		getline(cin, line);
		// map info
		stringstream ss(line);

		if(ss >> name){
			if(name == "LOCATIONS")
				break;
			if(ss >> x1 >> y1 >> x2 >> y2){
				MAP m(name, x1, y1, x2, y2);
				maps.push_back(m);
			}
		}
	}
	while(1){
		getline(cin, line);
		// location info
		stringstream ss(line);
		if(ss >> name){
			if(name == "REQUESTS")
				break;
			if(ss >> x1 >> y1){
				vector<MAP> covering_map;
				for(int i = 0; i < maps.size(); i++){
					if(maps[i].cover(x1, y1)){
						maps[i].relate_location(x1, y1);
						covering_map.push_back(maps[i]);
					}
				}
				sort(covering_map.begin(), covering_map.end());
				unique(covering_map.begin(), covering_map.end(), is_euqal_MAP);
				locations[name] = covering_map;
			}
		}
	}
	while(1){
		getline(cin, line);
		// request
		int detail;
		stringstream ss(line);
		if(ss >> name){
			if(name == "END")
				break;
			if(ss >> detail){
				cout << name << " at detail level " << detail << " ";
				if(!locations.count(name)){
					// unknown
					cout << err_unknown << endl;
				} else if (!locations[name].size()){
					// no map
					cout << err_location << endl;
				} else if (detail > locations[name].size()){
					// detail too high
					cout << err_detail << " " << locations[name].back().name << endl;
				} else {
					cout << "using " << locations[name][detail-1].name << endl;
				}
			}
		}
	}
	return 0;
}