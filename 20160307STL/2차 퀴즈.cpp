#include <iostream>
#include < vector>
#include <set>
#include <random>
#include <algorithm>

using namespace std;

class Cookie {
	int id;
public:
	Cookie( int n ) : id( n ) {}
	operator int() const { return id; };
};

int main() {
	vector<Cookie> v;
	v.reserve( 10000 );
	default_random_engine dre;
	uniform_int_distribution<int> ui( 1, 10000 );
	// random_shuffle 이라는 함수를 이용해서 정상적으로 만든걸 뒤섞을수 있다.

	// [문제1]
	// 랜덤값을 하나 만든다
	while ( v.size() != 10000 ) {
		int n = ui( dre );
		// 현재까지 만든 쿠키 중에 같은 값이 있나 찾는다.
		auto p = find( v.begin(), v.end(), n );
		// 같은 값이 없다면현재 값으로 쿠키를 만들어 추가한다
		if ( p == v.end() ) {
			v.push_back( n );
		}
	}

	// [문제2]
	sort( v.begin(), v.end() );
	auto p = unique( v.begin(), v.end() );
	v.erase( p, v.end() );
	cout << v.size() << endl;

	// [문제3]
	set<Cookie> s( v.begin(), v.end() );
	cout << s.size() << endl;

	/*
		for ( int i = 0; i < v.capacity(); ++i ) {
			v.push_back( ui( dre ) );
			auto p = unique( v.begin(), v.end() );
				v.erase( p, v.end() );
		}
		sort( v.begin(), v.end(), []( auto a, auto b ) {
			return a < b;
		} );

		while ( v.size() != 10000 ) {
			v.erase( unique( v.begin(), v.end() ), v.end() );
			v.push_back( ui( dre ) );
		}

		for ( const Cookie d : v )
			cout << d << " ";
		cout << endl;

		cout << endl << v.size() << endl;*/
}