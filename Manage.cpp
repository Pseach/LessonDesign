#include "manage.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

int Manage() {
	return 1;
}
//返回（CptRom总数）(局部函数
int ComputerRoom_Num() {
	int num = 0;
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在(直接返回num?)，则会创建一个新文件
	fclose(FP_ComputerRoom);
		ComputerRoom_Type Temp_ComputerRoom = {};
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
		ComputerRoom_Head->ComputerRoom_Next = NULL;
		ComputerRoom_Read = ComputerRoom_Head;
		while (!feof(FP_ComputerRoom)) {      //以尾接法建立一个链表。  feof检测文件是否结束
			ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
			if(fscanf(FP_ComputerRoom, "%s\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name))num++;//读出文件当前记录 //读到才num++
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
		fclose(FP_ComputerRoom);
	return num;
}

//用户管理系统
int User_Manage(){				//管理用户
	return 1;
}
int Transform_User_Book(){	//开启|关闭用户预定功能
	return 1;
}
int Delete_User() {		//删除用户
	return 1;
}
int Change_User(){		//更改用户
	return 1;
}
//机房管理系统
int Computer_Room_Manage(){			//机房管理
	return 1;
}
int Transform_Computer_Room(){	//开放|关闭机房
	return 1;
}
int Add_Computer_Room() { //添加机房（管理员才能管理？）
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);
	do {	//读取并存储
		ComputerRoom_Type Temp_ComputerRoom={};
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

		inputbox_getline("请输入机房名称", "请输入机房名称", Temp_ComputerRoom.ComputerRoom_Name, 40);      //输入机房名
		Temp_ComputerRoom.ComputerRoom_State = 1;	//创建时标记可用

		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
		ComputerRoom_Head->ComputerRoom_Next = NULL;
		ComputerRoom_Read = ComputerRoom_Head;
		while (!feof(FP_ComputerRoom)) {      //以尾接法建立一个链表。  feof检测文件是否结束
			ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
			fscanf(FP_ComputerRoom, "%s\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);//读出文件当前记录
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
		ComputerRoom_Read->ComputerRoom_Next = NULL;
		fclose(FP_ComputerRoom);

		ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
		while ((ComputerRoom_Point) && (strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0)&&(1))//比对数据，没找到相同用户名，且没找完，继续找
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
		if (!ComputerRoom_Point) {    //没找到机房名，则以追加的方式写入ComputerRooms.txt文本中，且档次的注册流程完成
			FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a");
			fprintf(FP_ComputerRoom, "%s\n", Temp_ComputerRoom.ComputerRoom_Name);
			fclose(FP_ComputerRoom);
			return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		}
		else {  //找到了，则需要重新输入机房名，再循环刚刚的过程。
			if (MessageBox(NULL, TEXT("重新添加？"), TEXT("机房已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
		}
	} while (1);
}
int Delete_Computer_Room(){	//删除机房
	return 1;
}
int Change_Computer_Room(){	//更改机房
	return 1;
}
//机位管理系统
int Computer_Manage(){			//机位管理
	return 1;
}
int Transform_Computer(){	//开放|关闭机位
	return 1;
}
int Add_Computer() { //添加机位（管理员才能管理？）
	if (ComputerRoom_Num()) {//有机位就执行
		FILE* FP_Computers = NULL;
		FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
		fclose(FP_Computers);
		do {	//读取并存储机位名 
			Computer_Type Temp_Computers = {};
			Computers_List Computers_Head, Computers_Read, Computer_Point;


			inputbox_getline("请输入机位名 ", "请输入机位名 ", Temp_Computers.Computer_Name, 40);      //输入机位名
			//Temp_Computers.Computer_State = (Temp_Type == 6) ? 1 : 0;	 //是(Y) 值为6 否(N)值为7;
			Temp_Computers.Computer_State = 1; // 创建时初始可用
			//Temp_Computers.IsPre_Book = 0;
			//Temp_Computers.IsFinal_Book = 0;

			FP_Computers = fopen("Files\\Computers.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
			Computers_Head = (Computers_List)malloc(sizeof(Computers_Size));
			Computers_Head->Computers_Next = NULL;
			Computers_Read = Computers_Head;
			while (!feof(FP_Computers)) {      //以尾接法建立一个链表。  feof检测文件是否结束
				Computer_Point = (Computers_List)malloc(sizeof(Computers_Size));
				fscanf(FP_Computers, "%s\n", Computer_Point->Computers_Data.Computer_Name);//读出文件当前记录
				Computers_Read->Computers_Next = Computer_Point;
				Computers_Read = Computer_Point;
			}
			Computers_Read->Computers_Next = NULL;
			fclose(FP_Computers);

			Computer_Point = Computers_Head->Computers_Next;
			while ((Computer_Point) && (strcmp(Temp_Computers.Computer_Name, Computer_Point->Computers_Data.Computer_Name) != 0) && (1))//比对数据，没找到相同用户名，且没找完，继续找
				Computer_Point = Computer_Point->Computers_Next;
			if (!Computer_Point) {    //没找到机位名，则以追加的方式写入Computers.txt文本中，且档次的注册流程完成
				FP_Computers = fopen("Files\\Computers.txt", "a");
				fprintf(FP_Computers, "%s\n", Temp_Computers.Computer_Name);
				fclose(FP_Computers);
				return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
			}
			else {  //找到了，则需要重新输入机位名，再循环刚刚的过程。
				if (MessageBox(NULL, TEXT("重新添加？"), TEXT("机位已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND | MB_SETFOREGROUND) == 7)return 1;
			}
		} while (1);
	}
	else if (MessageBox(NULL, TEXT("还没有任何机房！是否添加机房？"), TEXT("提醒"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6)Add_Computer_Room();
		 else return 1;
}
int Delete_Computer(){	//删除机位
	return 1;
}
int Change_Computer(){	//更改机位
	return 1;
}