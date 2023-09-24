#pragma once

#include "resource.h"
#include<commctrl.h>


WCHAR about[128] = L"xlCANdemo - Test Application for XL Family Driver\nAuthor：王志晨\nVersion:V1.1\nData:2023.9.13";
WCHAR ReleaseLog[256] = L"V1.0:初版\nV1.1:优化发送密钥时间,优化dll字符串大小";



//定义控件
HWND GUI;



HWND Button_send;
HWND Button_start;
HWND Button_stop;
HWND Button_test;
HWND Button_;
HWND Button_;
HWND Button_;
HWND Button_;
HWND Button_;
HWND Button_;
HWND Button_;
HWND Button_;
HWND Button_;
HWND Button_;


#define Button_send_id 1000
#define Button_start_id 1001
#define Button_stop_id 1002
#define Button_test_id 1003


HWND Edit_Textout;
HWND Edit_datain;
HWND Edit_info;
HWND Edit_debug;

#define Edit_Textout_id 2000
#define Edit_info_id 2001
#define Edit_debug_id 2002
#define Edit_Edit_datain_id 2003



HWND ListBox_did_list;
#define Edit_ListBox_did_list_id 3000


HWND ComboBox_ecu_list;
#define Edit_ComboBox_ecu_list_id 4000



HWND hTabCtrl;
#define hTabCtrl_id 5000
HWND hTabCtrl1;
#define hTabCtrl1_id 5001




#define Menu_about_id 0010
#define Menu_ReleaseLog_id   0020
#define Menu_file_1_id   0030
#define Menu_file_2_id   0031
#define Menu_tools_id 0040






HWND m_dlg1, m_dlg2, m_hShowDlg;