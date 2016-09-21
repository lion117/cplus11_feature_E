// Console_cpluse_extend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

#include "unit_test.h"
#include "test_promise2.h"
//#include "Poco/Tuple.h"
//using namespace Poco;

int main()
{
	//Tuple<int, int, string> i_tuple(1,5,"test");
	////i_tuple.set(1, 2, "test");
	////cout << i_tuple.get(0) << endl;
	// i_tuple->get();




	test_task();
	system("pause");
	return 0;
}