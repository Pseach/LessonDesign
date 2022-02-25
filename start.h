#pragma once
//二级目录文件
#include <string> // Page string

//extern int Page;//切换页面 换按钮 (弃用)

//数据结构
struct Windows { // 窗口数据
	int x;
	int y;
};

typedef struct {  //时间的数据结构
	int Year;
	int Month;
	int Day;
	int Time_Mod;	// 按手动调节 | 按系统时间 （可能用？）
}Time_Type;

typedef struct {  //机位的数据结构
	char Computer_Name[40];				//机位名字 
	char Computer_Room[40];				//哪个机房 
	int Computer_State;					//可用|不可用	1|0
	//int IsPre_Book;						//被初步预定
	//int IsFinal_Book; 					//被最终预定
}Computer_Type;

typedef struct {  //机房的数据结构
	char ComputerRoom_Name[40];				//机房名字
	int ComputerRoom_State;				//可用|不可用	1|0
	Computer_Type Computer_Data;		//（可能）用于按机房查询所有机位功能
}ComputerRoom_Type;

typedef struct {  //系统操作用户的数据结构
	char Username[40];
	char Password[40];
	int Type;					//用户|管理员
	int HaveComputer;			//是否拥有机位

	int Login_User_Type;		//未知|用户|管理员
	int Logined;				//登录状态
}User_Type;

typedef struct {  //预定信息的数据结构
	Time_Type Book_Time_Data;					//预定的时间
	Time_Type Computer_Book_Time_Data;			//机位的预定时间
	User_Type User_Book_Data;					//预定用户数据（名字）
	int Computer_Book_State;					//机位预定状态（没有被预定or初步预定or终极预定）
}Book_Type;

//book数据
//取消初步预定
//最终预定
// 添加计算机之前先添加机房（）用到机房查询所有机位（system（txt））
//可用时间段 （点击时间更改时间|系统时间）
//用文件存储预定信息，集中管理（查看所有预定用户？）
//初步预定就存到集中管理，还包括是否满足终极预定，预定时间
//时间对比（函数？）（重载<>？）

typedef struct Accounts_Node {  //链表用来存储从文件中读出来的数据
	User_Type Accounts_Data;
	struct Accounts_Node* Accounts_Next;
}Accounts_Size, * Accounts_List;

typedef struct ComputerRoom_Node {
	ComputerRoom_Type ComputerRoom_Data;
	struct ComputerRoom_Node* ComputerRoom_Next;
}ComputerRoom_Size, * ComputerRoom_List;

typedef struct Computers_Node {
	Computer_Type Computers_Data;
	struct Computers_Node* Computers_Next;
}Computers_Size, * Computers_List;

typedef struct Book_Node {
	Book_Type Book_Data;
	struct Book_Node* Book_Next;
}Book_Size, * Book_List;


//窗口配置
extern Windows VerticalWindows;
extern Windows LandscapeWindows;
extern Windows WindowsSize;

//用户当前配置
extern User_Type Temp_User;

//字体
extern const int Defaut_Font_Size;


//函数
int MainStart();
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Recovery_Button_State(int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Exit();

