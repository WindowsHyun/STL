//---------------------------------------------------------------------------
// 2016�� 05�� 09��
//
// 7�� STL �����̳�
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;

// �ҽ�.cpp �� ��� �ܾ� ������ �Ųٷ� ����϶�.
// using - > gnisu

int main() {
	string s;
	ifstream in( "�ҽ�.cpp" );
	int n{ 0 };
	while ( in >> s ) {
		// �� �ܾ� ���� s ���ٰ�
		copy( s.rbegin(), s.rend(), ostream_iterator<char>(cout, "") );
		cout << endl;
		n++;
		//cout << s << endl;
	}
	cout << "� �ΰ� : " << n << endl;
	save();
}