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


WCHAR szTitleConsole[MAX_LOADSTRING];              // Text záhlaví konzole
WCHAR szConsoleWindow[MAX_LOADSTRING];            // název třídy konzoloveho okna

// Předat dál deklarace funkcí zahrnuté v tomto modulu kódu:
ATOM                MyRegisterClass(HINSTANCE hInstance, WCHAR _className[]);
BOOL                InitInstance(HINSTANCE hInstance, int nCmdShow, WCHAR _title[], WCHAR _className[]);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



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
    MyRegisterClass(hInstance, szWindowClass);
	MyRegisterClass(hInstance, CharToLPCWSTR("ConsoleWindow"));

    // Provést inicializaci aplikace:
    if (!InitInstance (hInstance, nCmdShow, szTitle, szWindowClass))
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
ATOM MyRegisterClass(HINSTANCE hInstance, WCHAR _className[])
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
	wcex.lpszClassName = _className;
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow,  WCHAR _title[], WCHAR _className[])
{
   hInst = hInstance; // Uloží popisovač instance do naší globální proměnné.

   HWND hWnd = CreateWindowW(_className, _title, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, /*CW_USEDEFAULT*/1920, 1080, nullptr, nullptr, hInstance, nullptr);

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

	case WM_KEYDOWN:
	{
		//int keyL = GET_KEYSTATE_LPARAM(lParam);
		int keyW = GET_KEYSTATE_WPARAM(wParam);

		if (keyW == VK_RETURN)
		{
			RECT rect = CSurface::WindowRect;
			l = new Loader("index.html", rect.right - rect.left, rect.bottom - rect.top);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		}

	}
	break;
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
	case WM_LBUTTONDOWN:
	{
		double x = GET_X_LPARAM(lParam);
		double y = GET_Y_LPARAM(lParam);
		Debug::console << "MOUSE X: " << x << ", Y: " << y << endl;
		//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyzovat možnosti nabídky:
            switch (wmId)
            {
            case IDM_CONSOLE:
			{
				InitInstance(hInst, 3 , CharToLPCWSTR("Console Window"), CharToLPCWSTR("consoleWindow"));
			}
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
			LPWSTR ID = CharToLPCWSTR("");
			GetWindowText(hWnd, ID, MAX_LOADSTRING);

			GetWindowRect(hWnd, &CSurface::WindowRect);
			
			RECT rect = CSurface::WindowRect;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

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

			p->roundedRectangle(CSurface::cr, 0, 0, rect.right - rect.left, (rect.bottom - rect.top), Color(255, 255, 255, 1.0), 0);

			LPWSTR ConsoleWin = CharToLPCWSTR("Console Window");

			if (lstrcmpW(ID , ConsoleWin))
			{

				p->doRender(CSurface::cr, l->document);
			}
			else
			{
				//Debug::console.setParameters(CSurface::cr, hWnd, 13.0, Color(0, 0, 0, 1.0), Vector2(10.0, ((rect.bottom - rect.top) / 10.0)), rect.right - rect.left, (rect.bottom - rect.top) / 10.0);
				Debug::console.setCairo(CSurface::cr)
					->setHWnd(hWnd)
					->setFontSize(15.0)
					->setTextColor(Color(0, 0, 0, 1.0))
					->setPosition(Vector2(10.0, ((rect.bottom - rect.top) / 10.0)))
					->setWidth(rect.right - rect.left)->setHeight((rect.bottom - rect.top) / 10.0);
				Debug::console.update();
			}

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
	{
		LPWSTR ID = CharToLPCWSTR("");
		GetWindowText(hWnd, ID, MAX_LOADSTRING);

		if (lstrcmpW(ID, CharToLPCWSTR("Console Window")))
			PostQuitMessage(0);
	}

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
