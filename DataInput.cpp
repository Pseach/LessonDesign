#include "DataInput.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <ege/sys_edit.h>
int IsLegalInput(char* s) {

	char str[11];
	strcpy(str, s);
	if (str == NULL) {
		return 0;
	}
	int i = 0;
	while (str[i] != '\0') {
		if (str[i++] == ' ')return 0;
	}
	return 1;
}
int My_InputBox_Line(){

	return 1;
}

char *My_InputBox_One_Line(sys_edit* editBox) {
	setcolor(BLACK);
	int fontHeight = 48;
	setfont(fontHeight, 0, "楷体");
	setbkmode(TRANSPARENT);

	editBox->create(false);						//单行

	editBox->move(WindowsSize.x/4, WindowsSize.y/4);						//设置位置

	int editTextHeight = Defaut_Font_Size;

	//设置尺寸，高度一般要比字的高多一点，因为输入框的边框也占一定大小。
	editBox->size(editTextHeight * 10, editTextHeight + 8);

	editBox->setbgcolor(WHITE);					//设置背景颜色
	editBox->setcolor(BLACK);					//设置文字颜色
	editBox->setfont(editTextHeight, 0, "楷体");	//设置输入框字体
	editBox->setmaxlen(8);						//设置输入最大长度
	editBox->visible(true);						//使可见
	editBox->setfocus();							//获取焦点		

	//创建输入缓存区
	const int buffSize = 11;
	char strBuffer[11] = "";

	bool CanReturn = false;
	for (; is_run(); delay_fps(60)) {
		bool error = false;				//标记是否输入错误
		bool IsGetText = false;
		//检测到回车键抬起就标记输出
		while (kbmsg()) {
			key_msg msg = getkey();
			if ((msg.key == key_enter) && (msg.msg == key_msg_up)) {
				IsGetText = true;
			}
		}
		if (IsGetText) {
			//获取输入框内容字符串
			editBox->gettext(buffSize, strBuffer);
			//if ()CanReturn = 1;
			//else error = 1;
		}
		//cleardevice();		//清屏
		setcolor(BLACK);
		//outtextxy(10, 20, "输入数字:");
		if (CanReturn) {
			if (IsLegalInput(strBuffer)) {	//有输入但是输入错误
				//输出错误提示
				setcolor(RED);
				outtextxy(100, 60, "输入错误，请重新输入");
			}
			else {		//有输入并且输入正确
			//				xyprintf(100, 60, "%f", result);
				return strBuffer;
			}
		}

	}
	return 0;
}
