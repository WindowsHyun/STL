#include<iostream>
#include<random>
#include<fstream>
#include<ctime>
#include<string>
#include <vector>
#include<algorithm>
#include <Windows.h> //clear ����ϱ� ���Ͽ�
#include <iomanip> // ����� ����� ���Ͽ�?
#include<minmax.h>

#define INT_MAX_SIZE 2147483647

using namespace std;
using randData = pair<string, int>;
static int initDataValue = 10000;
static double startTime = 0, endTime = 0;
static string myID;
static int myScore;

void saveData(const vector<char>&, default_random_engine, const int&);
//void loadData(vector<randData>);
vector<randData> loadData(vector<randData>);
vector<randData> idSort(vector<randData>);
vector<randData> scoreSort(vector<randData>);
vector<randData> selectSort(vector<randData>, const int&, const int&); // Vector | 1 = ���̵�, 2 = ���� | 1 = ��������, 2 = ��������
void printAll(const vector<randData>&);
int myIDLocation(const vector<randData>&);


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

	ifstream read("2012180004.txt");
	char dataClear;
	if (read) {
		// ������ �������� �������
		cout << "DB�� �����մϴ�." << endl;
		cout << "DB�� ���� ����ڽ��ϱ�? (Y/N)";
		cin >> dataClear;
		system("cls");
	}
	if (dataClear == 'Y' || dataClear == 'y') {
		cout << "��� : DB�ʱ�ȭ �� ���Ӱ� �����Ͽ����ϴ�." << endl;
		saveData(v, dre, initDataValue);
	}
	else {
		cout << "��� : DB�� ������ ���·� �����մϴ�." << endl;
	}
	sql = loadData(sql);
	cout << "------------------------------------------------------------" << endl;
	cout << "\t\t\t�ʱ� ����� ���" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << endl;
	cout << "���̵� �Է����ּ��� : ";
	cin >> myID;
	cout << "������ �Է��� �ּ��� : ";

	while (1) {
		cin >> myScore;
		if (cin.fail() == 1) {
			cin.clear();
			myScore = INT_MAX_SIZE;
			sql.push_back(make_pair(myID, myScore));
			system("cls");
			cout << "���� : INT�� �ִ밪 �̻��� �ʰ��Ͽ� �ִ밪���� ������ �����մϴ�." << endl;
			break;
		}
		else {
			sql.push_back(make_pair(myID, myScore));
			system("cls");
			break;
		}
	}



	/*
	�䱸���׿��� �� ������ �������ζ�� ���� ���
	���� ���� id, �� ������ ó�� ���۽� �ޱ�� �Ͽ���.
	�Ź� ���� �Ҷ����� �����°��� ������ ������ �̰��� ���� Ȯ���� ���!

	myID = "WindowsHyun";
	myScore = 1806383;
	sql = loadData(sql);
	sql.push_back(make_pair(myID, myScore));
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
		cout << "5. ID�� �������� �����ϱ�" << endl;
		cout << "6. ������ �������� �����ϱ�" << endl;
		cout << "7. �� ���� ���Ʒ��� 10�� �𿩶�" << endl;
		cout << "8. ���� ����� �˷���" << endl;
		cout << "9. ����� DB �ҷ�����" << endl;
		cout << "------------------------------------------------------------" << endl;
		cout << endl;
		cout << "��ȣ�� �Է��ϼ��� : ";
		cin >> selectNum;

		switch (selectNum) {
		case 1:
			saveData(v, dre, initDataValue);

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
			mLocation = myIDLocation(sql);
			//cout << "���� " << mLocation << "�� �ֽ��ϴ�." << endl;
			cout << endl;
			cout << "���̵� �Է����ּ��� : ";
			cin >> myID;
			cout << "������ �Է��� �ּ��� : ";
			while (1) {
				cin >> myScore;
				if (cin.fail() == 1) {
					cin.clear();
					myScore = INT_MAX_SIZE;
					system("cls");
					cout << "���� : INT�� �ִ밪 �̻��� �ʰ��Ͽ� �ִ밪���� ������ �����մϴ�." << endl;
					cout << "��� : ID, ������ �����Ͽ����ϴ�." << endl;
					sql[mLocation].first = myID;
					sql[mLocation].second = myScore;
					break;
				}
				else {
					sql[mLocation].first = myID;
					sql[mLocation].second = myScore;
					system("cls");
					cout << "��� : ID, ������ �����Ͽ����ϴ�." << endl;
					break;
				}
			}
			break;

		case 4:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t���� ���� ��% �ΰ�..?" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			// �ϴ� ������ �������� �������� �ϰ� ��������.
			sql = selectSort(sql, 2, 2);
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			mLocation = myIDLocation(sql) + 1;
			//system("cls");
			double percentage, fullsize;
			fullsize = sql.size();
			percentage = mLocation / fullsize;
			cout << endl << "��ü �ο� : " << sql.size() << endl;
			cout << "���� ��� : " << mLocation << endl;
			cout << "���� : " << mLocation << "/" << sql.size() << "*100" << endl;
			cout << "��� : " << percentage * 100 << "%�� �ֽ��ϴ�." << endl;
			break;

		case 5:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\tID�� �������� �����ϱ�" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			sql = idSort(sql);
			break;

		case 6:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t������ �������� �����ϱ�" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			sql = scoreSort(sql);
			break;

		case 7:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t�� ���� ���Ʒ��� 10�� �𿩶�" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			// �ϴ� ������ �������� �������� �ϰ� ��������.
			sql = selectSort(sql, 2, 2);
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			mLocation = myIDLocation(sql);
			cout << endl;
			//cout << "���� " << mLocation + 1 << "�� �ֽ��ϴ�." << endl << endl;
			int startrange, endrange;
			startrange = -10, endrange = 10;

			if (mLocation <= 10) {
				startrange = 10 - 10 - mLocation;
			}
			if (mLocation + 10 >= sql.size()) {
				endrange = sql.size() - mLocation - 1;
			}

			for (int i = mLocation + startrange; i <= mLocation + endrange; ++i) {
				if (i == mLocation)
					cout << "--> ";
				cout << i + 1 << ". ���̵� : " << sql[i].first << setw(20) << "\t\t���� : " << sql[i].second << endl;
			}
			break;


		case 8:
			system("cls");
			cout << "------------------------------------------------------------" << endl;
			cout << "\t\t���� ����� �˷���" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << endl;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			// �ϴ� ������ �������� �������� �ϰ� ��������.
			sql = selectSort(sql, 2, 2);
			//------------------------------------------------------------------------------------------------------------------------------------------------------------
			mLocation = myIDLocation(sql);
			cout << endl;
			cout << "���� ����� ��ü : " << sql.size() << "�� ���� " << mLocation + 1 << "�� �Դϴ�." << endl << endl;

			break;

		case 9:
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

void saveData(const vector<char>& v, default_random_engine dre, const int& limitValue) {
	dre.seed((unsigned int)time(NULL));
	uniform_int_distribution<>ui(1, INT_MAX_SIZE);    // ���� ����
	uniform_int_distribution<>nd(0, 64); // �׳� ����
	uniform_int_distribution<>id(5, 15); // ���̵� ����
	cout << "���� : DB�� ���� �ϰ��ֽ��ϴ�..!" << endl;
	startTime = GetTickCount();
	string userid;
	ofstream out("2012180004.txt");
	for (int i = 0; i < limitValue; ++i) {
		userid.clear();
		for (int j = 0; j < id(dre); ++j) {
			userid += v[nd(dre)];
		}
		out << userid << " " << ui(dre) << endl;
	}
	endTime = GetTickCount();
	system("cls");
	cout << "��� : DB�� �ٽ� �����Ͽ����ϴ�..!" << endl;
	cout << "�ɸ� �ð� : " << (endTime - startTime) / 1000 << "��" << endl;
}

vector<randData> loadData(vector<randData> sql) {
	sql.clear();
	cout << "���� : DB�� Vector�� �߰� �ϰ��ֽ��ϴ�..!" << endl;
	startTime = GetTickCount();
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
	endTime = GetTickCount();
	cout << "��� : DB�� Vector�� �߰��Ͽ����ϴ�..!" << endl;
	cout << "�ɸ� �ð� : " << (endTime - startTime) / 1000 << "��" << endl;
	return sql;
}

vector<randData> idSort(vector<randData> sql) {
	int whatNum;
	cout << "1. ��������" << endl << "2. ��������" << endl;
	cout << "��ȣ�� �Է����ּ��� : ";
	cin >> whatNum;
	cout << endl;
	switch (whatNum) {
	case 1:
		sql = selectSort(sql, 1, whatNum);
		break;
	case 2:
		sql = selectSort(sql, 1, whatNum);
		break;
	default:
		system("cls");
		cout << "��� : ���� ��ȣ�� ����	�ϴ�. �ٽ� �õ����ּ���." << endl;
		break;
	};
	return sql;
}

vector<randData> scoreSort(vector<randData> sql) {
	int whatNum;
	cout << "1. ��������" << endl << "2. ��������" << endl;
	cout << "��ȣ�� �Է����ּ��� : ";
	cin >> whatNum;
	cout << endl;
	switch (whatNum) {
	case 1:
		sql = selectSort(sql, 2, whatNum);
		break;
	case 2:
		sql = selectSort(sql, 2, whatNum);
		break;
	default:
		system("cls");
		cout << "��� : ���� ��ȣ�� ����	�ϴ�. �ٽ� �õ����ּ���." << endl;
		break;
	};
	return sql;
}

vector<randData> selectSort(vector<randData> sql, const int& listData, const int& sortData) {
	if (listData == 1) {
		//ID�� ��������
		if (sortData == 1) {
			//��������
			cout << "���� : ID�� �������� �������� ������ �ϰ��ֽ��ϴ�..!" << endl;
			startTime = GetTickCount();
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.first < b.first;
			});
		}
		else {
			// ��������
			cout << "���� : ID�� �������� �������� ������ �ϰ��ֽ��ϴ�..!" << endl;
			startTime = GetTickCount();
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.first > b.first;
			});
		}
		//���� ��ġ
		endTime = GetTickCount();
		if (sortData == 1)
			cout << "��� : ID�������� �������� ���� �Ϸ�..!" << endl;
		if (sortData == 2)
			cout << "��� : ID�������� �������� ���� �Ϸ�..!" << endl;
		cout << "�ɸ� �ð� : " << (endTime - startTime) / 1000 << "��" << endl;
	}
	else if (listData == 2) {
		//������ ��������
		if (sortData == 1) {
			//��������
			cout << "���� : ������ �������� �������� ������ �ϰ��ֽ��ϴ�..!" << endl;
			startTime = GetTickCount();
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.second < b.second;
			});
		}
		else {
			// ��������
			cout << "���� : ������ �������� �������� ������ �ϰ��ֽ��ϴ�..!" << endl;
			startTime = GetTickCount();
			sort(sql.begin(), sql.end(), [](const randData& a, const randData& b) {
				return a.second > b.second;
			});
		}
		//���� ��ġ
		endTime = GetTickCount();
		if (sortData == 1)
			cout << "��� : ������������ �������� ���� �Ϸ�..!" << endl;
		if (sortData == 2)
			cout << "��� : ������������ �������� ���� �Ϸ�..!" << endl;
		cout << "�ɸ� �ð� : " << (endTime - startTime) / 1000 << "��" << endl;
	}

	return sql;
}

void printAll(const vector<randData>& sql) {
	for (auto d : sql) {

		cout << "���̵� : " << d.first << setw(20) << "\t\t���� : " << d.second << endl;
	}
}

int myIDLocation(const vector<randData>& sql) {
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