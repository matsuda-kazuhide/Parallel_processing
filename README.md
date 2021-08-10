# Parallel_processing
C++によるソーティングの並列分散処理

## ファイルの説明<br>
merge.cpp：通常のマージソートを行うコード<br>
merge_Openmp.cpp：並列処理を行うマージソートのコード<br>
OddEven.cpp：通常の奇遇転置ソートを行うコード<br>
P-OddEven.cpp：並列処理を行う奇遇転置ソートのコード<br>
rand.py：数列を作成したpythonのコード<br>
rand_10,000.csv：rand.pyで作成した、数列の長さが10,000のファイル<br>
rand_50,000.csv：rand.pyで作成した、数列の長さが50,000のファイル<br>
rand_1,000,000csv：rand.pyで作成した、数列の長さが1,000,000のファイル<br>

## 実行環境<br>
python3.7<br>
OpenMPを使用。<br>
brew install libomp<br>
brewを入れてない方は先にbrewをインストールしてください。

プロセッサ2.3 GHz デュアルコアIntel Core i5<br>
4スレッド<br>
メモリ8GB

### コンパイラ<br>
gcc version 11

並列処理を行うには-fopenmpのオプションをつける必要がある。<br>
また、実行前にいくつのスレッドを使うか指定する必要がある。
#### 実行例<br>
export OMP_NUM_THREADS=4<br>
g++-11 merge_Openmp.cpp -fopenmp<br> 
./a.out<br>



