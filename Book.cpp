#include "Book.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#include "Book.h"
#include "AccountControl.h"




int Pre_Book(){			//����Ԥ��
	/// <summary>
	/// ����Ѿ���¼������txt����ȡ�� Ԥ����ʱ�䣬����,��λ���ݣ����������ʣ�
	/// ʱ��������֮�⣬��ʾ����������֮�ڣ�����ҪԤ����ʱ��
	/// ���������ʱ��+ʱ���Ѿ��ڻ�������ʱ��֮�⣺���ѿ���ʱ�䣩�����ã�
	/// 
	///Book_Type��
	///Time_Type Book_Time;							//Ԥ����ʱ��
	///Time_Type Book_Time_Long;					//��λ��Ԥ��ʱ��
	///User_Type User_Book_Data;					//Ԥ���û����ݣ����֣�
	///ComputerRoom_Type ComputerRoom_Book_Data;    //Ԥ����������
	///Computer_Type Computer_Book_Data;			//Ԥ����λ����
	/// </summary>
	if (Temp_User.Logined) { //�ѵ�¼
		FILE* FP_BookData = NULL;
		FP_BookData = fopen("Files\\BookLog.txt", "a"); //�ļ����ڴ洢 ����������λ�Ƿ�ռ�ã���������
		fclose(FP_BookData);
		do {	//��ȡ���洢�˺����� 
			Add_User();
			User_Type Temp_ComputerRoom={};
			Accounts_List Accounts_Head, Accounts_Read, Account_Point;

			int Temp_Type = MessageBox(NULL, TEXT("�����˻�����ԱȨ�ޣ�"), TEXT("�û�Ȩ������"), MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);//MB_ICONQUESTION���ʺ�https://blog.csdn.net/yuyan987/article/details/78558648
			inputbox_getline("�������˺�", "�������˺�", Temp_ComputerRoom.Username, 40);      //�����˺�
			inputbox_getline("����������", "����������", Temp_ComputerRoom.Password, 40);      //��������
			Temp_ComputerRoom.Type = (Temp_Type == 6) ? 1 : 0;	 //��(Y) ֵΪ6 ��(N)ֵΪ7;	//����û�Ȩ��
			Temp_ComputerRoom.HaveComputer = 0;

			FP_BookData = fopen("Files\\BookLog.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
			if (Accounts_Head = (Accounts_List)malloc(sizeof(Accounts_Size))) {
				Accounts_Head->Accounts_Next = NULL;
			}
			Accounts_Read = Accounts_Head;
			while (!feof(FP_BookData)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
				if (Account_Point = (Accounts_List)malloc(sizeof(Accounts_Size))) {
					fscanf(FP_BookData, "%s %s %d %d\n", Account_Point->Accounts_Data.Username, Account_Point->Accounts_Data.Password, &Account_Point->Accounts_Data.Type, &Account_Point->Accounts_Data.HaveComputer);//�����ļ���ǰ��¼
					Accounts_Read->Accounts_Next = Account_Point;
					Accounts_Read = Account_Point;
				}
			}
			Accounts_Read->Accounts_Next = NULL;
			fclose(FP_BookData);

			Account_Point = Accounts_Head->Accounts_Next;
			while ((Account_Point) && (strcmp(Temp_ComputerRoom.Username, Account_Point->Accounts_Data.Username) != 0) && (1))//�ȶ����ݣ�û�ҵ���ͬ�û�������û���꣬������
				Account_Point = Account_Point->Accounts_Next;
			if (!Account_Point) {    //û�ҵ���ͬ�û���������׷�ӵķ�ʽд��BookLog.txt�ı��У��ҵ��ε�ע���������
				FP_BookData = fopen("Files\\BookLog.txt", "a");
				fprintf(FP_BookData, "%s %s %d %d\n", Temp_ComputerRoom.Username, Temp_ComputerRoom.Password, Temp_ComputerRoom.Type, Temp_ComputerRoom.HaveComputer);
				fclose(FP_BookData);
				return MessageBox(NULL, TEXT("��ӳɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
			}
			else {  //�ҵ��ˣ�����Ҫ���������û��������룬��ѭ���ոյĹ��̡�
				if (MessageBox(NULL, TEXT("������ӣ�"), TEXT("�û����Ѵ��ڣ�"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;
			}
		} while (1);
	}
	else {
		MessageBox(NULL, TEXT("��δ��¼��"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}
int Cancel_Pre_Book() {	//ȡ��Ԥ��
	return 1;
}
int Query_IsBooK(){		//
	return 1;
}
int Book() {			//Ԥ��ҳ��
	return 1;
}