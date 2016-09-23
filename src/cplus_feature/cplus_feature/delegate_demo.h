#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>
using namespace std;



class Worker
{
public:
	Worker(string t_worker) { _work_name = t_worker;  cout << t_worker << "report" << endl; }
	void regOnProcess(function<void(string, int)> t_func) 
	{ 
		_dele_on_process = t_func; 
		cout << "accept task" << endl;;
	}
	void regOnComplete(function<void(string, string)> t_func) { _dele_on_complete = t_func; }

	~Worker(){}

	void startWork()
	{
		
			for (int i = 0; i < 10; i++)
			{
				_dele_on_process(_work_name, i);
				Sleep(1000);
			}
			string i_result = _work_name + " had complete task ";
			_dele_on_complete(_work_name, i_result);	
	}



private:
	function<void(string, int)> _dele_on_process;
	function<void(string, string)>	  _dele_on_complete;
	string _work_name;




};


class Boss
{
public:
	Boss(){}
	void onProcess(string t_worker, int t_percent)
	{
		cout << "report to boss: "<<t_worker << "   "<<t_percent<<endl;
	}
	void onComplete(string  t_worker, string t_result)
	{
		cout <<"report to boss: " << t_worker << t_result << endl;
	}
	void hireWorker()
	{
		Worker i_worker1("tom");
		Worker i_worker2("leo");
		_worker_list.push_back(i_worker1);
	}

	void assignTask()
	{

	}

	void makeMoney()
	{
		for (auto itor : _worker_list)
		{
			using std::placeholders::_1;
			using std::placeholders::_2;
			function<void(string, int)> i_process_task = std::bind(&Boss::onProcess, this, _1, _2);
			itor.regOnProcess(i_process_task);
			function<void(string, string)> i_result_task = std::bind(&Boss::onComplete, this, _1, _2);
			itor.regOnComplete(i_result_task);
			itor.startWork();
		}
	}


private:
	vector<Worker> _worker_list;

#pragma region MAIN
public:
	static void main()
	{
		Boss i_boss;
		i_boss.hireWorker();
		i_boss.assignTask();
		i_boss.makeMoney();

		system("pause");
	}
	

#pragma endregion MAIN


};

