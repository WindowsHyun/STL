#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <functional>
using namespace std;

//----------------------------------------------------------------------------
int main()
//----------------------------------------------------------------------------
{
	//----------------------------------------------------------------------------
	// ������ ������ ������ ���� �ܾ�(string) ������ vector v�� �о� �Դ�.
	//
	// �� �������� �ܾ�� ���� ���Ͽ��� �������� �и��� ���������� ���Ѵ�.
	//----------------------------------------------------------------------------
	ifstream ifs( "80�ϰ��� ��������.txt" );

	vector<string> v( { istream_iterator<string>( ifs ), istream_iterator<string>() } );
	ifs.close();

	cout << "---------------------" << endl;
	cout << "STL �⸻�����Դϴ�." << endl;
	cout << "---------------------" << endl;

	cout << endl;
	cout << "��� " << v.size() << "���� �ܾ �о����ϴ�." << endl;

	// ������� ������ �Ǵ� �� Ȯ���� �� ������ �����ϵ��� ����.

	// ������ ó������ �ٽ� ���� �ʵ��� �Ѵ�.
	// vector<string> v �� �̿��Ͽ� ������� ������ �ذ�����.

	// [���� 1] �Ҽ��� ���� �������� ���� �󵵸� ���� ����ϴ� ���α׷��� �ۼ��϶�.
	// �������� �����ڶ� ������ ������ 1byte �ƽ�Ű ���ڸ� ���Ѵ�.
	// ��� ȭ���� �����϶�.
	//
	// (����) �����̳� map�� ����Ѵ�.
	// ���� �迭�� ����� �� �ִ� map�� ����� �̿��Ѵ�.

	map<unsigned char, int> m1;

	for ( auto iter = v.begin(); iter != v.end(); ++iter ) {
		for ( auto iter2 = iter->begin(); iter2 != iter->end(); ++iter2 ) {
			m1[*iter2]++;
		}
	}

	cout << endl << endl;
	cout << "[���� 1]�� ���" << endl;
	for ( auto d : m1 )
		cout << d.first << " --> " << d.second << endl;

	// [���� 2] ���� 1�� ����� ���� �󵵰� ���� �ͺ��� ����϶�.
	// ��� ȭ���� �����϶�.
	// (����) �����̳ʸ� �ϳ� �� �����϶�.
	// ��� ȭ���� �����϶�.
	map <int, unsigned char, std::greater<int>> m2;

	for ( auto d : m1 ) {
		m2.insert( pair<int, unsigned char>( d.second, d.first ) );
	}


	cout << endl << endl;
	cout << "[���� 2]�� ���" << endl;
	for ( auto d : m2 )
		cout << d.first << " --> " << d.second << endl;


	// [���� 3] ���� v�� �ܾ��� ���̰� �� ������ �������� �����϶�.
	// ���̰� ���� �� �ܾ ���� �տ� ������ �϶�.
	// ��� ȭ���� �����϶�.
	// (����) lambda�� ����Ѵ�.

	sort( v.begin(), v.end(), []( const string& a, const string& b ) {
		return a.length() > b.length();
	} );

	cout << endl << endl;
	cout << "[���� 3]�� ��� - 10000��°���� 20��" << endl;
	for ( int i = 10000; i < 10020; ++i )
		cout << v[i] << endl;


	// [���� 4] ���� 3�� ����� ������ ��� �ߺ��� �ܾ ������ �˾Ҵ�.
	// ��� �ܾ �� �� ���� �����ϵ��� ������ ������ ������ ��
	// ���� 3�� ���� �ܾ� ���� ������ ���� �϶�.
	// ��� ȭ���� �����϶�.
	// (����) �˰��� �Լ� unique�� ����Ѵ�.

	
	sort( v.begin(), v.end() );

	v.erase( unique( v.begin(), v.end() ), v.end() );

	sort( v.begin(), v.end(), []( const string& a, const string& b ) {
		return a.length() > b.length();
	} );

	cout << endl << endl;
	cout << "[���� 4]�� ���" << endl;
	cout << "�ߺ��� �ܾ ���� �� ������ ���Ҽ� : " << v.size() << endl;

	cout << "10000��°���� 10���� �ܾ�" << endl;
	for ( int i = 10000; i < 1010; ++i )
		cout << v[i] << endl;
	cout << endl << endl;
	cout << "���� �ڿ��� ���� 20���� �ܾ�" << endl;
	for ( auto i = v.rbegin(); i <= v.rbegin() + 20; ++i )
		cout << *i << endl;

	// [���� 5] ���̰� 7�� �ܾ �� ���� �ִ� �� ����϶�.

	int n;
	n = 0;
	for ( auto d : v ) {
		if ( d.length() == 7 ) {
			++n;
		}
	}

	cout << endl << endl;
	cout << "[���� 5]�� ��� " << endl;
	cout << "���̰� 7�� �ܾ��� �� : " << n << endl;

	// [���� 6] ���̰� 7�� �ܾ �������� ���� �ִ�.
	// ���̰� 7�� �ܾ ���� ���� vector<string> v2�� �Ű� ��ƶ�.
	// v���� ���̰� 7�� �ܾ �������� �ʾƾ� �Ѵ�.
	// (����) partition_copy() �� ����Ѵ�.

	vector<string> v2;
	v2.reserve( n+1 );

	partition_copy( v.begin(), v.end(), v2.begin(), v.begin(), []( string a )->bool{ 
			return a.length() == 7;
	} );


	cout << endl << endl;
	cout << "[���� 6]�� ��� " << endl;
	cout << "���̰� 7�� �ܾ��� �� " << v2.size() << endl;

	cout << "�տ��� ���� 20�� ���" << endl;
	for ( int i = 0; i < 20; ++i )
		cout << v2[i] << endl;
	cout << endl;



}