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
int Computer_Query() {		//��ѯ��λ

	for (; is_run(); delay_fps(270)) {
		FILE* FP_Computers = NULL;
		FP_Computers = fopen("Files\\Computers.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
		fclose(FP_Computers);
		ComputerRoom_List ComputerRoom_Head, ComputerRoom_Read, ComputerRoom_Point;

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
		//Defaut_Font_Size 
		int QuarryFont_Size = Defaut_Font_Size / 2;
		setfont(QuarryFont_Size, 0, "����������", 0, 0, 100, 0, 0, 0);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			// �ж����������£��������ȷ��λ�ã�ͬʱ�ж��Ƿ�Ϊ��ť����
			// ̧����������״̬
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //��ʼ��
				// ����Ƿ��а�ť������
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, 10);
				// �������µİ�ť����Ϊ����״̬
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
		xyprintf(Data1x, Data1y, "����");
		xyprintf(Data2x, Data2y, "����");
		xyprintf(Data3x, Data3y, "״̬");
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			Data3y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			xyprintf(Data2x, Data2y, "%s", ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name);
			if (ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State)xyprintf(Data3x, Data3y, "����");
			else xyprintf(Data3x, Data3y, "�ر�");
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;

		}
	}
	return 1;
}
int Computer_Room_Query() {	//��ѯ����
	for (; is_run(); delay_fps(270)) {
		FILE* FP_ComputerRoom = NULL;
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
		fclose(FP_ComputerRoom);
		//////////////////////////////////////////////////////////////////////////���ļ������ݴ���������
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
		/////////////////////////////////////////////////////////////////////////���ļ������ݴ���������
		int QuarryFont_Size = Defaut_Font_Size / 2;
		setfont(QuarryFont_Size, 0, "����������", 0, 0, 100, 0, 0, 0);
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //��ʼ��
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
		xyprintf(Data1x, Data1y, "��������");
		xyprintf(Data2x, Data2y, "״̬");
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			if(ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State)xyprintf(Data2x, Data2y, "����" );
			else xyprintf(Data2x, Data2y, "�ر�" );
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
		}
	}
	return 1;
}
int Computer_Room_Browse() {	//������� 
	return 1;
}