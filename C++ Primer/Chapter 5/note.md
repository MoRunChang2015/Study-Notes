# 第五章 语句

### 5.3 

+ case关键字和它对应的值一起被称为**case标签**，**case标签**必须是整型常量表达式。

+ 在switch语句中，如果某处一个带有初值的变量位于作用域之外，在另一处该变量位于作用域以内，则从前一处跳转到后一处是非法行为。
```c++
    switch (a) {
        case 0:
            string filename; // Error! string 会隐式初始化
            int ival = 0; // Error! 显式初始化
            int jval; // 正确
            break;
        case 1:
            jval = 1;
            // filename.empty();
    }
```


### 5.4

+ 范围for语句语法格式是
```c++
    for (declaration : expression)
        statement
```

+ 其中expression表示的必须是一个序列，比如用花括号括起来的初始值列表，数组，vector或者string。这些类型的共同特点是拥有能返回迭代器的begin和end成员。

+ do while语句使用的condition中使用到的变量必须定义在循环体之外，且不允许在condition内定义变量。

### 5.5

+ goto语句与switch语句类似，不能将程序的控制权从变量的作用域之外转移到作用域之内。
```c++
    goto end;
    int ix = 10; // Error! 绕过了一个带初始化的变量定义。
end:
    ix = 42;
```

### 5.6

+ exception, bad_alloc和bad_cast对象只能默认初始化，而其他类型应该用string对象或者c风格字符串初始化，不允许使用默认初始化的方式，这些异常类带有一个what的成员函数，获取异常信息。
