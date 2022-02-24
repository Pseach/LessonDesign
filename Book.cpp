#include "Book.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#include "Buttons.h"
#include "AccountControl.h"

// 按下按钮ID
int pressButtonId = -1;
int Book() {			//预定页面
	setinitmode(0); 
	//initgraph(VerticalWindows.x, VerticalWindows.y, INIT_NOFORCEEXIT); 
	initgraph(WindowsSize.x, WindowsSize.y, INIT_NOFORCEEXIT); 
	setcaption("机房机位预定系统");			//设置窗口标题
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//设置背景颜色 
	ege_enable_aa(true);//抗锯齿

	bool ClickButtonLocation_0 = false;

	bool ClickButtonLocation_1 = false;
	bool ClickButtonLocation_2 = false;
	bool ClickButtonLocation_3 = false;
	bool ClickButtonLocation_4 = false;
	bool ClickButtonLocation_5 = false;
	bool ClickButtonLocation_6 = false;

	bool RefreshPage = true;

	pressButtonId = -1;

	int Page = 0;//切换页面 换按钮



	//for (; is_run(); delay_fps(60)) { 	//is_run()一直返回 true
	//	Show_Online_Login_User();	// 每次刷新完页面显示当前账户
	//	while (mousemsg()) {
	//		mouse_msg msg = getmouse();
	//		//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
	//		if (msg.is_left()) {
	//			if (msg.is_down()) {
	//				//检测点击的按钮
	//				ClickButtonLocation_1 = insideRectButton(&ButtonLocation[1], msg.x, msg.y);			//点击位置1的按钮
	//				ClickButtonLocation_2 = insideRectButton(&ButtonLocation[2], msg.x, msg.y);
	//				ClickButtonLocation_3 = insideRectButton(&ButtonLocation[3], msg.x, msg.y);
	//				ClickButtonLocation_4 = insideRectButton(&ButtonLocation[4], msg.x, msg.y);
	//				ClickButtonLocation_5 = insideRectButton(&ButtonLocation[5], msg.x, msg.y);
	//				ClickButtonLocation_6 = insideRectButton(&ButtonLocation[6], msg.x, msg.y);
	//			}
	//			else {
	//				if (Page == 0) {
	//					if (ClickButtonLocation_1) {					//左键抬起，点击动作执行
	//						ClickButtonLocation_1 = false;
	//						RefreshPage = true;
	//						Add_User();
	//					}
	//					if (ClickButtonLocation_2) {
	//						ClickButtonLocation_2 = false;
	//						RefreshPage = true;
	//						Login_User();
	//					}
	//					if (ClickButtonLocation_3) {
	//						ClickButtonLocation_3 = false;
	//						RefreshPage = true;
	//						Logout_User();
	//					}
	//					if (ClickButtonLocation_4) {
	//						ClickButtonLocation_4 = false;
	//						RefreshPage = true;
	//						Book();
	//					}

	//				}
	//				else if (Page == 1) {
	//					if (ClickButtonLocation_1) {
	//						ClickButtonLocation_1 = false;
	//						RefreshPage = true;

	//					}
	//				}

	//			}
	//		}
	//	}
	//	if (RefreshPage) {			//刷新页面
	//		cleardevice();			//清除屏幕
	//		DrawPage(Page);			//传引用
	//		RefreshPage = false;	//初始化
	//	}

	//	return 1;
	//}


	for (; is_run(); delay_fps(60)) {
		Show_Online_Login_User();	// 每次刷新完页面显示当前账户
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			// 判断鼠标左键按下（左键按下确定位置，同时判断是否为按钮区域
			// 抬起则解除按下状态
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) {
				// 检查是否有按钮被按下
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, Defaut_Font_Size);
				// 将被按下的按钮设置为按下状态
				if (ButtonId != -1) {
					pressButtonId = ButtonId;
					ButtonLocation[pressButtonId].Pressed = true;
					RefreshPage = true;
				}
			}
			else {
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, Defaut_Font_Size);
				//左键抬起，如果有按钮被按下，解除按下状态
				if (pressButtonId != -1) {
					MessageBox(NULL, TEXT("TEXT"), TEXT("TEXT！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND);
					ButtonLocation[pressButtonId].Pressed = false;
					pressButtonId = -1;
					RefreshPage = true;
				}
			}

		}
		// 判断是否需要重绘，减少不必要的绘制操作
		if (RefreshPage) {
			cleardevice();
			DrawPage(Page);
			RefreshPage = false;
		}
		return 1;
	}
}
int Pre_Book(){			//初步预定
	if (MessageBox(NULL, TEXT("TEXT"), TEXT("TEXT！"), MB_YESNO | MB_ICONWARNING | MB_SETFOREGROUND) == 7)return 1;

	return 1;
}
int Cancel_Pre_Book() {	//取消初步预定
	return 1;
}
int Final_Book(){		//最终预定
	return 1;
}