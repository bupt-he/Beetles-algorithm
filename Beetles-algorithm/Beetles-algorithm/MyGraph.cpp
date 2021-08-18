#include"MyGraph.h"
using namespace std;
#include<string.h>
#include<vector>
#include<cstdio>
#include<time.h>
#include<algorithm>
#include<queue>
#include<stack>

#include<cmath>
#include<string>
#pragma warning(disable : 4996)

//extern Individual nodeMachine[GROUP_SCALE + 1];

int randomInt(int low, int high)
{
	int range = (high - low) + 1;
	//	srand((unsigned)time(nullptr));
		//!!!!!千万不要一直初始化随机数种子！！！！！！！！
	int x = rand() % range;
	return low + x;
}


void graphInit(MyGraph& graph, int num)
{
	graph.nodeNum = num;
	memset(graph.nodes, 0, sizeof(Node)*NODE_MAX);
	for (int i = 0; i < num; i++)
	{
		Node node = { i,nullptr };
		graph.nodes[i] = node;
	}
}

void graphRandom(MyGraph& graph)
{
	vector<int> v1, v2;
	int current, neighbor;
	for (int i = 1; i < graph.nodeNum - 1; i++)
	{
		v2.push_back(i);
	}
	int j = randomInt(0, (int)v2.size() - 1);
	current = v2[j];
	vector<int>::iterator pointer1 = remove(v2.begin(), v2.end(), current);
	v2.erase(pointer1, v2.end());
	v1.push_back(current);
	//从v2删除随机点current放入v1

	int edge[NODE_MAX][NODE_MAX] = {};

	//此处是为了保证生成有向连通图，因此需要先生成一条通路
	while (!v2.empty())
	{

		neighbor = randomInt(1, graph.nodeNum - 2);

		pointer1 = find(v1.begin(), v1.end(), neighbor);
		if (pointer1 == v1.end())
		{
			edge[current][neighbor] = 1;
			edge[neighbor][current] = 1;
			vector<int>::iterator pointer2 = remove(v2.begin(), v2.end(), neighbor);
			v2.erase(pointer2, v2.end());
			v1.push_back(neighbor);
			current = neighbor;
		}
	}

	//displayGraph(edge,graph.nodeNum,1);

	//给图添加随机边，概率为10%
	for (int i = 0; i < graph.nodeNum; i++)
	{
		for (int j = 0; j < graph.nodeNum; j++)
		{
			int m = randomInt(0, 100);
			if (m <= 10)
				edge[i][j] = 1;
		}
	}



	//保证生成正向连通图，删去多余的边
	int preNode[NODE_MAX] = {}, afterNode[NODE_MAX] = {};
	for (int i = 0; i < graph.nodeNum; i++)
	{
		for (int j = 0; j < graph.nodeNum; j++)
		{
			if (i >= j)
			{
				edge[i][j] = 0;
				continue;
			}
			if (j > 0 && edge[i][j] > 0)
			{
				preNode[j] = 1;
				afterNode[i] = 1;
			}
		}
	}

	//把矩阵表示转化为链表表示 并且如果i没有入度，那么i和nodes[0]相连  如果i没有出度，那么i和nodes[nodenum-1]相连 
	for (int i = 0; i < graph.nodeNum - 1; i++)
	{
		for (int j = 0; j < graph.nodeNum; j++)
		{
			if (edge[i][j] == 1)
			{
				Arc* arc = (Arc*)malloc(sizeof(Arc));
				arc->go = j;
				arc->next = graph.nodes[i].edge;
				graph.nodes[i].edge = arc;
			}
		}
		if (preNode[i] == 0 && i > 0)
		{
			Arc* arc = (Arc*)malloc(sizeof(Arc));
			arc->go = i;
			arc->next = graph.nodes[0].edge;
			graph.nodes[0].edge = arc;
		}
		if (afterNode[i] == 0)
		{
			Arc* arc = (Arc*)malloc(sizeof(Arc));
			arc->go = graph.nodeNum - 1;
			arc->next = graph.nodes[i].edge;
			graph.nodes[i].edge = arc;
		}
	}

	//	displayGraph(graph);
}

