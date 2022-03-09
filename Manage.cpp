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

//���أ�CptRom������(�ֲ�����
int ComputerRoom_Num() {
	int num = 0;
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ�������(ֱ�ӷ���num?)����ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);
		ComputerRoom_Type Temp_ComputerRoom = {};
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
		
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
		ComputerRoom_Head->ComputerRoom_Next = NULL;
		ComputerRoom_Read = ComputerRoom_Head;
		while (!feof(FP_ComputerRoom)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
			ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));////////////////���ۻ������أ�����һ����ֻ����������
			if(fscanf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State))num++;//�����ļ���ǰ��¼ //������num++
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
		fclose(FP_ComputerRoom);
	return num;
}

//������������������Ƿ��ж�Ӧ��λ
bool HaveComputerRoom(char Static_ComputerRoomName[]) {//ֻ������Ļ���������ֻ�ǡ��׵�ַ��
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);

	bool IsHave = 0;
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
	ComputerRoom_Head->ComputerRoom_Next = NULL;
	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_ComputerRoom)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
		ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));

		fscanf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);//�����ļ���ǰ��¼
		ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
		ComputerRoom_Read = ComputerRoom_Point;
	}
	ComputerRoom_Read->ComputerRoom_Next = NULL;
	fclose(FP_ComputerRoom);

	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
	while ((ComputerRoom_Point) && (strcmp(Static_ComputerRoomName, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0) && (1)) {//�ȶ�����
		ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
	}
	if (!ComputerRoom_Point) {    //û�ҵ�������
		//MessageBox(NULL, TEXT("û�ҵ���"), TEXT("û�ҵ���"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave=0;
	}
	else {  //�ҵ���
		//MessageBox(NULL, TEXT("�ҵ��ˣ�"), TEXT("�ҵ��ˣ�"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave = 1;

	}
	return IsHave;
}
bool HaveComputer(char Static_ComputerName[]) {
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Computers);

	bool IsHave = 0;
	ComputerRoom_Type Temp_ComputerRoom = {};
	Computer_Type Temp_Computers = {};
	Computers_List Computers_Head, Computers_Read, Computers_Point;

	FP_Computers = fopen("Files\\Computers.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	Computers_Head = (Computers_List)malloc(sizeof(Computers_Size));
	Computers_Head->Computers_Next = NULL;
	Computers_Read = Computers_Head;
	while (!feof(FP_Computers)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
		Computers_Point = (Computers_List)malloc(sizeof(Computers_Size));
		fscanf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n", Temp_ComputerRoom.ComputerRoom_Name, Computers_Point->Computers_Data.Computer_Name, &Temp_Computers.Computer_State);//�����ļ���ǰ��¼
		Computers_Read->Computers_Next = Computers_Point;
		Computers_Read = Computers_Point;
	}
	Computers_Read->Computers_Next = NULL;
	fclose(FP_Computers);

	Computers_Point = Computers_Head->Computers_Next;
	while ((Computers_Point) && (strcmp(Static_ComputerName, Computers_Point->Computers_Data.Computer_Name) != 0) && (1)) {//�ȶ�����
		Computers_Point = Computers_Point->Computers_Next;
	}
	if (!Computers_Point) {    //û�ҵ�������
		//MessageBox(NULL, TEXT("û�ҵ���"), TEXT("û�ҵ���"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave = 0;
	}
	else {  //�ҵ���
		//MessageBox(NULL, TEXT("�ҵ��ˣ�"), TEXT("�ҵ��ˣ�"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		IsHave = 1;
	}
	return IsHave;
}

//�û�����ϵͳ
int User_Manage(){				//�����û�

	return 1;
}

