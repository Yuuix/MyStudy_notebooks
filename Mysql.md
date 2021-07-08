# 数据库

[下载地址](https://www.navicat.com.cn/download/navicat-premium)

实现数据持久化

使用完整的管理系统统一管理，易于查询

报错：

[删除mysql](https://www.cnblogs.com/Do-n/p/14093268.html)

## 1. 数据库相关概念

1. #### **基础概念**

DB：database数据库，存储数据的仓库，它保存了一系列有组织的数据；

DBMS：数据库管理系统，数据库是通过DBMS创建和操作的容器；

SQL：结构化查询语言，专门用来和数据库通信的语言。

> 几乎所有DBMS都支持SQL
>
> 简单易学

## 2. 特点

- 将数据放到表中，表再放到库中；
- 一个数据库中可以有多个表，每个表都有一个自己的名字，用来标识自己，表名具有唯一性；
- 表中具有一些特性，这些特性定义了数据在表中如何存储；
- 表由列组成，我们也称为字段。所有表都由一个或多个列组成，每一列类似属性；
- 表中的数据是按行存储的，每一行类似对象。

## 3. 数据库引擎

不同的数据文件在磁盘中的不同组织形式

1. **InnoDB**
2. **MyIsam**

|            | MyIsam |       InnoDB        |
| :--------: | :----: | :-----------------: |
|  事务支持  | 不支持 |        支持         |
| 数据行锁定 | 不支持 |        支持         |
|  外键约束  | 不支持 |        支持         |
|  全文索引  |  支持  |       不支持        |
| 表空间大小 |  较小  | 较大，约为MyIsam2倍 |

常规使用操作

- MyIsam：节约空间，速度较快
- InnoDB：安全性高，事务的处理，多表多用户操作

> 在物理空间存在的位置

本质还是文件存储

MySQL引擎在物理文件上的区别

## 4. 事务

将一组SQL放到一个批次中去执行

[菜鸟教程](https://www.runoob.com/mysql/mysql-transaction.html)

> 事务原则：ACID原则 原子性，一致性，隔离性，持久性

- 原子性：一组SQL语句，要么全部执行，要么全部不执行
- 一致性：执行前和执行后，要保证数据库的完整性，遵循某些规则
- 持久性：事务没有提交，恢复到原状；事务提交，持久化到数据库，事务一旦提交不可逆
- 隔离性：数据库允许多个并发事务同时对其数据进行读写和修改的能力，隔离性可以防止多个事务并发执行时由于交叉执行而导致数据的不一致。事务隔离分为不同级别，包括读未提交（Read uncommitted）、读提交（read committed）、可重复读（repeatable read）和串行化（Serializable）。

**隔离级别**

如果事务没有隔离性，会由于多个线程访问同一个表时，引起脏读、不可重复读、幻读等情况，为了避免这些情况，四大隔离级别就是让多个事务访问同一个表也可以互不影响。

[四大隔离级别](https://www.cnblogs.com/fjdingsd/p/5273008.html)

1. 脏读：指一个事务读取到了另一个事务未提交的数据
2. 不可重复读：在一个事务内读取表的某一行数据，多次读取结果不同（不一定是错误）
3. 幻（虚）读（可重复读）：指在一个事务内读取到了别的事务插入的数据，导致前后读取不一致（一般是行影响，多了一行）
4. 串行：不同的事务串行执行，效率低

## 5. 索引

索引是帮助MySQL高效获取数据的数据结构

索引在小数据量的时候用处不大，但是在大数据的时候区别十分明显

索引并不是越多越好，每创建一个索引，就会对该索引创建一棵B+树

如果创建索引过多，会查找多棵树，反而降低查找效率

**聚簇索引：**数据和索引放在一起，innodb主键索引

**非聚簇索引：**数据和索引不放在一起，myisam索引

**索引的分类**

- **主键索引**
  
  - 唯一的标识，主键不能重复
  
- **唯一索引**
  
  - 避免重复的列出现，唯一索引可以重复，多个列都可以标识为唯一索引
  
- **常规索引**
  
  - 默认的，index、key关键字来设置
  - 在普通列上创建的索引
  - 回表：从普通索引列中查找主键，根据主键找到整行的记录
  - 索引覆盖：直接通过查找普通列查找要找的字段，可以直接返回，不需要从主键树中检索结果，通过改写sql语句来进行索引覆盖，避免回表，增大查找效率
  
- **全文索引**
  
  可以根据全文的关键词，指明包含这一关键词的都要哪几行，然后直接根据关键词搜索即可。
  
  而使用LIKE匹配不够灵活，而且要匹配表中所有行，效率低。
  
  - 在特定的数据库引擎上才有(如MyIsam)
  - 快速定位数据
  
- **组合索引**

**索引原则**

- 索引不是越多越好
- 不要对经常变动的数据加索引
- 小数据量的表不需要加索引
- 索引一般加在常用来查询的字段上

**索引的数据结构**

InnoDB的默认数据结构是B+树

## 6. MySQL备份

- 保证重要的数据不丢失
- 数据转移

MySQL数据备份的方式

- 直接拷贝物理文件
- 使用数据库可视化工具
- 命令行导出 mysqldump

## 7. 数据库设计

**糟糕的数据库**

- 数据冗余，浪费空间
- 数据库插入和删除都会麻烦、异常
- 程序的性能差

**良好的数据库设计**

- 节省内存空间
- 保证数据库的完整性
- 方便我们开发系统

**软件开发中，如何设计数据库**

1. 分析需求：分析业务和需要处理的数据库的需求
2. 概要设计：设计关系图

## 8. 三大范式

**规范数据库的设计**

1. **第一范式**

   要求数据库表的每一列都是不可分割的原子数据项

2. **第二范式**

   前提：满足第一范式

   每张表只描述一件事情

3. **第三范式**

   前提：满足第一第二范式

   确保数据表中每一列数据都和主键直接相关，而不能间接相关


