#include "Query.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

int Query() {
	return 1;
}
int Computer_Query() {		//��ѯ��λ
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Computers);
	system("Files\\BookLog.txt");
	return 1;
}
int Computer_Room_Query() {	//��ѯ����
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_ComputerRoom);
	system("Files\\ComputerRooms.txt");
	return 1;
}
int Computer_Room_Browse() {	//������� 
	return 1;
}