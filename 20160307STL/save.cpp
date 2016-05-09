// 2일차(1주)
// 소스파일 하드저장, 날짜 붙여서, cpp 파일 분리
// 정렬, 랜덤 넘버 생성

#include <iostream>
#include <chrono> //현재 시간읽어올때 사용,
#include<ctime>
#include <string>
#include<fstream>

void save();

using namespace std;

void save() {
	// 현재 시각을 읽어온다.
	chrono::system_clock::time_point tp = chrono::system_clock::now();
	//auto tp = chrono::system_clock::now(); // 같은내용

	// 시간을 날짜로 바꾼다.
	time_t tt = chrono::system_clock::to_time_t(tp);
	string date = ctime(&tt);
	date.resize(date.length() - 1); // 줄구분을 지워버린다.

	// 출력 파일을 연다.
	//ofstream out("Build Data/C++Class 복습과 이동의 이해(0321).txt", ios::app);
	ofstream out("Build Data/20160509.txt", ios::app);
	out << "" << endl;
	out << "---------------------------------------" << endl;
	out << "2016년 1학기 STL" << endl;
	out << date << endl;
	out << "---------------------------------------" << endl;
	out << "" << endl;

	// 입력파일(소스.cpp)을 연다.
	ifstream in("소스.cpp");

	// 입력파일의 모든 내용을 출력파일에 쓴다.
	char c;
	while (in.get(c))
		out.put(c);
}