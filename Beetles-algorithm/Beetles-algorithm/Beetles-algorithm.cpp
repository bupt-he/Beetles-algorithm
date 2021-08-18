// Beetles-algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Beetles.h"
#include "MyGraph.h"
#include<cmath>
#include<ctime>
using namespace std;

//天牛须种群数组
SingleBeetle X[N] = {};
//任务数组
double task[100];
//机器数组
double machine[100];
MyGraph graph;
int taskNum;
int machineNum;
SingleBeetle pg = {};

//*@ array  要处理的数组
//*@ d        要处理的数组的列数
//*@ note   生成1*d的随机单位向量(原向量范围是0-machineNum-1)
void rands(double *array,int d)
{
	double sum = 0;
	for (int i = 0; i < d; i++)
	{
		array[i] = randomInt(0,machineNum-1);
		sum += array[i] * array[i];
	}
	if (sum<=0)
	{
		printf("error ！主函数35行的随机单位向量为0\n");
	}
	for (int i = 0; i < d; i++)
	{
		array[i] = array[i] / sqrt(sum);
	}
}

//*@ param left     左式
//*@ param right  右式
//*@ note              符号函数
int sign(double left, double right)
{
	if (left < right)
		return -1;
	else if (left == right)
		return 0;
	else
		return 1;
}

//*@ param X     一只天牛
//*@ param d     天牛中的变量个数
//*@ note           计算天牛X的适应度
double basFiness(SingleBeetle& X,int d)
{
	double nodes[100] = {};

		int times[100] = {};
		for (int i = 0; i < 100; i++)
			times[i] = 1;
		for (int j = 0; j < d; j++)
		{
			times[X.choice[j]]++;
		}
		for (int i = 0; i < d; i++)
		{
			int index;
			double t, m;
			try
			{
				index = X.choice[i];
				t = task[i], m = machine[index];
				if (fabs(m-0)<=0.0001)
				{
					throw 0;
				}
			}
			catch (...)
			{
				cerr << "Beetles-alorithm.cpp 85行出现异常 machine=0" << endl;
			}
			nodes[i] = t / m * times[X.choice[i]];
		}
		criticalPath(graph,nodes,d);
		X.Fitness = graph.InstNum;
		return X.Fitness;
}

int main()
{
	taskNum = 50;
	machineNum = 40;
	D = taskNum;
	double p[N] = {};

	for (int i = 0; i < taskNum; i++)
	{
		task[i] = tryTT[i] / 20000 / 4;
	}

	task[0] = task[taskNum - 1] = 0;

	for (int i = 0; i < machineNum; i++)
	{
		int index = randomInt(0,19);
		machine[i] = machineLow[index];
	}

	graphInit(graph,taskNum);
	graphRandom(graph);

	srand(time(nullptr));
	
	//初始化位置信息
	for (int i = 0; i < N; i++)
		for (int j = 0; j < D; j++) {
			X[i].choice[j] = randomInt(0, machineNum - 1);
			if (X[i].choice[j]==machineNum)
			{
				X[i].choice[j] = machineNum-1;
			}
		}
	
	//先计算各个天牛个体的适应度
	for (int  i = 0; i < N; i++)
		p[i]=basFiness(X[i], D);

	

	//找出最佳天牛
	pg = X[N - 1];
	for (int i = 0; i < N; i++)
	{
		if (X[i].Fitness < pg.Fitness)
			pg = X[i];
	}

	double pBest[M] = {};

	//主循环
	for (int t = 0; t < 500; t++)
	{
		double fleft[N] = {}, fright[N] = {};
		double f[N] = {};
		for (int i = 0; i < N; i++)
		{
			int d0 = step / c;
			double dir[D_MAX] = {};
			rands(dir,D);
			SingleBeetle xleft = {};
			SingleBeetle xright = {};
			
			for (int j = 0; j < D; j++)
			{
				xleft.choice[j] = X[i].choice[j] + dir[j] * d0 / 2;
				xright.choice[j] = X[i].choice[j] - dir[j] * d0 / 2;
				if (xleft.choice[j]<0)     xleft.choice[j] = 0;
				if (xleft.choice[j] >= machineNum)  xleft.choice[j] = machineNum - 1;
				if (xright.choice[j] < 0)    xright.choice[j] = 0;
				if (xright.choice[j] >= machineNum) xright.choice[j] = machineNum - 1;
			}

			fleft[i] = basFiness(xleft,D);
			fright[i] = basFiness(xright,D);
			for (int j = 0; j < D; j++) {
				X[i].choice[j] = X[i].choice[j] - step * dir[j] * sign(fleft[i],fright[i]);
				if (X[i].choice[j] < 0)
					X[i].choice[j] = 0;
				if (X[i].choice[j]>=machineNum)
				{
					X[i].choice[j] = machineNum - 1;
				}
			}

			f[i] = basFiness(X[i],D);
			SingleBeetle tmp = {};
			if (f[i] < p[i])
			{
				p[i] = f[i];
				tmp = X[i];
			}
			if (p[i] < basFiness(pg, D))
				pg = tmp;
		}

		step = step * eta;
		pBest[t] = basFiness(pg, D);
		printf("%lf\n",pBest[t]);
	}
}
