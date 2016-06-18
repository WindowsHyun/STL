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
		cout << "����" << "(" << x << ", " << y << ") " << "�Ҵ��ڿ� �� " << num
			<< "\t" << "ù° �� " << p[0] << endl;
	}
	double dist() const {
		// �� �Լ��� (0,0)�� (x,y)�� �Ÿ��� �˷��ش�.
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
	// ���� ������?

	// [���� 2]
	m.reserve(100);
	for (int i = 0; i < 100; ++i) {
		m.push_back(Monster((rand() % 40) - 20, (rand() % 40) - 20, (rand() % 90) + 10));
	}

	cout << endl;
	cout << "-------------------" << endl;
	cout << "���� 2 ��� ���" << endl;
	cout << "-------------------" << endl;
	for (Monster d : m)
		d.show();








	// [���� 7]

	m.erase(remove_if(m.begin(), m.end(), [](const Monster& a)->bool {
		if (a.dist() > 10) {
			return false;
		}
	}), m.end());


	cout << endl;
	cout << "----------" << endl;
	cout << "���� 7 ��� ���" << endl;
	cout << "----------" << endl;
	for (Monster d : m) {
		cout << "�Ÿ� - " << d.dist() << "\t";
		d.show();
	}


	// [���� 8]

	ofstream out("�⸻����.txt");
	out << m;
	out.close();

	m.clear();
	cout << endl;
	cout << "���� 8 �����̳��� ���� �� " << m.size() << endl;

	ifstream in("�⸻����.txt");
	in >> m;

	cout << endl;
	cout << "----------" << endl;
	cout << "���� 8 ��� ���" << endl;
	cout << "----------" << endl;
	for (Monster d : m) {
		cout << "�Ÿ� - " << d.dist() << "\t";
		d.show();
	}
	
}

