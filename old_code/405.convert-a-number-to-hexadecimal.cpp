/*
 * @lc app=leetcode id=405 lang=cpp
 *
 * [405] Convert a Number to Hexadecimal
 */

// @lc code=start
class Solution {
public:
    char table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    long max = 4294967295;
    string toHex(long num) {
        if (num < 0)
            num = max + num + 1;
        if (num == 0)
            return "0";
        string res;
        while (num != 0) // 如果一定要8位，可以增加一个计数。
        {
            int mod = num % 16;
            num = num >> 4;
            res = table[mod] + res;
        }
        return res;
    }
};
// @lc code=end

