#include <graphics.h>
#include <string>		
#include <io.h>			//�����ļ�������
#include <direct.h>		//�����ļ�������
#include "start.h"		//��������
#include "Buttons.h"	//�Զ��尴ť
#include "AccountControl.h"	//�˻�����ϵͳ
#include "Book.h"			//Ԥ��ϵͳ
#include "Query.h"			//��ѯϵͳ
#include "Manage.h"			//����ϵͳ
#include "DataInput.h"		//�Զ�����������ޣ�
#include "Page.h"

int Page = 0;//�л�ҳ�� ����ť

void CreateFolder(std::string str);

//�˻�ȫ�ֱ���		//�û�|����Ա -1|0|1//�Ƿ�ӵ�л�λ//��¼״̬
User_Type Temp_User = { "NONE","NONE",-1,1,0}; //��ʼ���û���//��ʼ������ //��ʼ��Ȩ�� : δ֪|�û�|����Ա//CanBook//��¼״̬//

Windows VerticalWindows = {595,990};
Windows LandscapeWindows = {990,540 + 45};//Defaut : 990 , 540 + 45 
//Windows WindowsSize = LandscapeWindows; //Ī��������bug

Windows WindowsSize = { 990,540 + 45 };

//����ȫ�ֱ���
const int Defaut_Font_Size = (WindowsSize.y - 45) / 6 * 2 / 3 * 4 / 5;
const int Max_Input_Num = 10;

