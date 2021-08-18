
#ifndef __MYGRAPH_H__
#define __MYGRAPH_H__

#define NODE_MAX 1000 
struct Arc {
	double weight;
	struct Arc* next;
	int go;
};

struct Node {
	int index;
	struct Arc* edge;
};

struct MyGraph {
	Node nodes[NODE_MAX];
	int nodeNum;
	double InstNum;
};

//*@ param graph 要初始化的图
//*@ param num   要初始化的图的结点的数量
//*@ note        对图进行初始化: 边的权值 点的索引 点的个数 指令总数
void graphInit(MyGraph& graph, int num);

//*@ note          随机生成连通图
//*@ param graph   初始化后的图
void graphRandom(MyGraph& graph);

//*@ param graph  随机化之后的图
//*@ param nodes  一串存放图的节点的指令数的数组（指令数/机器数已经计算好）
//*@ param length 数组长度
//*@ note         求出图的关键路径
void criticalPath(MyGraph& graph, double* nodes, int length);

//*@ param graph 需要展示的图
//*@ note        输出图的dot语言
void displayGraph(MyGraph& graph);

//*@ param edge[NODE_MAX][NODE_MAX] 二维邻接矩阵
//*@ param length                   邻接矩阵的长和宽(图的实际节点个数)
//*@ note                           输出图的dot语言
void displayGraph(int edge[NODE_MAX][NODE_MAX], int length);

//*@ param edge[NODE_MAX][NODE_MAX] 二维邻接矩阵
//*@ param length                   邻接矩阵的长和宽(图的实际节点个数)
//*@ param times                    方便区分这是第几个
//*@ note                           输出图的dot语言
void displayGraph(int edge[NODE_MAX][NODE_MAX], int length, int times);

//*@ param low       随机数最小值
//*@ param high     随机数最大值
//*@ note                生成随机整数
int randomInt(int low, int high);

#endif // !__MYGRAPH_H__



