## 84. 柱形图中最大矩形面积

核心问题：找到每一个柱子左右第一个比它小的柱子，这是单调栈处理的典型问题。可以用严格递增的单调栈两个方向各找一次。

> 单调栈的操作是，保持栈中元素时单调的；对于每一个新的元素，和栈顶比较，如果栈顶更大（假设要找每个元素左边第一个比它小的元素），就pop掉，直到遇到小于的情况，记录（它的index，作为左边第一个比新元素小的），然后新元素入栈。（那些pop()掉的，是在新的更小的入栈元素左边的，并且更大；在右边的更多元素一定不会再考虑它）。

找左边第一个比它小的元素，也可以用类似dp的想法；每个元素的左边比它小，则没有，如果和它一样大，则dp[i-1]+1，如果比它大，+=dp[i-1]，并继续向前找。

### 只扫描一遍的单调栈

其实，在新元素i比栈顶小时，就已经可以确定[i]是栈顶右侧第一个小元素了。栈维护的，其实就是一个递增的序，栈顶第二个就是[i]左边第一个小的元素。

注意，下面维护的栈其实不是严格递增的，允许相同元素出现；但仍然可以保证正确性，因为相同元素会被连续出栈，最左侧的那个贡献出正确答案。

```c++
class Solution {
public:
    // 单调栈
    int largestRectangleArea(vector<int>& heights) {
        int m = heights.size();
        stack<int> st;
        st.push(-1); // 为了最后所有元素都可以很方便的出栈并计算宽度
        int res=0;
        int top;
        for(int i=0; i<m; i++) {
            // 注意，下面维护的栈其实不是严格递增的，允许相同元素连续出现；但仍然可以保证正确性，因为相同元素会被连续出栈，最左侧的那个贡献出正确答案。
            // 但不可以把相同元素丢弃，因为会影响“左侧第一个更小的元素”的位置
            // 可以丢弃左边的，保留右边的（因为左侧的都已经计算过了，并且对于相同的相邻元素，只有右侧的会有效）
            // if(st.top() >= 0 && heights[i] == heights[st.top()]) {
            //     st.pop();
            //     st.push(i);
            //     continue;
            // }
            while(st.top() >= 0 && heights[i] < heights[st.top()]){
                top = st.top();
                st.pop();
                int right = i;
                int left = st.top();
                // cout << top << " " << right << " " << left << endl;
                res = max(res, (right-left-1)*heights[top]);
            }
            st.push(i);
        }
        while(!st.empty()){
            int top = st.top();
            // cout << top << endl;
            if(top == -1)
                break;
            st.pop();
            res = max(res, heights[top] * (m-st.top()-1));
            // cout << heights[top] * (m-st.top()-1) << endl;
        }
        return res;
    }
};
```

### 暴力

有O(n^2)个柱子对，通过记录最矮的柱子，可以在计算每一个柱子对的复杂度为O(1)。但还是被卡掉了。

```c++
    int largestRectangleArea(vector<int>& heights) {
        int m = heights.size();
        int res = 0;
        for(int i=0; i<m; i++) {
            int min_val = INT_MAX;
            for(int j=i; j<m; j++) {
                min_val = min(min_val, heights[j]);
                res = max(res, min_val * (j-i+1));
            }
        }
        return res;
    }
```

### 分治

感觉不是很直观的分治，切分必须在最小的元素。

## 42. [接雨水 2D](https://www.acwing.com/solution/LeetCode/content/121/)

### 多次线性扫描（其实就是简单的动态规划形式）

开始考虑，要找到每个极小值区间。不对。

对于最终的水坑，每一个位置的深度决定于它左边最大的那个和右边最大的那个，这个为什么没想到呢QAQ。。

所以遍历两次，分别找每个位置左边最大与右边最大，最后再遍历一次得到解。（第三次遍历可以喝第二次扫描结合）。不过都是线性的嘛。

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int m = height.size();
        vector<int> lmax(m, 0);
        vector<int> rmax(m, 0);
        for(int i=1; i<m; i++) {
            lmax[i] = max(height[i-1], lmax[i-1]);
        }
        for(int i=m-2;i>=0;i--) {
            rmax[i] = max(height[i+1], rmax[i+1]);
        }
        int res=0;
        for(int i=1;i<m-1;i++) {
            int h = min(lmax[i], rmax[i]);
            // if(height[i] >= h) continue;
            res += max(h-height[i], 0);
        }
        return res;
    }
};
```

这个问题自己想了好久，。。开始也以为遍历可以的，想来想去又想不明白了，没有思考到核心问题，就是“决定每个位置水的高度的，究竟是什么？”；反而自己在想“每个水坑所在的区间是什么样子的”；思考的方式，思考对象的粒度要改变。


### 双指针收缩

空间复杂度可以进一步优化，变成O(1)；是3D算法的降维（这个应该是相似问题的通用思考方式）。

l左侧最高高度为lh，r右侧最高高度为rh，当l右移时，此时的h一定是lh：如果l的高度>h，没有影响； 如果 l < h，h一定是lh。（若是rh，那么一定有时刻l, rh两块是对应的，这不符合我的移动指针的规律。）

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int m=height.size();
        int l=0, r=m-1;
        int h=0;
        int res=0;
        while(l<r) {
            if(height[l] <= height[r]) {
                h=max(h, height[l++]);
                res+=max(h - height[l], 0);
            } else {
                h=max(h, height[r--]);
                res+=max(h- height[r], 0);
            }
        }
        return res;
    }
};
```

