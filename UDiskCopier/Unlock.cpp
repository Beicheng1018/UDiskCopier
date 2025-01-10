// Unlock.cpp: 实现文件
//

#include "pch.h"
#include "UDiskCopier.h"
#include "afxdialogex.h"
#include "Unlock.h"

//来自主页面的unlockPassword
extern CString unlockPassword;

// Unlock 对话框

IMPLEMENT_DYNAMIC(Unlock, CDialogEx)

Unlock::Unlock(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNLOCK, pParent)
{

}

Unlock::~Unlock()
{
}

void Unlock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_password);
}


BEGIN_MESSAGE_MAP(Unlock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Unlock::OnBnClickedButton1)
END_MESSAGE_MAP()


// Unlock 消息处理程序


void Unlock::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString inputPassword;
	m_password.GetWindowText(inputPassword);
	if (inputPassword == unlockPassword) {
		//关闭解锁页面
		CDialogEx::OnOK();
		//打开主页面
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
		//关闭某个可能存在的定时器
		KillTimer(1);
	}
	else {
		MessageBox(_T("密码错误"), _T("提示"),MB_OK| MB_ICONEXCLAMATION);
	}
	
}
