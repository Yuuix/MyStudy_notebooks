# 剑指Offer习题汇总

## ４. [ 二维数组中的查找](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)

- #### 题目描述

> 在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

- #### 解题思路

  **双指针**
  
  可以采用两个指针，一个指向行，一个指向列，先将指针指向右边界（此时可以保证向下走一定是递增的，向左走一定是递减的）。
  
  然后每次与目标值做对比，如果比目标值大，则行指针下移，如果比目标值小，列指针左移。
  
- #### 示例代码

  ```c++
  class Solution {
  public:
      bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
          if (matrix.empty()) return false;
          int l = 0, r = matrix[0].size() - 1;
          while (l >= 0 && l < matrix.size() && r >= 0 && r < matrix[0].size()) {
              if (matrix[l][r] == target) return true;
              if (matrix[l][r] < target) l++;
              else r--;
          }
          return false;
      }
  };
  ```

## 5. [替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)

- #### 题目描述

> 请实现一个函数，把字符串 `s` 中的每个空格替换成"%20"。

- #### 解题思路

  **双指针**

  在原字符串上做修改，可以遍历两次字符串

  第一次，统计空格的个数，将字符串扩容。

  第二次，维护两个指针，一个指针指向新开辟字符串大小的最后一位，一个指针指向原字符串的最后一位

  从后向前遍历原字符串，如果没有遇到空格，直接进行赋值操作，如果遇到空格，则将20%填入到字符串中

- #### 示例代码

  ```c++
  class Solution {
  public:
      string replaceSpace(string s) {
          int o_size = s.size() - 1;
          int cnt = 0;
          for (char c:s) cnt += (c == ' ');
          s.resize(s.size() + cnt * 2);
          int size = s.size() - 1;
          for (int i = size, j = o_size; i >= 0; i--, j--) {
              if (s[j] != ' ') {
                  s[i] = s[j];
              } else {
                  s[i] = '0';
                  s[i - 1] = '2';
                  s[i - 2] = '%';
                  i -= 2;
              }
          }
          return s;
      }
  };
  ```

## 7. [ 重建二叉树](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)

- #### 题目描述 (leetcode105\106)

> 输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

- #### 解题思路

**递归**

前序遍历：根左右

中序遍历：左中右

1. 根据前序遍历可以确定根的值，根据中序遍历可以将整个树划分为左右两部分

   如何根据根值在中序遍历中找到根的位值呢？可以使用哈希表存储根元素与下标的映射

2. 确定递归参数

   我们对两个数组（前序排列、中序排列）进行建树，所以两个序列是必不可少的

   在每次递归时，要被新划分的左右子树分别进行相同的建树过程，所以应该有确定左右子树边界的参数，所以可以传入两组序列的左右下标

3. 确定终止条件

   当前序排列中的左指针>右指针时，这时说明到达了叶子节点（因为此时右指针已经不动了，左指针还在加1），直接返回空节点

4. 单次循环要做的事情

   创建当前根节点，并递归创建左子树与右子树

   创建当前节点需要首先确定当前节点的元素值，也就是前序遍历的左指针指向的值

   在递归创建左右子树需要清晰的计算出当前左右子树前序遍历和中序遍历的范围

5. 返回root树根

- #### 示例代码

```c++
/*
* struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    unordered_map<int, int>mp;
public:
    TreeNode *rebuild(vector<int>& preorder, vector<int>& inorder, int pre_left, int pre_right, int in_left, int in_right) {
        if (pre_left > pre_right) return NULL; //当左指针大于右指针，也就是到了叶子节点，返回空节点
        int pre_root = pre_left;
        int in_root = mp[preorder[pre_root]];
        TreeNode *root = new TreeNode(preorder[pre_root]);
        int pre_sub = in_root - in_left;
        root->left = rebuild(preorder, inorder, pre_left + 1, pre_left + pre_sub, in_left, in_root - 1);
        root->right = rebuild(preorder, inorder, pre_left + pre_sub + 1, pre_right, in_root + 1, in_right);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for (int i = 0; i < n; i++) {
            mp[inorder[i]] = i;
        }
        return rebuild(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};

//[力扣](https://leetcode-cn.com)
```

## 12. [矩阵中的路径](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)

- #### 题目描述

> 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。
>
> [["a","b","c","e"],
> ["s","f","c","s"],
> ["a","d","e","e"]]
>
> 但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。

- #### 解题思路

**深度优先搜索+剪枝策略**

此题与深搜走地图相似，可以应用深度优先遍历的方法

回顾一下深搜伪代码

```c++
类型 dfs(参数) {
	终止(边界)条件；(通常边界有一些特征，比如根据递归步数（深度），到达特定位置等) if() {
        存储结果;
        返回值;
    }
	尝试每一种可能 for(int i = 0; i < n; i++) {
		本步执行操作(设置标志位等)；
		递归进行下一步dfs()；
		回溯部分，撤销本步操作(取消标志位等)；
	}
	返回值;
}
```

当然可以根据题目条件增加一些剪枝策略

**dfs部分**

1. 确定边界条件

   由于本题的目的是找到最终的字符串，那么我们可以用什么来确定我们已经找到这个字符串了呢，我们可以根据步数就可以确定。

   >  例如：如果字符串长度是2，那么如果我们走了两部还没有return false;就证明我们已经确定有两位已经找到了，字符串总共就两位，所以这就代表我们找到了完整的字符串

2. 确定递归参数

   首先我们应该传入的参数有board数组和字符串word，接下来还需要传入什么参数呢？当然是用什么传什么，暂时想不到的可以后续用到时再添加

   一定用的到的参数：为了确定起点，需要传入起始下标；为了确定终止条件，需要记录步数

   > 当然如果我们考虑避免重复，不能遍历已经走过的位置，还可以传入标记数组，当然标记数组也可以作为全局变量，但是要注意，每次重新开始执行dfs前需要清空标记数组

