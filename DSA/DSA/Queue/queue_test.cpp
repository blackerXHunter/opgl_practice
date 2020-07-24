#include "Queue.h"
int main() {
	dsa::Queue<int> q;
	q.enqueue(10);
	q.front();
	q.dequeue();
	return 0;
}