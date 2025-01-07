#pragma once
#include<string>
#include<vector>
#include <cstring>
#include<fstream>


//通过此类的函数，可以将全局变量的内容 按照一定格式写入到配置文件中
class ConfigSaver {
public:
	CString savePath;//保存路径
	CString copyFormat;//复制格式 黑名单or白名单
	CString fileSize;//限制文件大小
	CString copyDelay;//插入延迟
	CString extensions;//扩展名
	CString autoHide;//启动后自动隐藏
	CString copyPrompt;//复制提示
	CString reverseCopySelect;//选择反向复制
	CString reverseCopyKey;//反向复制的key
	CString autoCopy;//自动复制
	CString hideTray;//隐藏托盘

	void addCfg_LeftBrace();
	void addCfg_RightBrace();
	void addCfg_SavePath();
	void addCfg_CopyFormat();
	void addCfg_FileSize();
	void addCfg_CopyDelay();
	void addCfg_Extensions();
	void addCfg_AutoHide();
	void addCfg_CopyPrompt();
	void addCfg_ReverseCopySelect();
	void addCfg_ReverseCopyKey();
	void addCfg_AutoCopy();
	void addCfg_HideTray();

	void InitConfig();//初始化全局字符串变量config
};
