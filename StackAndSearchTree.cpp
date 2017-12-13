/*****************experiment *******************************
1、创建最大堆类，最大堆的存储结构使用链表。
2、提供操作:堆的插入、堆的删除。堆的初始化。Huffman树的构造。二叉搜索树的构造。
3、接收键盘录入的一系列整数，输出其对应的最大堆、Huffman编码以及二叉搜索树。
堆排序*/
#include <iostream>
using namespace std;
//最大堆
class MaxHeap
{
public:
	MaxHeap()
	{
		int MaxHeapSize = 10;
	}
	MaxHeap(int MaxHeapSize)
	{
		MaxSize = MaxHeapSize;
		heap = new int[MaxSize + 1];
		CurrentSize = 0;
	}
	~MaxHeap()
	{
		delete[] heap;
	}
	void Deactivate()
	{
		heap = 0;
	}
	int Size() const
	{
		return CurrentSize;
	}

	int Max()
	{
		if (CurrentSize == 0)
			cout << "异常" << endl;
		return heap[1];
	}
	MaxHeap& Insert(const int x)
	{//最大堆的插入
		if (CurrentSize == MaxSize)
			cout << "no space" << endl;
		//寻找插入的位置
		//i从新的叶节点开始，并沿着树上升
		int i = ++CurrentSize;
		//是否到达根，在i处是否改变最大树的性质
		while (i != 1 && x>heap[i / 2])
		{//不能把x放入heap[i]
			heap[i] = heap[i / 2];//将元素下移
			i /= 2;//移向父节点
		}
		heap[i] = x;//可以插入到i
		return *this;
	}
	//最大堆的删除
	MaxHeap& DeleteMax(int& x)
	{//将最大元素放入x，并从堆中删除最大元素
		// 检查堆是否为空
		if (CurrentSize == 0)
			cout << " null queue!" << endl;
		x = heap[1];//最大元素
		//重构堆
		int y = heap[CurrentSize--];//最后一个元素
		//从根开始，为y寻找合适的位置
		int i = 1;//堆的当前节点
		int ci = 2;//i的孩子
		while (ci <= CurrentSize)
		{//heap[ci]应是i的较大的孩子
			if (ci<CurrentSize&&heap[ci]<heap[ci + 1])
				ci++;
			//能把y放入heap[i]吗？
			if (y >= heap[ci])//能
				break;
			//不能
			heap[i] = heap[ci];//将孩子（正是较大的那个）上移
			i = ci;//下移一层
			ci = ci * 2;
		}
		heap[i] = y;

		return *this;
	}

	//最大堆的初始化
	void Initialize(int a[], int size, int ArraySize)
	{
		delete[] heap;
		heap = a;
		CurrentSize = size;
		MaxSize = ArraySize;
		//产生一个最大堆
		//从第一个含有孩子的节点开始
		for (int i = CurrentSize / 2; i >= 1; i--)
		{
			int y = heap[i];//子树的根
			//寻找放置y的位置
			int c = 2 * i;//c的父节点是y的目标位置
			while (c <= CurrentSize)
			{//heap[c]应是较大的同胞节点
				if (c<CurrentSize&&heap[c]<heap[c + 1])
					c++;
				//能把y放入heap[c/2]吗
				if (y >= heap[c])
					break;//能
				//不能
				heap[c / 2] = heap[c];//将孩子上移
				c *= 2;//下移一层
			}
			heap[c / 2] = y;
		}
	}
public:
	int CurrentSize, MaxSize;
	int *heap;
};
//最小堆
template <class T>
class MinHeap
{
public:
	MinHeap()
	{
		int MinHeapSize = 10;
	}
	MinHeap(int MinHeapSize)
	{
		MinSize = MinHeapSize;
		heap = new T[MinSize + 1];
		CurrentSize = 0;
	}
	~MinHeap()
	{
		delete[] heap;
	}
	void Deactivate()
	{
		heap = 0;
	}
	int Size() const
	{
		return CurrentSize;
	}

