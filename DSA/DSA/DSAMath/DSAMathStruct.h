#pragma once
#include <string>
#include <functional>
namespace dsa {
	class MathObject {
	public:
		virtual std::string to_string() const = 0;
	};

	class Number : public MathObject {

	};

	class Float : public Number {

	};

	class Integer : public Number {

	};

	class Operation : public MathObject {
	public:
		
	};

	class SingleOperation : public Operation {
	public:
		
	};
}