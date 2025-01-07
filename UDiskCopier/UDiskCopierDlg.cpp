
// UDiskCopierDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "UDiskCopier.h"
#include "UDiskCopierDlg.h"
#include "afxdialogex.h"
#include<string>
#include<vector>
#include <cstring>
#include<thread>
#include <fstream>
#include "ConfigSaver.h" // 配置文件写入
#include "ConfigLoader.h" // 配置文件读入
#include "Copier.h" // 复制功能的实现
#include "Extension.h"// 扩展名相应函数


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_ICON_NOTIFY  WM_USER+100

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

// 必须把菜单设成全局变量，不然每次打开的都是新的
HMENU hMenu = LoadMenu(NULL,MAKEINTRESOURCE(IDR_MENU1)); //菜单的ID
HMENU hSubMenu = GetSubMenu(hMenu, 0);
LRESULT CUDiskCopierDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONDOWN://点击左键，调出程序
	{
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
		break;
	}
	case WM_RBUTTONUP://点击右键，出现选择菜单
	{
		POINT point;
		GetCursorPos(&point); //鼠标位置

		SetForegroundWindow();

		TrackPopupMenu(hSubMenu, 0,
			point.x, point.y, 0, m_hWnd, NULL);
		break;
	}
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUDiskCopierDlg 对话框



CUDiskCopierDlg::CUDiskCopierDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UDISKCOPIER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDiskCopierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_ComBox_black_write);
	DDX_Control(pDX, IDC_EDIT1, m_fileExtensions);
	DDX_Control(pDX, IDC_EDIT2, m_delay);
	DDX_Control(pDX, IDC_EDIT3, m_fileSize);
	DDX_Control(pDX, IDC_FolerToU, m_FolderToU);
	DDX_Control(pDX, IDC_EDIT4, m_reverseCopyKey);
	DDX_Control(pDX, IDC_AUTOCOPY, m_AutoCopy);
	DDX_Control(pDX, IDC_HideTray, m_HideTray);
}

BEGIN_MESSAGE_MAP(CUDiskCopierDlg, CDialogEx)
	
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUDiskCopierDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_PATH, &CUDiskCopierDlg::OnEnChangePath)
	ON_BN_CLICKED(IDC_SHOWFILE, &CUDiskCopierDlg::OnBnClickedShowfile)
	ON_BN_CLICKED(IDC_SAVE_AND_START, &CUDiskCopierDlg::OnBnClickedSaveAndStart)
	ON_BN_CLICKED(IDC_CHECK_PICTURE, &CUDiskCopierDlg::OnBnClickedCheckPicture)
	ON_BN_CLICKED(IDC_CHECK_VIDEO, &CUDiskCopierDlg::OnBnClickedCheckVideo)
	ON_BN_CLICKED(IDC_CHECK_AUDIO, &CUDiskCopierDlg::OnBnClickedCheckAudio)
	ON_BN_CLICKED(IDC_CHECK_OFFICE, &CUDiskCopierDlg::OnBnClickedCheckOffice)
	ON_BN_CLICKED(IDC_CHECK1, &CUDiskCopierDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_HIDE_BUTTON, &CUDiskCopierDlg::OnBnClickedHideButton)
	ON_WM_CLOSE()
	ON_COMMAND(ID_TRAY_32771, &CUDiskCopierDlg::OnTray32771)
	ON_COMMAND(ID_TRAY_32772, &CUDiskCopierDlg::OnTray32772)
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_BN_CLICKED(IDC_AUTORUN, &CUDiskCopierDlg::OnBnClickedAutorun)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK3, &CUDiskCopierDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_RUN, &CUDiskCopierDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_BUTTON4, &CUDiskCopierDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_FolerToU, &CUDiskCopierDlg::OnBnClickedFolertou)
	ON_COMMAND(ID_TRAY_DIRECTORY, &CUDiskCopierDlg::OnTrayDirectory)
	ON_COMMAND(ID_TRAY_CODER, &CUDiskCopierDlg::OnTrayCoder)
	ON_COMMAND(ID_TRAY_COURSE, &CUDiskCopierDlg::OnTrayCourse)
	ON_COMMAND(ID_TRAY_AUTOCOPY, &CUDiskCopierDlg::OnTrayAutocopy)
	ON_BN_CLICKED(IDC_AUTOCOPY, &CUDiskCopierDlg::OnBnClickedAutocopy)
	ON_COMMAND(ID_TRAY_HideTray, &CUDiskCopierDlg::OnTrayHidetray)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_BN_CLICKED(IDC_HideTray, &CUDiskCopierDlg::OnBnClickedHidetray)
