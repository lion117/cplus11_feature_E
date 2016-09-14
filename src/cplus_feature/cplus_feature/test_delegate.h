#pragma once
#include <string>
#include <iostream>
#include <functional>
#include <vector>
using namespace std;



namespace Delegate{








class IObj
{
public:
	virtual int callback(string t_data) = 0;
};


class AppleObj : public IObj
{

public:
	virtual int callback(string t_data) final
	{
		cout << "this is  appleobj : "<<endl;
		return 0;
	}
};


class BananaObj : public IObj
{
public:
	virtual int callback( string t_data) final
	{	
		cout << "this is  banana object: " << endl;
		return 1;	
	}
};



class DeleManager
{
public:
	DeleManager() {};
	~DeleManager() {};
	void addObj(function<int(string)> t_dele)
	{
		_dele_list.push_back(t_dele);
	}

	void notify(string t_msg)
	{
		if (_dele_list.empty())
		{
			cout << "list is empty " << endl;
			return;
		}

		for (auto itor : _dele_list)
		{
			itor(t_msg);
		}
	}

private:
	vector <function<int(string)>> _dele_list;

#pragma region MAIN
public:
	static void main()
	{
		DeleManager i_manager;
		AppleObj i_apple;
		BananaObj i_banana;


		using std::placeholders::_1;

		std::function<int(string)> i_dele_apple = std::bind(&AppleObj::callback, i_apple, _1);
		i_manager.addObj(i_dele_apple);
		std::function<int(string)> i_dele_banana = std::bind(&BananaObj::callback, i_banana, _1);
		i_manager.addObj(i_dele_banana);

		i_manager.notify("happy middle september day");
	}


#pragma endregion MAIN

};






}