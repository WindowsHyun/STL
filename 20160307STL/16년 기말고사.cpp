#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


class Player {
	int hp;
	double x, y;
public:
	Player(double x, double y, int hp = 100) : x(x), y(y) {}
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
};

class Monster {
	int num;
	double x, y;
	int* p;
public:
	Monster(double x, double y, int n) : x(x), y(y), num(n) {
		p = new int[num];
		for (int i = 0; i < num; ++i)
			p[i] = rand();
	}
	void show() {
		cout << "몬스터" << "(" << x << ", " << y << ") " << "할당자원 수 " << num
			<< "\t" << "첫째 값 " << p[0] << endl;
	}
	double dist() const {
		// 이 함수는 (0,0)과 (x,y)의 거리를 알려준다.
		return sqrt(x*x + y*y);
	}
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
	double getN() const {
		return num;
	}

};

ostream& operator<<(ostream& out, const vector<Monster>& data) {
	for (auto d : data)
		out << d.getX() << " " << d.getY() << " " << d.getN() << endl;

	return out;
}


istream &operator >> (istream & in, vector<Monster>& data) {
	double a, b;
	int c;
	while (in >> a >> b >> c) {
		data.emplace_back(a, b, c);
	}
	return in;
}

//-----------
int main()
//-----------
{
	Player me(0.0, 0.0);

	vector<Monster> m;
	// 가장 무난한?

	// [문제 2]
	m.reserve(100);
	for (int i = 0; i < 100; ++i) {
		m.push_back(Monster((rand() % 40) - 20, (rand() % 40) - 20, (rand() % 90) + 10));
	}

	cout << endl;
	cout << "-------------------" << endl;
	cout << "문제 2 결과 출력" << endl;
	cout << "-------------------" << endl;
	for (Monster d : m)
		d.show();








	// [문제 7]

	m.erase(remove_if(m.begin(), m.end(), [](const Monster& a)->bool {
		if (a.dist() > 10) {
			return false;
		}
	}), m.end());


	cout << endl;
	cout << "----------" << endl;
	cout << "문제 7 결과 출력" << endl;
	cout << "----------" << endl;
	for (Monster d : m) {
		cout << "거리 - " << d.dist() << "\t";
		d.show();
	}


	// [문제 8]

	ofstream out("기말시험.txt");
	out << m;
	out.close();

	m.clear();
	cout << endl;
	cout << "문제 8 컨테이너의 원소 수 " << m.size() << endl;

	ifstream in("기말시험.txt");
	in >> m;

	cout << endl;
	cout << "----------" << endl;
	cout << "문제 8 결과 출력" << endl;
	cout << "----------" << endl;
	for (Monster d : m) {
		cout << "거리 - " << d.dist() << "\t";
		d.show();
	}
	
}

