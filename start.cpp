#include <graphics.h>
#include <string>
#include <io.h>
#include <direct.h>
#include "start.h"		//��������
#include "Buttons.h"	//�Զ��尴ť
#include "AccountControl.h"	//�˻�����ϵͳ
#include "Book.h"			//Ԥ��ϵͳ
#include "Query.h"			//��ѯϵͳ
#include "Manage.h"			//����ϵͳ
#include "DataInput.h"		//�Զ��������
#include "Page.h"

int Page = 0;//�л�ҳ�� ����ť

void CreateFolder(std::string str);

//�˻�ȫ�ֱ���
User_Type Temp_User = { "NONE","NONE",-1,0,0 }; //��ʼ���û���//��ʼ������ //��ʼ��Ȩ�� : δ֪|�û�|����Ա//�Ѿ��л�λ�ˣ����ã�//��¼״̬

Windows VerticalWindows = {595,990};
Windows LandscapeWindows = {990,540 + 45};//Defaut : 990 , 540 + 45 
//Windows WindowsSize = LandscapeWindows; //Ī��������bug

Windows WindowsSize = { 990,540 + 45 };

//����ȫ�ֱ���
const int Defaut_Font_Size = (WindowsSize.y - 45) / 6 * 2 / 3 * 4 / 5;

int MainStart() {

	CreateFolder("Files");	//�������ļ��з����ļ�

	setinitmode(0); //���ó�ʼ��ͼ�ε�ѡ���ģʽ
	//initgraph(VerticalWindows.x, VerticalWindows.y, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ(�����޸�ȫ��bug)  INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����
	initgraph(WindowsSize.x, WindowsSize.y, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ(�����޸�ȫ��bug) INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����
	setcaption("������λԤ��ϵͳ");		//���ô��ڱ���
	//setinitmode(mode, x, y) x, y �Ǵ������Ͻǳ�������Ļ������
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//���ñ�����ɫ 
	ege_enable_aa(true);//�����
	InitializeButton();	//��ʼ����ť��λ�ã�

	bool RefreshPage = true;

	int PressButtonId = -1;
	for (; is_run(); delay_fps(360)) {
		Show_Online_Login_User();	// ÿ��ˢ����ҳ����ʾ��ǰ�˻�	//��������������������������ʱ����ˢ�£���������������������
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			// �ж����������£��������ȷ��λ�ã�ͬʱ�ж��Ƿ�Ϊ��ť����
			// ̧����������״̬
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //��ʼ��
				// ����Ƿ��а�ť������
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, Defaut_Font_Size);

				// �������µİ�ť����Ϊ����״̬
				//if (ButtonId != -1) {
				//	PressButtonId = ButtonId;
				//	ButtonLocation[PressButtonId].Pressed = true;
				//	RefreshPage = true;
				//}
				if (ButtonId != -1)	//��ס123456��ť
					Initialize_Button_State(ButtonId, PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);
				else {						//û��ס123456��ť
					RefreshPage = false; // ����ˢ��?
				}
			}
			else { //ʹ�ָ� 
				//���̧������а�ť�����£��������״̬

				//if (PressButtonId != -1) { //��ס123456��ť
				//	ButtonLocation[PressButtonId].Pressed = false;
				//	PressButtonId = -1;
				//	RefreshPage = true;
				//}
				if (PressButtonId != -1)	//��ס123456��ť
					Recovery_Button_State(PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);
				else {						//û��ס123456��ť
					//RefreshPage = false; // ����ˢ��?
				}
			}
		}
		// �ж��Ƿ���Ҫ�ػ棬���ٲ���Ҫ�Ļ��Ʋ���
		if (RefreshPage) {
			cleardevice();
			DrawPage(Page);
			RefreshPage = false;
		}
	}
	closegraph(); 	//�ر�ͼ�ν���
	MessageBox(NULL, TEXT("��лʹ�ã�"), TEXT("������λԤ��ϵͳ"), MB_OK | MB_SETFOREGROUND);

	return 0;
}
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage) {//��װ //��ʼ����ť����ִ�в���
	PressButtonId = ButtonId;
	ButtonLocation[ButtonId].Pressed = true;	//��ʼ��
	RefreshPage = true;								//ʹ����ִ����ˢ��ҳ��
	return 1;
}
int Recovery_Button_State(int& PressButtonId, bool & ButtonLocationI_Press, bool& RefreshPage) {//��װ //�ָ���ť����ִ�в���

	switch (Page) {			//�������������������Ż��������÷������ҳ�벻�׽��й���   �Ż�˼·��ÿһҳ�����Լ��ķ�ҳ����������������(�Ż���ƨ�����ã��������أ�)
		case 0: {
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: {Add_User(); break; }
				case 2: {Login_User(); break; }
				case 3: {Logout_User(); break; }
				case 4: {Page = 1;  break; }//1
				case 5: {Page = 2;  break;	}//2
				case 6: {Page = 3;  break;}//3
			}
			break;	//Exit Page 0
		}
		case 1:	{
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: { Pre_Book(); break; }
				case 2: { Cancel_Pre_Book(); break; }
				case 3: { Query_IsBooK(); break; }
			}
			break;	//Exit Page 1
		}
		case 2:	{
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: { Computer_Query(); break; }
				case 2: { Computer_Room_Query(); break; }
				case 3: { Computer_Room_Browse(); break; }
			}
			break;	//Exit Page 2
		}
		case 3: {
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: {Page = 4; break; }
				case 2: {Page = 5; break; }
				case 3: {Page = 6; break; }
				case 4: {Page = 7; break; }
				case 5: {
					break;
				}
				case 6: {

					break;
				}
			}
			break;	//Exit Page 3
		}
		case 4: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: { break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
		case 5: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: { Add_Computer_Room(); break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
		case 6: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: {Add_Computer(); break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
		case 7: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: { break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
	}
	ButtonLocation[PressButtonId].Pressed = false;	//�ָ���ť
	PressButtonId = -1;								//��ʼ����ť�����ã���
	RefreshPage = true;								//ʹ����ִ����ˢ��ҳ��
	return 1;
}

void CreateFolder(std::string str){// �����ļ��У���Ҫ #include <io.h> �Լ� #include <direct.h>��
	const char* p = str.c_str();
	if (_access(p, 0) == -1) {    // �ļ��в������򴴽��ļ���
		(void)_mkdir(p);
	}
}

int Exit() { return 0; }
