#include "gui.h"


extern int COLOR[16];

void _deal() {//处理文件图形化界面的函数
	system("cls");
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);

	ExMessage m1;
	button* _001 = createbutton(600, 300, 260, 70, RED, "001.txt");
	button* _002 = createbutton(600, 400, 260, 70, RED, "002.txt");
	button* _003 = createbutton(600, 500, 260, 70, RED, "003.txt");
	button* _004 = createbutton(600, 600, 260, 70, RED, "004.txt");
	button* other = createbutton(50, 400, 300, 70, RED, "其他文件");
	button* _return1 = createbutton(50, 600, 300, 70, RED, "返回上级");


	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		getmessage(&m1);
		writetitle("请选择要处理的文件", 150);

		setbutton(_001, 50);	
		setbutton(_002, 50);
		setbutton(_003, 50);
		setbutton(_004, 50);
		setbutton(other, 50);
		setbutton(_return1, 50);

		//选择判断的逻辑
		if (clickButton(_001, m1))
			drawing((char*)"001.txt");
		if (clickButton(_002, m1))
			drawing((char*)"002.txt");
		if (clickButton(_003, m1))
			drawing((char*)"003.txt");
		if (clickButton(_004, m1))
			drawing((char*)"004.txt");
		if (clickButton(other, m1)) {
			char tempname[20];//定义一个数组，来输入文件名
			outtextxy(50,490 , "请在控制台输入文件名");
			EndBatchDraw();
			printf("请输入您想要处理的文件名（带扩展):");
			scanf_s("%s", tempname, 20);
			drawing(tempname);
		}
		if (clickButton(_return1, m1))
			break;
		EndBatchDraw();
	}
}


