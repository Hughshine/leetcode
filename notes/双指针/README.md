# 双指针

## 快慢指针

1. 判断链表中的环

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow, *fast;
        slow = fast = head;
        while(fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) return true;
        }
        return false;
    }
};
```

找到环的起点：相遇点距离环的起始点，就是再走已经走过的步数的距离，把fast放到头，慢速一起走，直到相交即可。142. 环形链表 II

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow, *fast;
        slow = fast = head;
        while(fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) {
                fast = head;
                while(fast != slow) {
                    fast = fast->next;
                    slow = slow->next;
                }
                return fast;
            }
        }
        return NULL;
    }
};
```

2. 找中间结点

```cpp
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *slow, *fast;
        slow = fast = head;
        while(fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        } 
        return slow;
    }
};
```

3. 找到倒数第k个元素（另，加一个preheader很好用）

```cpp
// 19. 删除链表的倒数第N个节点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *slow, *fast;
        slow = fast = head;
        ListNode dummy = ListNode(0);
        dummy.next = head;
        ListNode* former = &dummy;

        while(n--) {
            fast = fast->next;
        } 
        while(fast != NULL) {
            fast = fast->next;
            slow = slow->next;
            former = former->next;
        }

        former->next = slow->next;
        delete slow;
        return dummy.next;
    }
};
```

4. 找到相交链表的交点：“互补”。需要一点点思路。

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* pntA = headA, *pntB = headB;
        if(pntA == NULL || pntB == NULL) {
            return NULL;
        }
        while(pntA != pntB) {
            pntA = pntA ? pntA->next : headB;
            pntB = pntB ? pntB->next : headA;
        }
        return pntA;
    }
};
```

## 左右指针

1. 二分查找

2. 有序数组的“两数之和”

3. 反转数组

## 135. 分糖果

第一想法是，要找在严格单增、单减区间的排名，取两者最大值。

想在一次遍历中做两件事很麻烦，所以分别找，双向遍历。也不需要真正记录区间。

算法时间O(n), 空间复杂度O(n)。其实我觉得，空间在O(n)一般就很好啦，优化工作可以放在以后。。

可以发现，每个孩子所受影响的范围并不是全局的，只是左边最小的和右边最小的之间（这个角度和2D接雨水有点像，它希望找到左边最高的和右边最高的，不过两者数据依赖关系是不一致的），如此可以考虑设计O(1)的算法。

```c++
class Solution {
public:
    // 找到严格单增、单减区间，每个位置被它所处的两个区间所限制
    int candy(vector<int>& ratings) {
        int m = ratings.size();
        vector<int> left(m, 1);
        vector<int> right(m, 1);
        for(int i=1; i<m; i++) {
            if(ratings[i] > ratings[i-1] ) {
                left[i] = left[i-1] + 1;
            }
        }
        for(int i=m-2; i>=0; i--) {
            if(ratings[i] > ratings[i+1] ) {
                right[i] = right[i+1] + 1;
            }
        }
        int res=0;
        for(int i=0; i<m; i++) {
            res += max(left[i], right[i]);
        }   
        return res;
    }
};
```

### 空间继续降低

实际上，我们每经过一座山，就可以计算这一座山需要的糖果了；且只需要记录这座山的两个属性：上山坡的长度与下山坡的长度（水平长度），通过(1+h)*h/2即可计算。

讨厌的地方是，山脚这个点要小心处理，两个数值相等时发生的情况也要小心处理。

```c++
class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size() < 2) return ratings.size();
        int m = ratings.size();
        int lc=0, rc=0;
        bool up = ratings[0] <= ratings[1];
        int up_count=0, down_count=0;
        int res=0;
        for(int i=1; i<m; i++) {
            if(up && ratings[i] > ratings[i-1]) { 
                up_count++;
            }
            else if(!up && ratings[i] < ratings[i-1]) {
                down_count++;
            }
            else {
                up = !up;
                if(up) { // 已经跨过了一座山，核算, 总是少算右侧山脚处的一个1（因为两座山经常会共用山脚）
                    res += (1+up_count)*up_count/2 + (1+down_count)*down_count/2 + max(up_count, down_count);
                    if(ratings[i] == ratings[i-1]) { // 如果是等于的情况（两座山不共用山脚），把左边少的1加上。位置i是新的山脚。如 1 2 1 1
                        res+=1;
                        up_count = 0;
                        down_count = 0;
                    } else { // 否则，我将每一处山脚都当做是属于右边的山
                        up_count = 1;
                        down_count = 0;
                    }
                } else {
                    if(ratings[i] == ratings[i-1]) {  // 遇到了等于情况，宣告左边的山没有下山坡，直接计算
                        down_count = 0;
                        res += (1+up_count)*up_count/2 + (1+down_count)*down_count/2 + max(up_count, down_count) + 1;
                        up = !up;
                        up_count = 0;
                    }
                    else {
                        down_count = 1;
                    }
                }
            }
        }
        res += (1+up_count)*up_count/2 + (1+down_count)*down_count/2 + max(up_count, down_count) + 1;
        return res;
    }
};
```