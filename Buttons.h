#pragma once
//����Ŀ¼�ļ�


struct RectButton {// ���ΰ�ť
	int x, y;
	int width, height;
};

extern RectButton ShowOnline_Login_User;

extern RectButton ButtonLocation_0;
extern RectButton ButtonLocation_1;
extern RectButton ButtonLocation_2;
extern RectButton ButtonLocation_3;
extern RectButton ButtonLocation_4;
extern RectButton ButtonLocation_5;
extern RectButton ButtonLocation_6;




// �жϵ�(x, y) �Ƿ��ڰ�ť���������
bool insideRectButton(const RectButton* button, int x, int y);
// ���ư�ť
void drawRectButton(const RectButton* button);

int DrawPage(int& page);