### 单调栈

这个比较符合自己最初的思路，但是头脑比较混乱。这个算法的核心是，将水划分成“行”。

我们知道左边第一个大的和右边第一个大的，也能得到正确解答。（遍历的方法要知道左右最大的）。

<!-- 维护一个递减栈，栈中维护的是U型区域的左右高，即栈中相邻两个元素代表一个U型区域。 -->

<!-- 每一次更新的时候，相当于找未计算的水的深度，每次更新一个矩形面积。 -->

<!-- 对于每个位置i，遍历经过它以后，我们计算完的是，它左侧，它的高度以下的水的多少。 -->

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int m = height.size();
        stack<int> st;
        int res=0;
        for(int i=0; i<m; i++) {
            if(st.empty()) {
                st.push(i);
                continue;
            }
            int top = st.top();
            while(height[top] < height[i]) {
                st.pop();
                if(st.empty()) break;
                int h = min(height[i], height[st.top()]);
                res += (i-st.top()-1)*(h-height[top]);              
                top = st.top();
            }
            st.push(i);
        }
        return res;
    }
};
```

### 407. trapping water 3D

2D 与 3D是完全不一样的了。2D中每个位置的水被2个块（1D）确定，3D中确是被“一个圈”（2D）确定（而非四个）。开始想要遍历四次，当然错了。

算法是逐步“缩小圈”；其实对应2D情景中的双指针算法（就是0空间的算法），只不过3D中有一圈指针而已。

> 用优先队列维护圈，每次取出最小的，根据它向内收缩（上下左右都要尝试，需要记录每个位置是否被访问过）；再维护一个变量（这个变量的正确性下面阐述），记录出队列的元素中最大的，作为更新res的height。
> 
> 对应的二维情景就是，左右两个指针向中间收缩，每次收缩的是更小的那个指针；同时维护一个收缩过的位置的最大高度，用于更新。
> 
> 正确性：需要用数学归纳法思考，我们称被拓展的新的块叫b，h高度的块叫a；注意，每一个拓展块，在拓展时，都对应那个时刻围墙的载水的下限；a比b矮，相当于此时围墙以外的所有块都比围墙要矮，此时更新 h = max(h, newh)是很自然的；如果a比b高，假设b拓自a（若干步的、间接的，不一定必须相连），b周围的点的上界是a很好理解；b非拓展自a，是不可能的，因为不可能先选b再选a（因为a比b大）
> 
> 意思是，可以证明 h 是和目前被拓展的块直接相关的约束高度。

自己的代码写的非常冗余，不好看。

提交leetcode，函数不能使用static变量，不同测试样例之间会有影响。（似乎可以用这个方法做坏事？因为程序可以知道此时是第几个测试样例。）

```c++
class Solution {
public:
    struct pos {
        pos(int x, int y, int h){
            this->x = x; this->y = y; this->h = h;
        }
        int x=0; 
        int y=0;
        int h=0;
    };
    struct cmp {
        bool operator()(pos p1, pos p2) {
            return p1.h > p2.h;
        }
    };
    int m,n;
    int h;
    void inline step(vector<vector<int>>& heightMap, vector<vector<bool>>& visited, priority_queue<pos, vector<pos>, cmp>& q, pos p, int &res){
        h=max(h, p.h);
        if(p.y-1 >= 0 && !visited[p.x][p.y-1]) {
            visited[p.x][p.y-1] = true;
            res += max(h-heightMap[p.x][p.y-1], 0);
            q.push(pos(p.x, p.y-1, heightMap[p.x][p.y-1]));
        } 
        if(p.y+1 < n && !visited[p.x][p.y+1]) {
            visited[p.x][p.y+1] = true;
            res += max(h-heightMap[p.x][p.y+1], 0);
            q.push(pos(p.x, p.y+1, heightMap[p.x][p.y+1]));
        }
        if(p.x-1 >= 0 && !visited[p.x-1][p.y]) {
            visited[p.x-1][p.y] = true;
            res += max(h-heightMap[p.x-1][p.y], 0);
            q.push(pos(p.x-1, p.y, heightMap[p.x-1][p.y]));
        } 
        if(p.x+1 < m && !visited[p.x+1][p.y]) {
            visited[p.x+1][p.y] = true;
            res += max(h-heightMap[p.x+1][p.y], 0);
            q.push(pos(p.x+1, p.y, heightMap[p.x+1][p.y]));
        }
    }

    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.size() <= 2) 
            return 0;
        m=heightMap.size(), n=heightMap[0].size();
        priority_queue<pos, vector<pos>, cmp> p;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int res=0;
        h=0;

        for(int i=0; i<m; i++) {
            visited[i][0] = visited[i][n-1] = true;
            p.push(pos(i, 0, heightMap[i][0]));
            p.push(pos(i, n-1, heightMap[i][n-1]));
        }
        for(int j=1; j<n-1; j++) {
            visited[0][j] = visited[m-1][j] = true;
            p.push(pos(0, j, heightMap[0][j]));
            p.push(pos(m-1, j, heightMap[m-1][j]));
        }
        while(!p.empty()) {
            pos P = p.top();
            p.pop();
            step(heightMap, visited, p, P, res);
            // cout << P.x<<" " <<P.y << " res: " << res << endl;
            // for(int i=0; i<m; i++) {
            //     for(int j=0; j<n; j++) {
            //         cout << visited[i][j] << " ";
            //     }
            //     cout << endl << endl;
            // }
        }
        return res;
    }
};
```





