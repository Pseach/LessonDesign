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

int InitializeButton() { //按钮初始化
	int t = 0, k = 1;
	for (int i = 1; i <= 6; i++) {
		if (i >= 4 && i <= 6)t = 3, k = 4;
		ButtonLocation[i].X = k * BUTTONS_X_Len;
		ButtonLocation[i].Y = (i - t) * (BUTTONS_Y_Len + HALF_BUTTON_Y_Len);
		ButtonLocation[i].Width = BUTTONS_X_Len;
		ButtonLocation[i].Height = BUTTONS_X_Len;
	}//调个皮~嘻嘻
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

int searchButton(int x, int y, const RectButton buttonArray[], int length)	//返回按钮index
{
	int buttonId = -1;

	for (int i = 0; i < length; i++) {
		if (insideRectButton(&buttonArray[i], x, y)) {
			buttonId = i;
			break;   //退出，已经检测到，后面的按钮不再检测
		}
	}

	return buttonId;
}

int DrawPage(int& page) {


	//color_t lastFillColor = getfillcolor();//这个函数用于获取当前绘图填充色 
	//for (int i = 0; i < length; i++) {
	//	//根据状态进行不同的绘制，这里按状态改变颜色
	//	color_t ButtonsColour;
	//	if (buttonArray[i].pressed) {
	//		ButtonsColour = EGEARGB(0x50, 0x1E, 0x90, 0xFF); 	//按了 
	//	}
	//	else {
	//		ButtonsColour = EGEARGB(0x66, 0x40, 0xE0, 0xD0);		//没按 
	//	}
	//	//为了减少颜色设置操作进行的优化操作，少量绘制可有可无
	//	if (lastFillColor != ButtonsColour) {
	//		setfillcolor(ButtonsColour);
	//		lastFillColor = ButtonsColour;
	//	}
	//	// 绘制按钮
	//	ege_fillellipse(buttonArray[i].x - buttonArray[i].radius,
	//		buttonArray[i].y - buttonArray[i].radius,
	//		2 * buttonArray[i].radius,
	//		2 * buttonArray[i].radius);

	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // 文字颜色
	setfont(Defaut_Font_Size, 0, "方正喵呜体");					//字体大小  宽度比例自适应  字体文件

	if(page==0){	//菜单页 下方按钮 

		drawRectButton(&ButtonLocation[1]);
		xyprintf(ButtonLocation[1].X, ButtonLocation[1].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "添加账户");

		drawRectButton(&ButtonLocation[2]);
		xyprintf(ButtonLocation[2].X, ButtonLocation[2].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "登录账户");

		drawRectButton(&ButtonLocation[3]);
		xyprintf(ButtonLocation[3].X, ButtonLocation[3].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "退出账户");

		drawRectButton(&ButtonLocation[4]);
		xyprintf(ButtonLocation[4].X, ButtonLocation[4].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "预订系统");

		drawRectButton(&ButtonLocation[5]);
		xyprintf(ButtonLocation[5].X, ButtonLocation[5].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "查询系统");

		drawRectButton(&ButtonLocation[6]);
		xyprintf(ButtonLocation[6].X, ButtonLocation[6].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "管理系统");
		return 0;
	}
	if (page == 1) {
		drawRectButton(&ButtonLocation[1]);
		xyprintf(ButtonLocation[1].X, ButtonLocation[1].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "初步预定");

		drawRectButton(&ButtonLocation[2]);
		xyprintf(ButtonLocation[2].X, ButtonLocation[2].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "取消预定");

		drawRectButton(&ButtonLocation[3]);
		xyprintf(ButtonLocation[3].X, ButtonLocation[3].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "最终预定");
	}
}
