#include"Buttons.h"
#include <graphics.h>

//定义按钮，确定区域
RectButton Now_User_Button = {
	0 , 0 ,//220, 200,  /* x, y */
	540 , 90,//200, 80,   /* width, height */
	//Now_User_Button.fun[10]={}
};
RectButton Add_User_Button = {
	135 , 144 - 30 ,//220, 200,  /* x, y */
	270 , 114,//200, 80,   /* width, height */
	//Add_User_Button.fun[10]={}
};
RectButton Login_Button = {
	135 , 2 * 144 - 30 ,
	270 , 114,
	//Login_Button.fun[10] = {}
};
RectButton Change_Login_User_Button = {
	135 , 3 * 144 - 30 ,
	270 , 114,
	//Change_Login_User_Button.fun[10] = {}
};
RectButton Exit_Button = {
	135 , 4 * 144 - 30,
	270 , 114,
	//Exit_Button.fun[10] = {}
};



bool insideRectButton(const RectButton* button, int x, int y) {
	return (x >= button->x) && (y >= button->y)
		&& (x < button->x + button->width)
		&& (y < button->y + button->height);
}

void drawRectButton(const RectButton* button) {
	if (button->x == 0 && button->y == 0)setfillcolor(EGERGB(0x00, 0xBF, 0xFF));//setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	else setfillcolor(EGERGB(0xEA, 0x51, 0x7F));
	bar(button->x, button->y, button->x + button->width, button->y + button->height);

}

void draw()
{
	setbkmode(TRANSPARENT);

	setcolor(EGERGB(0xFC, 0xD3, 0x37)); // 文字颜色

	drawRectButton(&Now_User_Button);
	setfont(30, 0, "");						//字体大小  字体文件？
	xyprintf(30, 30, "当前账户：");

	drawRectButton(&Add_User_Button);
	setfont(60, 0, "");
	xyprintf(Add_User_Button.x + 15, Add_User_Button.y + 27, "添加账户");

	drawRectButton(&Login_Button);
	xyprintf(Login_Button.x + 15, Login_Button.y + 27, "登录账户");
	drawRectButton(&Change_Login_User_Button);
	xyprintf(Change_Login_User_Button.x + 15, Change_Login_User_Button.y + 27, "更改账户");
	drawRectButton(&Exit_Button);
	xyprintf(Exit_Button.x + 270 / 2 - 60, Exit_Button.y + 27, "退出");
}
