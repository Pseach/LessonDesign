#pragma once
//三级目录文件
struct RectButton {// 矩形按钮
	int x, y;
	int width, height;
};

extern RectButton Now_User_Button;
extern RectButton Add_User_Button;
extern RectButton Login_Button;
extern RectButton Change_Login_User_Button;
extern RectButton Exit_Button; //https://zhidao.baidu.com/question/26386872.html 多文件访问结构体


// 判断点(x, y) 是否在按钮点击区域内
bool insideRectButton(const RectButton* button, int x, int y);
// 绘制按钮
void drawRectButton(const RectButton* button);

void draw();