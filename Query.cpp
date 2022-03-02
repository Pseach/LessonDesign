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
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			Data3y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			xyprintf(Data2x, Data2y, "%s", ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name);
			if (ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State)xyprintf(Data3x, Data3y, "开放");
			else xyprintf(Data3x, Data3y, "关闭");
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

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
		int Data2x = WindowsSize.x / 2, Data2y = HeadlineButton.Height + Defaut_Font_Size;
		xyprintf(Data1x, Data1y, "机房名字");
		xyprintf(Data2x, Data2y, "状态");
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			if(ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State)xyprintf(Data2x, Data2y, "开放" );
			else xyprintf(Data2x, Data2y, "关闭" );
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
		}
	}
	return 1;
}
int Computer_Room_Browse() {	//浏览机房 
	return 1;
}