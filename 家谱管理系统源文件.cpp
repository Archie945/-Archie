#include <stdio.h>
#include <iostream>
using namespace std;
typedef struct node//����data�洢�ṹ
{
	char name[10];//�����Ա����
	char sex;//�����Ա�Ա�
	char mate[10];//�����Ա��ż����
	int generation;//�����Ա����
}node;

typedef struct btnode//������������ݽṹ
{
	struct node l;//������ֱϵ����
	struct btnode *brother;//����ָ���ֵ�
	struct btnode *child;//����ָ����
}btnode;


btnode *search (btnode *p,char ch[]);//����ָ�뺯����������Ҫ�޸ĺͻ�õĽڵ㣬����ͷָ�������
int generation(btnode *p,char ch[]);//����������³�Ա�Ĵ��ĵķ���ֵ
void children (btnode *p,char b[],char c,int d,char e[]);//�������׺��ӽڵ�
void output(btnode *n);//���������ݵ����
void Search();
void Print(btnode *p);
void Add();
void Delete();
void Inittree();
void Change();
int getdepth(btnode *t);
void lookbrother(btnode *t);
void lookparent (btnode *t,btnode *n);

btnode *root;

void display0()
{
	system("color 6f");
	cout<<"       ******************************************************************************"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       *                             ���׹���ϵͳ                                   *"<<endl;
	cout<<"       *                                                     by  Archie             *"<<endl;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"\n"<<endl;
	cout<<"\n"<<endl;
	cout<<"                     ��ӭʹ�ñ�ϵͳ"<<endl;
	cout<<"                     ����������Ҫ������Ӧ��š�����һ��ʹ�ã����ȳ�ʼ������\n"<<endl;
	cout<<"                     ��ע�⣺��ϵͳ��֧�ִ洢ͬ����Ա \n\n"<<endl;
	cout<<"                     1����ʼ������\n"<<endl;
	cout<<"                     2���鿴���Ⱥ��������Ϣ\n"<<endl;
	cout<<"                     3����Ӽ����Ա\n"<<endl;
	cout<<"                     4���޸ļ����Ա\n"<<endl;
	cout<<"                     5��ɾ�������Ա\n"<<endl;
	cout<<"                     6����ӡ����\n"<<endl;
	cout<<"                     7���˳���ϵͳ\n"<<endl;
	int n,depth;
	scanf("%d",&n);
	while(!n)
	{
		cout<<"                       �����������Ч������������"<<endl;
		scanf("%d",&n);
	}
	while(n<1||n>7)
	{
		cout<<"                       �����������Ч������������"<<endl;
		scanf("%d",&n);
	}
	switch(n)
	{
	case 1:
		Inittree();
		system("pause");
		break;
	case 2:
		Search();
		system("pause");
		break;
	case 3:
		Add();
		system("pause");
		break;
	case 4:
		Change();
		system("pause");
		break;
	case 5:
		Delete();
		system("pause");
		break;
	case 6:
		Print(root);
		system("pause");
		printf("\n��������������˵�");
		system("pause");
		getchar();
		display0();
	case 7:
		exit(0);
		break;
	}
}

