#include "Query.h"
#include "start.h"
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

int Query() {
	return 1;
}
int Computer_Query() {		//查询机位
	FILE* FP_Computers = NULL;
	FP_Computers = fopen("Files\\Computers.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_Computers);
	system("Files\\BookLog.txt");
	return 1;
}
int Computer_Room_Query() {	//查询机房
	FILE* FP_ComputerRoom = NULL;
	FP_ComputerRoom = fopen("Files\\ComputerRooms.txt", "a"); //如果文件不存在，则会创建一个新文件
	fclose(FP_ComputerRoom);
	system("Files\\ComputerRooms.txt");
	return 1;
}
int Computer_Room_Browse() {	//浏览机房 
	return 1;
}