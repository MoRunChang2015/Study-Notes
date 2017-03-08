### 快速排序

#### 基本思想

1. 选择一个基准元素,可以选择第一个元素或者最后一个元素。

2. 通过一趟排序讲待排序的记录分割成独立的两部分，其中一部分记录的元素值均比基准元素值小。另一部分记录的 元素值比基准值大。

3. 此时基准元素在其排好序后的正确位置

4. 然后分别对这两部分记录用同样的方法继续进行排序，直到整个序列有序。


![example](https://github.com/MoRunChang2015/Study-Notes/blob/master/algorithm%20and%20data%20structures/sort/Quick%20Sort/quick_sort.jpg)


+ 快速排序是**不稳定**的。


