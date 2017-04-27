#include<iostream>
#include<cmath>
using namespace std; 

//Global variables
int n,m,c;

/*Main Arrays
 Nmap: (2D)�x�s���y���ߪ���T
 Mmap: (2D)�x�s�s�⩱��T
 NetRevenue: (2D)�x�s�U���y���s��U�s�⩱���ɳf�įq�A�����Gdemand*(p-dist*c) 
 Output: (2D)�O����X�榡�ҭn�D���ɳf���� 
*/
 
//Declaration of functions
void Rev(int,int,int**,int**,double**); //�p��Net Revenue 
//double avg(double**); //�p�⥭���� 
//double sd(double,double**); //�p��зǮt 

int main(){
	cin>>n>>m>>c; //n�O���y���߼ơAm�O�s�⩱�ơAc�O�C�������f���ɳf����
	
	int**Nmap=new int*[n]; //Nmap�Ψ��x�s���y���߸�T 
	for(int a=0;a<n;a++){
		Nmap[a]=new int[4]; 
	} 
	
	for(int b=0;b<n;b++){ // [0]x���СB[1]y���СB[2]�سy�����B[3]�s�f�q 
		int Xn,Yn;
		cin>>Xn>>Yn;
		Nmap[b][0]=Xn;
		Nmap[b][1]=Yn;
	}
	
	int**Mmap=new int*[m]; //Mmap�Ψ��x�s�s�⤤�߸�T
	for(int o=0;o<m;o++){
		Mmap[o]=new int[5];
	} 
	
	for(int d=0;d<m;d++){ // [0]x���СB[1]y���СB[2]�ݨD�q�B[3]�سy�����B[4]����� 
		int Xm,Ym;
		cin>>Xm>>Ym;
		Mmap[d][0]=Xm;
		Mmap[d][1]=Ym;
	}
	
	for(int e=0;e<m;e++){ // [2]�ݨD�q 
		int D;
		cin>>D;
		Mmap[e][2]=D;
	}
	
	for(int f=0;f<m;f++){ // [3]�سy���� 
		int C;
		cin>>C;
		Mmap[f][3]=C;
	}
	
	for(int g=0;g<m;g++){ // [4]�ө���� 
		int P;
		cin>>P;
		Mmap[g][4]=P;
	}
	
	for(int i=0;i<n;i++){ // [2]�سy���� 
		int Cn;
		cin>>Cn;
		Nmap[i][2]=Cn;
	}
	
	for(int j=0;j<n;j++){ // [3] �s�f�q 
		int I;
		cin>>I;
		Nmap[j][3]=I;
	}
	
////////////////////////////////////��J����//////////////////////////////////////////// 
	
	double**NetRevenue=new double*[m]; //�Ψӭp��U���y���߹�U�s�⩱���ɳf�įq(���]�Ҧ��ݨD�ҳQ����) 
	for(int h=0;h<m;h++){
		NetRevenue[h]=new double[n];
	} 
	
	for(int k=0;k<n;k++){
		for(int l=0;l<m;l++){
			Rev(k,l,Nmap,Mmap,NetRevenue);
		}
	}
	
	///////////////////Step2:�p�⥭���H�μзǮt//////////////////
	/*�Шϥ�NetRevenue�}�C�����Ʀr�i�業���ƥH�μзǮt���p�� 
	double average = avg(NetRevenue);
	double standard_div = sd(average,NetRevenue);
	*/ 
	
	int**Output=new int*[m]; //��X�� 
	for(int x=0;x<m;x++){
		Output[x]=new int[n];
	}
	
	for(int zz=0;zz<m;zz++){ //��l�ƥ����s 
		for(int yy=0;yy<n;yy++){
			Output[zz][yy]=0;
		}
	}
	
	//////////////////Step3:�]�w�֭ȶ}�l����///////////////////
	//3-1:�NNetRevenue�ƧǡC�����D�A�̭n���n�A�}�ӷs�}�C�A�N�ѭt�d3����ӤH���
	/*3-2:�Hif����ѤW�ӤU����O�_�ŦX�֭ȻݨD�A�Y�ŦX�B�s�f�q>�ݨD�q�B�ݨD�q�����s�Y�i��ɳf 
	      �ɳf��NNmap�BMmap�����ƭȰ���֡C�æP�ɱN�ɳf�����bOutput�}�C���C */ 
	//3-3:�Y�J�p��]�w���֭ȡA�hbreak�A�����p��
	//(3-4): ���W���M�S���S�O�Q�סA��3-3�]�\�i�H�~��V�U����A�N�@�Ǻ|���������B�z�A�άO�Ĥ@����N����F�᭱�C�C��
	 
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
