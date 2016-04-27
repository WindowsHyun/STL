//---------------------------------------------------------------------------
// 2016년 04월 27일	( 8주 2일)
//
//---------------------------------------------------------------------------
#include <iostream>
#include<string>
#include <vector>
#include <iterator>
#include "save.h"

using namespace std;

template <class Iter, class Dest>
void my_copy(Iter b, Iter e, Dest d) {
	while (b != e) {
		/*d.operator++(123).operator*()
			= b.operator++(456).operator*();*/
		*d++ = *b++;
	}
}
class my_class {
public:
	//operator*() { }
};

int main() {
	vector<int> v{ 1,2,3,4,5 };
	vector<int> v2;

	/*my_copy(v.begin(), v.end(), back_inserter(v2));
	my_copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\n"));*/

	/*for (auto d : v2)
		cout << d << endl;*/

	back_insert_iterator<vector<int>> p(v2);
	*p = 333; // p.operator*(333)
				// {
				//		v2.push_back(333);
				// }

	cout << v2[0] << endl;

	// 세 번째 인자인 back_inserter은 반복자 어댑터이다.
	// 반복자에 요구되는 동작인 *, ++, == 등을 구현한 클래스 이다.
	// 백인서터는 값을 쓰려는 동작을 값을 삽입하는 동작으로 구현한다.

	save();
}