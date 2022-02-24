#pragma once
//二级目录文件

struct Windows { // 窗口数据
	int x;
	int y;
};
extern Windows VerticalWindows;
extern Windows LandscapeWindows;

//用户当前配置
extern char Online_Login_User_Name[40];
extern int Online_Login_User_Type;	//用户|管理员
extern int Online_Login_User_HaveComputer;

extern const int Defaut_Font_Size;

//数据结构
typedef struct {  //系统操作用户的数据结构
	char Username[40];
	char Password[40];
	int Type;	//用户|管理员
	int HaveComputer;
}User_Type;
typedef struct Accounts_Node {  //链表用来存储从文件中读出来的数据
	User_Type Accounts_Data;
	struct Accounts_Node* Accounts_Next;
}Accounts_Size, * Accounts_List;

typedef struct {  //机房的数据结构
	char ComputerRoom_Name[40];				//机房名字 
	int ComputerRoom_State;				//可用|不可用	1|0
}ComputerRoom_Type;
typedef struct ComputerRoom_Node {
	ComputerRoom_Type ComputerRoom_Data;
	struct ComputerRoom_Node* ComputerRoom_Next;
}ComputerRoom_Size, * ComputerRoom_List;

typedef struct {  //计算机的数据结构
	char Computer_Name[40];				//计算机名字 
	char Computer_Room[40];				//哪个机房 
	int Computer_State;					//可用|不可用	1|0
	int IsPre_Book;						//被初步预定
	int IsFinal_Book; 					//被最终预定
}Computer_Type;
typedef struct Computers_Node {
	Computer_Type Computers_Data;
	struct Computers_Node* Computers_Next;
}Computers_Size, * Computers_List;

//函数
int MainStart();
int Exit();

