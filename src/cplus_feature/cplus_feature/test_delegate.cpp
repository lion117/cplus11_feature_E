#include "stdafx.h"
#include "test_delegate.h"

namespace Delegate {











	std::string echo_delegate(string t_data)
	{
		cout << "delegate function : " << t_data << endl;
		return "echo : " + t_data;
	}

	void test_main()
	{
		std::function<string(string)> i_func_ptr;
		i_func_ptr = echo_delegate;
		cout << "run delegate functon " << i_func_ptr("this is test delegate demo ") << endl;
	}


}