	T Min()
	{
		if (CurrentSize == 0)
			cout << "异常" << endl;
		return heap[1];
	}
	MinHeap<T>& Insert(const T x)
	{
		if (CurrentSize == MinSize)
			cout << "no space" << endl;
		int i = ++CurrentSize;
		while (i != 1 && x<heap[i / 2])
		{
			heap[i] = heap[i / 2];
			i /= 2;
		}
		heap[i] = x;
		return *this;
	}

	MinHeap& DeleteMin(T& x)
	{
		if (CurrentSize == 0)
			cout << " null queue!" << endl;
		x = heap[1];

		T y = heap[CurrentSize--];
		int i = 1;
		int ci = 2;
		while (ci <= CurrentSize)
		{
			if (ci<CurrentSize&&heap[ci]>heap[ci + 1])
				ci++;
			if (y <= heap[ci])
				break;

			heap[i] = heap[ci];
			i = ci;
			ci = ci * 2;
		}
		heap[i] = y;

		return *this;
	}
	//最小堆的初始化
	void Initialize(T a[], int size, int ArraySize)
	{
		delete[] heap;
		heap = a;
		CurrentSize = size;
		MinSize = ArraySize;
		//产生一个最小堆
		//从第一个含有孩子的节点开始
		for (int i = CurrentSize / 2; i >= 1; i--)
		{
			T y = heap[i];//子树的根
			//寻找放置y的位置
			int c = 2 * i;//c的父节点是y的目标位置
			while (c <= CurrentSize)
			{//heap[c]应是较小的同胞节点
				if (c<CurrentSize&&heap[c]>heap[c + 1])
					c++;
				//能把y放入heap[c/2]吗
				if (y <= heap[c])
					break;//能
				//不能
				heap[c / 2] = heap[c];
				c *= 2;
			}
			heap[c / 2] = y;
		}
	}
public:
	int CurrentSize, MinSize;
	T *heap;
};
//二叉树
//二叉树的节点类
class BinaryTreeNode
{
	//friend class BinaryTree;
public:
	BinaryTreeNode()
	{
		LeftChild = RightChild = 0;
	}
	BinaryTreeNode(const int& e)
	{
		data = e;
		LeftChild = RightChild = 0;
	}
	BinaryTreeNode(const int& e, BinaryTreeNode *l, BinaryTreeNode *r)
	{
		data = e;
		LeftChild = l;
		RightChild = r;
	}
public:
	int data;
	BinaryTreeNode *LeftChild, *RightChild;
};
//二叉树类定义
class BinaryTree
{
	friend class BinaryTreeNode;
public:
	BinaryTree(){ root = 0; }
	virtual ~BinaryTree(){};
	//判断是否为空
	bool IsEmpty() const
	{
		return((root) ? false : true);
	}
	//取根节点
	bool Root(int& x) const
	{
		if (root)
		{
			x = root->data;
			return true;
		}
		else
			return false;
	}
	//创造二叉树
	void MakeTree(const int& element, BinaryTree& left, BinaryTree& right)
	{
		root = new BinaryTreeNode(element, left.root, right.root);
		left.root = right.root = 0;
	}
	//拆分二叉树
	void BreakTree(int& element, BinaryTree& left, BinaryTree& right)
	{
		if (!root)
			cout << "kongshu" << endl;
		element = root->data;
		left.root = root->LeftChild;
		right.root = root->RightChild;
		delete root;
		root = 0;
	}
	//前序遍历
	void PreOrder(void(*Visit)(BinaryTreeNode* u))
	{
		PreOrder(Visit, root);
	}
	//中序遍历

