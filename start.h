#pragma once
//����Ŀ¼�ļ�

extern int Page;//�л�ҳ�� ����ť

//���ݽṹ
struct Windows { // ��������
	int x;
	int y;
	Windows& operator=(Windows& value) {
		x = value.x;
		y = value.y;
		return *this;
	}//��Ч��???����
};

typedef struct time{  //ʱ������ݽṹ
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;
	int Time_Mod;	// ���ֶ����� | ��ϵͳʱ�� �������ã���
	time& operator=(time& value){
		Year = value.Year;
		Month = value.Month;
		Day = value.Day;
		Second = value.Second;
		return *this;
	}
	bool operator< (time const& value) const {
		if (Year != value.Year) return Year < value.Year;
		else if (Month != value.Month) return Month < value.Month;
		else if (Day != value.Day) return Day < value.Day;
		else if (Second != value.Second) return Second < value.Second;
	}
	bool operator> (time const& value) const {
		if (Year != value.Year) return Year > value.Year;
		else if (Month != value.Month) return Month > value.Month;
		else if (Day != value.Day) return Day > value.Day;
		else if (Second != value.Second) return Second > value.Second;
	}
	bool operator= (time const& value) const {
		return ((Year == value.Year) && (Month == value.Month) && (Day == value.Day) && (Second == value.Second));
	}
	bool operator!= (time const& value) const {
		return ((Year != value.Year) || (Month != value.Month) || (Day != value.Day) || (Second != value.Second));
	}
}Time_Type;
typedef struct {  //��λ�����ݽṹ
	char Computer_Name[40];				//��λ���� 
	char Computer_Room[40];				//�ĸ����� 
	int Computer_State;					//����|������	1|0
	int Computer_Book_State;			//��λԤ��״̬��û�б�Ԥ��or����Ԥ��or�ռ�Ԥ����
}Computer_Type;

typedef struct {  //���������ݽṹ
	char ComputerRoom_Name[40];				//��������
	int ComputerRoom_State;				//����|������	1|0
	//Time_Type ComputerRoom_CanBook_Time;		//����������Ԥ��ʱ�䣨ֱ��ȫ�ֹ���
	Computer_Type Computer_Data;		//���ڰ�������ѯ���л�λ����
}ComputerRoom_Type;

typedef struct usertpye{  //ϵͳ�����û������ݽṹ
	char Username[40];
	char Password[40];
	int Type;					//δ֪|�û�|����Ա -1|0|1
	int HaveComputer;			//�Ƿ�ӵ�л�λ
	//int Login_User_Type;		//δ֪|�û�|����Ա -1|0|1		//?????????
	int Logined;				//��¼״̬
	//usertpye& operator=(usertpye& value) {
	//	strcpy(Username, value.Username);
	//	strcpy(Password, value.Password);
	//	Type = value.Type;
	//	HaveComputer = value.HaveComputer;
	//	Login_User_Type = value.Login_User_Type;
	//	Logined = value.Logined;
	//	return *this;
	//}//��Ч��???����
}User_Type;

typedef struct {  //Ԥ����Ϣ�����ݽṹ
	Time_Type Book_Time;						//Ԥ����ʱ��
	Time_Type Book_Time_Long;					//��λ��Ԥ��ʱ��//��λСʱ
	User_Type User_Book_Data;					//Ԥ���û����ݣ����֣�
	ComputerRoom_Type ComputerRoom_Book_Data;   //Ԥ����������
	Computer_Type Computer_Book_Data;			//Ԥ����λ����
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
extern const int Defaut_Font_Size;


//����
int MainStart();
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Recovery_Button_State(int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage);
int Exit();

