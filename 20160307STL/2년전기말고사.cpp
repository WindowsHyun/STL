#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

string cookies[] = {
	"�밨�� ��Ű��", "����� ��Ű", "����ȣ�� ��Ű", "������� ��Ű", "������ ��Ű",
};

enum { BREAVE = 0, STRAWBERRY, GOOMIHO, WIZARD, PIRATE };

//-------------------------------------------------------------------------------
// Ŭ���� Cookie - ����ȭ�鿡 ������ ��� ��Ű�� �� Ŭ������ ǥ��!
//
// �̿� ���� ���ӿ��� Ŭ������ �ʿ��Ѱ��� �Բ�
// ��� ����� �����ϴ� ���� ������ �ƴ��� �����ϰ� ����غ��߰ڴ�.
//-------------------------------------------------------------------------------

class Cookie {
	int x, y;
	int kind;
	bool select;
public:
	Cookie() : x(), y(), kind(), select() {}
	Cookie( int x, int y, int kind ) : x( x ), y( y ), kind( kind ), select( false ) {}

	void update( int nx, int ny ) {
		x = nx;
		y = ny;
	};

	void render() {
		cout << cookies[kind] << "\t [" << x << ", " << y << "]" << endl;
	}

	void setSelect( bool s ) {
		select = s;
	}
	bool getSelect() const {
		return select;
	}
	int getKind() const {
		return kind;
	}
	void setKind( int n ) {
		kind = n;
	}
	int getX() const { return x; }
	int getY() const { return y; }
};

//-------------------------------------------------------------------------------
int main()
//-------------------------------------------------------------------------------
{
	//-------------------------------------------------------------------------------
	// � �����̳ʸ� ����ϴ� ���� ������ ���� ������ �ʴ´�.
	// �ϴ� ���� �����ϴٰ� �ϴ� ���͸� ����ϱ�� �Ѵ�.
	//-------------------------------------------------------------------------------

	vector<Cookie> cont;
	// ������ �����ϸ� 50���� ��Ű�� �ִ� �����̴�.
	// �� ��Ű���� �߷��� ������ ������ ���� �浹 �˻縦 �Ѵ�.
	// �� �˰����� ��� ������ ���� �𸣰ڴ�.
	// �ϴ�, ������ ���� ���� 50���� ��Ű�� �����Ѵ�.
	// ���ǻ� seed�� ������� �ʾ� �׻� ���� ���� ���� �������� �Ͽ���.

	default_random_engine dre;
	uniform_int<int> x( 0, 599 ), y( 0, 799 ), kind( 0, 4 );

	for ( int i = 0; i < 50; ++i )
		cont.push_back( Cookie( x( dre ), y( dre ), kind( dre ) ) );

	// [����1] �ݺ��ڸ� ������ �� �̸� �̿��Ͽ� ������ ��Ű���� �������϶�.
	// [����] ��Ű�� ����Լ� render�� ȣ���Ѵ�.

	cout << endl;
	cout << "[���� 1] ��� ���" << endl;

	for ( auto d : cont )
		d.render();

	// [���� 2] ȭ���� ��� ����ȣ�� ��Ű�� ���õǾ��ٰ� ����.
	//			���õ� ��Ű�� select ���� true�� ������.
	// 50���� ��Ű �� ����ȣ���� ����� ����϶�.

	int n = 0;
	auto p = cont.begin();

	for ( p; p != cont.end(); ++p ) {
		if ( p->getKind() == 2 ) {
			n += 1;
			p->setSelect( true );
		}
	}

	cout << endl;
	cout << "[���� 2] ��� ���" << endl;
	cout << "����ȣ�� ��Ű�� �� " << n << endl;
	cout << endl;

	// [���� 3] �˰��� �Լ� remove_if�� �̿��Ͽ� ���õ� ����ȣ�� ��Ű�� ���Ϳ��� ������.

	cont.erase( remove_if( cont.begin(), cont.end(), [](const Cookie& a) {
		return a.getSelect();
	} ), cont.end());

	cout << endl;
	cout << "[���� 3] ��� ���" << endl;
	cout << "����ȣ�� ��Ű�� ���� �� ������ ���� ��" << cont.size() << endl;
	cout << endl;

	// [���� 4] ������ ����ȣ�� ��Ű�� ���� ��ŭ ���ο� ��Ű�� �����Ͽ� ���Ϳ� �߰��϶�.
	// ���� ������ 50�� �����Ҷ��� ���� ���� ����ϸ� �ȴ�.

	for ( int i = 0; i < n; ++i )
		cont.push_back( Cookie( x( dre ), y( dre ), kind( dre ) ) );

	cout << endl;
	cout << "[���� 4] ��� ���" << endl;
	cout << "������ ��Ű �� ��ŭ ���� ������ �� ������ ���� �� " << cont.size() << endl;
	cout << endl;

	// [���� 5] ����ȣ�� ��Ű�� ���� �����Ͽ� ����ȣ�� ��Ű�� ��ų �������� �� ã��.
	// ����ȣ�� ��Ű�� �ƴ� ��Ű �� ���Ƿ� 10���� ��� ����ȣ�� ��Ű�� ���Ž��Ѷ�.

	uniform_int<int> ui( 0, 50 );
	
	for ( int i = 0; i < 10;) {
		int rand = ui( dre );
		if ( cont[rand].getKind() != 2 ) {
			cont[rand].setKind( 2 );
			++i;
		}
	}

	// [���� 6] �޴����� 180���� ��������. �� y ��ǥ���� ������ �������ٴ� ���̴�.
	// ��Ű�� ���忡�� ���� ���� ���� �ִ� ��Ű�� �ٴ����� �߶��ϰ� �Ǵ� ���̴�.
	// �׷����ϰ� �����Ϸ��� ��Ű���� y��ǥ �������� ������ �� y ��ǥ�� ���� ū ��Ű����
	// �ٴ����� �߶��ϵ��� �����ϴ� ���� �մ��� ���̴�.
	// ���� cont �� �ִ� ��Ű���� y ��ǥ ������������ �����϶�.

	sort( cont.begin(), cont.end(), []( const Cookie& a, const Cookie& b ) {
		return a.getY() > b.getY();
	} );

	cout << endl;
	cout << "[���� 6] ��� ���" << endl;
	cout << "y��ǥ ������ ���� �� ���" << endl;
	cout << endl;
	for ( auto data : cont )
		data.render();
}