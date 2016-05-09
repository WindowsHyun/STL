// 2����(1��)
// �ҽ����� �ϵ�����, ��¥ �ٿ���, cpp ���� �и�
// ����, ���� �ѹ� ����

#include <iostream>
#include <chrono> //���� �ð��о�ö� ���,
#include<ctime>
#include <string>
#include<fstream>

void save();

using namespace std;

void save() {
	// ���� �ð��� �о�´�.
	chrono::system_clock::time_point tp = chrono::system_clock::now();
	//auto tp = chrono::system_clock::now(); // ��������

	// �ð��� ��¥�� �ٲ۴�.
	time_t tt = chrono::system_clock::to_time_t(tp);
	string date = ctime(&tt);
	date.resize(date.length() - 1); // �ٱ����� ����������.

	// ��� ������ ����.
	//ofstream out("Build Data/C++Class ������ �̵��� ����(0321).txt", ios::app);
	ofstream out("Build Data/20160509.txt", ios::app);
	out << "" << endl;
	out << "---------------------------------------" << endl;
	out << "2016�� 1�б� STL" << endl;
	out << date << endl;
	out << "---------------------------------------" << endl;
	out << "" << endl;

	// �Է�����(�ҽ�.cpp)�� ����.
	ifstream in("�ҽ�.cpp");

	// �Է������� ��� ������ ������Ͽ� ����.
	char c;
	while (in.get(c))
		out.put(c);
}