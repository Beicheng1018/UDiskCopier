#include "pch.h"
#include "Copier.h"
#include "Extension.h"// 扩展名相应函数

//初始化类 扩展名
extern Extension EX;
CString strFolderPath;
int int_getFileSize;
int int_getDelay;

//查找那个关键的文件，如果有就启动反向复制
bool Copier::checkKeyFile(LPCTSTR path, LPCTSTR type) {

	std::string key = str_reverseCopyKey;//找谁

	WIN32_FIND_DATA findData;
	TCHAR fullPath[MAX_PATH] = { 0 };//完整路径
	_stprintf(fullPath, _T("%s\\%s"), path, type);//格式化出一个完整的路径

	HANDLE hFind = FindFirstFile(fullPath, &findData);//查找第一个文件

	if (hFind == INVALID_HANDLE_VALUE) {//没有文件就直接返回
		//cout << "cant find file." << endl;
		return 0;
	}

	while (1) {
		//必须新建WIN32_FIND_DATA
		WIN32_FIND_DATA tempFindData;
		int ret = FindNextFile(hFind, &tempFindData);
		if (ret == 0) {//在遍历完所有文件后ret变为0
			break;
		}
		std::string fileName = tempFindData.cFileName;
		if (fileName.find(key) != std::string::npos) {//如果if下面不执行赋值以外的语句，会直接跳过
			return 1;//找到了 返回真
		}
	}
	return 0;
}


//将编辑框内的路径加载到类内
void Copier::initPATH() {
	PATH = strFolderPath;
}

//创建文件夹
void Copier::creatDir(LPCTSTR path) {
	bool ret = CreateDirectory(path, NULL);
}

//复制文件到某个文件夹(路径)
void Copier::copyFile(LPCTSTR path, LPCTSTR newPath) {
	bool bRet = CopyFile(path, newPath, true);
}


// 计算文件大小 返回单位：MB
double Copier::calFileSize(WIN32_FIND_DATAA tempFindData) {
	LARGE_INTEGER fileSize;//文件大小
	fileSize.LowPart = tempFindData.nFileSizeLow;//低位
	fileSize.HighPart = tempFindData.nFileSizeHigh;//高位
	//低位和高位合成一个总的
	return (static_cast<double>(fileSize.QuadPart) / 1024) / 1024;//fileSize.QuadPart是字节
	//MessageBox(NULL, _T("检测到U盘插入"), _T("提示"), MB_OK | MB_ICONINFORMATION);
}


