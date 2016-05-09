//---------------------------------------------------------------------------
// 2016년 05월 09일
//
// 7장 STL 컨테이너
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;

// 소스.cpp 의 모든 단어 순서를 거꾸로 출력하라.
// using - > gnisu

int main() {
	string s;
	ifstream in( "소스.cpp" );
	int n{ 0 };
	while ( in >> s ) {
		// 한 단어 읽음 s 에다가
		copy( s.rbegin(), s.rend(), ostream_iterator<char>(cout, "") );
		cout << endl;
		n++;
		//cout << s << endl;
	}
	cout << "몇개 인가 : " << n << endl;
	save();
}