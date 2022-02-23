#include "DataIO.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

/** �˻�*/
typedef struct {  //ϵͳ�����û������ݽṹ
	char Username[40];
	char Password[40];
	int Type;	//�û�|����Ա
	int HaveComputer;
}User_Type;
typedef struct Accounts_Node {  //���������洢���ļ��ж�����������
	User_Type Accounts_Data;
	struct Accounts_Node* Accounts_Next;
}Accounts_Size, * Accounts_List;
/** �˻�*/

/** ����*/
typedef struct {  //���������ݽṹ
	char ComputerRoom_Name[40];				//�������� 
	int ComputerRoom_State;				//����|������	1|0
}ComputerRoom_Type;
typedef struct ComputerRoom_Node {
	ComputerRoom_Type ComputerRoom_Data;
	struct ComputerRoom_Node* ComputerRoom_Next;
}ComputerRoom_Size, * ComputerRoom_List;
/** ����*/

/** ��λ*/
typedef struct {  //����������ݽṹ
	char Computer_Name[40];				//��������� 
	char Computer_Room[40];				//�ĸ����� 
	int Computer_State;					//����|������	1|0
	int IsPre_Book;						//������Ԥ��
	int IsFinal_Book; 					//������Ԥ��
}Computer_Type;
typedef struct Computers_Node {
	Computer_Type Computers_Data;
	struct Computers_Node* Computers_Next;
}Computers_Size, * Computers_List;
/** ��λ*/

int Add_User() { //����˻�
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Accounts);
	do {	//��ȡ���洢�˺����� 
		User_Type Temp_Accounts;
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;
		//printf("\n�����û���������\n");
		//scanf("%s%s", Temp_Accounts.Username, Temp_Accounts.Password);

		int Temp_Type = MessageBox(NULL, TEXT("�����˻�����ԱȨ�ޣ�"), TEXT("�û�Ȩ������"), MB_YESNO | MB_ICONQUESTION);//MB_ICONQUESTION���ʺ�
		inputbox_getline("�������˺�", "�������˺�", Temp_Accounts.Username, 40);      //�����˺�//https://xege.org/manual/api/other/inputboxgetline.htm buffer area
		inputbox_getline("����������", "����������", Temp_Accounts.Password, 40);      //��������
		Temp_Accounts.Type = (Temp_Type == 6) ? 1 : 0;	 //��(Y) ֵΪ6 ��(N)ֵΪ7;	//����û�Ȩ��
		Temp_Accounts.HaveComputer = 0;

		FP_Accounts = fopen("Files\\Users.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size));
		Accounts_Head->Accounts_Next = NULL;
		Accounts_Read = Accounts_Head;
		while (!feof(FP_Accounts)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
			Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size));
			fscanf(FP_Accounts, "%s %s %d %d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.HaveComputer);//�����ļ���ǰ��¼
			Accounts_Read->Accounts_Next = Account_Point;
			Accounts_Read = Account_Point;
		}
		Accounts_Read->Accounts_Next = NULL;
		fclose(FP_Accounts);

		Account_Point = Accounts_Head->Accounts_Next;
		while (Account_Point && strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) != 0)//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
			Account_Point = Account_Point->Accounts_Next;
		if (!Account_Point) {    //û�ҵ���ͬ�û���������׷�ӵķ�ʽд��Users.txt�ı��У��ҵ��ε�ע���������
			FP_Accounts = fopen("Files\\Users.txt", "a");
			fprintf(FP_Accounts, "%s %s %d %d\n", Temp_Accounts.Username, Temp_Accounts.Password, Temp_Accounts.Type, Temp_Accounts.HaveComputer);
			fclose(FP_Accounts);
			return MessageBox(NULL, TEXT("��ӳɹ���"), TEXT("����"), MB_OK);
		}
		else {  //�ҵ��ˣ�����Ҫ���������û��������룬��ѭ���ոյĹ��̡�
			//printf("\n�û����Ѵ��ڣ����������룡\n");
			//printf("\n�����û���������\n");
			//scanf("%s%s", Temp_Accounts.Username, Temp_Accounts.Password);
			if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("�û����Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING) == 7)return 1;
		}
	} while (1);
}