int Delete_User() {		//ɾ���û�
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Accounts);
		User_Type Temp_Accounts={};
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;
		enum{isnotDelete,isDelete};
		int state = isnotDelete;
		//int Temp_Type = MessageBox(NULL, TEXT("�����˻�����ԱȨ�ޣ�"), TEXT("����û�"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION���ʺ�https://blog.csdn.net/yuyan987/article/details/78558648
		inputbox_getline("��������ɾ���˺�", "��������ɾ���˺�", Temp_Accounts.Username, Max_Input_Num);      //�����˺�//https://xege.org/manual/api/other/inputboxgetline.htm buffer area
		inputbox_getline("������ɾ���˻�������", "������ɾ���˻�������", Temp_Accounts.Password, Max_Input_Num);      //��������
		//Temp_Accounts.Type = (Temp_Type == 6) ? 1 : 0;	 //��(Y) ֵΪ6 ��(N)ֵΪ7;	//����û�Ȩ��
		//Temp_Accounts.CanBook = 1;

		FP_Accounts = fopen("Files\\Users.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		if (Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size))) {
			Accounts_Head->Accounts_Next = NULL;
		}
		Accounts_Read = Accounts_Head;
		while (!feof(FP_Accounts)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
			if (Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size))) {
				fscanf(FP_Accounts, "%s\t%s\t%d\t%d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.CanBook);//�����ļ���ǰ��¼

				Accounts_Read->Accounts_Next = Account_Point;
				Accounts_Read = Account_Point;
			}
		}
		Accounts_Read->Accounts_Next = NULL;
		fclose(FP_Accounts);
		Account_Point = Accounts_Head->Accounts_Next;
		/////////////////////////�����ѽ���//////////////////////
		
		Accounts_List AccountsHead, AccountsRead, AccountPoint;
		if (AccountsHead = (Accounts_List)malloc(sizeof(Accounts_Size))) {
			AccountsHead->Accounts_Next = NULL;
		}
		AccountsRead = AccountsHead;

		if ((Account_Point))
		//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
		do{

			AccountPoint = (Accounts_List)malloc(sizeof(Accounts_Size));
			if ((strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) == 0)) {

				if ((strcmp(Temp_Accounts.Password, Account_Point->Accounts_Data.Password) == 0)) {
					Account_Point = Account_Point->Accounts_Next;//ֱ����һ��������������
					state = isDelete;
				}
				else {
					MessageBox(NULL, TEXT("���벻����"), TEXT("���ѣ�"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
					return 0;
				}
			}
			AccountPoint = Account_Point;
			AccountsRead->Accounts_Next = AccountPoint;
			AccountsRead = AccountPoint;

			if(Account_Point!=NULL)Account_Point = Account_Point->Accounts_Next;

		}while (Account_Point);
		if(AccountsRead!=NULL)AccountsRead->Accounts_Next = NULL;

		AccountPoint = AccountsHead->Accounts_Next;//������
	

		FP_Accounts = fopen("Files\\Users.txt", "w");

		if (AccountPoint)
		do{
			fprintf(FP_Accounts, "%s\t%s\t%d\t%d\n", AccountPoint->Accounts_Data.Username, AccountPoint->Accounts_Data.Password, AccountPoint->Accounts_Data.Type, AccountPoint->Accounts_Data.CanBook);

			AccountPoint = AccountPoint->Accounts_Next;
			
		} while (AccountPoint);
		fclose(FP_Accounts);

		if(state)MessageBox(NULL, TEXT("��ɾ��"), TEXT("���ѣ�"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
		else MessageBox(NULL, TEXT("���޴���"), TEXT("���ѣ�"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
	return 1;
}

int Transform_User_BookPower() {		//����|�ر��û�Ԥ������
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Accounts);
	enum { isnotDelete, isDelete };
	int state = isnotDelete;
	User_Type Temp_Accounts{};
	Accounts_List Accounts_Head, Accounts_Read, Accounts_Point;
	FP_Accounts = fopen("Files\\Users.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	if (Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size))) {
		Accounts_Head->Accounts_Next = NULL;
	}
	//int Temp_Type = MessageBox(NULL, TEXT("�����˻�����ԱȨ�ޣ�"), TEXT("����û�"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION���ʺ�https://blog.csdn.net/yuyan987/article/details/78558648
	inputbox_getline("������Ҫ����Ȩ�޵��˺�", "������Ҫ����Ȩ�޵��˺�", Temp_Accounts.Username, Max_Input_Num);      

	Accounts_Read = Accounts_Head;
	while (!feof(FP_Accounts)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
		if (Accounts_Point = (Accounts_List)malloc(sizeof(Accounts_Size))) {
			fscanf(FP_Accounts, "%s\t%s\t%d\t%d\n", Accounts_Point->Accounts_Data.Username, Accounts_Point->Accounts_Data.Password, &Accounts_Point->Accounts_Data.Type, &Accounts_Point->Accounts_Data.CanBook);//�����ļ���ǰ��¼
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
	//�������ѽ���
	// �����������뵽�ĵ�����ͷд��
	FP_Accounts = fopen("Files\\Users.txt", "w");
	Accounts_Point = Accounts_Head->Accounts_Next;//��ʼ������Pointָ��Head����һ�������������ͷ����
	while (Accounts_Point) {
		//��ͷ��������
		fprintf(FP_Accounts, "%s\t%s\t%d\t%d\n", Accounts_Point->Accounts_Data.Username, Accounts_Point->Accounts_Data.Password, Accounts_Point->Accounts_Data.Type, Accounts_Point->Accounts_Data.CanBook);

		Accounts_Point = Accounts_Point->Accounts_Next;
	}

	if(state)MessageBox(NULL, TEXT("���ĳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	else MessageBox(NULL, TEXT("���޴���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_Accounts);

	return 1;
}
int Change_User() {	//�����û�
	return 1;
}
//��������ϵͳ
int Computer_Room_Manage(){			//��������
	return 1;
}
int Add_Computer_Room() { //��ӻ���������Ա���ܹ�����
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);
	do {	//��ȡ���洢
		ComputerRoom_Type Temp_ComputerRoom = {};
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

		inputbox_getline("������Ҫ��ӻ���������", "������Ҫ��ӻ���������", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);      //���������
		Temp_ComputerRoom.ComputerRoom_State = 1;	//����ʱ��ǿ���

		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
		ComputerRoom_Head->ComputerRoom_Next = NULL;
		ComputerRoom_Read = ComputerRoom_Head;
		while (!feof(FP_ComputerRoom)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
			ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
			fscanf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);//�����ļ���ǰ��¼
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
		ComputerRoom_Read->ComputerRoom_Next = NULL;
		fclose(FP_ComputerRoom);

		ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;

		while ((ComputerRoom_Point) && (strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0) && (1))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

		if (!ComputerRoom_Point) {    //û�ҵ�������������׷�ӵķ�ʽд��ComputerRooms.txt�ı��У��ҵ��ε�ע���������
			FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a");
			//fprintf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);
			fprintf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", Temp_ComputerRoom.ComputerRoom_Name, Temp_ComputerRoom.ComputerRoom_State);
			fclose(FP_ComputerRoom);
			return MessageBox(NULL, TEXT("��ӳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
		}
		else {  //�ҵ��ˣ�����Ҫ�����������������ѭ���ոյĹ��̡�
			if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("�����Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
		}
	} while (1);
}
int Delete_Computer_Room(){	//ɾ������
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);

	ComputerRoom_Type Temp_ComputerRoom = {};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point, ComputerRoom_Out;
	
	enum { isnotDelete, isDelete };
	int state = isnotDelete;
	inputbox_getline("��������ɾ������", "��������ɾ������", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
		ComputerRoom_Head->ComputerRoom_Next = NULL;
	}
	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_ComputerRoom)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
		if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			fscanf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);//�����ļ���ǰ��¼
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
	}

	ComputerRoom_Read->ComputerRoom_Next = NULL;
	fclose(FP_ComputerRoom);
	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
	/////////////////////////�����ѽ���//////////////////////
	ComputerRoom_Out = DeleteComputerRoomNode(ComputerRoom_Point, Temp_ComputerRoom,state);///ɾ������

	if (ComputerRoom_Out) {
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "w");
			do {
				fprintf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", ComputerRoom_Out->ComputerRoom_Data.ComputerRoom_Name, ComputerRoom_Out->ComputerRoom_Data.ComputerRoom_State);
				ComputerRoom_Out = ComputerRoom_Out->ComputerRoom_Next;

			} while (ComputerRoom_Out);
		fclose(FP_ComputerRoom);
			if (state)MessageBox(NULL, TEXT("��ɾ��"), TEXT("���ѣ�"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
			else MessageBox(NULL, TEXT("���޴˷�"), TEXT("���ѣ�"), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
	}
	return 1;
}
int Transform_Computer_Room() {	//����|�رջ���
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);
	enum { isnotDelete, isDelete };
	int state = isnotDelete;
	ComputerRoom_Type Temp_ComputerRoom{};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
		ComputerRoom_Head->ComputerRoom_Next = NULL;
	}
	inputbox_getline("������Ҫ����״̬�Ļ���", "������Ҫ����״̬�Ļ���", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);

	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_ComputerRoom)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
		if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			fscanf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, &ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);//�����ļ���ǰ��¼

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

	//�������ѽ���
	// �����������뵽�ĵ�����ͷд��
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "w");
	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;//��ʼ������Pointָ��Head����һ�������������ͷ����
	while (ComputerRoom_Point) {
		//��ͷ��������
		fprintf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State);
		ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
	}

	if (state)MessageBox(NULL, TEXT("���ĳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	else MessageBox(NULL, TEXT("���޴˷�"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_ComputerRoom);
	return 1;
}

int Change_Computer_Room(){	//���Ļ���
	return 1;
}
//��λ����ϵͳ
int Computer_Manage(){			//��λ����
	return 1;
}

int Add_Computer() { //��ӻ�λ������Ա���ܹ�����
	do{
		//if (ComputerRoom_Num()) {//�л�����ִ��
			ComputerRoom_Type Temp_ComputerRoom = {}; 
			ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
			inputbox_getline("�������λ���ڻ�������", "�������λ���ڻ�������", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);      //�������ڻ���
			if (HaveComputerRoom(Temp_ComputerRoom.ComputerRoom_Name)) {	//����Ƿ��д˻���
				FILE* FP_Computers = NULL;
				FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
				fclose(FP_Computers);
				do {	//��ȡ���洢��λ�� 
					//Computer_Type Temp_ComputerRoom.Computer_Data = {};
					Computers_List Computers_Head, Computers_Read, Computer_Point;

					inputbox_getline("�������λ�� ", "�������λ�� ", Temp_ComputerRoom.Computer_Data.Computer_Name, Max_Input_Num);      //�����λ��
					//Temp_ComputerRoom.Computer_Data.Computer_State = (Temp_Type == 6) ? 1 : 0;	 //��(Y) ֵΪ6 ��(N)ֵΪ7;
					Temp_ComputerRoom.Computer_Data.Computer_State = 1; // ����ʱ��ʼ����
					//Temp_ComputerRoom.Computer_Data.IsPre_Book = 0;
					//Temp_ComputerRoom.Computer_Data.IsFinal_Book = 0;
					
					FP_Computers = fopen("Files\\Computers.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������

					ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_List));
					Computers_Head = (Computers_List)malloc(sizeof(Computers_Size));

					ComputerRoom_Head->ComputerRoom_Next = NULL;
					Computers_Head->Computers_Next = NULL;

					ComputerRoom_Read = ComputerRoom_Head;
					Computers_Read = Computers_Head;

					while (!feof(FP_Computers)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
						ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
						Computer_Point = (Computers_List)malloc(sizeof(Computers_Size)); 
						fscanf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n", 
							ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, 
							Computer_Point->Computers_Data.Computer_Name, 
							&Computer_Point->Computers_Data.Computer_State);//�����ļ���ǰ��¼
						
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


					while ((ComputerRoom_Point) && (strcmp(Temp_ComputerRoom.Computer_Data.Computer_Name, Computer_Point->Computers_Data.Computer_Name) != 0))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
						ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

					while ((Computer_Point) && (strcmp(Temp_ComputerRoom.Computer_Data.Computer_Name, Computer_Point->Computers_Data.Computer_Name) != 0))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
						Computer_Point = Computer_Point->Computers_Next;

					if (!Computer_Point) {    //û�ҵ���λ��������׷�ӵķ�ʽд��Computers.txt�ı��У��ҵ��ε�ע���������
						FP_Computers = fopen("Files\\Computers.txt", "a");
						fprintf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n", Temp_ComputerRoom.ComputerRoom_Name,Temp_ComputerRoom.Computer_Data.Computer_Name, Temp_ComputerRoom.Computer_Data.Computer_State);
						fclose(FP_Computers);
						return MessageBox(NULL, TEXT("��ӳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
					}
					else {  //�ҵ��ˣ�����Ҫ���������λ������ѭ���ոյĹ��̡�
						if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("��λ�Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND | MB_SETFOREGROUND) == 7)return 1;
					}
				} while (1);
			}
			else {	//�������Ļ���������
				if (MessageBox(NULL, TEXT("������Ļ��������ڣ��Ƿ���ӻ�����"), TEXT("����"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer_Room(); }
				else return 0;//���Ӿ��߿�
			}		
		//}
		//else if (MessageBox(NULL, TEXT("��û���κλ������Ƿ���ӻ�����"), TEXT("����"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer_Room(); break;}
		//	 else return 0;//���Ӿ��߿�
	} while (1);
}
int Delete_Computer(){	//ɾ����λ
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Computers);

	ComputerRoom_Type Temp_ComputerRoom = {};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
	
	enum { isnotDelete, isDelete , FindRoom};
	int state = isnotDelete;
	inputbox_getline("��������ɾ����λ���ڻ���", "��������ɾ����λ���ڻ���", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);      
	inputbox_getline("��������ɾ���Ļ�λ", "��������ɾ���Ļ�λ", Temp_ComputerRoom.Computer_Data.Computer_Name, Max_Input_Num);      

	FP_Computers = fopen("Files\\Computers.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
		ComputerRoom_Head->ComputerRoom_Next = NULL;
	}
	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_Computers)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
		if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			
			fscanf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name, &ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State);//�����ļ���ǰ��¼
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
	}
	ComputerRoom_Read->ComputerRoom_Next = NULL;
	fclose(FP_Computers);
	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
	/////////////////////////�����ѽ���//////////////////////

	ComputerRoom_List ComputerRoomHead, ComputerRoomRead, ComputerRoomPoint;

	if (ComputerRoomHead = (ComputerRoom_List)malloc(sizeof(ComputerRoom_List))) {
		ComputerRoomHead->ComputerRoom_Next = NULL;
	}
	ComputerRoomRead = ComputerRoomHead;
	if ((ComputerRoom_Point))
		//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
		do {
			ComputerRoomPoint = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
			if ((strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) == 0)) {
				if(state != isDelete)state = FindRoom;
				if ((strcmp(Temp_ComputerRoom.Computer_Data.Computer_Name, ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name) == 0)) {
					ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;//ֱ����һ��������������
					state = isDelete;
				}
			}
			ComputerRoomPoint = ComputerRoom_Point;
			ComputerRoomRead->ComputerRoom_Next = ComputerRoomPoint;
			ComputerRoomRead = ComputerRoomPoint;

			if (ComputerRoom_Point != NULL)ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

		} while (ComputerRoom_Point);
		if (ComputerRoomRead != NULL)ComputerRoomRead->ComputerRoom_Next = NULL;

		ComputerRoomPoint = ComputerRoomHead->ComputerRoom_Next;//������

		FP_Computers = fopen("Files\\Computers.txt", "w");

		if (ComputerRoomPoint)
			do {
				fprintf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n", 
					ComputerRoomPoint->ComputerRoom_Data.ComputerRoom_Name,
					ComputerRoomPoint->ComputerRoom_Data.Computer_Data.Computer_Name,
					ComputerRoomPoint->ComputerRoom_Data.Computer_Data.Computer_State
				);
				ComputerRoomPoint = ComputerRoomPoint->ComputerRoom_Next;
			} while (ComputerRoomPoint);
			fclose(FP_Computers);

		if (state == isDelete)MessageBox(NULL, TEXT("��ɾ����"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
		else if (state == isnotDelete)MessageBox(NULL, TEXT("�޴˻���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
		else if (state == FindRoom)MessageBox(NULL, TEXT("���޴˻���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);

	return 1;
}
int Transform_Computer() {	//����|�رջ�λ
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Computers);

	enum { isnotDelete, isDelete , FindRoom};
	int state = isnotDelete;
	ComputerRoom_Type Temp_ComputerRoom = {};
	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

	FP_Computers = fopen("Files\\Computers.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	if (ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
		ComputerRoom_Head->ComputerRoom_Next = NULL;
	}
	inputbox_getline("������Ҫ����״̬�Ļ���", "������Ҫ����״̬�Ļ���", Temp_ComputerRoom.ComputerRoom_Name, Max_Input_Num);
	inputbox_getline("������Ҫ����״̬�Ļ�λ", "������Ҫ����״̬�Ļ�λ", Temp_ComputerRoom.Computer_Data.Computer_Name, Max_Input_Num);

	ComputerRoom_Read = ComputerRoom_Head;
	while (!feof(FP_Computers)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
		if (ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size))) {
			fscanf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n",
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
	//�������ѽ���
	// �����������뵽�ĵ�����ͷд��
	FP_Computers = fopen("Files\\Computers.txt", "w");
	ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;//��ʼ������Pointָ��Head����һ�������������ͷ����
	while (ComputerRoom_Point) {
		//��ͷ��������
		fprintf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n",
			ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name,
			ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name,
			ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State
		);
		ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
	}

	if (state== isDelete)MessageBox(NULL, TEXT("���ĳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	else if(state== isnotDelete)MessageBox(NULL, TEXT("�޴˻���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	else if (state == FindRoom)MessageBox(NULL, TEXT("���޴˻���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_Computers);
	return 1;
}

int Change_Computer(){	//���Ļ�λ
	return 1;
}
//Ԥ������
int Search_All_Book(){
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\BookLog.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);
	system("Files\\BookLog.txt");
	return 1;
}
int Agree_ALL_Book() {
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a");
	fclose(FP_BookData);
	Books_List Books_Head, Books_Read, Book_Point;

	FP_BookData = fopen("Files\\BookLog.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
	if (Books_Head = (Books_List)malloc(sizeof(Books_Size))) {
		Books_Head->Books_Next = NULL;
	}//��ʼ��ͷ�ڵ�
	Books_Read = Books_Head;//��Readָ������ͷ
	while (!feof(FP_BookData)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����	%02d-%02d-%02d
		Book_Point = (Books_List)malloc(sizeof(Books_Size));
		fscanf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long��%d UserName��%s BookRoom��%s BookComputer��%s BookState��%d\n",
			&Book_Point->Book_Data.Book_Time.Year, &Book_Point->Book_Data.Book_Time.Month, &Book_Point->Book_Data.Book_Time.Day,
			&Book_Point->Book_Data.Book_Time.Hour, &Book_Point->Book_Data.Book_Time.Minute, &Book_Point->Book_Data.Book_Time.Second,
			&Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
			Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
			Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
			&Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//Ӧ�������
		);//�����ļ���ǰ��¼

		if ( Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State == 1)
			Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State = 2;

		Books_Read->Books_Next = Book_Point;//����������Read����һ���ڵ�ָ�������Point��λ�ã�����������ʱ�����ݵ�Point�����ݴ浽Read�////Books_Read->Books_Next��Read��ָ�Ķ���Head�����µ�Head��
		Books_Read = Book_Point;//���ã�ѭ����ȥ������malloc����������Read
	}
	//�������
	Books_Read->Books_Next = NULL;//��ʼ��
	fclose(FP_BookData);

	//�������ѽ���
	// �����������뵽�ĵ�����ͷд��
	//��w��ɾ����д
	FP_BookData = fopen("Files\\BookLog.txt", "w");
	Book_Point = Books_Head->Books_Next;//��ʼ������Pointָ��Head����һ�������������ͷ����
	while (Book_Point) {
		//��ͷ��������
		fprintf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long��%d UserName��%s BookRoom��%s BookComputer��%s BookState��%d\n",
			Book_Point->Book_Data.Book_Time.Year, Book_Point->Book_Data.Book_Time.Month, Book_Point->Book_Data.Book_Time.Day,
			Book_Point->Book_Data.Book_Time.Hour, Book_Point->Book_Data.Book_Time.Minute, Book_Point->Book_Data.Book_Time.Second,
			Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
			Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
			Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
			Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//Ӧ�������
		);//��¼(�ӵ����)
		Book_Point = Book_Point->Books_Next;
	}
	MessageBox(NULL, TEXT("ͬ��Ԥ���ɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	fclose(FP_BookData);
	return 1;
}