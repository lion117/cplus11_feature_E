#pragma  once




#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for


int countdown(int from, int to);
int test_task();


// count down taking a second for each value:
inline int countdown(int from, int to) {
	for (int i = from; i != to; --i) {
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Finished!\n";
	return from - to;
}

inline int test_task()
{
	std::packaged_task<int(int, int)> task(countdown); // ���� packaged_task
	std::future<int> ret = task.get_future(); // ����� packaged_task ����״̬������� future ����.

	std::thread th(std::move(task), 10, 0);   //����һ�����߳���ɼ�������.

	ret._Is_ready();
	int value = ret.get();                    // �ȴ�������ɲ���ȡ���.

	std::cout << "The countdown lasted for " << value << " seconds.\n";

	th.join();
	return 0;
}