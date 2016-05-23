//---------------------------------------------------------------------------
// 2016년 05월 23일
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "save.h"

using namespace std;

class Game {
	int n;
};

// set의 정렬기준은 두 가지로 설정할 수 있다.
// 1. 탬플릿 파라미터
// 2. 생성자 파라미터

int main() {
	//1.
	set<Game, less<Game>> s;
	//2.
	//set <int> s( 기준 );

	//save();
}