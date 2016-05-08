#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include <stdlib.h>

#include "resource.h"
#pragma comment(lib, "Msimg32.lib")										// TransparentBlt ����ϱ� ���� ���̺귯�� ȣ��..
#define _CRT_SECURE_NO_WARNINGS

#define Game_Width 4															// ����
#define Game_Height 4														// ����
#define clear_TotalData 2048													// ���� ������ ����

using namespace std;
using savePair = pair<string, int>;

int clear_Total = 2048;															// ���� ������ ����
int gameData[Game_Width][Game_Height];									// ������ �����ϱ�
int gameDataCopy[Game_Width][Game_Height];							// ������ �����ϱ�
int put_Key;																		// 4 = Left, 8 = UP, 6 = Right, 2 = Down
int realMove = 0;																// ������ ���������� Ȯ�� ( 0 = �ȿ�����, 1 = ������ )
int Score = 0;																	// ���� ����
int gamePause = 0;																// ���� �Ͻ����� ( 0 = ����, 1 = ���� )
int lastScore = 0;																// ���� ������ ���� ����
int mX, mY;																		// ����ó ����� ���� ���콺 ��ǥ
int  click_X, click_Y, temp_X, temp_Y;											// ��óó ����� ���� ��ġ ��ǥ
int target_Score = 2048, now_HighScore = 2;								// ��ǥ ������ 2048, ���� �ִ� ������ ó���̴ϱ� 2
int NewGameAnswer;															// �޽��� �ڽ� Ȯ����� üũ�ϴ� �κ�

vector<savePair> saveData;													// ���̺� ���� �����ϱ� ���� vector ����

typedef struct gameDataXY {
	int bx;
	int by;
}gameDataXY;																	// ���� ��ġ ����

bool GameOver();																// False�� Game Not End, True �� Game End

void Check_4Way(int, HWND);													// ���� üũ�� ���� & HWND�߰� ������ WinGame ���� hwnd�� ����ϱ�����
void Seed_RandNum();															// �������� ���� �ѷ��ֱ�
void CopyMapData();															// �� ������ �Ǿ����� Ȯ���ϱ� ���� ����
void CompareData();															// �� ������ �Ǿ����� Ȯ���ϴ� üũ ��
void Draw_Map(HDC, HDC, HBITMAP, int, int);								// �迭�� ���ڸ� ������ �׷��ִ� �κ�
void NewGame();																// ���ο� ������ �����Ҷ� ȣ���ϴ� �Լ�
void WinGame(HWND);															// ��ǥ������ �����ߴ��� Ȯ����, ����������� �޽���â ����
string transArr(int(*)[Game_Height]);

// -----------------------------------------------------------------------------------------------------------
// ��, �Ʒ�, ����, ������ ���� �����̱�
void Down_PlusNum(int);	// �Ʒ��� �����鼭 ���� �����ϰ�� ���ϱ�
void Down_Num(int);		// ���ڸ� �Ʒ��� ��� ������

void Up_PlusNum(int);		// ���� �ø��鼭 ���� �����ϰ�� ���ϱ�
void Up_Num(int);			// ���ڸ� ���� ��� �ø���

void Left_PlusNum(int);		// �������� �и鼭 ���� �����ϰ�� ���ϱ�
void Left_Num(int);			// ���ڸ� �������� ��� �б�

