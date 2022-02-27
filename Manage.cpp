#include "manage.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

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

//bool HaveComputerFromRoom(char Static_ComputerName[]) {
//
//	return 1;
//}
//�û�����ϵͳ
int User_Manage(){				//�����û�
	return 1;
}
int Transform_User_Book(){	//����|�ر��û�Ԥ������
	return 1;
}
int Delete_User() {		//ɾ���û�
	return 1;
}
int Change_User(){		//�����û�
	return 1;
}
//��������ϵͳ
int Computer_Room_Manage(){			//��������
	return 1;
}
int Transform_Computer_Room(){	//����|�رջ���
	return 1;
}
int Add_Computer_Room() { //��ӻ���������Ա���ܹ�����
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);
	do {	//��ȡ���洢
		ComputerRoom_Type Temp_ComputerRoom={};
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
		
		inputbox_getline("������Ҫ��ӻ���������", "������Ҫ��ӻ���������", Temp_ComputerRoom.ComputerRoom_Name, 40);      //���������
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

		while ((ComputerRoom_Point) && (strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0)&&(1))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
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
	return 1;
}
int Change_Computer_Room(){	//���Ļ���
	return 1;
}
//��λ����ϵͳ
int Computer_Manage(){			//��λ����
	return 1;
}
int Transform_Computer(){	//����|�رջ�λ
	return 1;
}
int Add_Computer() { //��ӻ�λ������Ա���ܹ�����
	do{
		//if (ComputerRoom_Num()) {//�л�����ִ��
			ComputerRoom_Type Temp_ComputerRoom = {}; 
			ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;
			inputbox_getline("�������λ���ڻ�������", "�������λ���ڻ�������", Temp_ComputerRoom.ComputerRoom_Name, 40);      //�������ڻ���
			if (HaveComputerRoom(Temp_ComputerRoom.ComputerRoom_Name)) {	//����Ƿ��д˻���
				FILE* FP_Computers = NULL;
				FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
				fclose(FP_Computers);
				do {	//��ȡ���洢��λ�� 
					//Computer_Type Temp_ComputerRoom.Computer_Data = {};
					Computers_List Computers_Head, Computers_Read, Computer_Point;

					inputbox_getline("�������λ�� ", "�������λ�� ", Temp_ComputerRoom.Computer_Data.Computer_Name, 40);      //�����λ��
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
						fscanf(FP_Computers, "FromComputerRoom��%s\tComputer��%s\tComputer_State��%d\n", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name, Computer_Point->Computers_Data.Computer_Name, &Computer_Point->Computers_Data.Computer_State);//�����ļ���ǰ��¼
						
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


					//while ((ComputerRoom_Point) && (strcmp(Temp_ComputerRoom.ComputerRoom_Name, ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name) != 0) && (1))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������


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
	return 1;
}
int Change_Computer(){	//���Ļ�λ
	return 1;
}