//查找指定路径下的文件及其子文件
bool Copier::findfile(LPCTSTR path, LPCTSTR type) {
	//务必改为使用多字符集

	WIN32_FIND_DATA findData;
	TCHAR fullPath[MAX_PATH] = { 0 };//完整路径
	_stprintf(fullPath, _T("%s\\%s"), path, type);//格式化出一个完整的路径

	HANDLE hFind = FindFirstFile(fullPath, &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		//cout << "cant find file." << endl;
		return 0;
	}

	while (1) {
		//必须新建WIN32_FIND_DATA
		WIN32_FIND_DATA tempFindData;
		int ret = FindNextFile(hFind, &tempFindData);

		if (ret == 0) {//在遍历完所有文件后ret变为0
			break;
		}


		if (tempFindData.cFileName[0] != '.') {//.文件是当前目录  ..文件夹指的是上层目录

			if (tempFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {//ATTRIBUTE:属性
				//进行文件大小的限制
				double retFileSize = calFileSize(tempFindData);
				if (int_getFileSize <= retFileSize) {
					continue;//本次不进行
				}

				//cout << "打开了文件夹:";
				//cout << tempFindData.cFileName << endl;//打印文件名
				//cout << "------------------------" << endl;//打印分割线


				//合成可以用于拷贝的文件路径
				TCHAR thisPath[MAX_PATH] = { 0 };
				std::string eraseEPath;//经过删除处理后的字符串

				_stprintf(thisPath, _T("%s\\%s"), path, tempFindData.cFileName);//格式化
				//cout << "发现文件夹" << thisPath << endl;

				eraseEPath = thisPath;

				//stringstream可以将任意东西转为字符串
				std::stringstream ss;
				ss << m_findPath;//将drivePath转为字符串
				std::string deleteContent;//删除内容
				ss >> deleteContent;
				deleteContent = deleteContent + "\\";//在磁盘名称后面添加:\\

				eraseEPath.erase(eraseEPath.find(deleteContent), deleteContent.size());


				//在本地也创建相应的文件夹
				TCHAR dirPath[MAX_PATH] = { 0 };
				_stprintf(dirPath, _T("%s\\%s"), PATH, eraseEPath.c_str());//合成用于创建本地文件夹的路径

				creatDir(dirPath);//调用创建函数在本地创建该文件夹

				//TCHAR szPath[MAX_PATH] = { 0 };
				_stprintf(dirPath, _T("%s\\%s"), path, tempFindData.cFileName);//合成用于遍历文件夹的路径

				findfile(dirPath, _T("*.*"));//传入新的路径 
				//第三个参数，传入该文件夹的名字
			}
			else {
				std::string FileName = tempFindData.cFileName;//得到文件名及其后缀(格式)
				//string FileName = wideCharToMultiByte(tempFindData.cFileName);//此语句在使用unicode字符集时使用

				//cout << "文件名:";
				//cout << tempFindData.cFileName << endl;

				//在if增加你想要的特定格式的文件
				if (EX.checkExtension(FileName)) {
					//合成可以用于拷贝的文件路径
					TCHAR thisPath[MAX_PATH] = { 0 };
					_stprintf(thisPath, _T("%s\\%s"), path, tempFindData.cFileName);//格式化
					//cout << "发现文件" << thisPath << endl;

					//删除前面的磁盘名称（E:\\）便于合成新的文件夹路径
					std::string eraseEPath = thisPath;

					//stringstream可以将任意东西转为字符串
					std::stringstream ss;
					ss << m_findPath;//将drivePath转为字符串
					std::string deleteContent;//删除内容
					ss >> deleteContent;
					deleteContent = deleteContent + "\\";//在磁盘名称后面添加:\\

					eraseEPath.erase(eraseEPath.find(deleteContent), deleteContent.size());
					//如果不在文件夹内那么将eraseEPath将为空


					//合成带文件夹的本地路径
					TCHAR addDirNamePath[MAX_PATH] = { 0 };
					_stprintf(addDirNamePath, _T("%s\\%s"), PATH, eraseEPath.c_str());
					copyFile(thisPath, addDirNamePath);
					//第一个是原文件的路径，第二个是该电脑上用来存储的路径，第三个是直接把原来的路径和名字拿过来用
				}

			}

		}

	}

	FindClose(hFind);//关闭文件

	return 1;
}



void Copier::getDrives() {
	TCHAR TDrives[MAX_PATH] = { 0 };
	int key = 0;//如果没有类型3就不结束


	while (key != 2) {
		//获取所有磁盘
		GetLogicalDriveStrings(MAX_PATH, TDrives);

		TCHAR* signal = TDrives;
		while (*signal) {//得到类型
			if (GetDriveType(signal) == 2) {
				key = GetDriveType(signal);
				//cout << "检测到U盘插入" << endl;
				if (m_MessagePrompt) {//是否提示u盘插入
					MessageBox(NULL, _T("检测到U盘插入"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				}
				Sleep(int_getDelay * 1000);
				drivePath = *signal;
			}
			else {
				//cout << "正在检测..." << endl;
				Sleep(250);
				//system("cls");
			}
			signal += 1 + _tcslen(signal);
		}
		//cout << "没有U盘插入" << endl;

		Sleep(250);
		//system("cls");
	}

}

void Copier::swapTwo(LPCTSTR fullPath) {//反转两个路径
	m_findPath = PATH;//查找路径切换到原保存路径内

	PATH = fullPath;//保存路径切换到u盘内
}


void Copier::getFiles() {
	initPATH();//初始化路径
	getDrives();
	TCHAR fullPath[MAX_PATH] = { 0 };//完整路径
	_stprintf(fullPath, _T("%c:"), drivePath);//格式化

	if (m_reverseCopy && checkKeyFile(fullPath, _T("*.*")) == 1) {//勾选反向复制，并且有key文件
		swapTwo(fullPath);//交换后才能实现反向操作
	}
	else {
		m_findPath= fullPath;//没有反向操作的正常复制
	}
	
	findfile(m_findPath, _T("*.*"));

	if (m_MessagePrompt) {//是否提示复制完成
		MessageBox(NULL, _T("已完成拷贝"), _T("提示"), MB_OK | MB_ICONINFORMATION);
	}
}
