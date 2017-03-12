# 第十二章 动态内存


### 12.1

+ shared_ptr允许多个指针指向同一个对象，unique_ptr则"独占"所指向的对象。week_ptr是一个伴随类，是一种弱引用。这三种指针都在头文件`<memory>`中。

+ 调用make_shared函数在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr。
```c++
shared_ptr<string> p = make_shared<string>(10, '9'); // 括号内是初始化string的参数。
```

+ 当指向一个对象的最后一个shared_ptr被销毁的时候，shared_ptr类会自动销毁此对象。

+ 可以对动态分配的对象进行值初始化，只需在类型名之后跟一对空括号，否则进行默认初始化。
```c++
int *pi = new int();
string *ps = new string();
```

+ 如果提供了一个括号包围的初始化器，就可以使用auto，但是，由于编译器需要用初始化器的类型推断要分配的类型，只有当括号中仅有单一初始化器时才可以使用auto
```c++
auto p1 = new auto(obj); // p1 指向一个与obj类型相同的对象。
```

+ new不能分配所要求的内存空间时，会抛出一个bad_alloc的异常。也可以使用空位new，使new不能分配时返回空指针。
```c++
int* p = new(nothrow) int;
```

+ shared_ptr可以用普通的指针进行初始化，若指向的类型不一致则必须提供自己的操作用于delete。
```c++
shared_ptr<T> p(q,d); // p将使用可调用对象d代替delete
shared_ptr<T> p(p2,d); // p是shared_ptr p2的拷贝，唯一的区别是p将用可调用对象d代替delete。
```

+ 在调用`p.reset()`时，若p是唯一指向其对象的shared_ptr时，reset会释放此对象。若传递了可选参数内置指针q，会令p指向q，否则会将p置为空。若还传递了参数d，将会调用d而不是delete来释放q。
```c++
p.reset(new int(1024)); // p 指向一个新的对象。
```

+ shared_ptr可以使用`p.unique()`来判定时候是唯一的用户，也可以使用`p.use_count()`获取对象智能指针的数目(效率较低，仅仅用作调试)。

+ 不要混合使用普通指针和智能指针，也不要使用get初始化另一个智能值或为智能指针赋值。

+ 由于unique_ptr拥有它指向的对象，因此unique_ptr不支持普通的拷贝或赋值操作。
```c++
一些unique_ptr的专属操作
u = nullptr
u.release() // 放弃指针的控制权，返回指针，并置为空。用于转移控制权。
u.reset(),u.reset(q), u.reest(nullptr) // 释放u指向的对象，如果提供了内置指针q，令u指向这个对象。
```

+ unique_ptr转移控制权的方法`unique_ptr<string> p(p1.release());`，或者利用reset方法`p2.reset(p3.release());`
```c++
auto p = p2.release(); //　记得delete p;
```

+ 不能拷贝unique_ptr有一个例外，可以拷贝或赋值一个将要被销毁的unique_ptr,也就是可以从函数返回一个unique_ptr。

+ 向unique_ptr传递删除器必须再尖括号中unique_ptr指向类型之后提供删除器的类型。
```c++
unique_ptr<objT, delT> p(new objT, fcn);
```

+ week_ptr是一种不控制所指向对象生存期的智能指针，它指向由一个shared_ptr管理的对象，但是不会改变shared_ptr的引用计数，创建一个week_ptr时，要用一个shared_ptr来初始化。
```c++
w.expired() 若w.use_count()为0.返回true否则返回false
w.lock() 若expired为true，返回一个空shared_ptr;否则返回一个指向w的对象的shared_ptr
```


### 12.2

+ 动态new一个数组时，返回的是一个数组元素类型的指针。由于分配的内存并不是一个数组类型，因此不能对动态数组调用begin和end。这些函数使用到了数组维度，同样地，也不能使用范围for语句来处理动态数组中的元素。

+ c++11中，在new一个动态数组的时候，可以提供一个元素初始化器的花括号列表。
```c++
int *p = new int[10]{0,1,2,3,4,5,6,7,8,9};
```

+ 如果在delete一个数组指针时忘记了方括号，或者在delete一个单一对象的指针时候使用了方括号，编译器可能不会发出警告。程序可能在执行过程中发生未定义的行为。

+ 可以使用unique_ptr智能指针管理动态数组。当unique_ptr指向的是一个数组而不是一个对象的时候，就不能使用点或箭头运算符。
```c++
unique_ptr<T[]> u(p)
u[i] // 返回u拥有的数组中位置i处的对象。
```

+ 如果希望使用shared_ptr管理一个动态数组，必须提供一个自定义的删除器。同时，不能通过下标运算符访问
```c++
shared_ptr<int> sp(new int[10], [](int *p) {delete []p;});
sp.reset();

for (size_t i = 0; i != 10; ++i)
    *(sp.get() + i) = i;
```

### 12.3

+ allocator将内存分配跟对象构造分离开来。

+ 为了使用alocate返回的内存，必须用construct构造对象。使用过后调用`a.destroy(p)`，之后可以利用`a.deallocate(p, n)`把内存归还给系统。
```
a.construct(p, args); // 根据args创建对象保存在p指向的内存中。
```
