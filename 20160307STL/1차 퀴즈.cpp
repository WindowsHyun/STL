#include <iostream>
#include <random>
#include<fstream>

using namespace std;

int cmp(const void* p, const void *q) {
	int a = *(int*)p;
	int b = *(int*)q;
	if (a < b)
		return -1;
	if (a == b)
		return 0;
	return 1;
}


#define MAX_COUNT 10000000

int main() {
	default_random_engine dre;
	uniform_int_distribution<>ui;
	dre.seed(20121820777);

	// ���� ���� �Ѱ��� ui(dre)�� ����� �ִ�.
	cout << ui(dre) << endl;
	int* a = new int[10000000];
	// ����1. ui(dre)�� 1000���� ȣ���Ͽ� �� ����� HEAP �޸𸮿� �����϶�
	for (int i = 0; i < 10000000; ++i) {
		a[i] = ui(dre);
	}
	// ����2. qsort()�� ����Ͽ� [1]���� ������ ������ ������������ �����϶�.
	qsort(a, MAX_COUNT, sizeof(a[0]), cmp);
	// ����3. ���� ū ���� ���� �������� ȭ�鿡 ����϶�.
	cout << "���� ū �� " << a[9999999] << "���� ���� ��" << a[0] << endl;
	// ����4. ������ ����� << �����ڸ� ����Ͽ� �̸��� "�й�.txt"�� ���Ͽ� �����϶�.
	ofstream out("�й�.txt");		// , ios::app ���ҵ� ��� ����°� �̹Ƿ� ���ʿ䰡 ����.
	for (int i = 0; i < 10000000; ++i) {
		out << a[i] << " ";
	}
	
	//����5. ���İ���� ���Ͽ��� ������ �տ��� 100���� ȭ�鿡 ����ϴ� �ڵ带 �ۼ��϶�.
	ifstream in("�й�.txt");
	int x[100];
	for (int i = 0; i < 100; ++i) {
		in >> x[i];
	}

	for (int i = 0; i < 100; ++i) {
		cout << x[i] << " ";
	}
	
}