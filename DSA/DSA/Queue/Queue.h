#pragma once
#include "../List/List.h"

namespace dsa {
	template <typename T>
	class Queue : public List<T> {
	public:
		void enqueue(const T& e) { insertTail(e); }
		T dequeue() { return remove(first()); }
		const T& front() { return first()->data(); }
	};
}