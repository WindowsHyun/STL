

#include <iostream>
#include <list>
#include <cmath>
#include <random>
#include <algorithm>
#include<fstream>

using namespace std;

class Zombie
{
	int x, y;
	int hp{ 100 };
	bool alive;
public:
	Zombie( int x, int y ) : x( x ), y( y ), hp( 100 ), alive( true ) {}
	Zombie( int x, int y, int hp ) : x( x ), y( y ), hp( hp ), alive( true ) {}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	int getHP() const {
		return hp;
	}
	bool isAlive() const {
		return alive;
	}

	void render() const {
		cout << "��ġ(" << getX() << ", " << getY() << ") HP : " << getHP() << endl;
	}

	void decHP( int n ) {
		hp -= n;
		if ( hp < 0 )
			alive = false;
	}
};

/*
2�� ����
void print(const list<Zombie>& data, int n) {
cout << "������ �� : " << data.size() << endl;
auto p = data.begin();
for (int i = 0; i < n - 6; ++i) {
++p;
}
for (int i = 0; i <= 10; ++i) {
if (i == 5)
cout << "***" << i+n-5 << "***";
else
cout << "[" << i+n-5 << "]";
p->render();
++p;
}
}
*/
void print( list<Zombie > data, int start ) {
	cout << "������ �� : " << data.size() << endl;
	list<Zombie >::iterator p;
	p = data.begin();
	int num = 0;
	for ( int i = 0; i < start; ++i ) {
		++p;
		++num;
	}
	list<Zombie >::iterator p2;
	p2 = p;

	for ( int i = 0; i < 5; ++i ) {
		--p;
		--num;
	}

	for ( int i = 0; i <= 10; ++i ) {
		if ( p2 == p ) {
			cout << "***" << num << "*** ";
		}
		else {
			cout << "[" << num << "] ";
		}
		p->render();
		++num;
		++p;
	}

}


int main() {
	list<Zombie > data;

	default_random_engine dre;
	uniform_int_distribution<int > di( -1000, 1000 );

	//����1 ���� ���� ������ ������ ����Ͽ� ���� ��ü�� 100�� �����Ͽ� ����Ʈ�� �����϶�.
	for ( int i = 0; i < 100; ++i ) {
		int num = di( dre );
		data.push_back( Zombie( num, num ) );
	}
	/*
	1�� ���� ���� ���
	for ( int i=0; i< 100; ++i){
	data.emplace_back(di(dre), di(dre));
	*/

	//���� 2
	cout << "-----------------------------------------------------------------" << endl;
	cout << "[����2] ����Ʈ�� ���Ҹ� ����� 1~ *6* ~ 10" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	print( data, 6 );

	// ���� 3
	int bx = 100, by = 200;
	double dist;
	/*
	���� 3�� ����
	for (auto i = data.begin(); i != data.end(); ++i) {
	dist = sqrt((bx - i->getX())*(bx - i->getX()) + (by - (i->getY())) * (by - (i->getY())));
	if (dist == 0) {
	i->decHP(i->getHP());
	}
	else {
	i->decHP(1000 / dist);
	}
	}
	*/


	for ( auto &d : data ) {
		dist = sqrt( (bx - d.getX())*(bx - d.getX()) + (by - (d.getY())) * (by - (d.getY())) );

		if ( dist == 0 ) {
			d.decHP( d.getHP() );
		}
		else {
			d.decHP( 1000 / dist );
		}
	}

	// ����4��
	/*
	data.sort([](const Zombie& a, const Zombie& b) {
	return a.getHP() < b.getHP();
	});
	*/
	data.sort( [&data]( Zombie& a, Zombie & b )
	{
		return a.getHP() < b.getHP();
	} );

	cout << "-----------------------------------------------------------------" << endl;
	cout << "[����4] ����Ʈ�� ���Ҹ� �����(���� ��ġ6)" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	print( data, 6 );


	/*
	����5�� ����
	data.remove_if([](const Zombie& a) {
	return !a.isAlive();
	});
	*/

	for ( auto d : data ) {
		auto db = remove_if( data.begin(), data.end(), [&data]( const Zombie& a ) {
			if ( a.isAlive() == false ) {
				return true;
			}
			return false;
		} );
		data.erase( db, data.end() );
	}

	cout << "-----------------------------------------------------------------" << endl;
	cout << "[����5] ����Ʈ�� ���Ҹ� ����� (���� ��ġ6)" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "������ �� " << data.size() << endl;
	print( data, 6 );



	int datanum = 100 - data.size();

	for ( int i = 0; i < datanum; ++i ) {
		data.insert( data.begin(), Zombie( di( dre ), di( dre ) ) );
	}
	/*
	����6�� ����
	data.insert(data.begin(), 100 - data.size(), { di(dre), di(dre) });
	*/


	cout << "-----------------------------------------------------------------" << endl;
	cout << "[����6] ���� ������ ����(������ġ21)" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "������ �� " << data.size() << endl;
	print( data, 21 );
	/*
	//���� 7 ��
	ofstream out("��������.txt");
	out << data;
	out.close();



	data.clear();
	cout << endl;
	cout << "���� �������" << data.size() << endl;

	ifstream in("��������.txt");
	int x;
	int y;
	int hp;
	while (in >> x >> y >> hp )
	data.push_back(Zombie(x, y, hp));
	in.close();

	cout << "-----------------------------------------------------------------" << endl;
	cout << "[����8] ���Ͽ��� �о�� �� ���(������ġ 21)" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "������ �� " << data.size() << endl;
	print(data, 21);
	*/
}

ostream &operator <<( ostream &c, list <Zombie> data ) {
	for ( list< Zombie>::iterator i = data.begin(); i != data.end(); ++i )
		c << (*i).getX() << "\\t" << (*i).getY() << "\\t" << (*i).getHP();
	cout << endl;
	return c;
}
/*
���� 7�� ����
ostream& operator<<(ostream& out, const list<Zombie>& data) {
for (auto d : data)
out << d.getX() << " " << d.getY() << " " << d.getHP() << endl;

return out;
}

���� 8�� ����
istream &operator >>(istream & in, list<Zombie>& data) {
int a, b, c;
while (in >> a >> b >> c) {
data.emplace_back(a, b, c);
}
return in;
}
*/
