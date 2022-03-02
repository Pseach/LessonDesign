#include "Query.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "Buttons.h" //HeadlineButton.Height
#include "AccountControl.h"//Show_Online_Login_User

int Query() {
	return 1;
}
int Computer_Query() {		//查询机位

	for (; is_run(); delay_fps(270)) {
		FILE* FP_Computers = NULL;
		FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
		fclose(FP_Computers);
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

		FP_Computers = fopen("Files\\Computers.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			ComputerRoom_Head->ComputerRoom_Next = NULL;
		}
		ComputerRoom_Read = ComputerRoom_Head;
		while (!feof(FP_Computers)) {      //以尾接法建立一个链表。  feof检测文件是否结束
			if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
				fscanf(FP_Computers, "FromComputerRoom：%s\tComputer：%s\tComputer_State：%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name, &ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State);//读出文件当前记录
				ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
				ComputerRoom_Read = ComputerRoom_Point;
			}
		}
		ComputerRoom_Read->ComputerRoom_Next = NULL;
		fclose(FP_Computers);
		ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
		/////////////////////////链表已建立//////////////////////
		//Defaut_Font_Size 
		int QuarryFont_Size = Defaut_Font_Size / 2;
		setfont(QuarryFont_Size, 0, "方正喵呜体", 0, 0, 100, 0, 0, 0);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			// 判断鼠标左键按下（左键按下确定位置，同时判断是否为按钮区域
			// 抬起则解除按下状态
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //初始化
				// 检查是否有按钮被按下
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, 10);
				// 将被按下的按钮设置为按下状态
				//if (ButtonId != -1) {
				//	PressButtonId = ButtonId;
				//	ButtonLocation[PressButtonId].Pressed = true;
				//	RefreshPage = true;
				//}
				if (ButtonId == 0)	return 0;
			}
		}
		PIMAGE pimg = newimage();
		getimage(pimg, "990X585.png");
		putimage(0, 0, pimg);
		delimage(pimg);
		DrawPage(Page);
		Show_Online_Login_User();
		int Data1x = 0, Data1y = HeadlineButton.Height + Defaut_Font_Size;
		int Data2x = WindowsSize.x / 4 , Data2y = HeadlineButton.Height + Defaut_Font_Size;
		int Data3x = WindowsSize.x / 2 - 2 * QuarryFont_Size, Data3y = HeadlineButton.Height + Defaut_Font_Size;
		xyprintf(Data1x, Data1y, "机房");
		xyprintf(Data2x, Data2y, "名称");
		xyprintf(Data3x, Data3y, "状态");
		int cnt = 0;
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			Data3y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			xyprintf(Data2x, Data2y, "%s", ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name);
			if (ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State)xyprintf(Data3x, Data3y, "开放");
			else xyprintf(Data3x, Data3y, "关闭");
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
			cnt++;
			if (cnt == 19) {
				Data1x += WindowsSize.x / 2; Data1y = HeadlineButton.Height + Defaut_Font_Size;
				Data2x += WindowsSize.x / 2; Data2y = HeadlineButton.Height + Defaut_Font_Size;
				Data3x += WindowsSize.x / 2; Data3y = HeadlineButton.Height + Defaut_Font_Size;
			}
		}
	}
	return 1;
}
int Computer_Room_Query() {	//查询机房
	for (; is_run(); delay_fps(270)) {
		FILE* FP_ComputerRoom = NULL;
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
		fclose(FP_ComputerRoom);
		//////////////////////////////////////////////////////////////////////////把文件的内容存在链表里
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
		ComputerRoom_Head->ComputerRoom_Next = NULL;
		ComputerRoom_Read = ComputerRoom_Head;
		while (!feof(FP_ComputerRoom)) {      //以尾接法建立一个链表。  feof检测文件是否结束
			ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
			fscanf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);//读出文件当前记录
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
		ComputerRoom_Read->ComputerRoom_Next = NULL;
		fclose(FP_ComputerRoom);
		ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
		/////////////////////////////////////////////////////////////////////////把文件的内容存在链表里
		int QuarryFont_Size = Defaut_Font_Size / 2;
		setfont(QuarryFont_Size, 0, "方正喵呜体", 0, 0, 100, 0, 0, 0);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //初始化
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, 10);
				if (ButtonId == 0)	return 0;
			}
		}
		PIMAGE pimg = newimage();
		getimage(pimg, "990X585.png");
		putimage(0, 0, pimg);
		delimage(pimg);
		DrawPage(Page);
		Show_Online_Login_User();
		int Data1x = 0, Data1y = HeadlineButton.Height + Defaut_Font_Size ;
		int Data2x = WindowsSize.x / 2 - 2 * QuarryFont_Size, Data2y = HeadlineButton.Height + Defaut_Font_Size;
		xyprintf(Data1x, Data1y, "机房名字");
		xyprintf(Data2x, Data2y, "状态");
		int cnt = 0;
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			if(ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State)xyprintf(Data2x, Data2y, "开放" );
			else xyprintf(Data2x, Data2y, "关闭" );
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
			cnt++;
			if (cnt == 19) {
				Data1x += WindowsSize.x / 2; Data1y = HeadlineButton.Height + Defaut_Font_Size;
				Data2x += WindowsSize.x / 2; Data2y = HeadlineButton.Height + Defaut_Font_Size;
			}
		}
	}
	return 1;
}
int Query_BooK() {
	for (; is_run(); delay_fps(270)) {
		FILE* FP_BookData = NULL;
		FP_BookData = fopen("Files\\BookLog.txt", "a");
		fclose(FP_BookData);
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		Books_List Books_Head, Books_Read, Book_Point;
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
			Books_Read->Books_Next = Book_Point;//让用来读的Read的下一个节点指向读到的Point的位置（即让用来临时存数据的Point的数据存到Read里）////Books_Read->Books_Next即Read所指的对象（Head或者新的Head）
			Books_Read = Book_Point;//重置（循环上去会重新malloc）用来读的Read
		}
		//遍历完后，
		Books_Read->Books_Next = NULL;
		fclose(FP_BookData);
		Book_Point = Books_Head->Books_Next;//初始化（让Point指向Head的下一个（所存链表的头））
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int QuarryFont_Size = Defaut_Font_Size / 2;
		setfont(QuarryFont_Size, 0, "方正喵呜体", 0, 0, 100, 0, 0, 0);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //初始化
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, 10);
				if (ButtonId == 0)	return 0;
			}
		}
		PIMAGE pimg = newimage();
		getimage(pimg, "990X585.png");
		putimage(0, 0, pimg);
		delimage(pimg);
		DrawPage(Page);
		Show_Online_Login_User();
		int Data1x = 0, Data1y = HeadlineButton.Height + Defaut_Font_Size;		//Time
		//int Data2x =  8 * QuarryFont_Size, Data2y = HeadlineButton.Height + Defaut_Font_Size;		//Long
		//int Data3x = 12 * QuarryFont_Size, Data3y = HeadlineButton.Height + Defaut_Font_Size;		//User
		//int Data4x = (12 * QuarryFont_Size + WindowsSize.x - 4 * QuarryFont_Size) / 2, Data4y = HeadlineButton.Height + Defaut_Font_Size; 	//BookRoom
		//int Data5x = WindowsSize.x - 4 * QuarryFont_Size, Data5y = HeadlineButton.Height + Defaut_Font_Size;		//BookState
		int Data2x = 8 * QuarryFont_Size, Data2y = HeadlineButton.Height + Defaut_Font_Size;		//Long
		int Data3x = 14 * QuarryFont_Size, Data3y = HeadlineButton.Height + Defaut_Font_Size;		//User
		int Data4x = 20 * QuarryFont_Size, Data4y = HeadlineButton.Height + Defaut_Font_Size; 	//BookCPTfromRoom
		int Data5x = 26 * QuarryFont_Size, Data5y = HeadlineButton.Height + Defaut_Font_Size;		//BookComputer
		int Data6x = 32 * QuarryFont_Size, Data6y = HeadlineButton.Height + Defaut_Font_Size;		//BookState
		xyprintf(Data1x, Data1y, "时间");
		xyprintf(Data2x, Data2y, "时长");
		xyprintf(Data3x, Data3y, "预约人");
		xyprintf(Data4x, Data4y, "预约房间");		
		xyprintf(Data5x, Data5y, "预约机位");
		xyprintf(Data6x, Data6y, "预约状态");
		while (Book_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			Data3y += QuarryFont_Size;
			Data4y += QuarryFont_Size;
			Data5y += QuarryFont_Size;
			Data6y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%04d/%02d/%02d %02d:%02d:%02d", 
					Book_Point->Book_Data.Book_Time.Year, Book_Point->Book_Data.Book_Time.Month, Book_Point->Book_Data.Book_Time.Day,
					Book_Point->Book_Data.Book_Time.Hour, Book_Point->Book_Data.Book_Time.Minute, Book_Point->Book_Data.Book_Time.Second);
			xyprintf(Data2x, Data2y, "%d", Book_Point->Book_Data.Book_Time_Long.Hour);
			xyprintf(Data3x, Data3y, "%s", Book_Point->Book_Data.User_Book_Data.Username);
			xyprintf(Data4x, Data4y, "%s", Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name);
			xyprintf(Data5x, Data5y, "%s", Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name);

			if (Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State==2)xyprintf(Data6x, Data6y, "已上机");
			else if(Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State == 1)	xyprintf(Data6x, Data6y, "已预约");
			else xyprintf(Data6x, Data6y, "未预约");
			Book_Point = Book_Point->Books_Next;
		}

	}
	return 1;
}
//
int Computer_Room_Browse() {	//浏览机房 
	return 1;
}