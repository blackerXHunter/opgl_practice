#pragma once
#include "BinNode.h"
#include "../DSAMath/DSAUtility.h"
namespace dsa {
	template <typename T>
	class BinTree{
	protected:
		BinNode<T> *_root;
		int _size;int _height;
		
		int stature(BinNode<T> *node) {
			return (node == nullptr ? -1 : node->height);
		}
	public:
		int size()const { return _size; }
		int height()const { return _height; }
		BinNode<T> *root()const { return _root; }

		BinNode<T> *insertAsRC(BinNode<T> *node, const T &e) {
			++_size;
			node->insertAsRC(e);
			updateHeightAbove(node);
			return node->right;
		}
		BinNode<T> *insertAsLC(BinNode<T> *node, const T &e) {
			++_size;
			node->insertAsLC(e);
			updateHeightAbove(node);
			return node->left;
		}

		virtual int updateHeight(BinNode<T> *node);

		void updateHeightAbove(BinNode<T> *node) {
			while (node != nullptr) {
				updateHeight(node); node = node->parent;
			}
		}
	};
	template<typename T>
	inline int BinTree<T>::updateHeight(BinNode<T> *node) {
		return node->height = 1 + max(stature(node->left), stature(node->right));
	}
}