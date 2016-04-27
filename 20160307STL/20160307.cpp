#include <iostream>
#include<string>
// 레퍼런스와 포인터
using namespace std;

template <class T> // 아무 자료형이나 상관이 없게 만드는 방법,
void change(T& a, T& b){ // 변수를 복사하지 말고 사용하자.

	T temp = a;
	a = b;;
	b = temp;
}

class Monster{
private:
	string name;
	int num;
public:
	Monster(string name, int num) : name(name), num(num) {}
	//------------------------------------------------
	// 반환을 해주는 함수.
	string getName() const {
		return name;
	};
	int getNum() const {
		return num;
	}
	//------------------------------------------------
};

ostream& operator << (ostream& out, const Monster& m){
	out << m.getName() << " - " << m.getNum() << endl;
	return out; // out put stream
}


int main(){
	/*
	//int n{ 10 };
	//int & r = n; //레퍼런스
	//r++;
	//cout << n << endl;
	int x[2] = { 10, 20 };

	cout << &x[0] << ", " << &x[1] << endl; // 주소

	//int * p = &x[0];
	//++p;
	//*p = 333;

	int* const p = &x[0]; //번지를 못바꾸게 방지하는 방법.

	cout << x[0] << ", " << x[1] << endl;

	*/

	Monster x("빅뱅", 333), y("ogre", 777);

	change(x, y);

	cout << x << ", " << y << endl;
}