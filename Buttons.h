#pragma once
//三级目录文件

extern const int ButtonNumber;

struct RectButton {// 矩形按钮
	int IsTitle;
	int X, Y;
	int Width, Height;
	bool Pressed;
};

extern RectButton ShowOnline_Login_User;

extern RectButton ButtonLocation_0;

extern RectButton ButtonLocation[10];

int InitializeButton();//按钮初始化

bool insideRectButton(const RectButton* button, int x, int y);// 判断点(x, y) 是否在按钮点击区域内

void drawRectButton(const RectButton* button);// 绘制按钮

int searchButton(int x, int y, const RectButton buttonArray[], int length);// 查找 (x, y) 所在的按钮，返回按钮ID, 没有返回 -1

int DrawPage(int& page);