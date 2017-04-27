#include<iostream>
#include<cmath>
using namespace std; 

//Global variables
int n,m,c;

/*Main Arrays
 Nmap: (2D)儲存物流中心的資訊
 Mmap: (2D)儲存零售店資訊
 NetRevenue: (2D)儲存各物流中新對各零售店的補貨效益，公式：demand*(p-dist*c) 
 Output: (2D)記錄輸出格式所要求的補貨情形 
*/
 
//Declaration of functions
void Rev(int,int,int**,int**,double**); //計算Net Revenue 
//double avg(double**); //計算平均數 
//double sd(double,double**); //計算標準差 

int main(){
	cin>>n>>m>>c; //n是物流中心數，m是零售店數，c是每公里單位貨物補貨成本
	
	int**Nmap=new int*[n]; //Nmap用來儲存物流中心資訊 
	for(int a=0;a<n;a++){
		Nmap[a]=new int[4]; 
	} 
	
	for(int b=0;b<n;b++){ // [0]x坐標、[1]y坐標、[2]建造成本、[3]存貨量 
		int Xn,Yn;
		cin>>Xn>>Yn;
		Nmap[b][0]=Xn;
		Nmap[b][1]=Yn;
	}
	
	int**Mmap=new int*[m]; //Mmap用來儲存零售中心資訊
	for(int o=0;o<m;o++){
		Mmap[o]=new int[5];
	} 
	
	for(int d=0;d<m;d++){ // [0]x坐標、[1]y坐標、[2]需求量、[3]建造成本、[4]單位售價 
		int Xm,Ym;
		cin>>Xm>>Ym;
		Mmap[d][0]=Xm;
		Mmap[d][1]=Ym;
	}
	
	for(int e=0;e<m;e++){ // [2]需求量 
		int D;
		cin>>D;
		Mmap[e][2]=D;
	}
	
	for(int f=0;f<m;f++){ // [3]建造成本 
		int C;
		cin>>C;
		Mmap[f][3]=C;
	}
	
	for(int g=0;g<m;g++){ // [4]該店售價 
		int P;
		cin>>P;
		Mmap[g][4]=P;
	}
	
	for(int i=0;i<n;i++){ // [2]建造成本 
		int Cn;
		cin>>Cn;
		Nmap[i][2]=Cn;
	}
	
	for(int j=0;j<n;j++){ // [3] 存貨量 
		int I;
		cin>>I;
		Nmap[j][3]=I;
	}
	
////////////////////////////////////輸入結束//////////////////////////////////////////// 
	
	double**NetRevenue=new double*[m]; //用來計算各物流中心對各零售店的補貨效益(假設所有需求皆被滿足) 
	for(int h=0;h<m;h++){
		NetRevenue[h]=new double[n];
	} 
	
	for(int k=0;k<n;k++){
		for(int l=0;l<m;l++){
			Rev(k,l,Nmap,Mmap,NetRevenue);
		}
	}
	
	///////////////////Step2:計算平均以及標準差//////////////////
	/*請使用NetRevenue陣列中的數字進行平均數以及標準差的計算 
	double average = avg(NetRevenue);
	double standard_div = sd(average,NetRevenue);
	*/ 
	
	int**Output=new int*[m]; //輸出用 
	for(int x=0;x<m;x++){
		Output[x]=new int[n];
	}
	
	for(int zz=0;zz<m;zz++){ //初始化全為零 
		for(int yy=0;yy<n;yy++){
			Output[zz][yy]=0;
		}
	}
	
	//////////////////Step3:設定閥值開始檢驗///////////////////
	//3-1:將NetRevenue排序。不知道你們要不要再開個新陣列，就由負責3的兩個人協調
	/*3-2:以if條件由上而下檢驗是否符合閥值需求，若符合且存貨量>需求量且需求量不為零即進行補貨 
	      補貨後將Nmap、Mmap中的數值做減少。並同時將補貨紀錄在Output陣列中。 */ 
	//3-3:若遇小於設定之閥值，則break，結束計算
	//(3-4): 早上雖然沒有特別討論，但3-3也許可以繼續向下檢驗，將一些漏網之魚做處理，或是第一次交就先算了後面慢慢弄
	 
	for(int z=0;z<m;z++){
		for(int y=0;y<n-1;y++){
			cout<<Output[z][y]<<" ";
		}
		cout<<Output[z][n-1]<<endl;
	}
	
	return 0;
}

void Rev(int k,int l,int**Nmap,int**Mmap,double**NetRevenue){
	int dist;
	dist=abs(Nmap[k][0]-Mmap[l][0])+abs(Nmap[k][1]-Mmap[l][1]);
	int revenue;
	revenue=Mmap[l][2]*(Mmap[l][4]-(dist*c))-Mmap[l][3];
	NetRevenue[l][k]=revenue;
}
