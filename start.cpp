#include <graphics.h>
#include <string>		
#include <io.h>			//创建文件夹所用
#include <direct.h>		//创建文件夹所用
#include "start.h"		//窗口设置
#include "Buttons.h"	//自定义按钮
#include "AccountControl.h"	//账户控制系统
#include "Book.h"			//预订系统
#include "Query.h"			//查询系统
#include "Manage.h"			//管理系统
#include "DataInput.h"		//自定义输入框（暂无）
#include "Page.h"

int Page = 0;//切换页面 换按钮

void CreateFolder(std::string str);

//账户全局变量		//用户|管理员 -1|0|1//是否拥有机位//登录状态
User_Type Temp_User = { "NONE","NONE",-1,1,0}; //初始化用户名//初始化密码 //初始化权限 : 未知|用户|管理员//CanBook//登录状态//

Windows VerticalWindows = {595,990};
Windows LandscapeWindows = {990,540 + 45};//Defaut : 990 , 540 + 45 
//Windows WindowsSize = LandscapeWindows; //莫名其妙有bug

Windows WindowsSize = { 990,540 + 45 };

//字体全局变量
const int Defaut_Font_Size = (WindowsSize.y - 45) / 6 * 2 / 3 * 4 / 5;
const int Max_Input_Num = 10;