btnode *search (btnode *p,char ch[])
{
	btnode *q;
	if(p==NULL)
		return NULL;//û�м��ף�ͷָ����Ϊ��
	if(strcmpi(p->l.name,ch)==0)
		return p;
	if(p->brother)
	{
		q=search(p->brother,ch);
		if(q)
			return q;
	}
	if(p->child)
	{
		q=search(p->child,ch);
		if(q!=NULL)
			return q;
	}
	return NULL;
}
int generation(btnode *p,char ch[])
{
	btnode *q;
	if(p==NULL)
		return 0;
	if(strcmpi(p->l.name,ch)==0)
		return p->l.generation;
	if(p->brother)
	{
		q=search(p->brother,ch);
		if(q)
			return q->l.generation;
	}
	if(p->child)
	{

	}q=search (p->child,ch);
	if(q!=NULL)
		return q->l.generation;
	return 0;
}
void children (btnode *p,char b[],char c,int d,char e[])
{
	for(int i=0;i<10;i++)
	{
		p->l.name[i]=b[i];
		p->l.mate[i]=e[i];
		p->l.sex=c;
		p->l.generation=d;
	}
}
void Inittree()
{
	cout<<"       ******************************************************************************"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       *                             ��ʼ������.....                                *"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"\n"<<endl;
	int a;
	char b[10],c,d[10];
	printf("����������ʼ����������Ա�Ůʿf����ʿm���Լ���ż����");
	free(root);
	root=new btnode;
	scanf("%s %c %s",&b,&c,&d);
	while(c!='m'&&c!='f')
	{
		cout<<"�����Ա��������������������������Ա�Ůʿf����ʿm���Լ���ż����"<<endl;
		scanf("%s %c %s",&b,&c,&d);
	}
	a=1;
	root->child=NULL;
	root->brother=NULL;
	children (root,b,c,a,d);
	printf("���׳�ʼ���ɹ����ѷ������˵�\n");
	display0();
}
void output(btnode *n)
{
	btnode *t=NULL;
	
	printf("����������%s �Ա�%c  Ϊ��%d��,����ż��%s \n",n->l.name,n->l.sex,n->l.generation,n->l.mate);
	printf("\n");
	if(n->child==NULL)
	{
		printf("��������Ů");
	}
	else 
	{
		printf("���˵���Ů:");
		if(n->child->brother==NULL)
		{
			printf("������%s �Ա�%c\t",n->child->l.name,n->child->l.sex);
		}
		else 
		{
			printf("������%s �Ա�%c\t",n->child->l.name,n->child->l.sex);
			t=n->child->brother;
			while(t!=NULL)
			{
				printf("������%s �Ա�%c\t",t->l.name,t->l.sex);
				t=t->brother;
			}
		}
	}
	printf("\n");
	if(n->brother==NULL)
	{
		printf("������ͬ����Ա\n");
	}
	else
	{
		printf("���˵�ͬ����Ա��");
		if(n->brother->brother==NULL)
		{
			printf("������%s �Ա�%c\t",n->brother->l.name,n->brother->l.sex);
		}
		else 
		{
			printf("������%s �Ա�%c\t",n->brother->l.name,n->brother->l.sex);
			t=n->brother->brother;
			while (t!=NULL)
			{
				printf("������%s �Ա�%c\t",t->l.name,t->l.sex);
				t=t->brother;
			}
		}
	}
	lookparent(root,n);
	printf("\n��������������˵�");
		system("pause");
		getchar();
		display0();
}
void Search()
{
	btnode *n;
	char d[10];
	printf("����������ϵͳ�������������Ϣ");
	scanf("%s",&d);
	n=search(root,d);
	while(n==NULL)
	{
		printf("�������˲����ڣ�����������");
		scanf("%s",&d);
		n=search(root,d);
	}
	output(n);
	printf("\n");
	printf("\n��������������˵�");
	system("pause");
	getchar();
	
	display0();
}

int getdepth(btnode *t)
{
	if (!t)
	{
		return 0;
	}
	int ldepth=getdepth(t->child)+1;
	int rdepth=getdepth(t->brother)+1;
	return ldepth>rdepth?ldepth:rdepth;
}
void lookbrother(btnode *t)
{
	if(t!=NULL)
	{
		printf("%s ",t->l.name);
		lookbrother(t->brother);
	}
}

void lookparent (btnode *t,btnode *n)
{
		if(strcmp(t->child->l.name,n->l.name)==0)
		{
			printf("���˵ĸ�ĸ�ǣ�%s��%s\n",t->l.name,t->l.mate);
			system("pause");
			return;
		}
		lookparent(t->child,n);
		lookparent(t->brother,n);
		
}
void Print(btnode *p)
{
	if(strcmp(p->l.name," ")!=0)
	{
		
		printf("��%d����%s�ĺ����У�\n",p->l.generation,p->l.name);
		lookbrother(p->child);
		printf("\n");
	}
	if(p->child)
		Print(p->child);
	if(p->brother)
		Print(p->brother);
}
	


