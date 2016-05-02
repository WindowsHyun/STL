//---------------------------------------------------------------------------
// 2016�� 05�� 02�� (9�� 1��)
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
	// ���� ǥ�� back_inserter�ϴ� ���� �� �Լ����� �Ͼ
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