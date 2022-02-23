#include <graphics.h>
#include <io.h>
#include <direct.h>
#include "Buttons.h"
#include "DataIO.h"


void CreateFolder();

int MainStart() {
	CreateFolder();
	initgraph(540, 720, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����
	setcaption("������λԤ��ϵͳ");		//���ô��ڱ���
	//setinitmode(mode, x, y) x, y �Ǵ������Ͻǳ�������Ļ������
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//���ñ�����ɫ 
	ege_enable_aa(true);//�����
	bool redraw = true;
	bool clickAdd_User_Button = false;
	bool clickLogin_Button = false;
	bool clickChange_Login_User_Button = false;
	bool clickExit_Button = false;
	for (; is_run(); delay_fps(60)) { 	//is_run()һֱ���� true
		while (mousemsg()) {
			mouse_msg msg = getmouse();

			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {
				if (msg.is_down()) {
					//������İ�ť
					clickAdd_User_Button = insideRectButton(&Add_User_Button, msg.x, msg.y);			//�������˺�
					clickLogin_Button = insideRectButton(&Login_Button, msg.x, msg.y);					//�����¼�˻�
					clickChange_Login_User_Button = insideRectButton(&Change_Login_User_Button, msg.x, msg.y);	//��������˻�
					clickExit_Button = insideRectButton(&Exit_Button, msg.x, msg.y);							//����˳�

				}
				else {
					//���̧�𣬵������ִ��
					if (clickAdd_User_Button){
						clickAdd_User_Button = false;
						redraw = true;
						Add_User();
						
					}
					if (clickLogin_Button) {
						clickLogin_Button = false;
						redraw = true;
						MessageBox(0, 0, 0, 0); // ���������󡱱�ʾ�����Ч
					}
					if (clickChange_Login_User_Button) {
						clickChange_Login_User_Button = false;
						redraw = true;
						MessageBox(0, 0, 0, 0); // ���������󡱱�ʾ�����Ч
					}
					if (clickExit_Button) {
						clickExit_Button = false;
						redraw = true;
						return 0;
					}

				}
			}
		}
		//����
		if (redraw) {
			cleardevice();
			draw();
			redraw = false;
		}
		//cleardevice();	//���������������������ݡ�����ģ����õ�ǰ����ɫ��ջ���
	}

	closegraph(); 	//�ر�ͼ�ν���
	//MessageBox(NULL, "��лʹ��", " ", 0);

	return 0;
}

void CreateFolder() {// �����ļ��У���Ҫ #include <io.h> �Լ� #include <direct.h>��

	char folderName[] = "Files";    //�ļ�������

	if (_access(folderName, 0) == -1) {    // �ļ��в������򴴽��ļ���
		(void)_mkdir(folderName);
	}
}