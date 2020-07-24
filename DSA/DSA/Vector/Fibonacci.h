#pragma once
namespace dsa {
	class Fib {
	public:
		Fib(int n) :g(1), f(0) { while (g < n) next(); }
		int get() { return g; }
		int next() { g += f; f = g - f; return g; }
		int prev() { f = g - f; g -= f; return g; }
	private:
		int g, f;
	};
}