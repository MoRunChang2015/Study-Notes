### 希尔排序

#### 基本思想
1. 选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1；
2. 按增量序列个数k，对序列进行k 趟排序；
3. 每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m 的子序列，分别对各子表进行直接插入排序。仅增量因子为1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。

![example](https://github.com/MoRunChang2015/Study-Notes/blob/master/algorithm%20and%20data%20structures/sort/Shell%20Sort/shell_sort.jpg)

+ 希尔排序**不稳定**，希尔排序的复杂度主要取决于选取的序列，在小数组中希尔排序可以比快速排序和堆排序还快。

+ 已知最好的长序列是由Sedgewick提出的(1,5,19,41,109...)。