int Add_ComputerRoom() { //��ӻ���
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);
	do {	//��ȡ���洢�˺�����
		ComputerRoom_Type Temp_ComputerRoom;
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;


		inputbox_getline("�������������", "�������������", Temp_ComputerRoom.ComputerRoom_Name, 40);      //���������
		Temp_ComputerRoom.ComputerRoom_State = 1;	//����ʱ��ǿ���

		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
		ComputerRoom_Head->ComputerRoom_Next = NULL;
		ComputerRoom_Read = ComputerRoom_Head;
		while (!feof(FP_ComputerRoom)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
			ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
			fscanf(FP_ComputerRoom, "%s\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);//�����ļ���ǰ��¼
			ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
			ComputerRoom_Read = ComputerRoom_Point;
		}
		ComputerRoom_Read->ComputerRoom_Next = NULL;
		fclose(FP_ComputerRoom);

		ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
		while (ComputerRoom_Point && strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0)//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
		if (!ComputerRoom_Point) {    //û�ҵ�������������׷�ӵķ�ʽд��ComputerRooms.txt�ı��У��ҵ��ε�ע���������
			FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a");
			fprintf(FP_ComputerRoom, "%s\n", Temp_ComputerRoom.ComputerRoom_Name);
			fclose(FP_ComputerRoom);
			return 1;
		}
		else {  //�ҵ��ˣ�����Ҫ�����������������ѭ���ոյĹ��̡�
			if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("�����Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING) == 7)return 1;
		}
	} while (1);
}

//int Add_ComputerRoom() { //��ӻ���
//	FILE* FP_ComputerRoom = NULL;
//	ComputerRoom_Type Temp_ComputerRoom;
//	ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
//
//	printf("\n��������ӵĻ�������\n");
//	scanf("%s", Temp_ComputerRoom.ComputerRoom_Name);
//
//	FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "r");
//	if (FP_ComputerRoom == NULL) {     //��û�л���ʱ���൱��ComputerRoom.txt ��û���� ��
//		/*fclose(FP_ComputerRoom);*/
//		FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "a+");  //����׷�ӵķ�ʽд��ComputerRoom.txt�ı��У��ұ��εĴ����������
//		fprintf(FP_ComputerRoom, "%s\n", Temp_ComputerRoom.ComputerRoom_Name);
//		fclose(FP_ComputerRoom);
//		return 1;
//	}
//	else {   //  ��������Ѿ�����
//		do {
//			FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
//			ComputerRoom_Head = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
//			ComputerRoom_Head->ComputerRoom_Next = NULL;
//			ComputerRoom_Read = ComputerRoom_Head;
//			while (!feof(FP_ComputerRoom))       //��β�ӷ�����һ������  feof����ļ��Ƿ����
//			{
//				ComputerRoom_Point = (ComputerRoom_List)malloc(sizeof(ComputerRoom_Size));
//				fscanf(FP_ComputerRoom, "%s\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);//�����ļ���ǰ��¼
//				ComputerRoom_Read->ComputerRoom_Next = ComputerRoom_Point;
//				ComputerRoom_Read = ComputerRoom_Point;
//			}
//			ComputerRoom_Read->ComputerRoom_Next = NULL;
//			fclose(FP_ComputerRoom);
//
//			ComputerRoom_Point = ComputerRoom_Head->ComputerRoom_Next;
//			while (ComputerRoom_Point && strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0)//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
//				ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
//			if (!ComputerRoom_Point) {    //û�ҵ���ͬ����������׷�ӵķ�ʽд��ComputerRoom.txt�ı��У��ҵ��εĴ����������
//				FP_ComputerRoom = fopen("Files\\ComputerRoom.txt", "a+");
//				fprintf(FP_ComputerRoom, "%s\n", Temp_ComputerRoom.ComputerRoom_Name);
//				fclose(FP_ComputerRoom);
//				return 1;
//			}
//			else {  //�ҵ���ͬ����������Ҫ�����������������ѭ���ոյĹ��̡�
//				printf("\n�����Ѵ��ڣ����������룡\n");
//				printf("\n���������\n");
//				scanf("%s", Temp_ComputerRoom.ComputerRoom_Name);
//			}
//		} while (1);
//	}
//
//}
int Add_Computer() { //��ӻ�λ
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Computers);
	do {	//��ȡ���洢��λ�� 
		Computer_Type Temp_Computers;
		Computers_List Computers_Head, Computers_Read, Account_Point;

		//int Temp_Type = MessageBox(NULL, TEXT("�����˻�����ԱȨ�ޣ�"), TEXT("�û�Ȩ������"), MB_YESNO | MB_ICONQUESTION);//MB_ICONQUESTION���ʺ�

		inputbox_getline("�������λ�� ", "�������λ�� ", Temp_Computers.Computer_Name, 40);      //�����λ��
		//Temp_Computers.Computer_State = (Temp_Type == 6) ? 1 : 0;	 //��(Y) ֵΪ6 ��(N)ֵΪ7;
		Temp_Computers.Computer_State = 1; // ����ʱ��ʼ����
		Temp_Computers.IsPre_Book = 0;
		Temp_Computers.IsFinal_Book = 0;

		FP_Computers = fopen("Files\\Computers.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		Computers_Head = (Computers_List)malloc(sizeof(Computers_Size));
		Computers_Head->Computers_Next = NULL;
		Computers_Read = Computers_Head;
		while (!feof(FP_Computers)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
			Account_Point = (Computers_List)malloc(sizeof(Computers_Size));
			fscanf(FP_Computers, "%s\n", Account_Point->Computers_Data.Computer_Name);//�����ļ���ǰ��¼
			Computers_Read->Computers_Next = Account_Point;
			Computers_Read = Account_Point;
		}
		Computers_Read->Computers_Next = NULL;
		fclose(FP_Computers);

		Account_Point = Computers_Head->Computers_Next;
		while (Account_Point && strcmp(Temp_Computers.Computer_Name, Account_Point->Computers_Data.Computer_Name) != 0)//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
			Account_Point = Account_Point->Computers_Next;
		if (!Account_Point) {    //û�ҵ���ͬ�û���������׷�ӵķ�ʽд��Computers.txt�ı��У��ҵ��ε�ע���������
			FP_Computers = fopen("Files\\Computers.txt", "a");
			fprintf(FP_Computers, "%s\n", Temp_Computers.Computer_Name);
			fclose(FP_Computers);
			return 1;
		}
		else {  //�ҵ��ˣ�����Ҫ���������û��������룬��ѭ���ոյĹ��̡�
			//printf("\n�û����Ѵ��ڣ����������룡\n");
			//printf("\n�����û���������\n");
			//scanf("%s%s", Temp_Computers.Computer_Name, Temp_Computers.Computer_Room);
			if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("��λ�Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING) == 7)return 1;
		}
	} while (1);
}

//int Add_Computer() { //��Ӽ����
//	FILE* FP_Computer = NULL;
//	Computer_Type Temp_Computers;
//	Computers_List Computer_Head, Computer_Read, Computers_Point;
//
//
//	printf("\n��������ӵļ��������\n");
//	scanf("%s", Temp_Computers.Computer_Name);
//
//	FP_Computer = fopen("Files\\Computers.txt", "r");
//	if (FP_Computer == NULL) {     //��û���û���ʱ���൱��Computers.txt ��û���� ��
//		/*fclose(FP_Computer);*/
//		FP_Computer = fopen("Files\\Computers.txt", "a+");  //����׷�ӵķ�ʽд��Users�ı��У��ұ��ε�ע���������
//		fprintf(FP_Computer, "%s\n", Temp_Computers.Computer_Name);
//		fclose(FP_Computer);
//		return 1;
//	}
//	else {   //  ����û������Ѿ�����
//		do {
//			FP_Computer = fopen("Files\\Computers.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
//			Computer_Head = (Computers_List)malloc(sizeof(Computers_Size));
//			Computer_Head->Computers_Next = NULL;
//			Computer_Read = Computer_Head;
//			while (!feof(FP_Computer))       //��β�ӷ�����һ������  feof����ļ��Ƿ����
//			{
//				Computers_Point = (Computers_List)malloc(sizeof(Computers_Size));
//				fscanf(FP_Computer, "%s\n", Computers_Point->Computers_Data.Computer_Name);//�����ļ���ǰ��¼
//				Computer_Read->Computers_Next = Computers_Point;
//				Computer_Read = Computers_Point;
//			}
//			Computer_Read->Computers_Next = NULL;
//			fclose(FP_Computer);
//
//			Computers_Point = Computer_Head->Computers_Next;
//			while (Computers_Point && strcmp(Temp_Computers.Computer_Name, Computers_Point->Computers_Data.Computer_Name) != 0)//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
//				Computers_Point = Computers_Point->Computers_Next;
//			if (!Computers_Point) {    //û�ҵ���ͬ�û���������׷�ӵķ�ʽд��Computers.txt�ı��У��ҵ��ε�ע���������
//				FP_Computer = fopen("Files\\Computers.txt", "a+");
//				fprintf(FP_Computer, "%s\n", Temp_Computers.Computer_Name);
//				fclose(FP_Computer);
//				return 1;
//			}
//			else {  //�ҵ��ˣ�����Ҫ���������û��������룬��ѭ���ոյĹ��̡�
//				printf("\n������Ѵ��ڣ����������룡\n");
//				printf("\n��������ӵļ��������\n");
//				scanf("%s", Temp_Computers.Computer_Name);
//			}
//		} while (1);
//	}
//
//}

int Login() {
	return 1;
}


