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

extern Page Page_Exit;
extern Page Temp_FunName; // ��������ֵ

extern Page Menu_Page;
extern Page Book_Page;
extern Page Query_Page;
extern Page Manage_Page;
extern Page User_Manage_Page;
extern Page Computer_Room_Manage_Page;
extern Page Computer_Manage_Page;

