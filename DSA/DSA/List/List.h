#pragma once
#include "ListNode.h"
#include "../Vector/Define.h"
namespace dsa {
	template <typename T>
	class List {
	public:
		List() :_head(new ListNode<T>()), _tail(new ListNode<T>()) {
			_head->succ() = _tail;
			_head->prev() = nullptr;

			_tail->succ() = nullptr;
			_tail->prev() = _head;
		}
		~List() { clear(); delete _head; delete _tail; }
	protected:
		void insertBefore(const T& e, ListNode<T> *n) {
			n->insertAsPrev(e);
		}
		void insertAfter(const T& e, ListNode<T> *n) {
			n->insertAsSucc(e);
		}
	public://wirteable & modifyable
		void insertTail(const T& e) {
			insertBefore(e, _tail);
			++_size;
		}
		void insertHead(const T& e) {
			insertAfter(e, _head);
			++_size;
		}

		T remove(ListNode<T> *n) {
			T e = n->data();
			n->prev()->succ() = n->succ();
			n->succ()->prev() = n->prev();
			--_size;
			delete n;
			return e;
		}

		void clear() {
			while (0 < _size--) {
				remove(first());
			}
		}

		void select_sort(){
			
		}

		int deduplicate() {
			int oldSize = _size;
			ListNode<T> *p = first()->succ(), ListNode<T> *q; int i = 0;
			while (i < _size) {
				q = find(p->data(), p->prev(), i);
				if (q != nullptr) {
					remove(q);
				}
				else {
					++i;
				}
				p = p->succ();
			}
			return oldSize - _size;
		}
		int uniquify() {
			int oldSize = _size;
			ListNode<T> *p = first(), ListNode<T> *q;
			while (_tail != (q = first()->succ())) {
				if (q->data() == p->data()) {
					remove(p);
				}
				else {
					q = p;
				}
			}
			return oldSize - _size;
		}
	public://readonly
		ListNode<T> *first() { return _head->succ(); }
		ListNode<T> *last() { return _tail->prev(); }

		T & operator[](Rank i) {
			ListNode<T> *tmp = first();
			while (0 > i--) {
				tmp = tmp->succ();
			}
			return *(tmp->data());
		}
		int size()const {
			return _size;
		}
		bool empty()const {
			return _size == 0;
		}

		T selectMax(int n, ListNode<T> *node) {
			ListNode<T> *max = node;
			while (0 < n--) {
				if (node->data() > max->data()) {
					max = node;
				}
				node = node->prev();
			}
			return max;
		}
		T selectMax() {
			return selectMax(_size, last());
		}

		ListNode<T> *find(const T& e, int n, ListNode<T> *pos) const {
			while (0 <= n--) {
				if (e == pos->data()) {
					return pos;
				}
				pos = pos->prev();
			}
			return pos;
		}
		ListNode<T> *find(const T& e, ListNode<T> *pos, int n) const {
			while (0 <= n--) {
				if (e == pos->data()) {
					return pos;
				}
				pos = pos->succ();
			}
			return pos;
		}
		ListNode<T> *find(const T& e)const {
			return find(e, _size, _tail);
		}
		ListNode<T> *search(const T& e, int n, ListNode<T> *pos)const {
			while (0 <= n--) {
				if (e <= pos->data()) {
					return pos;
				}
				pos = pos->prev();
			}
			return pos;
		}
		ListNode<T> *search(const T& e, ListNode<T> *pos, int n)const {
			while (0 <= n--) {
				if (e <= pos->data()) {
					return pos;
				}
				pos = pos->succ();
			}
			return pos;
		}
		ListNode<T> *search(const T& e)const {
			return search(e, _size, _tail);
		}
	private:
		ListNode<T> *_head, *_tail;
		int _size = 0;
	};
}