void criticalPath(MyGraph& graph, double* nodes, int length)
{
	double machinetimes[100] = {};

	//首先对边的权值进行赋值
	for (int i = 0; i < graph.nodeNum; i++)
	{
		Arc* arc = graph.nodes[i].edge;
		double sum = 0;
		while (arc != nullptr)
		{
			sum += nodes[i];
			//		machinetimes[nodeMachine[]]
			arc->weight = sum;
			arc = arc->next;
		}
	}
	//赋值结束

	//然后寻找结点的入度
	int indegree[NODE_MAX] = {};
	for (int i = 0; i < graph.nodeNum; i++)
	{
		Arc* arc = graph.nodes[i].edge;
		for (; arc; arc = arc->next)
		{
			indegree[arc->go]++;
		}
	}
	int count = 0;
	queue<int> Q;
	for (int i = 0; i < graph.nodeNum; i++)
	{
		if (indegree[i] == 0)
		{
			Q.push(i);
		}
	}

	double ve[NODE_MAX] = {}, vl[NODE_MAX] = {};
	stack<int> S;
	while (!Q.empty())
	{
		int now = Q.front();
		Q.pop();
		S.push(now);
		count++;
		Arc* arc = graph.nodes[now].edge;
		for (; arc != nullptr; arc = arc->next)
		{
			int num = arc->go;
			if (--indegree[num] == 0)
			{
				Q.push(num);
			}
			if (ve[now] + arc->weight > ve[num])
			{
				ve[num] = ve[now] + arc->weight;
			}
		}
	}

	//已经求完拓扑排序
	//求出关键路径
	Arc* arc;
	int path = 0;
	double insNum = 0;
	if (count != graph.nodeNum)
	{
		graph.InstNum = -1;

		printf("拓扑结构错误\n");
	}
	int i, k;
	for (i = 0; i < graph.nodeNum; i++)
	{
		vl[i] = ve[graph.nodeNum - 1];
	}

	while (!S.empty())
	{
		int j = S.top();
		S.pop();

		for (arc = graph.nodes[j].edge; arc; arc = arc->next)
		{
			int num = arc->go;
			double dut = arc->weight;
			if (vl[num] - dut < vl[j])
			{
				vl[j] = vl[num] - dut;
			}
		}
	}
	//displayGraph(graph);


//	freopen("criticalpath.txt","w",stdout);
	for (int i = 0; i < graph.nodeNum; i++)
	{
		int flag = 0;
		arc = graph.nodes[i].edge;
		for (; arc; arc = arc->next)
		{
			k = arc->go;
			double dut = arc->weight;
			double ee = ve[i], el = vl[k] - dut;
			double mm = fabs(ee - el);
			char tag = (fabs(el - ee) < 0.001) ? '*' : ' ';
			if (tag == '*') {
				insNum += arc->weight;
				//			printf("%d->%d[shape=circle,label=\"%lf\"];\n",i,arc->go,arc->weight);
			}
		}
	}
	//	freopen("CON","w",stdout);
	graph.InstNum = insNum;
}

void displayGraph(MyGraph& graph)
{
	freopen("graph.txt", "w", stdout);
	printf("digraph G{\n");
	for (int i = 0; i < graph.nodeNum; i++)
	{
		Arc* arc = graph.nodes[i].edge;
		for (; arc; arc = arc->next)
		{
			printf("%d->%d[shape=circle,label=\"%lf\"];\n", i, arc->go, arc->weight);
		}
	}
	printf("}\n");
}

void displayGraph(int edge[NODE_MAX][NODE_MAX], int length)
{
	freopen("halfGraph.txt", "w", stdout);
	printf("digraph halfG{\n");
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (edge[i][j] > 0)
			{
				printf("%d->%d[shape=circle,arrowhead=none];\n", i, j);
			}
		}
	}
	printf("}\n");
}

void displayGraph(int edge[NODE_MAX][NODE_MAX], int length, int times)
{
	string path = "halfGraph" + std::to_string(times);
	const char *p = path.c_str();
	freopen(p, "w", stdout);
	printf("digraph halfG{\n");
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (edge[i][j] > 0)
			{
				printf("%d->%d[shape=circle,arrowhead=none];\n", i, j);
			}
		}
	}
	printf("}\n");
}