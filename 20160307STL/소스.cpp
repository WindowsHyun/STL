//---------------------------------------------------------------------------
// 2016�� 05�� 11��
//
// ���� �� ��(5.18) ���� 2 ����
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;

class Dog {
	int age{};
public:
	Dog() {}
	Dog( int n ) : age( n ){}
};

int main() {
	//Ű���忡�� ���ϴ� ��ŭ ���ڸ� �Է��ؼ� v�� ����� �ּ���.
	// �׸��� ���� ����� �ּ���.
	vector<int> v(istream_iterator<int>(cin), istream_iterator<int>());
	int sum{};
	for ( int d : v )
		sum+=d;

	cout << sum << endl;
	//save();
}