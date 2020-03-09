# 双周赛 21

第二题很有意思，根本不是medium的难度好嘛QAQ，没有做过类似的题。

中国版leetcode做的不够好，竞赛题目都没有在题库同步，解答也不如英文版。

### 1370. 上升下降字符串 easy str 

描述：将一个字符串中字符按字典序 严格递增再递减再递增再递减... 形成一个新的字符串。

方法：计数 + 遍历，不想作任何优化，反正都是O(n)的。

```c++
class Solution {
public:
    string sortString(string s) {
        unordered_map<char, int> count;
        int char_count=0;
        string res;
        for(int i=0; i<s.size(); i++) {
            if(count[s[i]]++ == 0) {
                char_count++;
            }
        }
        
        while(char_count!=0) {
            for(char ch='a'; ch<='z';ch++) {
                if(count[ch] != 0) {
                    res += ch; 
                    if(--count[ch] == 0) {
                        char_count--;
                    }
                }    
            }
            for(char ch='z'; ch>='a'; ch--) {
                if(count[ch] != 0) {
                    res += ch;
                    if(--count[ch] == 0) {
                        char_count--;
                    }
                }
            }
        }
        return res;
    }
};
```

### 1372 [二叉树中最长交错路径](https://leetcode-cn.com/problems/longest-zigzag-path-in-a-binary-tree/) tree dfs 

描述：交错路径就是`l, r, l, r, ...` 或者是 `r, l, r, l, ...`的一个路径。

很清晰的dfs的思路，每个节点计算左最长交错与又最长交错，逐次传递到上面。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int _max = 0;
    void dfs(TreeNode* root, int& l, int& r) {
        int ll, rr;
        if(root->left == nullptr) {
            l = 0;
        } else {
            dfs(root->left, ll, rr);
            l = rr+1;
            if(l > _max) {
                _max = l;
            }
        }
        if(root->right == nullptr) {
            r = 0;
        } else {
            dfs(root->right, ll, rr);
            r = ll+1;
            if(r > _max) {
                _max = r;
            }
        }
        return;
    }
    
    int longestZigZag(TreeNode* root) {
        _max = 0;
        int l=0, r=0;
        dfs(root, l, r);
        // int res = max(l, r);
        return _max;
    }
};
```

### 1373 [二叉搜索子树的最大键值和](https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/) tree dfs hard(蛮简单的)

描述： 找到一棵二叉树的所以BFS子树中 最大的键值和

其实也是很简单的dfs... 

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int _max;
    inline int get_left_val(TreeNode* node){
        if(node == NULL) 
            return INT_MIN;
        else 
            return node->val;
    }
    
    inline int get_right_val(TreeNode* node){
        if(node == NULL) 
            return INT_MAX;
        else 
            return node->val;
    }
    
    void dfs(TreeNode* root, bool& is_bst, int& sum) {
        if(root == nullptr) {
            is_bst=true;
            sum=0;
            return;
        }
        
        bool l, r;
        int lsum=0, rsum=0;
        dfs(root->left, l, lsum);
        dfs(root->right, r, rsum);
        if(l == true && r == true) {
            if(get_left_val(root->left) < root->val && get_right_val(root->right) > root->val) {
                is_bst = true;
                sum += lsum + rsum + root->val;
                _max = max(sum, _max);
                return;
            }
            sum = 0;
            is_bst = false;
        } else {
            is_bst=false;
            sum=0;
        }
    }
    int maxSumBST(TreeNode* root) {
        bool root_is_bst=false;
        int sum=0;
        dfs(root, root_is_bst, sum);
        return max(_max, sum);
    }
};
```

### 1371 找到字符串中元音个数为偶数的子串长度 string, status, HARD!!

这道题其实很难，标了一个medium。。

开始想用dp做，直接写了一个O(n^2)的dp，TLE，显然一维的字符串不需要二维的dp，没有长记性。

```c++
// O(n^2)dp
class Solution {
public:
    struct Status {
        bool a,e,i,o,u;
        Status() {
            a=e=i=o=u=false;
        }
        Status& operator=(const Status& s) {
            this->a = s.a;
            this->e = s.e;
            this->i = s.i;
            this->o = s.o;
            this->u = s.u;
            return *this;
        }
    };
    
    void print_status(Status& s) {
        cout << s.a << " " << s.e << " " << s.i << " " << s.o << " " << s.u << endl;
    }
    
    inline bool is_valid(Status& s) {
        return !(s.a || s.e || s.i || s.o || s.u);
    }
    
    inline bool is_vowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }
    
    inline void set_status(Status& s, char ch) {
        switch(ch) {
            case 'a':
                s.a = !s.a;
                break;
            case 'e':
                s.e = !s.e;
                break;
            case 'i':
                s.i = !s.i;
                break;
            case 'o':
                s.o = !s.o;
                break;
            case 'u':
                s.u = !s.u;
                break;
            default:
                // cout << "something wrong" << endl;
                break;
        }
    }
    
    int findTheLongestSubstring(string str) {
        int m=str.size();
        int res=0;
        vector<vector<Status>> status(m, vector<Status>(m));
        for(int i=0; i<m; i++) {
            if(is_vowel(str[i])) {
                set_status(status[i][i], str[i]);
            }else {
                res=1;
            } 
        }
        
        for(int i=1; i<m; i++) { // diff
            for(int st=0, e=st+i; e<m; st++, e++) { // 
                status[st][e] = status[st][e-1];
                set_status(status[st][e], str[e]);
                if(is_valid(status[st][e])) {
                    res = max(res, e-st+1);
                }
            }
        }
        return res;
        
    }
};
```

然后突然想到，这不是和`最长括号匹配`很像嘛，于是又撸O(n)的dp。dp[i]表示以i为结尾的最长满足题意的子字符串。

数据依赖是：

1. s[i]不是元音，直接s[i-1]+1
2. s[i]是元音，找到s[former]，former为s[i-1]匹配串的前一位
   * 和dp[i-1-dp[i-1]]匹配，匹配上，则可以连接前面的串
   * 不过匹配补上，和s[former+1]匹配，匹配上，保持不变

但其实是不对的，关键在于匹配是有“5组”的，字符串中的元音匹配序列可能是交叉的！如`ixxxoxxxixxxo`，而以这种方法找到的former，只能是相邻的，完全没有考虑交叉的情况。

正确答案是对“状态”进行跟踪！状态即是元音出现的一个表示，相同状态的第二（或更多）次出现，意味着和之前出现的位置是匹配的。本题的状态是`2**5`，我们遍历一次字符串，每次遇到元音，更新状态，如果以前出现过这个状态，按照第一次出现的位置更新最大距离。妙呀。

```c++
class Solution {
public:    
    int findTheLongestSubstring(string s) {
        map<int,int> m;
        m[0]=-1;
        string vowel = "aeiou";
        int mask=0,res(0);
        for(int i=0;i<s.size();i++)
        {
            for(int j=0;j<5;j++)
            {
                if(s[i]==vowel[j])
                {                  
                   mask = mask^(1<<j); 
                   break;
                }                                          
            }            
            if(m.find(mask)==m.end())
            {
                m[mask]=i;
            }
            res=max(res,i-m[mask]);            
        }
        return res;
    }
};
```

对于括号匹配，能否用类似方法呢？比较麻烦，因为左括号和右括号不是等价的，不是遇到两次相同的状态就是可行解（如果状态设计为`{`个数与`}`个数两者），可能还需要维护前缀和，状态数也是非线性的。
