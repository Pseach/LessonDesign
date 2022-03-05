#include "AccountControl.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Buttons.h"
#include "DataInput.h"
#include <ege/sys_edit.h>

//extern User_Type Temp_User;

int Show_Online_Login_User() {	//��ʾ��ǰ�˻�

	//LPCSTR Font1="\u65b9\u6b63\u55b5\u545c\u4f53";		
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // ������ɫ
	setfont(Defaut_Font_Size, 0, "����������");					//�����С  ��ȱ�������Ӧ  �����ļ�

	//settextjustify(CENTER_TEXT, CENTER_TEXT);//���־��У��Ժ�����ع������õ�

	//��ʾ��ǰ�˻���
	ege_line(0, 1, HeadlineButton.Width, 1);
	ege_line(0, HeadlineButton.Height, HeadlineButton.Width, HeadlineButton.Height);	//�����ı߿�

	drawRectButton(&HeadlineButton);	//������ʱ������
	xyprintf(HeadlineButton.Height * 1 / 5 / 2, HeadlineButton.Height * 1 / 5 / 2, "��ǰ�˻�:");//����ǰ�˻���"

	drawRectButton(&ShowOnline_Login_User);	//������ʱ������
	xyprintf(ShowOnline_Login_User.X, ShowOnline_Login_User.Y, "%s", Temp_User.Username); //��½�˻�Ϊ" "

	/////////////////////////////////////////////////////////////////////ʱ����ʾ-----��Ϊÿ��ҳ��ˢ�¶�����������������Ծͱ�ɾ�̬����
	time_t timep;
	struct tm* Time_Point;
	time(&timep);
	Time_Point = gmtime(&timep);
	//Temp_Book.Book_Time.Year = Time_Point->tm_year + 1900;
	//Temp_Book.Book_Time.Month = Time_Point->tm_mon + 1;
	//Temp_Book.Book_Time.Day = Time_Point->tm_mday;
	xyprintf(WindowsSize.x - 4 * Defaut_Font_Size, HeadlineButton.Height * 1 / 5 / 2, "%02d:%02d:%02d", ((Time_Point->tm_hour + 8) >= 24) ? (Time_Point->tm_hour + 8 - 24) : (Time_Point->tm_hour + 8), Time_Point->tm_min, Time_Point->tm_sec);
	/////////////////////////////////////////////////////////////////////ʱ����ʾ

	{ 
		int RemindFont_Size = Defaut_Font_Size / 2;
		setfont(RemindFont_Size, 0, "����������", 0, 0, 100, 0, 0, 0);
		setcolor(BLACK);
		//setcolor(WHITE);

		switch(Temp_User.Type){			//�����û���ȫ�ֱ����ṹ����ʾ��ǰ���û�����
			case -1: {	//δ֪
				xyprintf(0, HeadlineButton.Height + RemindFont_Size / 2, "���¼��");//4����	//���Ͻ�
				//xyprintf(HeadlineButton.Height / 5, HeadlineButton.Height + RemindFont_Size / 2, "���¼��");//4����	//���Ͻ�
				//xyprintf(HeadlineButton.Width - 4 * RemindFont_Size, HeadlineButton.Height + RemindFont_Size / 2, "���¼��");//4����	//���Ͻ�
				//xyprintf(HeadlineButton.width - 4 * RemindFont_Size, WindowsSize.y - RemindFont_Size * 3 / 2, "���¼��");//4����		//���½�
				break;
			}
			case 0: {	//��ͨ�û�
				xyprintf(0, HeadlineButton.Height + RemindFont_Size / 2, "�𾴵��û����ã�");//8����
				//xyprintf(HeadlineButton.X / 5, HeadlineButton.Height + RemindFont_Size / 2, "�𾴵��û����ã�");//8����
				//xyprintf(HeadlineButton.Width - 8 * RemindFont_Size, HeadlineButton.Height + RemindFont_Size / 2, "�𾴵��û����ã�");//8����
				//xyprintf(HeadlineButton.width - 8 * RemindFont_Size, WindowsSize.y - RemindFont_Size * 3 / 2, "�𾴵��û����ã�");//8����
				break;
			}
			case 1: {	//����Ա
				xyprintf(0, HeadlineButton.Height + RemindFont_Size / 2, "�𾴵Ĺ���Ա���ã�");//9����
				//xyprintf(HeadlineButton.X / 5, HeadlineButton.Height + RemindFont_Size / 2, "�𾴵Ĺ���Ա���ã�");//9����
				//xyprintf(HeadlineButton.Width - 9 * RemindFont_Size, HeadlineButton.Height + RemindFont_Size / 2, "�𾴵Ĺ���Ա���ã�");//9����
				//xyprintf(HeadlineButton.width - 9 * RemindFont_Size, WindowsSize.y - RemindFont_Size * 3 / 2, "�𾴵Ĺ���Ա���ã�");//9����
				break;
			}
		}
	}
	return 1;
}

