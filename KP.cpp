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
int sign;//物品序号
int wight;//物品重量
int value;//物品价值
};

int n,bestValue,cv,cw,C;//物品数量，价值最大，当前价值，当前重量，背包容量
int X[N],cx[N];//最终存储状态，当前存储状态
struct goods goods[N];


//动态规划法 
int KnapSack2(int n,struct goods a[],int C,int x[]){
    int V[N][10*N];
    for(int i = 0; i <= n; i++)//初始化第0列
        V[i][0] = 0;
    for(int j = 0; j <= C; j++)//初始化第0行
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
//贪心算法

int KnapSack1(int i){
	if(i>n-1){
	    if(bestValue < cv && cw + goods[i].wight <= C){
	        for(int k=0;k<n;k++)
	            X[k] = cx[k];//存储最优路径
	        bestValue = cv;
	    }
	    return bestValue;
	}
	cw = cw + goods[i].wight;
	cv = cv + goods[i].value;
	cx[i] = 1;//装入背包
	KnapSack1(i+1);
	cw = cw-goods[i].wight;
	cv = cv-goods[i].value;
	cx[i] = 0;//不装入背包
	KnapSack1(i+1);
	return bestValue;
} 


//回溯法
int BackTrack(int i){
    if(i > n-1){
        if(bestValue < cv){
            for(int k = 0; k < n; k++)
                X[k] = cx[k];//存储最优路径
            bestValue = cv;
        }
        return bestValue;
    }
    if(cw + goods[i].wight <= C){//进入左子树
        cw += goods[i].wight;
        cv += goods[i].value;
        cx[i] = 1;//装入背包
        BackTrack(i+1);
        cw -= goods[i].wight;
        cv -= goods[i].value;//回溯，进入右子树
    }
    cx[i] = 0;//不装入背包
    BackTrack(i+1);
    return bestValue;
}

bool m(struct goods a, struct goods b){
    return (a.value/a.wight) > (b.value/b.wight);
}

int KnapSack3(int n, struct goods a[], int C,int x[N]){
    memset(x,0,sizeof(x));
    sort(a,a+n,m);//将各物品按单位重量价值降序排列
    BackTrack(0);
    return bestValue;
} 

//主函数 
int main()
{	
	FILE *fp;
    char filename[30],x[31];
    cout<<"请输入要读出数据的文件名（带后缀）:\n";
    gets(filename);
    if((fp=fopen(filename,"r+"))==NULL){
        printf("ERROR!\n");
        exit(0);
    }
	fscanf(fp,"%d %d", &C, &n);
	printf("背包容量为: %d，物品个数为: %d\n", C, n);
	for(int i = 0; i < n; i++)
    {
		fscanf(fp, "%d %d",&goods[i].wight,&goods[i].value);
        printf("%d %d\n", goods[i].wight,goods[i].value); 
    }
    //输出
	ofstream outfile;
	outfile.open("out\result.txt");

    
    //选择算法 
    int sum1 = KnapSack1(0); 			//贪心算法 
    int sum2 = KnapSack2(n,goods,C,X);  //动态规划法
    int sum3 = KnapSack3(n,goods,C,X);  //回溯法 
	 
   	//时间
	time_t start ,end ;  
    double cost;  
 
 	while(1){
 		int x;
 		cout<<"\n\n------------------------------------\n请选择算法: \n\n"; 
	    printf("1. 动态规划法\n2. 贪心算法\n3. 回溯法\n");
	    scanf("%d",&x);
		
	    
		switch(x){
			case 1:
				time(&start);  

				printf("动态规划法求解0/1背包问题：\nX=[");
				for(int i = 0; i < n; i++)
	        		cout<<X[i]<<" ";//输出所求X[n]矩阵
	    		printf("]   装入总价值%d\n", sum2);
	    		time(&end);  
    			cost=difftime(end,start);
				printf("%f\n",cost);    
				outfile<<sum2<<"  运行时间： "<<cost<<endl;
				outfile.close();
	    		break;
	    	case 2:
	    		time(&start);  
	    		printf("贪心法求解0/1背包问题：\nX=[");
			    for(int i=0;i<n;i++){
			        cout << X[i]<<" ";
			        }
			    printf("] 装入总价值%d\n",sum1);
			    time(&end);  
    			cost=difftime(end,start); 
				printf("%f\n",cost);   
				outfile<<sum2<<"  运行时间： "<<cost<<endl;
				outfile.close();
			    break;
	    	case 3:
	    		time(&start);  
				printf("回溯法求解0/1背包问题:\nX=[");
	    		for(int i = 0; i < n; i++)
	        		cout << X[i] <<" ";//输出所求X[n]矩阵
	    		printf("]   装入总价值%d\n",sum3);
	    		time(&end);  
    			cost=difftime(end,start);
				printf("%f\n",cost);   
				outfile<<sum2<<"  运行时间： "<<cost<<endl;
				outfile.close(); 
				break; 
		}
		
	 } 
    return 0;
}