void Right_PlusNum(int);	// ���������� �и鼭 ���� �����ϰ�� ���ϱ�
void Right_Num(int);		// ���ڸ� ���������� ��� �б�
// -----------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Window Class Name";
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	RegisterClass(&WndClass);
	hwnd = CreateWindow("Window Class Name", "WindowsHyun 2048", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM  lParam) {
	static HDC hdc, mem0dc, mem1dc;
	PAINTSTRUCT ps;
	static HBITMAP image_Number[clear_TotalData];					// 2048���� �迭�� ����� �޸� �����ߤ�����
	static HBITMAP hbmOld, hbmMem, hbmMemOld;					// ������۸��� ���Ͽ�!
	static string gameArr;
	static char debug_Char[500];
	static gameDataXY gameDataXY[Game_Width][Game_Height];
	static int temp_HighNum = 2;
	static RECT rt;

#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);
#endif

	switch (iMsg) {
	case WM_COMMAND:
		srand((unsigned int)time(NULL));
		switch (LOWORD(wParam)) {
		case ID_GAME_NEWGAME:
			NewGameAnswer = MessageBox(hwnd, "������ ������ �ٽ� �����Ͻǲ�����?", "WindowsHyun 2048", MB_OKCANCEL);

			if (NewGameAnswer == IDOK) {
				NewGame();
			}
			break;

		case ID_TARGETSCORE_256:
			target_Score = 256;
			break;

		case ID_TARGETSCORE_512:
			target_Score = 512;
			break;

		case ID_TARGETSCORE_1024:
			target_Score = 1024;
			break;

		case ID_TARGETSCORE_2048:
			target_Score = 2048;
			break;

		case ID_GAME_EXITGAME:
			NewGameAnswer = MessageBox(hwnd, "������ ������ �����Ͻǲ�����?", "WindowsHyun 2048", MB_OKCANCEL);

			if (NewGameAnswer == IDOK) {
				PostQuitMessage(0);
			}
			break;
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;

	case WM_CHAR:
		if (wParam == 'a') {
			//auto savesql = saveData.begin();
			system("cls");
			for (auto d : saveData) {
				cout << d.first << endl;
			}
		}
		cout << endl << endl;
		break;

	case WM_KEYDOWN:
		if (wParam == VK_RIGHT) {
			put_Key = 6, realMove = 0;
			Check_4Way(put_Key, hwnd);
			gameArr = transArr(gameData);
			saveData.push_back(make_pair(gameArr, 0));
		}
		else if (wParam == VK_LEFT) {
			put_Key = 4, realMove = 0;
			Check_4Way(put_Key, hwnd);
			gameArr = transArr(gameData);
			saveData.push_back(make_pair(gameArr, 0));
		}
		else if (wParam == VK_UP) {
			put_Key = 8, realMove = 0;
			Check_4Way(put_Key, hwnd);
			gameArr = transArr(gameData);
			saveData.push_back(make_pair(gameArr, 0));
		}
		else if (wParam == VK_DOWN) {
			put_Key = 2, realMove = 0;
			Check_4Way(put_Key, hwnd);
			gameArr = transArr(gameData);
			saveData.push_back(make_pair(gameArr, 0));
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;

	case WM_LBUTTONUP:
		mX = LOWORD(lParam);
		mY = HIWORD(lParam);
		//���⼭ ����� �ؾ���

		for (int y = 0; y < Game_Height; ++y) {
			for (int x = 0; x < Game_Width; ++x) {
				if (gameDataXY[y][x].bx < mX && mX < 10 + gameDataXY[y][x].bx + 130 &&
					gameDataXY[y][x].by < mY && mY < 10 + gameDataXY[y][x].by + 130) {
					click_Y = y; click_X = x;								// X, Y ��ǥ�� �������ش�.
				}
			}
		}

		/*if (temp_X > click_X) {
			//����
			put_Key = 4, realMove = 0;
			Check_4Way(put_Key, hwnd);
		}
		else if (temp_X < click_X) {
			//������
			put_Key = 6, realMove = 0;
			Check_4Way(put_Key, hwnd);
		}
		else if (temp_Y > click_Y) {
			//��
			put_Key = 8, realMove = 0;
			Check_4Way(put_Key, hwnd);
		}
		else if (temp_Y < click_Y) {
			//�Ʒ�
			put_Key = 2, realMove = 0;
			Check_4Way(put_Key, hwnd);
		}*/

		InvalidateRgn(hwnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		mX = LOWORD(lParam);
		mY = HIWORD(lParam);

		for (int y = 0; y < Game_Height; ++y) {
			for (int x = 0; x < Game_Width; ++x) {
				if (gameDataXY[y][x].bx < mX && mX < 10 + gameDataXY[y][x].bx + 130 &&
					gameDataXY[y][x].by < mY && mY < 10 + gameDataXY[y][x].by + 130) {
					click_Y = y; click_X = x;								// X, Y ��ǥ�� �������ش�.
				}
				else if (mX < 10 || mY > 520 || mX > 520) {
					// �� ������ ����� �Ѵ� 0����
					click_Y = 0; click_X = 0;
					temp_X = 0, temp_Y = 0;
				}
			}
		}

		InvalidateRgn(hwnd, NULL, FALSE);
		break;

	case WM_LBUTTONDOWN:
		mX = LOWORD(lParam);
		mY = HIWORD(lParam);

		for (int y = 0; y < Game_Height; ++y) {
			for (int x = 0; x < Game_Width; ++x) {
				if (gameDataXY[y][x].bx < mX && mX < 10 + gameDataXY[y][x].bx + 130 &&
					gameDataXY[y][x].by < mY && mY < 10 + gameDataXY[y][x].by + 130) {
					click_Y = y; click_X = x;								// X, Y ��ǥ�� �������ش�.
					temp_X = x, temp_Y = y;							// ���콺�� �����̸� �ڵ����� X,Y ��ǥ�� �ٲ�� �׷��Ƿ� �ӽ� ��ġ�� ����
				}
			}
		}

		InvalidateRgn(hwnd, NULL, FALSE);
		break;

	case WM_CREATE:
		srand((unsigned int)time(NULL) + GetTickCount());

		GetClientRect(hwnd, &rt);

		image_Number[0] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));					// ���� ����
		image_Number[2] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP2));					// ���� 2
		image_Number[4] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP3));					// ���� 4
		image_Number[8] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP4));					// ���� 8
		image_Number[16] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP5));					// ���� 16
		image_Number[32] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP6));					// ���� 32
		image_Number[64] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP7));					// ���� 64
		image_Number[128] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP8));				// ���� 128
		image_Number[256] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP9));				// ���� 256
		image_Number[512] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP10));				// ���� 512
		image_Number[1024] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP11));			// ���� 1024
		image_Number[2048] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP12));			// ���� 2048

		put_Key = 0;		// 4 = Left, 8 = UP, 6 = Right, 2 = Down

		for (int i = 0; i < 2; ++i) {
			Seed_RandNum(); //�ʱ� �� 2�� ����!
		}

		gameArr = transArr(gameData);
		saveData.push_back(make_pair(gameArr, 0));
		break;

	case WM_PAINT:
		srand((unsigned int)time(NULL));

		hdc = BeginPaint(hwnd, &ps);

		mem0dc = CreateCompatibleDC(hdc);//2
		hbmMem = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);//3
		SelectObject(mem0dc, hbmMem);
		PatBlt(mem0dc, rt.left, rt.top, rt.right, rt.bottom, WHITENESS);
		hbmMemOld = (HBITMAP)SelectObject(mem0dc, hbmMem);//4
		mem1dc = CreateCompatibleDC(mem0dc);//5

		for (int i = 0; i < Game_Height; ++i) {
			for (int j = 0; j < Game_Width; ++j) {
				//gameDataXY

				gameDataXY[i][j].bx = 10 + j * 130;
				gameDataXY[i][j].by = 10 + i * 130;

				Draw_Map(mem0dc, mem1dc, image_Number[gameData[i][j]], 10 + (i * 130), 10 + (j * 130));
			}
		}
		//-----------------------------------------------------------------------------------------------------------------------------------------------
		// �ְ� ������ ã�ƶ�!
		temp_HighNum = 0;
		for (int i = 0; i < Game_Height; ++i) {
			for (int j = 0; j < Game_Width; ++j) {
				if (temp_HighNum <= gameData[i][j]) {
					temp_HighNum = gameData[i][j];
				}
			}
		}
		now_HighScore = temp_HighNum;

		//-----------------------------------------------------------------------------------------------------------------------------------------------
		// ���� �����͸� �ؽ�Ʈ�� ��ȯ
		sprintf(debug_Char, "WhatKey : %d, realMove : %d, Score = %d, lastScore = %d, mX = %d, mY = %d, ���� ��ġ ��ǥ = (%d, %d), ���� ��ġ ��ǥ = (%d, %d)",
			put_Key, realMove, Score, lastScore, mX, mY, click_X, click_Y, temp_X, temp_Y);
		TextOut(mem0dc, 0, 530, debug_Char, strlen(debug_Char));

		sprintf(debug_Char, "��ǥ ���� : %d, ���� �ְ� ���� ���� : %d", target_Score, now_HighScore);
		TextOut(mem0dc, 630, 10, debug_Char, strlen(debug_Char));

		for (int i = 0; i < Game_Height; ++i) {
			for (int j = 0; j < Game_Width; ++j) {
				sprintf(debug_Char, "%d  ", gameData[i][j]);
				TextOut(mem0dc, 600 + (i * 40), 300 + (j * 45), debug_Char, strlen(debug_Char));
			}
		}

		for (int i = 0; i < Game_Height; ++i) {
			for (int j = 0; j < Game_Width; ++j) {
				sprintf(debug_Char, "[%d , %d]", 10 + (i * 130), 10 + (j * 130));
				TextOut(mem0dc, 600 + (i * 80), 100 + (j * 45), debug_Char, strlen(debug_Char));
			}
		}

		//-----------------------------------------------------------------------------------------------------------------------------------------------

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mem0dc, 0, 0, SRCCOPY);

		SelectObject(mem0dc, hbmMemOld); //-4
		DeleteObject(hbmMem); //-3
		DeleteObject(hbmMemOld); //-3
		DeleteDC(mem0dc); //-2
		DeleteDC(mem1dc); //-2
		DeleteDC(hdc); //-2
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void Down_PlusNum(int lineData) {
	for (int i = Game_Height - 1; i >= 0; --i) {
		if (gameData[lineData][i] == gameData[lineData][i - 1] && i - 1 >= 0) {
			if (gameData[lineData][i] + gameData[lineData][i - 1] != 0) {
				realMove = 1;
			}

			gameData[lineData][i] = gameData[lineData][i] + gameData[lineData][i - 1];
			Score = Score + gameData[lineData][i - 1];
			gameData[lineData][i - 1] = 0;
			Down_Num(lineData);
		}
	}
}