int Add_User() { //ע��/����û�
	FILE* FP_Accounts = NULL;
	FP_Accounts = fopen("Files\\Users.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
	fclose(FP_Accounts);
	do {	//��ȡ���洢�˺����� 
		User_Type Temp_Accounts{};	//����ȡ�����ݴ��ڴ�
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		int Temp_Type = MessageBox(NULL, TEXT("�����˻�����ԱȨ�ޣ�"), TEXT("����û�"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION���ʺ�https://blog.csdn.net/yuyan987/article/details/78558648
		sys_edit editBox;

		inputbox_getline("�������˺�", "�������˺�", Temp_Accounts.Username, Max_Input_Num);      //�����˺�//https://xege.org/manual/api/other/inputboxgetline.htm buffer area
		//strcpy(Temp_Accounts.Username,My_InputBox_One_Line(&editBox));

		inputbox_getline("����������", "����������", Temp_Accounts.Password, Max_Input_Num);      //��������
		Temp_Accounts.Type = (Temp_Type == 6) ? 1 : 0;	 //��(Y) ֵΪ6 ��(N)ֵΪ7;	//����û�Ȩ��
		Temp_Accounts.CanBook = 1;
		/////////////////////////////////////////////////////////////////////////////��������
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
		///////////////////////////////////////////////////////////////////////////��������Point

		while ((Account_Point) && (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) != 0) && (1))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
			Account_Point = Account_Point->Accounts_Next;
		if (!Account_Point) {    //û�ҵ���ͬ�û���������׷�ӵķ�ʽд��Users.txt�ı��У��ҵ��ε�ע���������
			FP_Accounts = fopen("Files\\Users.txt", "a");
			fprintf(FP_Accounts, "%s\t%s\t%d\t%d\n", Temp_Accounts.Username, Temp_Accounts.Password, Temp_Accounts.Type, Temp_Accounts.CanBook);
			fclose(FP_Accounts);
			return MessageBox(NULL, TEXT("��ӳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
		}
		else {  //�ҵ��ˣ�����Ҫ���������û��������룬��ѭ���ոյĹ��̡�
			if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("�û����Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
		}
	} while (1);
}

int Login_User(){        	    //��¼
	if (Temp_User.Logined) { //�ѵ�¼
		MessageBox(NULL, TEXT("���ѵ�¼��"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	else {
		FILE* FP_Accounts = NULL;
		FP_Accounts = fopen("Files\\Users.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
		fclose(FP_Accounts);

		User_Type Temp_Accounts={};
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		bool isFindAccount = 0;
		do {	//��ȡ ���洢�˺����� 

			//�������ݼĴ浽Temp_Accounts
			if(!isFindAccount)inputbox_getline("�������˺�", "�������˺�", Temp_Accounts.Username, Max_Input_Num);      //�����˺�//https://xege.org/manual/api/other/inputboxgetline.htm buffer area

			inputbox_getline("����������", "����������", Temp_Accounts.Password, Max_Input_Num);      //��������

			FP_Accounts = fopen("Files\\Users.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
			Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size));
			Accounts_Head->Accounts_Next = NULL;
			Accounts_Read = Accounts_Head;

			while (!feof(FP_Accounts)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ���� // ����
				Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size));
				fscanf(FP_Accounts, "%s\t%s\t%d\t%d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.CanBook);//�����ļ���ǰ��¼
				//�Ա�
				if (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) == 0) {	//�Ա��˻����� == 0 ˵���ҵ�
					isFindAccount = 1;
					if(strcmp(Temp_Accounts.Password, Account_Point->Accounts_Data.Password) == 0){	//�Ա�����  == 0 �����Ǻ�
						//��¼
						Temp_Accounts.Type = Account_Point->Accounts_Data.Type;//�ı��¼�˻���Ȩ��
						Temp_Accounts.CanBook = Account_Point->Accounts_Data.CanBook;

						fclose(FP_Accounts);
						strcpy(Temp_User.Username, Temp_Accounts.Username);
						Temp_User.Type = Temp_Accounts.Type;	//�����û�����
						Temp_User.Logined = 1;			//�����¼״̬�ѵ�¼
						Temp_User.CanBook = Temp_Accounts.CanBook;

						return MessageBox(NULL, TEXT("��¼�ɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
					}else { //�������
						if ((MessageBox(NULL, TEXT("�������\n�Ƿ����������˺�����?"), TEXT("�˺����ҵ��ҵ���"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 6) ? 1 : 0) {//�� 1
							break;
						}
						else return 0;//�˳� 
					}
				}
			}
			//������
			if (!isFindAccount) {//û�ҵ��˻���
				if ((MessageBox(NULL, TEXT("û�е��ҵ��˺ţ�\n�Ƿ�ע���˻�?"), TEXT("û�е��ҵ��˺ţ�"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 6) ? 1 : 0) {
					Add_User();
				}
				else return 0;
			}

		} while (1);

	}
	return 1;
}

int Logout_User() {          //�˳��˻�
	if (Temp_User.Type == -1) {
		MessageBox(NULL, TEXT("����û�е�¼��"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	else {
		//User_Type Temp_User = { "NONE","NONE",-1,0,0 };//?
		strcpy(Temp_User.Username, "NONE");
		strcpy(Temp_User.Password, "NONE");
		Temp_User.CanBook = 1;
		Temp_User.Type = -1;
		Temp_User.Logined = 0;
		//Temp_User.CanBook = 1;
		MessageBox(NULL, TEXT("�����˳���ǰ�˻���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}