3. 确定每一步要做什么

   对于每一个位置，可以向4个方向遍历，遍历时先判断边界条件以及下一个位置是否被标记等

   如果一切顺利的话（没有超出边界，下一步没有使用过），那么我们将下一位标记，继续执行递归

4. 回溯阶段

   如果这一步执行结束，没有找到目标路径的话，回溯阶段需要将其标志位去掉

5. 剪枝策略

   由于深搜这种递归本来就是一种暴力求解方法，它会枚举出每一种可能的路径

   但是有一些路径在一开始就是错的，我们没有必要继续沿着这条路径枚举，我们可以将这些部分裁减掉

   在本题中，如果发现起点的字符和字符串中的第一个字符不匹配的话，直接就可以返回false了

```c++
bool dfs(vector<vector<char>>& board, string word, int x, int y, int step) {
    if (x < 0 || x >= row || y < 0 || y >= col || word[step] != board[x][y]) return false;
    book[x][y] = 1;
    if (step == word.size() - 1) return true;
    for (int i = 0 ; i < 4; i++) {
        int sx = x + dir[i][0];
        int sy = y + dir[i][1];
        if (sx < 0 || sx >= row || sy < 0 || sy >= col) continue;
        if (book[sx][sy] == 0) {
            res = dfs(board, word, sx, sy, step + 1);
            if (res) break;
            book[sx][sy] = 0;
        }
    }
    return res;
}
```

**主体部分**

对于这道题来说，其实每一个位置都可以作为一个起点，只要在整张地图中可以找到一个目标字符串的路径就要返回True，所以需要以地图中的每一个点作为起点运用一次深搜，只要以一个位置为起点可以找到目的字符串的完整路径，就直接返回True，如果以每一个位置为起点进行深搜都找不到完整路径，那么返回就False。

```c++
bool exist(vector<vector<char>>& board, string word) {
    row = board.size();
    col = board[0].size();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            memset(book, 0, sizeof(book));//每次执行前需要初始化标记数组，因为在上一次dfs之后，起点处的标记并没有释放，也可以使用下面两行代码搞定
            //if (i) book[i-1][j]=0;
            //if (j) book[i][j-1]=0;
            if (dfs(board, word, i, j, 0)) return true;
        }
    }
    return false;
}
```

- #### 示例代码 

```c++
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        row = board.size();
        col = board[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                memset(mark, 0, sizeof(mark));
                mark[i][j] = 1;
                if (dfs(board, word, i, j, 0)) return true;
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board, string word, int x, int y, int step) {
        if (x < 0 || x >= row || y < 0 || y >= col || board[x][y] != word[step]) return false;
        if (step == word.size() - 1) return true;
        for (int i = 0; i < 4; i++) {
            int sx = x + dir[i][0];
            int sy = y + dir[i][1];
            if (sx < 0 || sx >= row || sy < 0 || sy >= col || mark[sx][sy]) continue;
            mark[sx][sy] = 1;
            if(dfs(board, word, sx, sy, step + 1)) return true;
            mark[sx][sy] = 0;
        }
        return false;
    }
private:
    int row, col;
    int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
    int mark[10][10];
};
```

**精简版**

```c++
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(dfs(board, word, i, j, 0)) return true;
            }
        }
        return false;
    }
private:
    int rows, cols;
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int k) {
        if(i >= rows || i < 0 || j >= cols || j < 0 || board[i][j] != word[k]) return false;
        if(k == word.size() - 1) return true;
        board[i][j] = '\0';
        bool res = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i - 1, j, k + 1) || 
                      dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i , j - 1, k + 1);
        board[i][j] = word[k];
        return res;
    }
};

//作者：jyd
//链接：https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/solution/mian-shi-ti-12-ju-zhen-zhong-de-lu-jing-shen-du-yo/
```

## 13. [机器人的运动范围](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/)

- #### 题目描述

> 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

- #### 解题思路 

  **深搜/广搜**

**dfs**

​	此题同样可以用深搜的方法，和深搜走地图一样。对于每一个点我们应先检查一下它是否满足题目中的条件，不满足条件的位置相当于地图中的障碍物。

​	这里我们使用check函数检查是否满足条件，如代码中所示

1. 每次我们判断当前位置是否可以走，不可以走的位置我们记为0步
2. 为了防止原路返回，我们对走过的位置需要进行标记
3. 对于每一个位置，它虽然有4个方向可以走，但是为了避免重复，只需取右、下两个方向
4. 从一个位置能走的步数应当是它右面以及下面位置能走的步数之和加1

**bfs**

首先我们来回顾一下广搜伪代码

```c++
queue<类型>que;
que.push(首个元素);
while (!que.empty()) {
    类型 temp = que.front();
    que.pop();
    for(;;) { //将当前队首元素所有下一层元素加入队列（层序遍历就循环每一层元素个数，如果走地图就遍历四个方向为下一层，主要作用是为下一层定界）
        que.push();
    }
}
返回值;
```

1. 首先定义一个结构体（node）存储位置坐标，记录可以走的位置数res
2. 与深搜一样，我们也需要一个check函数来检查某一位置是否能走

> 做好了前期准备，下面正式进入广搜套路

3. 将起始位置入队列，并将起始位置标记为1，代表已经走过
4. 进入循环，如果队列不为空，弹出队首元素，并将队首元素所有符合条件的下一层元素入队（即下一步在4个方向能到达的位置）
5. 入队元素标记为1，每入队一个元素res+1
6. 依次类推，直至队列为空

- #### 示例代码

**dfs**

