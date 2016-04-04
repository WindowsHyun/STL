//---------------------------------------------------------------------------
// 2016년 04월 04일
//
//---------------------------------------------------------------------------
#include <iostream>
#include<algorithm>
#include<functional> // bind 함수를 쓰기위해서
#include <vector>
#include <utility> // pair 사용할때
#include<random>
#include <string>
#include <memory> // unique_ptr or shared_ptr 사용시 사용
#include "save.h"

using namespace std;

// 5.4 type traits

// 탬플릿 코드에서는 전달된 인자의 타입을 구분할 필요가 있다.
// 인자의 타입을 구분하기 위해
// 168Page에 저장되어있다.


template <class T>void f(T t) {
	f(t, is_pointer<T>());
}

template<class T>
void f(T t, true_type) {
	cout << "포인터 전달 (가리키는 값) - " << *t << endl;
}

template<class T>
void f(T t, false_type) {
	cout << "값이 전달 - " << t << endl;
}

int main() {
	// 어떤 함수가 있는데 넘겨주는 값이 포인터이면 그 것이 가리키는 값을,
	// 그냥 값이라면 그 값을 출력하는 함수를 작성하고 싶다.
	int n{ 100 };
	int* p{ &n };


	f(n);
	f(p);
	//save();
}