	void InOrder(void(*Visit)(BinaryTreeNode* u))
	{
		InOrder(Visit, root);
	}
	//后序遍历
	void PostOrder(void(*Visit)(BinaryTreeNode* u))
	{
		PostOrder(Visit, root);
	}
	//计算高度 
	int Height(BinaryTreeNode *t) const
	{
		if (!t)
			return 0;
		int hl = Height(t->LeftChild);
		int hr = Height(t->RightChild);
		if (hl>hr)
			return ++hl;
		else
			return ++hr;
	}

public:
	BinaryTreeNode *root;
	void PreOrder(void(*Visit)(BinaryTreeNode *u), BinaryTreeNode *t)
	{
		if (t)
		{
			Visit(t);
			PreOrder(Visit, t->LeftChild);
			PreOrder(Visit, t->RightChild);
		}
	}
	void InOrder(void(*Visit)(BinaryTreeNode *u), BinaryTreeNode *t)
	{
		if (t)
		{
			InOrder(Visit, t->LeftChild);
			Visit(t);
			InOrder(Visit, t->RightChild);
		}
	}
	void PostOrder(void(*Visit)(BinaryTreeNode *u), BinaryTreeNode *t)
	{
		if (t)
		{
			PostOrder(Visit, t->LeftChild);
			PostOrder(Visit, t->RightChild);
			Visit(t);
		}
	}
	//输出
	static void Output(BinaryTreeNode* t)
	{
		cout << t->data << ' ';
	}
	void PreOutput()
	{
		PreOrder(Output, root);
		cout << endl;
	}
	void InOutput()
	{
		InOrder(Output, root);
		cout << endl;
	}
	void PostOutput()
	{
		PostOrder(Output, root);
		cout << endl;
	}

	//由前序和中序  求出后序
	void output(BinaryTreeNode *t)
	{
		if (t)
		{
			output(t->LeftChild);
			output(t->RightChild);
			cout << t->data << ' ';
		}
	}
};

//链表节点
class ChainNode
{


public:
	friend class Chain;
	int data;
	ChainNode *link;

};

class Chain
{
public:

	Chain();
	virtual ~Chain();
	int Length() const;
	int Search(const int&x) const;
	Chain& Delete(int k, int& x);
	Chain& Insert(int k, int& x);
	Chain& Append(int& x);
	Chain& DeleteLast();
	void Output();

	ChainNode *first;


};

Chain::Chain()
{
	first = 0;

}

Chain::~Chain()//析构
{

	ChainNode *next;
	while (first)
	{
		next = first->link;
		//delete first;
		first = next;
	}

}
int Chain::Length() const//获得链表大小
{
	ChainNode *current = first;
	int len = 0;
	while (current)
	{
		len++;
		current = current->link;
	}
	return len;
}
int Chain::Search(const int&x) const//搜索一个值
{
	ChainNode *current = first;
	int index = 1;
	while (current && current->data != x)
	{
		current = current->link;
		index++;
	}
	if (current)  return index;
	return 0;
}
void Chain::Output()
{
	ChainNode *current = first;

	while (current)
	{
		cout << current->data;
		current = current->link;
	}
	cout << endl;

}
Chain& Chain::Delete(int k, int& x) //删除地k个元素,并保存在x中
{

	if (k<1 || !first)
	{
		cout << "ERROR: OutOfBound  AAAA";
		return *this;
	}
	ChainNode *p = first;
	if (k == 1)
		first = first->link;
	else
	{
		ChainNode *q = first;
		for (int index = 1; index<k - 1 && q; index++)
			q = q->link;
		if (!q || !q->link)
		{
			cout << "ERROR: OutOfBound BBBB";
			return *this;
		}
		p = q->link;
		q->link = p->link;
	}
	x = p->data;
	delete p;
	return *this;
}
Chain& Chain::Insert(int k, int& x)//在第k个元素后插入x
{
	if (k<0)
	{
		cout << "ERROR: OutOfBound CCCC";
		return *this;
	}
	ChainNode *p = first;
	for (int index = 1; index<k && p; index++)
		p = p->link;

	if (k>0 && !p)
	{
		cout << "ERROR: OutOfBound DDDD";
		return *this;
	}

	ChainNode *y = new ChainNode;
	y->data = x;
	if (k)
	{
		y->link = p->link;
		p->link = y;
	}
	else
	{
		y->link = first;
		first = y;
	}
	return *this;
}
//霍夫曼类

