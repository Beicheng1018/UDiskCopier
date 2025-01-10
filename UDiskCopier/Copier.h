#pragma once
#include<string>
#include<sstream>

//作用是将文件夹的内容拷贝回U盘
class Copier
{
private:
	CString PATH;//被拷贝过来的内容所在的文件夹  使用CString更安全，LPCTSTR可能会变
	CString reversePATH;//反向复制时用的
	LPCTSTR m_findPath;//可以是磁盘名，也可以是 保存路径
	TCHAR drivePath;//U盘名称 是E F 还是 G

public:
	bool m_reverseCopy;//是否打开了反向复制

	bool m_MessagePrompt;//布尔类型 是否提示复制完成

	std::string str_reverseCopyKey;//str类型的key

	void initPATH();//初始化PATH

	bool checkKeyFile(LPCTSTR path, LPCTSTR type);//查找那个关键的文件，如果有就启动反向复制

	void creatDir(LPCTSTR path); //创建文件夹

	void copyFile(LPCTSTR path, LPCTSTR newPath); //复制文件到某个文件夹(路径)

	double calFileSize(WIN32_FIND_DATAA tempFindData);// 计算文件大小 返回单位：MB

	bool findfile(LPCTSTR path, LPCTSTR type);// 查找指定路径下的文件及其子文件

	void getDrives();// 获得磁盘名称

	void getFiles();// 运行所有程序

	void swapTwo(LPCTSTR fullPath);

	void splitDir();//分文件复制
};

