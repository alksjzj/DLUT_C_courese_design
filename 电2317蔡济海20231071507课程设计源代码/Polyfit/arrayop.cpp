#include "Polyhead.h"

void arraycopy(double target[],double source[],int n) //数组拷贝
{
 int i;
 for(i=0;i<n;i++)
	 target[i]=source[i];
}

void arraysub(double x[],double y[],double z[],int n)// z=x-y;
{
 int i;
 for(i=0;i<n;i++)
	 z[i]=x[i]-y[i];
} 

double arraymax(double a[], int n) //数组最大值
{
  double max;
  int i;
  max=a[0];
  for(i=1;i<n;i++)
  {
	if(max<a[i]) max=a[i];
  }
   return max;
}

double arraymin(double a[], int n) //数组最小值
{
  double min;
  int i;
  min=a[0];
  for(i=1;i<n;i++)
  {
	if(min>a[i]) min=a[i];
  }
   return min;
}

double arrayscale(double a[], int n) // 数组的数值范围
{
  return arraymax(a,n)-arraymin(a,n);
}

double mean(double a[], int n)//取平均数
{
	double sum = 0;
	int i;
	for (i = 0; i < n; i++)
		sum = sum + a[i];
	return sum / n;
}

double variance(double a[], int n)//求方差的函数
{
	double M, sum = 0;
	int i;
	M = mean(a, n);//先取平均值
	for (i = 0; i < n; i++)
		sum = sum + (a[i] - M) * (a[i] - M);
	return sum / n;
}
