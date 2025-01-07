#pragma once
#include<string>
#include<vector>
#include <cstring>
#include<fstream>


//ͨ������ĺ��������Խ�ȫ�ֱ��������� ����һ����ʽд�뵽�����ļ���
class ConfigSaver {
public:
	CString savePath;//����·��
	CString copyFormat;//���Ƹ�ʽ ������or������
	CString fileSize;//�����ļ���С
	CString copyDelay;//�����ӳ�
	CString extensions;//��չ��
	CString autoHide;//�������Զ�����
	CString copyPrompt;//������ʾ
	CString reverseCopySelect;//ѡ������
	CString reverseCopyKey;//�����Ƶ�key
	CString autoCopy;//�Զ�����
	CString hideTray;//��������

	void addCfg_LeftBrace();
	void addCfg_RightBrace();
	void addCfg_SavePath();
	void addCfg_CopyFormat();
	void addCfg_FileSize();
	void addCfg_CopyDelay();
	void addCfg_Extensions();
	void addCfg_AutoHide();
	void addCfg_CopyPrompt();
	void addCfg_ReverseCopySelect();
	void addCfg_ReverseCopyKey();
	void addCfg_AutoCopy();
	void addCfg_HideTray();

	void InitConfig();//��ʼ��ȫ���ַ�������config
};
