# 第十章 泛型算法

### 10.1

+ 泛型算法本身不会执行容器的操作，它们只会运行于迭代器之上，执行迭代器的操作。


### 10.2

+ 那些只接受一个单一迭代器来表示第二个序列的算法，都假定第二个序列至少与第一个序列一样长。

+ 向目的位置迭代器写入数据的算法假定目的的位置足够大，能够容纳写入的元素。
```c++
vector<int> vec;
fill_n(vec.begin(), 10, 0); // 未定义行为
```

+ 插入迭代器(insert iterator)是一种向容器中添加元素的迭代器。定义在头文件**iterator**中的**back_inserter**接收一个指向容器的引用，返回一个与该容器绑定的插入迭代器。
```c++
vector<int> vec;
fill_n(back_inserter(vec), 10, 0);
```

+ 标准库算法对迭代器而不是容器进行操作。因此，算法不能(直接)添加或删除元素。


### 10.3

+ 谓词是一个可调用的表达式，其返回结果是一个能用作条件的值。标准库算法所使用的谓词分为两类：一元谓词，二元谓词。接收谓词参数的算法对输入序列中的元素调用谓词，所以，元素类型必须能转换为谓词的参数类型。

+ **lambda**表达式的形式如下,其中可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体。
```
[capture](parameter list) -> return type { function body }
```

+ **如果lambda的函数体包含任何单一return语句之外的内容，且未指定返回类型，则返回void？？？**

+ 捕获列表只用于局部**非static**变量，lambda可以直接使用局部static变量和它所在函数之外声明的名字。

+ 当定义一个lambda时，编译器生成一个与lambda对应的新的(未命名的)类类型。默认情况下，从lambda生成的类都包含一个对应该lambda所捕获的变量的数据成员，lambda的数据成员在lambda对象创建是初始化。

+ 在lambda表达式中，被捕获的变量的值是在lambda创建是拷贝，而不是调用时拷贝。

+ lambda表达式的引用捕获与返回引用有着相同的问题和限制，如果采用引用的方式捕获一个变量，就必须确保被引用的对象在lambda表达式执行的时候是存在的。

+ 混合使用隐式捕获和显式捕获的时候，捕获列表中的第一个元素必须是`&或者=`。


+ 如果希望改变值捕获的变量的值，就必须在参数列表首加上关键字**mutable**。
```c++
int a = 0;
auto f = [a] ()mutable {a++; return a;};
```
+ 在c++11中，可以使用定义在functional中的标准库bind函数，它接受一个可调用对象，生成一个新的可调用对象来"适应"原对象的参数列表。其中arg_lst用**`_n`**的形式表示占位符。
```c++
auto newCallable = bind(callable, arg_lst);
```
+ **bind函数的占位符`_n`是定义在std::placeholders这个命名空间中**
```c++
auto newCallable = bind(callable, std::placeholders::_1, arg);
```

+ 可以利用bind函数修正参数的值，也可以修正参数的顺序。
```c++
auto g = bind(f, a, b, _2, c, _1)
```

+ bind的不是占位符的参数默认被拷贝到bind返回的可调用对象中，如果需要传递引用的话需要使用`ref或者cref函数`
```c++
for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' ');
```

+ 函数ref返回的是一个对象，包含给定的引用，此对象是可拷贝的。对应的有cref函数，返回一个包含const引用的对象。

### 10.4

+ 对于插入迭代器it，`*it, ++it, it++`都不会对it做任何事情，每个操作都放回it。

+ 当调用front_inserter(c)的时候会调用c.push_front。
```
list<int> lst = {1, 2, 3, 4};
list<int> lst2, list3;
copy(list.cbegin(), list.cend(), front_inserter(list2)); // list is {4, 3, 2, 1};
copy(list.cbegin(), list.cend(), inserter(lst3, lst3.begin()); // list is {1, 2, 3, 4};
```

+ 空的**istream_iterator**可以当成尾后迭代器来使用，也就是**EOF**,下面代码可以从输入流中读入一串数字并保存在vector中。
```c++
istream_iterator<int> in_iter(cin), eof;
vector<int> vec(in_iter, eof);
```

+ 对于输入流迭代器，通过==/!=判定两个读取相同的类型的流迭代器是否绑定在同一个流中或者都是尾后迭代器。通过`*it`返回流中读取的数据，`it->mem`等同于`(*it).mem`，`++it, it++`使用元素类型所定义的>>运算符从输入流中读取下一个值，与往常一样，前置版本返回一个指向递增后迭代器的引用，后置则返回旧值。
```c++
istream_iterator<int> in(cin), eof;
cout << accumulate(in, eof, 0) << endl; //快速计算读入一串数字的和。
```
