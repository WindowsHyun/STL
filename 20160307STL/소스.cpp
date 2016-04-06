//---------------------------------------------------------------------------
// 2016년 04월 06일
//
// 6장
// 표준 템플릿 라이브러리(STL)
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
#include "save.h"

using namespace std;

// pair<string, int> 인 자료를 vector에 넣어 관리하고 싶다.
using Score = pair<string, int>;


int main() {
	vector<Score> v;

	v.push_back(make_pair("마우스", 40));
	v.push_back(make_pair("키보드", 50));
	v.push_back(make_pair("모니터", 100));
	v.push_back(make_pair("메모리", 1000));
	v.push_back(make_pair("cpu", 10000));

	// 이름순으로 정렬하여 출력해 보세요.

	sort(v.begin(), v.end(), [](const Score& a, const Score& b) {
		return a.second > b.second;
	});

	//STL 반복자를 이용한 컨테이너 원소 접근
	vector<Score>::iterator	i = v.begin();

	cout << i->first << " , " << i->second << endl;
	i++;
	cout << i->first << " , " << i->second << endl;

	//save();
}