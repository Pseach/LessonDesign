#include "manage.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

ComputerRoom_List DeleteComputerRoomNode(ComputerRoom_List head, ComputerRoom_Type nodeData,int& state){
	ComputerRoom_List p = head, pr = head;
	if (head == NULL){
		//printf("Linked table is empty!\n");
		state = 0;
		return NULL;
	}
	else {
		p = head;
		while (p->ComputerRoom_Next != NULL && strcmp(p->ComputerRoom_Data.ComputerRoom_Name, nodeData.ComputerRoom_Name) != 0) {
			pr = p;
			p = p->ComputerRoom_Next;
		}
		if (strcmp(p->ComputerRoom_Data.ComputerRoom_Name, nodeData.ComputerRoom_Name) == 0) {
			if (p == head)
				head = p->ComputerRoom_Next;
			else
				pr->ComputerRoom_Next = p->ComputerRoom_Next;
		}
		else {
			//printf("Can not find list num.\n");
			state = 0;
			return NULL;
		}
	}
	state = 1;
	return head;
}

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
			ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));////////////////无论机房开关，都算一个（只按名字来）
			if(fscanf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State))num++;//读出文件当前记录 //读到才num++
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
		fclose(FP_ComputerRoom);
	return num;
}

//根据输入机房，查找是否有对应机位
bool HaveComputerRoom(char Static_ComputerRoomName[]) {//只传数组的话，传过来只是“首地址”
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);

	bool IsHave = 0;
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
	while ((ComputerRoom_Point) && (strcmp(Static_ComputerRoomName, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0) && (1)) {//比对数据
		ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
	}
	if (!ComputerRoom_Point) {    //没找到机房名
		//MessageBox(NULL, TEXT("没找到！"), TEXT("没找到！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave=0;
	}
	else {  //找到了
		//MessageBox(NULL, TEXT("找到了！"), TEXT("找到了！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave = 1;

	}
	return IsHave;
}
bool HaveComputer(char Static_ComputerName[]) {
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Computers);

	bool IsHave = 0;
	ComputerRoom_Type Temp_ComputerRoom = {};
	Computer_Type Temp_Computers = {};
	Computers_List Computers_Head, Computers_Read, Computers_Point;

	FP_Computers = fopen("Files\\Computers.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
	Computers_Head = (Computers_List)malloc(sizeof(Computers_Size));
	Computers_Head->Computers_Next = NULL;
	Computers_Read = Computers_Head;
	while (!feof(FP_Computers)) {      //以尾接法建立一个链表。  feof检测文件是否结束
		Computers_Point = (Computers_List)malloc(sizeof(Computers_Size));
		fscanf(FP_Computers, "FromComputerRoom：%s\tComputer：%s\tComputer_State：%d\n", Temp_ComputerRoom.ComputerRoom_Name, Computers_Point->Computers_Data.Computer_Name, &Temp_Computers.Computer_State);//读出文件当前记录
		Computers_Read->Computers_Next = Computers_Point;
		Computers_Read = Computers_Point;
	}
	Computers_Read->Computers_Next = NULL;
	fclose(FP_Computers);

	Computers_Point = Computers_Head->Computers_Next;
	while ((Computers_Point) && (strcmp(Static_ComputerName, Computers_Point->Computers_Data.Computer_Name) != 0) && (1)) {//比对数据
		Computers_Point = Computers_Point->Computers_Next;
	}
	if (!Computers_Point) {    //没找到机房名
		//MessageBox(NULL, TEXT("没找到！"), TEXT("没找到！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave = 0;
	}
	else {  //找到了
		//MessageBox(NULL, TEXT("找到了！"), TEXT("找到了！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave = 1;
	}
	return IsHave;
}

//用户管理系统
int User_Manage(){				//管理用户

	return 1;
}

