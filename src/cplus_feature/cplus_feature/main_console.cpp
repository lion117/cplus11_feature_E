// Console_cpluse_extend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

#include "test_delegate.h"
#include "test_functional.h"

int _tmain(int argc, _TCHAR* argv[])
{

	Delegate::test_main();
	Functional::main();

	Delegate::DeleManager::main();

	system("pause");
	return 0;
}
