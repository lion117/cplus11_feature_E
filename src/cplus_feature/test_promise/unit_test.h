#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

#include "Poco/Thread.h"

#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future


void print_int(std::future<int>& fut);
int test_future();


inline void print_int(std::future<int>& fut) {
	int x = fut.get(); // ��ȡ����״̬��ֵ.
	std::cout << "value: " << x << '\n'; // ��ӡ value: 10.
}

inline int test_future()
{
	std::promise<int> prom; // ����һ�� std::promise<int> ����.
	std::future<int> fut = prom.get_future(); // �� future ����.
	std::thread t(print_int, std::ref(fut)); // �� future ��������һ���߳�t.
	
	Poco::Thread::sleep(1001);

	prom.set_value(10); // ���ù���״̬��ֵ, �˴����߳�t����ͬ��.
	t.join();
	return 0;
}



void print_global_promise();
int test_future1();

static std::promise<int> prom1;

inline void print_global_promise() {
	std::future<int> fut = prom1.get_future();
	int x = fut.get();
	std::cout << "value: " << x << '\n';
}

inline int test_future1()
{
	std::thread th1(print_global_promise);
	prom1.set_value(10);
	th1.join();

	prom1 = std::promise<int>();    // prom ��move��ֵΪһ���µ� promise ����.

	std::thread th2(print_global_promise);
	prom1.set_value(20);
	th2.join();

	return 0;
}