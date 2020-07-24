#pragma once

namespace dsa {
	template <typename T>
	class BinNode {
	public:
		BinNode(const T& e, BinNode<T> *p) :value(e), parent(p), left(nullptr), right(nullptr) {}

	public:
		BinNode<T> *left, *right, *parent;
		T value; int height; int size();
		BinNode<T> *insertAsLC(const T& e) {
			return left = new BinNode<T>(e, this);
		}
		BinNode<T> *insertAsRC(const T& e) {
			return right = new BinNode<T>(e, this);
		}

		template <typename Func>
		void preorder(Func f) {
			f(this);
			preorder(this->left);
			preorder(this->right);
		}
		template <typename Func>
		void inorder(Func f) {
			inorder(this->left);
			f(this);
			inorder(this->right);
		}
		template <typename Func>
		void postorder(Func f) {
			postorder(this->left);
			postorder(this->right);
			f(this);
		}
	};

	template<typename T>
	inline int BinNode<T>::size() {
		int s = 1;
		s += left->size();
		s += right->size();
		return s;
	}

}