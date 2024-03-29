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

//Defaut_Font_Size =        BUTTONS_Y_Len * 2 / 3         * 4 / 5;

RectButton HeadlineButton = {
	1 , 
	0 , 0,
	WindowsSize.x , BUTTONS_Y_Len * 2 / 3,
};

RectButton ShowOnline_Login_User = {
	1 ,
	HeadlineButton.Height * 1 / 5 / 2 + HeadlineButton.Height * 4 / 5 * 4 + ((WindowsSize.y - 45) / 6 * 2 / 3 * 4 / 5) / 2 ,
	HeadlineButton.Height * 1 / 5 / 2 ,
	HeadlineButton.Height * 4 / 5 * Max_Input_Num,
	HeadlineButton.Height * 4 / 5
};

RectButton ButtonLocation[10];

int InitializeButton() { //按钮初始化

	ButtonLocation[0] = { 0,WindowsSize.x - Defaut_Font_Size ,HeadlineButton.Height ,Defaut_Font_Size ,Defaut_Font_Size };//返回的（×）
	int t = 0, k = 1;
	for (int i = 1; i <= 6; i++) {
		ButtonLocation[i].IsTitle = 0;
		if (i >= 4 && i <= 6)t = 3, k = 4;
		ButtonLocation[i].X = k * BUTTONS_X_Len;
		ButtonLocation[i].Y = (i - t) * (BUTTONS_Y_Len + HALF_BUTTON_Y_Len);
		ButtonLocation[i].Width = BUTTONS_X_Len;
		ButtonLocation[i].Height = BUTTONS_Y_Len;
	}

	//调个皮~嘻嘻
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

bool insideRectButton(const RectButton* button, int x, int y) {//判断是否点击到了某个按钮
	return (x >= button->X) && (y >= button->Y)
		&& (x < button->X + button->Width)
		&& (y < button->Y + button->Height);
}

void drawRectButton(const RectButton* button) {//////点击特效

	//if (button->IsTitle){
	//	setfillcolor(EGERGB(0x00, 0xFF, 0xFF));//setfillcolor(EGERGB(0x1E, 0x90, 0xFF));
	//}
	//else {
	//	//setfillcolor(EGERGB(0xEA, 0x51, 0x7F));
	//	//setfillcolor(EGERGB(0x00, 0xFF, 0x7F)); //TextColour
	//	setfillcolor(BLUE);
	//}
	//bar(button->X, button->Y, button->X + button->Width, button->Y + button->Height);

}
int searchButton(int x, int y, const RectButton buttonArray[], int length) {	//返回按钮index
	int buttonId = -1;
	for (int i = 0; i < length; i++) {
		if (insideRectButton(&buttonArray[i], x, y)) {
			buttonId = i;
			break;   //退出，已经检测到，后面的按钮不再检测
		}
	}
	return buttonId;
}
//			MessageBox(NULL, TEXT("TEXT"), TEXT("TEXT！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND);
int DrawButtons(Pages pages_name) {//把Page.cpp里定义的页面结构体的页面名称显示在屏幕
	for (int i = 1; i <= 6; i++) {
		std::string str = pages_name.FunName[i];
		const char* p = str.c_str();
		xyprintf(ButtonLocation[i].X, ButtonLocation[i].Y + (BUTTONS_Y_Len - Defaut_Font_Size) / 2, "%s", p);
	}
	return 1;
}
int DrawPage(int& page) {

	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00, 0x00, 0x00)); // 文字颜色
	setfont(Defaut_Font_Size, 0, "方正喵呜体");					//字体大小  宽度比例自适应  字体文件

	//color_t lastFillColor = WHITE;//EGEARGB(WHITE);//= getfillcolor();//这个函数用于获取当前绘图填充色 
	for (int i = 0; i <= PageNum; i++) {	///////点击特效
		//根据状态进行不同的绘制，这里按状态改变颜色
		//color_t ButtonsColour;
		if (ButtonLocation[i].Pressed) {
			//ButtonsColour = EGEARGB(0x00, 0x1E, 0x90, 0xFF); 	//按了 
			drawRectButton(&ButtonLocation[i]);					//显示按钮位置
		}
		else {
			//ButtonsColour = EGEARGB(0x00, 0x40, 0xE0, 0xD0);		//没按 
		}
		////为了减少颜色设置操作进行的优化操作，少量绘制可有可无
		//if (lastFillColor != ButtonsColour) {
		//	setfillcolor(ButtonsColour);

		//	lastFillColor = ButtonsColour;
		//}
	}

	if(page)xyprintf(ButtonLocation[0].X, ButtonLocation[0].Y , "×");		//加上退出的按钮标识
	switch (page) {				///把Page.cpp里定义的页面结构体的页面名称显示在屏幕
		enum { Book_Quarry_Page = 100, ComputerRoom_Quarry_Page = 110, Computer_Quarry_Page = 120, Manage_Book_Page = 130 };
		case 0: {DrawButtons(Menu_Page); break; }
		case 1: {DrawButtons(Book_Page); break; }
		case 2: {DrawButtons(Query_Page); break; }
		case 3: {DrawButtons(Manage_Page); break; }
		case 4: {DrawButtons(User_Manage_Page); break; }
		case 5: {DrawButtons(Computer_Room_Manage_Page); break; }
		case 6: {DrawButtons(Computer_Manage_Page); break; }
		case 7: {DrawButtons(Book_Manage_Page); break; }

		case Book_Quarry_Page: { break; }
		case ComputerRoom_Quarry_Page: { break; }
		case Computer_Quarry_Page: { break; }
		case Manage_Book_Page: { break; }
	}
	return 1;
	
}
