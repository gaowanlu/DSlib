# DSinc
## 用C语言实现的数据结构函数库
## CommonType.h
为了使程序具有较强的通用性，本函数库基本数据类型将全部采用struct CommonType类型，用户可以自行在其中添加自己所需要的数据类型


## SequenceList.h(顺序表)  已测试
* SequenceList_init();(初始化顺序表以及释放顺序表内存)
* SequenceList_value();(获得指定下标位置的元素的地址)
* SequenceList_push();(往顺序表的后面添加新的元素)
* SequenceList_pop();(弹出顺序表末尾的元素)
* SequenceList_insert();(往顺序表中插入一个元素)
* SequenceList_delete();(删除顺序表指定下标位置的元素)


## Slist.h(单向链表)  已测试
* Slist_init();(初始化单向链表)
* Slist_free();(释放链表)
* Slist_before();(头插法加入新节点)
* Slist_after();(尾插法加入新节点)
* Slist_value();(获得第index个节点地址)
* Slist_insert();(在指定位置插入新节点)
* Slist_delete();(删除指定位置的节点)


