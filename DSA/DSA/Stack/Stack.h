#pragma once
#include "../Vector/Vector.h"
namespace dsa {
	template <typename T>
	class Stack :public Vector<T> {
	public:
		void Push(const T& e) {
			this->insert(size(), e);
		}
		T Pop() {
			return this->remove(size() - 1);
		}
		const T& top()const {
			return (*this)[size() - 1];
		}
	};
}