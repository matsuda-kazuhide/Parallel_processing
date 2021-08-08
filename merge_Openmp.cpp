#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;


void merge(double arr[], int l, int m, int r) {
    int i, j, k;

    int n1 = m - l + 1;  
    int n2 = r - m;      

    
    int L[n1]; 
    int R[n2]; 

   
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    
    i = 0;    
    j = 0;    
    k = l;    
   
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
     
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(double array[], int l, int r) {

    if (l < r) {
        
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(array, l, m);
            #pragma omp section
            mergeSort(array, m + 1, r);
        }
        merge(array, l, m, r);
    }

}


int main (void) {
    ifstream ifs;  
	ifs.open("rand_10,000.csv");	// ファイルオープン 開くファイルを変更する場合はここを変える。

    if(ifs.fail()){	// ファイルオープンに失敗したらそこで終了
		cerr << "ファイルを開けません\n";
		exit(1);
	}

    char buf[256];	// データ一時保管用配列

	int linenum = 0; // データの行数を数える

	while(ifs.getline(buf,sizeof(buf))){	// ファイルから1行ずつ読み込む
		linenum++;	// 行数をカウントしている
	}

	cerr << "読み込んだ行数 = " << linenum << "\n";

	ifs.clear(); // 末尾に到達したフラグクリア
	ifs.seekg(0, ios::beg);	// ファイル先頭に戻る

	double *array;
	array = new double[linenum];	// 配列確保


    string line;
    int j=0;
    char *find;
    while (getline(ifs,line)){
        try{
            array[j] = stod(line);
            j++;
        }
        catch(const std::invalid_argument& e){
            cout << "invalid argument" << endl;
        }
        catch(const std::out_of_range& e){
            cout << "Out of range" <<endl;
        }
    }
    
    int i;
    //double array[20] = {3, 6, 1, 7, 2, 0, 4, 5, 9, 8, 30, 60, 10, 70, 20, 0, 40, 50, 90, 80};
    
    printf("       array: ");
    for (i = 0; i < linenum; i++) {
        printf("%.f ", array[i]);
    }
    printf("\n");
    clock_t t1, t2;

    t1 = clock();
    mergeSort(array, 0, linenum - 1);
    t2 = clock();

    double t_time = (double)(t2 - t1)/CLOCKS_PER_SEC;
    printf("Time Elapsed: %.5f\n",t_time);

    return 0;
}