END_MESSAGE_MAP()

//检测开机自启的函数
BOOL checkAutoRun(CString startName);

//用于开始复制的函数
void startCopy();

//————————全局变量区————————
extern std::string config;
//创建用于初始化和更改的类  置为全局变量
ConfigSaver CS;
//初始化类   为全局变量
ConfigLoader CL;
//初始化类 扩展名
Extension EX;
//获得大小
extern int int_getFileSize;
//获得延迟时间
extern int int_getDelay;
//设置保存路径
extern CString strFolderPath;
//mfc应用程序所在的文件夹
CString mfcPath;
//————————————————————————————

//在mfc初始化中调用的函数
void CUDiskCopierDlg::initAll() {
	//在此添加需要通过配置文件初始化的操作

	//初始化默认路径
	GetDlgItem(IDC_PATH)->SetWindowText(CL.init_savePath);// 初始化编辑框内的默认路径
	strFolderPath = CL.init_savePath;//全局变量的另一个初始化路径也要赋值

	//初始化延迟复制时间
	m_delay.SetWindowText(CL.init_copyDelay);

	//初始化限制文件大小
	m_fileSize.SetWindowText(CL.init_fileSize);

	//初始化扩展名
	m_fileExtensions.SetWindowText(CL.init_extensions);

	//初始化反向复制KEY
	m_reverseCopyKey.SetWindowText(CL.init_reverseCopyKey);

	//初始化黑白名单
	if (CL.init_copyFormat == "write") {
		m_ComBox_black_write.SetCurSel(0);
	}
	else {
		m_ComBox_black_write.SetCurSel(1);
	}

	//初始化自动隐藏
	if (CL.init_autoHide == _T("ON")) {
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(1);
		SetTimer(1, 100, NULL);//创建定时器	用于关闭窗口
	}
	else {
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(0);
	}

	//初始化自动隐藏
	if (CL.init_copyPrompt == _T("ON")) {
		((CButton*)GetDlgItem(IDC_DisableMessage))->SetCheck(1);
	}
	else {
		((CButton*)GetDlgItem(IDC_DisableMessage))->SetCheck(0);
	}

	//初始化反向复制选择
	if (CL.init_reverseCopySelect == _T("ON")) {
		m_FolderToU.SetCheck(1);
	}
	else {
		m_FolderToU.SetCheck(0);
	}

	//初始化是否自动运行
	if (CL.init_autoCopy == _T("ON")) {
		m_AutoCopy.SetCheck(1);//设置主页面打勾
		CheckMenuItem(hSubMenu, ID_TRAY_AUTOCOPY, MF_BYCOMMAND | MF_CHECKED);//菜单打勾
		//还得执行自动运行
		//开始进行无限复制
		prepareForCopy();

		std::thread ST(startCopy);
		ST.detach();// 分离线程

	}
	else {
		m_AutoCopy.SetCheck(0);
	}

	//初始化反向复制选择
	if (CL.init_hideTray == _T("ON")) {
		m_HideTray.SetCheck(1);
		//隐藏托盘
		NOTIFYICONDATA NotifyIcon;//创建结构体
		NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
		NotifyIcon.hWnd = m_hWnd;//绑定句柄

		Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);//NIM_DELETE：删除
	}
	else {
		m_HideTray.SetCheck(0);
	}


	//初始化反向复制KEY的编辑框是否禁用
	if (m_FolderToU.GetCheck()) {
		m_reverseCopyKey.EnableWindow(TRUE);
	}
	else {
		m_reverseCopyKey.EnableWindow(FALSE);
	}
}

