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

	// 랜덤 정수 한개는 ui(dre)로 만들수 있다.
	cout << ui(dre) << endl;
	int* a = new int[10000000];
	// 문제1. ui(dre)를 1000만번 호출하여 그 결과를 HEAP 메모리에 저장하라
	for (int i = 0; i < 10000000; ++i) {
		a[i] = ui(dre);
	}
	// 문제2. qsort()를 사용하여 [1]에서 저장한 정수를 오름차순으로 정렬하라.
	qsort(a, MAX_COUNT, sizeof(a[0]), cmp);
	// 문제3. 가장 큰 값과 가장 작은값을 화면에 출력하라.
	cout << "가장 큰 값 " << a[9999999] << "가장 작은 값" << a[0] << endl;
	// 문제4. 정렬한 결과를 << 연산자를 사용하여 이름이 "학번.txt"인 파일에 저장하라.
	ofstream out("학번.txt");		// , ios::app 어팬드 모드 덮어쓰는거 이므로 쓸필요가 없다.
	for (int i = 0; i < 10000000; ++i) {
		out << a[i] << " ";
	}
	
	//문제5. 정렬결과를 파일에서 읽은후 앞에서 100개를 화면에 출력하는 코드를 작성하라.
	ifstream in("학번.txt");
	int x[100];
	for (int i = 0; i < 100; ++i) {
		in >> x[i];
	}

	for (int i = 0; i < 100; ++i) {
		cout << x[i] << " ";
	}
	
}