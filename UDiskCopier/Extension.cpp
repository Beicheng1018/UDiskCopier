#include "pch.h"
#include "Extension.h"



//检查这个名字里是否有数组的拓展名路径
bool Extension::checkExtension(std::string FileName) {
	if (blackOrWrite) {//黑名单模式
		for (std::string tempStr : extensionsArr) {// 遍历数组
			if (FileName.find(tempStr) != std::string::npos) {// 如果找到了，不等于npos
				return 0;// 找到了 返回1
			}
		}
		return 1;// 没找到 返回0
	}
	else {//白名单模式
		for (std::string tempStr : extensionsArr) {// 遍历数组
			if (FileName.find(tempStr) != std::string::npos) {// 如果找到了，不等于npos
				return 1;// 找到了 返回1
			}
		}
		return 0;// 没找到 返回0
	}
}


//将编辑框内的扩展名添加到数组中
void Extension::getExtensionsArr(std::string extensionsStr) {

	//在末尾添加一个逗号
	extensionsStr = extensionsStr + ",";

	int l_pos = 0;
	int r_pos = 0;//位置

	extensionsArr.resize(0);//先清空全局扩展名数组

	while (1) {//找不到时结束循环
		r_pos = extensionsStr.find(",", r_pos);//从pos以后查找逗号
		if (r_pos == -1 || extensionsStr == ",")break;//如果只等于一个逗号也返回

		//获得指定范围的字串
		std::string tempStr = extensionsStr.substr(l_pos, r_pos - l_pos);
		//进行处理，前面加. 后面加\0
		tempStr = "." + tempStr;
		tempStr = tempStr + "\0";

		//在全局变量的扩展名数组中添加
		extensionsArr.push_back(tempStr);//添加到数组

		r_pos++;
		l_pos = r_pos;//左指针移动
	}

}

//将cstring转为string
void Extension::getExtensions(CString CStr_extensions) {

	std::string extensionsStr;//临时str

	extensionsStr = CT2A(CStr_extensions);//将cstring转为string

	getExtensionsArr(extensionsStr);//将字符串转为数组

}