//创建快捷键
void CUDiskCopierDlg::creatHotKey() {
	RegisterHotKey(m_hWnd, 1002, MOD_ALT, 'S');//ALT+S
}

LRESULT CUDiskCopierDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	//处理热键
	if (wParam == 1002)
	{
		KillTimer(1);//关闭可能打开的计时器
		//打开设置的主页面
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
	}

	return  0;
}


// CUDiskCopierDlg 消息处理程序
BOOL CUDiskCopierDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//设置系统托盘
	NOTIFYICONDATA NotifyIcon;
	NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	//NotifyIcon.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	NotifyIcon.hIcon = m_hIcon;  //上面那句也可以
	NotifyIcon.hWnd = m_hWnd;
	lstrcpy(NotifyIcon.szTip, _T("自动磁盘拷贝器"));
	NotifyIcon.uCallbackMessage = WM_ICON_NOTIFY;//自定义消息
	NotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &NotifyIcon);   //添加系统托盘


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

	// TODO: 在此添加额外的初始化代码
	
	//加载配置文件的内容到字符串中
	CS.InitConfig();

	//调用配置文件解析器
	CL.parseConfig();

	CreateDirectory(_T("D:\\desktop\\result"), NULL);// 创建文件夹，如果存在就不会创建

	initAll();

	//检测是否已设为开机自启
	if(checkAutoRun(_T("UDiskCopier"))) {
		//如果已自启就默认勾选上
		CButton* pCheckbox = (CButton*)GetDlgItem(IDC_AUTORUN);
		pCheckbox->SetCheck(BST_CHECKED);
	}

	creatHotKey();//创建快捷键

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CUDiskCopierDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


	if (nID == SC_MINIMIZE)
	{
		ShowWindow(FALSE);//隐藏窗口
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUDiskCopierDlg::OnPaint()
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
HCURSOR CUDiskCopierDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUDiskCopierDlg::OnEnChangePath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码


}



CString BrowseDir(const TCHAR* szTitle, const TCHAR* pszInitPath, CWnd* pParent)
{
	CFolderPickerDialog dlg;// 创建文件夹选择对话框对象

	if (szTitle)
	{
		dlg.m_ofn.lpstrTitle = szTitle;// 设置对话框标题
	}

	if (pszInitPath)
	{
		dlg.m_ofn.lpstrInitialDir = pszInitPath;// 设置初始路径
	}

	if (dlg.DoModal() != IDOK)
	{
		return _T("");// 用户取消选择，返回空字符串
	}

	return dlg.GetPathName();// 返回所选文件夹的路径
}






void CUDiskCopierDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString strFolderPath;
	GetDlgItem(IDC_PATH)->GetWindowText(strFolderPath);// 获取编辑框中的文本作为初始路径
	strFolderPath.Trim();// 去除空格

	strFolderPath = BrowseDir(_T("请选择一个文件夹："), strFolderPath, this);
	if (strFolderPath.IsEmpty())
	{
		return; // 如果路径为空，返回
	}

	GetDlgItem(IDC_PATH)->SetWindowText(strFolderPath);// 设置编辑框内的路径
}




void CUDiskCopierDlg::OnBnClickedShowfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString folderPath;//要查看的文件夹路径

	GetDlgItemText(IDC_PATH, folderPath);

	ShellExecute(NULL, _T("open"), folderPath, NULL, NULL, SW_SHOWNORMAL);//打开文件夹
}



