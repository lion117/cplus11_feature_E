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
	int x = fut.get(); // 获取共享状态的值.
	std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

inline int test_future()
{
	std::promise<int> prom; // 生成一个 std::promise<int> 对象.
	std::future<int> fut = prom.get_future(); // 和 future 关联.
	std::thread t(print_int, std::ref(fut)); // 将 future 交给另外一个线程t.
	
	Poco::Thread::sleep(1001);

	prom.set_value(10); // 设置共享状态的值, 此处和线程t保持同步.
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

	prom1 = std::promise<int>();    // prom 被move赋值为一个新的 promise 对象.

	std::thread th2(print_global_promise);
	prom1.set_value(20);
	th2.join();

	return 0;
}