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
		int cnt = 0;
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			Data3y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			xyprintf(Data2x, Data2y, "%s", ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_Name);
			if (ComputerRoom_Point->ComputerRoom_Data.Computer_Data.Computer_State)xyprintf(Data3x, Data3y, "����");
			else xyprintf(Data3x, Data3y, "�ر�");
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
			cnt++;
			if (cnt == 19) {
				Data1x += WindowsSize.x / 2; Data1y = HeadlineButton.Height + Defaut_Font_Size;
				Data2x += WindowsSize.x / 2; Data2y = HeadlineButton.Height + Defaut_Font_Size;
				Data3x += WindowsSize.x / 2; Data3y = HeadlineButton.Height + Defaut_Font_Size;
			}
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
		int Data2x = WindowsSize.x / 2 - 2 * QuarryFont_Size, Data2y = HeadlineButton.Height + Defaut_Font_Size;
		xyprintf(Data1x, Data1y, "��������");
		xyprintf(Data2x, Data2y, "״̬");
		int cnt = 0;
		while (ComputerRoom_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%s", ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_Name);
			if(ComputerRoom_Point->ComputerRoom_Data.ComputerRoom_State)xyprintf(Data2x, Data2y, "����" );
			else xyprintf(Data2x, Data2y, "�ر�" );
			ComputerRoom_Point = ComputerRoom_Point->ComputerRoom_Next;
			cnt++;
			if (cnt == 19) {
				Data1x += WindowsSize.x / 2; Data1y = HeadlineButton.Height + Defaut_Font_Size;
				Data2x += WindowsSize.x / 2; Data2y = HeadlineButton.Height + Defaut_Font_Size;
			}
		}
	}
	return 1;
}
int Query_BooK() {
	for (; is_run(); delay_fps(270)) {
		FILE* FP_BookData = NULL;
		FP_BookData = fopen("Files\\BookLog.txt", "a");
		fclose(FP_BookData);
		////////////////////////////////////////////////////////////////////////////////////////////////////////
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
			Books_Read->Books_Next = Book_Point;//����������Read����һ���ڵ�ָ�������Point��λ�ã�����������ʱ�����ݵ�Point�����ݴ浽Read�////Books_Read->Books_Next��Read��ָ�Ķ���Head�����µ�Head��
			Books_Read = Book_Point;//���ã�ѭ����ȥ������malloc����������Read
		}
		//�������
		Books_Read->Books_Next = NULL;
		fclose(FP_BookData);
		Book_Point = Books_Head->Books_Next;//��ʼ������Pointָ��Head����һ�������������ͷ����
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		int Data1x = 0, Data1y = HeadlineButton.Height + Defaut_Font_Size;		//Time
		//int Data2x =  8 * QuarryFont_Size, Data2y = HeadlineButton.Height + Defaut_Font_Size;		//Long
		//int Data3x = 12 * QuarryFont_Size, Data3y = HeadlineButton.Height + Defaut_Font_Size;		//User
		//int Data4x = (12 * QuarryFont_Size + WindowsSize.x - 4 * QuarryFont_Size) / 2, Data4y = HeadlineButton.Height + Defaut_Font_Size; 	//BookRoom
		//int Data5x = WindowsSize.x - 4 * QuarryFont_Size, Data5y = HeadlineButton.Height + Defaut_Font_Size;		//BookState
		int Data2x = 8 * QuarryFont_Size, Data2y = HeadlineButton.Height + Defaut_Font_Size;		//Long
		int Data3x = 14 * QuarryFont_Size, Data3y = HeadlineButton.Height + Defaut_Font_Size;		//User
		int Data4x = 20 * QuarryFont_Size, Data4y = HeadlineButton.Height + Defaut_Font_Size; 	//BookCPTfromRoom
		int Data5x = 26 * QuarryFont_Size, Data5y = HeadlineButton.Height + Defaut_Font_Size;		//BookComputer
		int Data6x = 32 * QuarryFont_Size, Data6y = HeadlineButton.Height + Defaut_Font_Size;		//BookState
		xyprintf(Data1x, Data1y, "ʱ��");
		xyprintf(Data2x, Data2y, "ʱ��");
		xyprintf(Data3x, Data3y, "ԤԼ��");
		xyprintf(Data4x, Data4y, "ԤԼ����");		
		xyprintf(Data5x, Data5y, "ԤԼ��λ");
		xyprintf(Data6x, Data6y, "ԤԼ״̬");
		while (Book_Point) {
			Data1y += QuarryFont_Size;
			Data2y += QuarryFont_Size;
			Data3y += QuarryFont_Size;
			Data4y += QuarryFont_Size;
			Data5y += QuarryFont_Size;
			Data6y += QuarryFont_Size;
			xyprintf(Data1x, Data1y, "%04d/%02d/%02d %02d:%02d:%02d", 
					Book_Point->Book_Data.Book_Time.Year, Book_Point->Book_Data.Book_Time.Month, Book_Point->Book_Data.Book_Time.Day,
					Book_Point->Book_Data.Book_Time.Hour, Book_Point->Book_Data.Book_Time.Minute, Book_Point->Book_Data.Book_Time.Second);
			xyprintf(Data2x, Data2y, "%d", Book_Point->Book_Data.Book_Time_Long.Hour);
			xyprintf(Data3x, Data3y, "%s", Book_Point->Book_Data.User_Book_Data.Username);
			xyprintf(Data4x, Data4y, "%s", Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name);
			xyprintf(Data5x, Data5y, "%s", Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name);

			if (Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State==2)xyprintf(Data6x, Data6y, "���ϻ�");
			else if(Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State == 1)	xyprintf(Data6x, Data6y, "��ԤԼ");
			else xyprintf(Data6x, Data6y, "δԤԼ");
			Book_Point = Book_Point->Books_Next;
		}

	}
	return 1;
}
//
int Computer_Room_Browse() {	//������� 
	return 1;
}