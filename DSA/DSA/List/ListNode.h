#pragma once
namespace dsa {
template <typename T>
class ListNode {
public:
	ListNode(){}
	ListNode(T e, ListNode<T> *prev = nullptr, ListNode<T> *succ = nullptr):
		_data(e), _prev(prev), _succ(succ){}
public://writeable
	void set_data(T e) { _data = e; }
	ListNode<T> *insertAsPrev(const T &e);
	ListNode<T> *insertAsSucc(const T &e);
public://readonly
	const T& data()const { return _data; }
	ListNode<T>* &prev() { return _prev; }
	ListNode<T>* &succ() { return _succ; }
private:
	T _data;
	ListNode<T> *_prev, *_succ;
};


template<typename T>
inline ListNode<T>* ListNode<T>::insertAsPrev(const T & e) {
	ListNode<T> *newNode = new ListNode<T>(e, _prev, this);
	_prev->_succ = newNode;
	_prev = newNode;
	return newNode;
}
template<typename T>
inline ListNode<T>* ListNode<T>::insertAsSucc(const T & e) {
	ListNode<T> *newNode = new ListNode<T>(e, this, _succ);
	_succ->_prev = newNode;
	_succ = newNode;
	return newNode;
}


}