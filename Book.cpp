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

long long timecmp(Time_Type a, Time_Type b) {//a>b
	if (b.Hour >= 24)b.Day += b.Hour / 24;
	if (b.Day >= 30)b.Month += b.Month / 30;

	if(a.Month != b.Month)return a.Month > b.Month;
	if (a.Day != b.Day)return a.Day > b.Day;
	if (a.Hour != b.Hour)return a.Hour > b.Hour;
	if (a.Minute != b.Minute)return a.Minute > b.Minute;
	if (a.Second != b.Second)return a.Second > b.Second;
	return 0;
}
int canuse(char name[],int mod) {
	char s1[40], s2[40], s3[40];
	int state = 0;
	if (mod == 1) {
		FILE* FP_ComputerRoom = NULL;
		FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		while (!feof(FP_ComputerRoom)) {
			fscanf(FP_ComputerRoom, "ComputerRoomName��%s\tState��%d\n",s1, &state);//�����ļ���ǰ��¼
			if (strcmp(s1, name) == 0)return state;
		}
	}if (mod == 2) {
		FILE* FP_Computer = NULL;
		FP_Computer = fopen("Files\\ComputerRooms.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
		while (!feof(FP_Computer)) {
			fscanf(FP_Computer, "ComputerName��%s\tState��%d\n", s1, &state);//�����ļ���ǰ��¼
			if (strcmp(s1, name) == 0)return state;
		}
	}
	//fclose(FP_Computer);
}
int Pre_Book(){			//����Ԥ��									
	//////////////////////////////////////////////////////��ȱ�ٹ��ܣ��Լ�ĳ̨�����Ƿ�ԤԼ�ˣ���������һ̨���ԣ���
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a"); //�ļ����ڴ洢 ����������λ�Ƿ�ռ�ã���������
	fclose(FP_BookData);
	if (Temp_User.CanBook) {
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
				Temp_Book.Book_Time.Month = Time_Point->tm_mon + 1;//0~11
				Temp_Book.Book_Time.Day = ((Time_Point->tm_hour + 8) >= 24) ? (Time_Point->tm_mday + 1) : (Time_Point->tm_mday);	//������
				//Temp_Book.Book_Time.Hour = ((Time_Point->tm_hour + 8) >= 24) ? (Time_Point->tm_hour + 8 - 24) : (Time_Point->tm_hour + 8);//���ܳ��֡�26��Сʱ����������
				Temp_Book.Book_Time.Hour = (Time_Point->tm_hour + 8) % 24;//���ܳ��֡�26��Сʱ����������
				Temp_Book.Book_Time.Minute = Time_Point->tm_min;
				Temp_Book.Book_Time.Second = Time_Point->tm_sec;


				if (1) {///////////////////////////////////����Ƿ� �ո��Ѿ�ԤԼ����û����
					Book_Type localbookdata = {};
					FP_BookData = fopen("Files\\BookLog.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
					while (!feof(FP_BookData)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����	%02d-%02d-%02d
						Time_Type localtime = {};
						fscanf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long��%d UserName��%s BookRoom��%s BookComputer��%s BookState��%d\n",
							&localtime.Year, &localtime.Month, &localtime.Day,
							&localtime.Hour, &localtime.Minute, &localtime.Second,
							&localbookdata.Book_Time_Long.Hour, localbookdata.User_Book_Data.Username,
							localbookdata.ComputerRoom_Book_Data.ComputerRoom_Name,
							localbookdata.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
							&localbookdata.Computer_Book_Data.Computer_Book_State
						);//�����ļ���ǰ��¼
						if (localbookdata.Computer_Book_Data.Computer_Book_State == 1|| localbookdata.Computer_Book_Data.Computer_Book_State == 2) {					//ԤԼ��|ͬ������2��
							if (strcmp(Temp_User.Username, localbookdata.User_Book_Data.Username) == 0) {//ͬ��
								localtime.Hour += localbookdata.Book_Time_Long.Hour;
								if (!timecmp(Temp_Book.Book_Time, localtime)) {	//���ڵ�ʱ���������֮ǰʱ��+Լʱ �Ǿ���Ԥ��
									fclose(FP_BookData);
									return MessageBox(NULL, TEXT("���Ѿ���һ̨������ˣ�"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
								}
							}
						}
					}
					//�������
					fclose(FP_BookData);
				}


				//if (ComputerRoom_Num() == 0) {
				if (!ComputerRoom_Num()) {
					if (MessageBox(NULL, TEXT("��û���κλ������Ƿ���ӻ�����"), TEXT("����"), MB_YESNO | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6)Add_Computer_Room();	//����Ƿ��л���
					else return 0;//����ӻ��������Ļ�λ���˳�Ԥ����λ���ܣ�
				}

				do {
					char ch_time[10];//?
					inputbox_getline("������Ԥ��Сʱ��", "������Ԥ��Сʱ��", ch_time, 5);
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
					if (!canuse(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, 1)) { MessageBox(NULL, TEXT("������Ļ����ѱ��رգ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND); return 0; }
					if (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name)) {			//����������Ʋ�ѯ����
						inputbox_getline("�������λ����", "�������λ����", Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, 40);	//�еĻ������λ
						if (!canuse(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name,2)) { MessageBox(NULL, TEXT("������Ļ�λ�ѱ���ͣʹ�ã���"), TEXT("����"), MB_OK | MB_SETFOREGROUND); return 0; }
						if (HaveComputer(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name)) {
							break;//�о��˳����
						}
						else //�޾���
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
				}//��ʼ��ͷ�ڵ�
				Books_Read = Books_Head;//��Readָ������ͷ
				while (!feof(FP_BookData)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����	%02d-%02d-%02d
					if (Book_Point = (Books_List)malloc(sizeof(Books_Size))) {
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
				}
				//�������
				Books_Read->Books_Next = NULL;//��ʼ��
				fclose(FP_BookData);

				Book_Point = Books_Head->Books_Next;//��ʼ������Pointָ��Head����һ�������������ͷ����
				while ((Book_Point)//����ͷ
					&& (strcmp("a", "b") != 0)
					&& (1)
					)//adduser��cmp��=0 ����һ������û�ҵ���������while��ģ��������ң�
					Book_Point = Book_Point->Books_Next;//��ͷ��Next����
				if (!Book_Point) {    //����û�ҵ�
					FP_BookData = fopen("Files\\BookLog.txt", "a");
					Temp_Book.Computer_Book_Data.Computer_Book_State = 1;//����ͬ��ĳ���Ԥ����
					fprintf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long��%d UserName��%s BookRoom��%s BookComputer��%s BookState��%d\n",
						Temp_Book.Book_Time.Year, Temp_Book.Book_Time.Month, Temp_Book.Book_Time.Day,
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
	}//CanBook
	else {
		MessageBox(NULL, TEXT("���Ѿ�����ֹԤ�����ܣ�"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	return 0;
}
int Cancel_Pre_Book() {	//ȡ��Ԥ��//Ԥ��״̬���0
	FILE* FP_BookData = NULL;
	FP_BookData = fopen("Files\\BookLog.txt", "a");
	fclose(FP_BookData);

	if (Temp_User.Logined) { //�ѵ�¼ 
		Book_Type Temp_Book = {};
		time_t timep;
		struct tm* Time_Point;
		time(&timep);
		Time_Point = gmtime(&timep);

		Books_List Books_Head, Books_Read, Book_Point;


		if (!ComputerRoom_Num()) {
			if (MessageBox(NULL, TEXT("��û���κλ�����"), TEXT("����"), MB_OK | MB_SETFOREGROUND | MB_SETFOREGROUND) == 6)return 0;	//����Ƿ��л���
		}

		strcpy(Temp_Book.User_Book_Data.Username, Temp_User.Username);		//�û����� �浽Book��User 

		inputbox_getline("������ɾ����λ���ڻ�������", "������ɾ����λ���ڻ�������", Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, 40);	//���������
		if (HaveComputerRoom(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name)) {			//����������Ʋ�ѯ����
			inputbox_getline("�������λ����", "�������λ����", Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, 40);	//�еĻ������λ
			if (HaveComputer(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name)) {//�������λ�Ļ� 
			}
			else {//��
				MessageBox(NULL, TEXT("�û����޴˻�λ"), TEXT("����"), MB_OK | MB_SETFOREGROUND | MB_SETFOREGROUND);
				return 0;
			}
		}
		else {//�޵Ļ�
			MessageBox(NULL, TEXT("�޴˻�����"), TEXT("����"), MB_OK | MB_SETFOREGROUND | MB_SETFOREGROUND);
			return 0;
		}

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

			if ((strcmp(Temp_Book.User_Book_Data.Username, Book_Point->Book_Data.User_Book_Data.Username) == 0)
				&& (strcmp(Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name) == 0)
				&& (strcmp(Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name) == 0)
				&& (1 == Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State)//ɾ�����ܣ��м�ڵ����������յ���ָ��NULL��if����NULL��->Next����//�û�����ͬ��ԤԼ������ͬ��ԤԼ�Ļ�λ��ͬ��������ڵ���д������ע�ͣ�
				)
				Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State = 0;

			Books_Read->Books_Next = Book_Point;//����������Read����һ���ڵ�ָ�������Point��λ�ã�����������ʱ�����ݵ�Point�����ݴ浽Read�////Books_Read->Books_Next��Read��ָ�Ķ���Head�����µ�Head��
			Books_Read = Book_Point;//���ã�ѭ����ȥ������malloc����������Read
		}
		//�������
		Books_Read->Books_Next = NULL;//��ʼ��
		fclose(FP_BookData);

		//�������ѽ���
		// �����������뵽�ĵ�����ͷд��
		//��w��ɾ����д
		FP_BookData = fopen("Files\\BookLog.txt", "w");
		Book_Point = Books_Head->Books_Next;//��ʼ������Pointָ��Head����һ�������������ͷ����
		while (Book_Point) {
			//��ͷ��������
			fprintf(FP_BookData, "%04d/%02d/%02d %02d:%02d:%02d Long��%d UserName��%s BookRoom��%s BookComputer��%s BookState��%d\n",
				Book_Point->Book_Data.Book_Time.Year, Book_Point->Book_Data.Book_Time.Month, Book_Point->Book_Data.Book_Time.Day,
				Book_Point->Book_Data.Book_Time.Hour, Book_Point->Book_Data.Book_Time.Minute, Book_Point->Book_Data.Book_Time.Second,
				Book_Point->Book_Data.Book_Time_Long.Hour, Book_Point->Book_Data.User_Book_Data.Username,
				Book_Point->Book_Data.ComputerRoom_Book_Data.ComputerRoom_Name,
				Book_Point->Book_Data.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
				Book_Point->Book_Data.Computer_Book_Data.Computer_Book_State//Ӧ�������
			);//��¼(�ӵ����)
			Book_Point = Book_Point->Books_Next;
		}
		MessageBox(NULL, TEXT("ɾ��Ԥ���ɹ���"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
		fclose(FP_BookData);
	}
	else {
		MessageBox(NULL, TEXT("��δ��¼��"), TEXT("����"), MB_OK | MB_SETFOREGROUND);
	}
	return 1;
}
int Query_BooK(){		//
	system("Files\\BookLog.txt");
	return 1;
}
int Book() {			//Ԥ��ҳ��
	return 1;
}