//---------------------------------------------------------------------------
// 2016�� 04�� 04��
//
// 6��
// ǥ�� ���ø� ���̺귯��(STL)
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

// �����Լ�

int main() {
	int a[]{ 1,2,3,4,5,6,7,8,9,10 };

	// minmax()  �Լ��� ū ���� ���� ���� ���� ã�� �ִ� �����Լ��̴�.

	pair<int,int> p = minmax(&a[0], &a[10]);
	// ��ɷ� �� ���� �������ΰ�?
	// ���ϰ��� pair�ϲ���.

	//save();
}