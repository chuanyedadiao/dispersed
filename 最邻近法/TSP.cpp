#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<vector>
using namespace std;

typedef struct{
	char str[0x1000];
	int total; 
}Turn;

int row;//�� 
int list;//�� 
int start;//��ʼ��
int CNT;//�������ߣ������˳�����count 
int s[0x100]={0};
int min_total=0x999;
char way[0x1000];
Turn Hamilton[0x1000];
int count=0;

int find_min(vector<vector<int>  > W,int i)
{
    int min;
    min=0x1000;
	int m=0;
	for(;m<list;m++)
	{
		if(s[m]==1||m==start) continue; 
		if(min>W[i][m]) min=W[i][m];
	}
	return min;
}

void Result(vector<vector<int>  > W,int now,int &result)
{
	int j;
	int min;//�ҵ���Сֵ 
	if(CNT==row)//�˳��������ܹ��ж��ٸ��㣬��������˳� 
	{
		result+=W[now][start];
		way[CNT]='a'+start;
		Hamilton[count].total=result;
		strcpy(Hamilton[count].str,way);
		if(min_total>result){
		    min_total=result;	
		} 
		result-=W[now][start];
		count++;
		return;
	}	
	min=find_min(W,now);//�ҵ���I��û�б�����������С�ĵ��Ȩֵ 
	for(j=0;j<list;j++)
	{
		if(j==now) continue;//����Ϊͬһ��ͬһ�� 
		if(W[now][j]==min&&s[j]!=1) {
			CNT++;//��������������++ 
			s[j]=1;//��ʾ�߹�������� 
			result+=W[now][j];//���ϸõ��Ȩֵ 
			way[CNT-1]='a'+j;//���ϸõ� 
		    Result(W,j,result);//�ٴε��� 
			s[j]=0;//�˳�ѭ���������´ε��� 
			CNT--;//--��ʾ���˳�����һ���� 
			result-=W[now][j];
		}
	}
}

void TSP(vector<vector<int>  > W)
{
	row=W.size();//�������� 
	list=W[0].size();//�������� 
	int k;//��ʾ���ĸ���Ϊ��� 
	int result=0;//��ʾһ��·�������ܹ��Ƕ���Ȩֵ 
	for(k=0;k<row;k++){
		CNT=1;//��ֵΪ1 
		start=k;//���Ϊk 
		s[k]=1;
		way[CNT-1]='a'+k;
		Result(W,k,result);//��ʼ���� 
		s[k]=0;
		result=0;
	}
	int i=0;
	for(;i<count;i++)
	{
		if(Hamilton[i].total==min_total){
			cout<<"��СȨֵΪ: "<<Hamilton[i].total<<"   "<<"���·����: "<<Hamilton[i].str<<endl;
		}
	}
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
