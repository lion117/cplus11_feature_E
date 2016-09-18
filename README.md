# cplus11_feature_E

## purpose 
prproject  is to introduce C++ 11 new feature which could promote development efficience and rubust 

# C++ 委托机制
在GUI编程或者基于事件开发的项目中,经常需要使用回调函数. 为了处理这类回调事件, C# 特别提供了关键字**delegate**来实现. 
## 函数指针回调做法
在传统的C++开发过程中, 为了实现函数回调,一般的做法是将 C++ 的函数指针传给管理者.当有事件触发时,再执行该回调函数. 

基于函数指针的回调方式有一下缺点：
- 对萌新不友好, 上手困难
- 函数指针操作并不安全,无法在编译阶段检测来


#C++11 新特性
为了解决此类问题, C++11 从boost库中借鉴了新特性  **functional**, 以此为容器存储函数指针,从而优雅的实现回调机制

案例演示：
- 存储自由函数
- 存储lambda表达式
- 存储std::bind 结果 （非常重要）
- 存储类成员方法和类实例
- 存储类成员方法和类实例指针
- 存储结构体方法


```C++
#pragma once
#include <functional>
#include <iostream>

void print_num(int i);

inline void print_num(int i)
{
	std::cout << i << '\n';
}

struct PrintNum {
	void operator()(int i) const
	{
		std::cout << i << '\n';
	}
};

struct Foo {
	Foo(int num) : num_(num) {}
	void print_add(int i) const { std::cout << num_ + i << '\n'; }
	int num_;
};

void main();

inline void main()
{
	 // store a free function
	 std::function<void(int)> f_display = print_num;
	 f_display(-9);

	 // store a lambda
	 std::function<void()> f_display_42 = []() { print_num(42); };
	 f_display_42();

	 //store the result of a call to std::bind
	 std::function<void()> f_display_31337 = std::bind(print_num, 31337);
	 f_display_31337();

	 // //store a call to a member function
	 //std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
	 const Foo foo(314159);
	 //f_add_display(foo, 1);

	 //store a call to a data member accessor
	 //std::function<int(Foo const&)> f_num = &Foo::num_;
	 //std::cout << "num_: " << f_num(foo) << '\n';

	 // store a call to a member function and object
	 using std::placeholders::_1;
	 std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
	 f_add_display2(2);

	 // store a call to a member function and object ptr
	 std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
	 f_add_display3(3);

	 // store a call to a function object
	 std::function<void(int)> f_display_obj = PrintNum();
	 f_display_obj(18);
}

```


# 委托机制实现演示


```C++
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

```

# windows消息回调
在windows GUI 开发过程中, 一般通过 postmessage 来完成消息回调,触发GUI执行对应的操作. 这种方式简单易行,对萌新友好,且具备跨线程操作的功能. 但是postmessage 也有自身的缺陷：
- 过渡依赖windows消息机制
- 回调传参可定制程度低

# 总结
为了解决GUI 跨线程操作界面的导致主线程崩溃的情况, C++ 11 终于推出了自己的thread 类
thread 类提供detach() 的方法, 让worker线程也具备了操作GUI的能力. 
在GUI开发中, 通过使用**function** 和 **thread**等C++ 11 新特性,能够更便捷的开发出高质量的程序, 同时回避开发过程中的问题


# Worker Thread in GUI 
> 在常规的GUI开发过程中, 工作线程是不允许直接操作GUI界面控件的.如果使用工作线程操作界面将直接导致程序崩溃. 在C#中,软件提供一个接口：取消对线程间的操作安全检查来实现跨线程操作界面功能
```c++
//指定不再捕获对错误线程的调用
Control.CheckForIllegalCrossThreadCalls = false;
```
在C++11的新特性中, 增加的thread类时允许跨线程操作界面的

```
    CProgressCtrl *i_ptr_processs = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	i_ptr_processs->SetRange(0, 99);
	i_ptr_processs->SetStep(1);
	i_ptr_processs->SetPos(0);
	auto func = [=]
	{
		for (int i = 0; i < 100; i++)
		{
			i_ptr_processs->SetPos(i);
			Sleep(10);
		}
	};
	std::thread  i_thread(func);
	i_thread.detach();

```

# 总结
1. thread 提供detach() 的方法,实现线程生命周期的自管理.线程创建者无需关心线程什么时候销毁释放问题
2. 在GUI中使用跨线程操作界面是**多线程不安全的**,一般不推荐使用.











