#include"Buttons.h"
#include <graphics.h>
#include "start.h" // LandscapeWindows 
#include "AccountControl.h"

//LandscapeWindows.x = 990 .y=540+45;
const int BUTTONS_X_Len = LandscapeWindows.x / 6, BUTTONS_Y_Len = (LandscapeWindows.y - 45) / 6;
const int HALF_BUTTON_Y_Len = BUTTONS_Y_Len / 2;

RectButton ButtonLocation_0 = {
	0 , 0,
	LandscapeWindows.x , BUTTONS_Y_Len - 30,
};

RectButton ShowOnline_Login_User = {
	ButtonLocation_0.height * 1 / 5 / 2 + ButtonLocation_0.height * 4 / 5 * 4,
	ButtonLocation_0.height * 1 / 5 / 2 ,
	ButtonLocation_0.height * 4 / 5 * 40,
	ButtonLocation_0.height * 4 / 5 
};

RectButton ButtonLocation_1 = {
	BUTTONS_X_Len , 1 * BUTTONS_Y_Len + 1 * HALF_BUTTON_Y_Len ,
	BUTTONS_X_Len , BUTTONS_Y_Len,
};
RectButton ButtonLocation_2 = {
	BUTTONS_X_Len , 2 * BUTTONS_Y_Len + 2 * HALF_BUTTON_Y_Len ,
	BUTTONS_X_Len , BUTTONS_Y_Len,
};
RectButton ButtonLocation_3 = {
	BUTTONS_X_Len , 3 * BUTTONS_Y_Len + 3 * HALF_BUTTON_Y_Len ,
	BUTTONS_X_Len , BUTTONS_Y_Len,
};

RectButton ButtonLocation_4 = {
	BUTTONS_X_Len * 4, 1 * BUTTONS_Y_Len + 1 * HALF_BUTTON_Y_Len ,
	BUTTONS_X_Len , BUTTONS_Y_Len,
};
RectButton ButtonLocation_5 = {
	BUTTONS_X_Len * 4, 2 * BUTTONS_Y_Len + 2 *HALF_BUTTON_Y_Len ,
	BUTTONS_X_Len , BUTTONS_Y_Len,
};
RectButton ButtonLocation_6 = {
	BUTTONS_X_Len * 4, 3 * BUTTONS_Y_Len + 3 *HALF_BUTTON_Y_Len ,
	BUTTONS_X_Len , BUTTONS_Y_Len,
};


bool insideRectButton(const RectButton* button, int x, int y) {
	return (x >= button->x) && (y >= button->y)
		&& (x < button->x + button->width)
		&& (y < button->y + button->height);
}

void drawRectButton(const RectButton* button) {
	if ((button->x == 0 && button->y == 0)||(button->x == ButtonLocation_0.height * 1 / 5 / 2 + ButtonLocation_0.height * 4 / 5 * 4 && button->y == ButtonLocation_0.height * 1 / 5 / 2)){
		setfillcolor(EGERGB(0x00, 0xFF, 0xFF));//setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	}
	else {
		setfillcolor(EGERGB(0xEA, 0x51, 0x7F));
	}
	bar(button->x, button->y, button->x + button->width, button->y + button->height);
}

int DrawPage(int& page) {
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // 文字颜色
	setfont(Defaut_Font_Size, 0, "方正喵呜体");					//字体大小  宽度比例自适应  字体文件

	if(page==0){	//菜单页 下方按钮 

		drawRectButton(&ButtonLocation_1);
		xyprintf(ButtonLocation_1.x , ButtonLocation_1.y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "添加账户");

		drawRectButton(&ButtonLocation_2);
		xyprintf(ButtonLocation_2.x, ButtonLocation_2.y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "登录账户");

		drawRectButton(&ButtonLocation_3);
		xyprintf(ButtonLocation_3.x, ButtonLocation_3.y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "退出账户");

		drawRectButton(&ButtonLocation_4);
		xyprintf(ButtonLocation_4.x, ButtonLocation_4.y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "预订系统");

		drawRectButton(&ButtonLocation_5);
		xyprintf(ButtonLocation_5.x, ButtonLocation_5.y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "查询系统");

		drawRectButton(&ButtonLocation_6);
		xyprintf(ButtonLocation_6.x, ButtonLocation_6.y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "管理系统");
		return 0;
	}
	if (page == 1) {

	}
}
