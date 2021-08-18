
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

//*@ param graph Ҫ��ʼ����ͼ
//*@ param num   Ҫ��ʼ����ͼ�Ľ�������
//*@ note        ��ͼ���г�ʼ��: �ߵ�Ȩֵ ������� ��ĸ��� ָ������
void graphInit(MyGraph& graph, int num);

//*@ note          ���������ͨͼ
//*@ param graph   ��ʼ�����ͼ
void graphRandom(MyGraph& graph);

//*@ param graph  �����֮���ͼ
//*@ param nodes  һ�����ͼ�Ľڵ��ָ���������飨ָ����/�������Ѿ�����ã�
//*@ param length ���鳤��
//*@ note         ���ͼ�Ĺؼ�·��
void criticalPath(MyGraph& graph, double* nodes, int length);

//*@ param graph ��Ҫչʾ��ͼ
//*@ note        ���ͼ��dot����
void displayGraph(MyGraph& graph);

//*@ param edge[NODE_MAX][NODE_MAX] ��ά�ڽӾ���
//*@ param length                   �ڽӾ���ĳ��Ϳ�(ͼ��ʵ�ʽڵ����)
//*@ note                           ���ͼ��dot����
void displayGraph(int edge[NODE_MAX][NODE_MAX], int length);

//*@ param edge[NODE_MAX][NODE_MAX] ��ά�ڽӾ���
//*@ param length                   �ڽӾ���ĳ��Ϳ�(ͼ��ʵ�ʽڵ����)
//*@ param times                    �����������ǵڼ���
//*@ note                           ���ͼ��dot����
void displayGraph(int edge[NODE_MAX][NODE_MAX], int length, int times);

//*@ param low       �������Сֵ
//*@ param high     ��������ֵ
//*@ note                �����������
int randomInt(int low, int high);

#endif // !__MYGRAPH_H__



