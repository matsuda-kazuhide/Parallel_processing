//通常の奇遇転置ソート

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <string>
#include <cstring>


using namespace std;


//ソートを行う関数
void OddEven(double nums[], int n){
    bool issoted = false;
    while( !issoted ){
        issoted=true;
        int i;
        for(i=0; i<n-1; i+=2){
            if(nums[i] > nums[i+1]){
                swap(nums[i],nums[i+1]);
                issoted = false;
          }
        }
        for(i=1; i<n-1; i+=2){
            if(nums[i] > nums[i+1]){
                swap(nums[i],nums[i+1]);
                issoted = false;
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

    std::cout << "Given array is: ";
    /*
    for(int i=0; i<linenum; i++)
        cout << array[i] << " ";
    cout << endl;
    */
    clock_t t1, t2;

    t1 = clock();
    OddEven(array, linenum);
    t2 = clock();

    std::cout << "\nSorted array is: ";
    for(int i=0; i<linenum; i++)
        cout << array[i] << " ";
    cout << endl;

    double t_time = (double)(t2 - t1)/CLOCKS_PER_SEC;
    printf("Time Elapsed: %.5f\n",t_time);

    return 0;
}
