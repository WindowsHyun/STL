//---------------------------------------------------------------------------
// 2016�� 05�� 30��
//
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "save.h"

using namespace std;
/*

*/

int main() {
	vector<int> v{ 1,2,3,4,5 };
	reverse( v.begin(), v.end() );
	for ( int d : v )
		cout << d << " ";
	cout << endl;
	//save();
}