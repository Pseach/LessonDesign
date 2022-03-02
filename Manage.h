#pragma once
//三级目录文件

int Manage();

int ComputerRoom_Num();
bool HaveComputerRoom(char Static_ComputerRoomName[]);
bool HaveComputer(char Static_ComputerName[]);

//用户管理系统
int User_Manage();				//管理用户
int Transform_User_BookPower();	//开启|关闭用户预定功能
int Delete_User();		//删除用户
int Change_User();		//更改用户

//机房管理系统
int Computer_Room_Manage();			//机房管理
int Transform_Computer_Room();	//开放|关闭机房
int Add_Computer_Room();	//增加机房
int Delete_Computer_Room();	//删除机房
int Change_Computer_Room();	//更改机房

//机位管理系统
int Computer_Manage();			//机位管理
int Transform_Computer();	//开放|关闭机位 
int Add_Computer();		//增加机位
int Delete_Computer();	//删除机位
int Change_Computer();	//更改机位

//预定管理
int Search_All_Book();
int Agree_ALL_Book();