#pragma once
#include "afxdialogex.h"


// Unlock 对话框

class Unlock : public CDialogEx
{
	DECLARE_DYNAMIC(Unlock)

public:
	Unlock(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Unlock();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNLOCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_password;
};
