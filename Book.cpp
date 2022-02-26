#include "Book.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#include "Book.h"
#include "AccountControl.h"




int Pre_Book(){			//初步预定
	/// <summary>
	/// 如果已经登录：创建txt，读取所 预定的时间，机房,机位数据，（不存在问）
	/// 时间在允许之外，提示，，，允许之内：输入要预定的时长
	/// （如果现在时间+时长已经在机房允许时间之外：提醒开放时间）（不用）
	/// 
	///Book_Type：
	///Time_Type Book_Time;							//预定的时间
	///Time_Type Book_Time_Long;					//机位的预定时长
	///User_Type User_Book_Data;					//预定用户数据（名字）
	///ComputerRoom_Type ComputerRoom_Book_Data;    //预定机房数据
	///Computer_Type Computer_Book_Data;			//预定机位数据
	/// </summary>
	if (Temp_User.Logined) { //已登录
		FILE* FP_BookData = NULL;
		FP_BookData = fopen("Files\\BookLog.txt", "a"); //文件用于存储 ，，，，机位是否被占用，各种数据
		fclose(FP_BookData);
		do {	//读取并存储账号密码 
			Add_User();
			User_Type Temp_ComputerRoom={};
			Accounts_List Accounts_Head, Accounts_Read, Account_Point;

			int Temp_Type = MessageBox(NULL, TEXT("授予账户管理员权限？"), TEXT("用户权限设置"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION：问号https://blog.csdn.net/yuyan987/article/details/78558648
			inputbox_getline("请输入账号", "请输入账号", Temp_ComputerRoom.Username, 40);      //输入账号
			inputbox_getline("请输入密码", "请输入密码", Temp_ComputerRoom.Password, 40);      //输入密码
			Temp_ComputerRoom.Type = (Temp_Type == 6) ? 1 : 0;	 //是(Y) 值为6 否(N)值为7;	//标记用户权限
			Temp_ComputerRoom.HaveComputer = 0;

			FP_BookData = fopen("Files\\BookLog.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
			if (Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size))) {
				Accounts_Head->Accounts_Next = NULL;
			}
			Accounts_Read = Accounts_Head;
			while (!feof(FP_BookData)) {      //以尾接法建立一个链表。  feof检测文件是否结束
				if (Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size))) {
					fscanf(FP_BookData, "%s %s %d %d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.HaveComputer);//读出文件当前记录
					Accounts_Read->Accounts_Next = Account_Point;
					Accounts_Read = Account_Point;
				}
			}
			Accounts_Read->Accounts_Next = NULL;
			fclose(FP_BookData);

			Account_Point = Accounts_Head->Accounts_Next;
			while ((Account_Point) && (strcmp(Temp_ComputerRoom.Username, Account_Point->Accounts_Data.Username) != 0) && (1))//比对数据，没找到相同用户名，且没找完，继续找
				Account_Point = Account_Point->Accounts_Next;
			if (!Account_Point) {    //没找到相同用户名，则以追加的方式写入BookLog.txt文本中，且档次的注册流程完成
				FP_BookData = fopen("Files\\BookLog.txt", "a");
				fprintf(FP_BookData, "%s %s %d %d\n", Temp_ComputerRoom.Username, Temp_ComputerRoom.Password, Temp_ComputerRoom.Type, Temp_ComputerRoom.HaveComputer);
				fclose(FP_BookData);
				return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
			}
			else {  //找到了，则需要重新输入用户名和密码，再循环刚刚的过程。
				if (MessageBox(NULL, TEXT("重新添加？"), TEXT("用户名已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
			}
		} while (1);
	}
	else {
		MessageBox(NULL, TEXT("您未登录！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}
int Cancel_Pre_Book() {	//取消预定
	return 1;
}
int Query_IsBooK(){		//
	return 1;
}
int Book() {			//预定页面
	return 1;
}