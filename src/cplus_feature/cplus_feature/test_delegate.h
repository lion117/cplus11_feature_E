#pragma once
#include <string>
#include <iostream>
#include <functional>
using namespace std;



namespace Delegate{






class test_delegate
{
public:
	test_delegate();
	~test_delegate();

	std::string echo_delegate(string t_data)
	{
		cout << "delegate function : " << t_data << endl;
		return "echo : " + t_data;
	}

	static void main() 
	{





	}

};







string  echo_delegate(string t_data);
void test_main();



}