int Delete_User() {		//删除用户
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Accounts);
		User_Type Temp_Accounts={};
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;
		enum{isnotDelete,isDelete};
		int state = isnotDelete;
		//int Temp_Type = MessageBox(NULL, TEXT("授予账户管理员权限？"), TEXT("添加用户"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION：问号https://blog.csdn.net/yuyan987/article/details/78558648
		inputbox_getline("请输入所删除账号", "请输入所删除账号", Temp_Accounts.Username, Max_Input_Num);      //输入账号//https://xege.org/manual/api/other/inputboxgetline.htm buffer area
		inputbox_getline("请输入删除账户的密码", "请输入删除账户的密码", Temp_Accounts.Password, Max_Input_Num);      //输入密码
		//Temp_Accounts.Type = (Temp_Type == 6) ? 1 : 0;	 //是(Y) 值为6 否(N)值为7;	//标记用户权限
		//Temp_Accounts.CanBook = 1;

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
		/////////////////////////链表已建立//////////////////////
		
		Accounts_List AccountsHead, AccountsRead, AccountPoint;
		if (AccountsHead = (Accounts_List)malloc(sizeof(Accounts_Size))) {
			AccountsHead->Accounts_Next = NULL;
		}
		AccountsRead = AccountsHead;

		if ((Account_Point))
		//比对数据，没找到相同用户名，且没找完，继续找
		do{

			AccountPoint = (Accounts_List)malloc(sizeof(Accounts_Size));
			if ((strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) == 0)) {

				if ((strcmp(Temp_Accounts.Password, Account_Point->Accounts_Data.Password) == 0)) {
					Account_Point = Account_Point->Accounts_Next;//直接下一个，不读入这条
					state = isDelete;
				}
				else {
					MessageBox(NULL, TEXT("密码不符！"), TEXT("提醒！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
					return 0;
				}
			}
			AccountPoint = Account_Point;
			AccountsRead->Accounts_Next = AccountPoint;
			AccountsRead = AccountPoint;

			if(Account_Point!=NULL)Account_Point = Account_Point->Accounts_Next;

		}while (Account_Point);
		if(AccountsRead!=NULL)AccountsRead->Accounts_Next = NULL;

		AccountPoint = AccountsHead->Accounts_Next;//新链表
	

		FP_Accounts = fopen("Files\\Users.txt", "w");

		if (AccountPoint)
		do{
			fprintf(FP_Accounts, "%s\t%s\t%d\t%d\n", AccountPoint->Accounts_Data.Username, AccountPoint->Accounts_Data.Password, AccountPoint->Accounts_Data.Type, AccountPoint->Accounts_Data.CanBook);

			AccountPoint = AccountPoint->Accounts_Next;
			
		} while (AccountPoint);
		fclose(FP_Accounts);

		if(state)MessageBox(NULL, TEXT("已删除"), TEXT("提醒！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		else MessageBox(NULL, TEXT("查无此人"), TEXT("提醒！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
	return 1;
}

int Transform_User_BookPower() {		//开启|关闭用户预定功能
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Accounts);
	enum { isnotDelete, isDelete };
	int state = isnotDelete;
	User_Type Temp_Accounts{};
	Accounts_List Accounts_Head, Accounts_Read, Accounts_Point;
	FP_Accounts = fopen("Files\\Users.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
	if (Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size))) {
		Accounts_Head->Accounts_Next = NULL;
	}
	//int Temp_Type = MessageBox(NULL, TEXT("授予账户管理员权限？"), TEXT("添加用户"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION：问号https://blog.csdn.net/yuyan987/article/details/78558648
	inputbox_getline("请输入要更改权限的账号", "请输入要更改权限的账号", Temp_Accounts.Username, Max_Input_Num);      

	Accounts_Read = Accounts_Head;
	while (!feof(FP_Accounts)) {      //以尾接法建立一个链表。  feof检测文件是否结束
		if (Accounts_Point = (Accounts_List)malloc(sizeof(Accounts_Size))) {
			fscanf(FP_Accounts, "%s\t%s\t%d\t%d\n", Accounts_Point->Accounts_Data.Username, Accounts_Point->Accounts_Data.Password, &Accounts_Point->Accounts_Data.Type, &Accounts_Point->Accounts_Data.CanBook);//读出文件当前记录
			if (strcmp(Temp_Accounts.Username, Accounts_Point->Accounts_Data.Username) == 0) {
				Accounts_Point->Accounts_Data.CanBook = (Accounts_Point->Accounts_Data.CanBook == 1) ? 0 : 1;
				state = isDelete;
			}
			Accounts_Read->Accounts_Next = Accounts_Point;
			Accounts_Read = Accounts_Point;
		}
	}
	Accounts_Read->Accounts_Next = NULL;
	fclose(FP_Accounts);
	//新链表已建立
	// 下面重新输入到文档（从头写）
	FP_Accounts = fopen("Files\\Users.txt", "w");
	Accounts_Point = Accounts_Head->Accounts_Next;//初始化（让Point指向Head的下一个（所存链表的头））
	while (Accounts_Point) {
		//从头重新输入
		fprintf(FP_Accounts, "%s\t%s\t%d\t%d\n", Accounts_Point->Accounts_Data.Username, Accounts_Point->Accounts_Data.Password, Accounts_Point->Accounts_Data.Type, Accounts_Point->Accounts_Data.CanBook);

		Accounts_Point = Accounts_Point->Accounts_Next;
	}

	if(state)MessageBox(NULL, TEXT("更改成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	else MessageBox(NULL, TEXT("查无此人"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_Accounts);

	return 1;
}
int Change_User() {	//更改用户
	return 1;
}
//机房管理系统
int Computer_Room_Manage(){			//机房管理
	return 1;
}
int Add_Computer_Room() { //添加机房（管理员才能管理？）
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);
	do {	//读取并存储
		ComputerRoom_Type Temp_ComputerRoom = {};
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

		inputbox_getline("请输入要添加机房的名称", "请输入要添加机房的名称", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);      //输入机房名
		Temp_ComputerRoom.ComputerRoom_State = 1;	//创建时标记可用

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

		while ((ComputerRoom_Point) && (strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0) && (1))//比对数据，没找到相同用户名，且没找完，继续找
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

		if (!ComputerRoom_Point) {    //没找到机房名，则以追加的方式写入ComputerRooms.txt文本中，且档次的注册流程完成
			FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a");
			//fprintf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);
			fprintf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", Temp_ComputerRoom.ComputerRoom_Name, Temp_ComputerRoom.ComputerRoom_State);
			fclose(FP_ComputerRoom);
			return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		}
		else {  //找到了，则需要重新输入机房名，再循环刚刚的过程。
			if (MessageBox(NULL, TEXT("重新添加？"), TEXT("机房已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
		}
	} while (1);
}
int Delete_Computer_Room(){	//删除机房
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);

	ComputerRoom_Type Temp_ComputerRoom = {};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point, ComputerRoom_Out;
	
	enum { isnotDelete, isDelete };
	int state = isnotDelete;
	inputbox_getline("请输入所删除机房", "请输入所删除机房", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
	if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
		ComputerRoom_Head->ComputerRoom_Next = NULL;
	}
	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_ComputerRoom)) {      //以尾接法建立一个链表。  feof检测文件是否结束
		if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			fscanf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);//读出文件当前记录
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
	}

	ComputerRoom_Read->ComputerRoom_Next = NULL;
	fclose(FP_ComputerRoom);
	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
	/////////////////////////链表已建立//////////////////////
	ComputerRoom_Out = DeleteComputerRoomNode(ComputerRoom_Point, Temp_ComputerRoom,state);///删除链表

	if (ComputerRoom_Out) {
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "w");
			do {
				fprintf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", ComputerRoom_Out->ComputerRoom_Data.ComputerRoom_Name, ComputerRoom_Out->ComputerRoom_Data.ComputerRoom_State);
				ComputerRoom_Out = ComputerRoom_Out->ComputerRoom_Next;

			} while (ComputerRoom_Out);
		fclose(FP_ComputerRoom);
			if (state)MessageBox(NULL, TEXT("已删除"), TEXT("提醒！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
			else MessageBox(NULL, TEXT("查无此房"), TEXT("提醒！"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
	}
	return 1;
}
int Transform_Computer_Room() {	//开放|关闭机房
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);
	enum { isnotDelete, isDelete };
	int state = isnotDelete;
	ComputerRoom_Type Temp_ComputerRoom{};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
	if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
		ComputerRoom_Head->ComputerRoom_Next = NULL;
	}
	inputbox_getline("请输入要更改状态的机房", "请输入要更改状态的机房", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);

	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_ComputerRoom)) {      //以尾接法建立一个链表。  feof检测文件是否结束
		if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			fscanf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);//读出文件当前记录

			if (strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) == 0) {
				ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State = (ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State == 1) ? 0 : 1;
				state = isDelete;
			}
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
	}
	ComputerRoom_Read->ComputerRoom_Next = NULL;
	fclose(FP_ComputerRoom);

	//新链表已建立
	// 下面重新输入到文档（从头写）
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "w");
	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;//初始化（让Point指向Head的下一个（所存链表的头））
	while (ComputerRoom_Point) {
		//从头重新输入
		fprintf(FP_ComputerRoom, "ComputerRoomName：%s\tState：%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);
		ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
	}

	if (state)MessageBox(NULL, TEXT("更改成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	else MessageBox(NULL, TEXT("查无此房"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_ComputerRoom);
	return 1;
}

int Change_Computer_Room(){	//更改机房
	return 1;
}
//机位管理系统
int Computer_Manage(){			//机位管理
	return 1;
}

int Add_Computer() { //添加机位（管理员才能管理？）
	do{
		//if (ComputerRoom_Num()) {//有机房就执行
			ComputerRoom_Type Temp_ComputerRoom = {}; 
			ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
			inputbox_getline("请输入机位所在机房名称", "请输入机位所在机房名称", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);      //输入所在机房
			if (HaveComputerRoom(Temp_ComputerRoom.ComputerRoom_Name)) {	//检查是否有此机房
				FILE* FP_Computers = NULL;
				FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
				fclose(FP_Computers);
				do {	//读取并存储机位名 
					//Computer_Type Temp_ComputerRoom.Computer_Data = {};
					Computers_List Computers_Head, Computers_Read, Computer_Point;

					inputbox_getline("请输入机位名 ", "请输入机位名 ", Temp_ComputerRoom.Computer_Data.Computer_Name, Max_Input_Num);      //输入机位名
					//Temp_ComputerRoom.Computer_Data.Computer_State = (Temp_Type == 6) ? 1 : 0;	 //是(Y) 值为6 否(N)值为7;
					Temp_ComputerRoom.Computer_Data.Computer_State = 1; // 创建时初始可用
					//Temp_ComputerRoom.Computer_Data.IsPre_Book = 0;
					//Temp_ComputerRoom.Computer_Data.IsFinal_Book = 0;
					
					FP_Computers = fopen("Files\\Computers.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中

					ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_List));
					Computers_Head = (Computers_List)malloc(sizeof(Computers_Size));

					ComputerRoom_Head->ComputerRoom_Next = NULL;
					Computers_Head->Computers_Next = NULL;

					ComputerRoom_Read = ComputerRoom_Head;
					Computers_Read = Computers_Head;

					while (!feof(FP_Computers)) {      //以尾接法建立一个链表。  feof检测文件是否结束
						ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
						Computer_Point = (Computers_List)malloc(sizeof(Computers_Size)); 
						fscanf(FP_Computers, "FromComputerRoom：%s\tComputer：%s\tComputer_State：%d\n", 
							ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, 
							Computer_Point->Computers_Data.Computer_Name, 
							&Computer_Point->Computers_Data.Computer_State);//读出文件当前记录
						
						ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
						Computers_Read->Computers_Next = Computer_Point;

						ComputerRoom_Read = ComputerRoom_Point;
						Computers_Read = Computer_Point;
					}
					ComputerRoom_Read->ComputerRoom_Next = NULL;
					Computers_Read->Computers_Next = NULL;
					fclose(FP_Computers);
					
					ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
					Computer_Point = Computers_Head->Computers_Next;


					while ((ComputerRoom_Point) && (strcmp(Temp_ComputerRoom.Computer_Data.Computer_Name, Computer_Point->Computers_Data.Computer_Name) != 0))//比对数据，没找到相同用户名，且没找完，继续找
						ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

					while ((Computer_Point) && (strcmp(Temp_ComputerRoom.Computer_Data.Computer_Name, Computer_Point->Computers_Data.Computer_Name) != 0))//比对数据，没找到相同用户名，且没找完，继续找
						Computer_Point = Computer_Point->Computers_Next;

					if (!Computer_Point) {    //没找到机位名，则以追加的方式写入Computers.txt文本中，且档次的注册流程完成
						FP_Computers = fopen("Files\\Computers.txt", "a");
						fprintf(FP_Computers, "FromComputerRoom：%s\tComputer：%s\tComputer_State：%d\n", Temp_ComputerRoom.ComputerRoom_Name,Temp_ComputerRoom.Computer_Data.Computer_Name, Temp_ComputerRoom.Computer_Data.Computer_State);
						fclose(FP_Computers);
						return MessageBox(NULL, TEXT("添加成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
					}
					else {  //找到了，则需要重新输入机位名，再循环刚刚的过程。
						if (MessageBox(NULL, TEXT("重新添加？"), TEXT("机位已存在！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND | MB_SETFOREGROUND) == 7)return 1;
					}
				} while (1);
			}
			else {	//如果输入的机房不存在
				if (MessageBox(NULL, TEXT("所输入的机房不存在！是否添加机房？"), TEXT("提醒"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer_Room(); }
				else return 0;//不加就走开
			}		
		//}
		//else if (MessageBox(NULL, TEXT("还没有任何机房！是否添加机房？"), TEXT("提醒"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer_Room(); break;}
		//	 else return 0;//不加就走开
	} while (1);
}
int Delete_Computer(){	//删除机位
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Computers);

	ComputerRoom_Type Temp_ComputerRoom = {};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
	
	enum { isnotDelete, isDelete , FindRoom};
	int state = isnotDelete;
	inputbox_getline("请输入所删除机位所在机房", "请输入所删除机位所在机房", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);      
	inputbox_getline("请输入所删除的机位", "请输入所删除的机位", Temp_ComputerRoom.Computer_Data.Computer_Name, Max_Input_Num);      

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

	ComputerRoom_List ComputerRoomHead, ComputerRoomRead, ComputerRoomPoint;

	if (ComputerRoomHead = (ComputerRoom_List)malloc(sizeof(ComputerRoom_List))) {
		ComputerRoomHead->ComputerRoom_Next = NULL;
	}
	ComputerRoomRead = ComputerRoomHead;
	if ((ComputerRoom_Point))
		//比对数据，没找到相同用户名，且没找完，继续找
		do {
			ComputerRoomPoint = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
			if ((strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) == 0)) {
				if(state != isDelete)state = FindRoom;
				if ((strcmp(Temp_ComputerRoom.Computer_Data.Computer_Name, ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name) == 0)) {
					ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;//直接下一个，不读入这条
					state = isDelete;
				}
			}
			ComputerRoomPoint = ComputerRoom_Point;
			ComputerRoomRead->ComputerRoom_Next = ComputerRoomPoint;
			ComputerRoomRead = ComputerRoomPoint;

			if (ComputerRoom_Point != NULL)ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

		} while (ComputerRoom_Point);
		if (ComputerRoomRead != NULL)ComputerRoomRead->ComputerRoom_Next = NULL;

		ComputerRoomPoint = ComputerRoomHead->ComputerRoom_Next;//新链表

		FP_Computers = fopen("Files\\Computers.txt", "w");

		if (ComputerRoomPoint)
			do {
				fprintf(FP_Computers, "FromComputerRoom：%s\tComputer：%s\tComputer_State：%d\n", 
					ComputerRoomPoint->ComputerRoom_Data.ComputerRoom_Name,
					ComputerRoomPoint->ComputerRoom_Data.Computer_Data.Computer_Name,
					ComputerRoomPoint->ComputerRoom_Data.Computer_Data.Computer_State
				);
				ComputerRoomPoint = ComputerRoomPoint->ComputerRoom_Next;
			} while (ComputerRoomPoint);
			fclose(FP_Computers);

		if (state == isDelete)MessageBox(NULL, TEXT("已删除！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		else if (state == isnotDelete)MessageBox(NULL, TEXT("无此机房"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
		else if (state == FindRoom)MessageBox(NULL, TEXT("查无此机！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);

	return 1;
}
int Transform_Computer() {	//开放|关闭机位
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Computers);

	enum { isnotDelete, isDelete , FindRoom};
	int state = isnotDelete;
	ComputerRoom_Type Temp_ComputerRoom = {};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

	FP_Computers = fopen("Files\\Computers.txt", "r");//先用只读的方式把文件打开，把数据读出来，放在一个序列中
	if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
		ComputerRoom_Head->ComputerRoom_Next = NULL;
	}
	inputbox_getline("请输入要更改状态的机房", "请输入要更改状态的机房", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);
	inputbox_getline("请输入要更改状态的机位", "请输入要更改状态的机位", Temp_ComputerRoom.Computer_Data.Computer_Name, Max_Input_Num);

	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_Computers)) {      //以尾接法建立一个链表。  feof检测文件是否结束
		if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			fscanf(FP_Computers, "FromComputerRoom：%s\tComputer：%s\tComputer_State：%d\n",
				ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name,
				ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name,
				&ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State
			);
			if (strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) == 0) {
				state = FindRoom;
				if (strcmp(Temp_ComputerRoom.Computer_Data.Computer_Name, ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name) == 0) {
					state = isDelete;
					ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State = (ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State == 1) ? 0 : 1;
				}
			}
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
	}
	ComputerRoom_Read->ComputerRoom_Next = NULL;
	fclose(FP_Computers); 
	//新链表已建立
	// 下面重新输入到文档（从头写）
	FP_Computers = fopen("Files\\Computers.txt", "w");
	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;//初始化（让Point指向Head的下一个（所存链表的头））
	while (ComputerRoom_Point) {
		//从头重新输入
		fprintf(FP_Computers, "FromComputerRoom：%s\tComputer：%s\tComputer_State：%d\n",
			ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name,
			ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name,
			ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State
		);
		ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
	}

	if (state== isDelete)MessageBox(NULL, TEXT("更改成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	else if(state== isnotDelete)MessageBox(NULL, TEXT("无此机房"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	else if (state == FindRoom)MessageBox(NULL, TEXT("查无此机！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_Computers);
	return 1;
}

int Change_Computer(){	//更改机位
	return 1;
}
//预定管理
int Search_All_Book(){
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\BookLog.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);
	system("Files\\BookLog.txt");
	return 1;
}
int Agree_ALL_Book() {
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a");
	fclose(FP_BookData);
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

		if ( Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State == 1)
			Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State = 2;

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
	MessageBox(NULL, TEXT("同意预定成功！"), TEXT("提醒"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_BookData);
	return 1;
}