# 第二章 字符串、向量和数组

### 3.1 

+ **头文件不应包含using声明**

### 3.2

+ String如果使用**等号(＝)**初始化则实际上执行的是**拷贝初始化**编译器把等号右侧的初始值拷贝到新创建的对象中去,否则使用的是**直接初始化**。

+ 使用**getline**函数读入时，行末的换行符没有存在返回的字符串中(被丢弃了)。

+ 如果一条表达式中已经有了size()函数就不要再使用int了，这样可以避免混用int和unsigned可能带来的问题。如[stringSizeAndInt.cpp](https://github.com/MoRunChang2015/Study-Notes/blob/master/C%2B%2B%20Primer/Chapter%203/code/3.2/stringSizeAndInt.cpp)

+ 当把string对象和字符字面值以及字符串字面值混在一条语句中使用的时候，必须确保每个加号运算符的两侧的运算对象至少有一个是string。

+ **为了与C兼容**,C++中字符串字面值并不是标准库类型string的对象。

### 3.3

+ vector在初始化过程中，如果用的是圆括号，可以说提供的值是用来构造vector对象的，如果用的是花括号，可以表述成我们想列表初始化该vector对象。**但是**如果初始化时使用了花括号但是提供的值又不能列表初始化，就要考虑用这样的值来构造vector对象了。
```c++
    vector<int> v1{10, 1};       //  v1有 2  个元素
    vector<int> v2(10, 1);       //  v2有 10 个元素
    
    vector<string> v3{"hi"};     //  v3有 1  个元素
    vector<string> v4{10, "hi"}; //  v4有 10 个元素
```

+ **范围for语句体内不应改变其遍历列表的大小**

### 3.4

+ **任何一种可能改变vector对象容量的操作，如push_back，都会使该vector对象的迭代器失效。**

### 3.5

+ 字符数组再初始化的时候可以使用字符串字面值初始化，当使用这种方式时，一定要注意字符串字面值的结尾处还有一个**空字符**,这个空字符也会拷贝到字符数组中去。

+ **c++11**，在**iterator**头文件下有**begin(..),end(...)**函数用于获取数组的首指针和尾指针。

+ **如果执行完c_str()函数后程序想一直都能使用其返回的数组，最好将数组重新拷贝一份。**

### 3.6

+ **要使用范围for语句处理多维数组，除了最内层的循环外，其他所有循环的控制变量都应该是引用类型**
```c++
    for (const auto &row : a)             // 正确
        for (auto col : row)
            cout << col << endl;
            
    for (auto row : a)                    // 编译出错，这里的row的类型是int*
     　for (auto col : row)
            cout << col << endl;
```

+ **注意**, `using int_array = int[4]` 等价于 `typedef int int_array[4]`
