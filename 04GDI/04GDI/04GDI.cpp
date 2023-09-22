// 04GDI.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "04GDI.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY04GDI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY04GDI));

    MSG msg;

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY04GDI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY04GDI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#define SEGMENTS  500
#define PI 3.1415923

	switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
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
			HDC hdc = hdc = BeginPaint(hWnd, &ps);
			RECT rt;

			HPEN hPen = (HPEN)::GetStockObject(NULL_PEN);
			::SelectObject(hdc, hPen);
			int cxClient, cyClient;
			int x, y;
			POINT pt[SEGMENTS];

            // ȡ�ô��ڿͻ����Ĵ�С
			GetClientRect(hWnd, &rt);
			cxClient = rt.right - rt.left;
			cyClient = rt.bottom - rt.top;

			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, _T("Bitmap.bmp"), IMAGE_BITMAP, cxClient/2, cyClient/2, LR_LOADFROMFILE);
			HBRUSH brush1 = ::CreatePatternBrush(hBitmap);
			::SelectObject(hdc, brush1);
			Rectangle(hdc, 0, 0, cxClient / 2, cyClient / 2);

			HBRUSH brush2 = ::CreateSolidBrush(RGB(59, 67, 78));
			::SelectObject(hdc, brush2);
			Rectangle(hdc, cxClient / 2, 0, cxClient, cyClient / 2);

			HBRUSH brush3 = ::CreateSolidBrush(RGB(78, 100, 52));
			::SelectObject(hdc, brush3);
			Rectangle(hdc, 0, cyClient / 2, cxClient / 2, cyClient);

			HBRUSH brush4 = ::CreateSolidBrush(RGB(68, 7, 101));
			::SelectObject(hdc, brush4);
			Rectangle(hdc, cxClient / 2, cyClient / 2, cxClient, cyClient);


			// ��sin()
			SelectObject(hdc, (HPEN)::GetStockObject(BLACK_PEN));
			// ����������
			MoveToEx(hdc, cxClient / 2, cyClient/4, NULL);
			LineTo(hdc, cxClient, cyClient/4);
			// �ҳ�500���������
			for (size_t i = 0; i < SEGMENTS; i++)
			{
				pt[i].x = cxClient/2 *i / SEGMENTS + cxClient/2;
				pt[i].y = (cyClient / 4) * (1 - sin(2 * PI * i / SEGMENTS));
			}
			// ����������һ��
			Polyline(hdc, pt, SEGMENTS);

			// ����Բ
			SelectObject(hdc, (HBRUSH)::GetStockObject(NULL_BRUSH));
			Ellipse(hdc, 0, cyClient / 2, cxClient / 2, cyClient);

			// �������
			POINT lpPoint[6];
			for (size_t i = 0; i < sizeof(lpPoint); i++)
			{
				lpPoint[i].x = cxClient/4.0 * cos(i * PI / 3.0 + PI / 6.0) + cxClient * 3 / 4.0;
                 lpPoint[i].y =  cyClient / 4.0 * sin(i * PI / 3.0 + PI / 6.0) + cyClient * 3 / 4.0;
			}
			  Polygon(hdc, lpPoint, sizeof(lpPoint));

			EndPaint(hWnd, &ps);
			return 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �����ڡ������Ϣ�������
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
