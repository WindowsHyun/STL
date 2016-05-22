//---------------------------------------------------------------------------
// 2016�� 05�� 18��
//
// ���� �� ��(5.18) ���� 2 ����
//---------------------------------------------------------------------------
#include <iostream>
#include <set>
#include <algorithm>
#include "save.h"

using namespace std;
class Game {
	int n;
public:
	Game( int n ) : n( n ) {}
	int getN() const {
		return n;
	}
	bool operator<(const Game& b ) const {
		return n < b.n;
	}
};



int main() {
	set<Game> s1{ 1, 2, 3,  7, 8, 9 };

	for (const Game& d  : s1 )
		cout << d.getN();
	cout << endl;

	//save();
}