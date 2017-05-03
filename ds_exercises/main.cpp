#include <iostream>
using namespace std;
#include <vector>
using namespace std;
#include <opencv.hpp>
using namespace cv;


class A {
public:
	A() = default;
	A(int a)
	{
		cout << a << endl;
		n = a;
	}
	int n;
	~A() = default;
};
int main()
{
	int count = 0;
	vector<A> v(10, A(count++));
	return -1;
}