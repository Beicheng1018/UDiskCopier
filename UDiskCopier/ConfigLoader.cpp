#include "pch.h"
#include "ConfigLoader.h"

extern std::string config;

//�������ļ��в�����Ӧ����
CString ConfigLoader::myFind(CString findContent) {
	int startPos = init_config.Find(findContent);//��ʼλ��
	int endPos = startPos + findContent.GetLength() + 2;//����1�Ļ������Ƿֺŵ�λ�� Ϊ�˿�Խ�ֺ�+1 Ϊ�˿�Խð����+1
	int strEndPos = init_config.Find(_T("\""), endPos);//�� findContent����һ��λ�� ��ʼ�� ֱ����һ�� "
	return init_config.Mid(endPos, strEndPos - endPos);
}

//�����ļ� ������
void ConfigLoader::parseConfig() {
	init_config = config.c_str();//תΪCString

	init_savePath = getInit_savePath();//��ʼ������·��

	init_copyFormat = getInit_copyFormat();//��ʼ�����������ǰ�����

	init_fileSize = getInit_fileSize();

	init_copyDelay = getInit_copyDelay();

	init_extensions = getInit_extensions();

	init_autoHide = getInit_autoHide();

	init_copyPrompt = getInit_copyPrompt();

	init_reverseCopySelect = getInit_reverseCopySelect();

	init_reverseCopyKey = getInit_reverseCopyKey();

	init_autoCopy = getInit_autoCopy();

	init_hideTray = getInit_hideTray();
	//�ڴ˴�����µ�CL�������ݳ�ʼ��

}

//��ʼ������·��
CString ConfigLoader::getInit_savePath() {
	return myFind("\"savePath\"");
}

//��ʼ�����������ǰ�����
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