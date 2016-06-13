//---------------------------------------------------------------------------
// 2016년 06월 13일
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;

struct PS : pair<string, string> {
	PS() : pair<string, string>(string(), string()) {}
	PS(const string& s) :pair<string, string>(s, s) {
		sort(first.begin(), first.end());
	}
	operator string() const {
		return second;
	}
};


int main() {
	cout << "Anagram을 찾는 프로그램" << endl;

	/*cout << "산전 파일을 입력하세요 " << endl;
	string dictionary_name;
	cin >> dictionary_name;*/

	ifstream ifs("diction");
	if (!ifs.is_open()) {
		cout  << "diction 을 읽을수 없습니다." << endl;
		exit(0);
	}

	vector<PS> v;
	v.reserve(20159);

	copy(istream_iterator<string>(ifs), istream_iterator<string>(), back_inserter(v));
	cout << "모두" << v.size() << "개의 단어를 읽었습니다." << endl;

	//화면에 v를 출력해보자

	// 아이디어 읽은 단어와 그 단어를 정렬한 단어를 하나의 싸으로 만든다.
	// v의 first 기준으로 정렬한다.
	sort(v.begin(), v.end(), [](const PS& a, const PS& b) {
		return a.first < b.first;
	});

	// 처음부터 끝까지 정렬해 놓은 단어를 기준으로
	// 현재 위치와 다음 위치의 단어가 같은 것을 찾는다.
	// if (발견했다)
	//	발견한 위치부터 같지않은 단어가 나오는 위치를 찾는다.
	int i = 1;
	vector<PS>::const_iterator j = v.begin(),
		end = v.end(), k;
	while (true) {
		j = adjacent_find(j, end, [](const PS& a, const PS& b) {
			return a.first == b.first;
		});

		if (j == end)
			break;
		k = find_if_not(j + 1, end, [j](const PS& a) {
			return a.first == j->first;
		});

		// 구간 [j, k] 는 anagram이다.
		cout << "[" << i++ << "]" << " ";
		copy(j, k, ostream_iterator<string>(cout, " "));
		j = k;
		cout << endl;

	}

	save();
}