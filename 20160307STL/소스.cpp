//---------------------------------------------------------------------------
// 2016�� 04�� 11��
//
// 6��
// ǥ�� ���ø� ���̺귯��(STL)
//
//---------------------------------------------------------------------------
#include <iostream>
#include <set>
#include <random>
#include "save.h"

using namespace std;


int main() {
	// ���� �����̳� set<int>�� �������� 100�� �ְ� ����غ���
	set<int> s;

	for (int i = 0; i < 100; ++i)
		s.insert(rand());

	for (set<int>::const_iterator i = s.begin(); i != s.end(); ++i) {
		cout << *i << "\t";
	}

	//auto p = find(s.begin(), s.end(), 32757);
	auto p = s.find(32757);
	if (p != s.end()) {
		//ã��
		cout << *p << endl;
	}
	else {
		// ��ã��
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