```c++
class Solution {
public:
    int movingCount(int m, int n, int k) {
        return dfs(0, 0, m, n, k);
    }
private:
    int book[100][100] = {0};
    int check(int x, int y, int k) {
        int ans = 0;
        while (x || y) {
            ans += x % 10;
            ans += y % 10;
            x /= 10;
            y /= 10;
        }
        return ans <= k;
    }
    int dfs(int x, int y, int m, int n, int k) {
        if (!check(x, y, k) || x < 0 || x >= m || y < 0 || y >= n || book[x][y]) return 0;
        book[x][y] = 1;
        return dfs(x+1,y,m,n,k) + dfs(x,y+1,m,n,k) + 1;
    }
};
```

**bfs**

```c++
struct node {
    int x, y;
};

class Solution {
public:
    int movingCount(int m, int n, int k) {
        return bfs(0, 0, m, n, k);
    }
private:
    int book[100][100] = {0};
    int dir[2][2] = {0, 1, 1, 0};
    int check(int x, int y, int k) {
        int ans = 0;
        while (x || y) {
            ans += x % 10;
            ans += y % 10;
            x /= 10;
            y /= 10;
        }
        return ans <= k;
    }
    int bfs(int x, int y, int m, int n, int k) {
        if (!k) return 1; //如果k为0，只有(0,0)位置满足条件
        int res = 1;//代表(0,0)
        queue<node>que;
        que.push((node){0,0});
        book[0][0] = 1;
        while (!que.empty()) {
            node temp = que.front();
            que.pop();
            for (int i = 0; i < 2; i++) {
                int sx = temp.x + dir[i][0];
                int sy = temp.y + dir[i][1];
                if (sx < 0 || sx >= m || sy < 0 || sy >= n || book[sx][sy] || !check(sx, sy, k)) continue ;          
                que.push((node){sx, sy});
                book[sx][sy] = 1;
                res++;
            }   
        }
        return res;
    }
};
```

## 14. [剪绳子1](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/)

- #### 题目描述

> 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

- #### 解题思路

  **动态规划/递归+记忆化/贪心**

**动态规划**

> 回顾一下动态规划问题，该问题主要解决的是最大/最小值，方案总数，方案可不可行等问题。对于列举所有的方案，这类问题一定不是动态规划，而是回溯解决的问题（摘自某大佬总结）

以此题为例，我们来熟悉一下递归的流程

1. 确定dp数组及其含义

   dp[n]数组代表长度为n的绳子分段后的最大乘积

2. 确定动归公式

   由于长度小于n的绳子已经考虑每种分段情况的最大值了。所以对于长度为n的绳子，我们只需整体上分两段考虑就可以了，一段是n-i，另一段是i。

   - 如果对n-i的绳子进行细分（也就是说n-i至少分为两段），那么我们只需取 n - i 这部分分段后能取的最大值再乘 i 便是最大值，n - i 这部分绳子分段能取得的最大值，刚好是dp[n - i]做的事情，所以如果对n - i继续细分能取得的最大值就是 dp[n - i] * i;

   - 如果不对 n - i 长度的绳子继续细分，将其看作完整的一段，也就是真正的将整个绳子分为 n - i 和 i 两部分，此时值为 (n - i) * i;

   - dp[n] 应该取以上两者最大值为当划分 i 和n - i 两部分时的最大值，即`dp[n] = max( dp[n - i] * i,  (n - i) * i );`

3. 确定初始条件

   dp数组初始化为0，dp[2]=1，代表长度为2的绳子分段乘积最大值为1（长度为1的绳子默认为0）

**递归+记忆化**

递归效率要比动归效率低很多，它涉及了大量的重复计算；为了避免重复计算，可以使用记忆化数组记录已经计算过的值

> 也就是当递归产生的结果时，不要着急返回，先用记忆数组存储结果；当需要计算时，先别急着计算，先查找记忆数组中有没有计算好的结果

1. 先写递归函数，递归的思路和动归很像，只不过一个是至上而下（递归），一个是至下而上（动归）

   根据动归介绍，可以写出递归的代码如下

2. 在递归的返回值处，用一个记忆数组记录返回值，在每次递归时，先查找记忆数组有没有计算好的值，如果有直接用，没有在递归。

**贪心**

> 贪心策略通常应用于可以找到问题的局部最优解，且通过局部最优解可以推出全局最优找不到反例的情况

贪心需要先数学推导，参考[这篇文章](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/solution/mian-shi-ti-14-i-jian-sheng-zi-tan-xin-si-xiang-by/)，讲解非常透彻

首先需要先直到，当长度大于4的，最优的情况是将其尽可能以3分段，计算可以分成3段的个数为a，余数为b，在考虑以下三种情况

1. 当余数为0时，直接返回pow(3, a);
2. 当余数为1时，将最后一个3拆成2和1，因为2 * 2 > 3 * 1，故返回pow(3, a - 1) * 4;
3. 当余数为2时，返回pow(3, a) * 2;

- #### 示例代码

**动态规划**

```c++
class Solution {
public:
    int cuttingRope(int n) {
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 2; j < i / 2 + 2; j++) {//可以增加一些剪枝策略，如对于10来说先分成8(细分部分)和2，就没有必要分成2(细分部分)和8了
                dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
            }
        }
        return dp[n];
    }
private:
    int dp[60];
};
```

**递归**（超时）

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if (n <= 2) return 1;
        int ans = 0;
        for (int i = 1; i < n / 2 + 1; i++) {
            ans =  max(ans, max(cuttingRope(n - i) * i, (n - i) * i));
        }
        return ans;
    }
};
```

**递归+记忆化**

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if (n <= 2) book[n] = 1;
        int ans = 0;
        for (int i = 1; i < n / 2 + 1; i++) {
            if (book[n - i]) {
                ans = max(ans, max(book[n - i] * i, (n - i) * i));
            } else {
                ans =  max(ans, max(cuttingRope(n - i) * i, (n - i) * i));
            }
        }
        return book[n] = ans;
    }
private:
    int book[60];
};
```

