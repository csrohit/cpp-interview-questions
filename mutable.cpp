
// PROGRAM 1
#include <iostream>
using namespace std;

class Test {
public:
int x;
mutable int y;
Test() { x = 4; y = 10; }
};
int main()
{
	const Test t1;
	t1.y = 20;
	cout << t1.y << endl;
	return 0;
}