//数据处理函数
void drawing(char *filename) {

	EndBatchDraw();
	BeginBatchDraw();
	initgraph(1024, 768, EX_SHOWCONSOLE);
	FILE* fp = NULL;//定义要处理文件的指针

	//以下代码是存放已处理后的文件的信息
	POLYFITINFO pinfo[10];//已经处理后文件的所有信息

	FILE* result=NULL;//存放处理结果的文件
	fopen_s(&result, "result.txt", "rb");//打开处理结果文件
	int j = 0,pause=-1;//定位要处理的文件是在该结构体数组中的第几个元素,j用来计数


	while (!feof(result)) {
		fread(&pinfo[j],sizeof(POLYFITINFO),1,result);
		if (strcmp(filename, pinfo[j].filename) == 0)
			pause=j;//如果发现文件是重新再处理的，那就保留j的值
		j++;
	}//从文件中读入已处理的文件的信息并放入pinfo这个结构体数组中
	
	if (pause == -1)
		pause = j-1;//如果确实不是重新再处理的，那就新建一个“j”
	fclose(result);

	//以下代码是将一个数据文件的所有信息读入到数组中
	int i, datacount = 0;//分别是数据的大小和计数
	double datax[N], datay[N], fity[N],_fityerror[N];//从左到右分别是x的数据，y的数据、拟合后的y的数据和拟合后的误差数据
	double fiterror;		// 某一个阶数下的拟合误差
	int order; // 多项式的阶次

	PLOTAREA  parea = { 200,400,824,700 }; // 直方图显示区域，
	PLOTAREA  farea = { 10,600,80,700 };   // 文字显示区域 
	PLOTAREA dataarea = { 50,10,950,300 }; // 数据曲线显示区域
	
	errno_t err = fopen_s(&fp, filename, "r+");	

	if (err) {
		printf("您输入的文件不存在");
		return;
	}

	for (i = 0; i < N; i++)
	{
		fscanf(fp, "%lf %lf", &datax[i], &datay[i]);
		if (feof(fp) != 0) // 如果已经读到文件末尾，停止读文件。
			break;
	}

	datacount = i; // 数据的行数。
	fclose(fp);

	//将文件名和行数存储起来
	strcpy(pinfo[pause].filename, filename);
	pinfo[pause].row = datacount;

	settextcolor(WHITE);
	settextstyle(30, 0, "楷体");
	outtextxy(300, 10, "请在控制台选择要处理的操作");

	// 利用最小二乘确定多项式拟合的系数
	for (order = 1; order <= 9; order++)
	{
		polyfit(datacount, datax, datay, order, pinfo[pause].polyCoeff[order]);
	}
	EndBatchDraw();
	
	// 计算并记录拟合误差。
	for (order = 1; order <= 9; order++)
	{
		fiterror = 0;
		for (i = 0; i < datacount; i++)
		{
			fity[i] = fx(datax[i], pinfo[pause].polyCoeff[order], order);
			fiterror += (fity[i] - datay[i]) * (fity[i] - datay[i]);
		}
		pinfo[pause].fitError[order] = fiterror;
	}

	pinfo[pause].OptiOrder = 0;//先将最佳拟合次数置于0，作为之后是否进行处理的标准

	//选择程序
	system("cls");
	int option=0;
	printf("***************图形化数据处理程序***************\n");
	printf("*****您正在处理%s文件\n", filename);
	printf("*****您要输入最佳多项式的拟合阶数才可以输出结果\n");
	printf("*****1、显示原始数据\n");
	printf("*****2、显示某一阶拟合数据的图像（小于等于9）\n");
	printf("*****3、显示所有拟合的数据的图像\n");
	printf("*****4、显示误差数据直方图\n");
	printf("*****5、输入最佳多项式的拟合阶数\n");
	printf("*****6、清除窗口上所有的图像\n");
	printf("*****7、输出处理结果\n");
	printf("*****请输入选项1-7:");
	scanf_s("%d", &option);

	while (option != 7) {
		while (!(option <= 8 && option >= 1)) {
			printf("*****输入选项有误，请重新输入:");
			scanf_s("%d", &option);
		}
		//如果选项为8但没有进行过处理，则要重新输入
		while (option == 8 && pinfo[pause].OptiOrder == 0) {
			printf("*****输入选项有误，请重新输入:");
			scanf_s("%d", &option);
		}

		switch (option) {
		case 1:showdata(datax, datay, datacount, RED, dataarea); break;//绘制原始的图像		
		//显示指定拟合数据的图像
		case 2:
			printf("请输入想要查看的拟合阶数(1-9):");
			scanf_s("%d", &order);
			for (i = 0; i < datacount; i++)
			{
				fity[i] = fx(datax[i], pinfo[pause].polyCoeff[order], order);
			}
			showdata(datax, fity, datacount, COLOR[order], dataarea);
			break;
		//显示所有拟合数据的图像
		case 3:
			for (order = 1; order <= 9; order++)
			{
				for (i = 0; i < datacount; i++)
				{
					fity[i] = fx(datax[i], pinfo[pause].polyCoeff[order], order);
				}
				showdata(datax, fity, datacount, COLOR[order], dataarea);
			}
			break;

		case 4:
			showhisto(pinfo[pause].fitError, 9, parea); break; // 在parea 显示直方图
		case 5:
			// 输入最佳的多项式拟合阶次。
			printf("请输入最佳的多项式拟合阶次：（1-9）");
			rewind(stdin);
			scanf_s("%d", &pinfo[pause].OptiOrder);

			//计算在该拟合阶次下，误差的均值和方差
			for (i = 0; i < datacount; i++) {
				fity[i] = fx(datax[i], pinfo[pause].polyCoeff[pinfo[pause].OptiOrder], pinfo[pause].OptiOrder);
				_fityerror[i] = fity[i] - datay[i];
			}

			pinfo[pause].OptiOrder_fitError_mean = mean(_fityerror, datacount);
			pinfo[pause].OptiOrder_fitError_variance = variance(_fityerror, datacount);

			printf("最佳拟合阶次的误差已统计完毕，可以输入选项8查看误差图像\n查看图像前建议先清除窗口图像\n");
			break;
		case 6:
			initgraph(1024, 768, EX_SHOWCONSOLE);
			settextcolor(WHITE);
			settextstyle(30, 0, "楷体");
			outtextxy(300, 10, "请在控制台选择要处理的操作");
			break;
		//输出最佳拟合次数下误差的图像
		case 8:
			showdata(datax, _fityerror, datacount, WHITE, dataarea);
			break;
		}

		printf("请选择下一项任务执行:");
		scanf_s("%d", &option);
	}

	//判断是否有进行过处理
	if (pinfo[pause].OptiOrder != 0) {
		showpinfo(pinfo[pause], farea);
		pinfo[pause].status = 'Y';

		fopen_s(&result, "result.txt", "wb");//打开处理结果文件
		if(pause==j-1)//说明是新建的
			fwrite(&pinfo, sizeof(POLYFITINFO), j, result);
		else
			fwrite(&pinfo, sizeof(POLYFITINFO), j-1, result);
		fclose(result);
	}

	else{
		printf("本次未成功进行数据处理，可以重新进行");
		pinfo[pause].status = 'N';
	}
	printf("\n使用回车来返回");
	rewind(stdin);
	getchar();					// 返回窗口
}
