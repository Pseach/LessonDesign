#include "Book.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Book.h"
#include "AccountControl.h"
#include <string>
#include "Manage.h"//ComputerRoom_Num

//ժ��https://www.cnblogs.com/curo0119/p/7792627.html
enum error { correct, incorrect, overflow, null };
int error = correct;//Ĭ������ȷ��
int MyAtoi(const char* str) {	
	int flag = 1;
	if (str == NULL) {
		error = null;
		return 0;
	}
	while (*str == ' ' || *str == '\t' || *str == '\f' || *str == '\r' || *str == '\n')
		str++;
	if (*str == '-') {											//�����Ĵ�����incorrect
		error = incorrect;//�Ƿ�								//�����������
		flag = -1;
		str++;
	}
	else if (*str == '+')//ע������������õĲ���ѭ����������ֻ����Ϊ��һ���ַ����ֲ��ǺϷ���
		str++;
	int num = 0;
	while (*str != '\0') {//*str=='\0'Ҳ�ǽ�������֮һ
		if (*str >= '0' && (*str <= '9')) {
			num = num * 10 + *str - '0';//ע���ǡ�0��   ����������//��������Ժ�����
			str++;
		}
		else {
			error = incorrect;//�Ƿ�
			break;
		}
	}
	return num * flag;
}