void Delete()
{
	btnode *p;
	char ch[10];
	cout<<"����������Ҫɾ���ĳ�Ա����"<<endl;
	cin>>ch;
	p=search(root,ch);
	if(p==NULL)
	{
		printf("ϵͳ��δ��⵽���ˣ��޷�ɾ��");
		printf("��������������Ҫɾ���ĳ�Ա����");
		cin>>ch;
	    p=search(root,ch);
	}
	p->child=NULL;
	strcpy(p->l.name," ");
	printf("��ɾ��Ŀ���Ա\n");
	printf("\n��������������˵�");
		system("pause");
		getchar();
		display0();

}

void Add()
{
	int a;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       *                             ��ʼ��Ӽ�ͥ��Ա                               *"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"\n"<<endl;
	btnode *n,*m,*t=NULL;
	char b[10],c,d[10],e[10];
	printf("������Ҫ��ӳ�Ա����һ��������");
	scanf("%s",&d);
	n=search (root,d);
	a=generation(root,d);
	while(n==NULL)
	{
		printf("���˲��ڼ����ڣ���������������");
		scanf("%s",&d);
		n=search (root,d);
	}
	if(n->child==NULL)
	{
		printf("����������Ӽ�ͥ��Ա���������Ա�ע�ⲻ���������Լ���ż����");
		scanf("%s %c %s",&b,&c,&e);
		while(c!='m'&&c!='f')
	{
		cout<<"�����Ա����������������������Ա�Ůʿf����ʿm���Լ���ż����"<<endl;
		scanf("%s %c %s",&b,&c,&e);
	}
		a++;
		m=search(root,b);
		if(m!=NULL)
		{
			printf("��⵽���������ʧ�ܣ�");
		}
		else 
		{
			n->child=new btnode;
			n->child->brother=NULL;
			n->child->child=NULL;
			children(n->child,b,c,a,e);
			printf("��ӳɹ���\n");
		}
	}
	else
	{
		n=n->child;
		while (n->brother!=NULL)
			n=n->brother;
		printf("����������Ӽ�ͥ��Ա���������Ա�ע�ⲻ���������Լ���ż����");
		scanf("%s %c %s",&b,&c,&e);
		while(c!='m'&&c!='f')
			{
		cout<<"�����Ա����������������������Ա��Լ���ż��������Ůʿf����ʿm����"<<endl;
		scanf("%s %c %s",&b,&c,&e);
			}
		a++;
		for(int i=0;i<8;i++)
		{
			n->l.mate[i]=e[i];
		}
		m=search(root,b);
		if(m!=NULL)
		printf("��⵽���������ʧ�ܣ�");
		else
		{
			t=new btnode;
			children(t,b,c,a,e);
			t->brother=NULL;
			t->child=NULL;
			n->brother=t;
			printf("��ӳɹ���\n");
		}
	}
	printf("\n��������������˵�\n");
	system("pause");
	getchar();
	display0();
}

void Change()
{
	char a[10],r[10],c;
	btnode *n;
	int i;
	printf("������Ҫ�޸��˵�����");
	scanf("%s",&a);
	n=search(root,a);
	while(n==NULL)
	{
		printf("���˲����ڣ���������������");
		scanf("%s",&a);
		n=search(root,a);
	}
	printf("�Ѳ�ѯ��Ŀ�꣬������Ҫ�޸ĵ�����Ϣ�������ֺ��Ա�");
	scanf("%s %c",&r,&c);
	while(c!='m'&&c!='f')
	{
		cout<<"�����Ա����������������������Ա𣡣�Ůʿf����ʿm����"<<endl;
		scanf("%s %c",&r,&c);
	}
	for(i=0;i<10;i++)
		n->l.name[i]=r[i];
	n->l.sex=c;
	printf("�޸ĳɹ��ѷ������˵�\n");
	display0();
}



int main()
{
	display0();
	return 0;
}