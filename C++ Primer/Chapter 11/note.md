# 第十一章 关联容器

+ 标准库提供了8个关联容器，他们是`(unordered_)(multi)map/set`,定义在各自对应的头文件中。

### 11.2

+ 可以使用初始化列表初始化一个map,如下。使用`{key, value}`的形式表示键值对。
```c++
map<string, string> authors = {{"Joyce", "James}, {"Austen", "Jane}};
```

+ 对于有序的关联容器，关键字必须定义了<运算符,也可以自定义比较函数。自定义比较函数的时候需要再尖括号中紧跟元素类型给出(函数类型)，同时在创建一个容器对象的时候也需要提供比较函数的实例。
```c++
bool cmp(const int& a, const int& b) {
....
};

multiset<int, decltype(cmp)*> temp(cmp);
```

### 11.3

+ 对于set，key_type和value_type都返回关键字类型，在map中，key_type返回关键字类型，mapped_type返回关联的类型，value_type返回`pair<const key_type, mapped_type>`，可以改变pair的值，不能改变关键字成员的值。

+ 虽然 set类类型同时定义了iterator和const_iterator类型，但两种类型都只允许只读访问set中的元素。

+ 当使用一个迭代器遍历一个map、multimap、set或multiset的时候，迭代器按关键字升序遍历元素。

+ 对于不包含重复关键字的容器，添加单一元素的insert和emplace版本返回一个pair，告诉我们插入操作是否成功。pair的first成员是一个迭代器,指向具有给定关键字的元素；second成员是一个bool值，指出元素插入成功还是已经存在于容器中，若已在容器中值为false。

+ 对于包含重复关键字的容器，执行insert函数后返回的是一个指向新元素的迭代器。

+ 关联容器提供一个额外的earse操作，它接受一个key_type的参数，此版本删除所有匹配给定关键字的元素，返回实际删除的元素数量。如果利用一个迭代器或者一对迭代器表示范围删除元素，则返回删除元素后元素的迭代器。


+ 对于map和unordered_map的下标范围符，如果关键字不在map中，会为它创建一个元素并插入到map中，关键值会进行值初始化，所以我们只能对非const的map使用下标运算符号。

+ 关联容器提供三种特殊的查找元素的操作
```c++
lower_bound(k) 返回一个迭代器，指向第一个关键字不小于k的元素
upper_bound(k) 返回一个迭代器，指向第一个关键字大于k的元素
equal_range(k) 返回一个迭代器pair,表示关键字等于k的范围。若k不存在，pair的两个成员都等于c.end()
```

