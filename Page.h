#pragma once
//三级目录文件
#include<string>

// 页码结构（呕心沥血）		（学会重载再重构page。。。）
typedef struct pages {//所在层次 ,*各个开关[]，功能[],该页名称
	std::string PageName;	//翻不机密层次，
	int PageLayer;			
	struct pages* Link[7];
	std::string FunName[7];
}Pages;

extern Pages Page_Exit;
extern Pages Temp_FunName; // 不会乱序赋值

extern Pages Menu_Page;
extern Pages Book_Page;
extern Pages Query_Page;
extern Pages Manage_Page;
extern Pages User_Manage_Page;
extern Pages Computer_Room_Manage_Page;
extern Pages Computer_Manage_Page;
extern Pages Book_Manage_Page;
