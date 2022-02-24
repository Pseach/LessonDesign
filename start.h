#pragma once
//����Ŀ¼�ļ�

struct Windows { // ��������
	int x;
	int y;
};
extern Windows VerticalWindows;
extern Windows LandscapeWindows;

//�û���ǰ����
extern char Online_Login_User_Name[40];
extern int Online_Login_User_Type;	//�û�|����Ա
extern int Online_Login_User_HaveComputer;

extern const int Defaut_Font_Size;

//���ݽṹ
typedef struct {  //ϵͳ�����û������ݽṹ
	char Username[40];
	char Password[40];
	int Type;	//�û�|����Ա
	int HaveComputer;
}User_Type;
typedef struct Accounts_Node {  //���������洢���ļ��ж�����������
	User_Type Accounts_Data;
	struct Accounts_Node* Accounts_Next;
}Accounts_Size, * Accounts_List;

typedef struct {  //���������ݽṹ
	char ComputerRoom_Name[40];				//�������� 
	int ComputerRoom_State;				//����|������	1|0
}ComputerRoom_Type;
typedef struct ComputerRoom_Node {
	ComputerRoom_Type ComputerRoom_Data;
	struct ComputerRoom_Node* ComputerRoom_Next;
}ComputerRoom_Size, * ComputerRoom_List;

typedef struct {  //����������ݽṹ
	char Computer_Name[40];				//��������� 
	char Computer_Room[40];				//�ĸ����� 
	int Computer_State;					//����|������	1|0
	int IsPre_Book;						//������Ԥ��
	int IsFinal_Book; 					//������Ԥ��
}Computer_Type;
typedef struct Computers_Node {
	Computer_Type Computers_Data;
	struct Computers_Node* Computers_Next;
}Computers_Size, * Computers_List;

//����
int MainStart();
int Exit();

