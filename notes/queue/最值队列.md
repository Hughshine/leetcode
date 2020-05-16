## 面试题59-II 设计可以快速找到最大值的队列

首先队列支持普通的push, pop操作,再加上查询最大值,三个操作都要求是O(1)的时间. 开始怎么也想不到有什么方法让三个复杂度都是常数的. 原来,时间复杂度要考虑"均摊"的复杂度, 可能某一次操作直接达到了O(N), 但是全局的角度, 复杂度其实很低, 可能全局的复杂度只依赖于某一次单一的操作.

做这道题时,直接想到昨天看的LFU算法的实现, 通过map定位结点, 结点同时处于一个增序的链表(可以认为是二维的)中, 增加访问次数时尝试向后调整, 删除时删掉头结点. 开始我想这道题也要维护一个类似的增序链表, 但是插入的时候找位置时一定的O(N)的. 

现在去想,两道题的约束其实不同,LFU的数据特点完全由LFU算法本身决定,这个算法实际是,新节点放队头,旧结点相邻移动,只删除队头结点,这样的一个算法,所以map+list. 但是本题的数学特性完全来自于队列本身,可以想象,在随机访问的数组中,max就是O(n)的. 所以要去想队列在push/pop过程中最大值的变化关系. 当然很好理解需要两个数据结构,其中一个仍然是queue,但另一个是什么需要思考.

新放入的值如果很大,那么前面的所有比他小的值,取到的最大值都是他,除非再前面有比他更大的值.诶,这不是很类似单调栈的思路吗,只不过此时变成了队列而已.

在来了新的元素时,我们要从后面找到第一个比它大的,中间全部丢掉;在pop时,还要从前面删除;显然这是一个双端队列.

还有一处要想,我们用什么方式知道,普通队列pop的时候,双端队列也要pop? 其实只需要判断值是否相等即可(连续的相同元素,要全部保存在双端队列中).

```c++
class MaxQueue {
public:
    queue<int> q;
    deque<int> dq;

    MaxQueue() {
    }
    
    int max_value() {
        return dq.empty()?-1:dq.front();
    }
    
    void push_back(int value) {
        q.push(value);
        while(!dq.empty() && dq.back() < value) {
            dq.pop_back();
        }
        dq.push_back(value);
    }
    
    int pop_front() {
        if(q.empty()) return -1;
        int val = q.front();
        if(val == dq.front()) {
            q.pop();
            dq.pop_front();
        } else {
            q.pop();
        }
        return val;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
```

## 239. 滑动窗口最大值

单调队列就是所谓的最大值队列，竟然没有意识到以前做过，我的天。

```cpp
class MonotonicQueue {
public:
    void push(int n) {
        nq.push(n);
        while(!q.empty() && q.back() < n) {
            q.pop_back();
        }
        q.push_back(n);
    }
    int max() {
        return q.front();
    }
    void pop() {
        if(q.front() == nq.front()) {
            q.pop_front();
            nq.pop();
        } else {
            nq.pop();
        }
    }
    deque<int> q;
    queue<int> nq;
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // 优先队列不行：pop掉的是位置最前的
        MonotonicQueue q;
        int m = nums.size();
        // 如何维护一个队列的最大值
        vector<int> result;
        for(int i=0; i<m; i++) {
            if(i < k-1) {
                q.push(nums[i]);
            }
            else {
                q.push(nums[i]);
                result.emplace_back(q.max());
                q.pop();
            }
        }
        return result;
    }
};
```