**贪心**

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if (n <= 3) return n - 1;
        int a = n / 3;
        int b = n % 3;
        if (!b) return pow(3, a);
        if (b == 1) return pow(3, a - 1) * 4;
        return  pow(3, a) * 2;
    }
};
```

## 14. 剪绳子2

- #### 题目描述

> 与剪绳子1一样，只不过加了条件限制，n最大可以取到1000，会超出整型表示范围

- #### 解题思路

此题用动归的话，数值越界的问题不是那么好解决，这里使用贪心的方法，和剪绳子1一样的策略，尽可能的分成3段

如果长度大于4，每次*3，然后从长度中减去3，最后n剩余的长度，最多为4，还可能为2，3，这时直接与结果相乘即可

也可以使用**循环取余**的方法解决越界问题，[原理参考这篇](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/solution/mian-shi-ti-14-ii-jian-sheng-zi-iitan-xin-er-fen-f/)

主要公式：$x^a \% p =((x^{a-1}\%p)*x)\%p$ 

​				    $(xy)\%p=((x\%p)(y\%p))\%p$

所以可以先不断的对$x^1、x^2....$进行计算，然后一步步递推得到$x^a\%p$的结果

最后的结果仍然是三种情况，余数为0，1，2三种

​	余数为0：本来我们想得到的结果是$3^a\%1000000007$，我们通过循环取余得到了$3^{a-1}\%1000000007$，根据公式，可以得到

​					$3^a\%1000000007 = (3^{a-1}\%1000000007 * 3) \% 1000000007$

​	余数为1：同理	$(3^{a-1} * 4)\%1000000007 = (3^{a-1}\%1000000007 * 4) \% 1000000007$

​	余数为2：	$（3^a*2）\%1000000007 = （(3^{a-1}\%1000000007 * 3) \% 1000000007）* 2 \ \% 1000000007$

- #### 示例代码

```c++
class Solution {
public:
    int cuttingRope(int n) {
        if (n <= 3) return n - 1;
        if (n == 4) return 4;
        long ans = 1;//采用长整型
        while (n > 4) {
            ans = (ans * 3) % 1000000007; //在*3的过程中可能超出范围，需要取余运算
            n -= 3;
        }
        return ans * n % 1000000007; //最后*2时也可能超出范围，需要取余运算
    }
};
```

**循环取余**

```c++
class Solution {
public:
    int cuttingRope(int n) {
        #define p 1000000007
        if(n <= 3) return n - 1;
        if (n == 4) return n;
        int a = n / 3 - 1, b = n % 3;
        long rem = 1;
        while (a--) {
            rem = (rem * 3) % p;
        }
        if (!b) return (rem * 3) % p;
        if (b == 1) return (rem * 4) % p;
        return ((rem * 3) % p) * 2 % p;
    }
};
```

## 15. [二进制中1的个数](https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/)

- #### 题目描述

> 请实现一个函数，输入一个整数（以二进制串形式），输出该数二进制表示中 1 的个数。例如，把 9 表示成二进制是 1001，有 2 位是 1。因此，如果输入 9，则该函数输出 2。

- #### 解题思路

  **位运算/数学运算**

做这道题时，仿佛打开了新世界的大门，感受到了位运算的魅力

> **分享一些位运算小tips**
>
> 判断a是否是0元素：`!a`
>
> 判断元素奇偶性：`a&1`，1代表奇数，0代表偶数
>
> a+1：`a=-(~a)`
>
> 偶数a+1：`a | 1` 偶数a-1：`a ^ 1`
>
> a除2：`a >> 1` 	a乘2：`a << 1`
>
> 判断a是否与b相等：`a-b`，如果是0就相等
>
> 循环读入：`while(~scanf("%d", &a)){}`
>
> 满足条件时执行某操作：`i && printf("Hello!");`满足条件i时会执行printf
>
> 交换两个数：a ^= b; 	b ^= a;	 a ^= b;

现在就来看看下面几种思路：

1. 右移与1法

   将数字n与1，如果最后一位是1的话，得到的结果也一定是1，如果最后一位是0，得到的就是0，这样我们就判断了记录了最后一位的情况

   使n不断右移，每次与1，来判断最后一位是不是1，直至n等于0，得到所有n的个数。

2. n & (n - 1)

   通过n & (n - 1)可以将最后一个1消掉，这里可以用一个例子看一下（其实就是我们在二进制减法时的常识）

   ```
    0011000	#n
   -0000001	#1
   ---------
    0010001	#n-1 做减法时，由于我们会想前借位，所以最右面的1一定会被借走1位，从而变成0,其余1不变
   &0011000	#n
   ---------
    0010000	#n & (n-1) 可以看出只有最后一个1变为0，其余没有发生变化
   ```

   所以我们可以不断的通过n & (n - 1)来消掉最后一个1，直至n为0，记录有多少个1被消掉了

3. 判偶法（与第一种方法想法相同，只不过用了数学运算）

   每次%2如果是奇数，就证明最后一位是1，如果是偶数就证明最后一位是0。

   依次判断每一个位置，n不断/2，然后判断奇偶，奇数加1，偶数不加，直至n为0

- #### 示例代码

**右移与1法**

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while (n) {
            ans += n & 1;
            n >>= 1;
        }
        return ans;
    }
};
```

**n & (n - 1)**

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while (n) {
            ans++;
            n &= (n-1);
        }
        return ans;
    }
};
```

**判偶法**

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
       int ans = 0;
       while (n) {
           ans += n % 2;
           n >>= 1;
       }
       return ans;
    }
};
```

