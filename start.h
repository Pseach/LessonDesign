#pragma once
//����Ŀ¼�ļ�

extern int Page;//�л�ҳ�� ����ť

//����
extern const int Defaut_Font_Size;
extern const int Max_Input_Num;

//���ݽṹ
struct Windows { // ��������
	int x;
	int y;
	Windows& operator=(Windows& value) {
		x = value.x;
		y = value.y;
		return *this;
	}
};

typedef struct time{  //ʱ������ݽṹ
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;
}Time_Type;
typedef struct {  //��λ�����ݽṹ
	char Computer_Name[10];				//��λ���� 
	char Computer_Room[10];				//�ĸ����� 
	int Computer_State;					//����|������	1|0
	int Computer_Book_State;			//��λԤ��״̬��û�б�Ԥ��or����Ԥ��or�ռ�Ԥ����(������Ԥ���ļ��в�ѯ��ʷ��¼ʱ�ã�
}Computer_Type;

typedef struct {  //���������ݽṹ
	char ComputerRoom_Name[10];				//��������
	int ComputerRoom_State;				//����|������	1|0
	Computer_Type Computer_Data;		//���ڰ�������ѯ���л�λ����(?)
	Time_Type ComputerRoom_CanBook_Time;		//����������Ԥ��ʱ��
	Time_Type ComputerRoom_CanBook_TimeTo;		//����������Ԥ��ʱ��
}ComputerRoom_Type;

typedef struct usertpye{  //�û������ݽṹ
	char Username[10];
	char Password[10];
	int Type;					//δ֪|�û�|����Ա -1|0|1
	int CanBook;			//�Ƿ�ӵ�л�λ(CanBook)
	int Logined;				//��¼״̬
}User_Type;

typedef struct {  //Ԥ����Ϣ�����ݽṹ
	Time_Type Book_Time;						//Ԥ����ʱ��
	Time_Type Book_Time_Long;					//��λ��Ԥ��ʱ��//��λСʱ
	User_Type User_Book_Data;					//Ԥ���û����ݣ����֣�
	ComputerRoom_Type ComputerRoom_Book_Data;   //Ԥ����������
	Computer_Type Computer_Book_Data;			//Ԥ����λ����
}Book_Type;

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

typedef struct Books_Node {
	Book_Type Book_Data;
	struct Books_Node* Books_Next;
}Books_Size, * Books_List;


//��������
extern Windows VerticalWindows;
extern Windows LandscapeWindows;
extern Windows WindowsSize;

//�û���ǰ����
extern User_Type Temp_User;



//����
int MainStart();	//�������Ϊ���Ǻ���
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Recovery_Button_State(int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);	
int Exit();//û��

