#include<iostream>
#include<random>
#include<fstream>
#include<ctime>
#include<string>
#include <vector>
#include<algorithm>
#include <Windows.h> //clear 사용하기 위하여
#include <iomanip> // 깔끔한 출력을 위하여?

using namespace std;
using randData = pair<string, int>;
static int initDataValue = 10000;
static string myID;
static int myScore;

void saveData(vector<char>, default_random_engine, int);
//void loadData(vector<randData>);
vector<randData> loadData(vector<randData>);
void printAll(vector<randData>);
int myIDLocation(vector<randData>);

int main() {
	default_random_engine dre;    // 기본 엔진 사용
	vector<randData> sql;
	bool stlGUI = true;
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 랜덤 아이디 생성을 위한 부분
	string s("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789-_+");
	vector<char> v(s.begin(), s.end());
	/*
	랜덤 함수를 사용하여 ID를 뽑아야 하는데 ID같은경우 영어를 쓰는게 일반적이다.
	하지만 영어를 랜덤하게 할수 없으니 리스트에 a~Z까지 입력하여 랜덤으로 해당
	배열에 있는 숫자? 부분을 가져오게 할것이다.
	list<char> cont(s.begin(), s.end());
	cont.size() 총 65개 데이터를 등록함.
	cout << cont.size() << endl;
	*/
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	/*
	ifstream read("2012180004.txt");
	char dataClear;
	if (read) {
		// 파일이 존재하지 않을경우
		cout << "DB가 존재합니다." << endl;
		cout << "DB를 새로 만들겠습니까? (Y/N)";
		cin >> dataClear;
		system("cls");
	}
	if (dataClear == 'Y' || dataClear == 'y') {
		cout << "결과 : DB초기화 및 새롭게 저장하였습니다." << endl;
		saveData(v, dre, initDataValue);
	}
	else {
		cout << "결과 : DB를 유지한 상태로 시작합니다." << endl;
	}
	sql = loadData(sql);
	cout << "------------------------------------------------------------" << endl;
	cout << "\t\t\t초기 사용자 등록" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << endl;
	cout << "아이디를 입력해주세요 : ";
	cin >> myID;
	cout << "점수를 입력해 주세요 : ";
	cin >> myScore;
	sql.push_back(make_pair(myID, myScore));
	system("cls");
	/*
	요구사항에서 내 점수를 기준으로라는 말을 듣고선
	따로 직접 id, 와 점수를 처음 시작시 받기로 하였다.
	매번 실행 할때마다 나오는것은 귀찮긴 하지만 이것이 가장 확실한 방법!
	*/
	myID = "WindowsHyun";
	myScore = 1806383;
	sql = loadData(sql);
	sql.push_back(make_pair(myID, myScore));


	while (stlGUI) {
		int selectNum;
		cout << "------------------------------------------------------------" << endl;
		cout << "\t\t2012180004 권창현 STL 과제1" << endl;
		cout << "\t\tID : " << myID << "  Score : " << myScore << endl;
		cout << "\t\t총 등록된 DB 갯수 : " << sql.size() << "개 " << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "1. 새롭게 DB 저장하기 (" << initDataValue << " 개)" << endl;
		cout << "2. 저장 DB 갯수 변경하기" << endl;
		cout << "3. 자신의 ID, 점수 변경하기" << endl;
		cout << "4. 나는 상위 몇% 인가..?" << endl;
		cout << "5. ID를 기준으로 오른차순" << endl;
		cout << "6. 점수를 기준으로 내림차순" << endl;
		cout << "7. 내 위로 내아래로 10명 모여라" << endl;
		cout << "8. 저장된 DB 불러오기" << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << endl;
		cout << "번호를 입력하세요 : ";
		cin >> selectNum;

		switch (selectNum) {
		case 1:
			saveData(v, dre, initDataValue);
			system("cls");
			cout << "결과 : 모든 DB를 다시 저장하였습니다..!" << endl;
			sql = loadData(sql);
			sql.push_back(make_pair(myID, myScore));
			/*
			DB갯수를 변경하면서 다시 DB를 저장하면 기존의 내 아이디와 점수는 사라진다.
			그부분을 해결하기 위하여 다시 push_back을 해준다.
			*/
			break;
		case 2:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t저장 DB 갯수 변경하기" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			cout << "DB 갯수를 입력해주세요 : ";
			cin >> initDataValue;
			system("cls");
			cout << "결과 : DB를 최대 " << initDataValue << "까지 저장 가능합니다." << endl;
			break;

		case 3:
			system("cls");
			int mLocation;
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t자신의 ID, 점수 변경하기" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			mLocation = myIDLocation(sql);
			//cout << "현재 " << mLocation << "에 있습니다." << endl;
			cout << endl;
			cout << "아이디를 입력해주세요 : ";
			cin >> myID;
			cout << "점수를 입력해 주세요 : ";
			cin >> myScore;
			sql[mLocation].first = myID;
			sql[mLocation].second = myScore;

			system("cls");
			cout << "결과 : ID, 점수를 변경하였습니다." << endl;
			break;

		case 4:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t나는 상위 몇% 인가..?" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			cout << "점수를 기준으로 오름차순 정렬을 하는중 입니다..!" << endl;
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.second > b.second;
			});
			mLocation = myIDLocation(sql)+1;
			system("cls");
			double percentage, fullsize;
			fullsize = sql.size();
			percentage = mLocation / fullsize;
			cout << "전체 인원 : " << sql.size() << endl;
			cout << "나의 등수 : " << mLocation << endl;
			cout << "계산식 : " << mLocation << "/" << sql.size() << "*100" << endl;
			cout << "결과 : " << percentage * 100 << "%에 있습니다." << endl;
			break;

		case 5:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\tID를 기준으로 오른차순 중입니다..!" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.first < b.first;
			});
			system("cls");
			cout << "결과 : ID기준으로 오름차순 완료..!" << endl;
			break;

		case 6:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t점수를 기준으로 내림차순 중입니다..!" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.second < b.second;
			});
			system("cls");
			cout << "결과 : 점수기준으로 내림차순 완료..!" << endl;
			break;

		case 7:
			system("cls");
			//int mLocation;
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t자신의 ID, 점수 변경하기" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			// 일단 점수를 기준으로 오름차순 하고선 진행하자.
			cout << "점수를 기준으로 오름차순 정렬을 하는중 입니다..!" << endl;
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.second > b.second;
			});
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			mLocation = myIDLocation(sql);
			cout << "현재 " << mLocation << "에 있습니다." << endl << endl;
			int startrange, endrange;
			startrange = -10, endrange = 10;

			if (mLocation <= 10) {
				startrange = 10 - 10 - mLocation;
			}
			if (mLocation + 10 >= sql.size()) {
				endrange = sql.size() - mLocation - 1;
			}

			for (int i = mLocation + startrange; i < mLocation + endrange; ++i) {
				if (i == mLocation)
					cout << "--> ";
				cout << i << ". 아이디 : " << sql[i].first << setw(20) << "\t\t점수 : " << sql[i].second << endl;
			}


			break;

		case 8:
			system("cls");
			printAll(sql);
			break;

		default:
			system("cls");
			cout << "결과 : 메뉴에 없는 기능입니다..!" << endl;
			break;
		};



	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 저장하기

	/*
	시드값을 주는걸 몰라서 srand 에서의 시드값을 주어도 변경이 안되서 책을 찾아본 결과
	998페이지에서 시드값주는것을 확인하여 수정하였다.
	*/
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 불러오기

	/*
	void 일경우 포인터로 하여금 옮길수도 있지만
	확실하게  vector<randData> loadVector(vector<randData> sql) 하여금 리턴을 받게 하였다.
	*/
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 출력하기
	//
	//------------------------------------------------------------------------------------------------------------------------------------------------------------


}


