### 归并排序

#### 基本思想

在待排序的序列中选择出最大(最小)的一个数字与**第一个**位置的数字交换；然后再从待排序的序列中选出最大(最小)的一个与**第二个**位置的数字交换，依次类推，直到**第n-1个**和**第n个**比较完。

![merge_sort.jpg](https://github.com/MoRunChang2015/Study-Notes/blob/master/algorithm%20and%20data%20structures/sort/Merge%20Sort/merge_sort.jpg)

+ 归并排序是**稳定的**。
