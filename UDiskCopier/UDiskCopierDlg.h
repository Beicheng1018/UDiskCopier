
// UDiskCopierDlg.h: 头文件
//

#pragma once

#define WM_USER_SHELLICON (WM_USER + 1)

// CUDiskCopierDlg 对话框
class CUDiskCopierDlg : public CDialogEx
{
// 构造
public:
	CUDiskCopierDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UDISKCOPIER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangePath();
	afx_msg void OnBnClickedShowfile();
	afx_msg void OnBnClickedSaveAndStart();
	CComboBox m_ComBox_black_write;
	CEdit m_fileExtensions;
	afx_msg void OnBnClickedCheckPicture();
	afx_msg void OnBnClickedCheckVideo();
	afx_msg void OnBnClickedCheckAudio();
	afx_msg void OnBnClickedCheckOffice();
	CEdit m_delay;
	CEdit m_fileSize;
	//afx_msg void OnEnChangeEdit2();
	//afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedHideButton();
	afx_msg void OnClose();
	afx_msg void OnTray32771();
	afx_msg void OnTray32772();
	
	//afx_msg void OnBnClickedCheck2();
	CButton autoRun;
	afx_msg void OnBnClickedsetautorun();
	afx_msg void OnBnClickedAutorun();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton4();

	void setAutoHideConfig();
	void SetAutoRun();
	afx_msg void OnBnClickedRun();
	void setData();
	void initAll();
	void prepareForCopy();
	CButton m_FolderToU;
	CEdit m_reverseCopyKey;
	afx_msg void OnBnClickedFolertou();
	afx_msg void OnBnClickedAutoscopy();
	CButton m_AutoCopy;
};