## 16. [ 数值的整数次方](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/)

- #### 题目描述

> 实现 [pow(*x*, *n*)](https://www.cplusplus.com/reference/valarray/pow/) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。

- #### 解题思路

  **递归/迭代**

1. **递归**

   - 确定递归参数

     参数已经给我们了，就是基数x与指数n

   - 确定边界条件

     当n=0或x=1的时候，可以返回1

   - 单次递归执行操作

     当n<0时，返回1/myPow(x, -n)，也就是$\frac{1}{x^{-n}}$

     当n>0时，且为奇数时，返回x*myPow(x, n - 1)

     当n>0时，且为偶数时，返回myPow(x * x, n >> 1)，这里就用到了**快速幂**的方法，如果是偶数的话先执行平方操作，使迭代次数减半

2. **迭代**

   - 同样分情况考虑，如果n<0的话，就计算$(\frac{1}{x})^{-n}$；n>0的情况，正常计算$x^n$
   - 进行迭代，同样分为奇数和偶数，奇数的话直接*=x，偶数的话可以先执行平方操作，让迭代次数减半

> 注意事项，由于INT_MIN在取反的时候已经超出了INT所表示的范围（负数比正数多了一位）
>
> 所以在迭代时我们用了long long
>
> 在递归的时候我们需要当n取INT_MIN时，使其增加2，由于考虑了x=-1的情况，所以不能使其奇偶性发生变化，自增2。

- #### 示例代码

**递归**

```c++
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0 || x == 1) return 1;
        if (n == INT_MIN) n += 2;
        if (n < 0) {
            return 1 / myPow(x, -n);
        } else if (n & 1) {
            return x * myPow(x, n - 1);
        } else {
            return myPow(x * x, n >> 1);
        }
    }
};
```

**迭代**

```c++
class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1.0;
        long num = n;
        if (num < 0) {
            x = 1 / x;
            num = -num;
        }
        while (num) {
            if (num & 1) ans *= x;
            num >>= 1;
            x *= x;
        }
        return ans;
    }
};
```

## 17. [打印从1到最大的n位数](https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/)

- #### 题目描述

> 输入数字 `n`，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

- #### 解题思路

1. **傻瓜解法**

   ​	此题可以先算出边界值，即`pow(10, n) - 1`，然后一层循环搞定，时间空间复杂度都不算高：
   
   - 时间复杂度：O(10^n^)	
   
   - 空间复杂度：O(1)
   
2. **回溯全排列**

   如果考虑过n的位数可能过大，超过整数表示范围，那么就需要借助字符串进行加法计算 

   此题还可以看作是0-9数字的全排列问题，也就是在0-9十个数中任意挑选出n个数的全排列，那么可以用回溯的方法，依次列出每一个数

   - 确定递归参数，记录一个位数x即可；

     树的宽度是9，深度是n；

   - 确定边界条件，当位数等于n时，证明找到了n个数字，将其加入结果数组中；

   - 单次递归要做的事情，循环遍历9个数，计算结果（拼接字符串），然后继续进行下一次递归；

   - 回溯阶段，本层结束后，需要将本层的元素归还；

- #### 示例代码

**傻瓜解法**

```c++
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int>ans;
        for (int i = 1; i < pow(10, n); i++) {
            ans.push_back(i);
        }
        return ans;
    }
};
```

> 附加一个傻瓜解法的位运算版

```c++
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int>ans;
        int x = 0;
        while (x - pow(10, n)) {
            if (x) ans.push_back(x);
            x = -(~x);
        }
        return ans;
    }
};
```

**回溯全排列**

```c++
class Solution {
public:
    vector<int>ans;
    string sum;
    void backtracking(int x, int n) {
        if (x == n) {
            if (stoi(sum)) ans.push_back(stoi(sum));
            return ;
        }
        for (int i = 0; i <= 9; i++) {
            sum.push_back(i + '0');
            backtracking(x + 1, n);
            sum.pop_back();
        }
    }
    vector<int> printNumbers(int n) {
        backtracking(0, n);
        return ans;
    }
};
```

> 此处如果习惯用char[]字符数组呢，就省去了回溯的步骤，可以仔细考虑一下，其实是因为index下标会覆盖，而push操作必须回溯（因为下标不会被覆盖）
>
> 我将代码也放在下面，可以用于考虑一下回溯的过程

```c++
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Solution {
public:
    vector<int>ans;
    //string sum;
    char sum[100];
    void backtracking(int x, int n) {
        if (x == n) {
            if (stoi(sum)) ans.push_back(stoi(sum));
            return ;
        }
        for (int i = 0; i <= 9; i++) {
            //sum.push_back(i + '0');
            sum[x] = i + '0';
            backtracking(x + 1, n);
            //sum.pop_back();
        }
    }
    vector<int> printNumbers(int n) {
        backtracking(0, n);
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int>v;
    int n;
    cin >> n;
    v = sol.printNumbers(n);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}
```

## 18. [删除链表的节点](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

- #### 题目描述

> 给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
>
> 返回删除后的链表的头节点。

- #### 解题思路

1. **虚拟头节点**

   做链表的题目时，可以按需巧妙的设置一个虚拟头节点

   通过设置一个虚拟头节点，这样就可以始终保证，指针指向的是要删除元素的前一个位置。

   为什么指针要指向前一个位置呢：设想一下，如果指针指向的是要删除元素的位置，那么我们就无法改变指向这个元素的指针的指向；如果找到了这个元素	的上	一个位置，我们就可以直接让上一个元素的指针跳过被删除元素，而指向要删除元素的下一个元素，这样元素就被删除了。

2. **双指针**

   不使用虚拟头节点能不能做呢？当然是可以的，一样的思路，可以使用快慢指针去做，这时候慢指针的作用呢就是找到待删除节点的上一个位置
   
   因为不能索引第一个节点的上一个位置，所以首先对第一个位置进行判断，如果第一个位置是待删除位置，那么直接返回下一个位置即可，后面的操作就和方法一样了

- #### 示例代码

**虚拟头节点**

```c++
class Solution { 
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode ret;	//虚拟头节点
        ret.next = head;
        ListNode *p = &ret;
        while (p->next && p->next->val != val) p = p->next;
        p->next = p->next->next;
        return ret.next;
    }
};
```

**双指针**

```c++
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode *p = head, *q = head;
        if (p->val == val) return p->next;
        p = p->next;
        while (p->next && p->val != val) {
            p = p->next;
            q = q->next;
        }
        q->next = p->next;
        return head;
    }
};
```

## 21. [调整数组顺序使奇数位于偶数前面](https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/)

- #### 题目描述

> 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

- #### 解题思路

**首尾双指针**

定义首尾指针，首指针指向首元素，尾指针指向尾元素

首指针不断右移，遇到偶数位置停下来；尾指针不断左移，遇到奇数位置停下来；

这时两个指针元素互换，然后继续向下寻找，直至两指针相遇；

**快慢指针**

两个指针开始都指向首部位置，遇到奇数元素，快慢指针均向前移动；遇到偶数元素，慢指针停下，快指针继续移动直至到达奇数元素，慢值指针；与快指针元素互换，然后均向前移动；依次类推，直至遍历整个数组

- #### 示例代码

**首尾双指针**

```c++
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            while (l < r && (nums[l] & 1)) l++;
            while (l < r && !(nums[r] & 1)) r--;
            swap(nums[l], nums[r]);
        }
        return nums;
    }
};
```

**快慢指针**

```c++
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int l = 0, r = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] & 1) {
                swap(nums[l], nums[r]);
                l++;
                r++;
            } else {
                r++;
            }
        }
        return nums;
    }
};
```

## 22. [链表中倒数第k个节点](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)

- #### 题目描述

> 输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
>
> 例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 3 个节点是值为 4 的节点。

- #### 解题思路

仍然是采用双指针，既然是想要得到倒数第k个节点，那么就先让一个快指针先走k步，然后两个指针一起走，直至快指针到达终点，返回慢指针位置即可；

- #### 示例代码

**双指针**

```c++
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *p = head, *q = head;
        while (k--) q = q->next;
        while (p && q) {
            p = p->next;
            q = q->next;
        }
        return p;
    }
};
```

## 24. [反转链表](https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/)

- #### 题目描述

> 定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

- #### 解题思路

**迭代**

迭代每次修改指针指向元素，定义三个指针，一个指向前一个元素，一个指向当前元素，一个指向下一个元素

每次只执行操作，当前指针指向上一个元素，同时需要更新三个指针的指向；

**递归**



- #### 示例代码

**迭代**

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = NULL;
        ListNode *cur = head;
        ListNode *next;
        while (cur) {
            next = cur->next; 
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};
```

**递归**

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode *ret = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return ret;
    }
};
```

## 25. [合并两个排序的链表](https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/)

- #### 题目描述

> 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

- #### 解题思路

可以先定义一个虚拟头节点（一个新链表的头节点），然后依次比较l1和l2两个链表的值，哪个小把哪个加入到新链表中，然后把相应指针后移（添加哪个链表的元素，哪个链表的指针后移一位），每次都要将新链表指针后移一位。

- #### 示例代码

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode ret;
        ListNode *p = &ret;
        while (l1 || l2) { //两个链表均为空时，处理结束
            if (l1 && l2) {//如果均不为空，比较链表元素大小
                if (l1->val < l2->val) {
                    p->next = l1;
                    l1 = l1->next;
                } else {
                    p->next = l2;
                    l2 = l2->next;
                }
                p = p->next;
            } else { //如果有一个链表为空，直接将指针指向非空链表即可
                p->next = l1 ? l1 : l2;
                return ret.next;
            }
        }
        return ret.next;
    }
};
```

## 27. [二叉树的镜像](https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/)

- #### 题目描述

> 请完成一个函数，输入一个二叉树，该函数输出它的镜像。

- #### 解题思路

  **递归**

1. 采用递归的想法，递归让每一个节点都取镜像，每个节点的左子树指向右子树的镜像，右子树指向左子树的镜像

- #### 示例代码

```c++
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (!root) return root;
        TreeNode* p = root->left;
        root->left = mirrorTree(root->right);
        root->right = mirrorTree(p);
        return root;
    }
};
```

## 34. [二叉树中和为某一值的路径](https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof/)

- #### 题目描述

> 输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

- #### 解题思路

  **回溯**

  1. 回溯终止条件

     当左右节点均为空时，此时终止

  2. 确定递归参数

     每次传入一个节点，以及当前要找的目标值

  3. 单次递归做的事情

     每次将当前节点加入到路径数组中，判断路径和是否与目标相等

     左右节点为空，且目标值为0，证明是一条路径，则将路径数组加入到结果数组中，并将上一个节点弹出并返回

     左右节点为空，且目标值不为0时，证明不是一条路径，此时也需要将上一个节点弹出并返回

- #### 示例代码

```c++
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if (!root) return ans;
        dfs(root, target);
        return ans;
    }
