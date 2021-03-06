#include<iostream>
#include<cmath>
using namespace std;

//Global variables
int n, m, c;

/*Main Arrays
 Nmap: (2D)儲存物流中心的資訊
 Mmap: (2D)儲存零售店資訊
 NetRevenue: (2D)儲存各物流中新對各零售店的補貨效益，公式：demand*(p-dist*c)
 Output: (2D)記錄輸出格式所要求的補貨情形
*/

//Declaration of functions
void Rev(int, int, int**, int**, double**); //計算Net Revenue
void RevII(int, int, int**, int**, double**); //榨乾用，多了考慮不完全補貨的機制
double avg(double**); //計算平均數
double sd(double, double**); //計算標準差
void swap(int* &a, int* &b);

int main() {
	cin >> n >> m >> c; //n是物流中心數，m是零售店數，c是每公里單位貨物補貨成本

	int**Nmap = new int*[n]; //Nmap用來儲存物流中心資訊
	for (int a = 0; a < n; a++) {
		Nmap[a] = new int[4];
	}

	for (int b = 0; b < n; b++) { // [0]x坐標、[1]y坐標、[2]建造成本、[3]存貨量
		int Xn, Yn;
		cin >> Xn >> Yn;
		Nmap[b][0] = Xn;
		Nmap[b][1] = Yn;
	}

	int**Mmap = new int*[m]; //Mmap用來儲存零售中心資訊
	for (int o = 0; o < m; o++) {
		Mmap[o] = new int[5];
	}

	for (int d = 0; d < m; d++) { // [0]x坐標、[1]y坐標、[2]需求量、[3]建造成本、[4]單位售價
		int Xm, Ym;
		cin >> Xm >> Ym;
		Mmap[d][0] = Xm;
		Mmap[d][1] = Ym;
	}

	for (int e = 0; e < m; e++) { // [2]需求量
		int D;
		cin >> D;
		Mmap[e][2] = D;
	}

	for (int f = 0; f < m; f++) { // [3]建造成本
		int C;
		cin >> C;
		Mmap[f][3] = C;
	}

	for (int g = 0; g < m; g++) { // [4]該店售價
		int P;
		cin >> P;
		Mmap[g][4] = P;
	}

	for (int i = 0; i < n; i++) { // [2]建造成本
		int Cn;
		cin >> Cn;
		Nmap[i][2] = Cn;
	}

	for (int j = 0; j < n; j++) { // [3] 存貨量
		int I;
		cin >> I;
		Nmap[j][3] = I;
	}

////////////////////////////////////輸入結束////////////////////////////////////////////

	double**NetRevenue = new double*[m]; //用來計算各物流中心對各零售店的補貨效益(假設所有需求皆被滿足)
	for (int h = 0; h < m; h++) {
		NetRevenue[h] = new double[n];
	}

	for (int k = 0; k < n; k++) {
		for (int l = 0; l < m; l++) {
			Rev(k, l, Nmap, Mmap, NetRevenue);
		}
	}

	///////////////////Step2:計算平均以及標準差//////////////////
	//請使用NetRevenue陣列中的數字進行平均數以及標準差的計算
	double average, standard_div;

	int**Output = new int*[m]; //輸出用
	for (int x = 0; x < m; x++) {
		Output[x] = new int[n];
	}

	for (int zz = 0; zz < m; zz++) { //初始化全為零
		for (int yy = 0; yy < n; yy++) {
			Output[zz][yy] = 0;
		}
	}

	//////////////////Step3:設定閥值開始檢驗///////////////////
	//3-1:將NetRevenue排序。不知道你們要不要再開個新陣列，就由負責3的兩個人協調
	/*3-2:以if條件由上而下檢驗是否符合閥值需求，若符合且存貨量>需求量且需求量不為零即進行補貨
	      補貨後將Nmap、Mmap中的數值做減少。並同時將補貨紀錄在Output陣列中。 */

	double Threshold; //閥值(前面定義)
	//Threshold= average -0.56* standard_div;
	int* OutputN = new int[n];
	int* OutputM = new int[m];
	for (int i = 0; i < n; i++)
		OutputN[i] = 0;
	for (int i = 0; i < m; i++)
		OutputM[i] = 0;
	int Ncount = 0, Mcount = 0; //物流中心、零售店設置數量

	bool flag = true;

	for (int jjj = 0; jjj <= 521; jjj++) { //連結到264行，做若干次逼近

		if (jjj % 12 == 0) {
			average = avg(NetRevenue);
			standard_div = sd(average, NetRevenue);
		}

		double coefficient, kkk;
		if (jjj == 0)
			kkk = 0.1;
		else if (jjj == 21)
			kkk = 0.12;
		else if (jjj == 51)
			kkk = 0.15;
		else if (jjj == 81)
			kkk = 0.17;
		else if (jjj == 121)
			kkk = 0.19;
		else if (jjj == 181)
			kkk = 0.22;
		else if (jjj == 221)
			kkk = 0.27;
		else if (jjj == 361)
			kkk = 0.34;

		coefficient = 2.7 - (kkk * (jjj % 12));
		Threshold = average + coefficient * standard_div * 1.1;
		if (jjj == 521)
			Threshold = 0;

		for (int z = 0; z < n; z++) {
			/*每跑一次迴圈，找出一個能創造最大利潤的物流中心，
			補完後重新計算NetRevenue，再找下一個物流中心，
			一直找直到沒有能創造出正的利益的物流中心為止。*/

			/*double** NetRevenue = new double* [m]; //用來計算各物流中心對各零售店的補貨效益(假設所有需求皆被滿足)
			for (int h = 0; h < m; h++){
			    NetRevenue[h] = new double[n];
			}*/

			for (int k = 0; k < n; k++) {
				for (int l = 0; l < m; l++) {
					Rev(k, l, Nmap, Mmap, NetRevenue);
				}
			}

			int* NOrder = new int[m]; //用來幫物流中心對每家零售店所能創造的利益作排序
			for (int i = 0; i < m; i++) {
				NOrder[i] = i;
			}

			double* N_revenue = new double[n]; //記錄每一個物流中心能創造的利潤
			double maxN_revenue = 0;  //能創造的最大利潤
			int* max_NOrder = new int[m]; //能創造最大利潤的物流中心的補貨清單
			int maxN = -1; //能創造最大利潤的物流中心

			for (int i = 0; i < n; i++) {
				if (OutputN[i] == 1)
					continue;

				for (int j = 0; j < m; j++) { //N排序用
					for (int k = 0; k < j; k++) {
						if (NetRevenue[NOrder[j - k]][i] > NetRevenue[NOrder[j - k - 1]][i]) {
							swap(NOrder[j - k], NOrder[j - k - 1]);
						}
						else
							break;
					}
				}

				int inventory = Nmap[i][3];
				int stopM = -1;
				for (int j = 0; j < m; j++) { //計算該物流中心能創造的利潤

					if (abs(NetRevenue[NOrder[j]][i]) >= Threshold && inventory - Mmap[NOrder[j]][2] >= 0) {
						N_revenue[i] += NetRevenue[NOrder[j]][i];
						inventory -= Mmap[NOrder[j]][2];
						if (j == m - 1)
							stopM = m;
					}
					else {
						stopM = j;
						break;
					}
				}

				N_revenue[i] -= Nmap[i][2]; //利潤要扣掉物流中心的建設成本

				if (N_revenue[i] > maxN_revenue) {
					maxN = i;
					for (int l = 0; l < m; l++) {

						if (l < stopM)
							max_NOrder[l] = NOrder[l];
						else
							max_NOrder[l] = -1;
					}
					maxN_revenue = N_revenue[i];
				}
			}
			//完成此迴圈後將找到一個能創造最大利益的物流中心

			//如果沒能找到能創造出正的利益的物流中心，則演算法結束
			if (maxN != -1) { //該物流中心進行補貨
				OutputN[maxN] = 1;
				for (int i = 0; i < m; i++) {

					if (max_NOrder[i] != -1) {
						OutputM[max_NOrder[i]] = 1;
						Output[max_NOrder[i]][maxN] += Mmap[max_NOrder[i]][2];
						Nmap[maxN][3] -= Mmap[max_NOrder[i]][2]; //存貨量 - 需求量
						Mmap[max_NOrder[i]][2] = 0;
					}
				}
			}
			else {
				break;
			}
		}

		if (jjj % 6 == 0) {
			//開始榨乾物流中心
			for (int z = 0; z < n; z++) { //跑好跑滿，這裡的z沒有實質意義

				for (int k = 0; k < n; k++) {
					for (int l = 0; l < m; l++) {
						RevII(k, l, Nmap, Mmap, NetRevenue);
					}
				}

				int MAXX = 0, MAXX_N = -1, MAXX_M = -1;

				for (int kk = 0; kk < n; kk++) {
					if (OutputN[kk] != 1)
						continue;

					if (Nmap[kk][3] == 0)
						continue;

					for (int i = 0; i < m; i++) { //榨乾它
						if (NetRevenue[i][kk] > MAXX) {
							MAXX = NetRevenue[i][kk];
							MAXX_N = kk;
							MAXX_M = i;
						}
					}
				}

				if (MAXX_N == -1)
					break;

				else {
					int quant; //確認補貨量
					if (Mmap[MAXX_M][2] < Nmap[MAXX_N][3])
						quant = Mmap[MAXX_M][2];
					else
						quant = Nmap[MAXX_N][3];

					OutputM[MAXX_M] = 1;
					Output[MAXX_M][MAXX_N] += quant;
					Nmap[MAXX_N][3] -= quant; //存貨量 - 需求量
					Mmap[MAXX_M][2] -= quant;
				}

			}
		}
	} //連結到126行，做若干次逼近


	/*輸出開始*/
	int output_N = 0, output_M = 0;
	for (int i = 0; i < n; i++) {
		if (OutputN[i] != 0)
			Ncount ++;
	}
	for (int i = 0; i < m; i++) {
		if (OutputM[i] != 0)
			Mcount ++;
	}
	cout << Ncount << " ";
	for (int i = 0; i < n; i++) {
		if (OutputN[i] == 1) {
			cout << i + 1;
			output_N ++;
			if (output_N != Ncount)
				cout << " ";
		}
	}
	cout << endl << Mcount << " ";
	for (int i = 0; i < m; i++) {
		if (OutputM[i] == 1) {
			cout << i + 1;
			output_M ++;
			if (output_M != Mcount)
				cout << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << Output[i][j];
			if (j != n - 1)
				cout << " ";
		}
		if (i != m - 1)
			cout << endl;
	}
	//3-3:若遇小於設定之閥值，則break，結束計算
	//(3-4): 早上雖然沒有特別討論，但3-3也許可以繼續向下檢驗，將一些漏網之魚做處理，或是第一次交就先算了後面慢慢弄

	return 0;
}

