## 440 寻找字典序第k小的数字

昨天实在是太困了QAQ。想不明白，直接按照题解写的。

很直观，字典序呈现一个树的结构。有两种操作：增加深度、向右移动（此处注意，9其实并不特别）。我们就是要通过这两个操作定位目标排名。

前缀串即从树根到某个中间点的路径，目标是逐渐增加前缀串位数。其实就是不断确定是否在一棵子树（从最左上开始），如果不在，向右移动，如果在，向下移动。因而需要计算一棵子树的大小。移动前缀的过程中，要注意排名的变化，向下移动，排名+1，向右移动，排名+子树的大小。

所以最最关键就是算子树的大小。方法是每一层一算，用上界-下界。加入我的前缀串是`xxx1`，那么我的上界串是`xxx2`，前缀串不断变长，上界串也不断变长。`xxx20..0 - xxx10..0`。

```c++
class Solution {
public:
    int getNumber(long prefix, long n) {
        long count=0;
        // next表示了这棵子树的最上界，n+1也同时限制上界
        // 对于前缀，它的上界 next 只需往后不断填0
        for(long cur = prefix, next = prefix + 1; cur <= n; cur*=10, next*=10) {
            count += min(next, n+1) - cur; // 关键就是这一句
        }
        return count;
    }
    int findKthNumber(int n, int k) {
        int p = 1; // 记录排名
        int prefix = 1; 
        while(p < k) {
            int count = getNumber(prefix, n); // 找一棵子树的大小
            if(p + count > k) { // 如果在这棵树下
                prefix *= 10; // 向下移动一层
                p++; // 向下移动一层，其实排名是增加1
            } else { // 如果不在这棵子树下
                prefix ++;  // 移动一个兄弟节点
                p += count; // 向右移动节点，排名其实移动子树的大爱小
            }
        }
        return prefix;
    }
};
```