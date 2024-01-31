#include"revise.h"
FILE* revisep;


void revisedata()//数据文件处理函数
{
	IMAGE background;
	loadimage(&background, "background.jpg", 1024, 768);

	//定义鼠标变量和按钮变量
	ExMessage m2;
	button* createfile = createbutton(210, 350, 300, 70, RED, "新增文件");
	button* createdata = createbutton(540, 350, 300, 70, RED, "新增数据");
	button* modifydata = createbutton(362, 460, 300, 70, RED, "修改数据");
	button* _return2 = createbutton(362, 570, 300, 70, RED, "返回菜单");

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &background);
		getmessage(&m2);
		writetitle("请选择要处理的选项", 150);

		setbutton(createfile, 50);
		setbutton(createdata, 50);
		setbutton(modifydata, 50);
		setbutton(_return2, 50);
		outtextxy(170, 670, "选择后请在控制台依据提示操作");
		//选择判断的逻辑
		if (clickButton(createfile, m2))
			create();
		if (clickButton(createdata, m2))
			created();
		if (clickButton(modifydata, m2))
			modify();
		if (clickButton(_return2, m2))
			break;
		EndBatchDraw();
	}
}

void create() {
	system("cls");
	FILE* fileP=NULL;
	char fileName[30];     

	printf("请输入所要创建文件的名字（带扩展名）：");
	scanf_s("%s", fileName, 30);
	//使用“读入”方式打开文件
	errno_t err = fopen_s(&fileP, fileName, "r");
	if (err) {
		//如果无法打开，则采用“写入”的方式打开文件
		fopen_s(&fileP, fileName, "w");
		printf("文件已创建成功");
	}
	else
		printf("文件已存在");
	fclose(fileP);
}

void created() {
	system("cls");
	FILE* fileP;
	char fileName[30];
	printf("请输入所要追加数据的文件的名字（带扩展名）:");
	scanf_s("%s", fileName, 20);
	//使用“读入”方式打开文件
	errno_t err = fopen_s(&fileP, fileName, "r");

	while (err) {
		//如果无法打开，则重新输入文件的名字
		printf("文件打开失败，请重新输入:");
		scanf_s("%s", fileName, 20);
		err = fopen_s(&fileP, fileName, "r");
	}

	//接下来先对文件中所有的数据进行读入
	int i,datacount;//这里i为计数
	double datax[N], datay[N];

	for (i = 0; i < N; i++)
	{
		fscanf(fileP, "%lf %lf", &datax[i], &datay[i]);
		if (feof(fileP) != 0) // 如果已经读到文件末尾，停止读文件。
			break;
	}//此时i的值就是data的数量
	fclose(fileP);//关闭文件
	
	datacount = i + 1;//追加后的数据个数为datacount，控制下面输出的循环

	printf("文件打开成功，请输入追加的数据，并按空格分隔自变量和因变量:\n");
	scanf_s("%lf %lf", &datax[i], &datay[i]);

	fopen_s(&fileP, fileName, "w");
	
	for (i = 0; i < datacount; i++)
	{
		fprintf(fileP,"%lf %lf\n", datax[i], datay[i]);
	}

	printf("数据追加成功,请返回窗口");
	fclose(fileP);
}



void modify() {
	system("cls");
	FILE* fileP;
	char fileName[30];
	printf("请输入所要更改数据的文件的名字（带后缀）:");
	scanf_s("%s", fileName, 20);
	//使用“读入”方式打开文件
	errno_t err = fopen_s(&fileP, fileName, "r");

	while (err) {
		//如果无法打开，则重新输入文件的名字
		printf("文件打开失败，请重新输入:");
		scanf_s("%s", fileName, 20);
		err = fopen_s(&fileP, fileName, "r");
	}

	//接下来先对文件中所有的数据进行读入
	int i,datacount;
	double datax[N], datay[N],modify_x, modify_y;//modify_x和modify_y是通过定位要修改的x和y来决定

	for (i = 0; i < N; i++)
	{
		fscanf(fileP, "%lf %lf", &datax[i], &datay[i]);
		if (feof(fileP) != 0) // 如果已经读到文件末尾，停止读文件。
			break;
	}//此时i的值就是data的数量

	datacount = i;
	fclose(fileP);


	printf("文件打开成功，请输入要更改的数据，并按空格分隔自变量和因变量:\n");
	scanf_s("%lf %lf", &modify_x, &modify_y);
	for (i = 0; i < datacount; i++)
		if (datax[i]==modify_x&&datay[i]==modify_y)
			break;
	if (i == datacount)
	{
		printf("没有这一组数据，请重新在窗口选择操作");
		return;
	}

	fopen_s(&fileP, fileName, "w");

	printf("已找到需要更改的数据，请输入替换的数据，并按空格分隔自变量和因变量:\n");
	scanf_s("%lf %lf", &modify_x, &modify_y);
	datax[i] = modify_x; datay[i] = modify_y;//输入后重新赋值

	for (i = 0; i < datacount; i++)
	{
		fprintf(fileP, "%lf %lf\n", datax[i], datay[i]);//重新写入
	}

	printf("数据更改成功,请返回窗口");
	fclose(fileP);
}



