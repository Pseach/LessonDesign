#pragma once
//����Ŀ¼�ļ�

extern int Page = 0;//�л�ҳ�� ����ť

//���ݽṹ
struct Windows { // ��������
	int x;
	int y;
};


typedef struct {  //ϵͳ�����û������ݽṹ
	char Username[40];
	char Password[40];
	int Type;					//�û�|����Ա
	int HaveComputer;			//�Ƿ�ӵ�л�λ

	int Login_User_Type;		//δ֪|�û�|����Ա
	int Logined;				//��¼״̬

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


//��������
extern Windows VerticalWindows;
extern Windows LandscapeWindows;
extern Windows WindowsSize;

//�û���ǰ����
extern User_Type Temp_User;

//
extern const int Defaut_Font_Size;


//����
int MainStart();
int Recovery_Button_State(int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Exit();

