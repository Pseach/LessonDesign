#pragma once
//����Ŀ¼�ļ�

int Manage();

int ComputerRoom_Num();
bool HaveComputerRoom(char Static_ComputerRoomName[]);
bool HaveComputer(char Static_ComputerName[]);

//�û�����ϵͳ
int User_Manage();				//�����û�
int Transform_User_BookPower();	//����|�ر��û�Ԥ������
int Delete_User();		//ɾ���û�
int Change_User();		//�����û�

//��������ϵͳ
int Computer_Room_Manage();			//��������
int Transform_Computer_Room();	//����|�رջ���
int Add_Computer_Room();	//���ӻ���
int Delete_Computer_Room();	//ɾ������
int Change_Computer_Room();	//���Ļ���

//��λ����ϵͳ
int Computer_Manage();			//��λ����
int Transform_Computer();	//����|�رջ�λ 
int Add_Computer();		//���ӻ�λ
int Delete_Computer();	//ɾ����λ
int Change_Computer();	//���Ļ�λ

//Ԥ������
int Search_All_Book();
int Agree_ALL_Book();