#pragma once
//����Ŀ¼�ļ�
struct RectButton {// ���ΰ�ť
	int x, y;
	int width, height;
};

extern RectButton Now_User_Button;
extern RectButton Add_User_Button;
extern RectButton Login_Button;
extern RectButton Change_Login_User_Button;
extern RectButton Exit_Button; //https://zhidao.baidu.com/question/26386872.html ���ļ����ʽṹ��


// �жϵ�(x, y) �Ƿ��ڰ�ť���������
bool insideRectButton(const RectButton* button, int x, int y);
// ���ư�ť
void drawRectButton(const RectButton* button);

void draw();