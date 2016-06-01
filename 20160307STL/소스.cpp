//---------------------------------------------------------------------------
// 2016³â 05¿ù 30ÀÏ
//
//---------------------------------------------------------------------------
#include <iostream>
#include <set>
#include "save.h"

using namespace std;

class Game {
	int level{ 19 };
public:
	Game( int n ) : level( n ) {}
	bool operator< ( const Game& other ) const {
		return level < other.level;
	}
};

int main() {
	set<Game> s;
	s.insert( { 1, 10, 5, 3, 19 } );
	//save();
}