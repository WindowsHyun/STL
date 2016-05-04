//---------------------------------------------------------------------------
// 2016년 05월 04일 (9주 1일)
//
// 알고리즘 조작(269)
// 알고리즘과 멤버함수 비교
// 알고리즘 인자로서의 함수
// 람다 사용하기
// 함수객체
// 선정의 함수객체와 바인더
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <set>
#include <functional>
#include <algorithm>
#include <iterator>
#include<deque>
#include "save.h"

using namespace std;

// 바인더 (293)

int main() {
	set<int, greater<int>> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	deque<int> coll2;

	// transform을 써서 coll1의 모든 원소를 coll2로 옮기면서 10을 곱한다.
	//transform(coll1.begin(), coll1.end(), back_inserter(coll2), coll

		//save();
}