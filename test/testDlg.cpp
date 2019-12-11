
// testDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChildDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DATA_SHOW_LENGHT	2000	//总共显示的点个数
#define DATA_UPDATE_LENGHT	10    //每次更新的点个数
double xBuff[DATA_SHOW_LENGHT] = { 0 };
double yBuff[DATA_SHOW_LENGHT] = { 0 };
double yBuff2[DATA_SHOW_LENGHT] = { 0 };
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestDlg 对话框



CtestDlg::CtestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_Show_Curve);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CtestDlg::On_ShowCurve)
	ON_COMMAND(ID_32772, &CtestDlg::On_Open_childDlg)
	ON_BN_CLICKED(IDOK, &CtestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CtestDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CtestDlg 消息处理程序

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);  //IDR_MENU1为菜单栏ID号
	SetMenu(&menu);
	m_Show_Curve.GetTitle()->AddString(_T("我就是噪声"));
	CChartAxis *pAxis = NULL;
	pAxis = m_Show_Curve.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_Show_Curve.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetMinMax(0, 360);
	for (int i = 0; i < DATA_SHOW_LENGHT; i++) {
		xBuff[i] = i;
		yBuff[i] = rand() % 360;
		yBuff2[i] = rand() % 360;
	}
	
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtestDlg::OnTimer(UINT nIDEvent) {
	static int offset = 0;
	for (int i = 0; i < DATA_SHOW_LENGHT - DATA_UPDATE_LENGHT; i++)
	{
		xBuff[i] = xBuff[i] + 10;
		yBuff[i] = rand() % 360;
		yBuff2[i] = rand() % 360;
	}

	int index = DATA_SHOW_LENGHT - DATA_UPDATE_LENGHT;
	for (int i = 0; i < DATA_UPDATE_LENGHT; i++)
	{
		xBuff[index + i] = xBuff[index + i] + 10;
		yBuff[index + i] = rand() % 360; 
		yBuff2[index + i] = rand() % 360;
	}
	//DataShow(xBuff, yBuff, DATA_SHOW_LENGHT);
	m_Show_Curve.EnableRefresh(false);
	CChartLineSerie *pLineSerie;
	m_Show_Curve.RemoveAllSeries();
	pLineSerie = m_Show_Curve.CreateLineSerie();
	pLineSerie->SetColor(RGB(0, 255, 0));
	pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序
	pLineSerie->AddPoints(xBuff, yBuff, DATA_SHOW_LENGHT);
	CChartLineSerie *pLineSerie2;
	pLineSerie2 = m_Show_Curve.CreateLineSerie();
	pLineSerie2->SetColor(RGB(0, 0, 255));
	pLineSerie2->AddPoints(xBuff, yBuff2, DATA_SHOW_LENGHT);
	UpdateWindow();
	m_Show_Curve.EnableRefresh(true);
	offset++;
	if (offset > 10000) {
		offset = 0;
	}
}

void CtestDlg::On_ShowCurve()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(0, 300, NULL);
}


void CtestDlg::On_Open_childDlg()
{
	// TODO: 在此添加命令处理程序代码
	ChildDlg dlg;
	dlg.DoModal();
}


void CtestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	char szPath[MAX_PATH];
	CString str;

	ZeroMemory(szPath, sizeof(szPath));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	//CString cs_szPath;
	//cs_szPath.Format("%s", szPath);
	bi.pszDisplayName = szPath;
	bi.lpszTitle = _T("请选择需要打包的目录：");
	bi.ulFlags = 0x0040 | BIF_EDITBOX;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		str.Format(_T("选择的目录为 %s"), szPath);

		AfxMessageBox(str);
	}
	vector<string> filess;
	string projectPath = szPath;
	//getFiles(projectPath, filess);
	getFiless(projectPath, filess);
	for (int i = 0; i < filess.size(); i++)
	{
		str = filess[i].c_str();

		AfxMessageBox(str);
	}
}

CString CtestDlg::BootOpenDialog()
{
	CString strFile = _T("");

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT, _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}

	return strFile;
}

void CtestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	CString m_strDescPath = "";
	m_strDescPath = BootOpenDialog();
}

void getFiles(string path, vector<string>& files)
{
	intptr_t   hFile = 0;//文件句柄，过会儿用来查找
	struct _finddata_t fileinfo;//文件信息
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		//如果查找到第一个文件
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))//如果是文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(fileinfo.name);
				//	getFiles(p.assign(path).append("\\").append(fileinfo.name), files);

			}
			//else//如果是文件
			//{
			//	files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			//}
		} while (_findnext(hFile, &fileinfo) == 0); //能寻找到其他文件

		_findclose(hFile);  //结束查找，关闭句柄
	}
}
void getFiless(string path, vector<string>& files)
{
	intptr_t   hFile = 0;//文件句柄，过会儿用来查找
	struct _finddata_t fileinfo;//文件信息
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*.csv").c_str(), &fileinfo)) != -1)
		//如果查找到第一个文件
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))//如果是文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiless(p.assign(path).append("\\").append(fileinfo.name), files);

			}
			else//如果是文件
			{
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));

				files.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0); //能寻找到其他文件

		_findclose(hFile);  //结束查找，关闭句柄
	}
}