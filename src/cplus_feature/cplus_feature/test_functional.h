#pragma once
#include <functional>
#include <iostream>

namespace Functional{





struct Foo {
	Foo(int num) : num_(num) {}
	void print_add(int i) const { std::cout << num_ + i << '\n'; }
	int num_;
};


void print_num(int i);

struct PrintNum {

	void operator()(int i) const
	{
		std::cout << i << '\n';
	}
};



 void main();



}