void Rev(int k, int l, int**Nmap, int**Mmap, double**NetRevenue) {
	int dist;
	dist = abs(Nmap[k][0] - Mmap[l][0]) + abs(Nmap[k][1] - Mmap[l][1]);
	int revenue;
	revenue = Mmap[l][2] * (Mmap[l][4] - (dist * c)) - Mmap[l][3];
	NetRevenue[l][k] = revenue;
}

void RevII(int k, int l, int**Nmap, int**Mmap, double**NetRevenue) {
	int dist;
	dist = abs(Nmap[k][0] - Mmap[l][0]) + abs(Nmap[k][1] - Mmap[l][1]);
	int revenue;

	if (Mmap[l][2] < Nmap[k][3])
		revenue = Mmap[l][2] * (Mmap[l][4] - (dist * c)) - Mmap[l][3];
	else
		revenue = Nmap[k][3] * (Mmap[l][4] - (dist * c)) - Mmap[l][3];

	NetRevenue[l][k] = revenue;
}

void swap(int* &a, int* &b) {

	int* temp = a;
	a = b;
	b = temp;
}

double avg(double**R) {
	double sum = 0;
	double len = n * m;
	for (int a = 0; a < m; a++) {
		for (int b = 0; b < n; b++) {
			sum += R[a][b];
		}
	}
	return sum / len;
}

double sd(double AA, double**RR) {
	double sum = 0, len = n * m;
	for (int a = 0; a < m; a++) {
		for (int b = 0; b < n; b++) {
			double div;
			div = (RR[a][b] - AA) * (RR[a][b] - AA);
			sum += div;
		}
	}
	return sqrt(sum / len);
}


/*可以用來湊數字的地方有
1. 128~131行
可以改變coefficient的變率
我自己的感覺是越細碎越好
然後jjj的最大值也可以改變
jjj大約到300以上就有機率TLE 400以上超高機率TLE 不過還是可以都嘗試看看

2. 226行
可以決定每幾組進行榨乾一次
我自己的實驗是不要每個榨也不要都不榨
大約設在4~10之間就好
目前有逼出比較高數字的都是5~7*/