class Huffman
{
	friend BinaryTree HuffmanTree(int[], int);
public:
	Huffman(){};
	~Huffman(){};
	operator int() const
	{
		return weight;
	}

	//template <class T>///////////////////////////////////////////////////////////////////////////////////////
	BinaryTree HuffmanTree(int a[], int n)
	{//根据权重a[1:n]构造霍夫曼树
		//创建一个单节点树的数组
		Huffman *w = new Huffman[n + 1];
		BinaryTree z, zero;
		for (int i = 1; i <= n; i++)
		{
			z.MakeTree(a[i], zero, zero);
			w[i].weight = a[i];
			w[i].tree = z;
		}
		//把数组变成一个最小堆
		MinHeap<Huffman> H(1);
		H.Initialize(w, n, n);

		//将堆中的树不断合并
		Huffman x, y;
		for (int i = 1; i<n; i++)
		{
			H.DeleteMin(x);
			H.DeleteMin(y);
			z.MakeTree(0, x.tree, y.tree);
			x.weight += y.weight;
			x.tree = z;
			H.Insert(x);
		}

		H.DeleteMin(x);//最后的树
		H.Deactivate();
		delete[] w;
		return x.tree;
	}

	void Code(BinaryTree huf, Chain& c, int x, int& zero, int& one)
	{
		BinaryTreeNode *t;
		t = huf.root;
		BinaryTree left, right;
		//递归
		if (t->LeftChild)
		{
			c.Insert(c.Length(), zero);
			left.root = t->LeftChild;
			Code(left, c, x, zero, one);
		}
		if (t->RightChild)
		{
			c.Insert(c.Length(), one);
			right.root = t->RightChild;
			Code(right, c, x, zero, one);
		}
		if (t->LeftChild == NULL && t->RightChild == NULL)
		{
			cout << "权值为" << t->data << "的编码：";
			c.Output();
			c.Delete(c.Length(), x);
			return;

		}
		if (c.Length() >= 1)
			c.Delete(c.Length(), x);
		if (c.Length() == 0)
			return;
		return;

	}
public:
	BinaryTree tree;
	int weight;
};

class BSTree :public BinaryTree
{
public:
	BSTree(){}
	virtual ~BSTree(){}


	bool Search(const int& k, int& e) const
	{//搜索与k匹配的元素
		//指针p从树根开始查找
		BinaryTreeNode *p = root;
		while (p)//检查p->data
			if (k<p->data) p = p->LeftChild;
			else if (k>p->data) p = p->RightChild;
			else
			{//找到元素
				e = p->data;
				return true;
			}

		return false;
	}

	BSTree& Insert(const int& e)
	{
		BinaryTreeNode *p = root,//搜索指针
			*pp = 0;//p的父节点指针
		while (p)
		{//检查p->data
			pp = p;
			//将p移向孩子节点
			if (e<p->data) p = p->LeftChild;
			else if (e>p->data) p = p->RightChild;
			else
				cout << "failure" << endl;//出现重复
		}
		//为e建立一个节点，并将该节点连接至pp
		BinaryTreeNode *r = new BinaryTreeNode(e);
		if (root)
		{
			if (e<pp->data) pp->LeftChild = r;
			else pp->RightChild = r;
		}
		else//插入到空树
			root = r;

		return *this;
	}


