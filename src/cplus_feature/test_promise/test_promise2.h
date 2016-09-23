#pragma  once




#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for
#include "Poco/Thread.h"

int work(int from, int to);
int testMain();




// count down taking a second for each value:
inline int work(int from, int to) {
	for (int i = from; i != to; --i) {
		std::cout <<"ticks"<< i << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Finished!\n";
	return from - to;
}

inline int testMain()
{
	std::packaged_task<int(int, int)> task(work); // ���� packaged_task
	std::future<int> ret = task.get_future(); // ����� packaged_task ����״̬������� future ����.

	//std::function<int(int, int)> i_dele = std::bind(task, 10, 0);
	//std::thread th(i_dele);
	std::thread th(std::move(task), (10), (0));   //����һ�����߳���ɼ�������.

	while(!ret._Is_ready())
	{
		cout << "waiting for result"<<endl;
		Poco::Thread::sleep(500);
	}

	int value = ret.get();                    // �ȴ�������ɲ���ȡ���.

	std::cout << "The countdown lasted for " << value << " seconds.\n";

	th.join();
	return 0;
}