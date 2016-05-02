//---------------------------------------------------------------------------
// 2016년 05월 02일 (9주 1일)
//
//---------------------------------------------------------------------------
#include <iostream>
#include<string>
#include <vector>
#include <iterator>
#include <list>
#include "save.h"

using namespace std;

template <class Iter, class Dest>
void my_copy(Iter b, Iter e, Dest d) {
	while (b != e) {
		//d.operator*() = b.operator*();
		(d.operator*()).operator = (b.operator*());
		// d++;
		d.operator++();
		// b++;
		b.operator++();
	}
}

template <class Cont>
class my_back_inserter {
	Cont* cont;
public:
	my_back_inserter(Cont& v) {
		cont = &v;
	}
	my_back_inserter& operator*() {
		return *this;
	}
	void operator++() {}
	// 실제 표준 back_inserter하는 일은 이 함수에서 일어남
	void operator=(int n) {
		cont->push_back(n);
	}
};

int main() {
	vector<int> v{ 1,2,3,4,5 };
	list<int> v2;

	my_back_inserter<list<int>> p(v2);

	my_copy(v.begin(), v.end(), p);

	for (auto d : v2)
		cout << d << endl;

	save();
}