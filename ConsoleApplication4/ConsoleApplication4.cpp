#include "stdafx.h"
#include "WindowsProject1.h"
#include <iostream>
#include<Windowsx.h> 
#include<vector>
#include<Windows.h>
#include<fstream>
#include<string>
#include<ctime>
#include <cstdio>
#include"MyDll.h"
#include"FreeImage.h"
#define MAX_LOADSTRING 100
using namespace std;
// Глобальные переменные:
HBRUSH oldb = NULL;
int N= 12;
int w= 600;
int hei= 600;
int r1[3] = {0,0,0};
int r2[3] = {230,0,0};
int k;
int va;
int height, width;
bool x = false;
bool x1 = false;
int c1 = 0, c2 = 100, c3 = 0;
char* ch1;
char* ch2;
string s1 = "C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\info.ini";
string s2 = "C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\info1.ini";
TCHAR ts1[] = L"C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\info.ini";
TCHAR ts2[]= L"C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\info1.ini";
HINSTANCE hInst;     // текущий экземпляр
vector<int> le;
vector<int> to;
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

												// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int, HWND);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int Func(int &i,char *c,int size)
{
	string s;
	while (c[i]>='0'&&c[i]<='9'&&i<size)
	{
		s = s + c[i];
		i++;
	}
	while (!(c[i] >= '0'&&c[i] <= '9')&&i<size)
	{
		i++;
	}
	int num = atoi(s.c_str());
	return num;
}
void F1()
{
	FILE *f;
	errno_t err;
	err=fopen_s(&f,"C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\info.txt" , "r");
	if (err!=0) cout << "Не открылся файл";
	else {
		fscanf_s(f,"%d",&N);
		fscanf_s(f, "%d", &w);
		fscanf_s(f, "%d", &hei);
		for(int i=0;i<3;i++) fscanf_s(f, "%d", &r1[i]);
		for (int i = 0; i<3; i++) fscanf_s(f, "%d", &r2[i]);
	}
};
void F2()
{
	DWORD fz;
	HANDLE File = CreateFile(ts1, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == File) cout << "Не открылся файл";
	else
	{
		int size = GetFileSize(File, &fz);
		HANDLE map = CreateFileMapping(File, nullptr, PAGE_READONLY, 0, 0, nullptr);
		char *ch = (char*)MapViewOfFile(map, FILE_MAP_READ, 0, 0, size);
		int i = 0;
		N = Func(i, ch, size);
		w = Func(i, ch, size);
		hei = Func(i, ch, size);
		for (int j = 0; j < 3; j++) {
			r1[j] = Func(i, ch, size);
		}
		for (int j = 0; j < 3; j++) {
			r2[j] = Func(i, ch, size);
		}
		UnmapViewOfFile(ch);
		CloseHandle(map);
	}
	CloseHandle(File);
};
void F3()
{
	ifstream f(s1);
	if(!f)  cout << "Не открылся файл";
	else
	{
		f >> N;
		f >> w >> hei;
		f >> r1[0] >> r1[1] >> r1[2];
		f >> r2[0] >> r2[1] >> r2[2];
	}
	f.close();
};
void F4()
{
	DWORD fz,ou;
	HANDLE File=CreateFile(ts1, GENERIC_READ, 0, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == File) cout << "Не открылся файл";
	else
	{
		int kol = GetFileSize(File, &fz);
		char *c = new char[kol];
		ReadFile(File, c, kol, &ou, NULL);
		int i = 0;
		N = Func(i, c, kol);
		w = Func(i, c, kol);
		hei = Func(i, c, kol);
		for (int j = 0; j < 3; j++) r1[j] = Func(i, c, kol);
		for (int j = 0; j < 3; j++) r2[j] = Func(i, c, kol);
		delete[] c;
	}
	CloseHandle(File);
};
void F1z()
{
	FILE *f;
	errno_t err;
	err = fopen_s(&f, "C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\info1.txt", "w");
	if (err != 0) cout << "Не открылся файл";
	else
	{
		fprintf_s(f, "%d%c", N,' ');
		fprintf_s(f, "%d%c", w, ' ');
		fprintf_s(f, "%d%c", hei, ' ');
		for (int j = 0; j < 3; j++) fprintf_s(f, "%d%c", r1[j], ' ');
		for (int j = 0; j < 3; j++) fprintf_s(f, "%d%c", r2[j], ' ');
	}
};
void F2z()
{
	DWORD fz;
	HANDLE File = CreateFile(ts2, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == File) cout << "Не открылся файл";
	else
	{
		HANDLE map = CreateFileMapping(File, nullptr, PAGE_READWRITE, 0, 512, nullptr);
		char *ch = (char*)MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, 512);
		string s = to_string(N) + " " + to_string(w) + " " + to_string(hei) + " ";
		for (int i = 0; i < 3; i++) s = s + to_string(r1[i]) + " ";
		for (int i = 0; i < 3; i++) s = s + to_string(r2[i]) + " ";
		int l = s.length();
		for (int i = 0; i < l; i++) ch[i] = s[i];
		UnmapViewOfFile(ch);
		CloseHandle(map);
	}
	CloseHandle(File);
};
void F3z()
{
	ofstream f;
	f.open(s2, ios::out);
	if(!f) cout << "Не открылся файл";
	else {
		f << N << " ";
		f << w << " " << hei << " ";
		f << r1[0] << " " << r1[1] << " " << r1[2] << " ";
		f << r2[0] << " " << r2[1] << " " << r2[2] << " ";
	}
};
void F4z2(HANDLE File,int a)
{
	DWORD ou;
	string s = to_string(a);
	int n = s.length();
	for (int j = 0; j < n; j++)
		WriteFile(File, &s[j], 1, &ou, NULL);
	char c = ' ';
	WriteFile(File, &c, 1, &ou, NULL);
}
void F4z()
{
	HANDLE File = CreateFile(ts2,GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == File) cout << "Не открылся файл";
	else
	{
		F4z2(File, N);
		F4z2(File, w);
		F4z2(File, hei);
		for (int j = 0; j < 3; j++) F4z2(File, r1[j]);
		for (int j = 0; j < 3; j++) F4z2(File, r2[j]);
	}
	CloseHandle(File);
};

