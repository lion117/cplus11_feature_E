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
	Worker(string t_worker) 
	{
		_work_name = t_worker;  
		cout << t_worker << " create " << endl; 
	}
	~Worker() {}
	void regOnProcess(function<void(const string&, const  int& )> t_func) 
	{ 
		cout << _work_name << "  accept regOnProcess from boss " << endl;
		_dele_on_process = t_func; 
	}
	void regOnComplete(function<void(const string& , const string&)> t_func) 
	{ 
		cout << _work_name << "  accept regOnComplete from boss " << endl;
		_dele_on_complete = t_func; 
	}
	

	void startAsynicWork()
	{
		auto i_func = [&] {
			for (int i = 0; i < 10; i++)
			{
				if (_dele_on_process._Empty())
				{
					cout<< "delegate functon be null"<<endl;
					return;
				}	
				_dele_on_process(_work_name, i);
				Sleep(1000);	
			}
			if (!_dele_on_complete._Empty())
			{
				string i_result = "  Mission had been completed by : "+ _work_name;
				_dele_on_complete(_work_name, i_result);
			}	
		};
		std::thread i_thread(i_func);
		i_thread.detach();			
	}
private:
	function<void(const string & , const int&)>		  _dele_on_process;
	function<void(const string &, const string&)>	  _dele_on_complete;
	string _work_name;
};

class Boss
{
public:
	Boss() {}
	void onProcess(string t_worker, int t_percent) {
		cout << t_worker << "report to boss: " << "   " << t_percent << endl;
	}
	void onComplete(string  t_worker, string t_result) {
		cout << t_worker << "report to boss: " << t_result << endl;
	}
	void hireWorker() {
		Worker i_worker1("tom");
		Worker i_worker2("leo");
		_worker_list.push_back(i_worker1);
		_worker_list.push_back(i_worker2);
	}
	void assignTask()
	{
		for (auto & itor : _worker_list)
		{
			auto i_process_task = [&](const string&  t_name, const int&  t_percent) {
				return onProcess(t_name, t_percent); 
			};
			itor.regOnProcess(i_process_task);
			auto i_result_task = [&](const string&  t_name, const string& t_result) {return onComplete(t_name, t_result); };
			itor.regOnComplete(i_result_task);
		}
	}
	void makeMoney() {
		for (auto & itor : _worker_list)
		{
			itor.startAsynicWork();/////start work
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