void saveData(vector<char> v, default_random_engine dre, int limitValue) {
	dre.seed((unsigned int)time(NULL));
	uniform_int_distribution<>ui(1, 1000000000);    // 고르게 분포
	uniform_int_distribution<>nd(0, 64); // 그냥 분포
	uniform_int_distribution<>id(5, 15); // 아이디 길이

	string userid;
	ofstream out("2012180004.txt");
	for (int i = 0; i < limitValue; ++i) {
		userid.clear();
		for (int j = 0; j < id(dre); ++j) {
			userid += v[nd(dre)];
		}
		out << userid << " " << ui(dre) << endl;
	}

}

vector<randData> loadData(vector<randData> sql) {
	sql.clear();
	ifstream in("2012180004.txt");
	string _line;
	char txtid[200], txtscore[200];;

	while (!in.eof()) {
		in >> txtid;
		in >> txtscore;

		if (atoi(txtscore) == 0)
			break;
		//in.getline(txtid, sizeof(txtid));
		//cout << "ID : "<<  txtid  << "\t\t\t\t\tScore : " <<  txtscore << endl;
		sql.push_back(make_pair(txtid, atoi(txtscore)));
	}
	return sql;
}

void printAll(vector<randData> sql) {
	for (auto d : sql) {

		cout << "아이디 : " << d.first << setw(20) << "\t\t점수 : " << d.second << endl;
	}
}

int myIDLocation(vector<randData> sql) {
	auto p = find_if(sql.begin(), sql.end(), [](const randData& a) {
		if (a.first == myID)
			return true;
		return false;
	});
	if (p != sql.end()) {
		return p - sql.begin();
	}
	else {
		return -1;
	}
}