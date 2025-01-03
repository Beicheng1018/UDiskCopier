#include "pch.h"
#include "ConfigSaver.h"


//���ڴ�������ļ����ַ���(�ܳ�)
std::string config;


//InitAndSave���ڵĶ���
void ConfigSaver::addCfg_LeftBrace() {// ���ļ���ʼ��ӻ�����
	std::ofstream ofs;
	ofs.open("config.txt", std::ios::out);//��ֻд��ʽ�� ��ʵ������ļ�
	ofs << "{";
	ofs.close();
}

//��׷����ʽ�����ļ�������
void addAnything_app(CString filePath, CString content) {
	std::ofstream ofs;
	ofs.open(filePath, std::ios::app);//��׷����ʽ��
	ofs << content;
	ofs.close();
}

void ConfigSaver::addCfg_RightBrace() {// ���ļ�ĩβ��ӻ�����
	addAnything_app(_T("config.txt"), _T("}"));
}
void ConfigSaver::addCfg_SavePath() {//�������ļ��б���·��
	CString tempContent;
	tempContent.Format(_T("\"savePath\":\"%s\""), savePath);//��ʽ��Ϊ��Ҫ������--·��
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_CopyFormat() {//������������ǰ�����
	CString tempContent;
	tempContent.Format(_T(",\"copyFormat\":\"%s\""), copyFormat);
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_CopyDelay() {
	CString tempContent;
	tempContent.Format(_T(",\"copyDelay\":\"%s\""), copyDelay);
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_FileSize() {
	CString tempContent;
	tempContent.Format(_T(",\"fileSize\":\"%s\""), fileSize);
	addAnything_app(_T("config.txt"), tempContent);
}


void ConfigSaver::addCfg_Extensions() {
	CString tempContent;
	tempContent.Format(_T(",\"extensions\":\"%s\""), extensions);
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_AutoHide() {
	CString tempContent;
	tempContent.Format(_T(",\"autoHide\":\"%s\""), autoHide);
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_CopyPrompt() {
	CString tempContent;
	tempContent.Format(_T(",\"copyPrompt\":\"%s\""), copyPrompt);
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_ReverseCopySelect() {
	CString tempContent;
	tempContent.Format(_T(",\"reverseCopySelect\":\"%s\""), reverseCopySelect);
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_ReverseCopyKey() {
	CString tempContent;
	tempContent.Format(_T(",\"reverseCopyKey\":\"%s\""), reverseCopyKey);
	addAnything_app(_T("config.txt"), tempContent);
}


void ConfigSaver::InitConfig() {
	std::ifstream ifs;
	ifs.open("config.txt", std::ios::in);

	std::string tempConfig;
	while (getline(ifs, tempConfig))//getline��string��ȫ�ֺ���
	{
		config += tempConfig;
	}
}
