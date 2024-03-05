#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <string>
#include <WinUser.h>



#define MAX_LOADSTRING 100
#define TMR_1 1
#define DISTANCE_BETWEEN_FLOORS 120
#define G 10
#define ELEVATOR_WEIGHT 1000

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR textHeight[MAX_LOADSTRING];

INT value;
//people
struct people {
	int x;
	int y = 585;
	int number;
}person0, person1, person2, person3, person4,person;
// buttons
HWND hwndButton;

// sent data
int col = 0;
int height = 0;
int movement = 0;
int door_movement = 0;
int floor_diff = 1;
int button = 0;
int flooor = 0;
int person_movement = 0;
int jump = 0;
bool empty = 0;
int weight = 0;
int force = 0;
std::vector<Point> data;
RECT drawArea1 = { 0, 0, 150, 200 };
RECT drawArea2 = { 50, 400, 650, 422 };
RECT drawArea4 = { 632, 60, 860, 650 };
RECT drawArea3 = { 610, 60, 881, 720 };
RECT textArea1 = { 960, 50, 1050, 80 };
RECT textArea2 = { 975, 80, 1005, 100 };
RECT textArea3 = { 1040, 50, 1120, 100 };
RECT textArea4 = { 1040, 90, 1120, 120 };
RECT personArea4 = { 80, 0, 610, 189 };
RECT personArea2 = { 80, 191, 610, 429 };
RECT personArea0 = { 80, 560, 610, 669 };
RECT personArea3 = { 890, 191, 1450, 309 };
RECT personArea1 = { 890, 311, 1450, 549 };
RECT textArea5 = { 1150, 50, 1210, 100 };
RECT textArea6 = { 1150, 90, 1210, 120 };

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);
void check_floor();
void check_weight();
void floor_zero(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, int exit);
void text(HDC hdc) {
	Graphics graphics(hdc);
	Pen pen(Color(0, 0, 0));
	LPCWSTR a = L"Floor:";
	LPCWSTR b = L"Weight: \n (max 600kg) ";
	LPCWSTR c = L"Force \n ";
	DrawText(hdc, a, 8, &textArea1, DT_TOP);
	DrawText(hdc, b, 22, &textArea3, DT_TOP|DT_CENTER);
	DrawText(hdc, c, 12, &textArea5, DT_TOP|DT_CENTER);
	wchar_t buffer1[2];
	wchar_t buffer2[4];
	wchar_t buffer3[8];
	weight = int(empty) * 70;
	force = G * (weight + ELEVATOR_WEIGHT);
	wsprintfW(buffer1, L"%i", height);
	wsprintfW(buffer2, L"%i", weight);
	wsprintfW(buffer3, L"%i", force);
	DrawText(hdc, buffer1, 1, &textArea2, DT_BOTTOM | DT_INTERNAL);
	DrawText(hdc, buffer2, 2, &textArea4, DT_BOTTOM | DT_INTERNAL|DT_CENTER);
	DrawText(hdc, buffer3, 6, &textArea6, DT_BOTTOM | DT_INTERNAL|DT_CENTER);
}
void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen3(Color(0, 0, 0));
	Pen pen2(Color(255, 25 * col, 0, 255));
	Pen pen4(Color(255, 255, 255));
	text(hdc);
	graphics.DrawRectangle(&pen3, 610, 50, 270, 670);
	graphics.DrawRectangle(&pen, 630, 550 - movement, 230, 120);
	if (height % 2 == 0) {
		graphics.DrawRectangle(&pen4, 610, 555 - DISTANCE_BETWEEN_FLOORS * height, 20, 0 + door_movement);
	}
	else
		graphics.DrawRectangle(&pen4, 860, 555 - DISTANCE_BETWEEN_FLOORS * height, 20, 0 + door_movement);
}
void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}
void input_person0(HDC hdc) {
	Graphics graphics(hdc);
	Image image(L"person0.jpg");
	Pen pen(Color(255, 0, 0, 255));
	if (flooor % 2 == 0) {
		person0.x = 400;
	}
	else person0.x = 1000;
	graphics.DrawImage(&image, person0.x +person_movement, person0.y - movement+jump);
	graphics.DrawRectangle(&pen, 630, 550 - movement, 230, 120);
	person.number = 0;
}
void input_person1(HDC &hdc) {
	Graphics graphics(hdc);
	Image image(L"person1.jpg");
	Pen pen(Color(255, 0, 0, 255));
	if (flooor % 2 == 0) {
		person1.x = 400;
	}
	else person1.x = 1000;
	graphics.DrawImage(&image, person1.x + person_movement , person1.y - movement + jump);
	graphics.DrawRectangle(&pen, 630, 550 - movement, 230, 120);
	person.number = 1;
}
void input_person2(HDC &hdc) {
	Graphics graphics(hdc);
	Image image(L"person2.jpg");
	Pen pen(Color(255, 0, 0, 255));
	if (flooor % 2 == 0) {
		person2.x = 400;
	}
	else person2.x = 1000;
	graphics.DrawImage(&image, person2.x + person_movement , person2.y - movement + jump);
	graphics.DrawRectangle(&pen, 630, 550 - movement, 230, 120);
	person.number = 2;
}
void input_person3(HDC &hdc) {
	Graphics graphics(hdc);
	Image image(L"person3.jpg");
	Pen pen(Color(255, 0, 0, 255));
	if (flooor % 2 == 0) {
		person3.x = 400;
	}
	else person3.x = 950;
	graphics.DrawImage(&image, person3.x + person_movement , person3.y - movement + jump);
	graphics.DrawRectangle(&pen, 630, 550 - movement, 230, 120);
	person.number = 3;
}
void input_person4(HDC &hdc) {
	Graphics graphics(hdc);
	Image image(L"person4.jpg");
	Pen pen(Color(255, 0, 0, 255));
	if (flooor % 2 == 0) {
		person4.x = 400;
	}
	else person4.x = 1000;
	graphics.DrawImage(&image, person4.x + person_movement ,person4.y - movement + jump);
	graphics.DrawRectangle(&pen, 630, 550 - movement, 230, 120);
	person.number = 4;
}
void repaintPerson0(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	input_person0(hdc);
	EndPaint(hWnd, &ps);
}
void repaintPerson1(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	input_person1(hdc);
	EndPaint(hWnd, &ps);
}
void repaintPerson2(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	input_person2(hdc);
	EndPaint(hWnd, &ps);
}
void repaintPerson3(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	input_person3(hdc);
	EndPaint(hWnd, &ps);
}
void repaintPerson4(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	input_person4(hdc);
	EndPaint(hWnd, &ps);
}
void ground(HDC hdc) {
	Graphics graphics(hdc);
	Pen pen(Color(0, 0, 0));
	graphics.DrawLine(&pen, 80, 190, 610, 190);
	graphics.DrawLine(&pen, 80, 430, 610, 430);
	graphics.DrawLine(&pen, 80, 670, 610, 670);
	graphics.DrawLine(&pen, 880, 310, 1450, 310);
	graphics.DrawLine(&pen, 880, 550, 1450, 550);
	graphics.DrawRectangle(&pen, 610, 50, 270, 670);
	graphics.DrawRectangle(&pen, 926, 40, 100, 80);
	graphics.DrawRectangle(&pen, 1026, 40, 100, 80);
	graphics.DrawRectangle(&pen, 1127, 40, 100, 80);
}
void doors(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps) {
	Graphics graphics(hdc);
	int buf = 0;
	Pen pen(Color(255, 255, 255));
	for (int i = 0; i < 116; i++) {
		door_movement++;
		if (i % 5 == 0) {
			repaintWindow(hWnd, hdc, ps, &drawArea3);
			if (person.number == 0) {
				repaintPerson0(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 1) {
				repaintPerson1(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 2) {
				repaintPerson2(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 3) {
				repaintPerson3(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 4) {
				repaintPerson4(hWnd, hdc, ps, &drawArea4);
			}
			Sleep(100);
		}
	}
	if (height % 2 == 0) {
		for (int i = 0; i < 250; i++) {
			if (empty == 0)
				person_movement++;
			else
				person_movement--;
			if (person_movement % 2 == 0) {
				jump += 2;;
			}
			else jump -= 2;;
			if (i % 5 == 0) {
				if (person.number == 0) {
					repaintPerson0(hWnd, hdc, ps, &personArea0);
					repaintPerson0(hWnd, hdc, ps, &personArea2);
					repaintPerson0(hWnd, hdc, ps, &personArea4);
					repaintPerson0(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 1) {
					repaintPerson1(hWnd, hdc, ps, &personArea0);
					repaintPerson1(hWnd, hdc, ps, &personArea2);
					repaintPerson1(hWnd, hdc, ps, &personArea4);
					repaintPerson1(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 2) {
					repaintPerson2(hWnd, hdc, ps, &personArea0);
					repaintPerson2(hWnd, hdc, ps, &personArea2);
					repaintPerson2(hWnd, hdc, ps, &personArea4);
					repaintPerson2(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 3) {
					repaintPerson3(hWnd, hdc, ps, &personArea0);
					repaintPerson3(hWnd, hdc, ps, &personArea2);
					repaintPerson3(hWnd, hdc, ps, &personArea4);
					repaintPerson3(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 4) {
					repaintPerson4(hWnd, hdc, ps, &personArea0);
					repaintPerson4(hWnd, hdc, ps, &personArea2);
					repaintPerson4(hWnd, hdc, ps, &personArea4);
					repaintPerson4(hWnd, hdc, ps, &drawArea4);
				}
				Sleep(100);
			}
		}
		empty = 1;
	}
	else {
		for (int i = 0; i < 250; i++) {
			if (empty == 0)
				person_movement--;
			else
				person_movement++;
			if (person_movement % 2 == 0) {
				jump += 2;;
			}
			else jump -= 2;;
			if (i % 5 == 0) {
				if (person.number == 0) {
					repaintPerson0(hWnd, hdc, ps, &personArea1);
					repaintPerson0(hWnd, hdc, ps, &personArea3);
					repaintPerson0(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 1) {
					repaintPerson1(hWnd, hdc, ps, &personArea1);
					repaintPerson1(hWnd, hdc, ps, &personArea3);
					repaintPerson1(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 2) {
					repaintPerson2(hWnd, hdc, ps, &personArea1);
					repaintPerson2(hWnd, hdc, ps, &personArea3);
					repaintPerson2(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 3) {
					repaintPerson3(hWnd, hdc, ps, &personArea1);
					repaintPerson3(hWnd, hdc, ps, &personArea3);
					repaintPerson3(hWnd, hdc, ps, &drawArea4);
				}
				else if (person.number == 4) {
					repaintPerson4(hWnd, hdc, ps, &personArea1);
					repaintPerson4(hWnd, hdc, ps, &personArea3);
					repaintPerson4(hWnd, hdc, ps, &drawArea4);
				}
				Sleep(100);
			}
		}
		empty = 1;
	}
	for (int i = 0; i < 116; i++) {
		door_movement--;
		if (i % 5 == 0) {
			repaintWindow(hWnd, hdc, ps, &drawArea3);
			if (person.number == 0) {
				repaintPerson0(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 1) {
				repaintPerson1(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 2) {
				repaintPerson2(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 3) {
				repaintPerson3(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 4) {
				repaintPerson4(hWnd, hdc, ps, &drawArea4);
			}
			Sleep(100);
		}
	}
	repaintWindow(hWnd, hdc, ps, &drawArea3);
	repaintWindow(hWnd, hdc, ps, &personArea0);
	repaintWindow(hWnd, hdc, ps, &personArea1);
	repaintWindow(hWnd, hdc, ps, &personArea2);
	repaintWindow(hWnd, hdc, ps, &personArea3);
	repaintWindow(hWnd, hdc, ps, &personArea4);
}
TIMERPROC CALLBACK Timerproc(HWND hWnd, UINT message, WPARAM wParam, DWORD dwTime) {
	HDC hdc;
	PAINTSTRUCT ps;
	if (height != 0) {
		floor_zero(hWnd, hdc, ps, 2 * height);
	}
	return 0;
}
void one_floor_down(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, int exit) {
	floor_diff = abs((exit - height) * DISTANCE_BETWEEN_FLOORS);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
	for (int i = 1; i <=floor_diff; i+=2) {
		movement-=2;
		if (i % 5 == 0) {
			repaintWindow(hWnd, hdc, ps, &textArea6);
			repaintWindow(hWnd, hdc, ps, &drawArea3);
			if (person.number == 0) {
				repaintPerson0(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 1) {
				repaintPerson1(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 2) {
				repaintPerson2(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 3) {
				repaintPerson3(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 4) {
				repaintPerson4(hWnd, hdc, ps, &drawArea4);
			}
			Sleep(100);
		}
		check_floor();
		check_weight();
	}
	repaintWindow(hWnd, hdc, ps, &drawArea3);
	repaintWindow(hWnd, hdc, ps, &textArea2);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
	if (person.number == 0) {
		repaintPerson0(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 1) {
		repaintPerson1(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 2) {
		repaintPerson2(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 3) {
		repaintPerson3(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 4) {
		repaintPerson4(hWnd, hdc, ps, &drawArea4);
	}
	Sleep(1000);
	doors(hWnd, hdc, ps);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
}
void floor_zero(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, int exit) {
	floor_diff = abs((exit - height) * DISTANCE_BETWEEN_FLOORS);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
	for (int i = 1; i <= floor_diff; i += 2) {
		movement -= 2;
		if (i % 5 == 0) {
			repaintWindow(hWnd, hdc, ps, &textArea6);
			repaintWindow(hWnd, hdc, ps, &drawArea3);
			if (person.number == 0) {
				repaintPerson0(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 1) {
				repaintPerson1(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 2) {
				repaintPerson2(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 3) {
				repaintPerson3(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 4) {
				repaintPerson4(hWnd, hdc, ps, &drawArea4);
			}
			Sleep(100);
		}
		check_floor();
		check_weight();
	}
	repaintWindow(hWnd, hdc, ps, &drawArea3);
	repaintWindow(hWnd, hdc, ps, &textArea2);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
	if (person.number == 0) {
		repaintPerson0(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 1) {
		repaintPerson1(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 2) {
		repaintPerson2(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 3) {
		repaintPerson3(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 4) {
		repaintPerson4(hWnd, hdc, ps, &drawArea4);
	}
	Sleep(1000);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
}
void one_floor_up(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, int exit) {
	floor_diff = abs((exit - height) * DISTANCE_BETWEEN_FLOORS);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
	for (int i = 1; i <= floor_diff; i+=2) {
		movement+=2;
		repaintWindow(hWnd, hdc, ps, &textArea6);
		if (i % 5 == 0) {
			repaintWindow(hWnd, hdc, ps, &drawArea3);
			if (person.number == 0) {
				repaintPerson0(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 1) {
				repaintPerson1(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 2) {
				repaintPerson2(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 3) {
				repaintPerson3(hWnd, hdc, ps, &drawArea4);
			}if (person.number == 4) {
				repaintPerson4(hWnd, hdc, ps, &drawArea4);
			}
			Sleep(100);
		}
		check_floor();
		check_weight();
	}
	repaintWindow(hWnd, hdc, ps, &drawArea4);
	repaintWindow(hWnd, hdc, ps, &drawArea3);
	repaintWindow(hWnd, hdc, ps, &textArea2);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
	if (person.number == 0) {
		repaintPerson0(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 1) {
		repaintPerson1(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 2) {
		repaintPerson2(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 3) {
		repaintPerson3(hWnd, hdc, ps, &drawArea4);
	}if (person.number == 4) {
		repaintPerson4(hWnd, hdc, ps, &drawArea4);
	}
	Sleep(1000);
	doors(hWnd, hdc, ps);
	repaintWindow(hWnd, hdc, ps, &textArea4);
	repaintWindow(hWnd, hdc, ps, &textArea6);
	
}

// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassEx(&wcex);
}
void check_floor() {
	if (movement >= 0 && movement < DISTANCE_BETWEEN_FLOORS)
		height = 0;
	if (movement >= DISTANCE_BETWEEN_FLOORS && movement < 2* DISTANCE_BETWEEN_FLOORS)
		height = 1;
	if (movement >= 2* DISTANCE_BETWEEN_FLOORS && movement < 3* DISTANCE_BETWEEN_FLOORS)
		height = 2;
	if (movement >= 3* DISTANCE_BETWEEN_FLOORS && movement < 4* DISTANCE_BETWEEN_FLOORS)
		height = 3;
	if (movement >= 4* DISTANCE_BETWEEN_FLOORS)
		height = 4;
}
void check_weight() {
	weight = int(empty)*70;
}
void moving(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, int flooor, int button) {
	if (height == flooor) 
		doors(hWnd, hdc, ps);
	if (flooor > height)
		one_floor_up(hWnd, hdc, ps, flooor);
	else if (flooor < height)
		one_floor_down(hWnd, hdc, ps, flooor);
	if (button > height)
		one_floor_up(hWnd, hdc, ps, button);
	else if (button < height)
		one_floor_down(hWnd, hdc, ps, button);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("0"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 130, 30, 30, hWnd, (HMENU)ID_BUTTON40, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 100, 30, 30, hWnd, (HMENU)ID_BUTTON41, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 70, 30, 30, hWnd, (HMENU)ID_BUTTON42, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 40, 30, 30, hWnd, (HMENU)ID_BUTTON43, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("0"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 252, 30, 30, hWnd, (HMENU)ID_BUTTON30, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 222, 30, 30, hWnd, (HMENU)ID_BUTTON31, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 192, 30, 30, hWnd, (HMENU)ID_BUTTON32, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 162, 30, 30, hWnd, (HMENU)ID_BUTTON34, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("0"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 375, 30, 30, hWnd, (HMENU)ID_BUTTON20, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 345, 30, 30, hWnd, (HMENU)ID_BUTTON21, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 315, 30, 30, hWnd, (HMENU)ID_BUTTON23, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 285, 30, 30, hWnd, (HMENU)ID_BUTTON24, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("0"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 497, 30, 30, hWnd, (HMENU)ID_BUTTON10, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 467, 30, 30, hWnd, (HMENU)ID_BUTTON12, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 437, 30, 30, hWnd, (HMENU)ID_BUTTON13, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		1460, 407, 30, 30, hWnd, (HMENU)ID_BUTTON14, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 620, 30, 30, hWnd, (HMENU)ID_BUTTON01, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 590, 30, 30, hWnd, (HMENU)ID_BUTTON02, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 560, 30, 30, hWnd, (HMENU)ID_BUTTON03, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		40, 530, 30, 30, hWnd, (HMENU)ID_BUTTON04, GetModuleHandle(NULL), NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);

	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON01:
			button = 1;
			flooor = 0;
			/*repaintPerson1(hWnd, hdc, ps, &personArea0);*/
			moving(hWnd, hdc, ps, flooor, button);
			input_person0(hdc);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON02:
			button = 2;
			flooor = 0;
			repaintPerson2(hWnd, hdc, ps, &personArea0);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON03:
			button = 3;
			flooor = 0;
			repaintPerson3(hWnd, hdc, ps, &personArea0);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON04:
			button = 4;
			flooor = 0;
			repaintPerson4(hWnd, hdc, ps, &personArea0);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON10:
			button = 0;
			flooor = 1;
			repaintPerson0(hWnd, hdc, ps, &personArea1);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			break;
		case ID_BUTTON12:
			button = 2;
			flooor = 1;
			repaintPerson2(hWnd, hdc, ps, &personArea1);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON13:
			button = 3;
			flooor = 1;
			repaintPerson3(hWnd, hdc, ps, &personArea1);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON14:
			button = 4;
			flooor = 1;
			repaintPerson4(hWnd, hdc, ps, &personArea1);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON20:
			button = 0;
			flooor = 2;
			repaintPerson0(hWnd, hdc, ps, &personArea2);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			break;
		case ID_BUTTON21:
			button = 1;
			flooor = 2;
			repaintPerson1(hWnd, hdc, ps, &personArea2);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON23:
			button = 3;
			flooor = 2;
			repaintPerson3(hWnd, hdc, ps, &personArea2);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON24:
			button = 4;
			flooor = 2;
			repaintPerson4(hWnd, hdc, ps, &personArea2);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON30:
			button = 0;
			flooor = 3;
			repaintPerson0(hWnd, hdc, ps, &personArea3);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			break;
		case ID_BUTTON31:
			button = 1;
			flooor = 3;
			repaintPerson1(hWnd, hdc, ps, &personArea3);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON32:
			button = 2;
			flooor = 3;
			repaintPerson2(hWnd, hdc, ps, &personArea3);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON34:
			button = 4;
			flooor = 3;
			repaintPerson4(hWnd, hdc, ps, &personArea3);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON40:
			button = 0;
			flooor = 4; 
			repaintPerson0(hWnd, hdc, ps, &personArea4);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			break;
		case ID_BUTTON41:
			button = 1;
			flooor = 4;
			repaintPerson1(hWnd, hdc, ps, &personArea4);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON42:
			button = 2;
			flooor = 4;
			repaintPerson2(hWnd, hdc, ps, &personArea4);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		case ID_BUTTON43:
			button = 3;
			flooor = 4;
			repaintPerson3(hWnd, hdc, ps, &personArea4);
			moving(hWnd, hdc, ps, flooor, button);
			person_movement = 0;
			empty = 0;
			repaintWindow(hWnd, hdc, ps, &textArea4);
			repaintWindow(hWnd, hdc, ps, &textArea6);
			SetTimer(hWnd, TMR_1, 5000, (TIMERPROC)Timerproc);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		ground(hdc);
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			if (message) {
				KillTimer(hWnd, TMR_1);
			}
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
