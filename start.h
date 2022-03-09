#pragma once
//二级目录文件

extern int Page;//切换页面 换按钮

//字体
extern const int Defaut_Font_Size;
extern const int Max_Input_Num;

//数据结构
struct Windows { // 窗口数据
	int x;
	int y;
	Windows& operator=(Windows& value) {
		x = value.x;
		y = value.y;
		return *this;
	}
};

typedef struct time{  //时间的数据结构
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;
}Time_Type;
typedef struct {  //机位的数据结构
	char Computer_Name[10];				//机位名字 
	char Computer_Room[10];				//哪个机房 
	int Computer_State;					//可用|不可用	1|0
	int Computer_Book_State;			//机位预定状态（没有被预定or初步预定or终极预定）(用于在预定文件中查询历史记录时用）
}Computer_Type;

typedef struct {  //机房的数据结构
	char ComputerRoom_Name[10];				//机房名字
	int ComputerRoom_State;				//可用|不可用	1|0
	Computer_Type Computer_Data;		//用于按机房查询所有机位功能(?)
	Time_Type ComputerRoom_CanBook_Time;		//机房的允许预定时间
	Time_Type ComputerRoom_CanBook_TimeTo;		//机房的允许预定时间
}ComputerRoom_Type;

typedef struct usertpye{  //用户的数据结构
	char Username[10];
	char Password[10];
	int Type;					//未知|用户|管理员 -1|0|1
	int CanBook;			//是否拥有机位(CanBook)
	int Logined;				//登录状态
}User_Type;

typedef struct {  //预定信息的数据结构
	Time_Type Book_Time;						//预定的时间
	Time_Type Book_Time_Long;					//机位的预定时长//单位小时
	User_Type User_Book_Data;					//预定用户数据（名字）
	ComputerRoom_Type ComputerRoom_Book_Data;   //预定机房数据
	Computer_Type Computer_Book_Data;			//预定机位数据
}Book_Type;

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

typedef struct Books_Node {
	Book_Type Book_Data;
	struct Books_Node* Books_Next;
}Books_Size, * Books_List;


//窗口配置
extern Windows VerticalWindows;
extern Windows LandscapeWindows;
extern Windows WindowsSize;

//用户当前配置
extern User_Type Temp_User;



//函数
int MainStart();	//可以理解为就是函数
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Recovery_Button_State(int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);	
int Exit();//没用

