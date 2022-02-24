#include "AccountControl.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#include "Buttons.h"

int Show_Online_Login_User() {	//显示当前账户
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // 文字颜色

	setfont(Defaut_Font_Size, 0, "方正喵呜体");					//字体大小  宽度比例自适应  字体文件

	//显示当前账户栏
	drawRectButton(&ButtonLocation_0);	//“当前账户："
	xyprintf(ButtonLocation_0.height * 1 / 5 / 2, ButtonLocation_0.height * 1 / 5 / 2, "当前账户：");

	drawRectButton(&ShowOnline_Login_User); //登陆账户为" "
	xyprintf(ShowOnline_Login_User.x, ShowOnline_Login_User.y, "%s", Temp_User.Username);

	{ 
		int RemindFont_Size = Defaut_Font_Size / 2;
		setfont(RemindFont_Size, 0, "方正喵呜体", 0, 0, 100, 0, 0, 0);
		setcolor(EGERGB(0x00, 0x00, 0x00));

		switch(Temp_User.Type){

			case -1: {	//未知
				xyprintf(ButtonLocation_0.width - 4 * RemindFont_Size, ButtonLocation_0.height, "请登录！");//4个字
				break;
			}
			case 0: {	//普通用户
				xyprintf(ButtonLocation_0.width - 8 * RemindFont_Size, ButtonLocation_0.height, "尊敬的用户您好！");//8个字
				break;
			}
			case 1: {	//管理员
				xyprintf(ButtonLocation_0.width - 9 * RemindFont_Size, ButtonLocation_0.height, "尊敬的管理员您好！");//9个字
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
		User_Type Temp_Accounts;
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		int Temp_Type = MessageBox(NULL, TEXT("授予账户管理员权限？"), TEXT("用户权限设置"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION：问号https://blog.csdn.net/yuyan987/article/details/78558648
		inputbox_getline("请输入账号", "请输入账号", Temp_Accounts.Username, 40);      //输入账号//https://xege.org/manual/api/other/inputboxgetline.htm buffer area
		inputbox_getline("请输入密码", "请输入密码", Temp_Accounts.Password, 40);      //输入密码
		Temp_Accounts.Type = (Temp_Type == 6) ? 1 : 0;	 //是(Y) 值为6 否(N)值为7;	//标记用户权限
		Temp_Accounts.HaveComputer = 0;

		FP_Accounts = fopen("Files\\Users.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size));
		Accounts_Head->Accounts_Next = NULL;
		Accounts_Read = Accounts_Head;
		while (!feof(FP_Accounts)) {      //以尾接法建立一个链表。  feof检测文件是否结束
			Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size));
			fscanf(FP_Accounts, "%s %s %d %d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.HaveComputer);//读出文件当前记录
			Accounts_Read->Accounts_Next = Account_Point;
			Accounts_Read = Account_Point;
		}
		Accounts_Read->Accounts_Next = NULL;
		fclose(FP_Accounts);

		Account_Point = Accounts_Head->Accounts_Next;
		while ((Account_Point) && (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) != 0) && (1))//比对数据，没找到相同用户名，且没找完，继续找
			Account_Point = Account_Point->Accounts_Next;
		if (!Account_Point) {    //没找到相同用户名，则以追加的方式写入Users.txt文本中，且档次的注册流程完成
			FP_Accounts = fopen("Files\\Users.txt", "a");
			fprintf(FP_Accounts, "%s %s %d %d\n", Temp_Accounts.Username, Temp_Accounts.Password, Temp_Accounts.Type, Temp_Accounts.HaveComputer);
			fclose(FP_Accounts);
			return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		}
		else {  //找到了，则需要重新输入用户名和密码，再循环刚刚的过程。
			if (MessageBox(NULL, TEXT("重新添加？"), TEXT("用户名已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
		}
	} while (1);
}

int Login_User(){        	    //登录
	/// <summary>
	/// 		//已登录
	///		//提示：您已登录
	///	//未登录
	///		//输入账户密码
	///			//搜数据
	///				//搜到：	
	///					// flag1
	///					//密码正确：	提示：登陆成功
	///					//密码错误：	问：是否重新输入
	///						//是：输 返回到flag1 
	///						//否：退出
	///				//没搜到：	提示：没有当前账户
	///					//问：注册吗 
	///						//注册： 	Add_User();
	///						//退出： 
	/// </summary>
	if (Temp_User.Logined) { //已登录
		MessageBox(NULL, TEXT("您已登录！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	else {

		FILE* FP_Accounts = NULL;
		FP_Accounts = fopen("Files\\Users.txt", "a"); //如果文件不存在，则会创建一个新文件
		fclose(FP_Accounts);

		User_Type Temp_Accounts;
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		bool isFindAccount = 0;
		do {	//读取 并存储账号密码 

			//输入数据寄存到Temp_Accounts
			if(!isFindAccount)inputbox_getline("请输入账号", "请输入账号", Temp_Accounts.Username, 40);      //输入账号//https://xege.org/manual/api/other/inputboxgetline.htm buffer area

			inputbox_getline("请输入密码", "请输入密码", Temp_Accounts.Password, 40);      //输入密码

			FP_Accounts = fopen("Files\\Users.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
			Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size));
			Accounts_Head->Accounts_Next = NULL;
			Accounts_Read = Accounts_Head;

			while (!feof(FP_Accounts)) {      //以尾接法建立一个链表。  feof检测文件是否结束 // 遍历
				Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size));
				fscanf(FP_Accounts, "%s %s %d %d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.HaveComputer);//读出文件当前记录
				//对比
				if (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) == 0) {	//对比账户名： == 0 说明找到
					isFindAccount = 1;
					if(strcmp(Temp_Accounts.Password, Account_Point->Accounts_Data.Password) == 0){	//对比密码  == 0 密码吻合
						//登录
						Temp_Accounts.Type = Account_Point->Accounts_Data.Type;//改变登录账户的权限
						fclose(FP_Accounts);
						strcpy(Temp_User.Username, Temp_Accounts.Username);
						Temp_User.Type = Temp_Accounts.Type;	//更换当前登录状态
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
		Temp_User = { "NONE","NONE",-1,0,0 };
		MessageBox(NULL, TEXT("您已退出当前账户！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}