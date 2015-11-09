#define LOCAL

#include <stdio.h>
#include <string.h>
int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	return 0;
}



#define LOCAL

#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main(){
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	return 0;
}