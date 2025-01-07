#pragma once
#include<string>


//通过此类的函数可以将配置文件的内容读到全局变量
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
	CString getInit_savePath();//初始化保存路径
	CString getInit_copyFormat();//初始化黑名单还是白名单
	CString getInit_fileSize();//限制文件大小
	CString getInit_copyDelay();//延迟时间
	CString getInit_extensions();//扩展名
	CString getInit_autoHide();//自动隐藏
	CString getInit_copyPrompt();//自动隐藏
	CString getInit_reverseCopySelect();//是否反向复制
	CString getInit_reverseCopyKey();//反向复制的key
	CString getInit_autoCopy();//自动复制
	CString getInit_hideTray();//隐藏托盘
};
