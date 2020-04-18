# dual 22

做的题目多些，就会发现自己基础的薄弱。这周的两个场次，后面两道题都没有时间思考。

## 5348. [两个数组间的距离](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)

距离定义：数组一中，这样的元素i的数目：数组二中任何元素j都满足abs(i-j)>d.

排序自然好做。

> 中英文的题号似乎不一样

```c++
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int m=arr1.size(), n=arr2.size();
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        int res=0;
        for(int i=0, j=0;i<m && j<n;) {
            if(arr1[i] + d < arr2[j]) {
                i++;
                continue;
            }
            if(abs(arr1[i] - arr2[j]) <= d) {
                res++;
                i++;
                continue;
            }
            j++;
        }
        return m-res;
    }
};
```

## 5349. 安排电影院座位

没有什么特别思路，直接用的暴力；但发现自己连暴力都不会暴，思路不清楚。

由于预定座位是有限的，最高1e4，因而用map存储每个行的访问情况。其实遍历两次会比较清晰，用一个set去存这些行被预定的位置。

其中1、10不需要存，然后分别讨论情况每行（其实需要的是“被减去”的位置数）：

init: 2

1. 2345, xxxx -= 1
2. xxxx 6789 -= 1
3. xx 3456 xx && (not 0) -= 1

其他行都是满的, 2*n-count.

附赠一份我写的垃圾代码。要注意这种“译码”式问题的写法，与或非都可以用的.. 时间复杂度相同，多遍历一次也无所谓。

```c++
class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        map<int, int> rows;
        map<int, bool> _23;
        map<int, bool> _45;
        map<int, bool> _67;
        map<int, bool> _89;
        
        for(auto seat: reservedSeats) {
            int row = seat[0]-1;
            int col = seat[1];
            
            if(rows.find(row) == rows.end()) {
                rows[row] = 2;
                _23[row] = false;
                _45[row] = false;
                _67[row] = false;
                _89[row] = false;
            }
                
            if(rows[row] == 0) {continue;}
            if(col==1 || col==10) continue;
            if( col==2 || col==3 ) {
                if(_23[row]) continue;
                _23[row] = true;
                if(_45[row]) {continue;}
                if(!_67[row] && _89[row]) {continue;}
                rows[row]--;
                continue;
            }
            if( col==4 || col==5 ) {
                if(_45[row]) {continue;}
                _45[row] = true;
                if(rows[row] == 2) {rows[row]--; continue;}
                
                if(_23[row] && !_67[row] && !_89[row])
                    continue;
                rows[row]--;
                
                
            }
            if( col==6 || col==7 ) {
                if(_67[row]) {continue;}
                _67[row] = true;
                if(rows[row] == 2) {rows[row]--; continue;}
                if(!_23[row] && !_45[row] && _89[row] ) 
                    continue;
                rows[row]--;
                
            }
            if( col==8 || col == 9) {
                if(_89[row]) continue;
                _89[row] = true;
                if(_67[row]) {continue;}
                if(!_45[row] && _23[row]) {continue;}
                rows[row]--;
                continue;
            }
        }
        int res=2*n;
        for(auto i: rows) {
            res -= (2-i.second);
        }
        return res;
    }
};
```


## 5350. 将整数按权重排序

认为是一个数论题，自己，，诶，没有这方面知识。

每个数的权重就是，它按照“偶数/2, 奇数*3-1”这个规则最终变成0的次数。

看到了一个人写的题解，说记忆化，有点惊醒的感觉，我再想想。

一下子就简单很多了，因为范围只要1-1000. 但考虑时会想到，1000以外要不要记录呢、每一个数的计算过程中间见到的数字要记录吗..

最后发现，不记录每个数字中间的计算结果，效果就很好（从2开始往上加，逐个记录即可，不用保留路径上的数字），可能因为会更多击中比自己小的段吧。

记录中间结果也可以，但不要记录太多，会产生大量重复（比如前20个）。超过一千范围，重复击中某个值的概率变低，便没有必要记录了。

提取结果的时候需要保证排序的稳定性。

> 但其实还忽略了一个问题，万一有的数字超过2^32次呢，这里算了每个数字、万一有一个数组不可算呢。不过最大到达的数字是2e5左右，可能还好吧。其实没有当做数学问题去做了。

```c++
typedef pair<int, int> IIP;
class Solution {
public:
    vector<int> look_up_table;
    Solution(): look_up_table(1001, 0){
        look_up_table[1]=1;
        for(int i=2; i<1001; i++) {
            int j=i;
            int count=0;
            while(j>1000 || j<=1000 && look_up_table[j] == 0) {
                if(j%2 == 0) {
                    j/=2;
                } else {
                    j = 3*j+1;
                }
                count++;
            }
            count += look_up_table[j];
            look_up_table[i] = count;
        }
    }
    // int limit=20;
    // Solution(): look_up_table(1001, 0){
    //     look_up_table[1]=1;
    //     for(int i=2; i<1001; i++, limit--) {
    //         int j=i;
    //         int count=0;
    //         while(j>1000 || j<=1000 && look_up_table[j] == 0) {
    //             if(j%2 == 0) {
    //                 j/=2;
    //             } else {
    //                 j = 3*j+1;
    //             }
    //             count++;
    //         }
    //         count += look_up_table[j];
            
    //         look_up_table[i] = count;
    //         j=i;
    //         while(limit>0 && j!=1) {
    //             overall ++;
    //             count--;
    //             if(j%2 == 0) {
    //                 j/=2;
    //             } else {
    //                 j = 3*j+1;
    //             }
    //             if(j > 1000) {over++; continue;}
    //             look_up_table[j] = count;
    //         }
    //     }
    // }
    int getKth(int lo, int hi, int k) {
        vector<IIP> weights;
        for(int i=lo; i<=hi; i++) {
            weights.emplace_back(i, look_up_table[i]);
        }
        sort(weights.begin(), weights.end(), 
            [](const IIP & a, const IIP & b) -> bool
        { 
            if(a.second == b.second) {
                return a.first < b.first;
            }
            return a.second < b.second; 
        });
        // for(int i=0; i<weights.size(); i++) {
        //     cout << weights[i].first << " " << weights[i].second << endl;
        // }
        return weights[k-1].first;
    }
};
```

## 分比萨 TODO