private:
    vector<vector<int>>ans;//结果数组
    vector<int>path;	//路径数组
    void dfs(TreeNode *root, int target) {
        path.push_back(root->val);	//每次将当前节点值加入到数组中
        target -= root->val;	//向下继续寻找target-root->val的值
        if (!target && !root->left && !root->right) path.push_back(temp);
        //如果向下寻找的值为0，且此时刚好是叶子节点，证明这是一条路径，将路径数组加入到结果数组中
        if (root->left) dfs(root->left, target);
        if (root->right) dfs(root->right, target);
        path.pop_back();
    }
};
```

```c++
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (!root) return ans;
        dfs(root, targetSum);
        return ans;
    }

    void dfs(TreeNode *root, int targetSum) {
        if (!root) return ;
        path.push_back(root->val);
        if (root->val == targetSum && !root->left && !root->right) ans.push_back(path);
        dfs(root->left, targetSum - root->val);
        dfs(root->right, targetSum - root->val);
        path.pop_back();
        return ;
    }
private:
    vector<vector<int>>ans;
    vector<int>path;
};
```

## 36. [ 二叉搜索树与双向链表](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)

- #### 题目描述

> 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

- #### 解题思路

  **深搜**

- #### 示例代码

```c++
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == NULL) return root;
        dfs(root);
        head->left = pre;
        pre->right = head;
        return head;
    }
