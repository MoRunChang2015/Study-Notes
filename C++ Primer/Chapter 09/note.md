# 第九章 顺序容器

### 9.1

+ deque是双端队列。支持快速随机访问，在头尾插入/删除速度很快。

+ list和forward_list与vector,deque和array相比，这两个容器的额外内存开销也很大，这部分额外内存开销用于储存相邻位置的指针。

### 9.2

+ 创建一个容器为另一个容器的拷贝的时候，两个容器的类型及其元素类型必须匹配。不过，当传递迭代器参数来拷贝一个范围时，就不要求容器类型是相同的了，只要能将要拷贝的元素转换为要初始化的容器的元素类型即可。

+ 标准库array定义的时候需要指定类型和大小
```c++
array<int, 42>;
array<string, 10>;
```

+ assign操作不适用于关联容器和array
```c++
seq.assign(b,e); // 将seq中的元素替换为迭代器b和e表示范围中的元素。迭代器b和e不能指向seq中的元素。
seq.assign(il);  // 将seq中的元素替换为初始化列表il中的元素
seq.assign(n,t); // 将seq中的元素替换为n个值为t的元素。
```

+ 赋值相关运算会导致指向左边容器的内部的迭代器、引用和指针全部失效。而swap操作将容器内容交换不会导致容器的迭代器、引用和指针失效(容器类型为array和string的情况除外)。

+ 顺序容器通过assign允许从一个不同但相容类型赋值，或者从容器的一个子序列赋值。

+ swap操作交换两个类型相同的容器的内容。其中元素不会被移动，除了string外，指向容器的迭代器、引用和指针再swap操作之后都不会失效。它们依然指向swap之前所指向的那些元素，但是在swap之后，这些元素已经属于不同的容器了。

+ swap两个array会真正交换他们的元素，因此，交换两个array所需时间与array中元素数目成正比。

+ 容器即提供成员函数版本的swap,也提供非成员函数版本的swap，建议统一使用非成员函数版本的swap。

+ 每个容器类型都支持相等运算符(==和!=)，除了无序关联容器外的所有容器都支持关系运算符(>,<,>=,<=),只有当容器元素类型也定义了相应的比较运算符时，才可以使用关系运算符来比较两个容器(也就是需要定义==和<)。

### 9.3

+ 当用一个对象来初始化容器时，或将一个对象插入到容器中时，实际上放入到容器中的是对象值的一个拷贝，而不是对象本身。

+ insert函数将元素插入到迭代器所指定的位置之**前**。

+ c++11中，引入`emplace_front, emplace，emplace_back`，emplace函数在容器中直接构造元素。传递给emplace函数的参数必须与元素类型的构造函数相匹配。

+ erase函数返回指向最后一个删除的元素之**后**的迭代器。

+ 因为**forward_list**是一个单向链表，它没有定义insert,erase,emplace而是定义了**insert_after,emplace_after和erase_after**，也定义了一个首前的迭代器**before_begin**，用于在链表开始加入元素或删除元素。

+ **在对容器的大小进行操作之后，注意更新迭代器**，不要保存end返回的迭代器。

### 9.4

+ c++11，使用`shrink_to_fit`来要求deque,vector或string退回不需要的内存空间,但是具体实现可以选择忽略此请求。


### 9.5

+ string的搜索函数如果搜索不到结果就会返回一个**string::npos**的static成员

+ c++11中,可以用`to_string(val)`返回val的string表示，其中val可以是任何算术类型。

+ c++11中，可以用`stoi(s,p,b)`返回起始子串，返回值是int。p是size_t的指针，用于保存s中第一个非数值的下标，默认是0。b是转换所用的基数默认是10。类似的还有`stol, stoul, stoll, stoull`

+ c++11中，可以用`stof(s,p)`返回起始子串，返回值是float。p是size_t的指针，用于保存s中第一个非数值的下标，默认是0。类似的还有`stol, stoul, stod, stould`

### 9.6

+ 默认情况下，stack和queue是基于deque实现的，priority_queue是在vector之上实现的。

容器适配器|可选用的适配器
-----|--------
stack|除array和forward_list外任何容器类型
queue|list，deque
priority_queue|vector,deque
