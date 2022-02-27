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

int Pre_Book(){			//初步预定										//------------------没有初始化数据（状态什么的（已被预定））
	//////////////////////////////////////////////////////还缺少功能：检测同一时间段是否预定多台电脑（book state）以及某台电脑是否被预约了（不能两人一台电脑？）
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a"); //文件用于存储 ，，，，机位是否被占用，各种数据
	fclose(FP_BookData);
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
			Temp_Book.Book_Time.Month = Time_Point->tm_mon + 1;
			Temp_Book.Book_Time.Day = Time_Point->tm_mday;
			Temp_Book.Book_Time.Hour = Time_Point->tm_hour + 8;
			Temp_Book.Book_Time.Minute = Time_Point->tm_min;
			Temp_Book.Book_Time.Second = Time_Point->tm_sec;

			//if (ComputerRoom_Num() == 0) {
			if (!ComputerRoom_Num()) {
				if (MessageBox(NULL, TEXT("还没有任何机房！是否添加机房？"), TEXT("提醒"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6)Add_Computer_Room();	//检查是否有机房
				else return 0;//不添加机房哪来的机位，退出预定机位功能！
			}

			do{
			char ch_time[10];//?
			inputbox_getline("请输入预定小时数", "请输入预定小时数", ch_time , 5);
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
				if (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name)) {			//输入机房名称查询有无
					inputbox_getline("请输入机位名称", "请输入机位名称", Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, 40);	//有的话输入机位
					if (HaveComputer(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name)) {
						break;//有就退出审核
					}else //无就问
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
			}
			Books_Read = Books_Head;
			while (!feof(FP_BookData)) {      //以尾接法建立一个链表。  feof检测文件是否结束
				if (Book_Point = (Books_List)malloc(sizeof(Books_Size))) {
					fscanf(FP_BookData, "%d/%d/%d %d:%d:%d Long:%d\tUserName:%s\tBookRoom:%s\tBookComputer:%s\tBookState:%d\n",
						&Book_Point->Book_Data.Book_Time.Year, &Book_Point->Book_Data.Book_Time.Month, &Book_Point->Book_Data.Book_Time.Day,
						&Book_Point->Book_Data.Book_Time.Hour, &Book_Point->Book_Data.Book_Time.Minute, &Book_Point->Book_Data.Book_Time.Second,
						&Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
						Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
						Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
						&Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//应该是这个
					);//读出文件当前记录
					Books_Read->Books_Next = Book_Point;
					Books_Read = Book_Point;
				}
			}
			Books_Read->Books_Next = NULL;
			fclose(FP_BookData);

			Book_Point = Books_Head->Books_Next;
			while ((Book_Point) 
				&& (strcmp("a", "b") != 0) 
				&& (1)
				)//待加入检查重复预订
				Book_Point = Book_Point->Books_Next;
			if (!Book_Point) {    //没找到，则以追加的方式写入BookLog.txt文本中
				FP_BookData = fopen("Files\\BookLog.txt", "a");
				Temp_Book.Computer_Book_Data.Computer_Book_State = 1;//（待同意的初步预定）
				fprintf(FP_BookData,"%d/%d/%d %d:%d:%d Long:%d\tUserName:%s\t BookRoom:%s\tBookComputer:%s\tBookState:%d\n",
					Temp_Book.Book_Time.Year, Temp_Book.Book_Time.Month ,Temp_Book.Book_Time.Day,
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