void Down_Num(int lineData) {
	for (int i = 0; i < Game_Height; ++i) {
		for (int i = Game_Height - 1; i >= 0; --i) {
			if (gameData[lineData][i] == 0 && i - 1 >= 0) {
				int temp_num = gameData[lineData][i];
				gameData[lineData][i] = gameData[lineData][i - 1];
				gameData[lineData][i - 1] = temp_num;
			}
		}
	}
}

string transArr(int(*arr)[Game_Height]) {
	string arr_savedata = "";
	int temp;
	for (int i = 0; i < Game_Height; ++i) {
		for (int j = 0; j < Game_Width; ++j) {
			char self[10];
			string data = itoa(arr[j][i], self, 10);
			data += " ";
			arr_savedata += data;
		}
		arr_savedata += "\n";
		//arr_savedata += "\n";
	}
	//cout << arr_savedata << endl;
	return arr_savedata;
}

void Up_PlusNum(int lineData) {
	for (int i = 0; i < Game_Height; ++i) {
		if (gameData[lineData][i] == gameData[lineData][i + 1] && i + 1 < 4) {
			if (gameData[lineData][i] + gameData[lineData][i + 1] != 0) {
				realMove = 1;
			}

			gameData[lineData][i] = gameData[lineData][i] + gameData[lineData][i + 1];
			Score = Score + gameData[lineData][i + 1];
			gameData[lineData][i + 1] = 0;
			Up_Num(lineData);
		}
	}
}

