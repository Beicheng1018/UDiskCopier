#include "pch.h"
#include "Copier.h"
#include "Extension.h"// ��չ����Ӧ����

//��ʼ���� ��չ��
extern Extension EX;
CString strFolderPath;
int int_getFileSize;
int int_getDelay;

//�����Ǹ��ؼ����ļ�������о�����������
bool Copier::checkKeyFile(LPCTSTR path, LPCTSTR type) {

	std::string key = str_reverseCopyKey;//��˭

	WIN32_FIND_DATA findData;
	TCHAR fullPath[MAX_PATH] = { 0 };//����·��
	_stprintf(fullPath, _T("%s\\%s"), path, type);//��ʽ����һ��������·��

	HANDLE hFind = FindFirstFile(fullPath, &findData);//���ҵ�һ���ļ�

	if (hFind == INVALID_HANDLE_VALUE) {//û���ļ���ֱ�ӷ���
		//cout << "cant find file." << endl;
		return 0;
	}

	while (1) {
		//�����½�WIN32_FIND_DATA
		WIN32_FIND_DATA tempFindData;
		int ret = FindNextFile(hFind, &tempFindData);
		if (ret == 0) {//�ڱ����������ļ���ret��Ϊ0
			break;
		}
		std::string fileName = tempFindData.cFileName;
		if (fileName.find(key) != std::string::npos) {//���if���治ִ�и�ֵ�������䣬��ֱ������
			return 1;//�ҵ��� ������
		}
	}
	return 0;
}


//���༭���ڵ�·�����ص�����
void Copier::initPATH() {
	PATH = strFolderPath;
}

//�����ļ���
void Copier::creatDir(LPCTSTR path) {
	bool ret = CreateDirectory(path, NULL);
}

//�����ļ���ĳ���ļ���(·��)
void Copier::copyFile(LPCTSTR path, LPCTSTR newPath) {
	bool bRet = CopyFile(path, newPath, true);
}


// �����ļ���С ���ص�λ��MB
double Copier::calFileSize(WIN32_FIND_DATAA tempFindData) {
	LARGE_INTEGER fileSize;//�ļ���С
	fileSize.LowPart = tempFindData.nFileSizeLow;//��λ
	fileSize.HighPart = tempFindData.nFileSizeHigh;//��λ
	//��λ�͸�λ�ϳ�һ���ܵ�
	return (static_cast<double>(fileSize.QuadPart) / 1024) / 1024;//fileSize.QuadPart���ֽ�
	//MessageBox(NULL, _T("��⵽U�̲���"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
}


