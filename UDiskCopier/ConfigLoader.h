#pragma once
#include<string>


//ͨ������ĺ������Խ������ļ������ݶ���ȫ�ֱ���
class ConfigLoader {
public:
	CString init_config;
	CString init_savePath;
	CString init_copyFormat;
	CString init_fileSize;
	CString init_copyDelay;
	CString init_extensions;
	CString init_autoHide;
	CString init_copyPrompt;
	CString init_reverseCopySelect;
	CString init_reverseCopyKey;
	CString init_autoCopy;
	CString init_hideTray;

	void parseConfig();
	CString myFind(CString findContent);
	CString getInit_savePath();//��ʼ������·��
	CString getInit_copyFormat();//��ʼ�����������ǰ�����
	CString getInit_fileSize();//�����ļ���С
	CString getInit_copyDelay();//�ӳ�ʱ��
	CString getInit_extensions();//��չ��
	CString getInit_autoHide();//�Զ�����
	CString getInit_copyPrompt();//�Զ�����
	CString getInit_reverseCopySelect();//�Ƿ�����
	CString getInit_reverseCopyKey();//�����Ƶ�key
	CString getInit_autoCopy();//�Զ�����
	CString getInit_hideTray();//��������
};
