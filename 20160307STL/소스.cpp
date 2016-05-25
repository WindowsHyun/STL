//---------------------------------------------------------------------------
// 2016년 05월 25일
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;
/*
439쪽 그 외 STL 컨테이너
STL 알고리즘과 함께 어울려 작동하는 컨테이너를 만들 수 있는 방법은?

1. STL 컨테이너가 요구하는 인터페이스를 제공한다.
	- string을 stl 컨테이너로 이용하는 경우를 말한다.
	- string은 begin(), end(), push_back()등을 제공한다.
2. 컨테이너와 알고리즘간의 인터페이스를 담당하는 객체를 제공한다(반복자)
	기존 배열
	반복자는 포린터에 대하여 특수화(specializtion)되어 있으므로
3. wrapper 클래스를 직접 만들어 사용한다.

------------------------------------------------------------------------------------------
표준을 준수하는 컨테이너를 만들어 보자.

ItemBox 컨테이너 - 특별히 하는 일 없는 array<T, size>와 비슷한 컨테이너
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

	//내림차순으로 정렬해보자

	sort( a.begin(), a.end(), []( int a, int b ) {
		return a > b;
	} );

	for ( int d : a )
		cout << d << " ";
	cout << endl;

	// 원소의 순서를 순환, rotate
	rotate( a.begin(), a.begin() + 2, a.end() );

	for ( int d : a )
		cout << d << " ";
	cout << endl;

	//save();
}