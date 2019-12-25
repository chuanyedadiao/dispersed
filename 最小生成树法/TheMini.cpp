#include<iostream>
#include<stdlib.h>
#include<vector>
#include<malloc.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
using namespace std;

typedef struct sqstack{
	char *base;
	char *top;
	int stacksize;
}SqStack;

typedef struct{
	char str[0x100];
	int total;
}turn;

int row,list;//�� 
int s[0x100]={0};//������С������������Ƿ������ 
int num[0x1000][0x1000]={0}; 
int point=0; //������С���������Ѿ��ҵ��˼����� 
turn Ora[0x100];
int CNT=0;
int MIN=0X1000;

int find_min(vector<vector<int>  > M)
{
    int min;
    min=0x10000;
	int n=0,m;
	for(;n<row;n++)
	{
		for(m=n;m<list;m++)
		{
			if(m==n) continue;
			if(min>M[n][m]&&s[m]!=1) min=M[n][m];
		}
	}
 	return min;
}

void find_tree(vector<vector<int>  > M)
{
	int i,j,min;
	for(point=0;point!=row-1;)
	{
		min=find_min(M);
		for(i=0;i<row;i++)
	    {
			for(j=i+1;j<list;j++){
			    if(M[i][j]==min&&s[j]!=1){
					s[j]=1;
					point++;
					num[i][j]=M[i][j];
					num[j][i]=M[i][j];
					if(point==row) break;
			    }
			}
			if(point==row) break;
	    }//����һ���µ�num�Ķ�ά���飬���ڴ���µı�
	}
}

void InitStack(SqStack *stack)
{
	stack->base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!stack->base) 
	{
		cout<<"����ջʧ�ܣ�";
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}//��ʼ��ջ 

void Push(SqStack *stack,char e)
{
	if(stack->top-stack->base==STACK_INIT_SIZE)
	{
		stack->base=(char *)realloc(stack->base,(stack->stacksize+STACKINCREMENT)*sizeof(char));
		stack->top=stack->base+stack->stacksize;
		stack->stacksize+=STACKINCREMENT;
	}
	if(!stack->base){
		cout<<"����Ԫ��ʱջ�������·���ռ����";
		return;
	}
    *(stack->top)=e;
    stack->top++;
}//���뵽ջtop 

void Pop(SqStack *stack)
{
	if(stack->top-stack->base==0)
	{
		cout<<"��ջΪ�գ�";
		return ;
	}
	stack->top--;
}//����ջ��top 

void visit(char e)
{
	cout<<e;
}
int StackEmpty(SqStack stack)
{
	if(stack.top-stack.base==0)
	{ 
		return 0;
	}
	else {
		return 1;
	}
}
int find_same(char string[],char e)
{
	int i=0;
	while(string[i]!='\0'){
		if(e==string[i]) return 1;
		i++;
	}
	return 0;
}

int Result(char string[],vector<vector<int>  > M)
{
	int final=0;
	int i=0,j=1;
	for(;string[j]!='\0';i++,j++){
		final+=M[string[i]-'a'][string[j]-'a'];
	}
	return final;
}
void Shrink(SqStack stack,int count,vector<vector<int>  > &M)
{
	int i,j=0;
	for(i=0;i<point-1;i++){
		if(!find_same(Ora[count].str,*(stack.base+i))){
		    Ora[count].str[j]=*(stack.base+i);
			j++;
		}
    }
    Ora[count].str[j]=*(stack.top-1);
    Ora[count].total=Result(Ora[count].str,M);
    if(MIN>Ora[count].total) MIN=Ora[count].total;
}
void find_turn(vector<vector<int>  > M)
{
	SqStack stack;
	InitStack(&stack);
	int i=0,j=0,k,start=0;
	int m[0x100][0x100]={0};
	point=0;
	for(start=0;start<row;start++)
	{
		Push(&stack,start+'a');
	    point++;
	    for(i=start;;)
	    {
			if(point==2*row-1){
				Shrink(stack,CNT,M);
				CNT++;
			}
			for(;j<list;j++)
			{
				if(num[i][j]!=0&&m[i][j]!=1){
					m[i][j]=1;
					Push(&stack,j+'a');
					i=j;
					k=0;
					point++;
					break;
				}
			}
			if(j==list){
				if(point==1){
					Pop(&stack);
				}
				else{
					point--;
					i=*(stack.top-2)-'a';
					k=*(stack.top-1)-'a';
					Pop(&stack);
					m[i][k]=0;//��ԭ
					k++;
			    }
			}
			if(!StackEmpty(stack)) break;
			j=k;
	    }
	    point=0;
	    j=0;
	}
}//�ҵ�ŷ����·������ջ 
void Output()
{
	int i;
	for(;i<CNT;i++)
	{
		if(Ora[i].total==MIN){
			cout<<"��СȨֵ��:"<<Ora[i].total<<"   ";
			cout<<"���·����"<<Ora[i].str<<endl;
		}
    }
}
void Print()
{
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<list;j++)
		{
			printf("%d\t",num[i][j]);
		}
		printf("\n");
	}
}
void TSP(vector<vector<int>  > M)
{
	row=M.size();
	list=M[0].size();
	find_tree(M);
	Print();
	find_turn(M);
	Output();
}
int main()
{
	int degree=9;
	vector<vector<int> > W(degree,vector<int>(degree,-1));
	int a[9][9] = {{0,5,12,5,5,2,10,3,15},{5,0,9,7,8,4,2,5,7},{12,9,0,9,16,1,2,4,3},{5,7,9,0,8,3,4,5,6},{5,8,16,8,0,6,7,8,9},{2,4,1,3,6,0,4,3,5},{10,2,2,4,7,4,0,2,3},{3,5,4,5,8,3,2,0,1},{15,7,3,6,9,5,3,1,0}};
	for(int i = 0;i < 9;i++){
		for(int j = 0;j < 9;j++){
			W[i][j] = a[i][j];
		}
	}
	TSP(W);
	return 0;
}
