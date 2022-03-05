#include "AccountControl.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Buttons.h"
#include "DataInput.h"
#include <ege/sys_edit.h>

//extern User_Type Temp_User;

int Show_Online_Login_User() {	//显示当前账户

	//LPCSTR Font1="\u65b9\u6b63\u55b5\u545c\u4f53";		
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // 文字颜色
	setfont(Defaut_Font_Size, 0, "方正喵呜体");					//字体大小  宽度比例自适应  字体文件

	//settextjustify(CENTER_TEXT, CENTER_TEXT);//文字居中，以后可能重构代码用到

	//显示当前账户栏
	ege_line(0, 1, HeadlineButton.Width, 1);
	ege_line(0, HeadlineButton.Height, HeadlineButton.Width, HeadlineButton.Height);	//顶栏的边框

	drawRectButton(&HeadlineButton);	//此行暂时无作用
	xyprintf(HeadlineButton.Height * 1 / 5 / 2, HeadlineButton.Height * 1 / 5 / 2, "当前账户:");//“当前账户："

	drawRectButton(&ShowOnline_Login_User);	//此行暂时无作用
	xyprintf(ShowOnline_Login_User.X, ShowOnline_Login_User.Y, "%s", Temp_User.Username); //登陆账户为" "

	/////////////////////////////////////////////////////////////////////时间显示-----因为每次页面刷新都调用这个函数，所以就变成静态的了
	time_t timep;
	struct tm* Time_Point;
	time(&timep);
	Time_Point = gmtime(&timep);
	//Temp_Book.Book_Time.Year = Time_Point->tm_year + 1900;
	//Temp_Book.Book_Time.Month = Time_Point->tm_mon + 1;
	//Temp_Book.Book_Time.Day = Time_Point->tm_mday;
	xyprintf(WindowsSize.x - 4 * Defaut_Font_Size, HeadlineButton.Height * 1 / 5 / 2, "%02d:%02d:%02d", ((Time_Point->tm_hour + 8) >= 24) ? (Time_Point->tm_hour + 8 - 24) : (Time_Point->tm_hour + 8), Time_Point->tm_min, Time_Point->tm_sec);
	/////////////////////////////////////////////////////////////////////时间显示

	{ 
		int RemindFont_Size = Defaut_Font_Size / 2;
		setfont(RemindFont_Size, 0, "方正喵呜体", 0, 0, 100, 0, 0, 0);
		setcolor(BLACK);
		//setcolor(WHITE);

		switch(Temp_User.Type){			//根据用户的全局变量结构体显示当前的用户类型
			case -1: {	//未知
				xyprintf(0, HeadlineButton.Height + RemindFont_Size / 2, "请登录！");//4个字	//左上角
				//xyprintf(HeadlineButton.Height / 5, HeadlineButton.Height + RemindFont_Size / 2, "请登录！");//4个字	//左上角
				//xyprintf(HeadlineButton.Width - 4 * RemindFont_Size, HeadlineButton.Height + RemindFont_Size / 2, "请登录！");//4个字	//右上角
				//xyprintf(HeadlineButton.width - 4 * RemindFont_Size, WindowsSize.y - RemindFont_Size * 3 / 2, "请登录！");//4个字		//右下角
				break;
			}
			case 0: {	//普通用户
				xyprintf(0, HeadlineButton.Height + RemindFont_Size / 2, "尊敬的用户您好！");//8个字
				//xyprintf(HeadlineButton.X / 5, HeadlineButton.Height + RemindFont_Size / 2, "尊敬的用户您好！");//8个字
				//xyprintf(HeadlineButton.Width - 8 * RemindFont_Size, HeadlineButton.Height + RemindFont_Size / 2, "尊敬的用户您好！");//8个字
				//xyprintf(HeadlineButton.width - 8 * RemindFont_Size, WindowsSize.y - RemindFont_Size * 3 / 2, "尊敬的用户您好！");//8个字
				break;
			}
			case 1: {	//管理员
				xyprintf(0, HeadlineButton.Height + RemindFont_Size / 2, "尊敬的管理员您好！");//9个字
				//xyprintf(HeadlineButton.X / 5, HeadlineButton.Height + RemindFont_Size / 2, "尊敬的管理员您好！");//9个字
				//xyprintf(HeadlineButton.Width - 9 * RemindFont_Size, HeadlineButton.Height + RemindFont_Size / 2, "尊敬的管理员您好！");//9个字
				//xyprintf(HeadlineButton.width - 9 * RemindFont_Size, WindowsSize.y - RemindFont_Size * 3 / 2, "尊敬的管理员您好！");//9个字
				break;
			}
		}
	}
	return 1;
}

