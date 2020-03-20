## 5. 最长回文串

核心，奇偶性区分

### 与反串做最长子串匹配 + 位置验证

回文串即正反相同的串，因而可以直接找原串与反串的最长公共子串；但注意，找到的最长公共子串可能并不对应原串的的子串，所以在dp的时候要做位置验证，确定这两个更长的串对应原串里的同一个子串。时间复杂度为$O(n^2)$。空间复杂度可以为O(n)。

### 基本回文串的动态规划拓张

第二中动态规划算法：最小的回文串分别为a, aa 形式，即偶数或奇数形式，我们用R(i, j) = true/false表示第i-j位为回文串的情况。初始化矩阵对角线为1、对每个R(i, i+1)进行判断。矩阵的增长由对角线向右上角增长，对于奇数位与偶数位要分别增长，一旦遇到false，对应循环可以直接break，因为回文串的任意中心串都是回文串。时间复杂度O(n^2)但是算有剪枝，如果以每个/两个字符为中心的回文串长度较小，会相对快（其实和暴力枚举法很像）。（其实空间复杂度可以为O(1)）

### 暴力

以每个字符、每相邻两个字符为中心，向外拓张，失败即向右移动，时间复杂度O(n^2), 空间复杂度为O(1)；认为是这三种最好写的解

> Manacher 算法 时间可以达到O(n)，但是比较偏，是字符串处理算法，类似KMP

### 注意

string.substr(start, len);

## 10. regular expr matching

> 递归的想法，都做了好久，还是最慢的


## recursive

递归有些像“决策树”，优先想好如何分叉，什么条件做主干，对于算法的复杂度、实现难度关系大。比如判断是否pattern的第二位是"*"应优先（作为第一层循环）于判断string和pattern的首字符是否match，因为两者不是独立的，是否是真正的“match”依赖于后面的 “*”，如果后面的“*”无意义，则这一次判断就没有意义。

另，`string[string.length()]=''`, 并不会出现越界错误

```c++
        bool isMatch(string s, string p) {
        if(p.empty()) 
            return s.empty();
        // if(p.length()==1) {
        //     return  (s[0] == p[0] || p[0] == '.') && s.length()==1;
        // }
        if(p[1] == '*') {
            return isMatch(s, p.substr(2)) || !s.empty() && (s[0] == p[0]||p[0]=='.') && isMatch(s.substr(1), p);
        } else {
            return !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
        }
        
    }
```

### dp

自己的思路真的乱，声明的那些地方就更不要错了；

这道题一看就可以dp，更长串的匹配由子串的匹配结果增长得到。dp的原点是0长度串的匹配，所以需要m+1 * n+1大小数组。

```c++
dp[i][j] = p[j-1] != '*' ? dp[i-1][j-1] && s[i-1] = p[j-1] (额外算上'.'的匹配)
    : dp[i][j-2] // 1. '*' 的作用是前一个字符出现0次
    || dp[i-1][j] && s[i-1] == p[j-2] (额外算上'.'的匹配) // 2. '*' 的作用是前一个字符出现多一次（即若干次）, 相同长度的pattern，可以确认的目标串更长 // **注意，两者情况的总和一定要是'*'可能情况的全集
```

自己开始的思路是，'*' 要不相当于删去前一个字符，要不等同于没有，如此则少了“匹配任意个前面字符的情况”。

动态规划的矩阵，增长的方式一般不会仅是一个方向；如果少考虑了情况，可能就会出现这种错误。（递推关系一定要能表示全集）。

## 44. wildcard matching

### dp

这道题的约束比第10题更小，因为'*'是否match不再需要根据前面的元素，因而有更简化的算法。用dp做和第10题的思路完全一致

```c++
define dp[i][j] : s[0:i-1] match p[0:j-1] 

init dp: dp[0][0] = true, dp[0][i] := (p[0:i-1] == "*"*(i-1))

p[j] is not '*': dp[i][j] = s[i-1] match p[j-1]
    is '*': dp[i][j] = dp[i][j-1] ('*' match nothing)  || dp[i-1][j] ('*' match one more char)
```

### iterate

一个pattern可能有多个方式去匹配同一个string，（如 aaa与**），我们使最后一个\*匹配最多的字符，前面的\*匹配（能匹配目标串）最少量的字符，（这其实是一种贪心的想法）。

设置两个指针分别指向两个string的开始，进行匹配。如果pattern串非\*，则正常匹配前移指针。如果是\*，记录此时原串与模式串的指针位置，从\*匹配0个字符开始尝试，即下一次迭代，原串位置不变，模式串位置+=1；如果遇到mismatch，则返回上一次\*的匹配位置，然后让\*匹配多一个字符重新尝试（即目标串指针++；注意，记录的指针位置也加1）。

因为我们让每个\*都在匹配尽可能少的必要的符号，所以在模式串指针到达结尾后，也要重新尝试，让上一个\*匹配更多的字符。

循环跳出的条件是：mismatch，且这个位置前也没有遇到过\*，直接return false；或者是一直尝试让一个\*match了全部的目标串，但一直没有办法达成条件（此时目标串指针到达结尾，模式串指针不在结尾）。

尝试完成后，模式串指针的后面可能是一堆\*，处理一下就好了。

