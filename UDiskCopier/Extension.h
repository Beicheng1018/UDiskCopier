#pragma once
#include<string>
#include<vector>

class Extension
{
public:
	bool blackOrWrite = 0;//���������ǰ����� ��Ϊ1 ��Ϊ0

	std::vector<std::string>extensionsArr;//��չ������

	bool checkExtension(std::string FileName); //�������������Ƿ����������չ��·��

	void getExtensionsArr(std::string extensionsStr);//���༭���ڵ���չ����ӵ�������

	void getExtensions(CString CStr_extensions);//��cstringתΪstring ���뵽�����Ǹ�������
};

