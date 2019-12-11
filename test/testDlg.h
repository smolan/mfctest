
// testDlg.h: 头文件
//
#include "ChartCtrl/ChartCtrl.h"
#include <string> 
#include<vector>
#include <io.h>   
#include <direct.h>
#pragma once
using namespace std;
void getFiles(string path, vector<string>& files);
void getFiless(string path, vector<string>& files);
// CtestDlg 对话框
class CtestDlg : public CDialogEx
{
// 构造
public:
	CtestDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CChartCtrl m_Show_Curve;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On_ShowCurve();
	afx_msg void On_Open_childDlg();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg CString BootOpenDialog();
};
