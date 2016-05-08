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
#pragma comment(lib, "Msimg32.lib")										// TransparentBlt 사용하기 위해 라이브러리 호출..
#define _CRT_SECURE_NO_WARNINGS

#define Game_Width 4															// 가로
#define Game_Height 4														// 세로
#define clear_TotalData 2048													// 게임 마지막 숫자

using namespace std;
using savePair = pair<string, int>;

int clear_Total = 2048;															// 게임 마지막 숫자
int gameData[Game_Width][Game_Height];									// 게임판 설정하기
int gameDataCopy[Game_Width][Game_Height];							// 게임판 복사하기
int put_Key;																		// 4 = Left, 8 = UP, 6 = Right, 2 = Down
int realMove = 0;																// 실제로 움직였는지 확인 ( 0 = 안움직임, 1 = 움직임 )
int Score = 0;																	// 실제 점수
int gamePause = 0;																// 게임 일시정지 ( 0 = 진행, 1 = 정지 )
int lastScore = 0;																// 게임 정지후 최종 점수
int mX, mY;																		// 제스처 사용을 위한 마우스 좌표
int  click_X, click_Y, temp_X, temp_Y;											// 제처처 사용을 위한 위치 좌표
int target_Score = 2048, now_HighScore = 2;								// 목표 점수는 2048, 현재 최대 점수는 처음이니깐 2
int NewGameAnswer;															// 메시지 박스 확인취소 체크하는 부분

vector<savePair> saveData;													// 세이브 파일 저장하기 위한 vector 저장

typedef struct gameDataXY {
	int bx;
	int by;
}gameDataXY;																	// 게임 위치 저장

bool GameOver();																// False는 Game Not End, True 는 Game End

void Check_4Way(int, HWND);													// 방향 체크후 동작 & HWND추가 이유는 WinGame 에서 hwnd를 사용하기위해
void Seed_RandNum();															// 랜덤으로 숫자 뿌려주기
void CopyMapData();															// 맵 변동이 되었는지 확인하기 위한 복사
void CompareData();															// 맵 변동이 되었는지 확인하는 체크 툴
void Draw_Map(HDC, HDC, HBITMAP, int, int);								// 배열의 숫자를 맵으로 그려주는 부분
void NewGame();																// 새로운 게임을 시작할때 호출하는 함수
void WinGame(HWND);															// 목표점수에 도달했는지 확인후, 도달했을경우 메시지창 띄우기
string transArr(int(*)[Game_Height]);

// -----------------------------------------------------------------------------------------------------------
// 위, 아래, 왼쪽, 오른쪽 숫자 움직이기
void Down_PlusNum(int);	// 아래로 내리면서 같은 숫자일경우 더하기
void Down_Num(int);		// 숫자를 아래로 모두 내리기

void Up_PlusNum(int);		// 위로 올리면서 같은 숫자일경우 더하기
void Up_Num(int);			// 숫자를 위로 모두 올리기

void Left_PlusNum(int);		// 왼쪽으로 밀면서 같은 숫자일경우 더하기
void Left_Num(int);			// 숫자를 왼쪽으로 모두 밀기

