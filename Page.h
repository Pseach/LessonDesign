#pragma once
//����Ŀ¼�ļ�
#include<string>
// ҳ��ṹ��Ż����Ѫ��
typedef struct pages {//���ڲ�� ,*��������[]������[],��ҳ����
	std::string PageName; //�������ܲ��
	int Page_Layer; 
	struct pages* Link[7];
	std::string FunName[7];
}Page;

extern Page Menu_Page;
extern Page Page_Exit;
extern Page Temp_FunName; // ��������ֵ