# [House Robber 1/2/3](https://leetcode-cn.com/problems/house-robber/submissions/)

都比较简单（没有股票问题复杂），非常直接。

## 1

一排屋子，就是最简单的dp；每个房子抢或者被抢。

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        int m=nums.size();
        if(m==0) return 0;
        vector<vector<int>> dp(m, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = nums[0];
        for(int i=1; i<m; i++) {
            dp[i][0] = max(dp[i-1][1], dp[i-1][0]);
            dp[i][1] = dp[i-1][0] + nums[i];
        }
        return max(dp[m-1][0], dp[m-1][1]);
    }
};
```

可以用一维数组的方式思考，但自己感觉把思考粒度放到最细，思维负担比较轻，不用担心自己有疏漏。

## 2 

一个环型的屋子。其实就是枚举情况： 只考虑第一个屋子 或者 只考虑最后一个屋子。

于是运行两遍1的算法就好了。

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        int m=nums.size();
        if(m==0) return 0;
        if(m==1) return nums[0];
        vector<vector<int>> dp(m, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = nums[0];
        int res;
        for(int i=1; i<m-1; i++) {
            dp[i][0] = max(dp[i-1][1], dp[i-1][0]);
            dp[i][1] = dp[i-1][0] + nums[i];
        }
        res = max(dp[m-2][0], dp[m-2][1]); 
        
        dp[m-1][0] = 0;
        dp[m-1][1] = nums[m-1];
        for(int i=m-2; i>0; i--) {
            dp[i][0] = max(dp[i+1][1], dp[i+1][0]);
            dp[i][1] = dp[i+1][0] + nums[i];
        }
        return max(res, max(dp[1][0], dp[1][1]));
    }
};
```

## 3

树型的，其实一样。前面的dp其实都可以优化为常量的，每一个房间之和前面的一个有关系。树也是如此，父亲只与孩子有关系；所以孩子的状态直接递归的就可以传递上去。

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

    void helper(TreeNode* root, int& rob, int& nrob) {
        if(root == NULL) {
            rob = 0;
            nrob = 0;
            return;
        }
        int lrob, lnrob, rrob, rnrob;
        helper(root->left, lrob, lnrob);
        helper(root->right, rrob, rnrob);
        rob = lnrob + rnrob + root->val;
        nrob = max(lrob, lnrob) + max(rrob, rnrob);
        return;
    }

    int rob(TreeNode* root) {
        int rob, nrob;
        helper(root, rob, nrob);
        return max(rob, nrob);
    }
};
```