void Up_Num(int lineData) {
	for (int i = 0; i < Game_Height; ++i) {
		for (int i = 0; i < Game_Height; ++i) {
			if (gameData[lineData][i] == 0 && i + 1 < 4) {
				int temp_num = gameData[lineData][i];
				gameData[lineData][i] = gameData[lineData][i + 1];
				gameData[lineData][i + 1] = temp_num;
			}
		}
	}
}

void Left_PlusNum(int lineData) {
	for (int i = 0; i < Game_Height; ++i) {
		if (gameData[i][lineData] == gameData[i + 1][lineData] && i + 1 < 4) {
			if (gameData[i][lineData] + gameData[i + 1][lineData] != 0) {
				realMove = 1;
			}

			gameData[i][lineData] = gameData[i][lineData] + gameData[i + 1][lineData];
			Score = Score + gameData[i + 1][lineData];
			gameData[i + 1][lineData] = 0;
			Left_Num(lineData);
		}
	}
}

void Left_Num(int lineData) {
	for (int i = 0; i < Game_Height; ++i) {
		for (int i = 0; i < Game_Height; ++i) {
			if (gameData[i][lineData] == 0 && i + 1 < 4) {
				int temp_num = gameData[i][lineData];
				gameData[i][lineData] = gameData[i + 1][lineData];
				gameData[i + 1][lineData] = temp_num;
			}
		}
	}
}

