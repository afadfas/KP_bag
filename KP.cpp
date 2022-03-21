#include <time.h>  
#include <windows.h>
#include <stdio.h>   
#include <iostream>
#include<cstdio>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<fstream>


#define MAX(a,b) a < b ? b : a
#define N 100
using namespace std;

struct goods{
int sign;//��Ʒ���
int wight;//��Ʒ����
int value;//��Ʒ��ֵ
};

int n,bestValue,cv,cw,C;//��Ʒ��������ֵ��󣬵�ǰ��ֵ����ǰ��������������
int X[N],cx[N];//���մ洢״̬����ǰ�洢״̬
struct goods goods[N];


//��̬�滮�� 
int KnapSack2(int n,struct goods a[],int C,int x[]){
    int V[N][10*N];
    for(int i = 0; i <= n; i++)//��ʼ����0��
        V[i][0] = 0;
    for(int j = 0; j <= C; j++)//��ʼ����0��
        V[0][j] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= C; j++)
        if(j < a[i-1].wight)
            V[i][j] = V[i-1][j];
        else
            V[i][j] = MAX(V[i-1][j],V[i-1][j-a[i-1].wight] + a[i-1].value);

    for(int i = n,j = C; i > 0; i--){
        if(V[i][j] > V[i-1][j]){
            x[i-1] = 1;
            j = j - a[i-1].wight;
        }
        else
            x[i-1] = 0;
    }
    return V[n][C];
}
//̰���㷨

int KnapSack1(int i){
	if(i>n-1){
	    if(bestValue < cv && cw + goods[i].wight <= C){
	        for(int k=0;k<n;k++)
	            X[k] = cx[k];//�洢����·��
	        bestValue = cv;
	    }
	    return bestValue;
	}
	cw = cw + goods[i].wight;
	cv = cv + goods[i].value;
	cx[i] = 1;//װ�뱳��
	KnapSack1(i+1);
	cw = cw-goods[i].wight;
	cv = cv-goods[i].value;
	cx[i] = 0;//��װ�뱳��
	KnapSack1(i+1);
	return bestValue;
} 


//���ݷ�
int BackTrack(int i){
    if(i > n-1){
        if(bestValue < cv){
            for(int k = 0; k < n; k++)
                X[k] = cx[k];//�洢����·��
            bestValue = cv;
        }
        return bestValue;
    }
    if(cw + goods[i].wight <= C){//����������
        cw += goods[i].wight;
        cv += goods[i].value;
        cx[i] = 1;//װ�뱳��
        BackTrack(i+1);
        cw -= goods[i].wight;
        cv -= goods[i].value;//���ݣ�����������
    }
    cx[i] = 0;//��װ�뱳��
    BackTrack(i+1);
    return bestValue;
}

bool m(struct goods a, struct goods b){
    return (a.value/a.wight) > (b.value/b.wight);
}

int KnapSack3(int n, struct goods a[], int C,int x[N]){
    memset(x,0,sizeof(x));
    sort(a,a+n,m);//������Ʒ����λ������ֵ��������
    BackTrack(0);
    return bestValue;
} 

//������ 
int main()
{	
	FILE *fp;
    char filename[30],x[31];
    cout<<"������Ҫ�������ݵ��ļ���������׺��:\n";
    gets(filename);
    if((fp=fopen(filename,"r+"))==NULL){
        printf("ERROR!\n");
        exit(0);
    }
	fscanf(fp,"%d %d", &C, &n);
	printf("��������Ϊ: %d����Ʒ����Ϊ: %d\n", C, n);
	for(int i = 0; i < n; i++)
    {
		fscanf(fp, "%d %d",&goods[i].wight,&goods[i].value);
        printf("%d %d\n", goods[i].wight,goods[i].value); 
    }
    //���
	ofstream outfile;
	outfile.open("out\result.txt");

    
    //ѡ���㷨 
    int sum1 = KnapSack1(0); 			//̰���㷨 
    int sum2 = KnapSack2(n,goods,C,X);  //��̬�滮��
    int sum3 = KnapSack3(n,goods,C,X);  //���ݷ� 
	 
   	//ʱ��
	time_t start ,end ;  
    double cost;  
 
 	while(1){
 		int x;
 		cout<<"\n\n------------------------------------\n��ѡ���㷨: \n\n"; 
	    printf("1. ��̬�滮��\n2. ̰���㷨\n3. ���ݷ�\n");
	    scanf("%d",&x);
		
	    
		switch(x){
			case 1:
				time(&start);  

				printf("��̬�滮�����0/1�������⣺\nX=[");
				for(int i = 0; i < n; i++)
	        		cout<<X[i]<<" ";//�������X[n]����
	    		printf("]   װ���ܼ�ֵ%d\n", sum2);
	    		time(&end);  
    			cost=difftime(end,start);
				printf("%f\n",cost);    
				outfile<<sum2<<"  ����ʱ�䣺 "<<cost<<endl;
				outfile.close();
	    		break;
	    	case 2:
	    		time(&start);  
	    		printf("̰�ķ����0/1�������⣺\nX=[");
			    for(int i=0;i<n;i++){
			        cout << X[i]<<" ";
			        }
			    printf("] װ���ܼ�ֵ%d\n",sum1);
			    time(&end);  
    			cost=difftime(end,start); 
				printf("%f\n",cost);   
				outfile<<sum2<<"  ����ʱ�䣺 "<<cost<<endl;
				outfile.close();
			    break;
	    	case 3:
	    		time(&start);  
				printf("���ݷ����0/1��������:\nX=[");
	    		for(int i = 0; i < n; i++)
	        		cout << X[i] <<" ";//�������X[n]����
	    		printf("]   װ���ܼ�ֵ%d\n",sum3);
	    		time(&end);  
    			cost=difftime(end,start);
				printf("%f\n",cost);   
				outfile<<sum2<<"  ����ʱ�䣺 "<<cost<<endl;
				outfile.close(); 
				break; 
		}
		
	 } 
    return 0;
}
