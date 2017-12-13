/*****************experiment *******************************
1�����������࣬���ѵĴ洢�ṹʹ������
2���ṩ����:�ѵĲ��롢�ѵ�ɾ�����ѵĳ�ʼ����Huffman���Ĺ��졣�����������Ĺ��졣
3�����ռ���¼���һϵ��������������Ӧ�����ѡ�Huffman�����Լ�������������
������*/
#include <iostream>
using namespace std;
//����
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
			cout << "�쳣" << endl;
		return heap[1];
	}
	MaxHeap& Insert(const int x)
	{//���ѵĲ���
		if (CurrentSize == MaxSize)
			cout << "no space" << endl;
		//Ѱ�Ҳ����λ��
		//i���µ�Ҷ�ڵ㿪ʼ��������������
		int i = ++CurrentSize;
		//�Ƿ񵽴������i���Ƿ�ı������������
		while (i != 1 && x>heap[i / 2])
		{//���ܰ�x����heap[i]
			heap[i] = heap[i / 2];//��Ԫ������
			i /= 2;//���򸸽ڵ�
		}
		heap[i] = x;//���Բ��뵽i
		return *this;
	}
	//���ѵ�ɾ��
	MaxHeap& DeleteMax(int& x)
	{//�����Ԫ�ط���x�����Ӷ���ɾ�����Ԫ��
		// �����Ƿ�Ϊ��
		if (CurrentSize == 0)
			cout << " null queue!" << endl;
		x = heap[1];//���Ԫ��
		//�ع���
		int y = heap[CurrentSize--];//���һ��Ԫ��
		//�Ӹ���ʼ��ΪyѰ�Һ��ʵ�λ��
		int i = 1;//�ѵĵ�ǰ�ڵ�
		int ci = 2;//i�ĺ���
		while (ci <= CurrentSize)
		{//heap[ci]Ӧ��i�Ľϴ�ĺ���
			if (ci<CurrentSize&&heap[ci]<heap[ci + 1])
				ci++;
			//�ܰ�y����heap[i]��
			if (y >= heap[ci])//��
				break;
			//����
			heap[i] = heap[ci];//�����ӣ����ǽϴ���Ǹ�������
			i = ci;//����һ��
			ci = ci * 2;
		}
		heap[i] = y;

		return *this;
	}

	//���ѵĳ�ʼ��
	void Initialize(int a[], int size, int ArraySize)
	{
		delete[] heap;
		heap = a;
		CurrentSize = size;
		MaxSize = ArraySize;
		//����һ������
		//�ӵ�һ�����к��ӵĽڵ㿪ʼ
		for (int i = CurrentSize / 2; i >= 1; i--)
		{
			int y = heap[i];//�����ĸ�
			//Ѱ�ҷ���y��λ��
			int c = 2 * i;//c�ĸ��ڵ���y��Ŀ��λ��
			while (c <= CurrentSize)
			{//heap[c]Ӧ�ǽϴ��ͬ���ڵ�
				if (c<CurrentSize&&heap[c]<heap[c + 1])
					c++;
				//�ܰ�y����heap[c/2]��
				if (y >= heap[c])
					break;//��
				//����
				heap[c / 2] = heap[c];//����������
				c *= 2;//����һ��
			}
			heap[c / 2] = y;
		}
	}
