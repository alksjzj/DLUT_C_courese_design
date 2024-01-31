#ifndef __Polyhead_H
#define __Polyhead_H


#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <string.h>

typedef struct
{
  char filename[20];//数据的名字
  int row;//数据的行数，也是变量x的数量
  double polyCoeff[10][10];//多项式的系数
  double fitError[10];//不同拟合情况下的相对误差
  int OptiOrder;//最佳拟合次数
  double OptiOrder_fitError_mean;//最佳拟合次数下误差的绝对值
  double OptiOrder_fitError_variance;//最佳拟合次数下误差的方差
  char status;//状态
}POLYFITINFO;   // 这个结构体的成员可以根据设计需求进行修改和增加。


typedef struct 
{ 
	int x0,y0,x1,y1;  
}PLOTAREA;


extern int COLOR[16];

// 函数声明

// 数组基本操作 文件：arrayop.cpp
double arrayscale(double a[], int n);
double arraymin(double a[], int n);
double arraymax(double a[], int n);
void arraycopy(double target[],double source[],int n);
void arraysub(double x[],double y[],double z[],int n);// z=x-y;

// 多项式拟合函数
void polyfit(int n,double x[],double y[],int poly_n,double p[]);
void gauss_solve(int n,double A[],double x[],double b[]);
void reverseP(double arr[],int size);

// 多项式函数处理
double fx(double x, double coeffs[], int degree);


// 图形显示  文件： datagraph.cpp
void showhisto(double result[],int n, PLOTAREA area);
void showpinfo(POLYFITINFO pinfo,PLOTAREA farea);
void showdata(double dataX[],double dataY[],int n, long color, PLOTAREA p);

double mean(double a[], int n);//取平均数
double variance(double a[], int n);//求方差的函数
#endif