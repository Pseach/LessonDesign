#include "Book.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#include "Buttons.h"
#include "AccountControl.h"

// ���°�ťID
int pressButtonId = -1;
int Book() {			//Ԥ��ҳ��
	setinitmode(0); 
	//initgraph(VerticalWindows.x, VerticalWindows.y, INIT_NOFORCEEXIT); 
	initgraph(WindowsSize.x, WindowsSize.y, INIT_NOFORCEEXIT); 
	setcaption("������λԤ��ϵͳ");			//���ô��ڱ���
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//���ñ�����ɫ 
	ege_enable_aa(true);//�����

	bool ClickButtonLocation_0 = false;

	bool ClickButtonLocation_1 = false;
	bool ClickButtonLocation_2 = false;
	bool ClickButtonLocation_3 = false;
	bool ClickButtonLocation_4 = false;
	bool ClickButtonLocation_5 = false;
	bool ClickButtonLocation_6 = false;

	bool RefreshPage = true;

	pressButtonId = -1;

	int Page = 0;//�л�ҳ�� ����ť



	//for (; is_run(); delay_fps(60)) { 	//is_run()һֱ���� true
	//	Show_Online_Login_User();	// ÿ��ˢ����ҳ����ʾ��ǰ�˻�
	//	while (mousemsg()) {
	//		mouse_msg msg = getmouse();
	//		//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
	//		if (msg.is_left()) {
	//			if (msg.is_down()) {
	//				//������İ�ť
	//				ClickButtonLocation_1 = insideRectButton(&ButtonLocation[1], msg.x, msg.y);			//���λ��1�İ�ť
	//				ClickButtonLocation_2 = insideRectButton(&ButtonLocation[2], msg.x, msg.y);
	//				ClickButtonLocation_3 = insideRectButton(&ButtonLocation[3], msg.x, msg.y);
	//				ClickButtonLocation_4 = insideRectButton(&ButtonLocation[4], msg.x, msg.y);
	//				ClickButtonLocation_5 = insideRectButton(&ButtonLocation[5], msg.x, msg.y);
	//				ClickButtonLocation_6 = insideRectButton(&ButtonLocation[6], msg.x, msg.y);
	//			}
	//			else {
	//				if (Page == 0) {
	//					if (ClickButtonLocation_1) {					//���̧�𣬵������ִ��
	//						ClickButtonLocation_1 = false;
	//						RefreshPage = true;
	//						Add_User();
	//					}
	//					if (ClickButtonLocation_2) {
	//						ClickButtonLocation_2 = false;
	//						RefreshPage = true;
	//						Login_User();
	//					}
	//					if (ClickButtonLocation_3) {
	//						ClickButtonLocation_3 = false;
	//						RefreshPage = true;
	//						Logout_User();
	//					}
	//					if (ClickButtonLocation_4) {
	//						ClickButtonLocation_4 = false;
	//						RefreshPage = true;
	//						Book();
	//					}

	//				}
	//				else if (Page == 1) {
	//					if (ClickButtonLocation_1) {
	//						ClickButtonLocation_1 = false;
	//						RefreshPage = true;

	//					}
	//				}

	//			}
	//		}
	//	}
	//	if (RefreshPage) {			//ˢ��ҳ��
	//		cleardevice();			//�����Ļ
	//		DrawPage(Page);			//������
	//		RefreshPage = false;	//��ʼ��
	//	}

	//	return 1;
	//}


	for (; is_run(); delay_fps(60)) {
		Show_Online_Login_User();	// ÿ��ˢ����ҳ����ʾ��ǰ�˻�
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			// �ж����������£��������ȷ��λ�ã�ͬʱ�ж��Ƿ�Ϊ��ť����
			// ̧����������״̬
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) {
				// ����Ƿ��а�ť������
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, Defaut_Font_Size);
				// �������µİ�ť����Ϊ����״̬
				if (ButtonId != -1) {
					pressButtonId = ButtonId;
					ButtonLocation[pressButtonId].Pressed = true;
					RefreshPage = true;
				}
			}
			else {
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, Defaut_Font_Size);
				//���̧������а�ť�����£��������״̬
				if (pressButtonId != -1) {
					MessageBox(NULL, TEXT("TEXT"), TEXT("TEXT��"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND);
					ButtonLocation[pressButtonId].Pressed = false;
					pressButtonId = -1;
					RefreshPage = true;
				}
			}

		}
		// �ж��Ƿ���Ҫ�ػ棬���ٲ���Ҫ�Ļ��Ʋ���
		if (RefreshPage) {
			cleardevice();
			DrawPage(Page);
			RefreshPage = false;
		}
		return 1;
	}
}
int Pre_Book(){			//����Ԥ��
	if (MessageBox(NULL, TEXT("TEXT"), TEXT("TEXT��"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;

	return 1;
}
int Cancel_Pre_Book() {	//ȡ������Ԥ��
	return 1;
}
int Final_Book(){		//����Ԥ��
	return 1;
}