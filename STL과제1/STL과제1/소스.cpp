#include<iostream>
#include<random>
#include<fstream>
#include<ctime>
#include<string>
#include <vector>
#include<algorithm>
#include <Windows.h> //clear ����ϱ� ���Ͽ�

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
	default_random_engine dre;    // �⺻ ���� ���
	vector<randData> sql;
	bool stlGUI = true;
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// ���� ���̵� ������ ���� �κ�
	string s("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789-_+");
	vector<char> v(s.begin(), s.end());
	/*
	���� �Լ��� ����Ͽ� ID�� �̾ƾ� �ϴµ� ID������� ��� ���°� �Ϲ����̴�.
	������ ��� �����ϰ� �Ҽ� ������ ����Ʈ�� a~Z���� �Է��Ͽ� �������� �ش�
	�迭�� �ִ� ����? �κ��� �������� �Ұ��̴�.
	list<char> cont(s.begin(), s.end());
	cont.size() �� 65�� �����͸� �����.
	cout << cont.size() << endl;
	*/
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	saveData(v, dre, initDataValue);
	sql = loadData(sql);
	cout << "------------------------------------------------------------" << endl;
	cout << "\t\t\t�ʱ� ����� ���" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << endl;
	cout << "���̵� �Է����ּ��� : ";
	cin >> myID;
	cout << "������ �Է��� �ּ��� : ";
	cin >> myScore;
	sql.push_back(make_pair(myID, myScore));
	system("cls");
	/*
	�䱸���׿��� �� ������ �������ζ�� ���� ���
	���� ���� id, �� ������ ó�� ���۽� �ޱ�� �Ͽ���.
	�Ź� ���� �Ҷ����� �����°��� ������ ������ �̰��� ���� Ȯ���� ���!
	*/
	while (stlGUI) {
		int selectNum;
		cout << "------------------------------------------------------------" << endl;
		cout << "\t\t2012180004 ��â�� STL ����1" << endl;
		cout << "\t\tID : " << myID << "  Score : " << myScore << endl;
		cout << "\t\t�� ��ϵ� DB ���� : " << sql.size() << "�� " << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << "1. ���Ӱ� DB �����ϱ� (" << initDataValue << " ��)" << endl;
		cout << "2. ���� DB ���� �����ϱ�" << endl;
		cout << "3. �ڽ��� ID, ���� �����ϱ�" << endl;
		cout << "4. ���� ���� ��% �ΰ�..?" << endl;
		cout << "5. ID�� �������� ��������" << endl;
		cout << "6. ������ �������� ��������" << endl;
		cout << "7. �� ���� ���Ʒ��� 10�� �𿩶�" << endl;
		cout << "8. ����� DB �ҷ�����" << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << endl;
		cout << "��ȣ�� �Է��ϼ��� : ";
		cin >> selectNum;

		switch (selectNum) {
		case 1:
			saveData(v, dre, initDataValue);
			system("cls");
			cout << "��� : ��� DB�� �ٽ� �����Ͽ����ϴ�..!" << endl;
			sql = loadData(sql);
			sql.push_back(make_pair(myID, myScore));
			/*
			DB������ �����ϸ鼭 �ٽ� DB�� �����ϸ� ������ �� ���̵�� ������ �������.
			�׺κ��� �ذ��ϱ� ���Ͽ� �ٽ� push_back�� ���ش�.
			*/
			break;
		case 2:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t���� DB ���� �����ϱ�" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			cout << "DB ������ �Է����ּ��� : ";
			cin >> initDataValue;
			system("cls");
			cout << "��� : DB�� �ִ� " << initDataValue << "���� ���� �����մϴ�." << endl;
			break;

		case 3:
			system("cls");
			int mLocation;
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t�ڽ��� ID, ���� �����ϱ�" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			mLocation= myIDLocation(sql);
			//cout << "���� " << mLocation << "�� �ֽ��ϴ�." << endl;
			cout << endl;
			cout << "���̵� �Է����ּ��� : ";
			cin >> myID;
			cout << "������ �Է��� �ּ��� : ";
			cin >> myScore;
			sql[mLocation].first = myID;
			sql[mLocation].second = myScore;

			system("cls");
			cout << "��� : ID, ������ �����Ͽ����ϴ�." << endl;
			break;

		case 8:
			system("cls");
			printAll(sql);
			break;

		default:
			system("cls");
			cout << "��� : �޴��� ���� ����Դϴ�..!" << endl;
			break;
		};



	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// �����ϱ�

	/*
	�õ尪�� �ִ°� ���� srand ������ �õ尪�� �־ ������ �ȵǼ� å�� ã�ƺ� ���
	998���������� �õ尪�ִ°��� Ȯ���Ͽ� �����Ͽ���.
	*/
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// �ҷ�����

	/*
	void �ϰ�� �����ͷ� �Ͽ��� �ű���� ������
	Ȯ���ϰ�  vector<randData> loadVector(vector<randData> sql) �Ͽ��� ������ �ް� �Ͽ���.
	*/
	//------------------------------------------------------------------------------------------------------------------------------------------------------------
	// ����ϱ�
	//
	//------------------------------------------------------------------------------------------------------------------------------------------------------------


}


void saveData(vector<char> v, default_random_engine dre, int limitValue) {
	dre.seed((unsigned int)time(NULL));
	uniform_int_distribution<>ui(1, 100000);    // ���� ����
	uniform_int_distribution<>nd(0, 64); // �׳� ����
	uniform_int_distribution<>id(5, 15); // ���̵� ����

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
		cout << "���̵� : " << d.first << "\t\t���� : " << d.second << endl;
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