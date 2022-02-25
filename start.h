#pragma once
//����Ŀ¼�ļ�
#include <string> // Page string

//extern int Page;//�л�ҳ�� ����ť (����)

//���ݽṹ
struct Windows { // ��������
	int x;
	int y;
};

typedef struct {  //ʱ������ݽṹ
	int Year;
	int Month;
	int Day;
	int Time_Mod;	// ���ֶ����� | ��ϵͳʱ�� �������ã���
}Time_Type;

typedef struct {  //��λ�����ݽṹ
	char Computer_Name[40];				//��λ���� 
	char Computer_Room[40];				//�ĸ����� 
	int Computer_State;					//����|������	1|0
	//int IsPre_Book;						//������Ԥ��
	//int IsFinal_Book; 					//������Ԥ��
}Computer_Type;

typedef struct {  //���������ݽṹ
	char ComputerRoom_Name[40];				//��������
	int ComputerRoom_State;				//����|������	1|0
	Computer_Type Computer_Data;		//�����ܣ����ڰ�������ѯ���л�λ����
}ComputerRoom_Type;

typedef struct {  //ϵͳ�����û������ݽṹ
	char Username[40];
	char Password[40];
	int Type;					//�û�|����Ա
	int HaveComputer;			//�Ƿ�ӵ�л�λ

	int Login_User_Type;		//δ֪|�û�|����Ա
	int Logined;				//��¼״̬
}User_Type;

typedef struct {  //Ԥ����Ϣ�����ݽṹ
	Time_Type Book_Time_Data;					//Ԥ����ʱ��
	Time_Type Computer_Book_Time_Data;			//��λ��Ԥ��ʱ��
	User_Type User_Book_Data;					//Ԥ���û����ݣ����֣�
	int Computer_Book_State;					//��λԤ��״̬��û�б�Ԥ��or����Ԥ��or�ռ�Ԥ����
}Book_Type;

//book����
//ȡ������Ԥ��
//����Ԥ��
// ��Ӽ����֮ǰ����ӻ��������õ�������ѯ���л�λ��system��txt����
//����ʱ��� �����ʱ�����ʱ��|ϵͳʱ�䣩
//���ļ��洢Ԥ����Ϣ�����й����鿴����Ԥ���û�����
//����Ԥ���ʹ浽���й����������Ƿ������ռ�Ԥ����Ԥ��ʱ��
//ʱ��Աȣ���������������<>����

typedef struct Accounts_Node {  //���������洢���ļ��ж�����������
	User_Type Accounts_Data;
	struct Accounts_Node* Accounts_Next;
}Accounts_Size, * Accounts_List;

typedef struct ComputerRoom_Node {
	ComputerRoom_Type ComputerRoom_Data;
	struct ComputerRoom_Node* ComputerRoom_Next;
}ComputerRoom_Size, * ComputerRoom_List;

typedef struct Computers_Node {
	Computer_Type Computers_Data;
	struct Computers_Node* Computers_Next;
}Computers_Size, * Computers_List;

typedef struct Book_Node {
	Book_Type Book_Data;
	struct Book_Node* Book_Next;
}Book_Size, * Book_List;


//��������
extern Windows VerticalWindows;
extern Windows LandscapeWindows;
extern Windows WindowsSize;

//�û���ǰ����
extern User_Type Temp_User;

//����
extern const int Defaut_Font_Size;


//����
int MainStart();
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Recovery_Button_State(int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Exit();

