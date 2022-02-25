#pragma once
//三级目录文件
#include<string>

// 页码结构（呕心沥血）
typedef struct pages {//所在层次 ,*各个开关[]，功能[],该页名称
	std::string PageName; //翻不机密层次
	int Page_Layer; 
	struct pages* Link[7];
	std::string FunName[7];
}Page;

extern Page Page_Exit;
extern Page Temp_FunName; // 不会乱序赋值

extern Page Menu_Page;
extern Page Book_Page;
extern Page Query_Page;
extern Page Manage_Page;
extern Page User_Manage_Page;
extern Page Computer_Room_Manage_Page;
extern Page Computer_Manage_Page;

