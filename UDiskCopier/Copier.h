#pragma once
#include<string>
#include<sstream>

//�����ǽ��ļ��е����ݿ�����U��
class Copier
{
private:
	CString PATH;//�������������������ڵ��ļ���  ʹ��CString����ȫ��LPCTSTR���ܻ��
	CString reversePATH;//������ʱ�õ�
	LPCTSTR m_findPath;//�����Ǵ�������Ҳ������ ����·��
	TCHAR drivePath;//U������ ��E F ���� G

public:
	bool m_reverseCopy;//�Ƿ���˷�����

	bool m_MessagePrompt;//�������� �Ƿ���ʾ�������

	std::string str_reverseCopyKey;//str���͵�key

	void initPATH();//��ʼ��PATH

	bool checkKeyFile(LPCTSTR path, LPCTSTR type);//�����Ǹ��ؼ����ļ�������о�����������

	void creatDir(LPCTSTR path); //�����ļ���

	void copyFile(LPCTSTR path, LPCTSTR newPath); //�����ļ���ĳ���ļ���(·��)

	double calFileSize(WIN32_FIND_DATAA tempFindData);// �����ļ���С ���ص�λ��MB

	bool findfile(LPCTSTR path, LPCTSTR type);// ����ָ��·���µ��ļ��������ļ�

	void getDrives();// ��ô�������

	void getFiles();// �������г���

	void swapTwo(LPCTSTR fullPath);

	void splitDir();//���ļ�����
};

