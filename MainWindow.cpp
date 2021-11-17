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
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
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
    OutputDebugStringA(__FUNCTION__ "���Ăяo����܂����B\n");
}

MainWindow::~MainWindow()
{
    OutputDebugStringA(__FUNCTION__ "���Ăяo����܂����B\n");
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂�
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
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
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI: ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND  - �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT    - ���C�� �E�B���h�E��`�悷��
//  WM_DESTROY  - ���~���b�Z�[�W��\�����Ė߂�
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
            // �I�����ꂽ���j���[�̉��:
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
            // TODO: HDC ���g�p����`��R�[�h�������ɒǉ����Ă�������...
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

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
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
