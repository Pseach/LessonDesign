#include "DataIO.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

/** 账户*/
typedef struct {  //系统操作用户的数据结构
	char Username[40];
	char Password[40];
	int Type;	//用户|管理员
	int HaveComputer;
}User_Type;
typedef struct Accounts_Node {  //链表用来存储从文件中读出来的数据
	User_Type Accounts_Data;
	struct Accounts_Node* Accounts_Next;
}Accounts_Size, * Accounts_List;
/** 账户*/

/** 机房*/
typedef struct {  //机房的数据结构
	char ComputerRoom_Name[40];				//机房名字 
	int ComputerRoom_State;				//可用|不可用	1|0
}ComputerRoom_Type;
typedef struct ComputerRoom_Node {
	ComputerRoom_Type ComputerRoom_Data;
	struct ComputerRoom_Node* ComputerRoom_Next;
}ComputerRoom_Size, * ComputerRoom_List;
/** 机房*/

/** 机位*/
typedef struct {  //计算机的数据结构
	char Computer_Name[40];				//计算机名字 
	char Computer_Room[40];				//哪个机房 
	int Computer_State;					//可用|不可用	1|0
	int IsPre_Book;						//被初步预定
	int IsFinal_Book; 					//被最终预定
}Computer_Type;
typedef struct Computers_Node {
	Computer_Type Computers_Data;
	struct Computers_Node* Computers_Next;
}Computers_Size, * Computers_List;
/** 机位*/

int Add_User() { //添加账户
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Accounts);
	do {	//读取并存储账号密码 
		User_Type Temp_Accounts;
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;
		//printf("\n输入用户名和密码\n");
		//scanf("%s%s", Temp_Accounts.Username, Temp_Accounts.Password);

		int Temp_Type = MessageBox(NULL, TEXT("授予账户管理员权限？"), TEXT("用户权限设置"), MB_YESNO | MB_ICONQUESTION);//MB_ICONQUESTION：问号
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
		while (Account_Point && strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) != 0)//比对数据，没找到相同用户名，且没找完，继续找
			Account_Point = Account_Point->Accounts_Next;
		if (!Account_Point) {    //没找到相同用户名，则以追加的方式写入Users.txt文本中，且档次的注册流程完成
			FP_Accounts = fopen("Files\\Users.txt", "a");
			fprintf(FP_Accounts, "%s %s %d %d\n", Temp_Accounts.Username, Temp_Accounts.Password, Temp_Accounts.Type, Temp_Accounts.HaveComputer);
			fclose(FP_Accounts);
			return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK);
		}
		else {  //找到了，则需要重新输入用户名和密码，再循环刚刚的过程。
			//printf("\n用户名已存在，请重新输入！\n");
			//printf("\n输入用户名和密码\n");
			//scanf("%s%s", Temp_Accounts.Username, Temp_Accounts.Password);
			if (MessageBox(NULL, TEXT("重新添加？"), TEXT("用户名已存在！"), MB_YESNO | MB_ICONWARNING) == 7)return 1;
		}
	} while (1);
}

int Add_ComputerRoom() { //添加机房
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);
	do {	//读取并存储账号密码
		ComputerRoom_Type Temp_ComputerRoom;
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
		while (ComputerRoom_Point && strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0)//比对数据，没找到相同用户名，且没找完，继续找
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
		if (!ComputerRoom_Point) {    //没找到机房名，则以追加的方式写入ComputerRooms.txt文本中，且档次的注册流程完成
			FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a");
			fprintf(FP_ComputerRoom, "%s\n", Temp_ComputerRoom.ComputerRoom_Name);
			fclose(FP_ComputerRoom);
			return 1;
		}
		else {  //找到了，则需要重新输入机房名，再循环刚刚的过程。
			if (MessageBox(NULL, TEXT("重新添加？"), TEXT("机房已存在！"), MB_YESNO | MB_ICONWARNING) == 7)return 1;
		}
	} while (1);
}

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
int Add_Computer() { //添加机位
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Computers);
	do {	//读取并存储机位名 
		Computer_Type Temp_Computers;
		Computers_List Computers_Head, Computers_Read, Account_Point;

		//int Temp_Type = MessageBox(NULL, TEXT("授予账户管理员权限？"), TEXT("用户权限设置"), MB_YESNO | MB_ICONQUESTION);//MB_ICONQUESTION：问号

		inputbox_getline("请输入机位名 ", "请输入机位名 ", Temp_Computers.Computer_Name, 40);      //输入机位名
		//Temp_Computers.Computer_State = (Temp_Type == 6) ? 1 : 0;	 //是(Y) 值为6 否(N)值为7;
		Temp_Computers.Computer_State = 1; // 创建时初始可用
		Temp_Computers.IsPre_Book = 0;
		Temp_Computers.IsFinal_Book = 0;

		FP_Computers = fopen("Files\\Computers.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
		Computers_Head = (Computers_List)malloc(sizeof(Computers_Size));
		Computers_Head->Computers_Next = NULL;
		Computers_Read = Computers_Head;
		while (!feof(FP_Computers)) {      //以尾接法建立一个链表。  feof检测文件是否结束
			Account_Point = (Computers_List)malloc(sizeof(Computers_Size));
			fscanf(FP_Computers, "%s\n", Account_Point->Computers_Data.Computer_Name);//读出文件当前记录
			Computers_Read->Computers_Next = Account_Point;
			Computers_Read = Account_Point;
		}
		Computers_Read->Computers_Next = NULL;
		fclose(FP_Computers);

		Account_Point = Computers_Head->Computers_Next;
		while (Account_Point && strcmp(Temp_Computers.Computer_Name, Account_Point->Computers_Data.Computer_Name) != 0)//比对数据，没找到相同用户名，且没找完，继续找
			Account_Point = Account_Point->Computers_Next;
		if (!Account_Point) {    //没找到相同用户名，则以追加的方式写入Computers.txt文本中，且档次的注册流程完成
			FP_Computers = fopen("Files\\Computers.txt", "a");
			fprintf(FP_Computers, "%s\n", Temp_Computers.Computer_Name);
			fclose(FP_Computers);
			return 1;
		}
		else {  //找到了，则需要重新输入用户名和密码，再循环刚刚的过程。
			//printf("\n用户名已存在，请重新输入！\n");
			//printf("\n输入用户名和密码\n");
			//scanf("%s%s", Temp_Computers.Computer_Name, Temp_Computers.Computer_Room);
			if (MessageBox(NULL, TEXT("重新添加？"), TEXT("机位已存在！"), MB_YESNO | MB_ICONWARNING) == 7)return 1;
		}
	} while (1);
}

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