private:
    Node *pre, *head;
    void dfs(Node *cur) {
        if (!cur) return ;
        dfs(cur->left);
        if (!pre) head = cur;
        else {
            cur->left = pre;
            pre->right = cur;
        }
        pre = cur;
        dfs(cur->right);
    }
};
```

## 37. [数字序列中某一位的数字](https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/)

- #### 题目描述

> 数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。
>
> 请写一个函数，求任意第n位对应的数字。

- #### 解题思路

  **数学类问题**

  对于这种数学类问题，需要从数学的角度去分析，模拟一下当给定一个数字n的时候，我们通常会如何思考求解n位对应的数字。

  我们通常会这样思考，对于一个n为数字

  当n<=9时，直接返回n对应的数字

  当n>9，我们会先判断n是否属于10-99，10-99中有9 * 10 * 2 = 180个数字。怎么判断呢，就看看n减去之前的9个数(1-9)，剩下的数还够不够180呗，如果n减去之前的9个数，剩下的数比180还大，那n对应的肯定是一个三位数，那我们就在减去这180，判断剩下的个数还够不够100-999(9 * 100 * 3)个数，如果在这个范围内，也就是剩下的数不足(9 * 100 * 3)个了，那这个n一定落在某个三位数的某一位，我们先取得这个三位数，也就是100+(n - 1) / (digit + 1)，得到这个数之后，还要得到具体是某一位(n - 1) % (digit + 1)，可以先将这个数转换为字符串，然后获得该位字符所对应的整数值。

- #### 示例代码

```c++
class Solution {
public:
    int findNthDigit(int n) {
        if (n < 10) return n;
        int digit = 0;
        while (n > 9 * pow(10, digit) * (digit + 1)) {
            n -= (9 * pow(10, digit) * (digit + 1));
            digit++;
        }
        int ans = pow(10, digit) + (n - 1) / (digit + 1);
        string temp = to_string(ans);
        return temp[(n - 1) % (digit + 1)] - '0';
    }
};
```

## 46. [把数字翻译成字符串](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/)

- #### 题目描述

> 给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

- #### 解题思路

  **动态规划**

  一般求解这种方法总数问题，比较容易想到使用动态规划的方法

  当相邻的两个数小于25时，此时dp[i] = dp[i - 1] + dp[i - 2]; 

  //dp[i - 1]就是将第i位单独算作一个数的方法总数，dp[i - 2]就是将相邻两位组合起来剩下的方法数

  若大于25，此时dp[i] = dp[i - 1];

  初始条件，当只有零或一个数的时候，那么方法总数为1

- #### 示例代码

```c++
class Solution {
public:
    int translateNum(int num) {
        string str = to_string(num);
        vector<int>dp(2);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 1; i < str.size(); i++) {
            if (str[i - 1] != '0' && (int)((str[i - 1] - '0') * 10 + (str[i] - '0')) <= 25) {
                dp[i % 2] = dp[(i - 1) % 2] + dp[i % 2];
            }
            else dp[i % 2] = dp[(i - 1) % 2];
        }
        return dp[(str.size() - 1) % 2];
    }
};
```

## 56. [数组中数字出现的次数1](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/)

- #### 题目描述

> 一个整型数组 `nums` 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

- #### 解题思路

  **位运算**

  运用异或运算，对数组中所有的数字进行异或运算，由于只有两个数字出现一次，其余数字都出现了两次，出现两次的异或运算会两两抵消，所以最后结果就是，两个只有一个的元素异或运算结果。

  当分组内只有一个单独元素，其余都是成对的话，我们通过异或运算会很容易把这个元素取到，但是现在问题就是如何将这两个单独元素分到不同的组里，那么就要找到这两个元素的不同点。根据两个元素的异或结果，可根据最后一位1值就是两者不同的位置，首先通过一个变量记录这个位置。

  然后遍历一遍数组，根据这个变量将所有元素分为两组，每组含一个单独元素，通过异或运算可以得到这两个值。

- #### 示例代码

```c++
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int temp = 0;
        for (int num:nums) {
            temp ^= num;
        }
        int a = 1;
        while (!(temp & a)) {
            a <<= 1;
        }
        int b = 0, c = 0;
        for (int num:nums) {
            if (num & a) {
                b ^= num;
            } else {
                c ^= num;
            }
        }
        return {b, c};
    }
};
```

## 57. [和为s的连续正数序列](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/)

- #### 示例代码

> 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
>
> 序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

- #### 解题思路

  **滑动窗口**

  通过左右指针去维护一个窗口，用一个变量去记录窗口内元素和，当元素和大于目标值，左指针后移，当元素和小于目标值，右指针后移，当元素和等于目标值，将区间元素读入中间数组，然后将中间数组加入到结果数组中。

  一直到左指针指向元素大于目标值，循环结束。

- #### 示例代码

**前缀和+哈希表**（效率低）

```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<long long>ans(target + 1);   //前缀和数组
        ans[0] = 0;
        for (int i = 1; i <= target; i++) {
            ans[i] = ans[i - 1] + i;
            mp[ans[i]] = i;
        }
        mp[0] = 0;
        for (int i = 1; i <= target; i++) {
            if (mp.find(ans[i] - target) != mp.end()) {
                if (i - mp[ans[i] - target] <= 1) continue;
                for (int j = mp[ans[i] - target] + 1; j <= i; j++) {
                    path.push_back(j);
                }
                if (!path.empty()) res.push_back(path);
                path.clear();
            }
        }
        return res;
    }
