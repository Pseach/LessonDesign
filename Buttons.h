#pragma once
//����Ŀ¼�ļ�

extern const int ButtonNumber;

struct RectButton {// ���ΰ�ť
	int IsTitle;
	int X, Y;
	int Width, Height;
	bool Pressed;
};

extern RectButton ShowOnline_Login_User;

extern RectButton ButtonLocation_0;

extern RectButton ButtonLocation[10];

int InitializeButton();//��ť��ʼ��

bool insideRectButton(const RectButton* button, int x, int y);// �жϵ�(x, y) �Ƿ��ڰ�ť���������

void drawRectButton(const RectButton* button);// ���ư�ť

int searchButton(int x, int y, const RectButton buttonArray[], int length);// ���� (x, y) ���ڵİ�ť�����ذ�ťID, û�з��� -1

int DrawPage(int& page);