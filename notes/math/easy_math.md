## 3. 找两个有序数组的中位数

不喜欢有许多特殊情况的算法题。不过分开写这道题也还好吧。

核心问题：找到第k大数字的算法。为什么转换成第k大的呢，因为“中位数”其实是很人为的数学定义，在偶数奇数是一定要分开算的。

二分是根据“k”做二分的，搜索空间就是两个数组的各自前k个数。这种递归都怎么方便怎么来，注意递归终点的情景。

```c++
class Solution {
public:
    int inline findKth(vector<int>& nums1, vector<int>& nums2, int s1, int e1, int s2, int e2, int k){
        // cout << s1 << " " << e1 << ", " << s2 << " " << e2 << ", " << k << endl; 
        if(e1 < s1) {
            return nums2[s2+k-1];
        } else if(e2 < s2) {
            return nums1[s1+k-1];
        }
        if(k==1) return (nums1[s1]<=nums2[s2])?nums1[s1]:nums2[s2];

        int mid1 = min(e1, s1+k/2 - 1), mid2 = min(e2, s2+k/2 - 1);
        // cout << mid1 << " " << mid2 << endl;
        if(nums1[mid1] <= nums2[mid2]) {
            return findKth(nums1, nums2, mid1+1, e1, s2, e2, k-mid1+s1-1);
        } else {
            return findKth(nums1, nums2, s1, e1, mid2+1, e2, k-mid2+s2-1);
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m=nums1.size(), n=nums2.size();
        int k=m+n;
        if((k)%2 == 0) {
            int kth = findKth(nums1, nums2, 0, m-1, 0, n-1, k/2);
            int k1th = findKth(nums1, nums2, 0, m-1, 0, n-1, k/2+1);
            // cout << kth << " " << k1th << endl;
            return ((double)kth+k1th)/2;
        } else {
            int kth = findKth(nums1, nums2, 0, m-1, 0, n-1, k/2+1);
            // cout << kth << endl;
            return kth;
        }
    }
};
```

## 面试题57-II 和为s的连续正数序列 easy

没有思考过，不是很好做。数学问题要想一想参数之间的依赖关系，可能会很简化。

一个连续区间实际由起点与终点，或起点与向量长度表示；我们希望区间的数值和为target，可以由等差数列公式计算。区间数其实时很多的，但反过来，我们能否去尝试寻找所有可能的起点呢？

长度为i时，根据target，我们能算出相应的x，我们检查x是否为整数(每个i对应的x是唯一的)。如此，遍历i，即可得到一个线性算法。


```c++
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;
        int t=target;
        for(int i=1; i<t ;i++) {
            if((2*t)%(i+1)!=0) continue;
            int t1 = 2*t /(i+1);
            // cout << t1 << " ";
            if(t1-i < 2) break;
            int t2 = t1-i;
            // cout << t2 << " ";
            if(t2%2!=0) continue;
            int x = t2/2;
            // cout << x << " " << i << endl;
            vector<int> v(i+1);
            for(int j=0;j<i+1;j++) {
                v[j] = x;
                x++;
            }
            res.push_back(v);
        }
        vector<vector<int>> rres(res.size());
        int i=0;
        for(auto iter=res.rbegin(); iter!=res.rend(); iter++, i++) {
            rres[i] = *iter;
        }
        return rres;
    }
};
```

最后的reverse不好看.可能因为第二层的数组长度不确定，不能直接使用`std::reverse`?