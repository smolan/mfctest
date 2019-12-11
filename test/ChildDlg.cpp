// ChildDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "ChildDlg.h"
#include "afxdialogex.h"


// ChildDlg 对话框

IMPLEMENT_DYNAMIC(ChildDlg, CDialogEx)

ChildDlg::ChildDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ChildDlg::~ChildDlg()
{
}

void ChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChildDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChildDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChildDlg 消息处理程序
BOOL ChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString text = _T("我有一只小毛驴");
	GetDlgItem(IDC_EDIT1)->SetWindowText(text);
	GetDlgItem(IDC_STATIC)->SetWindowText(text);
	return TRUE;
}

void ChildDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(text);
	GetDlgItem(IDC_STATIC)->SetWindowText(text);
}
