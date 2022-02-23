#include "DataIO.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>



//int Add_ComputerRoom() { //添加机房
//	FILE* FP_ComputerRoom = NULL;
//	ComputerRoom_Type Temp_ComputerRoom;
//	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
//
//	printf("\n清输入添加的机房名字\n");
//	scanf("%s", Temp_ComputerRoom.ComputerRoom_Name);
//
//	FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "r");
//	if (FP_ComputerRoom == NULL) {     //还没有机房时，相当于ComputerRoom.txt 还没创建 。
//		/*fclose(FP_ComputerRoom);*/
//		FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "a+");  //则以追加的方式写入ComputerRoom.txt文本中，且本次的创建流程完成
//		fprintf(FP_ComputerRoom, "%s\n", Temp_ComputerRoom.ComputerRoom_Name);
//		fclose(FP_ComputerRoom);
//		return 1;
//	}
//	else {   //  如果机房已经存在
//		do {
//			FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
//			ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
//			ComputerRoom_Head->ComputerRoom_Next = NULL;
//			ComputerRoom_Read = ComputerRoom_Head;
//			while (!feof(FP_ComputerRoom))       //以尾接法建立一个链表。  feof检测文件是否结束
//			{
//				ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
//				fscanf(FP_ComputerRoom, "%s\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);//读出文件当前记录
//				ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
//				ComputerRoom_Read = ComputerRoom_Point;
//			}
//			ComputerRoom_Read->ComputerRoom_Next = NULL;
//			fclose(FP_ComputerRoom);
//
//			ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
//			while (ComputerRoom_Point && strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0)//比对数据，没找到相同用户名，且没找完，继续找
//				ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
//			if (!ComputerRoom_Point) {    //没找到相同机房，则以追加的方式写入ComputerRoom.txt文本中，且档次的创建流程完成
//				FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "a+");
//				fprintf(FP_ComputerRoom, "%s\n", Temp_ComputerRoom.ComputerRoom_Name);
//				fclose(FP_ComputerRoom);
//				return 1;
//			}
//			else {  //找到相同机房，则需要重新输入机房名，再循环刚刚的过程。
//				printf("\n机房已存在，请重新输入！\n");
//				printf("\n输入机房名\n");
//				scanf("%s", Temp_ComputerRoom.ComputerRoom_Name);
//			}
//		} while (1);
//	}
//
//}


//int Add_Computer() { //添加计算机
//	FILE* FP_Computer = NULL;
//	Computer_Type Temp_Computers;
//	Computers_List Computer_Head, Computer_Read, Computers_Point;
//
//
//	printf("\n清输入添加的计算机名字\n");
//	scanf("%s", Temp_Computers.Computer_Name);
//
//	FP_Computer = fopen("Files\\Computers.txt", "r");
//	if (FP_Computer == NULL) {     //还没有用户表时，相当于Computers.txt 还没创建 。
//		/*fclose(FP_Computer);*/
//		FP_Computer = fopen("Files\\Computers.txt", "a+");  //则以追加的方式写入Users文本中，且本次的注册流程完成
//		fprintf(FP_Computer, "%s\n", Temp_Computers.Computer_Name);
//		fclose(FP_Computer);
//		return 1;
//	}
//	else {   //  如果用户数据已经存在
//		do {
//			FP_Computer = fopen("Files\\Computers.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
//			Computer_Head = (Computers_List)malloc(sizeof(Computers_Size));
//			Computer_Head->Computers_Next = NULL;
//			Computer_Read = Computer_Head;
//			while (!feof(FP_Computer))       //以尾接法建立一个链表。  feof检测文件是否结束
//			{
//				Computers_Point = (Computers_List)malloc(sizeof(Computers_Size));
//				fscanf(FP_Computer, "%s\n", Computers_Point->Computers_Data.Computer_Name);//读出文件当前记录
//				Computer_Read->Computers_Next = Computers_Point;
//				Computer_Read = Computers_Point;
//			}
//			Computer_Read->Computers_Next = NULL;
//			fclose(FP_Computer);
//
//			Computers_Point = Computer_Head->Computers_Next;
//			while (Computers_Point && strcmp(Temp_Computers.Computer_Name, Computers_Point->Computers_Data.Computer_Name) != 0)//比对数据，没找到相同用户名，且没找完，继续找
//				Computers_Point = Computers_Point->Computers_Next;
//			if (!Computers_Point) {    //没找到相同用户名，则以追加的方式写入Computers.txt文本中，且档次的注册流程完成
//				FP_Computer = fopen("Files\\Computers.txt", "a+");
//				fprintf(FP_Computer, "%s\n", Temp_Computers.Computer_Name);
//				fclose(FP_Computer);
//				return 1;
//			}
//			else {  //找到了，则需要重新输入用户名和密码，再循环刚刚的过程。
//				printf("\n计算机已存在，请重新输入！\n");
//				printf("\n清输入添加的计算机名字\n");
//				scanf("%s", Temp_Computers.Computer_Name);
//			}
//		} while (1);
//	}
//
//}

int Login() {
	return 1;
}