void CUDiskCopierDlg::OnBnClickedCheckPicture()
{
	// TODO: 在此添加控件通知处理程序代码

	CString extensions;
	m_fileExtensions.GetWindowText(extensions); //获得复选框内容

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_PICTURE))->GetCheck()) { //选择时
		if (extensions == _T("")) {
			extensions = _T("jpg,png,bmp");
		}
		else {//如果不是空的就在前面加个逗号
			extensions = extensions + _T(",jpg,png,bmp");
		}

		m_fileExtensions.SetWindowText(extensions); //设置编辑框内容
	}
	else { //取消选择时
		extensions.Replace(_T(",jpg"),_T(""));//将里面的拓展名替换为空
		extensions.Replace(_T("jpg"),_T(""));//将里面的拓展名替换为空
		extensions.Replace(_T(",png"),_T(""));
		extensions.Replace(_T("png"),_T(""));
		extensions.Replace(_T(",bmp"),_T(""));
		extensions.Replace(_T("bmp"),_T(""));

		m_fileExtensions.SetWindowText(extensions);
	}
}


void CUDiskCopierDlg::OnBnClickedCheckVideo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString extensions;
	m_fileExtensions.GetWindowText(extensions); //获得复选框内容

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_VIDEO))->GetCheck()) { //选择时
		if (extensions == _T("")) {
			extensions = _T("mkv,mp4,avi,flv,mov,wmv,webm");
		}
		else {//如果不是空的就在前面加个逗号
			extensions = extensions + _T(",mkv,mp4,avi,flv,mov,wmv,webm");
		}

		m_fileExtensions.SetWindowText(extensions); //设置编辑框内容
	}
	else { //取消选择时
		extensions.Replace(_T(",mkv"), _T(""));//将里面的拓展名替换为空
		extensions.Replace(_T("mkv"), _T(""));//将里面的拓展名替换为空
		extensions.Replace(_T(",mp4"), _T(""));
		extensions.Replace(_T("mp4"), _T(""));
		extensions.Replace(_T(",avi"), _T(""));
		extensions.Replace(_T("avi"), _T(""));
		extensions.Replace(_T(",flv"), _T(""));
		extensions.Replace(_T("flv"), _T(""));
		extensions.Replace(_T(",mov"), _T(""));
		extensions.Replace(_T("mov"), _T(""));
		extensions.Replace(_T(",wmv"), _T(""));
		extensions.Replace(_T("wmv"), _T(""));
		extensions.Replace(_T(",webm"), _T(""));
		extensions.Replace(_T("webm"), _T(""));

		m_fileExtensions.SetWindowText(extensions);
	}
}


void CUDiskCopierDlg::OnBnClickedCheckAudio()
{
	// TODO: 在此添加控件通知处理程序代码
	CString extensions;
	m_fileExtensions.GetWindowText(extensions); //获得复选框内容
	
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_AUDIO))->GetCheck()) { //选择时
		if (extensions == _T("")) {
			extensions = _T("mp3,wav,wma,ape,flac,ogg,aac");
		}
		else {//如果不是空的就在前面加个逗号
			extensions = extensions + _T(",mp3,wav,wma,ape,flac,ogg,aac");
		}

		m_fileExtensions.SetWindowText(extensions); //设置编辑框内容
	}
	else { //取消选择时
		extensions.Replace(_T(",mp3"), _T(""));//将里面的拓展名替换为空
		extensions.Replace(_T("mp3"), _T(""));//将里面的拓展名替换为空
		extensions.Replace(_T(",wav"), _T(""));
		extensions.Replace(_T("wav"), _T(""));
		extensions.Replace(_T(",wma"), _T(""));
		extensions.Replace(_T("wma"), _T(""));
		extensions.Replace(_T(",ape"), _T(""));
		extensions.Replace(_T("ape"), _T(""));
		extensions.Replace(_T(",flac"), _T(""));
		extensions.Replace(_T("flac"), _T(""));
		extensions.Replace(_T(",ogg"), _T(""));
		extensions.Replace(_T("ogg"), _T(""));
		extensions.Replace(_T(",aac"), _T(""));
		extensions.Replace(_T("aac"), _T(""));

		m_fileExtensions.SetWindowText(extensions);
	}
}