int Add_User() { //注册/添加用户
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Accounts);
	do {	//读取并存储账号密码 
		User_Type Temp_Accounts{};	//将读取数据暂存于此
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		int Temp_Type = MessageBox(NULL, TEXT("授予账户管理员权限？"), TEXT("添加用户"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION：问号https://blog.csdn.net/yuyan987/article/details/78558648
		sys_edit editBox;

		inputbox_getline("请输入账号", "请输入账号", Temp_Accounts.Username, Max_Input_Num);      //输入账号//https://xege.org/manual/api/other/inputboxgetline.htm buffer area
		//strcpy(Temp_Accounts.Username,My_InputBox_One_Line(&editBox));

		inputbox_getline("请输入密码", "请输入密码", Temp_Accounts.Password, Max_Input_Num);      //输入密码
		Temp_Accounts.Type = (Temp_Type == 6) ? 1 : 0;	 //是(Y) 值为6 否(N)值为7;	//标记用户权限
		Temp_Accounts.CanBook = 1;
		/////////////////////////////////////////////////////////////////////////////建立链表
		FP_Accounts = fopen("Files\\Users.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		if (Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size))) {
			Accounts_Head->Accounts_Next = NULL;
		}
		Accounts_Read = Accounts_Head;
		while (!feof(FP_Accounts)) {      //以尾接法建立一个链表。  feof检测文件是否结束
			if (Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size))) {
				fscanf(FP_Accounts, "%s\t%s\t%d\t%d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.CanBook);//读出文件当前记录
				Accounts_Read->Accounts_Next = Account_Point;
				Accounts_Read = Account_Point;
			}
		}
		Accounts_Read->Accounts_Next = NULL;
		fclose(FP_Accounts);
		Account_Point = Accounts_Head->Accounts_Next;
		///////////////////////////////////////////////////////////////////////////建立链表到Point

		while ((Account_Point) && (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) != 0) && (1))//比对数据，没找到相同用户名，且没找完，继续找
			Account_Point = Account_Point->Accounts_Next;
		if (!Account_Point) {    //没找到相同用户名，则以追加的方式写入Users.txt文本中，且档次的注册流程完成
			FP_Accounts = fopen("Files\\Users.txt", "a");
			fprintf(FP_Accounts, "%s\t%s\t%d\t%d\n", Temp_Accounts.Username, Temp_Accounts.Password, Temp_Accounts.Type, Temp_Accounts.CanBook);
			fclose(FP_Accounts);
			return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		}
		else {  //找到了，则需要重新输入用户名和密码，再循环刚刚的过程。
			if (MessageBox(NULL, TEXT("重新添加？"), TEXT("用户名已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
		}
	} while (1);
}

int Login_User(){        	    //登录
	if (Temp_User.Logined) { //已登录
		MessageBox(NULL, TEXT("您已登录！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	else {
		FILE* FP_Accounts = NULL;
		FP_Accounts = fopen("Files\\Users.txt", "a"); //如果文件不存在，则会创建一个新文件
		fclose(FP_Accounts);

		User_Type Temp_Accounts={};
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		bool isFindAccount = 0;
		do {	//读取 并存储账号密码 

			//输入数据寄存到Temp_Accounts
			if(!isFindAccount)inputbox_getline("请输入账号", "请输入账号", Temp_Accounts.Username, Max_Input_Num);      //输入账号//https://xege.org/manual/api/other/inputboxgetline.htm buffer area

			inputbox_getline("请输入密码", "请输入密码", Temp_Accounts.Password, Max_Input_Num);      //输入密码

			FP_Accounts = fopen("Files\\Users.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
			Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size));
			Accounts_Head->Accounts_Next = NULL;
			Accounts_Read = Accounts_Head;

			while (!feof(FP_Accounts)) {      //以尾接法建立一个链表。  feof检测文件是否结束 // 遍历
				Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size));
				fscanf(FP_Accounts, "%s\t%s\t%d\t%d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.CanBook);//读出文件当前记录
				//对比
				if (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) == 0) {	//对比账户名： == 0 说明找到
					isFindAccount = 1;
					if(strcmp(Temp_Accounts.Password, Account_Point->Accounts_Data.Password) == 0){	//对比密码  == 0 密码吻合
						//登录
						Temp_Accounts.Type = Account_Point->Accounts_Data.Type;//改变登录账户的权限
						Temp_Accounts.CanBook = Account_Point->Accounts_Data.CanBook;

						fclose(FP_Accounts);
						strcpy(Temp_User.Username, Temp_Accounts.Username);
						Temp_User.Type = Temp_Accounts.Type;	//更换用户种类
						Temp_User.Logined = 1;			//变更登录状态已登录
						Temp_User.CanBook = Temp_Accounts.CanBook;

						return MessageBox(NULL, TEXT("登录成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
					}else { //密码错误
						if ((MessageBox(NULL, TEXT("密码错误！\n是否重新输入账号密码?"), TEXT("账号已找到找到！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 6) ? 1 : 0) {//是 1
							break;
						}
						else return 0;//退出 
					}
				}
			}
			//搜完了
			if (!isFindAccount) {//没找到账户，
				if ((MessageBox(NULL, TEXT("没有到找到账号！\n是否注册账户?"), TEXT("没有到找到账号！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 6) ? 1 : 0) {
					Add_User();
				}
				else return 0;
			}

		} while (1);

	}
	return 1;
}

int Logout_User() {          //退出账户
	if (Temp_User.Type == -1) {
		MessageBox(NULL, TEXT("您还没有登录！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	else {
		//User_Type Temp_User = { "NONE","NONE",-1,0,0 };//?
		strcpy(Temp_User.Username, "NONE");
		strcpy(Temp_User.Password, "NONE");
		Temp_User.CanBook = 1;
		Temp_User.Type = -1;
		Temp_User.Logined = 0;
		//Temp_User.CanBook = 1;
		MessageBox(NULL, TEXT("您已退出当前账户！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}