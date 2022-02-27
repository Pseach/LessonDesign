#include "Page.h"
#include "start.h"

Pages Page_Exit = {};
Pages Temp_FunName = {};

//须由内层向外初始化

Pages Book_Page = {
	"预定系统",1,
	{	&Menu_Page,				//[0]
		&Temp_FunName,		//[1]
		&Temp_FunName,		//[2]
		&Temp_FunName,		//[3]
		&Temp_FunName,		//[4]
		&Temp_FunName,		//[5]
		&Temp_FunName,		//[6]
	},
	{
	"×","预定机位","取消预定","预定查询","","","",
	}
};

Pages Query_Page = {
	"查询系统",1,
	{	&Menu_Page,				//[0]
		&Temp_FunName,		//[1]
		&Temp_FunName,		//[2]
		&Temp_FunName,		//[3]
		&Temp_FunName,		//[4]
		&Temp_FunName,		//[5]
		&Temp_FunName,		//[6]
	},
	{
	"×","机位查询","机房查询","浏览机房","","","",
	}
};
	
	Pages User_Manage_Page = {
		"账户管理",2,
		{	&Temp_FunName,		//[0]
			&Temp_FunName,		//[1]
			&Temp_FunName,		//[2]
			&Temp_FunName,		//[3]
			&Temp_FunName,		//[4]
			&Temp_FunName,		//[5]
			&Temp_FunName,		//[6]
		},
		{
		"","删除账户","更改账户","更改用户预定权限","","","",
		}
	};
	Pages Computer_Room_Manage_Page = {
		"机房管理",2,
		{	&Temp_FunName,		//[0]
			&Temp_FunName,		//[1]
			&Temp_FunName,		//[2]
			&Temp_FunName,		//[3]
			&Temp_FunName,		//[4]
			&Temp_FunName,		//[5]
			&Temp_FunName,		//[6]
		},
		{
		"","增加机房","删除机房","更改机房","开关机房","","",
		}
	};
	Pages Computer_Manage_Page = {
		"机位管理",2,
		{	& Temp_FunName,		//[0]
			& Temp_FunName,		//[1]
			& Temp_FunName,		//[2]
			& Temp_FunName,		//[3]
			& Temp_FunName,		//[4]
			& Temp_FunName,		//[5]
			& Temp_FunName,		//[6]
		},
		{
		"","增加机位","删除机位","更改机位","开关机位","","",
		}
	};
	Pages Book_Manage_Page = {
		"预定管理",2,
		{	&Temp_FunName,		//[0]
			&Temp_FunName,		//[1]
			&Temp_FunName,		//[2]
			&Temp_FunName,		//[3]
			&Temp_FunName,		//[4]
			&Temp_FunName,		//[5]
			&Temp_FunName,		//[6]
		},
		{
		"","浏览预定信息","同意预定请求","","","","",
		}
	};
Pages Manage_Page = {
	"管理系统",1,
	{	&Menu_Page,						//[0]
		& User_Manage_Page,					//[1]
		& Computer_Room_Manage_Page,		//[2]
		& Computer_Manage_Page,				//[3]
		& Temp_FunName,		//[4]
		& Temp_FunName,		//[5]
		& Temp_FunName,		//[6]
	},
	{
	"×","账户管理","机房管理","机位管理","预定管理","","",
	}
};

Pages Menu_Page = {
	"菜单",1,
	{	& Page_Exit,				//[0]
		& Temp_FunName,		//[1]
		& Temp_FunName,		//[2]
		& Temp_FunName,		//[3]
		& Temp_FunName,		//[4]
		& Temp_FunName,		//[5]
		& Computer_Room_Manage_Page,		//[6]
	},
	{
	"×","添加账户","登录账户","退出账户","预定系统","查询系统","管理系统",
	}
};