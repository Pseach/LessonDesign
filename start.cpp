#include <graphics.h>
#include <string>
#include <io.h>
#include <direct.h>
#include "start.h"		//窗口设置
#include "Buttons.h"	//自定义按钮
#include "AccountControl.h"	//账户控制系统
#include "Book.h"			//预订系统
#include "Query.h"			//查询系统
#include "Manage.h"			//管理系统
#include "DataInput.h"		//自定义输入框
#include "Page.h"

int Page = 0;//切换页面 换按钮

void CreateFolder(std::string str);

//账户全局变量
User_Type Temp_User = { "NONE","NONE",-1,0,0 }; //初始化用户名//初始化密码 //初始化权限 : 未知|用户|管理员//已经有机位了（不用）//登录状态

Windows VerticalWindows = {595,990};
Windows LandscapeWindows = {990,540 + 45};//Defaut : 990 , 540 + 45 
//Windows WindowsSize = LandscapeWindows; //莫名其妙有bug

Windows WindowsSize = { 990,540 + 45 };

//字体全局变量
const int Defaut_Font_Size = (WindowsSize.y - 45) / 6 * 2 / 3 * 4 / 5;

int MainStart() {

	CreateFolder("Files");	//创建空文件夹放置文件

	setinitmode(0); //设置初始化图形的选项和模式
	//initgraph(VerticalWindows.x, VerticalWindows.y, INIT_NOFORCEEXIT); //如果设置width = -1 , height = -1, 那么窗口将会全屏显示(懒得修复全屏bug)  INIT_NOFORCEEXIT , 使关闭窗口的时候不强制退出程序，但窗口会消失，需要配合is_run函数
	initgraph(WindowsSize.x, WindowsSize.y, INIT_NOFORCEEXIT); //如果设置width = -1 , height = -1, 那么窗口将会全屏显示(懒得修复全屏bug) INIT_NOFORCEEXIT , 使关闭窗口的时候不强制退出程序，但窗口会消失，需要配合is_run函数
	setcaption("机房机位预定系统");		//设置窗口标题
	//setinitmode(mode, x, y) x, y 是窗口左上角出现在屏幕的坐标
	setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//设置背景颜色 
	ege_enable_aa(true);//抗锯齿
	InitializeButton();	//初始化按钮（位置）

	bool RefreshPage = true;

	int PressButtonId = -1;
	for (; is_run(); delay_fps(360)) {
		Show_Online_Login_User();	// 每次刷新完页面显示当前账户	//！！！！！！！！！！！！有时候不用刷新！！！！！！！！！！！
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			// 判断鼠标左键按下（左键按下确定位置，同时判断是否为按钮区域
			// 抬起则解除按下状态
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //初始化
				// 检查是否有按钮被按下
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, Defaut_Font_Size);

				// 将被按下的按钮设置为按下状态
				//if (ButtonId != -1) {
				//	PressButtonId = ButtonId;
				//	ButtonLocation[PressButtonId].Pressed = true;
				//	RefreshPage = true;
				//}
				if (ButtonId != -1)	//点住123456按钮
					Initialize_Button_State(ButtonId, PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);
				else {						//没点住123456按钮
					RefreshPage = false; // 不用刷新?
				}
			}
			else { //使恢复 
				//左键抬起，如果有按钮被按下，解除按下状态

				//if (PressButtonId != -1) { //点住123456按钮
				//	ButtonLocation[PressButtonId].Pressed = false;
				//	PressButtonId = -1;
				//	RefreshPage = true;
				//}
				if (PressButtonId != -1)	//点住123456按钮
					Recovery_Button_State(PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);
				else {						//没点住123456按钮
					//RefreshPage = false; // 不用刷新?
				}
			}
		}
		// 判断是否需要重绘，减少不必要的绘制操作
		if (RefreshPage) {
			cleardevice();
			DrawPage(Page);
			RefreshPage = false;
		}
	}
	closegraph(); 	//关闭图形界面
	MessageBox(NULL, TEXT("感谢使用！"), TEXT("机房机位预定系统"), MB_OK | MB_SETFOREGROUND);

	return 0;
}
int Initialize_Button_State(int& ButtonId, int& PressButtonId, bool& ButtonLocationI_Press, bool& RefreshPage) {//封装 //初始化按钮并且执行操作
	PressButtonId = ButtonId;
	ButtonLocation[ButtonId].Pressed = true;	//初始化
	RefreshPage = true;								//使函数执行完刷新页面
	return 1;
}
int Recovery_Button_State(int& PressButtonId, bool & ButtonLocationI_Press, bool& RefreshPage) {//封装 //恢复按钮并且执行操作

	switch (Page) {			//！！！！！！！！可优化！按所用方法标记页码不易进行管理   优化思路：每一页都有自己的分页！！！！！！！！(优化个屁！弃用（不会重载）)
		case 0: {
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: {Add_User(); break; }
				case 2: {Login_User(); break; }
				case 3: {Logout_User(); break; }
				case 4: {Page = 1;  break; }//1
				case 5: {Page = 2;  break;	}//2
				case 6: {Page = 3;  break;}//3
			}
			break;	//Exit Page 0
		}
		case 1:	{
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: { Pre_Book(); break; }
				case 2: { Cancel_Pre_Book(); break; }
				case 3: { Query_IsBooK(); break; }
			}
			break;	//Exit Page 1
		}
		case 2:	{
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: { Computer_Query(); break; }
				case 2: { Computer_Room_Query(); break; }
				case 3: { Computer_Room_Browse(); break; }
			}
			break;	//Exit Page 2
		}
		case 3: {
			switch (PressButtonId) {
				case 0: {Page = 0; break; }
				case 1: {Page = 4; break; }
				case 2: {Page = 5; break; }
				case 3: {Page = 6; break; }
				case 4: {Page = 7; break; }
				case 5: {
					break;
				}
				case 6: {

					break;
				}
			}
			break;	//Exit Page 3
		}
		case 4: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: { break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
		case 5: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: { Add_Computer_Room(); break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
		case 6: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: {Add_Computer(); break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
		case 7: {
			switch (PressButtonId) {
			case 0: {Page = 3; break; }
			case 1: { break; }
			case 2: { break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	//Exit Page 3
		}
	}
	ButtonLocation[PressButtonId].Pressed = false;	//恢复按钮
	PressButtonId = -1;								//初始化按钮（不用？）
	RefreshPage = true;								//使函数执行完刷新页面
	return 1;
}

void CreateFolder(std::string str){// 创建文件夹（需要 #include <io.h> 以及 #include <direct.h>）
	const char* p = str.c_str();
	if (_access(p, 0) == -1) {    // 文件夹不存在则创建文件夹
		(void)_mkdir(p);
	}
}

int Exit() { return 0; }
