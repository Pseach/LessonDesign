#include <graphics.h>
#include <io.h>
#include <direct.h>
#include "start.h"		//��������
#include "Buttons.h"	//�Զ��尴ť
#include "AccountControl.h"	//�˻�����ϵͳ
#include "Book.h"			//Ԥ��ϵͳ
#include "Query.h"			//��ѯϵͳ
#include "Manage.h"			//����ϵͳ
#include "DataInput.h"		//�Զ��������


void CreateFolder();

//�˻�ȫ�ֱ���
User_Type Temp_User = { "NONE","NONE",-1,0,0 }; //��ʼ���û���//��ʼ������ //��ʼ��Ȩ�� : δ֪|�û�|����Ա//�Ѿ��л�λ�ˣ����ã�//��¼״̬

//����ȫ�ֱ���
const int Defaut_Font_Size = ButtonLocation_0.Height * 4 / 5;

Windows VerticalWindows = {595,990};
Windows LandscapeWindows = {990,540 + 45};//Defaut : 990 , 540 + 45 
//Windows WindowsSize = LandscapeWindows; //Ī��������bug
Windows WindowsSize = { 990,540 + 45 };

int MainStart() {
	CreateFolder();	//�������ļ��з����ļ�

	setinitmode(0); //���ó�ʼ��ͼ�ε�ѡ���ģʽ
	//initgraph(VerticalWindows.x, VerticalWindows.y, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ(�����޸�ȫ��bug)  INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����
	initgraph(WindowsSize.x, WindowsSize.y, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ(�����޸�ȫ��bug) INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����
	setcaption("������λԤ��ϵͳ");		//���ô��ڱ���
	//setinitmode(mode, x, y) x, y �Ǵ������Ͻǳ�������Ļ������
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//���ñ�����ɫ 
	ege_enable_aa(true);//�����
	InitializeButton();
	bool ClickButtonLocation_0 = false;

	bool ClickButtonLocation_1 = false;
	bool ClickButtonLocation_2 = false;
	bool ClickButtonLocation_3 = false;
	bool ClickButtonLocation_4 = false;
	bool ClickButtonLocation_5 = false;
	bool ClickButtonLocation_6 = false;

	int Page = 0;//�л�ҳ�� ����ť

	bool RefreshPage = true;

	for (; is_run(); delay_fps(60)) { 	//is_run()һֱ���� true
		Show_Online_Login_User();	// ÿ��ˢ����ҳ����ʾ��ǰ�˻�
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {

				if (msg.is_down()) {
					//������İ�ť

					ClickButtonLocation_1 = insideRectButton(&ButtonLocation[1], msg.x, msg.y);			//���λ��1�İ�ť
					ClickButtonLocation_2 = insideRectButton(&ButtonLocation[2], msg.x, msg.y);
					ClickButtonLocation_3 = insideRectButton(&ButtonLocation[3], msg.x, msg.y);
					ClickButtonLocation_4 = insideRectButton(&ButtonLocation[4], msg.x, msg.y);
					ClickButtonLocation_5 = insideRectButton(&ButtonLocation[5], msg.x, msg.y);
					ClickButtonLocation_6 = insideRectButton(&ButtonLocation[6], msg.x, msg.y);
				}
				else {
					if (Page == 0) {
						if (ClickButtonLocation_1) {					//���̧�𣬵������ִ��
							ClickButtonLocation_1 = false;
							RefreshPage = true;
							Add_User();
						}
						if (ClickButtonLocation_2) {					
							ClickButtonLocation_2 = false;
							RefreshPage = true;
							Login_User();
						}
						if (ClickButtonLocation_3) {
							ClickButtonLocation_3 = false;
							RefreshPage = true;
							Logout_User();
						}
						if (ClickButtonLocation_4) {
							ClickButtonLocation_4 = false;
							RefreshPage = true;
							Page = 1;
							Book();

						}

					}
					else if (Page == 1) {
						if (ClickButtonLocation_1) {
							ClickButtonLocation_1 = false;
							RefreshPage = true;
							 
						}
					}
					 
				}
			}
		}
		if (RefreshPage) {			//ˢ��ҳ��
			cleardevice();			//�����Ļ
			DrawPage(Page);			//������
			RefreshPage = false;	//��ʼ��
		}
	}

	closegraph(); 	//�ر�ͼ�ν���
	MessageBox(NULL, TEXT("��лʹ�ã�"), TEXT("������λԤ��ϵͳ"), MB_OK | MB_SETFOREGROUND);

	return 0;
}

void CreateFolder() {// �����ļ��У���Ҫ #include <io.h> �Լ� #include <direct.h>��

	char folderName[] = "Files";    //�ļ�������

	if (_access(folderName, 0) == -1) {    // �ļ��в������򴴽��ļ���
		(void)_mkdir(folderName);
	}
}

int Exit() { return 0; }