#include"Button.h"
#include"user.h"
#include"Polyfit/Polyhead.h"
#include"gui.h"
#include"revise.h"
#include"display.h"
int main() {
	//背景与鼠标信息的初始化
	initgraph(1024, 768);
	ExMessage msg;
	IMAGE background;
	loadimage(&background,"background.jpg",1024,768);
	//主界面三个按钮的初始化
	button *signup=createbutton(387, 350, 250, 90, RED, "注册");
	button *login= createbutton(387, 460, 250, 90, RED, "登入");
	button *_exit = createbutton(387, 570, 250, 90, RED, "退出");
	//登陆后主界面的按钮初始化
	button* deal = createbutton(210, 350, 300, 70, RED, "处理文件");
	button* revise = createbutton(540, 350, 300, 70, RED, "修改文件");
	button* display = createbutton(230, 460, 600, 70, RED, "文件分类统计信息显示");
	button* _return = createbutton(362 ,570 , 300, 70, RED, "退出登录");

	//能否登录的判断标志
	int i = 0;

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		setbutton(signup,70);
		setbutton(login,70);
		setbutton(_exit,70);
		writetitle("数据处理与信息管理系统", 45);
		//获取鼠标信息
		getmessage(&msg);
		//判断鼠标的信息
		if (clickButton(signup, msg))
			registers();
		if (clickButton(login, msg))
			i=Input_login();//判断是否登陆成功
		if (clickButton(_exit, msg)) 
			exit(0);
		
		//如果登录成功，则进入内循环
		while (i) {
			getmessage(&msg);
			
			BeginBatchDraw();
			putimage(0, 0, &background);
			writetitle("数据处理与信息管理系统", 45);
			//初始化四个按钮，并获取鼠标信息
			setbutton(deal,50);
			setbutton(revise,50);
			setbutton(display,50);
			setbutton(_return,50);
			getmessage(&msg);

			if (clickButton(deal, msg))
				_deal();
			if (clickButton(revise, msg))
				revisedata();
			if (clickButton(display, msg))
				_display();
			if (clickButton(_return, msg)) {
				i = 0;
				break;
			}
			EndBatchDraw();
		}
		EndBatchDraw();
	}
	closegraph();

	return 0;
}