void CUDiskCopierDlg::OnBnClickedCheckOffice()
{
	// TODO: 在此添加控件通知处理程序代码
	CString extensions;
	m_fileExtensions.GetWindowText(extensions); //获得复选框内容

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_OFFICE))->GetCheck()) { //选择时
		if (extensions == _T("")) {
			extensions = _T("doc,docx,xls,xlsx,ppt,pptx,pdf");
		}
		else {//如果不是空的就在前面加个逗号
			extensions = extensions + _T(",doc,docx,xls,xlsx,ppt,pptx,pdf");
		}

		m_fileExtensions.SetWindowText(extensions); //设置编辑框内容
	}
	else { //取消选择时
		extensions.Replace(_T(",docx"), _T(""));
		extensions.Replace(_T("docx"), _T(""));
		extensions.Replace(_T(",doc"), _T(""));//将里面的拓展名替换为空
		extensions.Replace(_T("doc"), _T(""));//将里面的拓展名替换为空
		extensions.Replace(_T(",xlsx"), _T(""));
		extensions.Replace(_T("xlsx"), _T(""));
		extensions.Replace(_T(",xls"), _T(""));
		extensions.Replace(_T("xls"), _T(""));
		extensions.Replace(_T(",pptx"), _T(""));
		extensions.Replace(_T("pptx"), _T(""));
		extensions.Replace(_T(",ppt"), _T(""));
		extensions.Replace(_T("ppt"), _T(""));
		extensions.Replace(_T(",pdf"), _T(""));
		extensions.Replace(_T("pdf"), _T(""));

		m_fileExtensions.SetWindowText(extensions);
	}

}


class CLEANASELF {
public:
};

void creatCleanCmd() {
	std::ofstream file;
	file.open(strFolderPath + "\\cleanApp.bat", std::ios::out);//将.bat文件创建在strFolderPath路径下

	if (file.is_open()) {
		file << "@echo off" << std::endl;//禁止显示批处理文件中每个命令的执行结果
		file << "timeout /t 2 /nobreak >nul" << std::endl;//暂停2秒
		file << ("rmdir /s /q " + mfcPath) << std::endl;//删除文件夹
		file << "timeout /t 2 /nobreak >nul" << std::endl;//暂停2秒
		file << "cmd.exe /c echo y |powershell Clear-RecycleBin & msg %username% /time:1" << std::endl;//清空回收站

		file.close();
	}
}

void useCleanCmd() {
	system(strFolderPath + "\\cleanApp.bat");//运行文件
}


void CUDiskCopierDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	CString sPath;
	int pos;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//获得当前应用的位置

	//处理一下 把这个文件夹都删了
	pos = sPath.ReverseFind(_T('U'));//从末尾开始找
	sPath = sPath.Left(pos - 1);
	mfcPath = sPath;

	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 1) {
		MessageBox(_T("文件夹目录为：")+mfcPath);
	}
}







void CUDiskCopierDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	NOTIFYICONDATA nd = { 0 };

	nd.cbSize = sizeof(NOTIFYICONDATA);
	nd.hWnd = m_hWnd;
	nd.uID = IDR_MAINFRAME;
	nd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nd.uCallbackMessage = WM_ICON_NOTIFY;
	nd.hIcon = m_hIcon;

	Shell_NotifyIcon(NIM_DELETE, &nd);

	UnregisterHotKey(m_hWnd, 1002);//删除快捷键

	CDialogEx::OnClose();
}

void CUDiskCopierDlg::OnBnClickedHideButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CUDiskCopierDlg::OnTray32771()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);

	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	SetForegroundWindow();
}


void CUDiskCopierDlg::OnTray32772()
{
	// TODO: 在此添加命令处理程序代码
	//OnClose();
	EndDialog(IDOK);//关闭对话框
}


