//---------------------------------------------------------------------------
// 2016년 04월 04일
//
// 6장
// 표준 템플릿 라이브러리(STL)
//
//---------------------------------------------------------------------------
#include <iostream>
#include<algorithm>
#include<functional> // bind 함수를 쓰기위해서
#include <vector>
#include <utility> // pair 사용할때
#include<random>
#include <string>
#include <memory> // unique_ptr or shared_ptr 사용시 사용
#include "save.h"

using namespace std;

// 보조함수

int main() {
	int a[]{ 1,2,3,4,5,6,7,8,9,10 };

	// minmax()  함수는 큰 값과 작은 값을 같이 찾아 주는 보조함수이다.

	pair<int,int> p = minmax(&a[0], &a[10]);
	// 어떤걸로 이 값을 받을것인가?
	// 리턴값이 pair일꺼다.

	//save();
}