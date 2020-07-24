#include "Vector.h"
#include <algorithm>
#include <iostream>
template<typename T>
void PrintAll(dsa::Vector<T>& c) {
	c.travese([](int i) {std::cout << i << " "; });
}
int main() {
	dsa::Vector<int> vec;
	vec.insert(0, 4);
	vec.insert(0, 5);
	vec.insert(0, 3);
	vec.insert(0, 9);
	vec.insert(0, 1);
	vec.insert(0, 6);
	vec.put(0, 5);
	std::cout << vec.fibSearch(4, 0, vec.size()) << std::endl;
	PrintAll(vec);
	return 0;
}