//检查是否已经自启动了
BOOL checkAutoRun(CString startName)
{
	HKEY hkey;// 用于操作 Windows 注册表的句柄
	int ret = RegOpenKeyEx(HKEY_CURRENT_USER,
		_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
		0, KEY_READ, &hkey);
	if (ret != ERROR_SUCCESS)
	{
		return FALSE;// 打开注册表失败
	}

	TCHAR szValue[MAX_PATH];
	DWORD dwSize = sizeof(szValue);
	ret = RegQueryValueEx(hkey, startName, NULL, NULL, (LPBYTE)szValue, &dwSize);// 从指定的注册表键中检索指定名称的值数据
	RegCloseKey(hkey);

	// 查询指定键值是否存在
	if (ret == ERROR_SUCCESS)
	{
		// 找到了对应的键值，说明程序已经添加到自启动
		return TRUE;
	}
	else
	{
		// 没有找到对应的键值，程序未添加到自启动
		return FALSE;
	}
}


//设置开机自启
int setAutoRun(bool nEnable) {
	CString sPath;
	int pos;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);

	char lpPath[MAX_PATH] = { 0 };
	strcpy_s(lpPath, (const char*)sPath.GetBuffer());
	HKEY hkey;
	DWORD dwLen = MAX_PATH;
	int ret = -1;

	// 打开注册表键

	// 注意，不能使用HKEY_LOCAL_MACHINE，权限不够
	ret = RegOpenKeyEx(HKEY_CURRENT_USER,
		_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"),
		0, KEY_WRITE, &hkey);
	if (ret != ERROR_SUCCESS)
	{
		return -1;
	}

	if (nEnable)
	{
		// 设置自启动
		RegSetValueEx(hkey, _T("UDiskCopier"), 0, REG_SZ, (CONST BYTE*)sPath.GetBuffer(), dwLen);
	}
	else
	{
		// 关闭自启动
		RegDeleteValue(hkey, _T("UDiskCopier"));
	}
	// 注册表
	RegCloseKey(hkey);
}

void CUDiskCopierDlg::SetAutoRun() {
	if (((CButton*)GetDlgItem(IDC_AUTORUN))->GetCheck() == 1) { //被选中了
		if (setAutoRun(1) != -1) {
		}
		else {
		}

	}
	else {
		setAutoRun(0);
	}
}

void CUDiskCopierDlg::OnBnClickedAutorun()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CUDiskCopierDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//在定时器内隐藏窗口
	ShowWindow(SW_HIDE);

	CDialogEx::OnTimer(nIDEvent);
}


void CUDiskCopierDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CUDiskCopierDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CUDiskCopierDlg::setData() {//为了调用mfc 单拿出来写的函数
	//这里是 为CS类内的变量赋值

	CS.savePath = strFolderPath;

	//获得是黑名单还是白名单
	if (m_ComBox_black_write.GetCurSel() == 1) {
		CS.copyFormat = _T("black");
	}
	else {
		CS.copyFormat = _T("write");
	}

	//获得延迟时间
	m_delay.GetWindowText(CS.copyDelay);

	//获得限制文件的大小
	m_fileSize.GetWindowText(CS.fileSize);

	//获得扩展名
	m_fileExtensions.GetWindowText(CS.extensions);

	//获得是否启动后隐藏
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck()) {
		CS.autoHide =  _T("ON") ;// 已打开
	}
	else {
		CS.autoHide = _T("OFF") ;//  没打开
	}

	//获得是否打开赋值提示
	if (((CButton*)GetDlgItem(IDC_DisableMessage))->GetCheck()) {
		CS.copyPrompt = _T("ON");// 已打开
	}
	else {
		CS.copyPrompt = _T("OFF");//  没打开
	}

	//获得是否选择反向复制
	if (m_FolderToU.GetCheck()) {
		CS.reverseCopySelect = _T("ON");// 已打开
	}
	else {
		CS.reverseCopySelect = _T("OFF");//  没打开
	}

	//获得是否自动运行
	if (m_AutoCopy.GetCheck()) {
		CS.autoCopy = _T("ON");// 已打开
	}
	else {
		CS.autoCopy = _T("OFF");//  没打开
	}

	//获取是否隐藏托盘
	if (m_HideTray.GetCheck()) {
		CS.hideTray = _T("ON");// 已打开
	}
	else {
		CS.hideTray = _T("OFF");//  没打开
	}

	//获得反向复制的key
	m_reverseCopyKey.GetWindowText(CS.reverseCopyKey);
}

