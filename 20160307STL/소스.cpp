//---------------------------------------------------------------------------
// 2016년 05월 11일
//
// 다음 주 수(5.18) 퀴즈 2 예정
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
	//키보드에서 원하는 만큼 숫자를 입력해서 v를 만들어 주세요.
	// 그리고 합을 출력해 주세요.
	vector<int> v(istream_iterator<int>(cin), istream_iterator<int>());
	int sum{};
	for ( int d : v )
		sum+=d;

	cout << sum << endl;
	//save();
}