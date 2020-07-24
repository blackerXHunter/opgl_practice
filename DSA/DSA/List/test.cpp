#include "List.h"
#include <iostream>
using namespace std;
int main() {
	dsa::List<int> l;
	l.insertHead(10);
	l.insertHead(20);
	cout << l.empty();
	cout << l.size() << " " << l.remove(l.last()) << " " ;
	cout << l.size();
	getchar();
	return 0;
}