int main(int argc, char* argv[])
{	
	if (argc > 1)
	{
		int var = atoi(argv[1]);
		if (var > 0 && var < 5)
		{
			va = var;
			if (var == 1)
			{
				F1();
			}
			else if (var == 2)
			{
				F2();
			}
			else if (var == 3)
			{
				F3();
			}
			if (var == 4)
			{
				F4();
			}
			srand(time(0));
			// TODO: разместите код здесь.
			HINSTANCE hInstance = GetModuleHandle(NULL);
			// Инициализация глобальных строк
			LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
			LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
			MyRegisterClass(hInstance);
			HWND hwnd = NULL;
			// Выполнить инициализацию приложения:
			if (!InitInstance(hInstance, SW_SHOW, hwnd))
			{
				return FALSE;
			}
			HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
			MSG msg;
			//New
			HMODULE hund;
			char* (*load_image) (const char* filename, int& width, int& height);
			hund = LoadLibrary(L"myDLL.dll");
			if (!hund) cout << "error";
			load_image = (char* (*)(const char* filename, int& width, int& height)) GetProcAddress(hund, "load_image");
			if (!load_image) cout << "error";
			ch1 = load_image("C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\png1.png", width, height);
			ch2 = load_image("C:\\Users\\vladi\\Desktop\\ConsoleApplication4\\ConsoleApplication4\\1jp.jpg", width, height);
			if(ch1!=NULL) cout <<1;			
			if (ch2 != NULL) cout << 1;
			cout << width;
			//
			// Цикл основного сообщения:
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			UnregisterClass(szWindowClass, hInstance);
			if (va == 1)
			{
				F1z();
			}
			else if (va == 2)
			{
				F2z();
			}
			else if (va == 3)
			{
				F3z();
			}
			if (va == 4)
			{
				F4z();
			}
			DeleteObject(oldb);
			FreeLibrary(hund);
		}
	}
	else cout << "Wrong input";
	return 0;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	HBRUSH b= CreateSolidBrush(RGB(r1[0],r1[1],r1[2]));
	wcex.hbrBackground = b;
	oldb = b;
	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND h)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, w, hei, HWND_DESKTOP, nullptr, hInstance, nullptr);
	h = hWnd;
	if (hWnd==NULL)
	{
		return FALSE;
	}
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	w = rect.right - rect.left;
	hei = rect.bottom - rect.top;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		int k1 = (rect.right - rect.left) / N;
		if (!x) {
			k = k1;
			x = true;
		}
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(r2[0], r2[1], r2[2]));
		SelectObject(hdc, pen);
		for (int i = 0; i < rect.right; i += k)
		{
			MoveToEx(hdc, i, 0, NULL);
			LineTo(hdc, i, rect.bottom);
		}
		for (int i = 0; i < rect.bottom; i += k)
		{
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, rect.right, i);
		}
		DeleteObject(pen);
		pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		SelectObject(hdc, pen);
		HBRUSH b = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, b);
		vector<int>::iterator p, p2;
		HBITMAP bitmap1 = CreateBitmap(width, height, 1, 32, ch1);
		HBITMAP bitmap2 = CreateBitmap(width, height, 1, 32, ch2);
		for (p = le.begin(), p2 = to.begin(); p != le.end(); p++, p2++)
		{
			HDC hdc2 = CreateCompatibleDC(hdc);
			int l = (*p / k)*k;
			int t = (*p2 / k)*k;
			//Ellipse(hdc, l, t, l + k, t + k);
			int var = rand() % 2;
			if (var == 0) SelectObject(hdc2, bitmap1);
			else SelectObject(hdc2, bitmap2);
			BitBlt(hdc, l, t, width, height, hdc2, 0, 0, SRCCOPY);
			DeleteDC(hdc2);
		}
		EndPaint(hWnd, &ps);
		DeleteObject(pen);
		DeleteObject(b);
		DeleteObject(bitmap1);
		DeleteObject(bitmap2);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	{
		int wmId = LOWORD(wParam);
		if ((wmId == 17 && GetKeyState(81)) || (GetKeyState(17) && wmId == 81))
		{
			PostQuitMessage(WM_QUIT);
		}
		else if ((wmId == 16 && GetKeyState(67)) || (GetKeyState(16) && wmId == 67))
		{
			STARTUPINFO in;
			ZeroMemory(&in, sizeof(in));
			in.cb = sizeof(STARTUPINFO);
			PROCESS_INFORMATION in2;
			CreateProcess(_T("C:\\WINDOWS\\system32\\notepad.exe"), L"", NULL, NULL, FALSE, 0, NULL, NULL, &in, &in2);

		}
	}
	break;
	case WM_KEYUP:
	{
		int wmId = LOWORD(wParam);
		if (wmId == 13 && x1)
		{
			r1[0] = rand() % 256;
			r1[1] = rand() % 256;
			r1[2] = rand() % 256;
			HBRUSH b = CreateSolidBrush(RGB(r1[0], r1[1], r1[2]));
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)b);
			DeleteObject(oldb);
			oldb = b;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (wmId == 27)
		{
			PostQuitMessage(WM_QUIT);
		}
		else if ((wmId == 17 && GetKeyState(81)) || (GetKeyState(17) && wmId == 81))
		{
			PostQuitMessage(WM_QUIT);
		}
		else if (wmId == 13 && !x1) x1 = true;
	}
	break;
	case WM_LBUTTONUP:
	{
		HDC hdc = GetDC(hWnd);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		int m1 = GET_X_LPARAM(lParam);
		int m2 = GET_Y_LPARAM(lParam);
		//int k = (rect.right - rect.left) / N;
		HBRUSH b = CreateSolidBrush(RGB(0, 255, 0));
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		SelectObject(hdc, pen);
		SelectObject(hdc, b);
		le.push_back(m1);
		to.push_back(m2);
		int l = (m1 / k)*k, t = (m2 / k)*k;
		//
		char* ch;
		int var = rand() % 2;
		if (var == 0) ch = ch1;
		else ch = ch2;
		HBITMAP bitmap = CreateBitmap(width, height, 1, 32, ch);
		HDC hdc2 = CreateCompatibleDC(hdc);
        SelectObject(hdc2, bitmap);
		BitBlt(hdc, l, t, width, height, hdc2, 0, 0, SRCCOPY);
		//SelectObject(hdc2, oldm);
		//Ellipse(hdc, l, t, l + k, t + k);
		ReleaseDC(hWnd, hdc);
		DeleteObject(pen);
		DeleteObject(b);
		DeleteDC(hdc2);
		DeleteObject(bitmap);
		//	 
	}
	break;
	case WM_QUIT:
	{

	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
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