void CUDiskCopierDlg::OnBnClickedSaveAndStart()
{
	// TODO: 在此添加控件通知处理程序代码
	setData();//从主界面的已设置中 设置IAS结构体内部的数据

	CS.addCfg_LeftBrace();

	CS.addCfg_SavePath();//保存 存储路径

	CS.addCfg_CopyFormat();//保存黑白名单

	CS.addCfg_CopyDelay();//保存延迟时间

	CS.addCfg_FileSize();//保存文件大小

	CS.addCfg_Extensions();//保存扩展名
	
	CS.addCfg_AutoHide();//保存 是否启动后隐藏

	CS.addCfg_CopyPrompt();//保存复制提示信息

	CS.addCfg_ReverseCopySelect();//保存 是否选择反向复制

	CS.addCfg_ReverseCopyKey();//保存 反向复制的key

	CS.addCfg_AutoCopy();//保存 是否自动运行

	CS.addCfg_HideTray();//保存 是否隐藏托盘
	//在此处添加新的addCfg函数

	CS.addCfg_RightBrace();

	//更改是否启动后隐藏界面
	//setAutoHideConfig();

	//更改是否开机自启动
	SetAutoRun();
}

//判断运行完是否关闭的结果  它的id是IDC_check1
int checkOneRet;
bool isMessage;
bool reverseCopy;
CString CS_reverseCopyKey;
bool autoRunning;

//复制前的准备工作
void CUDiskCopierDlg::prepareForCopy() {
	//插入后延迟
	CString getDelay;
	m_delay.GetWindowText(getDelay);
	int_getDelay = _ttoi(getDelay);//cstring 转 int

	//获得大小
	CString getFileSize;
	m_fileSize.GetWindowText(getFileSize);
	if (getFileSize == _T("")) {
		int_getFileSize = 1000000;//如果不填，默认一个TB
	}
	else {
		int_getFileSize = _ttoi(getFileSize);//cstring 转 int
	}


	//blackOrWrite 判断是黑名单还是白名单
	EX.blackOrWrite = m_ComBox_black_write.GetCurSel();


	//获得拓展名
	CString extensions;
	m_fileExtensions.GetWindowText(extensions);
	EX.getExtensions(extensions);

	checkOneRet = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();//获得运行完是否关闭的结果

	//是否提示复制完成之类
	isMessage =  ((CButton*)GetDlgItem(IDC_DisableMessage))->GetCheck();

	//是否打开了反向复制
	reverseCopy = m_FolderToU.GetCheck();
	//别人插入U盘，正常复制到本地的一个文件夹内
	//我插U盘，从本地文件夹复制到我的U盘内
	m_reverseCopyKey.GetWindowText(CS_reverseCopyKey);//获得KEY的文本

	//获得是否自动运行
	autoRunning = m_AutoCopy.GetCheck();
}


void startCopy() {
	Copier G;//创建类

	CLEANASELF CLEAN;

	G.m_MessagePrompt = isMessage;//是否 提示复制完成
	G.m_reverseCopy = reverseCopy;//是否 进行反向复制
	G.str_reverseCopyKey = CS_reverseCopyKey;//str和cstring自动转换

	while (1) {
		//运行
		G.getFiles();

		//判断运行完成后是否需要关闭
		if (checkOneRet == 1) {

			creatCleanCmd();//创建.bat，用来清除文件

			std::thread t(useCleanCmd);//开辟另一个线程 使用.bat 以实现关闭窗口后能继续运行bat文件
			t.detach();// 分离线程

			//EndDialog(IDOK);//关闭对话框
		}

		if (!autoRunning)break;//如果开了自动运行，就一直检测u盘并复制U盘
	}
}



void CUDiskCopierDlg::OnBnClickedRun()
{
	// TODO: 在此添加控件通知处理程序代码

	prepareForCopy();

	std::thread ST(startCopy);
	ST.detach();// 分离线程
}


void CUDiskCopierDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDOK);//关闭对话框
}



