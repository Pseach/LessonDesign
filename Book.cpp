#include "Book.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Book.h"
#include "AccountControl.h"
#include <string>
#include "Manage.h"//ComputerRoom_Num

//摘自https://www.cnblogs.com/curo0119/p/7792627.html
enum error { correct, incorrect, overflow, null };
int error = correct;//默认是正确的
int MyAtoi(const char* str) {	
	int flag = 1;
	if (str == NULL) {
		error = null;
		return 0;
	}
	while (*str == ' ' || *str == '\t' || *str == '\f' || *str == '\r' || *str == '\n')
		str++;
	if (*str == '-') {											//负数的处理返回incorrect
		error = incorrect;//非法								//按需求改轮子
		flag = -1;
		str++;
	}
	else if (*str == '+')//注意对正负号我用的不是循环，正负号只有作为第一个字符出现才是合法的
		str++;
	int num = 0;
	while (*str != '\0') {//*str=='\0'也是结束条件之一
		if (*str >= '0' && (*str <= '9')) {
			num = num * 10 + *str - '0';//注意是‘0‘   　　　　　//溢出处理稍后贴上
			str++;
		}
		else {
			error = incorrect;//非法
			break;
		}
	}
	return num * flag;
}

long long timecmp(Time_Type a, Time_Type b) {//a>b
	if (b.Hour >= 24)b.Day += b.Hour / 24;
	if (b.Day >= 30)b.Month += b.Month / 30;

	if(a.Month != b.Month)return a.Month > b.Month;
	if (a.Day != b.Day)return a.Day > b.Day;
	if (a.Hour != b.Hour)return a.Hour > b.Hour;
	if (a.Minute != b.Minute)return a.Minute > b.Minute;
	if (a.Second != b.Second)return a.Second > b.Second;
	return 0;
}
int canuse(char name[],int mod) {
	char s1[40], s2[40], s3[40];
	int state = 0;
	if (mod == 1) {
		FILE* FP_ComputerRoom = NULL;
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		while (!feof(FP_ComputerRoom)) {
			fscanf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n",s1, &state);//读出文件当前记录
			if (strcmp(s1, name) == 0)return state;
		}
	}if (mod == 2) {
		FILE* FP_Computer = NULL;
		FP_Computer = fopen("Files\\ComputerRooms.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		while (!feof(FP_Computer)) {
			fscanf(FP_Computer, "ComputerName：%s\tState：%d\n", s1, &state);//读出文件当前记录
			if (strcmp(s1, name) == 0)return state;
		}
	}
	//fclose(FP_Computer);
}
int Pre_Book(){			//初步预定									
	//////////////////////////////////////////////////////还缺少功能：以及某台电脑是否被预约了（不能两人一台电脑？）
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a"); //文件用于存储 ，，，，机位是否被占用，各种数据
	fclose(FP_BookData);
	if (Temp_User.CanBook) {
		if (Temp_User.Logined) { //已登录 
			do {

				Book_Type Temp_Book = {};
				time_t timep;
				struct tm* Time_Point;
				time(&timep);
				Time_Point = gmtime(&timep);
				/*Time_Type Temp_Time = {};
				Time_Type Book_Time_Long = {};
				User_Type User_Book_Data = {};
				ComputerRoom_Type ComputerRoom_Book_Data = {};
				Computer_Type Computer_Book_Data = {};*/

				Books_List Books_Head, Books_Read, Book_Point;

				Temp_Book.Book_Time.Year = Time_Point->tm_year + 1900;
				Temp_Book.Book_Time.Month = Time_Point->tm_mon + 1;//0~11
				Temp_Book.Book_Time.Day = ((Time_Point->tm_hour + 8) >= 24) ? (Time_Point->tm_mday + 1) : (Time_Point->tm_mday);	//补回来
				//Temp_Book.Book_Time.Hour = ((Time_Point->tm_hour + 8) >= 24) ? (Time_Point->tm_hour + 8 - 24) : (Time_Point->tm_hour + 8);//可能出现“26”小时等意外数据
				Temp_Book.Book_Time.Hour = (Time_Point->tm_hour + 8) % 24;//可能出现“26”小时等意外数据
				Temp_Book.Book_Time.Minute = Time_Point->tm_min;
				Temp_Book.Book_Time.Second = Time_Point->tm_sec;


				if (1) {///////////////////////////////////检查是否 刚刚已经预约过还没结束
					Book_Type localbookdata = {};
					FP_BookData = fopen("Files\\BookLog.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
					while (!feof(FP_BookData)) {      //以尾接法建立一个链表。  feof检测文件是否结束	%02d-%02d-%02d
						Time_Type localtime = {};
						fscanf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long：%d UserName：%s BookRoom：%s BookComputer：%s BookState：%d\n",
							&localtime.Year, &localtime.Month, &localtime.Day,
							&localtime.Hour, &localtime.Minute, &localtime.Second,
							&localbookdata.Book_Time_Long.Hour, localbookdata.User_Book_Data.Username,
							localbookdata.ComputerRoom_Book_Data.ComputerRoom_Name,
							localbookdata.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
							&localbookdata.Computer_Book_Data.Computer_Book_State
						);//读出文件当前记录
						if (localbookdata.Computer_Book_Data.Computer_Book_State == 1|| localbookdata.Computer_Book_Data.Computer_Book_State == 2) {					//预约了|同意请求（2）
							if (strcmp(Temp_User.Username, localbookdata.User_Book_Data.Username) == 0) {//同名
								localtime.Hour += localbookdata.Book_Time_Long.Hour;
								if (!timecmp(Temp_Book.Book_Time, localtime)) {	//现在的时间如果大于之前时间+约时 那就能预定
									fclose(FP_BookData);
									return MessageBox(NULL, TEXT("您已经有一台计算机了！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
								}
							}
						}
					}
					//遍历完后，
					fclose(FP_BookData);
				}


				//if (ComputerRoom_Num() == 0) {
				if (!ComputerRoom_Num()) {
					if (MessageBox(NULL, TEXT("还没有任何机房！是否添加机房？"), TEXT("提醒"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6)Add_Computer_Room();	//检查是否有机房
					else return 0;//不添加机房哪来的机位，退出预定机位功能！
				}

				do {
					char ch_time[10];//?
					inputbox_getline("请输入预定小时数", "请输入预定小时数", ch_time, 5);
					switch (error) {
					case correct:
						break;
					case null:
						//MessageBox(NULL, TEXT("输入非法！请重新输入！"), TEXT("警告"), MB_OK | MB_SETFOREGROUND);
						//error = correct;
						//break;
					case incorrect:
						MessageBox(NULL, TEXT("输入非法！请重新输入！"), TEXT("警告"), MB_OK | MB_SETFOREGROUND);
						error = correct;
						break;
					case overflow:
						MessageBox(NULL, TEXT("输入的数太大！请重新输入！"), TEXT("警告"), MB_OK | MB_SETFOREGROUND);
						error = correct;
					}
					Temp_Book.Book_Time_Long.Hour = MyAtoi(ch_time);
				} while (error != correct);
				strcpy(Temp_Book.User_Book_Data.Username, Temp_User.Username);		//把输入的临时信息放到临时预定的数据结构体里

				do {//---------------------------优化！！！！(没对应机位的时候，问是否添加的时候，直接添加所输入的机位而不是再输)
					inputbox_getline("请输入添加机位所在机房名称", "请输入添加机位所在机房名称", Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, 40);	//先输入机房
					if (!canuse(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, 1)) { MessageBox(NULL, TEXT("您输入的机房已被关闭！！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND); return 0; }
					if (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name)) {			//输入机房名称查询有无
						inputbox_getline("请输入机位名称", "请输入机位名称", Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, 40);	//有的话输入机位
						if (!canuse(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name,2)) { MessageBox(NULL, TEXT("您输入的机位已被暂停使用！！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND); return 0; }
						if (HaveComputer(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name)) {
							break;//有就退出审核
						}
						else //无就问
							if (MessageBox(NULL, TEXT("该机房无此机位，是否添加机位"), TEXT("提醒"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer(); continue; }	//continue会跳到“}”
							else return 0;	//不添加机位就退出
					}
					else {//无的话问添加否
						if (MessageBox(NULL, TEXT("还没有该机房！是否添加机房？"), TEXT("提醒"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer_Room(); continue; }	//是的话就添加机房，//continue:填加完机房，重新输入要添加机位的机房
						else return 0;	//不添加机房就退出
					}
				} while (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name));



				Temp_Book.Computer_Book_Data.Computer_Book_State = 0;//初始化预定状态

				FP_BookData = fopen("Files\\BookLog.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
				if (Books_Head = (Books_List)malloc(sizeof(Books_Size))) {
					Books_Head->Books_Next = NULL;
				}//初始化头节点
				Books_Read = Books_Head;//让Read指向链表头
				while (!feof(FP_BookData)) {      //以尾接法建立一个链表。  feof检测文件是否结束	%02d-%02d-%02d
					if (Book_Point = (Books_List)malloc(sizeof(Books_Size))) {
						fscanf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long：%d UserName：%s BookRoom：%s BookComputer：%s BookState：%d\n",
							&Book_Point->Book_Data.Book_Time.Year, &Book_Point->Book_Data.Book_Time.Month, &Book_Point->Book_Data.Book_Time.Day,
							&Book_Point->Book_Data.Book_Time.Hour, &Book_Point->Book_Data.Book_Time.Minute, &Book_Point->Book_Data.Book_Time.Second,
							&Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
							Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
							Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
							&Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//应该是这个
						);//读出文件当前记录
						Books_Read->Books_Next = Book_Point;//让用来读的Read的下一个节点指向读到的Point的位置（即让用来临时存数据的Point的数据存到Read里）////Books_Read->Books_Next即Read所指的对象（Head或者新的Head）
						Books_Read = Book_Point;//重置（循环上去会重新malloc）用来读的Read
					}
				}
				//遍历完后，
				Books_Read->Books_Next = NULL;//初始化
				fclose(FP_BookData);

				Book_Point = Books_Head->Books_Next;//初始化（让Point指向Head的下一个（所存链表的头））
				while ((Book_Point)//链表头
					&& (strcmp("a", "b") != 0)
					&& (1)
					)//adduser：cmp！=0 （不一样）（没找到）才运行while里的（即往后找）
					Book_Point = Book_Point->Books_Next;//从头往Next遍历
				if (!Book_Point) {    //（）没找到
					FP_BookData = fopen("Files\\BookLog.txt", "a");
					Temp_Book.Computer_Book_Data.Computer_Book_State = 1;//（待同意的初步预定）
					fprintf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long：%d UserName：%s BookRoom：%s BookComputer：%s BookState：%d\n",
						Temp_Book.Book_Time.Year, Temp_Book.Book_Time.Month, Temp_Book.Book_Time.Day,
						Temp_Book.Book_Time.Hour, Temp_Book.Book_Time.Minute, Temp_Book.Book_Time.Second,
						Temp_Book.Book_Time_Long.Hour, Temp_Book.User_Book_Data.Username,
						Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name,
						Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
						Temp_Book.Computer_Book_Data.Computer_Book_State//应该是这个
					);//记录
					fclose(FP_BookData);

					return MessageBox(NULL, TEXT("预定成功！等待同意！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
				}
				else {  //找到了，则需要重新输入用户名和密码，再循环刚刚的过程。
					if (MessageBox(NULL, TEXT("重新添加？"), TEXT("用户名已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
				}
			} while (1);
		}
		else {
			MessageBox(NULL, TEXT("您未登录！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		}
	}//CanBook
	else {
		MessageBox(NULL, TEXT("您已经被禁止预定功能！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	return 0;
}
int Cancel_Pre_Book() {	//取消预定//预定状态变成0
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a");
	fclose(FP_BookData);

	if (Temp_User.Logined) { //已登录 
		Book_Type Temp_Book = {};
		time_t timep;
		struct tm* Time_Point;
		time(&timep);
		Time_Point = gmtime(&timep);

		Books_List Books_Head, Books_Read, Book_Point;


		if (!ComputerRoom_Num()) {
			if (MessageBox(NULL, TEXT("还没有任何机房！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6)return 0;	//检查是否有机房
		}

		strcpy(Temp_Book.User_Book_Data.Username, Temp_User.Username);		//用户姓名 存到Book里User 

		inputbox_getline("请输入删除机位所在机房名称", "请输入删除机位所在机房名称", Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, 40);	//先输入机房
		if (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name)) {			//输入机房名称查询有无
			inputbox_getline("请输入机位名称", "请输入机位名称", Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, 40);	//有的话输入机位
			if (HaveComputer(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name)) {//有这个机位的话 
			}
			else {//无
				MessageBox(NULL, TEXT("该机房无此机位"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND | MB_SETFOREGROUND);
				return 0;
			}
		}
		else {//无的话
			MessageBox(NULL, TEXT("无此机房！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND | MB_SETFOREGROUND);
			return 0;
		}

		FP_BookData = fopen("Files\\BookLog.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		if (Books_Head = (Books_List)malloc(sizeof(Books_Size))) {
			Books_Head->Books_Next = NULL;
		}//初始化头节点
		Books_Read = Books_Head;//让Read指向链表头
		while (!feof(FP_BookData)) {      //以尾接法建立一个链表。  feof检测文件是否结束	%02d-%02d-%02d
			Book_Point = (Books_List)malloc(sizeof(Books_Size));
			fscanf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long：%d UserName：%s BookRoom：%s BookComputer：%s BookState：%d\n",
				&Book_Point->Book_Data.Book_Time.Year, &Book_Point->Book_Data.Book_Time.Month, &Book_Point->Book_Data.Book_Time.Day,
				&Book_Point->Book_Data.Book_Time.Hour, &Book_Point->Book_Data.Book_Time.Minute, &Book_Point->Book_Data.Book_Time.Second,
				&Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
				Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
				Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
				&Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//应该是这个
			);//读出文件当前记录

			if ((strcmp(Temp_Book.User_Book_Data.Username, Book_Point->Book_Data.User_Book_Data.Username) == 0)
				&& (strcmp(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name) == 0)
				&& (strcmp(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name) == 0)
				&& (1 == Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State)//删除功能（中间节点跳过）（终点则指向NULL（if（！NULL）->Next））//用户名相同，预约机房相同，预约的机位相同，把这个节点进行处理（左边注释）
				)
				Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State = 0;

			Books_Read->Books_Next = Book_Point;//让用来读的Read的下一个节点指向读到的Point的位置（即让用来临时存数据的Point的数据存到Read里）////Books_Read->Books_Next即Read所指的对象（Head或者新的Head）
			Books_Read = Book_Point;//重置（循环上去会重新malloc）用来读的Read
		}
		//遍历完后，
		Books_Read->Books_Next = NULL;//初始化
		fclose(FP_BookData);

		//新链表已建立
		// 下面重新输入到文档（从头写）
		//（w）删完重写
		FP_BookData = fopen("Files\\BookLog.txt", "w");
		Book_Point = Books_Head->Books_Next;//初始化（让Point指向Head的下一个（所存链表的头））
		while (Book_Point) {
			//从头重新输入
			fprintf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long：%d UserName：%s BookRoom：%s BookComputer：%s BookState：%d\n",
				Book_Point->Book_Data.Book_Time.Year, Book_Point->Book_Data.Book_Time.Month, Book_Point->Book_Data.Book_Time.Day,
				Book_Point->Book_Data.Book_Time.Hour, Book_Point->Book_Data.Book_Time.Minute, Book_Point->Book_Data.Book_Time.Second,
				Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
				Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
				Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
				Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//应该是这个
			);//记录(接到最后)
			Book_Point = Book_Point->Books_Next;
		}
		MessageBox(NULL, TEXT("删除预定成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		fclose(FP_BookData);
	}
	else {
		MessageBox(NULL, TEXT("您未登录！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}
int Query_BooK(){		//
	system("Files\\BookLog.txt");
	return 1;
}
int Book() {			//预定页面
	return 1;
}