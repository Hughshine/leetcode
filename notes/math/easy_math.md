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