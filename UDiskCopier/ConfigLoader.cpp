#include "pch.h"
#include "ConfigLoader.h"

extern std::string config;

//在配置文件中查找相应内容
CString ConfigLoader::myFind(CString findContent) {
	int startPos = init_config.Find(findContent);//开始位置
	int endPos = startPos + findContent.GetLength() + 2;//不加1的话正好是分号的位置 为了跨越分号+1 为了跨越冒号再+1
	int strEndPos = init_config.Find(_T("\""), endPos);//从 findContent的下一个位置 开始找 直到下一个 "
	return init_config.Mid(endPos, strEndPos - endPos);
}

//配置文件 解析器
void ConfigLoader::parseConfig() {
	init_config = config.c_str();//转为CString

	init_savePath = getInit_savePath();//初始化保存路径

	init_copyFormat = getInit_copyFormat();//初始化黑名单还是白名单

	init_fileSize = getInit_fileSize();

	init_copyDelay = getInit_copyDelay();

	init_extensions = getInit_extensions();

	init_autoHide = getInit_autoHide();

	init_copyPrompt = getInit_copyPrompt();

	init_reverseCopySelect = getInit_reverseCopySelect();

	init_reverseCopyKey = getInit_reverseCopyKey();

	init_autoCopy = getInit_autoCopy();

	init_hideTray = getInit_hideTray();
	//在此处添加新的CL类内数据初始化

}

//初始化保存路径
CString ConfigLoader::getInit_savePath() {
	return myFind("\"savePath\"");
}

//初始化黑名单还是白名单
CString ConfigLoader::getInit_copyFormat() {
	return myFind("\"copyFormat\"");
}

CString ConfigLoader::getInit_fileSize() {
	return myFind("\"fileSize\"");
}

CString ConfigLoader::getInit_copyDelay() {
	return myFind("\"copyDelay\"");
}

CString ConfigLoader::getInit_extensions() {
	return myFind("\"extensions\"");
}

CString ConfigLoader::getInit_autoHide() {
	return myFind("\"autoHide\"");
}

CString ConfigLoader::getInit_copyPrompt() {
	return myFind("\"copyPrompt\"");
}

CString ConfigLoader::getInit_reverseCopySelect() {
	return myFind("\"reverseCopySelect\"");
}

CString ConfigLoader::getInit_reverseCopyKey() {
	return myFind("\"reverseCopyKey\"");
}

CString ConfigLoader::getInit_autoCopy() {
	return myFind("\"autoCopy\"");
}

CString ConfigLoader::getInit_hideTray() {
	return myFind("\"hideTray\"");
}