private: 
    vector<vector<int>>res;
    vector<int>path;
    unordered_map<int, int>mp; 
};
```

**滑动窗口**

```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int l = 1, r = 1;
        int sum = 0;
        vector<int>path;
        vector<vector<int>>ans;
        while (l <= target / 2) {
            if (sum > target) {
                sum -= l;
                l++; 
            } else if (sum < target) {
                sum += r;
                r++;
            } else {
                for (int i = l; i < r; i++) {
                    path.push_back(i);
                }
                ans.push_back(path);
                path.clear();
                sum -= l;
                l++;
            }
        }
        return ans;
    }
};
```

## 60. [n个骰子的点数](https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/)

- #### 题目描述

> 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。
>
> 你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。

- #### 解题思路

  **动态规划**

1. 确定动归状态

   dp数组代表投n次骰子的概率数组。

2. 确定递推关系式

   $f(n, x) = \sum_{1}^{6}{f(n-1, x - i) * \frac{1}{6}}$

3. 确定初始条件

   当n=1时，概率数组中每一位均为$\frac{1}{6}$

由于根据上述递推关系式，x位可能会出现负数f(n, 3-6)，所以我们可以反向递推

既然新的动归数组(n)每一位都是通过之前的动归数组(n-1)前六位累加；可以转换思路，每一次将当前动归数组每一位累加至后一个动归数组的后六位不就可以了

- #### 示例代码

```c++
class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<double>dp(6, 1 / 6.0);
        for (int i = 2; i <= n; i++) {
            vector<double>temp(5 * i + 1);
            for (int j = 0; j < dp.size(); j++) {
                for (int k = 0; k < 6; k++) {
                    temp[j + k] += dp[j] / 6;
                }
            }
            dp = temp;
        }
        return dp;
    }
};
```

## 62. [ 圆圈中最后剩下的数字](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/)

- #### 题目描述

> 0,1,···,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字（删除后从下一个数字开始计数）。求出这个圆圈里剩下的最后一个数字。
>
> 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

- #### 解题思路

  **动态规划/递归**

  此题为约瑟夫环问题，找出一组数中最后一个被删除的数字

  设$f(n,m)$为在0~n-1之间每隔m个数删除一个数字的结果，当它删除一个数字后，将从下标t=m%n之后开始继续循环删数

  删除一个数字后，就只剩下n-1个数字，此时变成了$f(n-1, m)$的问题，但是不同的是，此时是从下标0开始删除数字，如果能找到$f(n-1, m)$问题最后的结果（假如最终结果是x）和$f(n,m)$的关系，就可以使用动态规划了。下面我们来看看$f(n,m)$问题删除一个数后继续继续在n-1个数字中删除，还$f(n-1,m)$问题之前的坐标映射关系

  ```
  f(n, m)删除一个数字后，从t开始继续删数，就好像将t前面的数都移动到最右面开始继续循环删除数字
  t t+1 t+2 t+3 ....... t-3 t-2
  0  1   2   3          n-1 n-2 f(n-1,m)问题
  从下标可以看出，如果f(n-1,m)最后删除的是第x位，那么f(n,m)最终应该返回的是(t+x)%n位
  推导出最终的递推公式：(x+t)%n=(x+m%n)%n=(x+m)%n 
  ```

  有了递推公式，我们便可以使用动态规划进行一步步运算了，初始条件为，当n=1时返回0。

- #### 示例代码

**动态规划**

```c++
class Solution {
public:
    int lastRemaining(int n, int m) {
        int x = 0;
        for (int i = 2; i <= n; i++) {
            x = (x + m) % i;
        }
        return x;
    }
};
```

**递归**

```c++
class Solution {
public:
    int lastRemaining(int n, int m) {
        if (n == 1) return 0;
        return (lastRemaining(n - 1, m) + m) % n;
    }
};
```

## 66. [构建乘积数组](https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/)

- #### 题目描述

> 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B[i] 的值是数组 A 中除了下标 i 以外的元素的积, 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

- #### 解题思路

1. 将表格分为上三角和下三角两个部分，先计算上三角的累乘将结果累加到数组中
2. 计算下三角的累乘将结果叠加到结果数组中

![Picture1.png](assets/6056c7a5009cb7a4674aab28505e598c502a7f7c60c45b9f19a8a64f31304745-Picture1.png)

- #### 示例代码

```c++
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        vector<int>b(n, 1);
        for (int i = 1; i < n; i++) {//先计算下三角的值，从1开始，因为第0位不能累乘第a[0]位，此次计算除了第b[0]的所有值
            b[i] = b[i - 1] * a[i - 1];
        }
        int acc = 1;
        for (int i = n - 2; i >= 0; i--) {//再计算上三角，从n-2开始，因为n-1位不能累乘a[n-1]位,用acc记录累乘的结果
            acc *= a[i + 1];
            b[i] *= acc;
        }
        return b;
    }
};
```

