#include"Buttons.h"
#include <graphics.h>
#include "start.h" // WindowsSize 
#include "AccountControl.h"

//LandscapeWindows.x = 990 .y=540+45;
const int BUTTONS_X_Len = WindowsSize.x / 6, BUTTONS_Y_Len = (WindowsSize.y - 45) / 6;
const int HALF_BUTTON_Y_Len = BUTTONS_Y_Len / 2;

RectButton ButtonLocation_0 = {
	0 , 0,
	WindowsSize.x , BUTTONS_Y_Len - 30,
};

RectButton ShowOnline_Login_User = {
	ButtonLocation_0.Height * 1 / 5 / 2 + ButtonLocation_0.Height * 4 / 5 * 4,
	ButtonLocation_0.Height * 1 / 5 / 2 ,
	ButtonLocation_0.Height * 4 / 5 * 40,
	ButtonLocation_0.Height * 4 / 5 
};

RectButton ButtonLocation[10];

int InitializeButton() { //��ť��ʼ��
	int t = 0, k = 1;
	for (int i = 1; i <= 6; i++) {
		if (i >= 4 && i <= 6)t = 3, k = 4;
		ButtonLocation[i].X = k * BUTTONS_X_Len;
		ButtonLocation[i].Y = (i - t) * (BUTTONS_Y_Len + HALF_BUTTON_Y_Len);
		ButtonLocation[i].Width = BUTTONS_X_Len;
		ButtonLocation[i].Height = BUTTONS_X_Len;
	}//����Ƥ~����
	//for (int i = 4; i <= 6; i++) {
	//	ButtonLocation[i].X = 4 * BUTTONS_X_Len;
	//	ButtonLocation[i].Y = (i - 3) * (BUTTONS_Y_Len + HALF_BUTTON_Y_Len);
	//	ButtonLocation[i].Width = BUTTONS_X_Len;
	//	ButtonLocation[i].Height = BUTTONS_X_Len;
	//}
	return 1;
}

bool insideRectButton(const RectButton* button, int x, int y) {
	return (x >= button->X) && (y >= button->Y)
		&& (x < button->X + button->Width)
		&& (y < button->Y + button->Height);
}

void drawRectButton(const RectButton* button) {
	if ((button->X == 0 && button->Y == 0)||(button->X == ButtonLocation_0.Height * 1 / 5 / 2 + ButtonLocation_0.Height * 4 / 5 * 4 && button->Y == ButtonLocation_0.Height * 1 / 5 / 2)){
		setfillcolor(EGERGB(0x00, 0xFF, 0xFF));//setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	}
	else {
		setfillcolor(EGERGB(0xEA, 0x51, 0x7F));
		//setfillcolor(EGERGB(0x00, 0xFF, 0x7F)); //TextColour

	}
	bar(button->X, button->Y, button->X + button->Width, button->Y + button->Height);
}

int searchButton(int x, int y, const RectButton buttonArray[], int length)	//���ذ�ťindex
{
	int buttonId = -1;

	for (int i = 0; i < length; i++) {
		if (insideRectButton(&buttonArray[i], x, y)) {
			buttonId = i;
			break;   //�˳����Ѿ���⵽������İ�ť���ټ��
		}
	}

	return buttonId;
}

int DrawPage(int& page) {


	//color_t lastFillColor = getfillcolor();//����������ڻ�ȡ��ǰ��ͼ���ɫ 
	//for (int i = 0; i < length; i++) {
	//	//����״̬���в�ͬ�Ļ��ƣ����ﰴ״̬�ı���ɫ
	//	color_t ButtonsColour;
	//	if (buttonArray[i].pressed) {
	//		ButtonsColour = EGEARGB(0x50, 0x1E, 0x90, 0xFF); 	//���� 
	//	}
	//	else {
	//		ButtonsColour = EGEARGB(0x66, 0x40, 0xE0, 0xD0);		//û�� 
	//	}
	//	//Ϊ�˼�����ɫ���ò������е��Ż��������������ƿ��п���
	//	if (lastFillColor != ButtonsColour) {
	//		setfillcolor(ButtonsColour);
	//		lastFillColor = ButtonsColour;
	//	}
	//	// ���ư�ť
	//	ege_fillellipse(buttonArray[i].x - buttonArray[i].radius,
	//		buttonArray[i].y - buttonArray[i].radius,
	//		2 * buttonArray[i].radius,
	//		2 * buttonArray[i].radius);

	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // ������ɫ
	setfont(Defaut_Font_Size, 0, "����������");					//�����С  ��ȱ�������Ӧ  �����ļ�

	if(page==0){	//�˵�ҳ �·���ť 

		drawRectButton(&ButtonLocation[1]);
		xyprintf(ButtonLocation[1].X, ButtonLocation[1].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "����˻�");

		drawRectButton(&ButtonLocation[2]);
		xyprintf(ButtonLocation[2].X, ButtonLocation[2].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "��¼�˻�");

		drawRectButton(&ButtonLocation[3]);
		xyprintf(ButtonLocation[3].X, ButtonLocation[3].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "�˳��˻�");

		drawRectButton(&ButtonLocation[4]);
		xyprintf(ButtonLocation[4].X, ButtonLocation[4].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "Ԥ��ϵͳ");

		drawRectButton(&ButtonLocation[5]);
		xyprintf(ButtonLocation[5].X, ButtonLocation[5].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "��ѯϵͳ");

		drawRectButton(&ButtonLocation[6]);
		xyprintf(ButtonLocation[6].X, ButtonLocation[6].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "����ϵͳ");
		return 0;
	}
	if (page == 1) {
		drawRectButton(&ButtonLocation[1]);
		xyprintf(ButtonLocation[1].X, ButtonLocation[1].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "����Ԥ��");

		drawRectButton(&ButtonLocation[2]);
		xyprintf(ButtonLocation[2].X, ButtonLocation[2].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "ȡ��Ԥ��");

		drawRectButton(&ButtonLocation[3]);
		xyprintf(ButtonLocation[3].X, ButtonLocation[3].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "����Ԥ��");
	}
}
