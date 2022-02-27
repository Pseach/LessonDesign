#include"Buttons.h"
#include <graphics.h>
#include "start.h" // WindowsSize 
#include "AccountControl.h"
#include <string>
#include "Page.h"

const int ButtonNumber = 6;
const int PageNum = 7;
//(WindowsSize.y - 45) / 6 * 2 / 3
//LandscapeWindows.x = 990 .y=540+45;

const int BUTTONS_X_Len = WindowsSize.x / 6, BUTTONS_Y_Len = (WindowsSize.y - 45) / 6;
const int HALF_BUTTON_Y_Len = BUTTONS_Y_Len / 2;

RectButton ButtonLocation_0 = {
	1 , 
	0 , 0,
	WindowsSize.x , BUTTONS_Y_Len * 2 / 3,
};

RectButton ShowOnline_Login_User = {
	1 ,
	ButtonLocation_0.Height * 1 / 5 / 2 + ButtonLocation_0.Height * 4 / 5 * 4,
	ButtonLocation_0.Height * 1 / 5 / 2 ,
	ButtonLocation_0.Height * 4 / 5 * 40,
	ButtonLocation_0.Height * 4 / 5 
};

RectButton ButtonLocation[10];

int InitializeButton() { //��ť��ʼ��
	ButtonLocation[0] = { 0,WindowsSize.x - Defaut_Font_Size ,ButtonLocation_0.Height ,Defaut_Font_Size ,Defaut_Font_Size };//���صģ�����
	int t = 0, k = 1;
	for (int i = 1; i <= 6; i++) {
		ButtonLocation[i].IsTitle = 0;
		if (i >= 4 && i <= 6)t = 3, k = 4;
		ButtonLocation[i].X = k * BUTTONS_X_Len;
		ButtonLocation[i].Y = (i - t) * (BUTTONS_Y_Len + HALF_BUTTON_Y_Len);
		ButtonLocation[i].Width = BUTTONS_X_Len;
		ButtonLocation[i].Height = BUTTONS_Y_Len;
	}//����Ƥ~����
	//for (int i = 1; i <= 3; i++) {
	//	ButtonLocation[i].X =  BUTTONS_X_Len;
	//	ButtonLocation[i].Y = i *(BUTTONS_Y_Len + HALF_BUTTON_Y_Len);
	//	ButtonLocation[i].Width = BUTTONS_X_Len;
	//	ButtonLocation[i].Height = BUTTONS_Y_Len;
	//}
	//for (int i = 4; i <= 6; i++) {
	//	ButtonLocation[i].X = 4 * BUTTONS_X_Len;
	//	ButtonLocation[i].Y = (i - 3) * (BUTTONS_Y_Len + HALF_BUTTON_Y_Len);
	//	ButtonLocation[i].Width = BUTTONS_X_Len;
	//	ButtonLocation[i].Height = BUTTONS_Y_Len;
	//}

	return 1;
}

bool insideRectButton(const RectButton* button, int x, int y) {
	return (x >= button->X) && (y >= button->Y)
		&& (x < button->X + button->Width)
		&& (y < button->Y + button->Height);
}

void drawRectButton(const RectButton* button) {

	if (button->IsTitle){
		setfillcolor(EGERGB(0x00, 0xFF, 0xFF));//setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	}
	else {
		//setfillcolor(EGERGB(0xEA, 0x51, 0x7F));
		//setfillcolor(EGERGB(0x00, 0xFF, 0x7F)); //TextColour
		setfillcolor(BLUE);
	}
	bar(button->X, button->Y, button->X + button->Width, button->Y + button->Height);
}


void DrawRectButton(const RectButton* button, color_t Colour) {

	if (button->IsTitle) {
		setfillcolor(EGERGB(0x00, 0xFF, 0xFF));//setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	}
	else {
		//setfillcolor(EGERGB(0xEA, 0x51, 0x7F));
		//setfillcolor(EGERGB(0x00, 0xFF, 0x7F)); //TextColour
		setfillcolor(BLUE);
	}
	bar(button->X, button->Y, button->X + button->Width, button->Y + button->Height);
}

int searchButton(int x, int y, const RectButton buttonArray[], int length) {	//���ذ�ťindex
	int buttonId = -1;
	for (int i = 0; i < length; i++) {
		if (insideRectButton(&buttonArray[i], x, y)) {
			buttonId = i;
			break;   //�˳����Ѿ���⵽������İ�ť���ټ��
		}
	}
	return buttonId;
}
//			MessageBox(NULL, TEXT("TEXT"), TEXT("TEXT��"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND);
int DrawButtons(Pages pages_name) {
	for (int i = 1; i <= 6; i++) {
		std::string str = pages_name.FunName[i];
		const char* p = str.c_str();
		xyprintf(ButtonLocation[i].X, ButtonLocation[i].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "%s", p);
	}
	return 1;
}
int DrawPage(int& page) {

	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // ������ɫ
	setfont(Defaut_Font_Size, 0, "����������");					//�����С  ��ȱ�������Ӧ  �����ļ�

	//color_t lastFillColor = WHITE;//EGEARGB(WHITE);//= getfillcolor();//����������ڻ�ȡ��ǰ��ͼ���ɫ 
	for (int i = 0; i <= PageNum; i++) {
		//����״̬���в�ͬ�Ļ��ƣ����ﰴ״̬�ı���ɫ
		//color_t ButtonsColour;
		if (ButtonLocation[i].Pressed) {
			//ButtonsColour = EGEARGB(0x00, 0x1E, 0x90, 0xFF); 	//���� 
			drawRectButton(&ButtonLocation[i]);					//��ʾ��ťλ��
		}
		else {
			//ButtonsColour = EGEARGB(0x00, 0x40, 0xE0, 0xD0);		//û�� 
		}
		////Ϊ�˼�����ɫ���ò������е��Ż��������������ƿ��п���
		//if (lastFillColor != ButtonsColour) {
		//	setfillcolor(ButtonsColour);

		//	lastFillColor = ButtonsColour;
		//}
	}

	if(page)xyprintf(ButtonLocation[0].X, ButtonLocation[0].Y , "��");
	switch (page) {
		case 0: {DrawButtons(Menu_Page); break; }
		case 1: {DrawButtons(Book_Page); break; }
		case 2: {DrawButtons(Query_Page); break; }
		case 3: {DrawButtons(Manage_Page); break; }
		case 4: {DrawButtons(User_Manage_Page); break; }
		case 5: {DrawButtons(Computer_Room_Manage_Page); break; }
		case 6: {DrawButtons(Computer_Manage_Page); break; }
		case 7: {DrawButtons(Book_Manage_Page); break; }
	}
	//if (page == 0)	DrawButtons(Menu_Page);
	//if (page == 1)	DrawButtons(Book_Page); 
	//if (page == 2)	DrawButtons(Query_Page);
	//if (page == 3)	DrawButtons(Manage_Page);
	//if (page == 4)	DrawButtons(User_Manage_Page);
	//if (page == 5)	DrawButtons(Computer_Room_Manage_Page);
	//if (page == 6)	DrawButtons(Computer_Manage_Page);
	//if (page == 7)	DrawButtons(Book_Manage_Page);
	return 1;
	
}