void Right_PlusNum(int lineData) {
	for (int i = Game_Height - 1; i >= 0; --i) {
		if (gameData[i][lineData] == gameData[i - 1][lineData] && i - 1 >= 0) {
			if (gameData[i][lineData] + gameData[i - 1][lineData] != 0) {
				realMove = 1;
			}

			gameData[i][lineData] = gameData[i][lineData] + gameData[i - 1][lineData];
			Score = Score + gameData[i - 1][lineData];
			gameData[i - 1][lineData] = 0;
			Right_Num(lineData);
		}
	}
}

void Right_Num(int lineData) {
	for (int i = 0; i < Game_Height; ++i) {
		for (int i = Game_Height - 1; i >= 0; --i) {
			if (gameData[i][lineData] == 0 && i - 1 >= 0) {
				int temp_num = gameData[i][lineData];
				gameData[i][lineData] = gameData[i - 1][lineData];
				gameData[i - 1][lineData] = temp_num;
			}
		}
	}
}

void Check_4Way(int put_Key, HWND hwnd) {
	// 4 = Left, 8 = UP, 6 = Right, 2 = Down
	if (GameOver() == false && gamePause == 0) {
		CopyMapData();		// ���� ������ �����Ѵ�

		for (int i = 0; i < Game_Height; ++i) {
			if (put_Key == 6) {
				Right_Num(i);
				Right_PlusNum(i);
			}
			else if (put_Key == 4) {
				Left_Num(i);
				Left_PlusNum(i);
			}
			else if (put_Key == 8) {
				Up_Num(i);
				Up_PlusNum(i);
			}
			else if (put_Key == 2) {
				Down_Num(i);
				Down_PlusNum(i);
			}
		}

		CompareData();		// ���� ������ ���Ѵ�

		if (realMove == 1) {
			Seed_RandNum();
		}
		WinGame(hwnd);
	}
	else {
		// Game The End �ϰ�� ��
		if (gamePause == 0) {
			NewGameAnswer = MessageBox(hwnd, "Game Over..!\n\n���̻� �����ϼ� �ִ� ���ڰ� �����ϴ�.\n������ ����� �Ͻðڽ��ϱ�?", "WindowsHyun 2048", MB_OKCANCEL);
			if (NewGameAnswer == IDOK) {
				NewGame();
			}
			else {
				MessageBox(hwnd, "������ ���� �����Դϴ�.\n���ο� ������ �����Ͻ÷��� ( Game - NewGame )�� Ŭ�����ּ���.", "WindowsHyun 2048", MB_OK);
				lastScore = Score;
				Score = 0;
				gamePause = 1;
			}
		}
	}
}

