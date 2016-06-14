#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

string cookies[] = {
	"용감한 쿠키군", "딸기맛 쿠키", "구미호맛 쿠키", "마법사맛 쿠키", "해적맛 쿠키",
};

enum { BREAVE = 0, STRAWBERRY, GOOMIHO, WIZARD, PIRATE };

//-------------------------------------------------------------------------------
// 클래스 Cookie - 게임화면에 나오는 모든 쿠키를 이 클래스로 표현!
//
// 이와 같은 게임에서 클래스가 필요한가와 함께
// 상속 관계로 구현하는 것이 좋을지 아닌지 진지하게 고민해봐야겠다.
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
	// 어떤 컨테이너를 사용하는 것이 좋을지 감이 잡히지 않는다.
	// 일단 가장 무난하다고 하는 벡터를 사용하기로 한다.
	//-------------------------------------------------------------------------------

	vector<Cookie> cont;
	// 게임을 시작하면 50개의 쿠키가 있는 상태이다.
	// 이 쿠키들은 중력의 영향을 받으며 서로 충돌 검사를 한다.
	// 이 알고리즘을 어떻게 구현할 지는 모르겠다.
	// 일단, 임의의 값을 갖는 50개의 쿠키를 생성한다.
	// 편의상 seed를 사용하지 않아 항상 같은 램덤 값이 나오도록 하였다.

	default_random_engine dre;
	uniform_int<int> x( 0, 599 ), y( 0, 799 ), kind( 0, 4 );

	for ( int i = 0; i < 50; ++i )
		cont.push_back( Cookie( x( dre ), y( dre ), kind( dre ) ) );

	// [문제1] 반복자를 선안한 후 이를 이용하여 생성된 쿠키들을 렌더링하라.
	// [도움말] 쿠키의 멤버함수 render를 호출한다.

	cout << endl;
	cout << "[문제 1] 출력 결과" << endl;

	for ( auto d : cont )
		d.render();

	// [문제 2] 화면의 모든 구미호맛 쿠키가 선택되었다고 하자.
	//			선택된 쿠키의 select 값을 true로 만들어라.
	// 50개의 쿠키 중 구미호맛이 몇개인지 출려하라.

	int n = 0;
	auto p = cont.begin();

	for ( p; p != cont.end(); ++p ) {
		if ( p->getKind() == 2 ) {
			n += 1;
			p->setSelect( true );
		}
	}

	cout << endl;
	cout << "[문제 2] 출력 결과" << endl;
	cout << "구미호맛 쿠키의 수 " << n << endl;
	cout << endl;

	// [문제 3] 알고리즘 함수 remove_if를 이용하여 선택된 구미호맛 쿠키를 벡터에서 지워라.

	cont.erase( remove_if( cont.begin(), cont.end(), [](const Cookie& a) {
		return a.getSelect();
	} ), cont.end());

	cout << endl;
	cout << "[문제 3] 출력 결과" << endl;
	cout << "구미호맛 쿠키를 지운 후 벡터의 원소 수" << cont.size() << endl;
	cout << endl;

	// [문제 4] 지워진 구미호맛 쿠키의 갯수 만큼 새로운 쿠키를 생성하여 벡터에 추가하라.
	// 랜덤 엔진은 50개 생성할때와 같은 것을 사용하면 된다.

	for ( int i = 0; i < n; ++i )
		cont.push_back( Cookie( x( dre ), y( dre ), kind( dre ) ) );

	cout << endl;
	cout << "[문제 4] 출력 결과" << endl;
	cout << "제가한 쿠키 수 만큼 새로 생성한 후 벡터의 원소 수 " << cont.size() << endl;
	cout << endl;

	// [문제 5] 구미호맛 쿠키를 많이 제거하여 구미호맛 쿠키의 스킬 게이지가 꽉 찾다.
	// 구미호맛 쿠키가 아닌 쿠키 중 임의로 10개를 골라 구미호맛 쿠키로 변신시켜라.

	uniform_int<int> ui( 0, 50 );
	
	for ( int i = 0; i < 10;) {
		int rand = ui( dre );
		if ( cont[rand].getKind() != 2 ) {
			cont[rand].setKind( 2 );
			++i;
		}
	}

	// [문제 6] 휴대폰을 180도로 뒤집었다. 즉 y 좌표값이 완전히 뒤집혔다는 말이다.
	// 쿠키들 입장에서 보면 제일 위에 있던 쿠키가 바닥으로 추락하게 되는 샘이다.
	// 그럴듯하게 구현하려면 쿠키들은 y좌표 기준으로 정렬한 후 y 좌표가 가장 큰 쿠키부터
	// 바닥으로 추락하도록 구현하는 것이 합당할 것이다.
	// 현재 cont 에 있는 쿠키들을 y 좌표 내림차순으로 정렬하라.

	sort( cont.begin(), cont.end(), []( const Cookie& a, const Cookie& b ) {
		return a.getY() > b.getY();
	} );

	cout << endl;
	cout << "[문제 6] 출력 결과" << endl;
	cout << "y좌표 순으로 정렬 한 결과" << endl;
	cout << endl;
	for ( auto data : cont )
		data.render();
}