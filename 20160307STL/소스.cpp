//---------------------------------------------------------------------------
// 2016�� 05�� 25��
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;
/*
439�� �� �� STL �����̳�
STL �˰���� �Բ� ���� �۵��ϴ� �����̳ʸ� ���� �� �ִ� �����?

1. STL �����̳ʰ� �䱸�ϴ� �������̽��� �����Ѵ�.
	- string�� stl �����̳ʷ� �̿��ϴ� ��츦 ���Ѵ�.
	- string�� begin(), end(), push_back()���� �����Ѵ�.
2. �����̳ʿ� �˰����� �������̽��� ����ϴ� ��ü�� �����Ѵ�(�ݺ���)
	���� �迭
	�ݺ��ڴ� �����Ϳ� ���Ͽ� Ư��ȭ(specializtion)�Ǿ� �����Ƿ�
3. wrapper Ŭ������ ���� ����� ����Ѵ�.

------------------------------------------------------------------------------------------
ǥ���� �ؼ��ϴ� �����̳ʸ� ����� ����.

ItemBox �����̳� - Ư���� �ϴ� �� ���� array<T, size>�� ����� �����̳�
------------------------------------------------------------------------------------------
*/
template <class T, int n>
class ItemBox {
	T data[n];
public:
	T* begin() {
		return data;
		//return data;
	};
	T* end() {
		return data + n;
	}
	size_t size() {
		return n;
	};
};

int main() {
	ItemBox<int, 10> a;
	auto p = a.begin();
	for ( int i = 0; i < a.size(); ++i )
		*p++ = i + 1;

	copy( a.begin(), a.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;

	//������������ �����غ���

	sort( a.begin(), a.end(), []( int a, int b ) {
		return a > b;
	} );

	for ( int d : a )
		cout << d << " ";
	cout << endl;

	// ������ ������ ��ȯ, rotate
	rotate( a.begin(), a.begin() + 2, a.end() );

	for ( int d : a )
		cout << d << " ";
	cout << endl;

	//save();
}