int Pre_Book(){			//����Ԥ��										//------------------û�г�ʼ�����ݣ�״̬ʲô�ģ��ѱ�Ԥ������
	//////////////////////////////////////////////////////��ȱ�ٹ��ܣ����ͬһʱ����Ƿ�Ԥ����̨���ԣ�book state���Լ�ĳ̨�����Ƿ�ԤԼ�ˣ���������һ̨���ԣ���
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a"); //�ļ����ڴ洢 ����������λ�Ƿ�ռ�ã���������
	fclose(FP_BookData);
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
		do {

			Book_Type Temp_Book = {};
			time_t timep;
			struct tm* Time_Point;
			time(&timep);
			Time_Point = gmtime(&timep);
			/*Time_Type Temp_Time = {};
			Time_Type Book_Time_Long = {};
			User_Type User_Book_Data = {};
			ComputerRoom_Type ComputerRoom_Book_Data = {};
			Computer_Type Computer_Book_Data = {};*/

			Books_List Books_Head, Books_Read, Book_Point;

			Temp_Book.Book_Time.Year = Time_Point->tm_year + 1900;
			Temp_Book.Book_Time.Month = Time_Point->tm_mon + 1;
			Temp_Book.Book_Time.Day = Time_Point->tm_mday;
			Temp_Book.Book_Time.Hour = Time_Point->tm_hour + 8;
			Temp_Book.Book_Time.Minute = Time_Point->tm_min;
			Temp_Book.Book_Time.Second = Time_Point->tm_sec;

			//if (ComputerRoom_Num() == 0) {
			if (!ComputerRoom_Num()) {
				if (MessageBox(NULL, TEXT("��û���κλ������Ƿ���ӻ�����"), TEXT("����"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6)Add_Computer_Room();	//����Ƿ��л���
				else return 0;//����ӻ��������Ļ�λ���˳�Ԥ����λ���ܣ�
			}

			do{
			char ch_time[10];//?
			inputbox_getline("������Ԥ��Сʱ��", "������Ԥ��Сʱ��", ch_time , 5);
				switch (error) {
					case correct:
						break;
					case null:
						//MessageBox(NULL, TEXT("����Ƿ������������룡"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
						//error = correct;
						//break;
					case incorrect:
						MessageBox(NULL, TEXT("����Ƿ������������룡"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
						error = correct;
						break;
					case overflow:
						MessageBox(NULL, TEXT("�������̫�����������룡"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
						error = correct;
				}
				Temp_Book.Book_Time_Long.Hour = MyAtoi(ch_time);
			} while (error != correct);
			strcpy(Temp_Book.User_Book_Data.Username, Temp_User.Username);		//���������ʱ��Ϣ�ŵ���ʱԤ�������ݽṹ����
			
			do {//---------------------------�Ż���������(û��Ӧ��λ��ʱ�����Ƿ���ӵ�ʱ��ֱ�����������Ļ�λ����������)
				inputbox_getline("��������ӻ�λ���ڻ�������", "��������ӻ�λ���ڻ�������", Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, 40);	//���������
				if (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name)) {			//����������Ʋ�ѯ����
					inputbox_getline("�������λ����", "�������λ����", Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, 40);	//�еĻ������λ
					if (HaveComputer(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name)) {
						break;//�о��˳����
					}else //�޾���
						if (MessageBox(NULL, TEXT("�û����޴˻�λ���Ƿ���ӻ�λ"), TEXT("����"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer(); continue; }	//continue��������}��
							else return 0;	//����ӻ�λ���˳�
				}
				else {//�޵Ļ�����ӷ�
					if (MessageBox(NULL, TEXT("��û�иû������Ƿ���ӻ�����"), TEXT("����"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6) { Add_Computer_Room(); continue; }	//�ǵĻ�����ӻ�����//continue:������������������Ҫ��ӻ�λ�Ļ���
					else return 0;	//����ӻ������˳�
				}
			} while (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name));


			Temp_Book.Computer_Book_Data.Computer_Book_State = 0;//��ʼ��Ԥ��״̬
			FP_BookData = fopen("Files\\BookLog.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
			if (Books_Head = (Books_List)malloc(sizeof(Books_Size))) {
				Books_Head->Books_Next = NULL;
			}
			Books_Read = Books_Head;
			while (!feof(FP_BookData)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
				if (Book_Point = (Books_List)malloc(sizeof(Books_Size))) {
					fscanf(FP_BookData, "%d/%d/%d %d:%d:%d Long:%d\tUserName:%s\tBookRoom:%s\tBookComputer:%s\tBookState:%d\n",
						&Book_Point->Book_Data.Book_Time.Year, &Book_Point->Book_Data.Book_Time.Month, &Book_Point->Book_Data.Book_Time.Day,
						&Book_Point->Book_Data.Book_Time.Hour, &Book_Point->Book_Data.Book_Time.Minute, &Book_Point->Book_Data.Book_Time.Second,
						&Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
						Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
						Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
						&Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//Ӧ�������
					);//�����ļ���ǰ��¼
					Books_Read->Books_Next = Book_Point;
					Books_Read = Book_Point;
				}
			}
			Books_Read->Books_Next = NULL;
			fclose(FP_BookData);

			Book_Point = Books_Head->Books_Next;
			while ((Book_Point) 
				&& (strcmp("a", "b") != 0) 
				&& (1)
				)//���������ظ�Ԥ��
				Book_Point = Book_Point->Books_Next;
			if (!Book_Point) {    //û�ҵ�������׷�ӵķ�ʽд��BookLog.txt�ı���
				FP_BookData = fopen("Files\\BookLog.txt", "a");
				Temp_Book.Computer_Book_Data.Computer_Book_State = 1;//����ͬ��ĳ���Ԥ����
				fprintf(FP_BookData,"%d/%d/%d %d:%d:%d Long:%d\tUserName:%s\t BookRoom:%s\tBookComputer:%s\tBookState:%d\n",
					Temp_Book.Book_Time.Year, Temp_Book.Book_Time.Month ,Temp_Book.Book_Time.Day,
					Temp_Book.Book_Time.Hour, Temp_Book.Book_Time.Minute, Temp_Book.Book_Time.Second,
					Temp_Book.Book_Time_Long.Hour, Temp_Book.User_Book_Data.Username,
					Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name,
					Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
					Temp_Book.Computer_Book_Data.Computer_Book_State//Ӧ�������
					);//��¼
				fclose(FP_BookData);

				return MessageBox(NULL, TEXT("Ԥ���ɹ����ȴ�ͬ�⣡"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
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