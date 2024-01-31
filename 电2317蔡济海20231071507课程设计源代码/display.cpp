#include"display.h"
#include"Polyfit/Polyhead.h"

//初始化管理系统界面
void _display() {
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	ExMessage m3;

	button* search = createbutton(362, 350, 300, 70, RED, "查找文件");
	button* watch = createbutton(230, 460, 600, 70, RED, "查看已经处理过的文件");
	button* ___return = createbutton(362, 570, 300, 70, RED, "返回上级");


	//以下代码是存放已处理后的文件的信息
	POLYFITINFO watchinfo[10];//已经处理后文件的所有信息

	FILE* result = NULL;//存放处理结果的文件
	fopen_s(&result, "result.txt", "rb");//打开处理结果文件
	int j = 0;

	while (!feof(result)) {
		fread(&watchinfo[j], sizeof(POLYFITINFO), 1, result);
		j++;
	}//从文件中读入已处理的文件的信息并放入pinfo这个结构体数组中
	fclose(result);

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		setbutton(search, 50);
		setbutton(watch, 50);
		setbutton(___return, 50);
		writetitle("信息管理子系统", 230);
		
		if (j == 1) {
			settextstyle(40, 0, "楷体");
			outtextxy(220, 680, "您还没有成功处理过任何数据文件");
		}
		//获取鼠标信息
		getmessage(&m3);
		//判断鼠标的信息
		if (clickButton(search, m3)) {
			system("cls");
			char tempname[20];//定义一个数组，来输入文件名
			settextstyle(40, 0, "楷体");
			outtextxy(220,300 , "请在控制台输入想要查找的文件名");
			EndBatchDraw();
			printf("请输入您想要查找的文件名（带扩展名):");
			scanf_s("%s", tempname, 20);
			f_search(tempname);
		}
		if (clickButton(watch, m3)) {
			if (j != 1) 
				f_watch(watchinfo,j-1);//j-1才是所处理的真实数据值
		}
		if (clickButton(___return, m3))
			break;

		EndBatchDraw();
	}
}


void f_watch(POLYFITINFO *info,int j) {
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);
	ExMessage m4; int i;
	POLYFITINFO temp;//作为排序时候的中间变量
	int min;//本程序采用的是选择排序，所以定义最小值的下标

	button* sort = createbutton(362, 300, 300, 70, RED, "默认排序");
	button* opti_sort = createbutton(230, 390, 600, 70, RED, "按最佳拟合的大小排序");
	button* mean_sort = createbutton(230, 480, 600, 70, RED, "按最佳的误差均值排序");
	button* variance_sort = createbutton(230, 570, 600, 70, RED, "按最佳的误差方差排序");
	button* ____return = createbutton(362, 660, 300, 70, RED, "返回上级");

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		setbutton(sort, 50);
		setbutton(opti_sort, 50);
		setbutton(mean_sort, 50);
		setbutton(variance_sort, 50);
		setbutton(____return, 50);
		writetitle("选择排序的方式", 230);

		settextstyle(40, 0, "楷体");
		outtextxy(220, 200, "选择后请在控制台上查看输出结果");
		
		
		//获取鼠标信息
		getmessage(&m4);
		//判断鼠标的信息
		if (clickButton(sort, m4)) {
			system("cls");
			printf("文件名\t数据数\t最佳拟合次数\t最佳误差均值\t最佳误差方差\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(opti_sort, m4)) {
			system("cls");

			for (i = 0; i < j; i++) {
				min = i;
				for (int k = i + 1; k < j; k++) {
					if (info[k].OptiOrder < info[min].OptiOrder)
						min = k;
				}
				temp = info[min]; info[min] = info[i]; info[i] = temp;
			}

			printf("文件名\t数据数\t最佳拟合次数\t最佳误差均值\t最佳误差方差\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(mean_sort, m4)) {
			system("cls");

			for (i = 0; i < j; i++) {
				min = i;
				for (int k = i + 1; k < j; k++) {
					if (info[k].OptiOrder_fitError_mean < info[min].OptiOrder_fitError_mean)
						min = k;
				}
				temp = info[min]; info[min] = info[i]; info[i] = temp;
			}

			printf("文件名\t数据数\t最佳拟合次数\t最佳误差均值\t最佳误差方差\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(variance_sort, m4)) {
			system("cls");

			for (i = 0; i < j; i++) {
				min = i;
				for (int k = i + 1; k < j; k++) {
					if (info[k].OptiOrder_fitError_variance < info[min].OptiOrder_fitError_variance)
						min = k;
				}
				temp = info[min]; info[min] = info[i]; info[i] = temp;
			}

			printf("文件名\t数据数\t最佳拟合次数\t最佳误差均值\t最佳误差方差\n");
			for (i = 0; i < j; i++) {
				printf("%s\t%d\t%d\t\t%.3lf\t\t%.3lf\n", info[i].filename, info[i].row, info[i].OptiOrder, info[i].OptiOrder_fitError_mean, info[i].OptiOrder_fitError_variance);
			}
		}
		if (clickButton(____return, m4))
			break;

		EndBatchDraw();
	}



}

void f_search(char* filename) {

	FILE* fp = NULL;
	errno_t err=fopen_s(&fp, filename, "r");

	if (err) {
		printf("文件不存在\n");
		return;
	}//从文件中读入已处理的文件的信息并放入pinfo这个结构体数组中

	printf("您所查找的文件存在，若您没有对其进行数据处理可以尝试进行处理\n");
	fclose(fp);

}