```c++
class Solution {
public:
    bool isMatch(string s, string p) {
        int m=s.size(), n=p.size();
        int i=0, j=0, lasti=-1, lastj=-1;
        for(; i<m; i++, j++) {
            // cout << i << " " << j << " " << lasti << " " << lastj << endl;
            if(p[j] == '*') {
                lasti = i;
                lastj = j;
                i--;
                continue;
            }
            if(j == n || (s[i] != p[j] && p[j] != '?')) { // 匹配失败
                // goback
                if(lastj < 0) 
                    return false;
                    
                i = lasti++;
                j = lastj;
                
                continue;
            }
        }
        // cout << i << " " << j << endl;
        // append *
        while(p[j] == '*') {
            j++;
        }
        return j==n;
    }
};
```

### recursion

递归思路也很清晰，可以使用与迭代方法相似的剪枝，认为原因是这道题的“递推依赖”很简单，所以dp性能稍差。dp可能是稳定的算法吧QAQ。

## 32. 最长有效括号

### dp

自己的思路太局限了，知道要用dp的想法做，就不去深入思考。这么简单的题。

开始以为增长的方式是，前面或后面加一个()、或前后包围一对括号，但实际不是，可能是这种情况："((()))((()))", 必须每一个分配组合都要检查。本质上是O(n^3)的算法。TLE。

但实际上这道题只是一个符号串的线性分析，dp优先想，一维上有没有递推关系。

dp[i] 表示 以第i位为结尾的最长有效括号的长度。

在已知dp[0:i]后，我们计算dp[i]，如果s[i-1]为'('，则一定不会匹配，为0；如果为')'，看倒数第二位，若为'('，两者一定匹配，dp[i] = dp[i-2] + 2；如果为')'，则第i位可能将第i-1位所在的最长串与其前面相距1位的最长串连接起来，所以要检查，第i-1位前面的最长串前的字符是否为'('，如果是，则成功连接，dp[i] = dp[i-1-dp[i-1]-1] + dp[i-1] + 2, 如果不是，这个字符仍然是多余的，为0.

### stack

还需要认真体会思维过程。

遍历时，遇到'('则入栈（index），遇到')'则尝试更新结果。遇到')'的可能情况是

1. 没有人和它匹配。
2. 位置为i的括号和它匹配。

但要注意，和位置i匹配，不意味着长度就是j-i+1, 因为可能有(xxx)(xxx)的情况，是连续的。所以要维护起始点位置。

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        stack<int> st;
        int start=0, ans=0;
        for(int i=0; i<n; i++) {
            if(s[i] == '(') {
                st.push(i);
            } else { // ')'
                if(!st.empty()) {
                    st.pop();
                    if(st.empty()) { //  
                        ans = max(ans, i-start+1); // 没有top()，需要根据start计算
                    } else {
                        ans = max(ans, i-st.top()); // 此时top()是i对应左括号的前一个，做差直接得到两括号之间的字符数
                    }
                } else {
                    start = i+1; // 更新以i字符结尾的，可能子串的首字符位置
                }
            }
        }
        return ans;
    }
};
```

### 线性

```c++
class Solution {
public:
    // 线性扫描：
    // 有效括号序列的性质：所有“前缀和”>=0（'('=1, ')'=-1），且总和=0. 每一个右括号唯一确定左括号
    // 想象将原串对于所有有效括号序列、无效序列进行了划分。从左到右扫描，维护前缀和，等于0时更新数字，这种方式可以找到所有有效括号序列左侧不是'('的情况。恰相反，从右向左可以找到右侧不是‘)’的情况。

    // 如果原串是合法的，那么从左遍历或从右编译都是一次对；
    // 如果不合法，则对于每个有效序列，或者左边多一些括号，右边多一些括号；
    // 从左遍历可以找到右边多一些括号的情况；从右遍历正相反。
    int longestValidParentheses(string s) {
        int n = s.size();
        int start=0, sum=0, ans=0;
        for(int i=0; i<n; i++) {
            if(s[i] == '(') sum ++;
            else sum--;
            if(sum == 0) ans = max(ans, i-start+1);
            if(sum < 0) {
                start = i+1;
                sum = 0;
            }
        }
        int end = n-1;
        sum = 0;
        for(int i=n-1; i>=0; i--) {
            if(s[i] == ')') sum ++;
            else sum--;
            if(sum == 0) ans = max(ans, end-i+1);
            if(sum < 0) {
                end = i-1;
                sum = 0;
            }
        }
        return ans;
    }
};
```

## 62,63 不同路径

非降路径问题，没有障碍物时直接就是C_{m+n}^{n}

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        long res = 1;
        int i = min(m, n)-1;
        for(int x=m+n-2, y=1; i>0; i--) {
            res *= x--;
            res /= y++;
        }
        return res;
    }
};
```

使用int放res范围不够，但是除法只能从小变大，因为可能会除不尽。


有了障碍物，就要动态规划了；算是最经典的动态规划问题了。开始不想开一个新数组的，但是int放不下结果。

空间可以修成O(n);

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid[0][0] == 1) return 0;
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<vector<long>> dp(m, vector<long>(n, 0));
        dp[0][0] = 1;
        for(int i=1; i<m; i++) {
            if(obstacleGrid[i][0] == 1)
                dp[i][0] = 0;
            else 
                dp[i][0] = dp[i-1][0];
        }
        for(int i=1; i<n; i++) {
            if(obstacleGrid[0][i] == 1)
                dp[0][i] = 0;
            else 
                dp[0][i] = dp[0][i-1];
        }

        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                if(obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                    continue;
                }
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};
```

