// HTMLRenderer.cpp: Definuje vstupní bod pro aplikaci.
//

#include "HTMLRenderer.h"
#include "CairoSurface.h"
//

#define MAX_LOADSTRING 100
#define	CAIRO_HAS_WIN32_SURFACE 1

// Globální proměnné:
HINSTANCE hInst;                                // aktuální instance
WCHAR szTitle[MAX_LOADSTRING];                  // Text záhlaví
WCHAR szWindowClass[MAX_LOADSTRING];            // název třídy hlavního okna

// Předat dál deklarace funkcí zahrnuté v tomto modulu kódu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HBITMAP g_hbmBall = NULL;



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Sem umístěte kód.

    // Inicializovat globální řetězce
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HTMLRENDERER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Provést inicializaci aplikace:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HTMLRENDERER));

    MSG msg;

    // Hlavní smyčka zpráv:
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
//  FUNKCE: MyRegisterClass()
//
//  ÚČEL: Zaregistruje třídu okna.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HTMLRENDERER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HTMLRENDERER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCE: InitInstance(HINSTANCE, int)
//
//   ÚČEL: Uloží popisovač instance a vytvoří hlavní okno.
//
//   KOMENTÁŘE:
//
//        V této funkci uložíme popisovač instance do globální proměnné a
//        vytvoříme a zobrazíme hlavní okno programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Uloží popisovač instance do naší globální proměnné.

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
//  FUNKCE: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ÚČEL: Zpracuje zprávy pro hlavní okno.
//
//  WM_COMMAND  – zpracování aplikační nabídky
//  WM_PAINT    - vykreslení hlavního okna
//  WM_DESTROY  - vystavení zprávy o ukončení a návrat
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_MOUSEWHEEL:
	{
		if (l)
		{
			double zDelta = GET_WHEEL_DELTA_WPARAM(wParam)/10;

			l->document->pPadding->pTop->value = l->document->pPadding->pTop->value + zDelta;
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		}
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyzovat možnosti nabídky:
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
			GetWindowRect(hWnd, &rect);
			BITMAP bm;
			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmOld =  CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
			HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hbmOld);

			GetObject(hbmOld, sizeof(bm), &bm);


            // TODO: Sem přidejte jakýkoli kód výkresu, který používá hdc...

			CSurface::surface = cairo_win32_surface_create(hdcMem);
			CSurface::cr = cairo_create(CSurface::surface);

			if (!p)
			{		
				p = new Renderer();
				Debug d = Debug(p);
				l = new Loader("index.html", rect.right - rect.left, rect.bottom - rect.top);
			}

			Debug::console.setParameters(CSurface::cr, 13.0, Color(255, 255, 255, 1.0), Vector2(10.0, ((rect.bottom - rect.top) / 10.0*5.0)), rect.right - rect.left, (rect.bottom - rect.top) / 10.0);

			p->roundedRectangle(CSurface::cr, 0, 0, rect.right - rect.left, (rect.bottom - rect.top), Color(255, 255, 255, 1.0), 0);

			p->doRender(CSurface::cr, l->document);

			cairo_destroy(CSurface::cr);
			cairo_surface_destroy(CSurface::surface);

			bool retVal = BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

			cairo_surface_write_to_png(CSurface::surface, "hello.png");


			SelectObject(hdcMem, hOld);
			DeleteObject(hbmOld);
			DeleteDC(hdcMem);

            EndPaint(hWnd, &ps);

			return 0;
        }
        break;
    case WM_DESTROY:
		DeleteObject(g_hbmBall);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Obslužná rutina zprávy pro pole O aplikaci.
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