int MainStart() {

	CreateFolder("Files");	//�������ļ��з����ļ�

	setinitmode(0); //���ó�ʼ��ͼ�ε�ѡ���ģʽ
	//initgraph(VerticalWindows.x, VerticalWindows.y, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ(�����޸�ȫ��bug)  INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����
	initgraph(WindowsSize.x, WindowsSize.y, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ(�����޸�ȫ��bug) INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����

	//setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//���ñ�����ɫ 
	setbkcolor(WHITE);
	PIMAGE pimg = newimage();
	getimage(pimg, "990X585.png");
	putimage(0, 0, pimg);
	delimage(pimg);
	DrawPage(Page);

	setcaption("������λԤ��ϵͳ");		//���ô��ڱ���
	//setinitmode(mode, x, y) x, y �Ǵ������Ͻǳ�������Ļ������
	ege_enable_aa(true);//�����
	InitializeButton();	//��ʼ����ť��λ�ã�

	bool RefreshPage = true;

	int PressButtonId = -1;

	for (; is_run(); delay_fps(90)) {
		/////////////////////////////ÿ��ˢ�¶�Ҫ���»���
		cleardevice();
		PIMAGE pimg = newimage();
		getimage(pimg, "990X585.png");
		putimage(0, 0, pimg);
		delimage(pimg);
		DrawPage(Page);				// ÿ��ˢ����ҳ�水ť����	
		Show_Online_Login_User();	// ÿ��ˢ����ҳ����ʾ��ǰ�˻�	

		while (mousemsg()) {			////////////copy from Intrnet
			mouse_msg msg = getmouse();
			// �ж����������£��������ȷ��λ�ã�ͬʱ�ж��Ƿ�Ϊ��ť����
			// ̧����������״̬
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //��ʼ��
				// ����Ƿ��а�ť������
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, 10);
				// �������µİ�ť����Ϊ����״̬
				//if (ButtonId != -1) {
				//	PressButtonId = ButtonId;
				//	ButtonLocation[PressButtonId].Pressed = true;
				//	RefreshPage = true;
				//}
				if (ButtonId != -1)	//��ס123456��ť
					Initialize_Button_State(ButtonId, PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);//ֻ�ǽ�����ע�ͷ�װ��һ��
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
					Recovery_Button_State(PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);		//ֻ�ǽ�����ע�ͷ�װ��һ�£�ʵ�����������ͷŵ�ʱ��ʵ��ĳЩ����
				else {						//û��ס123456��ť
					//RefreshPage = false; // ����ˢ��?
				}
			}
		}
		// �ж��Ƿ���Ҫ�ػ棬���ٲ���Ҫ�Ļ��Ʋ���
		if (RefreshPage) {
			//cleardevice();
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
		enum { Menu_Page = 0 , Book_Page, Query_Page, Manage_Page, User_Manage_Page, Computer_Room_Manage_Page, Computer_Manage_Page, Book_Manage_Page };
		enum { Book_Quarry_Page = 100, ComputerRoom_Quarry_Page = 110, Computer_Quarry_Page = 120 ,Manage_Book_Page = 130};
		case Menu_Page: {
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: {Add_User(); break; }
				case 2: {Login_User(); break; }
				case 3: {Logout_User(); break; }
				case 4:  if (Temp_User.Type == -1) { MessageBox(NULL, TEXT("����û�е�¼�����¼��"), TEXT("Ȩ�޹���"), MB_OK | MB_SETFOREGROUND); break; }
						{Page = Book_Page;  break; }
				case 5: if (Temp_User.Type == -1) { MessageBox(NULL, TEXT("����û�е�¼�����¼��"), TEXT("Ȩ�޹���"), MB_OK | MB_SETFOREGROUND); break; }//�������ͨ�û����޷��㿪��������
						{Page = Query_Page;  break;	}
				case 6: if (Temp_User.Type == -1) { MessageBox(NULL, TEXT("����û�е�¼�����¼��"), TEXT("Ȩ�޹���"), MB_OK | MB_SETFOREGROUND); break; }//�������ͨ�û����޷��㿪��������
						if (Temp_User.Type != 1) { MessageBox(NULL, TEXT("�����ǹ���Ա����Ȩ���˲�����"), TEXT("Ȩ�޹���"), MB_OK | MB_SETFOREGROUND); break; }//�������ͨ�û����޷��㿪��������
						{Page = Manage_Page;  break;}
			}
			break;	
		}
		case Book_Page:	{
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: { Pre_Book(); break; }
				case 2: { Cancel_Pre_Book(); break; }
				case 3: { Page = Book_Quarry_Page; Query_BooK(); Page = Book_Page; break; }
			}
			break;	
		}
		case Query_Page:	{
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: { Page = Computer_Quarry_Page; Computer_Query();Page = Query_Page; break; }
				case 2: { Page = ComputerRoom_Quarry_Page; Computer_Room_Query(); Page = Query_Page; break; }
				case 3: { Computer_Room_Browse(); break; }
			}
			break;	
		}
		case Manage_Page: {
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: {Page = User_Manage_Page; break; }
				case 2: {Page = Computer_Room_Manage_Page; break; }
				case 3: {Page = Computer_Manage_Page; break; }
				case 4: {Page = Book_Manage_Page; break; }
				case 5: {
					break;
				}
				case 6: {

					break;
				}
			}
			break;
		}
		case User_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: { Delete_User(); break; }
			case 2: { Transform_User_BookPower(); break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}
		case Computer_Room_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: { Add_Computer_Room(); break; }
			case 2: { Delete_Computer_Room(); break; }
			case 3: { Transform_Computer_Room(); break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}
		case Computer_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: { Add_Computer(); break; }
			case 2: { Delete_Computer(); break; }
			case 3: { Transform_Computer(); break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}
		case Book_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: {Page = Manage_Book_Page; Query_BooK(); Page = Book_Manage_Page; break; }
			case 2: { Agree_ALL_Book(); break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}

		 ////////////////////////////////////////////////////////////����ҳ��Ϊ�հ�ҳ�����ڲ�ѯ���ܵĵ���������
		case Book_Quarry_Page: {
			switch (PressButtonId) {
			case 0: {Page = Book_Page; break; }
			}
			break;
		}
		case Computer_Quarry_Page: {
			switch (PressButtonId) {
			case 0: {Page = Query_Page; break; }
			}
			break;
		}
		case ComputerRoom_Quarry_Page: {
			switch (PressButtonId) {
			case 0: {Page = Query_Page; break; }
			}
			break;
		}
		case Manage_Book_Page: {
			switch (PressButtonId) {
			case 0: {Page = Book_Manage_Page; break; }
			}
			break;
		}
		////////////////////////////////////////////////////////////����ҳ��Ϊ�հ�ҳ�����ڲ�ѯ���ܵĵ���������
	}
	ButtonLocation[PressButtonId].Pressed = false;	//�ָ���ť
	PressButtonId = -1;								//��ʼ����ť�����ã���
	RefreshPage = true;								//ʹ����ִ����ˢ��ҳ��
	return 1;
}

void CreateFolder(std::string str){// �����ļ��У���Ҫ #include <io.h> �Լ� #include <direct.h>��
	const char* p = str.c_str();	//stringת��Ϊchar[]����Ȼ���溯���ò���
	if (_access(p, 0) == -1) {    // �ļ��в������򴴽��ļ���
		(void)_mkdir(p);
	}
}

int Exit() { return 0; }
