#include "framework.h"
#include "오목게임만들기-격자좌표변환.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;

    // 기본 메시지 루프입니다:
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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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


#define MAX_LOADSTRING 100
#define X_COUNT 19
#define Y_COUNT 19
#define GRID_SIZE 30
void DrawGrid(HDC hdc) 
{
    HBRUSH hBrush = CreateSolidBrush(RGB(244, 176, 77));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    for (int y = 0; y < Y_COUNT; y++)
    {
        for (int x = 0; x < X_COUNT; x++)
        {
            
            Rectangle(hdc,
                GRID_SIZE / 2 + x * GRID_SIZE,
                GRID_SIZE / 2 + y * GRID_SIZE,
                GRID_SIZE / 2 + (x + 1) * GRID_SIZE,
                GRID_SIZE / 2 + (y + 1) * GRID_SIZE);
        }
    }
}


POINT getGridPosition(int mouseX, int mouseY)
{
    POINT gridPos;
    int offset = GRID_SIZE / 2;

    //마우스 클릭하면 바독알 좌표 계산
    gridPos.x = (mouseX - offset + GRID_SIZE / 2) / GRID_SIZE;
    gridPos.y = (mouseY - offset + GRID_SIZE / 2) / GRID_SIZE;
    return gridPos;
}



void DrawStone(HDC hdc, int gridX, int gridY, bool isBlack)
{
    //바독판에 시작 오프섹
    int offset = GRID_SIZE / 2;
    //바독판 표시 위치 중심좌표
    int centerX = offset + gridX * GRID_SIZE;
    int centerY = offset + gridY * GRID_SIZE;
    //둘의 반지름 (셀 크기와 40~45% 정도)
    int radius = GRID_SIZE * 0.45;

    //색상
    COLORREF color = isBlack ? RGB(0, 0, 0) : RGB(255, 255, 255);
    HBRUSH hBrush = CreateSolidBrush(color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    //둘 그리기
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

    //브러시 복원 및 삭제
    SelectObject(hdc, oldBrush);
    DeleteObject(hBrush);
}



int board[Y_COUNT+1][X_COUNT+1] = { 0, };

bool  checkWin8Dir(int x, int y,int player)
{
    const int dx[8] = { 1, 0, 1,  -1,-1,0,-1,1 };
    const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

    for (int dir = 0; dir < 8; ++dir)
    {
        int count = 1;

        //방향 탐객
        for (int i = 1; i < 5; i++)
        {
            int nx = x + dx[dir] * i;
            int ny = y + dy[dir] * i;
            if (nx < 0 || ny < 0 || nx >= 19 || ny >= 19) break;
            if (board[ny][nx] == player)
                count++;
            else
                break;
        }
        if(count == 5) return true; // 정확이 5일때 때만 승리
    }
    return false;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int mx, my;
    static bool isBlackTurn = true;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
    case WM_LBUTTONDOWN:
        mx = LOWORD(lParam);
        my = HIWORD(lParam);
        POINT grid = getGridPosition(mx, my);

        if (board[grid.y][grid.x] == 0)
        {
            int player = isBlackTurn ? 1 : 2;
            board[grid.y][grid.x] = player;
            if (checkWin8Dir(grid.x, grid.y, player))
            {
                MessageBox(hWnd,
                    isBlackTurn? L"Black WIN" : L"White Win",
                    L"게임 종료",
                    MB_OK);

                 //게임 초기화 또는 종료 처리
                 //보드판 초기화 memset(boarc,0,sizeof(board);
            }
            isBlackTurn = !isBlackTurn;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
        }


            //돌 넣기 로직
            /*if (board[grid.y][grid.x] == 0)
            {
                board[grid.y][grid.x] = isBlackTurn? 1 : 2;
                isBlackTurn = !isBlackTurn;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
            }*/
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DrawGrid(hdc);

            for (int y = 0; y < Y_COUNT; y++) 
            {
                for (int x = 0; x < X_COUNT; x++)
                {
                    if (board[y][x] == 1)
                    {
                        DrawStone(hdc, x, y, true);
                    }
                    else if(board[y][x] == 2)
                    {
                        DrawStone(hdc, x, y, false);
                    }

                }
            }
            EndPaint(hWnd, &ps);
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
