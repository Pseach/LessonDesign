#include "DataInput.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <ege/sys_edit.h>
int IsLegalInput(char* s) {

	char str[11];
	strcpy(str, s);
	if (str == NULL) {
		return 0;
	}
	int i = 0;
	while (str[i] != '\0') {
		if (str[i++] == ' ')return 0;
	}
	return 1;
}
int My_InputBox_Line(){

	return 1;
}

char *My_InputBox_One_Line(sys_edit* editBox) {
	setcolor(BLACK);
	int fontHeight = 48;
	setfont(fontHeight, 0, "����");
	setbkmode(TRANSPARENT);

	editBox->create(false);						//����

	editBox->move(WindowsSize.x/4, WindowsSize.y/4);						//����λ��

	int editTextHeight = Defaut_Font_Size;

	//���óߴ磬�߶�һ��Ҫ���ֵĸ߶�һ�㣬��Ϊ�����ı߿�Ҳռһ����С��
	editBox->size(editTextHeight * 10, editTextHeight + 8);

	editBox->setbgcolor(WHITE);					//���ñ�����ɫ
	editBox->setcolor(BLACK);					//����������ɫ
	editBox->setfont(editTextHeight, 0, "����");	//�������������
	editBox->setmaxlen(8);						//����������󳤶�
	editBox->visible(true);						//ʹ�ɼ�
	editBox->setfocus();							//��ȡ����		

	//�������뻺����
	const int buffSize = 11;
	char strBuffer[11] = "";

	bool CanReturn = false;
	for (; is_run(); delay_fps(60)) {
		bool error = false;				//����Ƿ��������
		bool IsGetText = false;
		//��⵽�س���̧��ͱ�����
		while (kbmsg()) {
			key_msg msg = getkey();
			if ((msg.key == key_enter) && (msg.msg == key_msg_up)) {
				IsGetText = true;
			}
		}
		if (IsGetText) {
			//��ȡ����������ַ���
			editBox->gettext(buffSize, strBuffer);
			//if ()CanReturn = 1;
			//else error = 1;
		}
		//cleardevice();		//����
		setcolor(BLACK);
		//outtextxy(10, 20, "��������:");
		if (CanReturn) {
			if (IsLegalInput(strBuffer)) {	//�����뵫���������
				//���������ʾ
				setcolor(RED);
				outtextxy(100, 60, "�����������������");
			}
			else {		//�����벢��������ȷ
			//				xyprintf(100, 60, "%f", result);
				return strBuffer;
			}
		}

	}
	return 0;
}