void Right_PlusNum(int);	// 오른쪽으로 밀면서 같은 숫자일경우 더하기
void Right_Num(int);		// 숫자를 오른쪽으로 모두 밀기
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
	static HBITMAP image_Number[clear_TotalData];					// 2048개의 배열을 만드는 메모리 낭비중ㅋㅋㅋ
	static HBITMAP hbmOld, hbmMem, hbmMemOld;					// 더블버퍼링을 위하여!
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
			NewGameAnswer = MessageBox(hwnd, "정말로 게임을 다시 시작하실껀가요?", "WindowsHyun 2048", MB_OKCANCEL);

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
			NewGameAnswer = MessageBox(hwnd, "정말로 게임을 종료하실껀가요?", "WindowsHyun 2048", MB_OKCANCEL);

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
		//여기서 계산을 해야함

		for (int y = 0; y < Game_Height; ++y) {
			for (int x = 0; x < Game_Width; ++x) {
				if (gameDataXY[y][x].bx < mX && mX < 10 + gameDataXY[y][x].bx + 130 &&
					gameDataXY[y][x].by < mY && mY < 10 + gameDataXY[y][x].by + 130) {
					click_Y = y; click_X = x;								// X, Y 좌표를 저장해준다.
				}
			}
		}

		/*if (temp_X > click_X) {
			//왼쪽
			put_Key = 4, realMove = 0;
			Check_4Way(put_Key, hwnd);
		}
		else if (temp_X < click_X) {
			//오른쪽
			put_Key = 6, realMove = 0;
			Check_4Way(put_Key, hwnd);
		}
		else if (temp_Y > click_Y) {
			//위
			put_Key = 8, realMove = 0;
			Check_4Way(put_Key, hwnd);
		}
		else if (temp_Y < click_Y) {
			//아래
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
					click_Y = y; click_X = x;								// X, Y 좌표를 저장해준다.
				}
				else if (mX < 10 || mY > 520 || mX > 520) {
					// 판 범위를 벗어나면 둘다 0으로
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
					click_Y = y; click_X = x;								// X, Y 좌표를 저장해준다.
					temp_X = x, temp_Y = y;							// 마우스가 움직이면 자동으로 X,Y 좌표도 바뀐다 그러므로 임시 위치로 저장
				}
			}
		}

		InvalidateRgn(hwnd, NULL, FALSE);
		break;

	case WM_CREATE:
		srand((unsigned int)time(NULL) + GetTickCount());

		GetClientRect(hwnd, &rt);

		image_Number[0] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));					// 숫자 없음
		image_Number[2] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP2));					// 숫자 2
		image_Number[4] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP3));					// 숫자 4
		image_Number[8] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP4));					// 숫자 8
		image_Number[16] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP5));					// 숫자 16
		image_Number[32] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP6));					// 숫자 32
		image_Number[64] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP7));					// 숫자 64
		image_Number[128] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP8));				// 숫자 128
		image_Number[256] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP9));				// 숫자 256
		image_Number[512] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP10));				// 숫자 512
		image_Number[1024] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP11));			// 숫자 1024
		image_Number[2048] = (HBITMAP)LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP12));			// 숫자 2048

		put_Key = 0;		// 4 = Left, 8 = UP, 6 = Right, 2 = Down

		for (int i = 0; i < 2; ++i) {
			Seed_RandNum(); //초기 블럭 2개 설정!
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
		// 최고 점수를 찾아라!
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
		// 게임 데이터를 텍스트로 변환
		sprintf(debug_Char, "WhatKey : %d, realMove : %d, Score = %d, lastScore = %d, mX = %d, mY = %d, 현재 위치 좌표 = (%d, %d), 이전 위치 좌표 = (%d, %d)",
			put_Key, realMove, Score, lastScore, mX, mY, click_X, click_Y, temp_X, temp_Y);
		TextOut(mem0dc, 0, 530, debug_Char, strlen(debug_Char));

		sprintf(debug_Char, "목표 점수 : %d, 현재 최고 높은 숫자 : %d", target_Score, now_HighScore);
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
		CopyMapData();		// 게임 데이터 복사한다

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

		CompareData();		// 게임 데이터 비교한다

		if (realMove == 1) {
			Seed_RandNum();
		}
		WinGame(hwnd);
	}
	else {
		// Game The End 일경우 ↓
		if (gamePause == 0) {
			NewGameAnswer = MessageBox(hwnd, "Game Over..!\n\n더이상 움직일수 있는 숫자가 없습니다.\n게임을 재시작 하시겠습니까?", "WindowsHyun 2048", MB_OKCANCEL);
			if (NewGameAnswer == IDOK) {
				NewGame();
			}
			else {
				MessageBox(hwnd, "게임이 정지 상태입니다.\n새로운 게임을 시작하시려면 ( Game - NewGame )을 클릭해주세요.", "WindowsHyun 2048", MB_OK);
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
				// 위, 아래 일경우
				if (gameData[i][j] == gameData[i][j + 1] || gameData[i][j] == gameData[i][j - 1]) {
					if (j + 1 <= 3 && j - 1 >= 0) {
						checkData++;
					}
				}
			}

			if (put_Key == 4 || put_Key == 6) {
				// 왼쪽 오른쪽 일경우
				if (gameData[i][j] == gameData[i + 1][j] || gameData[i][j] == gameData[i - 1][j]) {
					if (i + 1 <= 3 && i - 1 >= 0) {
						checkData++;
					}
				}
			}
		}
	}

	if (checkData != 0) {
		return 0;	//False 게임 아직 안끝남
	}
	else {
		return 1;	//True 게임 아직 진행중
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
		Seed_RandNum(); //초기 블럭 2개 설정!
	}
	target_Score = 2048, now_HighScore = 2;
}

void WinGame(HWND hwnd) {
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	// 해당 점수에 도달할 경우!
	if (now_HighScore >= target_Score) {
		now_HighScore = 2;
		NewGameAnswer = MessageBox(hwnd, "해당 목표에 도달하였습니다!\n게임을 재시작 하시겠습니까?", "WindowsHyun 2048", MB_OKCANCEL);

		if (NewGameAnswer == IDOK) {
			NewGame();
		}
		else {
			MessageBox(hwnd, "게임이 정지 상태입니다.\n새로운 게임을 시작하시려면 ( Game - NewGame )을 클릭해주세요.", "WindowsHyun 2048", MB_OK);
			gamePause = 1;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------
}