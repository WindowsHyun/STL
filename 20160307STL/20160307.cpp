#include <iostream>
#include<string>
// ���۷����� ������
using namespace std;

template <class T> // �ƹ� �ڷ����̳� ����� ���� ����� ���,
void change(T& a, T& b){ // ������ �������� ���� �������.

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
	// ��ȯ�� ���ִ� �Լ�.
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
	//int & r = n; //���۷���
	//r++;
	//cout << n << endl;
	int x[2] = { 10, 20 };

	cout << &x[0] << ", " << &x[1] << endl; // �ּ�

	//int * p = &x[0];
	//++p;
	//*p = 333;

	int* const p = &x[0]; //������ ���ٲٰ� �����ϴ� ���.

	cout << x[0] << ", " << x[1] << endl;

	*/

	Monster x("���", 333), y("ogre", 777);

	change(x, y);

	cout << x << ", " << y << endl;
}