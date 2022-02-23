#include <graphics.h>
#include <io.h>
#include <direct.h>
#include "Buttons.h"
#include "DataIO.h"


void CreateFolder();

int MainStart() {
	CreateFolder();
	initgraph(540, 720, INIT_NOFORCEEXIT); //如果设置width = -1 , height = -1, 那么窗口将会全屏显示 INIT_NOFORCEEXIT , 使关闭窗口的时候不强制退出程序，但窗口会消失，需要配合is_run函数
	setcaption("机房机位预定系统");		//设置窗口标题
	//setinitmode(mode, x, y) x, y 是窗口左上角出现在屏幕的坐标
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//设置背景颜色 
	ege_enable_aa(true);//抗锯齿
	bool redraw = true;
	bool clickAdd_User_Button = false;
	bool clickLogin_Button = false;
	bool clickChange_Login_User_Button = false;
	bool clickExit_Button = false;
	for (; is_run(); delay_fps(60)) { 	//is_run()一直返回 true
		while (mousemsg()) {
			mouse_msg msg = getmouse();

			//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
			if (msg.is_left()) {
				if (msg.is_down()) {
					//检测点击的按钮
					clickAdd_User_Button = insideRectButton(&Add_User_Button, msg.x, msg.y);			//点击添加账号
					clickLogin_Button = insideRectButton(&Login_Button, msg.x, msg.y);					//点击登录账户
					clickChange_Login_User_Button = insideRectButton(&Change_Login_User_Button, msg.x, msg.y);	//点击更改账户
					clickExit_Button = insideRectButton(&Exit_Button, msg.x, msg.y);							//点击退出

				}
				else {
					//左键抬起，点击动作执行
					if (clickAdd_User_Button){
						clickAdd_User_Button = false;
						redraw = true;
						Add_User();
						
					}
					if (clickLogin_Button) {
						clickLogin_Button = false;
						redraw = true;
						MessageBox(0, 0, 0, 0); // 弹出“错误”表示点击有效
					}
					if (clickChange_Login_User_Button) {
						clickChange_Login_User_Button = false;
						redraw = true;
						MessageBox(0, 0, 0, 0); // 弹出“错误”表示点击有效
					}
					if (clickExit_Button) {
						clickExit_Button = false;
						redraw = true;
						return 0;
					}

				}
			}
		}
		//绘制
		if (redraw) {
			cleardevice();
			draw();
			redraw = false;
		}
		//cleardevice();	//这个函数用于清除画面内容。具体的，是用当前背景色清空画面
	}

	closegraph(); 	//关闭图形界面
	//MessageBox(NULL, "感谢使用", " ", 0);

	return 0;
}

void CreateFolder() {// 创建文件夹（需要 #include <io.h> 以及 #include <direct.h>）

	char folderName[] = "Files";    //文件夹名称

	if (_access(folderName, 0) == -1) {    // 文件夹不存在则创建文件夹
		(void)_mkdir(folderName);
	}
}