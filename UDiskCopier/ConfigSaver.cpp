#include "pch.h"
#include "ConfigSaver.h"


//用于存放配置文件的字符串(很长)
std::string config;


//InitAndSave类内的定义
void ConfigSaver::addCfg_LeftBrace() {// 在文件开始添加花括号
	std::ofstream ofs;
	ofs.open("config.txt", std::ios::out);//以只写形式打开 以实现清空文件
	ofs << "{";
	ofs.close();
}

//以追加形式增加文件夹内容
void addAnything_app(CString filePath, CString content) {
	std::ofstream ofs;
	ofs.open(filePath, std::ios::app);//以追加形式打开
	ofs << content;
	ofs.close();
}

void ConfigSaver::addCfg_RightBrace() {// 在文件末尾添加花括号
	addAnything_app(_T("config.txt"), _T("}"));
}
void ConfigSaver::addCfg_SavePath() {//在配置文件中保存路径
	CString tempContent;
	tempContent.Format(_T("\"savePath\":\"%s\""), savePath);//格式化为想要的内容--路径
	addAnything_app(_T("config.txt"), tempContent);
}

void ConfigSaver::addCfg_CopyFormat() {//保存黑名单还是白名单
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
	while (getline(ifs, tempConfig))//getline是string的全局函数
	{
		config += tempConfig;
	}
}
