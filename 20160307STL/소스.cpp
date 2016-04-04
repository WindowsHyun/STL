//---------------------------------------------------------------------------
// 2016�� 04�� 04��
//
//---------------------------------------------------------------------------
#include <iostream>
#include<algorithm>
#include<functional> // bind �Լ��� �������ؼ�
#include <vector>
#include <utility> // pair ����Ҷ�
#include<random>
#include <string>
#include <memory> // unique_ptr or shared_ptr ���� ���
#include "save.h"

using namespace std;

// 5.4 type traits

// ���ø� �ڵ忡���� ���޵� ������ Ÿ���� ������ �ʿ䰡 �ִ�.
// ������ Ÿ���� �����ϱ� ����
// 168Page�� ����Ǿ��ִ�.


template <class T>void f(T t) {
	f(t, is_pointer<T>());
}

template<class T>
void f(T t, true_type) {
	cout << "������ ���� (����Ű�� ��) - " << *t << endl;
}

template<class T>
void f(T t, false_type) {
	cout << "���� ���� - " << t << endl;
}

int main() {
	// � �Լ��� �ִµ� �Ѱ��ִ� ���� �������̸� �� ���� ����Ű�� ����,
	// �׳� ���̶�� �� ���� ����ϴ� �Լ��� �ۼ��ϰ� �ʹ�.
	int n{ 100 };
	int* p{ &n };


	f(n);
	f(p);
	//save();
}