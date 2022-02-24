#include "AccountControl.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#include "Buttons.h"

int Show_Online_Login_User() {	//��ʾ��ǰ�˻�
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // ������ɫ

	setfont(Defaut_Font_Size, 0, "����������");					//�����С  ��ȱ�������Ӧ  �����ļ�

	//��ʾ��ǰ�˻���
	drawRectButton(&ButtonLocation_0);	//����ǰ�˻���"
	xyprintf(ButtonLocation_0.height * 1 / 5 / 2, ButtonLocation_0.height * 1 / 5 / 2, "��ǰ�˻���");

	drawRectButton(&ShowOnline_Login_User); //��½�˻�Ϊ" "
	xyprintf(ShowOnline_Login_User.x, ShowOnline_Login_User.y, "%s", Temp_User.Username);

	{ 
		int RemindFont_Size = Defaut_Font_Size / 2;
		setfont(RemindFont_Size, 0, "����������", 0, 0, 100, 0, 0, 0);
		setcolor(EGERGB(0x00, 0x00, 0x00));

		switch(Temp_User.Type){

			case -1: {	//δ֪
				xyprintf(ButtonLocation_0.width - 4 * RemindFont_Size, ButtonLocation_0.height, "���¼��");//4����
				break;
			}
			case 0: {	//��ͨ�û�
				xyprintf(ButtonLocation_0.width - 8 * RemindFont_Size, ButtonLocation_0.height, "�𾴵��û����ã�");//8����
				break;
			}
			case 1: {	//����Ա
				xyprintf(ButtonLocation_0.width - 9 * RemindFont_Size, ButtonLocation_0.height, "�𾴵Ĺ���Ա���ã�");//9����
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
		User_Type Temp_Accounts;
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		int Temp_Type = MessageBox(NULL, TEXT("�����˻�����ԱȨ�ޣ�"), TEXT("�û�Ȩ������"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION���ʺ�https://blog.csdn.net/yuyan987/article/details/78558648
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
		while ((Account_Point) && (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) != 0) && (1))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
			Account_Point = Account_Point->Accounts_Next;
		if (!Account_Point) {    //û�ҵ���ͬ�û���������׷�ӵķ�ʽд��Users.txt�ı��У��ҵ��ε�ע���������
			FP_Accounts = fopen("Files\\Users.txt", "a");
			fprintf(FP_Accounts, "%s %s %d %d\n", Temp_Accounts.Username, Temp_Accounts.Password, Temp_Accounts.Type, Temp_Accounts.HaveComputer);
			fclose(FP_Accounts);
			return MessageBox(NULL, TEXT("��ӳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
		}
		else {  //�ҵ��ˣ�����Ҫ���������û��������룬��ѭ���ոյĹ��̡�
			if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("�û����Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
		}
	} while (1);
}

int Login_User(){        	    //��¼
	/// <summary>
	/// 		//�ѵ�¼
	///		//��ʾ�����ѵ�¼
	///	//δ��¼
	///		//�����˻�����
	///			//������
	///				//�ѵ���	
	///					// flag1
	///					//������ȷ��	��ʾ����½�ɹ�
	///					//�������	�ʣ��Ƿ���������
	///						//�ǣ��� ���ص�flag1 
	///						//���˳�
	///				//û�ѵ���	��ʾ��û�е�ǰ�˻�
	///					//�ʣ�ע���� 
	///						//ע�᣺ 	Add_User();
	///						//�˳��� 
	/// </summary>
	if (Temp_User.Logined) { //�ѵ�¼
		MessageBox(NULL, TEXT("���ѵ�¼��"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	else {

		FILE* FP_Accounts = NULL;
		FP_Accounts = fopen("Files\\Users.txt", "a"); //����ļ������ڣ���ᴴ��һ�����ļ�
		fclose(FP_Accounts);

		User_Type Temp_Accounts;
		Accounts_List Accounts_Head, Accounts_Read, Account_Point;

		bool isFindAccount = 0;
		do {	//��ȡ ���洢�˺����� 

			//�������ݼĴ浽Temp_Accounts
			if(!isFindAccount)inputbox_getline("�������˺�", "�������˺�", Temp_Accounts.Username, 40);      //�����˺�//https://xege.org/manual/api/other/inputboxgetline.htm buffer area

			inputbox_getline("����������", "����������", Temp_Accounts.Password, 40);      //��������

			FP_Accounts = fopen("Files\\Users.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
			Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size));
			Accounts_Head->Accounts_Next = NULL;
			Accounts_Read = Accounts_Head;

			while (!feof(FP_Accounts)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ���� // ����
				Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size));
				fscanf(FP_Accounts, "%s %s %d %d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.HaveComputer);//�����ļ���ǰ��¼
				//�Ա�
				if (strcmp(Temp_Accounts.Username, Account_Point->Accounts_Data.Username) == 0) {	//�Ա��˻����� == 0 ˵���ҵ�
					isFindAccount = 1;
					if(strcmp(Temp_Accounts.Password, Account_Point->Accounts_Data.Password) == 0){	//�Ա�����  == 0 �����Ǻ�
						//��¼
						Temp_Accounts.Type = Account_Point->Accounts_Data.Type;//�ı��¼�˻���Ȩ��
						fclose(FP_Accounts);
						strcpy(Temp_User.Username, Temp_Accounts.Username);
						Temp_User.Type = Temp_Accounts.Type;	//������ǰ��¼״̬
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
		Temp_User = { "NONE","NONE",-1,0,0 };
		MessageBox(NULL, TEXT("�����˳���ǰ�˻���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}