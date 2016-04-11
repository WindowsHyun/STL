//---------------------------------------------------------------------------
// 2016년 04월 11일
//
// 6장
// 표준 템플릿 라이브러리(STL)
//
//---------------------------------------------------------------------------
#include <iostream>
#include <set>
#include <random>
#include "save.h"

using namespace std;


int main() {
	// 연관 컨테이너 set<int>에 랜덤정수 100개 넣고 출력해보자
	set<int> s;

	for (int i = 0; i < 100; ++i)
		s.insert(rand());

	for (set<int>::const_iterator i = s.begin(); i != s.end(); ++i) {
		cout << *i << "\t";
	}

	//auto p = find(s.begin(), s.end(), 32757);
	auto p = s.find(32757);
	if (p != s.end()) {
		//찾음
		cout << *p << endl;
	}
	else {
		// 못찾음
	}

	/*
	uniform_int_distribution <>ui(0,1000);
	default_random_engine dre;

	for (int i = 0; i < 100; ++i)
	s.insert(ui(dre));

	for (auto iter = s.begin(); iter != s.end(); ++iter) {
		cout << *iter << " ";
	}
	*/
	save();
}