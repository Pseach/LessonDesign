#include <graphics.h>
#include <io.h>
#include <direct.h>
#include "start.h"	//��������
#include "Buttons.h"	
#include "DataIO.h"		

void CreateFolder();

//����


int MainStart() {
	setinitmode(0); //���ó�ʼ��ͼ�ε�ѡ���ģʽ
	CreateFolder();	//�������ļ��з����ļ�
	initgraph(LandscapeWindows.x, LandscapeWindows.y, INIT_NOFORCEEXIT); //�������width = -1 , height = -1, ��ô���ڽ���ȫ����ʾ INIT_NOFORCEEXIT , ʹ�رմ��ڵ�ʱ��ǿ���˳����򣬵����ڻ���ʧ����Ҫ���is_run����
	setcaption("������λԤ��ϵͳ");		//���ô��ڱ���
	//setinitmode(mode, x, y) x, y �Ǵ������Ͻǳ�������Ļ������
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//���ñ�����ɫ 
	ege_enable_aa(true);//�����
	bool redraw = true;

	bool ClickButtonLocation_0 = false;
	bool ClickButtonLocation_1 = false;
	bool ClickButtonLocation_2 = false;
	bool ClickButtonLocation_3 = false;
	bool ClickButtonLocation_4 = false;
	bool ClickButtonLocation_5 = false;
	bool ClickButtonLocation_6 = false;

	int Page = 0;//�л�ҳ������
	for (; is_run(); delay_fps(60)) { 	//is_run()һֱ���� true
		while (mousemsg()) {
			mouse_msg msg = getmouse();

			//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
			if (msg.is_left()) {
				if (msg.is_down()) {
					//������İ�ť
					ClickButtonLocation_0 = insideRectButton(&ButtonLocation_0, msg.x, msg.y);			//�������˺�

				}
				else {
					//���̧�𣬵������ִ��
					if (ClickButtonLocation_0){
						ClickButtonLocation_0 = false;
						redraw = true;
						Add_User();
					}
				}
			}
		}
		//����
		if (redraw) {
			cleardevice();
			DrawPage(0);
			redraw = false;
		}
		//cleardevice();	//���������������������ݡ�����ģ����õ�ǰ����ɫ��ջ���
	}

	closegraph(); 	//�ر�ͼ�ν���
	MessageBox(NULL, TEXT("��лʹ�ã�"), TEXT(" "), MB_OK);

	return 0;
}

void CreateFolder() {// �����ļ��У���Ҫ #include <io.h> �Լ� #include <direct.h>��

	char folderName[] = "Files";    //�ļ�������

	if (_access(folderName, 0) == -1) {    // �ļ��в������򴴽��ļ���
		(void)_mkdir(folderName);
	}
}

int Exit() { return 0; }