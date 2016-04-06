//---------------------------------------------------------------------------
// 2016�� 04�� 06��
//
// 6��
// ǥ�� ���ø� ���̺귯��(STL)
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
#include "save.h"

using namespace std;

// pair<string, int> �� �ڷḦ vector�� �־� �����ϰ� �ʹ�.
using Score = pair<string, int>;


int main() {
	vector<Score> v;

	v.push_back(make_pair("���콺", 40));
	v.push_back(make_pair("Ű����", 50));
	v.push_back(make_pair("�����", 100));
	v.push_back(make_pair("�޸�", 1000));
	v.push_back(make_pair("cpu", 10000));

	// �̸������� �����Ͽ� ����� ������.

	sort(v.begin(), v.end(), [](const Score& a, const Score& b) {
		return a.second > b.second;
	});

	//STL �ݺ��ڸ� �̿��� �����̳� ���� ����
	vector<Score>::iterator	i = v.begin();

	cout << i->first << " , " << i->second << endl;
	i++;
	cout << i->first << " , " << i->second << endl;

	//save();
}