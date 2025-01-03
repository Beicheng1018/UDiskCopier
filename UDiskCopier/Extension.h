#pragma once
#include<string>
#include<vector>

class Extension
{
public:
	bool blackOrWrite = 0;//黑名单还是白名单 黑为1 白为0

	std::vector<std::string>extensionsArr;//扩展名数组

	bool checkExtension(std::string FileName); //检查这个名字里是否有数组的拓展名路径

	void getExtensionsArr(std::string extensionsStr);//将编辑框内的扩展名添加到数组中

	void getExtensions(CString CStr_extensions);//将cstring转为string 传入到上面那个函数中
};

