#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    int n = 7;
    vector<vector<int>> dp(n+1, vector<int>(4, 0));
    // 状态还需要包含剪切板的字符数  
    // 第i步，输出的字符数，剪切板的字符数
    // base: 都是零
    for(int i=1; i<=n; i++) {  // 可以通过堆问题数据结构更详尽的了解，找更好的转移方程
        dp[i][0] = max(dp[i-1][0], dp[i-1][3]) + 1;
        dp[i][1] = max(dp[i-1][0], dp[i-1][3]);
        dp[i][2] = dp[i][1];
        dp[i][3] = MAX(dp[0...i][2].first+copy);
    }
    cout << max(dp[n][0], dp[n][3]) << endl;
}


// 需要总结基本数据结构的使用，比如优先队列
// 引用什么头文件