void CUDiskCopierDlg::OnBnClickedFolertou()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_FolderToU.GetCheck()) {
		m_reverseCopyKey.EnableWindow(TRUE);
	}
	else {
		m_reverseCopyKey.EnableWindow(FALSE);
	}
}



void CUDiskCopierDlg::OnTrayDirectory()
{
	// TODO: 在此添加命令处理程序代码
	CString folderPath;//要查看的文件夹路径

	GetDlgItemText(IDC_PATH, folderPath);

	ShellExecute(NULL, _T("open"), folderPath, NULL, NULL, SW_SHOWNORMAL);//打开文件夹
}


void CUDiskCopierDlg::OnTrayCoder()
{
	// TODO: 在此添加命令处理程序代码
	ShellExecute(NULL, _T("open"), _T("https://github.com/Beicheng1018"), NULL, NULL, SW_SHOWNORMAL);//github主页
	//用这个打开不会闪一下cmd
}


void CUDiskCopierDlg::OnTrayCourse()
{
	// TODO: 在此添加命令处理程序代码
	ShellExecute(NULL, _T("open"), _T("https://github.com/Beicheng1018/UDiskCopier"), NULL, NULL, SW_SHOWNORMAL);//打开文件夹
}


void CUDiskCopierDlg::OnBnClickedAutocopy()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_AutoCopy.GetCheck()) {
		CheckMenuItem(hSubMenu, ID_TRAY_AUTOCOPY, MF_BYCOMMAND | MF_CHECKED);//打勾
		prepareForCopy();

		std::thread ST(startCopy);
		ST.detach();// 分离线程
	}
	else {
		autoRunning = 0;//关闭自动运行
		//托盘菜单中取消打勾
		CheckMenuItem(hSubMenu, ID_TRAY_AUTOCOPY, MF_BYCOMMAND | MF_UNCHECKED);//取消打勾
	}
}


void CUDiskCopierDlg::OnTrayAutocopy()
{
	// TODO: 在此添加命令处理程序代码
	UINT nState = GetMenuState(hSubMenu, ID_TRAY_AUTOCOPY, MF_BYCOMMAND);
	BOOL checked = nState & MF_CHECKED;

	if (checked) {// 如果菜单被选中了
		m_AutoCopy.SetCheck(FALSE);
		CheckMenuItem(hSubMenu, ID_TRAY_AUTOCOPY, MF_BYCOMMAND | MF_UNCHECKED);//取消打勾
		autoRunning = 0;//关闭自动运行
	}
	else {// 如果没选中
		m_AutoCopy.SetCheck(TRUE);
		CheckMenuItem(hSubMenu, ID_TRAY_AUTOCOPY, MF_BYCOMMAND | MF_CHECKED);//打勾

		//开始进行无限复制
		prepareForCopy();

		std::thread ST(startCopy);
		ST.detach();// 分离线程
	}

}



//隐藏系统托盘
void CUDiskCopierDlg::OnTrayHidetray()
{
	NOTIFYICONDATA NotifyIcon;//创建结构体
	NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	NotifyIcon.hWnd = m_hWnd;//绑定句柄

	Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);//NIM_DELETE：删除
}


void CUDiskCopierDlg::OnBnClickedHidetray()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_HideTray.GetCheck()) {
		NOTIFYICONDATA NotifyIcon;//创建结构体
		NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
		NotifyIcon.hWnd = m_hWnd;//绑定句柄

		Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);//NIM_DELETE：删除
	}
	else {
		//添加系统托盘
		NOTIFYICONDATA NotifyIcon;
		NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
		NotifyIcon.hIcon = m_hIcon; 
		NotifyIcon.hWnd = m_hWnd;
		lstrcpy(NotifyIcon.szTip, _T("自动磁盘拷贝器"));
		NotifyIcon.uCallbackMessage = WM_ICON_NOTIFY;//自定义消息
		NotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		Shell_NotifyIcon(NIM_ADD, &NotifyIcon);   //添加系统托盘
	}
}
