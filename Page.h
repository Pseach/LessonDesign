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

extern Page Menu_Page;
extern Page Page_Exit;
extern Page Temp_FunName; // 不会乱序赋值