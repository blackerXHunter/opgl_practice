#pragma once
namespace dsa {
	template<typename T>
	T max(const T& l, const T& r) {
		return l > r ? l : r;
	}
	template<typename T>
	T min(const T &l, const T &r) {
		return l < r ? r : l;
	}
}