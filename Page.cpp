#include "Page.h"
#include "start.h"

Pages Page_Exit = {};
Pages Temp_FunName = {};

//�����ڲ������ʼ��

Pages Book_Page = {
	"Ԥ��ϵͳ",1,
	{	&Menu_Page,				//[0]
		&Temp_FunName,		//[1]
		&Temp_FunName,		//[2]
		&Temp_FunName,		//[3]
		&Temp_FunName,		//[4]
		&Temp_FunName,		//[5]
		&Temp_FunName,		//[6]
	},
	{
	"��","Ԥ����λ","ȡ��Ԥ��","Ԥ����ѯ","","","",
	}
};

Pages Query_Page = {
	"��ѯϵͳ",1,
	{	&Menu_Page,				//[0]
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
	
	Pages User_Manage_Page = {
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
		"","ɾ���˻�","�����˻�","�����û�Ԥ��Ȩ��","","","",
		}
	};
	Pages Computer_Room_Manage_Page = {
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
	Pages Computer_Manage_Page = {
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
	Pages Book_Manage_Page = {
		"Ԥ������",2,
		{	&Temp_FunName,		//[0]
			&Temp_FunName,		//[1]
			&Temp_FunName,		//[2]
			&Temp_FunName,		//[3]
			&Temp_FunName,		//[4]
			&Temp_FunName,		//[5]
			&Temp_FunName,		//[6]
		},
		{
		"","���Ԥ����Ϣ","ͬ��Ԥ������","","","","",
		}
	};
Pages Manage_Page = {
	"����ϵͳ",1,
	{	&Menu_Page,						//[0]
		& User_Manage_Page,					//[1]
		& Computer_Room_Manage_Page,		//[2]
		& Computer_Manage_Page,				//[3]
		& Temp_FunName,		//[4]
		& Temp_FunName,		//[5]
		& Temp_FunName,		//[6]
	},
	{
	"��","�˻�����","��������","��λ����","Ԥ������","","",
	}
};

Pages Menu_Page = {
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