	BSTree& Delete(const int& k, int& e)
	{//删除关键之为k的元素并将其放入e
		BinaryTreeNode *p = root, *pp = 0;
		while (p && p->data != k)
		{
			pp = p;
			if (k<p->data) p = p->LeftChild;
			else p = p->RightChild;
		}
		if (!p)
			cout << "NO key" << endl;

		e = p->data;

		//对树进行重构
		//处理p有两个孩子的情形
		if (p->LeftChild && p->RightChild)//两个孩子
		{//转换成有0或1个孩子的情形
			//在潘的左子树中
			BinaryTreeNode *s = p->LeftChild, *ps = p;
			while (s->RightChild)
			{
				ps = s;
				s = s->RightChild;
			}

			p->data = s->data;
			p = s;
			pp = ps;
		}

		BinaryTreeNode *c;
		if (p->LeftChild) c = p->LeftChild;
		else c = p->RightChild;

		if (p == root) root = c;
		else
		{
			if (p == pp->LeftChild)
				pp->LeftChild = c;
			else
				pp->RightChild = c;
		}

		delete p;
		return *this;


	}

	void Ascend(){ InOutput(); }

};


void main()
{
	//堆
	cout << "堆" << endl;
	int n;
	cout << "堆的大小(最大为10)： ";
	cin >> n;
	int *a = new int[12];
	cout << "输入元素  : ";
	for (int i = 1; i<n + 1; i++)
		cin >> a[i];
	MaxHeap m(n);
	//初始化
	m.Initialize(a, n, 10);
	cout << "对最大堆进行初始化" << endl;
	cout << "输出最大堆：";
	for (int j = 1; j <= n; j++)
		cout << m.heap[j] << " ";
	cout << endl;
	//插入
	cout << "堆的插入" << endl;
	cout << "输入要插入的值：";
	int b;
	cin >> b;
	m.Insert(b);
	cout << "输出插入" << b << "的最大堆：";
	for (int i1 = 1; i1<n + 2; i1++)
		cout << m.heap[i1] << " ";
	cout << endl;
	//堆的删除
	cout << "堆的删除" << endl;
	int x;
	m.DeleteMax(x);
	cout << "删除的元素为： ";
	cout << x << endl;
	cout << "输出最大堆：";
	for (int j1 = 1; j1<n + 1; j1++)
		cout << m.heap[j1] << " ";
	//堆排序
	cout << endl;
	cout << "堆排序" << endl;
	cout << "排序前：";
	for (int i2 = 1; i2<n + 1; i2++)
		cout << m.heap[i2] << " ";
	cout << endl;
	cout << "排序后：";
	for (int i3 = 1; i3<n + 1; i3++)
	{
		m.DeleteMax(x);
		cout << x << " ";
	}
	cout << endl;
	cout << "///////////////////////////////////////////////////////" << endl;
	//霍夫曼树
	cout << "霍夫曼树" << endl;
	int n1;
	cout << "权值的个数(最大为10)： ";
	cin >> n1;
	int *a1 = new int[n1 + 1];
	cout << "输入每个权值  : ";
	for (int i4 = 1; i4<n1 + 1; i4++)
		cin >> a1[i4];

	Huffman huff;
	BinaryTree hufftree;
	hufftree = huff.HuffmanTree(a1, n1);
	// hufftree.PreOutput();
	// hufftree.InOutput();
	// hufftree.PostOutput();
	//输出编码
	int x1 = 0;
	Chain c;
	static int zero = 0, one = 1;
	huff.Code(hufftree, c, x1, zero, one);
	cout << "///////////////////////////////////////////////////////" << endl;
	//二叉搜索树
	cout << "二叉搜索树" << endl;
	int n2;
	cout << "二叉搜索树的大小： ";
	cin >> n2;
	int *a2 = new int[n2 + 1];
	cout << "输入元素  : ";
	for (int i6 = 1; i6<n2 + 1; i6++)
		cin >> a2[i6];
	BSTree bs;
	for (int i5 = 1; i5<n2 + 1; i5++)
		bs.Insert(a2[i5]);
	cout << "输出二叉搜索树：";
	bs.Ascend();
}
