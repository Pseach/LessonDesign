#include "DataIO.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>



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