public:
	int CurrentSize, MaxSize;
	int *heap;
};
//��С��
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
			cout << "�쳣" << endl;
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
	//��С�ѵĳ�ʼ��
	void Initialize(T a[], int size, int ArraySize)
	{
		delete[] heap;
		heap = a;
		CurrentSize = size;
		MinSize = ArraySize;
		//����һ����С��
		//�ӵ�һ�����к��ӵĽڵ㿪ʼ
		for (int i = CurrentSize / 2; i >= 1; i--)
		{
			T y = heap[i];//�����ĸ�
			//Ѱ�ҷ���y��λ��
			int c = 2 * i;//c�ĸ��ڵ���y��Ŀ��λ��
			while (c <= CurrentSize)
			{//heap[c]Ӧ�ǽ�С��ͬ���ڵ�
				if (c<CurrentSize&&heap[c]>heap[c + 1])
					c++;
				//�ܰ�y����heap[c/2]��
				if (y <= heap[c])
					break;//��
				//����
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
//������
//�������Ľڵ���
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
//�������ඨ��
class BinaryTree
{
	friend class BinaryTreeNode;
public:
	BinaryTree(){ root = 0; }
	virtual ~BinaryTree(){};
	//�ж��Ƿ�Ϊ��
	bool IsEmpty() const
	{
		return((root) ? false : true);
	}
	//ȡ���ڵ�
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
	//���������
	void MakeTree(const int& element, BinaryTree& left, BinaryTree& right)
	{
		root = new BinaryTreeNode(element, left.root, right.root);
		left.root = right.root = 0;
	}
	//��ֶ�����
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
	//ǰ�����
	void PreOrder(void(*Visit)(BinaryTreeNode* u))
	{
		PreOrder(Visit, root);
	}
	//�������

	void InOrder(void(*Visit)(BinaryTreeNode* u))
	{
		InOrder(Visit, root);
	}
	//�������
	void PostOrder(void(*Visit)(BinaryTreeNode* u))
	{
		PostOrder(Visit, root);
	}
	//����߶� 
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
	//���
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

	//��ǰ�������  �������
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

//����ڵ�
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

Chain::~Chain()//����
{

	ChainNode *next;
	while (first)
	{
		next = first->link;
		//delete first;
		first = next;
	}

}
int Chain::Length() const//��������С
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
int Chain::Search(const int&x) const//����һ��ֵ
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
Chain& Chain::Delete(int k, int& x) //ɾ����k��Ԫ��,��������x��
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
Chain& Chain::Insert(int k, int& x)//�ڵ�k��Ԫ�غ����x
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
//��������

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
	{//����Ȩ��a[1:n]�����������
		//����һ�����ڵ���������
		Huffman *w = new Huffman[n + 1];
		BinaryTree z, zero;
		for (int i = 1; i <= n; i++)
		{
			z.MakeTree(a[i], zero, zero);
			w[i].weight = a[i];
			w[i].tree = z;
		}
		//��������һ����С��
		MinHeap<Huffman> H(1);
		H.Initialize(w, n, n);

		//�����е������Ϻϲ�
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

		H.DeleteMin(x);//������
		H.Deactivate();
		delete[] w;
		return x.tree;
	}

	void Code(BinaryTree huf, Chain& c, int x, int& zero, int& one)
	{
		BinaryTreeNode *t;
		t = huf.root;
		BinaryTree left, right;
		//�ݹ�
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
			cout << "ȨֵΪ" << t->data << "�ı��룺";
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
	{//������kƥ���Ԫ��
		//ָ��p��������ʼ����
		BinaryTreeNode *p = root;
		while (p)//���p->data
			if (k<p->data) p = p->LeftChild;
			else if (k>p->data) p = p->RightChild;
			else
			{//�ҵ�Ԫ��
				e = p->data;
				return true;
			}

		return false;
	}

	BSTree& Insert(const int& e)
	{
		BinaryTreeNode *p = root,//����ָ��
			*pp = 0;//p�ĸ��ڵ�ָ��
		while (p)
		{//���p->data
			pp = p;
			//��p�����ӽڵ�
			if (e<p->data) p = p->LeftChild;
			else if (e>p->data) p = p->RightChild;
			else
				cout << "failure" << endl;//�����ظ�
		}
		//Ϊe����һ���ڵ㣬�����ýڵ�������pp
		BinaryTreeNode *r = new BinaryTreeNode(e);
		if (root)
		{
			if (e<pp->data) pp->LeftChild = r;
			else pp->RightChild = r;
		}
		else//���뵽����
			root = r;

		return *this;
	}


	BSTree& Delete(const int& k, int& e)
	{//ɾ���ؼ�֮Ϊk��Ԫ�ز��������e
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

		//���������ع�
		//����p���������ӵ�����
		if (p->LeftChild && p->RightChild)//��������
		{//ת������0��1�����ӵ�����
			//���˵���������
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
	//��
	cout << "��" << endl;
	int n;
	cout << "�ѵĴ�С(���Ϊ10)�� ";
	cin >> n;
	int *a = new int[12];
	cout << "����Ԫ��  : ";
	for (int i = 1; i<n + 1; i++)
		cin >> a[i];
	MaxHeap m(n);
	//��ʼ��
	m.Initialize(a, n, 10);
	cout << "�����ѽ��г�ʼ��" << endl;
	cout << "������ѣ�";
	for (int j = 1; j <= n; j++)
		cout << m.heap[j] << " ";
	cout << endl;
	//����
	cout << "�ѵĲ���" << endl;
	cout << "����Ҫ�����ֵ��";
	int b;
	cin >> b;
	m.Insert(b);
	cout << "�������" << b << "�����ѣ�";
	for (int i1 = 1; i1<n + 2; i1++)
		cout << m.heap[i1] << " ";
	cout << endl;
	//�ѵ�ɾ��
	cout << "�ѵ�ɾ��" << endl;
	int x;
	m.DeleteMax(x);
	cout << "ɾ����Ԫ��Ϊ�� ";
	cout << x << endl;
	cout << "������ѣ�";
	for (int j1 = 1; j1<n + 1; j1++)
		cout << m.heap[j1] << " ";
	//������
	cout << endl;
	cout << "������" << endl;
	cout << "����ǰ��";
	for (int i2 = 1; i2<n + 1; i2++)
		cout << m.heap[i2] << " ";
	cout << endl;
	cout << "�����";
	for (int i3 = 1; i3<n + 1; i3++)
	{
		m.DeleteMax(x);
		cout << x << " ";
	}
	cout << endl;
	cout << "///////////////////////////////////////////////////////" << endl;
	//��������
	cout << "��������" << endl;
	int n1;
	cout << "Ȩֵ�ĸ���(���Ϊ10)�� ";
	cin >> n1;
	int *a1 = new int[n1 + 1];
	cout << "����ÿ��Ȩֵ  : ";
	for (int i4 = 1; i4<n1 + 1; i4++)
		cin >> a1[i4];

	Huffman huff;
	BinaryTree hufftree;
	hufftree = huff.HuffmanTree(a1, n1);
	// hufftree.PreOutput();
	// hufftree.InOutput();
	// hufftree.PostOutput();
	//�������
	int x1 = 0;
	Chain c;
	static int zero = 0, one = 1;
	huff.Code(hufftree, c, x1, zero, one);
	cout << "///////////////////////////////////////////////////////" << endl;
	//����������
	cout << "����������" << endl;
	int n2;
	cout << "�����������Ĵ�С�� ";
	cin >> n2;
	int *a2 = new int[n2 + 1];
	cout << "����Ԫ��  : ";
	for (int i6 = 1; i6<n2 + 1; i6++)
		cin >> a2[i6];
	BSTree bs;
	for (int i5 = 1; i5<n2 + 1; i5++)
		bs.Insert(a2[i5]);
	cout << "���������������";
	bs.Ascend();
}