//����ָ��·���µ��ļ��������ļ�
bool Copier::findfile(LPCTSTR path, LPCTSTR type) {
	//��ظ�Ϊʹ�ö��ַ���

	WIN32_FIND_DATA findData;
	TCHAR fullPath[MAX_PATH] = { 0 };//����·��
	_stprintf(fullPath, _T("%s\\%s"), path, type);//��ʽ����һ��������·��

	HANDLE hFind = FindFirstFile(fullPath, &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		//cout << "cant find file." << endl;
		return 0;
	}

	while (1) {
		//�����½�WIN32_FIND_DATA
		WIN32_FIND_DATA tempFindData;
		int ret = FindNextFile(hFind, &tempFindData);

		if (ret == 0) {//�ڱ����������ļ���ret��Ϊ0
			break;
		}


		if (tempFindData.cFileName[0] != '.') {//.�ļ��ǵ�ǰĿ¼  ..�ļ���ָ�����ϲ�Ŀ¼

			if (tempFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {//ATTRIBUTE:����
				//�����ļ���С������
				double retFileSize = calFileSize(tempFindData);
				if (int_getFileSize <= retFileSize) {
					continue;//���β�����
				}

				//cout << "�����ļ���:";
				//cout << tempFindData.cFileName << endl;//��ӡ�ļ���
				//cout << "------------------------" << endl;//��ӡ�ָ���


				//�ϳɿ������ڿ������ļ�·��
				TCHAR thisPath[MAX_PATH] = { 0 };
				std::string eraseEPath;//����ɾ���������ַ���

				_stprintf(thisPath, _T("%s\\%s"), path, tempFindData.cFileName);//��ʽ��
				//cout << "�����ļ���" << thisPath << endl;

				eraseEPath = thisPath;

				//stringstream���Խ����ⶫ��תΪ�ַ���
				std::stringstream ss;
				ss << m_findPath;//��drivePathתΪ�ַ���
				std::string deleteContent;//ɾ������
				ss >> deleteContent;
				deleteContent = deleteContent + "\\";//�ڴ������ƺ������:\\

				eraseEPath.erase(eraseEPath.find(deleteContent), deleteContent.size());


				//�ڱ���Ҳ������Ӧ���ļ���
				TCHAR dirPath[MAX_PATH] = { 0 };
				_stprintf(dirPath, _T("%s\\%s"), PATH, eraseEPath.c_str());//�ϳ����ڴ��������ļ��е�·��

				creatDir(dirPath);//���ô��������ڱ��ش������ļ���

				//TCHAR szPath[MAX_PATH] = { 0 };
				_stprintf(dirPath, _T("%s\\%s"), path, tempFindData.cFileName);//�ϳ����ڱ����ļ��е�·��

				findfile(dirPath, _T("*.*"));//�����µ�·�� 
				//������������������ļ��е�����
			}
			else {
				std::string FileName = tempFindData.cFileName;//�õ��ļ��������׺(��ʽ)
				//string FileName = wideCharToMultiByte(tempFindData.cFileName);//�������ʹ��unicode�ַ���ʱʹ��

				//cout << "�ļ���:";
				//cout << tempFindData.cFileName << endl;

				//��if��������Ҫ���ض���ʽ���ļ�
				if (EX.checkExtension(FileName)) {
					//�ϳɿ������ڿ������ļ�·��
					TCHAR thisPath[MAX_PATH] = { 0 };
					_stprintf(thisPath, _T("%s\\%s"), path, tempFindData.cFileName);//��ʽ��
					//cout << "�����ļ�" << thisPath << endl;

					//ɾ��ǰ��Ĵ������ƣ�E:\\�����ںϳ��µ��ļ���·��
					std::string eraseEPath = thisPath;

					//stringstream���Խ����ⶫ��תΪ�ַ���
					std::stringstream ss;
					ss << m_findPath;//��drivePathתΪ�ַ���
					std::string deleteContent;//ɾ������
					ss >> deleteContent;
					deleteContent = deleteContent + "\\";//�ڴ������ƺ������:\\

					eraseEPath.erase(eraseEPath.find(deleteContent), deleteContent.size());
					//��������ļ�������ô��eraseEPath��Ϊ��


					//�ϳɴ��ļ��еı���·��
					TCHAR addDirNamePath[MAX_PATH] = { 0 };
					_stprintf(addDirNamePath, _T("%s\\%s"), PATH, eraseEPath.c_str());
					copyFile(thisPath, addDirNamePath);
					//��һ����ԭ�ļ���·�����ڶ����Ǹõ����������洢��·������������ֱ�Ӱ�ԭ����·���������ù�����
				}

			}

		}

	}

	FindClose(hFind);//�ر��ļ�

	return 1;
}



void Copier::getDrives() {
	TCHAR TDrives[MAX_PATH] = { 0 };
	int key = 0;//���û������3�Ͳ�����


	while (key != 2) {
		//��ȡ���д���
		GetLogicalDriveStrings(MAX_PATH, TDrives);

		TCHAR* signal = TDrives;
		while (*signal) {//�õ�����
			if (GetDriveType(signal) == 2) {
				key = GetDriveType(signal);
				//cout << "��⵽U�̲���" << endl;
				if (m_MessagePrompt) {//�Ƿ���ʾu�̲���
					MessageBox(NULL, _T("��⵽U�̲���"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
				}
				Sleep(int_getDelay * 1000);
				drivePath = *signal;
			}
			else {
				//cout << "���ڼ��..." << endl;
				Sleep(250);
				//system("cls");
			}
			signal += 1 + _tcslen(signal);
		}
		//cout << "û��U�̲���" << endl;

		Sleep(250);
		//system("cls");
	}

}

void Copier::swapTwo(LPCTSTR fullPath) {//��ת����·��
	m_findPath = PATH;//����·���л���ԭ����·����

	PATH = fullPath;//����·���л���u����
}


void Copier::getFiles() {
	initPATH();//��ʼ��·��
	getDrives();
	TCHAR fullPath[MAX_PATH] = { 0 };//����·��
	_stprintf(fullPath, _T("%c:"), drivePath);//��ʽ��

	if (m_reverseCopy && checkKeyFile(fullPath, _T("*.*")) == 1) {//��ѡ�����ƣ�������key�ļ�
		swapTwo(fullPath);//���������ʵ�ַ������
	}
	else {
		m_findPath= fullPath;//û�з����������������
	}
	
	findfile(m_findPath, _T("*.*"));

	if (m_MessagePrompt) {//�Ƿ���ʾ�������
		MessageBox(NULL, _T("����ɿ���"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
	}
}
