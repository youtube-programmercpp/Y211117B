#include "framework.h"
#include "MainWindow.h"
#include "Resource.h"

#include <string>
namespace Win32Wrap {
    std::wstring LoadStringW
    ( _In_opt_                                 HINSTANCE hInstance   
    , _In_                                     UINT      uID         
    )
    {
        LPCWSTR lpBuffer;
        if (const auto n = ::LoadStringW
        ( /*_In_opt_                                 HINSTANCE hInstance   */hInstance   
        , /*_In_                                     UINT      uID         */uID         
        , /*_Out_writes_to_(cchBufferMax, return +1) LPWSTR    lpBuffer    */LPWSTR(&lpBuffer)
        , /*_In_                                     int       cchBufferMax*/0
        ))
            return { lpBuffer, static_cast<size_t>(n) };
        else
            return {};
    }
}


//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MainWindow::MyRegisterClass(HINSTANCE hInstance)
{
    const auto sWindowClass = Win32Wrap::LoadStringW(hInstance, IDC_Y211117B);




    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_Y211117B));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_Y211117B);
    wcex.lpszClassName  = sWindowClass.c_str();
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

MainWindow::MainWindow()
{
    OutputDebugStringA(__FUNCTION__ "が呼び出されました。\n");
}

MainWindow::~MainWindow()
{
    OutputDebugStringA(__FUNCTION__ "が呼び出されました。\n");
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL MainWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    const auto sTitle = Win32Wrap::LoadStringW(hInstance, IDS_APP_TITLE);



   HWND hWnd = CreateWindowW(LPCWSTR(MyRegisterClass(hInstance)), sTitle.c_str(), WS_OVERLAPPEDWINDOW,
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
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_NCDESTROY:
        delete reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        return 0;
    case WM_CREATE:
        SetWindowLongPtr(hWnd, GWLP_USERDATA, LONG_PTR(new MainWindow));
        return 0;
    case WM_COMMAND:
        if (const auto p = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA))) {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(HINSTANCE(GetWindowLongPtr(hWnd, GWLP_HINSTANCE)), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
            // TODO: HDC を使用する描画コードをここに追加してください...
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

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK MainWindow::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
