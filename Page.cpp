#include "Page.h"
#include "start.h"

Page Page_Exit = {};
Page Temp_FunName = {};

Page Book_Page = {
	"预定系统",1,
	{	&Page_Exit,				//[0]
		&Temp_FunName,		//[1]
		&Temp_FunName,		//[2]
		&Temp_FunName,		//[3]
		&Temp_FunName,		//[4]
		&Temp_FunName,		//[5]
		&Temp_FunName,		//[6]
	},
	{
	"×","预定机位","取消预定","","","","",
	}
};

Page Query_Page = {
	"查询系统",1,
	{	&Page_Exit,				//[0]
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

	Page User_Manage = {
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
		"","删除账户","更改账户","开关预定功能","","","",
		}
	};
	Page Computer_Room_Manage_Page = {
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
	Page Computer_Manage_Page = {
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
Page Manage_Page = {
	"管理系统",1,
	{	& Page_Exit,						//[0]
		& User_Manage,						//[1]
		& Computer_Room_Manage_Page,		//[2]
		& Computer_Manage_Page,				//[3]
		& Temp_FunName,		//[4]
		& Temp_FunName,		//[5]
		& Temp_FunName,		//[6]
	},
	{
	"×","账户管理系统","机房管理系统","机位管理系统","","","",
	}
};

Page Menu_Page = {
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