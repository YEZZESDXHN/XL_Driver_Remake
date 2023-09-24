// XL_Demo.cpp : 定义应用程序的入口点。


#include "framework.h"
#include "main.h"
#include<commctrl.h>
//#include <iostream>
//#include<tchar.h>


#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING]= L"XL_Demo";                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]= L"XL_Demo";            // 主窗口类名

LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);



HWND CreatePageWnd(HWND hTab, WNDPROC PageWndProc)
{
	RECT rcTabDisplay;
	//获取Tab控件客户区的的大小（Tab窗口坐标系）
	GetClientRect(hTab, &rcTabDisplay);//获取Tab窗口的大小（而不是在屏幕坐标系中）
	TabCtrl_AdjustRect(hTab, FALSE, &rcTabDisplay);//通过窗口大小，获取客户区大小。
	//创建与Tab控件客户区大小的画布
	HWND hPage = CreateWindowEx(
		NULL,		//window extend Style
		TEXT("edit"),   // window class name
		NULL,  // window caption
		WS_CHILD,      // window style
		rcTabDisplay.left,            // initial x position
		rcTabDisplay.top,            // initial y position
		rcTabDisplay.right,            // initial x size
		rcTabDisplay.bottom,            // initial y size
		hTab,                     // parent window handle
		NULL,                     // window menu handle
		hInst,                // program instance handle
		NULL);                    // creation parameters
	SetWindowLongPtr(hPage, GWLP_WNDPROC, (LONG_PTR)PageWndProc);//子类化窗口
	return hPage;
}

int  WINAPI   WinMain(HINSTANCE  hInstance, HINSTANCE  hPrevInstance,
	LPSTR lpCmdLine, int  nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_XLDEMO, szWindowClass, MAX_LOADSTRING);

	//1.注册窗口类
	WNDCLASS  wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)(GetStockObject(DEFAULT_PALETTE));//背景色
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);//光标
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_XLDEMO));//图标
												//wnd.lpfnWndProc = DefWindowProc;//默认窗口过程函数，用于处理消息
	wnd.lpfnWndProc = MyWindowProc;//自定义的窗口过程函数
	wnd.lpszClassName = L"MrHuang";//窗口类名
	wnd.lpszMenuName = NULL;//菜单资源名称
	wnd.style = CS_HREDRAW | CS_VREDRAW;//窗口类、样式
	wnd.hInstance = hInstance;//实例句柄

	RegisterClass(&wnd);

	GUI = CreateWindow(L"MrHuang", L"XL Demo",
			WS_OVERLAPPEDWINDOW, 100, 100, 1300, 800, NULL, NULL, hInstance, NULL);

	// 创建TabCtrl控件
	hTabCtrl = CreateWindowEx(0, TEXT("SysTabControl32"), NULL, WS_VISIBLE | WS_CHILD | TCS_TABS,
		100, 100, 300, 200, GUI, (HMENU)hTabCtrl_id, hInstance, 0);

	//CreatePageWnd(hTabCtrl, MyWindowProc);

	// 插入选项卡
	TCITEM tcItem = { 0 };
	tcItem.mask = TCIF_IMAGE | TCIF_TEXT;
	tcItem.pszText = (LPTSTR)TEXT("Item1");
	tcItem.iImage = 0;
	SendMessage(hTabCtrl, TCM_INSERTITEM, 0, (LPARAM)&tcItem);

	tcItem.pszText = (LPTSTR)TEXT("Item2");
	SendMessage(hTabCtrl, TCM_INSERTITEM, 1, (LPARAM)&tcItem);

	tcItem.pszText = (LPTSTR)TEXT("Item3");
	SendMessage(hTabCtrl, TCM_INSERTITEM, 2, (LPARAM)&tcItem);

	//Button_test = CreateWindowExW(
	//	0, L"button", L"init", WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON, 10, 10,
	//	50, 50, hTabCtrl, (HMENU)Button_test_id, GetModuleHandle(NULL), NULL
	//);



	//显示窗口
	ShowWindow(GUI, nShowCmd);
	//更新窗口(发送WM_PAINT)
	UpdateWindow(GUI);

	

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_XLDEMO));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
LRESULT  CALLBACK    MyWindowProc(HWND hWnd, UINT Msg,WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_COMMAND:
        {
		//菜单ID
			WORD  menuId = LOWORD(wParam);
			switch (menuId)
			{
			case Menu_ReleaseLog_id:
				MessageBox(hWnd, ReleaseLog, L"提示", MB_OK);
				break;
			
			case Menu_about_id:
				{
					//hdc = GetDC(Text_out);
					//TextOut(hdc, 0, 0, TEXT("向上"), 9);
					MessageBox(hWnd, about, L"关于", MB_OK);
					break;
				}
			}
        }
        break;
    case WM_PAINT:
        {
            
		break;
        }
        
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_CREATE:
		{
			//创建顶层菜单
			HMENU  hTop = CreateMenu();//空菜单

			InsertMenu(hTop, 0, MF_STRING | MF_BYPOSITION, Menu_tools_id, L"工具"); //添加第二项

																		//创建弹出菜单(子菜单)
			HMENU  hPopUp = CreatePopupMenu();//空菜单 
			AppendMenu(hPopUp, MF_SEPARATOR, NULL, NULL);//分隔条
			AppendMenu(hPopUp, MF_STRING, Menu_file_1_id, L"打开");
			InsertMenu(hPopUp, 0, MF_STRING | MF_BYPOSITION, Menu_file_2_id, L"新建");

			//添加第三项
			AppendMenu(hTop, MF_POPUP, (UINT_PTR)hPopUp, L"打开");

			AppendMenu(hTop, MF_STRING, Menu_about_id, L"关于"); //添加第一项
			AppendMenu(hTop, MF_STRING, Menu_ReleaseLog_id, L"ReleaseLog"); //添加第一项
			//InsertMenu(hTop, 0, MF_STRING | MF_BYPOSITION, 400, L"关于"); //添加第二项

			//设置窗口菜单
			SetMenu(hWnd, hTop);

			//释放菜单资源
			DestroyMenu(hTop);
			DestroyMenu(hPopUp);
			break;
		}




    }
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}




