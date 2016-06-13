//---------------------------------------------------------------------------
// 2016�� 06�� 13��
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
	cout << "Anagram�� ã�� ���α׷�" << endl;

	/*cout << "���� ������ �Է��ϼ��� " << endl;
	string dictionary_name;
	cin >> dictionary_name;*/

	ifstream ifs("diction");
	if (!ifs.is_open()) {
		cout  << "diction �� ������ �����ϴ�." << endl;
		exit(0);
	}

	vector<PS> v;
	v.reserve(20159);

	copy(istream_iterator<string>(ifs), istream_iterator<string>(), back_inserter(v));
	cout << "���" << v.size() << "���� �ܾ �о����ϴ�." << endl;

	//ȭ�鿡 v�� ����غ���

	// ���̵�� ���� �ܾ�� �� �ܾ ������ �ܾ �ϳ��� ������ �����.
	// v�� first �������� �����Ѵ�.
	sort(v.begin(), v.end(), [](const PS& a, const PS& b) {
		return a.first < b.first;
	});

	// ó������ ������ ������ ���� �ܾ ��������
	// ���� ��ġ�� ���� ��ġ�� �ܾ ���� ���� ã�´�.
	// if (�߰��ߴ�)
	//	�߰��� ��ġ���� �������� �ܾ ������ ��ġ�� ã�´�.
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

		// ���� [j, k] �� anagram�̴�.
		cout << "[" << i++ << "]" << " ";
		copy(j, k, ostream_iterator<string>(cout, " "));
		j = k;
		cout << endl;

	}

	save();
}