#include "Book.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Book.h"
#include "AccountControl.h"
#include <string>




int Pre_Book(){			//����Ԥ��										//------------------û�г�ʼ�����ݣ�״̬ʲô�ģ��ѱ�Ԥ������
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
			char chtime[1];
			inputbox_getline("������Ԥ��Сʱ��0~9", "������Ԥ��Сʱ��0~9", chtime , 1);
			Temp_Book.Book_Time_Long.Hour = chtime[0] - '0';

			strcpy(Temp_Book.User_Book_Data.Username , Temp_User.Username);
			//if (Temp_Book.ComputerRoom_Book_Data.ComputerRoom_State) 
			
			inputbox_getline("�������������", "�������������", Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name, 40);
			//if(����)

			inputbox_getline("�������λ����", "�������λ����", Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name, 40);
			//if(����)


			Temp_Book.Computer_Book_Data.Computer_Book_State = 0;//��ʼ��Ԥ��״̬
			FP_BookData = fopen("Files\\BookLog.txt", "r");//����ֻ���ķ�ʽ���ļ��򿪣������ݶ�����������һ��������
			if (Books_Head = (Books_List)malloc(sizeof(Books_Size))) {
				Books_Head->Books_Next = NULL;
			}
			Books_Read = Books_Head;
			while (!feof(FP_BookData)) {      //��β�ӷ�����һ������  feof����ļ��Ƿ����
				if (Book_Point = (Books_List)malloc(sizeof(Books_Size))) {
					fscanf(FP_BookData, "%d/%d/%d %d:%d:%d Long:%d UserName:%s BookRoom:%s BookComputer:%s BookState:%d\n",
						&Temp_Book.Book_Time.Year, &Temp_Book.Book_Time.Month, &Temp_Book.Book_Time.Day,
						&Temp_Book.Book_Time.Hour, &Temp_Book.Book_Time.Minute, &Temp_Book.Book_Time.Second,
						&Temp_Book.Book_Time_Long.Hour, Temp_Book.User_Book_Data.Username,
						Temp_Book.ComputerRoom_Book_Data.ComputerRoom_Name,
						Temp_Book.ComputerRoom_Book_Data.Computer_Data.Computer_Name,
						Temp_Book.Computer_Book_Data.Computer_Book_State//Ӧ�������
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
				fprintf(FP_BookData,"%d/%d/%d %d:%d:%d Long:%d UserName:%s BookRoom:%s BookComputer:%s BookState:%d\n",
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