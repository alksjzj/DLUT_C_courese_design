#include "Polyhead.h"

int COLOR[] = { BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE };

void showdata(double dataX[],double dataY[],int n, long color, PLOTAREA p)
{
  	int i;
	int x0,y1,height,width;
	double minX,scaleX, minY, scaleY;

	//  find the min and scale of the input array
	minX=arraymin(dataX,n);
	scaleX=arrayscale(dataX,n);

	minY=arraymin(dataY,n);
	scaleY=arrayscale(dataY,n);
	  
	// Set the plot area;
	x0=p.x0; 
	y1=p.y1;
	height=p.y1-p.y0;
	width=p.x1-p.x0;

	// Plot the graph
	setlinecolor(color);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	for(i=0;i<n-1;i++)
	{
		line(x0+(dataX[i]-minX)/scaleX*width,y1-(dataY[i]-minY)/scaleY*height, x0+(dataX[i+1]-minX)/scaleX*width, y1-(dataY[i+1]-minY)/scaleY*height);
	}
}

void showhisto(double result[],int n, PLOTAREA area)
{
	int i;
	double max;
	float xscale,yscale;
	
	max=result[1];//误差最大值肯定是第一个 
	for(i=1;i<n;i++)
		if(max<result[i]) max=result[i];
	xscale=(area.x1-area.x0)/(float)n;
	yscale=(area.y1-area.y0)/(float)max;
	for(i=1;i<=n;i++)
	{ 
		char s[30];
		sprintf_s(s,30,"%.2lf",result[i]);
		setfillcolor(COLOR[i+1]);
		solidrectangle(area.x0+i*xscale,area.y1,area.x0+(i+1)*xscale,area.y1-result[i]*yscale);
		//以下是在直方图上显示误差数据的代码
		settextstyle(20, 0, "楷体");
		outtextxy(area.x0+i*xscale+5, area.y1 - result[i] * yscale-30, s);
	}
}


void showpinfo(POLYFITINFO pinfo,PLOTAREA farea)
{
// need to set the project properties to MBCS	
settextstyle(20, 0, "楷体");
 char s[50];
 sprintf_s(s,50,"文件名为:%s",strupr(pinfo.filename));
 outtextxy(farea.x0,farea.y0,s);
 sprintf_s(s,50,"数据的个数为:%d",pinfo.row);
 outtextxy(farea.x0,farea.y0+20,s);
 sprintf_s(s,50,"最佳的拟合次数为:%d",pinfo.OptiOrder);
 outtextxy(farea.x0,farea.y0+40,s);
 sprintf_s(s,50,"最佳的拟合的相对误差为:%.4lf",pinfo.fitError[pinfo.OptiOrder]);
 outtextxy(farea.x0,farea.y0+60,s);
 sprintf_s(s, 50, "最佳的拟合误差平均值为:%.4lf", pinfo.OptiOrder_fitError_mean);
 outtextxy(farea.x0, farea.y0 + 80, s);
 sprintf_s(s, 50, "最佳的拟合误差的方差为:%.4lf", pinfo.OptiOrder_fitError_variance);
 outtextxy(farea.x0, farea.y0 + 100, s);
}
