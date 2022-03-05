#pragma once
#include <graphics.h>
#include <ege/sys_edit.h>
//三级目录文件

//https://docs.microsoft.com/zh-cn/cpp/error-messages/tool-errors/linker-tools-warning-lnk4002?view=msvc-170
//https://docs.microsoft.com/zh-cn/visualstudio/msbuild/errors/msb8027?view=vs-2022
int My_InputBox_Line();
char* My_InputBox_One_Line(ege::sys_edit* editBox);