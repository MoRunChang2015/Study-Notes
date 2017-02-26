# 第十二章 动态内存


### 12.1

+ shared_ptr允许多个指针指向同一个对象，unique_ptr则"独占"所指向的对象。week_ptr是一个伴随类，是一种若应用。这三种指针都在头文件`<memory>`中。

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

+　new不能分配所要求的内存空间时，会抛出一个bad_alloc的异常。也可以使用空位new，使new不能分配时返回空指针。
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
