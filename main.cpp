//一级目录文件
#include "start.h"

Windows VerticalWindows = {
    540,720,
};

Windows LandscapeWindows = {//x + 180
    990,540 + 45,
};


int main(){
    MainStart();
    return 0;
}
