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

	cout << endl << v.size() << endl;

}