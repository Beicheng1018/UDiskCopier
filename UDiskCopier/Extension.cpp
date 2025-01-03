#include "pch.h"
#include "Extension.h"



//�������������Ƿ����������չ��·��
bool Extension::checkExtension(std::string FileName) {
	if (blackOrWrite) {//������ģʽ
		for (std::string tempStr : extensionsArr) {// ��������
			if (FileName.find(tempStr) != std::string::npos) {// ����ҵ��ˣ�������npos
				return 0;// �ҵ��� ����1
			}
		}
		return 1;// û�ҵ� ����0
	}
	else {//������ģʽ
		for (std::string tempStr : extensionsArr) {// ��������
			if (FileName.find(tempStr) != std::string::npos) {// ����ҵ��ˣ�������npos
				return 1;// �ҵ��� ����1
			}
		}
		return 0;// û�ҵ� ����0
	}
}


//���༭���ڵ���չ����ӵ�������
void Extension::getExtensionsArr(std::string extensionsStr) {

	//��ĩβ���һ������
	extensionsStr = extensionsStr + ",";

	int l_pos = 0;
	int r_pos = 0;//λ��

	extensionsArr.resize(0);//�����ȫ����չ������

	while (1) {//�Ҳ���ʱ����ѭ��
		r_pos = extensionsStr.find(",", r_pos);//��pos�Ժ���Ҷ���
		if (r_pos == -1 || extensionsStr == ",")break;//���ֻ����һ������Ҳ����

		//���ָ����Χ���ִ�
		std::string tempStr = extensionsStr.substr(l_pos, r_pos - l_pos);
		//���д���ǰ���. �����\0
		tempStr = "." + tempStr;
		tempStr = tempStr + "\0";

		//��ȫ�ֱ�������չ�����������
		extensionsArr.push_back(tempStr);//��ӵ�����

		r_pos++;
		l_pos = r_pos;//��ָ���ƶ�
	}

}

//��cstringתΪstring
void Extension::getExtensions(CString CStr_extensions) {

	std::string extensionsStr;//��ʱstr

	extensionsStr = CT2A(CStr_extensions);//��cstringתΪstring

	getExtensionsArr(extensionsStr);//���ַ���תΪ����

}
