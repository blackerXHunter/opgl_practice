#pragma once
#include "Define.h"
#include "Fibonacci.h"
#include <algorithm>
#include <functional>
namespace dsa {
	template <typename T>
	class Vector {
	public:
		Vector(size_t c = Default_Init_Size) {
			_elements = new T[_cap = c]; _size = 0;
		}
		Vector(const Vector<T>& oth) {
			copyFrom(oth._elements, 0, oth.size());
		}
		virtual ~Vector() {
			delete[] _elements;
		}

	public:
		T& operator [](Rank r) { return _elements[r]; }
		const T& operator[](Rank r)const { return _elements[r]; }
		Vector<T> &operator =(const Vector<T>& oth) {
			if (this != &oth) {
				copyFrom(oth._elements, 0, oth.size());
			}
			return *this;
		}
	public:
		size_t capacity()const {
			return _cap;
		}
		size_t size()const {
			return _size;
		}

		const T& get(Rank r) const {
			if (r < _size) {
				return _elements[r];
			}
		}

		virtual void put(Rank r, const T& ele) {
			if (r < _size) {
				_elements[r] = ele;
			}
		}

		virtual void insert(Rank r, const T& ele) {
			if (r <= _size) {
				++_size;
				for (Rank i = _size - 1; i > r; --i) {
					_elements[i] = _elements[i - 1];
				}
				_elements[r] = ele;
				expand();
			}
		}

		virtual T remove(Rank r) {
			T e = _elements[r];
			remove(r, r + 1);
			return e;
		}
		virtual int remove(Rank lo, Rank hi) {
			if (hi <= lo) {
				return 0;
			}
			while (hi < _size) {
				_elements[lo++] = _elements[hi++];
			}
			_size = lo;
			return hi - lo;
		}

		int disordered() {//查看有多少个相邻逆序对
			for (size_t i = 1; i < _size; ++i) {
				int c = 0;
				if (_elements[i - 1] > _elements[i]) {
					c++;
				}
			}
			reutrn c;
		}

		int find(const T& t) const {
			if (_size > 0) {
				return find(t, 0, _size);
			}
			else {
				return -1;
			}
		}

		int find(const T& t, Rank lo, Rank hi) const {//无序查找算法
			while (lo < hi-- && t != _elements[hi]);
			return hi;
		}

		template <typename TrFunc>
		void travese(TrFunc &visit) {
			for (Rank i = 0; i < _size; ++i) {
				visit(_elements[i]);
			}
		}

		//排序

		//气泡排序
		Rank bubble(Rank lo, Rank hi) {
			Rank last = lo;
			while (++lo < hi) {
				if (_elements[lo - 1] > _elements[lo]) {
					last = lo;
					std::swap(_elements[lo - 1], _elements[lo]);
				}
			}
			return last;
		}
		void bubble_sort() {
			Rank lo = 0, hi = size();
			while (lo < (hi = bubble(lo, hi))) {
				//pass
			}
		}
		//归并排序
		void merge_sort() {
			merge_sort_implement(0, _size);
		}
		void merge_sort_implement(Rank lo, Rank hi) {
			if (hi <= lo) {
				return lo;
			}
			Rank mi = (lo + hi) >> 1;
			merge_sort_implement(lo, mi);
			merge_sort_implement(mi, hi);

			merge(lo, mi, mi, hi);
		}
		void merge(Rank leftLo, Rank leftHi, Rank rightLo, Rank rightHi) {
			int i = std::min(leftLo, rightLo);
			while (leftLo < leftHi && rightLo < rightHi) {
				if (_elements[leftLo] < _elements[rightLo]) {
					_elements[i++] = _elements[leftLo++];
				}
				else {
					_elements[i++] = _elements[rightLo++];
				}
			}
			while (leftLo < leftHi) {
				_elements[i++] = _elements[leftLo++];
			}
			while (rightLo < rightHi) {
				_elements[i++] = _elements[rightLo++];
			}
		}
		void sort() {

		}

		//搜索
		Rank binSearch(const T& ele, Rank lo, Rank hi)const { // 有序查找
			while (lo < hi) {
				Rank mi = (lo + hi) >> 1;
				if (ele < _elements[mi]) {
					hi = mi;
				}
				else if (_elements[mi] < ele) {
					lo = mi + 1;
				}
			}
			return --lo;
		}
		Rank fibSearch(const T& ele, Rank lo, Rank hi)const {// 有序查找
			Fib fib(hi - lo);
			while (lo < hi) {
				while (hi - lo < fib.get()) {
					fib.prev();
				}
				Rank mi = lo + fib.get() - 1;
				if (ele < _elements[mi]) {
					hi = mi;
				}
				else if (_elements[mi] < ele) {
					lo = mi + 1;
				}
			}
			return --lo;
		}
		Rank search(const T& ele) const {
			return rand() % 2 ? binSearch(ele, 0, _size) : fibSearch(ele, 0, _size);
		}


		//唯一化
		int deduplicate() {//无序版本的去重操作
			int oldSize = _size;
			for (size_t i = 1; i < _size;) {
				if (find(_elements[i], 0, i) < 0) {
					i++;
				}
				else {
					remove(i);
				}
			}
			return oldSize - _size;
		}
		int uniquify() {//有序版本的去重操作
			if (_size > 1) {
				int i = 0, j = 1;
				while (j < _size) {
					if (_elements[i] != _elements[j]) {
						_elements[++i] = _elements[j];
					}
					else {
						j++;
					}
				}
				int cc = _size - i + 1;
				_size = ++i;
				return cc;
			}
			return 0;
		}
	private:
		T *_elements;
		int _size, _cap;
		void copyFrom(T* const A, Rank lo, Rank hi) {//拷贝
			_elements = new T[_cap = 2 * (hi - lo)];
			_size = 0;
			while (lo < hi) {
				_elements[_size++] = A[lo++];
			}
		}
		void expand() {//数组扩张
			if (_size < _cap) {
				return;
			}
			int expSize = std::max(_cap, Default_Init_Size);
			T *old_ele = _elements; _elements = new T[_cap = 2 * expSize];
			for (int i = 0; i < _size; ++i) {
				_elements[i] = old_ele[i];
			}
			delete[] old_ele;
		}
		void shirk() {//数组缩减

		}
	};

}