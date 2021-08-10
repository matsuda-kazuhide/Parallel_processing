//openmpを使った奇遇転置ソート

#include <omp.h>
#include <iostream>
#include <fstream>//追加
#include <sstream>//追加
#include <string>//追加
#include <cstring>//追加
#include <stdio.h>//追加
#include <time.h>//追加
using namespace std;


//並列奇遇転置ソートを行う関数
void P_OddEven(double* a, int n, int threadNumber){
    int phase;
    int i;
    int tmp;
    #pragma omp parallel num_threads(thread_count) default(none) shared(a,n) private(i,tmp,phase)
        for(phase=0; phase<n; phase++){
            //Even phase
            if(phase%2==0){
                #pragma omp for
                    for (i=1; i<n; i+=2){
                        if(a[i-1]>a[i]){
                            tmp = a[i-1];
                            a[i-1] = a[i];
                            a[i] = tmp;
                        }
                    }
            }
            //Odd phase
            else{
                #pragma omp for
                    for (i=1; i<n-1; i+=2){
                        if(a[i]>a[i+1]){
                            tmp = a[i+1];
                            a[i+1] = a[i];
                            a[i] = tmp;
                        }
                    }
            }
        }
    }

int main(){
    ifstream ifs;  
    ifs.open("rand_50,000.csv");	// ファイルオープン 開くファイルを変更する場合はここを変える。

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
	array = new double[linenum];	// 行数 linenum 分の配列を動的に確保

    string line;
    int j=0;
    char *find;
    while (getline(ifs,line)){
        try{
            array[j] = stoi(line);
            j++;
        }
        catch(const std::invalid_argument& e){
            cout << "invalid argument" << endl;
        }
        catch(const std::out_of_range& e){
            cout << "Out of range" <<endl;
        }
    }
    
    int thread_num = 4;

    std::cout << "Given array is: ";
    /*
    for(int i=0; i<linenum; i++)
        cout << array[i] << " ";
    cout << endl;
    */
    clock_t t1, t2;

    t1 = clock();
    P_OddEven(array,linenum,thread_num);
    t2 = clock();

    std::cout << "\nSorted array is: ";
    for(int i=0; i<linenum; i++)
        cout << array[i] << " ";
    cout << endl;

    double t_time = (double)(t2 - t1)/CLOCKS_PER_SEC;
    printf("Time Elapsed: %.5f\n",t_time);

    return 0;
}
