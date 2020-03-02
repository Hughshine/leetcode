## 23 合并k个有序列表

方法：原地归并。在lists中推入NULL节点保证有偶数（m）个list，n=m/2，每次将第i个与第i+n个合并。合并的时候，将后面的list插入到前面的list。

平均时间复杂度O(Nlogk)，大概是log(k)次n长度（平均列表长度）列表的合并。最高复杂度不会过分的坏。空间复杂度为O(1)。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 归并着排序
        int m = lists.size();
        if(m == 0) return NULL;
        if(m == 1) return lists[0];
        if(m%2 == 1) {
            lists.push_back(NULL);
            m+=1;
        }
        int n = m/2;
        while(true) {
            // cout << n << endl;
            for(int i=0; i<n; i++) { 
                ListNode* node1 = lists[i];
                ListNode* node2 = lists[i+n];
                ListNode* former1 = NULL;
                if(node1 == NULL) {
                    lists[i] = node2;
                    continue;
                } 
                if(node2 == NULL) {
                    continue;
                }
                while(node1 != NULL && node2 != NULL) {
                    if(node1->val < node2->val) {
                        former1 = node1;
                        node1 = node1->next;
                    } else {
                        // insert node2 before node1
                        ListNode* tmp2 = node2;
                        node2 = node2->next;
                        if(former1 == NULL) {
                            tmp2->next = node1;
                            lists[i] = tmp2;
                            former1 = tmp2;
                        } else {
                            former1->next=tmp2;
                            tmp2->next=node1;
                            former1 = tmp2;
                        } 
                    }
                }
                while(node2 != NULL) {
                    former1->next = node2;
                    former1 = node2;
                    node2 = node2->next;
                }
            }
            if(n==1) break;
            if(n%2 != 0) {
                lists[n] = NULL;
                n = n/2 + 1;
            }  else {
                n = n/2;
            }
        }
        return lists[0];
    }
};
```