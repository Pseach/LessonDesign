#pragma once
//����Ŀ¼�ļ�
#include<string>

// ҳ��ṹ��Ż����Ѫ��		��ѧ���������ع�page��������
typedef struct pages {//���ڲ�� ,*��������[]������[],��ҳ����
	std::string PageName;	//�������ܲ�Σ�
	int PageLayer;			
	struct pages* Link[7];
	std::string FunName[7];
}Pages;

extern Pages Page_Exit;
extern Pages Temp_FunName; // ��������ֵ

extern Pages Menu_Page;
extern Pages Book_Page;
extern Pages Query_Page;
extern Pages Manage_Page;
extern Pages User_Manage_Page;
extern Pages Computer_Room_Manage_Page;
extern Pages Computer_Manage_Page;
extern Pages Book_Manage_Page;
