#include <graphics.h>
#include <io.h>
#include <direct.h>
#include "start.h"	//窗口设置
#include "Buttons.h"	
#include "DataIO.h"		

void CreateFolder();

//窗口


int MainStart() {
	setinitmode(0); //设置初始化图形的选项和模式
	CreateFolder();	//创建空文件夹放置文件
	initgraph(LandscapeWindows.x, LandscapeWindows.y, INIT_NOFORCEEXIT); //如果设置width = -1 , height = -1, 那么窗口将会全屏显示 INIT_NOFORCEEXIT , 使关闭窗口的时候不强制退出程序，但窗口会消失，需要配合is_run函数
	setcaption("机房机位预定系统");		//设置窗口标题
	//setinitmode(mode, x, y) x, y 是窗口左上角出现在屏幕的坐标
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//设置背景颜色 
	ege_enable_aa(true);//抗锯齿
	bool redraw = true;

	bool ClickButtonLocation_0 = false;
	bool ClickButtonLocation_1 = false;
	bool ClickButtonLocation_2 = false;
	bool ClickButtonLocation_3 = false;
	bool ClickButtonLocation_4 = false;
	bool ClickButtonLocation_5 = false;
	bool ClickButtonLocation_6 = false;

	int Page = 0;//切换页面来换
	for (; is_run(); delay_fps(60)) { 	//is_run()一直返回 true
		while (mousemsg()) {
			mouse_msg msg = getmouse();

			//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
			if (msg.is_left()) {
				if (msg.is_down()) {
					//检测点击的按钮
					ClickButtonLocation_0 = insideRectButton(&ButtonLocation_0, msg.x, msg.y);			//点击添加账号

				}
				else {
					//左键抬起，点击动作执行
					if (ClickButtonLocation_0){
						ClickButtonLocation_0 = false;
						redraw = true;
						Add_User();
					}
				}
			}
		}
		//绘制
		if (redraw) {
			cleardevice();
			DrawPage(0);
			redraw = false;
		}
		//cleardevice();	//这个函数用于清除画面内容。具体的，是用当前背景色清空画面
	}

	closegraph(); 	//关闭图形界面
	MessageBox(NULL, TEXT("感谢使用！"), TEXT(" "), MB_OK);

	return 0;
}

void CreateFolder() {// 创建文件夹（需要 #include <io.h> 以及 #include <direct.h>）

	char folderName[] = "Files";    //文件夹名称

	if (_access(folderName, 0) == -1) {    // 文件夹不存在则创建文件夹
		(void)_mkdir(folderName);
	}
}

int Exit() { return 0; }