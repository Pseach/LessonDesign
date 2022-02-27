#pragma once
//二级目录文件

extern int Page;//切换页面 换按钮

//数据结构
struct Windows { // 窗口数据
	int x;
	int y;
	Windows& operator=(Windows& value) {
		x = value.x;
		y = value.y;
		return *this;
	}//无效果???（）
};

typedef struct time{  //时间的数据结构
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;
	int Time_Mod;	// 按手动调节 | 按系统时间 （可能用？）
	time& operator=(time& value){
		Year = value.Year;
		Month = value.Month;
		Day = value.Day;
		Second = value.Second;
		return *this;
	}
	bool operator< (time const& value) const {
		if (Year != value.Year) return Year < value.Year;
		else if (Month != value.Month) return Month < value.Month;
		else if (Day != value.Day) return Day < value.Day;
		else if (Second != value.Second) return Second < value.Second;
	}
	bool operator> (time const& value) const {
		if (Year != value.Year) return Year > value.Year;
		else if (Month != value.Month) return Month > value.Month;
		else if (Day != value.Day) return Day > value.Day;
		else if (Second != value.Second) return Second > value.Second;
	}
	bool operator= (time const& value) const {
		return ((Year == value.Year) && (Month == value.Month) && (Day == value.Day) && (Second == value.Second));
	}
	bool operator!= (time const& value) const {
		return ((Year != value.Year) || (Month != value.Month) || (Day != value.Day) || (Second != value.Second));
	}
}Time_Type;
typedef struct {  //机位的数据结构
	char Computer_Name[40];				//机位名字 
	char Computer_Room[40];				//哪个机房 
	int Computer_State;					//可用|不可用	1|0
	int Computer_Book_State;			//机位预定状态（没有被预定or初步预定or终极预定）
}Computer_Type;

typedef struct {  //机房的数据结构
	char ComputerRoom_Name[40];				//机房名字
	int ComputerRoom_State;				//可用|不可用	1|0
	//Time_Type ComputerRoom_CanBook_Time;		//机房的允许预定时间（直接全局管理）
	Computer_Type Computer_Data;		//用于按机房查询所有机位功能
}ComputerRoom_Type;

typedef struct usertpye{  //系统操作用户的数据结构
	char Username[40];
	char Password[40];
	int Type;					//未知|用户|管理员 -1|0|1
	int HaveComputer;			//是否拥有机位
	//int Login_User_Type;		//未知|用户|管理员 -1|0|1		//?????????
	int Logined;				//登录状态
	//usertpye& operator=(usertpye& value) {
	//	strcpy(Username, value.Username);
	//	strcpy(Password, value.Password);
	//	Type = value.Type;
	//	HaveComputer = value.HaveComputer;
	//	Login_User_Type = value.Login_User_Type;
	//	Logined = value.Logined;
	//	return *this;
	//}//无效果???（）
}User_Type;

typedef struct {  //预定信息的数据结构
	Time_Type Book_Time;						//预定的时间
	Time_Type Book_Time_Long;					//机位的预定时长//单位小时
	User_Type User_Book_Data;					//预定用户数据（名字）
	ComputerRoom_Type ComputerRoom_Book_Data;   //预定机房数据
	Computer_Type Computer_Book_Data;			//预定机位数据
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

//字体
extern const int Defaut_Font_Size;


//函数
int MainStart();
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Recovery_Button_State(int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Exit();