bool GameOver() {
	// 4 = Left, 8 = UP, 6 = Right, 2 = Down
	int checkData = 0;

	for (int i = 0; i < Game_Height; ++i) {
		for (int j = 0; j < Game_Width; ++j) {
			if (gameData[i][j] == 0) {
				checkData++;
			}
		}
	}

	for (int i = 0; i < Game_Height; ++i) {
		for (int j = 0; j < Game_Width; ++j) {
			if (put_Key == 8 || put_Key == 2) {
				// ��, �Ʒ� �ϰ��
				if (gameData[i][j] == gameData[i][j + 1] || gameData[i][j] == gameData[i][j - 1]) {
					if (j + 1 <= 3 && j - 1 >= 0) {
						checkData++;
					}
				}
			}

			if (put_Key == 4 || put_Key == 6) {
				// ���� ������ �ϰ��
				if (gameData[i][j] == gameData[i + 1][j] || gameData[i][j] == gameData[i - 1][j]) {
					if (i + 1 <= 3 && i - 1 >= 0) {
						checkData++;
					}
				}
			}
		}
	}

	if (checkData != 0) {
		return 0;	//False ���� ���� �ȳ���
	}
	else {
		return 1;	//True ���� ���� ������
	}
}

void Draw_Map(HDC hdc, HDC memdc, HBITMAP hBit1, int X, int Y) {
	memdc = CreateCompatibleDC(hdc);
	SelectObject(memdc, hBit1);
	TransparentBlt(hdc, X, Y, 120, 120, memdc, 0, 0, 120, 120, RGB(255, 0, 0));
	DeleteDC(memdc);
}

void Seed_RandNum() {
	int dataX = 0, dataY = 0;
re_Raise:
	srand((unsigned int)time(NULL) + dataX + dataY + GetTickCount());
	dataX = rand() % Game_Width;
	dataY = rand() % Game_Height;

	if (gameData[dataX][dataY] != 0) {
		goto re_Raise;
	}
	else {
		gameData[dataX][dataY] = 2;
	}
}

void CopyMapData() {
	for (int i = 0; i < Game_Height; ++i) {
		for (int j = 0; j < Game_Width; ++j) {
			gameDataCopy[i][j] = gameData[i][j];
		}
	}
}

void CompareData() {
	for (int i = 0; i < Game_Height; ++i) {
		for (int j = 0; j < Game_Width; ++j) {
			if (gameDataCopy[i][j] != gameData[i][j]) {
				realMove = 1;
			}
		}
	}
}

void NewGame() {
	put_Key = 0;		// 4 = Left, 8 = UP, 6 = Right, 2 = Down
	gamePause = 0;
	for (int i = 0; i < Game_Height; ++i) {
		for (int j = 0; j < Game_Width; ++j) {
			gameData[i][j] = 0;
			gameDataCopy[i][j] = 0;
		}
	}
	for (int i = 0; i < 2; ++i) {
		Seed_RandNum(); //�ʱ� �� 2�� ����!
	}
	target_Score = 2048, now_HighScore = 2;
}

void WinGame(HWND hwnd) {
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	// �ش� ������ ������ ���!
	if (now_HighScore >= target_Score) {
		now_HighScore = 2;
		NewGameAnswer = MessageBox(hwnd, "�ش� ��ǥ�� �����Ͽ����ϴ�!\n������ ����� �Ͻðڽ��ϱ�?", "WindowsHyun 2048", MB_OKCANCEL);

		if (NewGameAnswer == IDOK) {
			NewGame();
		}
		else {
			MessageBox(hwnd, "������ ���� �����Դϴ�.\n���ο� ������ �����Ͻ÷��� ( Game - NewGame )�� Ŭ�����ּ���.", "WindowsHyun 2048", MB_OK);
			gamePause = 1;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------
}