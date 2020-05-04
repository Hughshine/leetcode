## Nim Game

## Stone Game

### 标准的dp解法

考虑dp算法时，全部用最简化最直接的方式构造状态与转移过程。比如在这个问题里，我们令dp[i][j]为选择[i...j]堆石头时的状态，状态为（先手的最高分数，后手的最高分数）。最终的解以dp[0][k-1].fir与sec的差值是否大于0做判断。

考虑状态转移的过程。“先手”实际是相对的。任何一方的一次选择就是一次状态转移。不过我们仍以回合制考虑，对于dp[i][j]，如果先手方选择了第i个，后手方其实是作为子问题的先手方！


状态转移方程就很好想了。一般斜着扩增数组时，我习惯还是以行的形式开始，从倒数第一行推到第一行。（缓存的一致性也好一点，也不复杂）。

```cpp
typedef pair<int, int> PII;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int k = piles.size();
        vector<vector<PII>> dp(k, vector<PII>(k, PII(0, 0)));
        for(int i=0; i<k; i++) {
            dp[i][i].first = piles[i];
            dp[i][i].second = 0;
        }
        for(int i=k-2; i>=0; i--) {
            for(int j=i+1; j<k; j++) {
                int choose_left = piles[i]+dp[i+1][j].second;
                int choose_right =  piles[j]+dp[i][j-1].second;
                if(choose_left >= choose_right) {
                    dp[i][j].first = choose_left;
                    dp[i][j].second = dp[i+1][j].first; 
                } else {
                    dp[i][j].first = choose_right;
                    dp[i][j].second = dp[i][j-1].first;
                }
                
            }
        }
        // for(int i=0; i<k; i++) {
        //     for(int j=0; j<k; j++) {
        //         cout << "(" << dp[i][j].first << "," << dp[i][j].second << ") ";
        //     }
        //     cout << endl;
        // }
        return dp[0][k-1].first > dp[0][k-1].second;
    }
}; 
```