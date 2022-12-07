#include <iostream>
using namespace std;

//赋值重载运算符
//C++编译器可能会给类添加四个函数：
//（1）默认构造函数，空实现
//（2）默认析构函数，空实现
//（3）默认考本构造函数，对成员函数进行浅拷贝
//（4）默认赋值函数，对成员进行浅拷贝
//对象的赋值运算是用一个已经存在的对象，给另一个已经存在的对象赋值。
//如果类中的定义没有重载赋值函数，编译器就会提供一个默认赋值函数
//
//重载赋值函数语法：类名 & operator=（const 类名&源对象）
//注意：
//（1）编译器提供的默认赋值函数，是浅拷贝
//（2）如果对象不存在堆区内存空间，默认赋值函数可以满足需求，否则需要深拷贝
//（3）赋值运算和拷贝构造不同：拷贝构造是指原来的对象不存在，用已存在的对象进行构造；
//赋值运算是指存在的两个对象，把其中一个对象的成员变量的值赋给另一个对象的成员变量。
class CGirl
{
public:
	int m_bh;//编号
	string m_name;//姓名
	int* m_ptr; //计划使用堆空间

	CGirl() { m_ptr = nullptr; }
	~CGirl() { if (m_ptr) delete m_ptr; m_ptr = nullptr; }

	void show() {  //显示全部成员变量
		cout << "编号 : " << m_bh << " 姓名 ：" << m_name <<", *m_ptr="<< *m_ptr << ", m_ptr=" <<m_ptr<< endl;
	}

	CGirl& operator=(const CGirl& g)  //深拷贝赋值重载
	{
		if (this == &g) return *this;  //判断类是否相等，相等就不需要执行
		if (g.m_ptr == nullptr)  //如果源对象为空，则清空对象的内存和指针
		{
			if (m_ptr != nullptr) {
				delete m_ptr; m_ptr = nullptr;
			}
		}
		else
		{
			if (m_ptr == nullptr) m_ptr = new int; //如果目标对象的指针为空，先分配内存
			memcpy(m_ptr, g.m_ptr, sizeof(int));//然后把源对象的数据复制存放在目标对象的内存中
		}
		m_bh = g.m_bh, m_name = g.m_name;
		cout << "调用了赋值重载函数 " << endl;
		return *this;//返回this指针解引用
	}

};

int main()
{
	CGirl g1, g2;  //创建对象
	g1.m_bh = 1, g1.m_name = "西施";
	g1.m_ptr = new int(3);
	g1.show();
	//g2.show();

	//对象的赋值运算
	g2=g1 ;       //相当于g2.m_name=g1.m_name, g2.m_bh=g1.m_bh;
	g2.show();

	//在程序中存在g1=g1这种语法，这是合法的；如果是这样，那么赋值函数数中的代码就不需要执行。

	return 0;
}