翻转：栈/尾插

## 栈

不写用栈完成功能的代码了，用栈还是用空间的吧QAQ，虽然也可以一个一取。。。

## 尾插

尾插是一个不错的将单向链表弄成倒序的一个逻辑：找到首和尾，不断将首部拆开作为尾的next，

加一个链表头会使链表调整的逻辑变的舒服。

还是有其他变更逻辑是正确的，但是不好调，思路不直接。

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k <= 1) return head;
        ListNode dummy(0);
        ListNode *former = &dummy;
        ListNode *first=head, *end=head;
        for(int i=0; i<k-1; i++) {
            end = end->next;
            if(end == NULL) return head;
        }
        while(true) {
            ListNode* cur = first;
            ListNode* next_start = end->next;
            while(cur != end) {
                ListNode* tmp = cur->next;
                cur->next = end->next;
                end->next = cur;
                cur = tmp;
            }
            former->next = end;
            former = first;
            if(next_start == NULL) return dummy.next;
            first = end = next_start;
            for(int i=0; i<k-1; i++) {
                end = end->next;
                if(end == NULL) return dummy.next;
            }    
        }
        return dummy.next;
    }
};
```