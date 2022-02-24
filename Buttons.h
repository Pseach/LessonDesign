#pragma once
//三级目录文件


struct RectButton {// 矩形按钮
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




// 判断点(x, y) 是否在按钮点击区域内
bool insideRectButton(const RectButton* button, int x, int y);
// 绘制按钮
void drawRectButton(const RectButton* button);

int DrawPage(int& page);