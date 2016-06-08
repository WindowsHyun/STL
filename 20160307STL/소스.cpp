//---------------------------------------------------------------------------
// 2016�� 06�� 08��
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;

class IntSequence {
	int value;
public:
	IntSequence(int val) : value(val) {}
	int operator() () {
		cout << value << endl;
		return ++value;

	}
};
template<class Iter, class Call>
Call foreach(Iter b, Iter e, Call c) {
	while (b != e)
		c(*b++);

	return c;
}
class MeanValue {
	int sum{ 0 };
	int count{ 0 };
public:
	void operator()(int n) {
		sum += n;
		count++;
	}
	double value() {
		return (double)sum / count;
	}
};

int main() {
	vector<int> v{ istream_iterator<int>(cin), istream_iterator<int>() };      //�Է� �������� ctrl+z
	cout << "��հ��� " << foreach(v.begin(), v.end(), MeanValue()).value() << endl;

	//save();
}