int MainStart() {

	CreateFolder("Files");	//创建空文件夹放置文件

	setinitmode(0); //设置初始化图形的选项和模式
	//initgraph(VerticalWindows.x, VerticalWindows.y, INIT_NOFORCEEXIT); //如果设置width = -1 , height = -1, 那么窗口将会全屏显示(懒得修复全屏bug)  INIT_NOFORCEEXIT , 使关闭窗口的时候不强制退出程序，但窗口会消失，需要配合is_run函数
	initgraph(WindowsSize.x, WindowsSize.y, INIT_NOFORCEEXIT); //如果设置width = -1 , height = -1, 那么窗口将会全屏显示(懒得修复全屏bug) INIT_NOFORCEEXIT , 使关闭窗口的时候不强制退出程序，但窗口会消失，需要配合is_run函数

	//setbkcolor(EGERGB(0xEA, 0x51, 0x7F)); 	//设置背景颜色 
	setbkcolor(WHITE);
	PIMAGE pimg = newimage();
	getimage(pimg, "990X585.png");
	putimage(0, 0, pimg);
	delimage(pimg);
	DrawPage(Page);

	setcaption("机房机位预定系统");		//设置窗口标题
	//setinitmode(mode, x, y) x, y 是窗口左上角出现在屏幕的坐标
	ege_enable_aa(true);//抗锯齿
	InitializeButton();	//初始化按钮（位置）

	bool RefreshPage = true;

	int PressButtonId = -1;

	for (; is_run(); delay_fps(90)) {
		/////////////////////////////每次刷新都要重新绘制
		cleardevice();
		PIMAGE pimg = newimage();
		getimage(pimg, "990X585.png");
		putimage(0, 0, pimg);
		delimage(pimg);
		DrawPage(Page);				// 每次刷新完页面按钮字体	
		Show_Online_Login_User();	// 每次刷新完页面显示当前账户	

		while (mousemsg()) {			////////////copy from Intrnet
			mouse_msg msg = getmouse();
			// 判断鼠标左键按下（左键按下确定位置，同时判断是否为按钮区域
			// 抬起则解除按下状态
			int ButtonId = -1;
			if (msg.is_left() && msg.is_down()) { //初始化
				// 检查是否有按钮被按下
				ButtonId = searchButton(msg.x, msg.y, ButtonLocation, 10);
				// 将被按下的按钮设置为按下状态
				//if (ButtonId != -1) {
				//	PressButtonId = ButtonId;
				//	ButtonLocation[PressButtonId].Pressed = true;
				//	RefreshPage = true;
				//}
				if (ButtonId != -1)	//点住123456按钮
					Initialize_Button_State(ButtonId, PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);//只是将上面注释封装了一下
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
					Recovery_Button_State(PressButtonId, ButtonLocation[PressButtonId].Pressed, RefreshPage);		//只是将上面注释封装了一下，实现左键点击后释放的时候实现某些功能
				else {						//没点住123456按钮
					//RefreshPage = false; // 不用刷新?
				}
			}
		}
		// 判断是否需要重绘，减少不必要的绘制操作
		if (RefreshPage) {
			//cleardevice();
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
		enum { Menu_Page = 0 , Book_Page, Query_Page, Manage_Page, User_Manage_Page, Computer_Room_Manage_Page, Computer_Manage_Page, Book_Manage_Page };
		enum { Book_Quarry_Page = 100, ComputerRoom_Quarry_Page = 110, Computer_Quarry_Page = 120 ,Manage_Book_Page = 130};
		case Menu_Page: {
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: {Add_User(); break; }
				case 2: {Login_User(); break; }
				case 3: {Logout_User(); break; }
				case 4:  if (Temp_User.Type == -1) { MessageBox(NULL, TEXT("您还没有登录！请登录！"), TEXT("权限管理"), MB_OK | MB_SETFOREGROUND); break; }
						{Page = Book_Page;  break; }
				case 5: if (Temp_User.Type == -1) { MessageBox(NULL, TEXT("您还没有登录！请登录！"), TEXT("权限管理"), MB_OK | MB_SETFOREGROUND); break; }//如果是普通用户，无法点开，并提醒
						{Page = Query_Page;  break;	}
				case 6: if (Temp_User.Type == -1) { MessageBox(NULL, TEXT("您还没有登录！请登录！"), TEXT("权限管理"), MB_OK | MB_SETFOREGROUND); break; }//如果是普通用户，无法点开，并提醒
						if (Temp_User.Type != 1) { MessageBox(NULL, TEXT("您不是管理员！无权做此操作！"), TEXT("权限管理"), MB_OK | MB_SETFOREGROUND); break; }//如果是普通用户，无法点开，并提醒
						{Page = Manage_Page;  break;}
			}
			break;	
		}
		case Book_Page:	{
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: { Pre_Book(); break; }
				case 2: { Cancel_Pre_Book(); break; }
				case 3: { Page = Book_Quarry_Page; Query_BooK(); Page = Book_Page; break; }
			}
			break;	
		}
		case Query_Page:	{
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: { Page = Computer_Quarry_Page; Computer_Query();Page = Query_Page; break; }
				case 2: { Page = ComputerRoom_Quarry_Page; Computer_Room_Query(); Page = Query_Page; break; }
				case 3: { Computer_Room_Browse(); break; }
			}
			break;	
		}
		case Manage_Page: {
			switch (PressButtonId) {
				case 0: {Page = Menu_Page; break; }
				case 1: {Page = User_Manage_Page; break; }
				case 2: {Page = Computer_Room_Manage_Page; break; }
				case 3: {Page = Computer_Manage_Page; break; }
				case 4: {Page = Book_Manage_Page; break; }
				case 5: {
					break;
				}
				case 6: {

					break;
				}
			}
			break;
		}
		case User_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: { Delete_User(); break; }
			case 2: { Transform_User_BookPower(); break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}
		case Computer_Room_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: { Add_Computer_Room(); break; }
			case 2: { Delete_Computer_Room(); break; }
			case 3: { Transform_Computer_Room(); break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}
		case Computer_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: { Add_Computer(); break; }
			case 2: { Delete_Computer(); break; }
			case 3: { Transform_Computer(); break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}
		case Book_Manage_Page: {
			switch (PressButtonId) {
			case 0: {Page = Manage_Page; break; }
			case 1: {Page = Manage_Book_Page; Query_BooK(); Page = Book_Manage_Page; break; }
			case 2: { Agree_ALL_Book(); break; }
			case 3: { break; }
			case 4: { break; }
			case 5: {
				break;
			}
			case 6: {

				break;
			}
			}
			break;	
		}

		 ////////////////////////////////////////////////////////////以下页面为空白页，用于查询功能的的清屏功能
		case Book_Quarry_Page: {
			switch (PressButtonId) {
			case 0: {Page = Book_Page; break; }
			}
			break;
		}
		case Computer_Quarry_Page: {
			switch (PressButtonId) {
			case 0: {Page = Query_Page; break; }
			}
			break;
		}
		case ComputerRoom_Quarry_Page: {
			switch (PressButtonId) {
			case 0: {Page = Query_Page; break; }
			}
			break;
		}
		case Manage_Book_Page: {
			switch (PressButtonId) {
			case 0: {Page = Book_Manage_Page; break; }
			}
			break;
		}
		////////////////////////////////////////////////////////////以下页面为空白页，用于查询功能的的清屏功能
	}
	ButtonLocation[PressButtonId].Pressed = false;	//恢复按钮
	PressButtonId = -1;								//初始化按钮（不用？）
	RefreshPage = true;								//使函数执行完刷新页面
	return 1;
}

void CreateFolder(std::string str){// 创建文件夹（需要 #include <io.h> 以及 #include <direct.h>）
	const char* p = str.c_str();	//string转换为char[]，不然下面函数用不了
	if (_access(p, 0) == -1) {    // 文件夹不存在则创建文件夹
		(void)_mkdir(p);
	}
}

int Exit() { return 0; }
