#include "Page.h"
#include "start.h"

Page Page_Exit = {};
Page Temp_FunName = {};

Page Book_Page = {
	"Ԥ��ϵͳ",1,
	{	&Page_Exit,				//[0]
		&Temp_FunName,		//[1]
		&Temp_FunName,		//[2]
		&Temp_FunName,		//[3]
		&Temp_FunName,		//[4]
		&Temp_FunName,		//[5]
		&Temp_FunName,		//[6]
	},
	{
	"��","Ԥ����λ","ȡ��Ԥ��","","","","",
	}
};

Page Query_Page = {
	"��ѯϵͳ",1,
	{	&Page_Exit,				//[0]
		&Temp_FunName,		//[1]
		&Temp_FunName,		//[2]
		&Temp_FunName,		//[3]
		&Temp_FunName,		//[4]
		&Temp_FunName,		//[5]
		&Temp_FunName,		//[6]
	},
	{
	"��","��λ��ѯ","������ѯ","�������","","","",
	}
};

	Page User_Manage = {
		"�˻�����",2,
		{	&Temp_FunName,		//[0]
			&Temp_FunName,		//[1]
			&Temp_FunName,		//[2]
			&Temp_FunName,		//[3]
			&Temp_FunName,		//[4]
			&Temp_FunName,		//[5]
			&Temp_FunName,		//[6]
		},
		{
		"","ɾ���˻�","�����˻�","����Ԥ������","","","",
		}
	};
	Page Computer_Room_Manage_Page = {
		"��������",2,
		{	&Temp_FunName,		//[0]
			&Temp_FunName,		//[1]
			&Temp_FunName,		//[2]
			&Temp_FunName,		//[3]
			&Temp_FunName,		//[4]
			&Temp_FunName,		//[5]
			&Temp_FunName,		//[6]
		},
		{
		"","���ӻ���","ɾ������","���Ļ���","���ػ���","","",
		}
	};
	Page Computer_Manage_Page = {
		"��λ����",2,
		{	& Temp_FunName,		//[0]
			& Temp_FunName,		//[1]
			& Temp_FunName,		//[2]
			& Temp_FunName,		//[3]
			& Temp_FunName,		//[4]
			& Temp_FunName,		//[5]
			& Temp_FunName,		//[6]
		},
		{
		"","���ӻ�λ","ɾ����λ","���Ļ�λ","���ػ�λ","","",
		}
	};
Page Manage_Page = {
	"����ϵͳ",1,
	{	& Page_Exit,						//[0]
		& User_Manage,						//[1]
		& Computer_Room_Manage_Page,		//[2]
		& Computer_Manage_Page,				//[3]
		& Temp_FunName,		//[4]
		& Temp_FunName,		//[5]
		& Temp_FunName,		//[6]
	},
	{
	"��","�˻�����ϵͳ","��������ϵͳ","��λ����ϵͳ","","","",
	}
};

Page Menu_Page = {
	"�˵�",1,
	{	& Page_Exit,				//[0]
		& Temp_FunName,		//[1]
		& Temp_FunName,		//[2]
		& Temp_FunName,		//[3]
		& Temp_FunName,		//[4]
		& Temp_FunName,		//[5]
		& Computer_Room_Manage_Page,		//[6]
	},
	{
	"��","����˻�","��¼�˻�","�˳��˻�","Ԥ��ϵͳ","��ѯϵͳ","����ϵͳ",
	}
};