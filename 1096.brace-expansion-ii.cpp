/*
 * @lc app=leetcode id=1096 lang=cpp
 *
 * [1096] Brace Expansion II
 *
 * https://leetcode.com/problems/brace-expansion-ii/description/
 *
 * algorithms
 * Hard (61.43%)
 * Likes:    148
 * Dislikes: 103
 * Total Accepted:    8.5K
 * Total Submissions: 13.9K
 * Testcase Example:  '"{a,b}{c,{d,e}}"\r'
 *
 * Under a grammar given below, strings can represent a set of lowercase
 * words.  Let's use R(expr) to denote the set of words the expression
 * represents.
 * 
 * Grammar can best be understood through simple examples:
 * 
 * 
 * Single letters represent a singleton set containing that word.
 * 
 * R("a") = {"a"}
 * R("w") = {"w"}
 * 
 * 
 * When we take a comma delimited list of 2 or more expressions, we take the
 * union of possibilities.
 * 
 * R("{a,b,c}") = {"a","b","c"}
 * R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each
 * word at most once)
 * 
 * 
 * When we concatenate two expressions, we take the set of possible
 * concatenations between two words where the first word comes from the first
 * expression and the second word comes from the second
 * expression.
 * 
 * R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
 * R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg",
 * "acdfh", "acefg", "acefh"}
 * 
 * 
 * 
 * 
 * Formally, the 3 rules for our grammar:
 * 
 * 
 * For every lowercase letter x, we have R(x) = {x}
 * For expressions e_1, e_2, ... , e_k with k >= 2, we have R({e_1,e_2,...}) =
 * R(e_1) ∪ R(e_2) ∪ ...
 * For expressions e_1 and e_2, we have R(e_1 + e_2) = {a + b for (a, b) in
 * R(e_1) × R(e_2)}, where + denotes concatenation, and × denotes the cartesian
 * product.
 * 
 * 
 * Given an expression representing a set of words under the given grammar,
 * return the sorted list of words that the expression represents.
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "{a,b}{c,{d,e}}"
 * Output: ["ac","ad","ae","bc","bd","be"]
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "{{a,z},a{b,c},{ab,z}}"
 * Output: ["a","ab","ac","z"]
 * Explanation: Each distinct word is written only once in the final
 * answer.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= expression.length <= 60
 * expression[i] consists of '{', '}', ','or lowercase English letters.
 * The given expression represents a set of words based on the grammar given in
 * the description.
 * 
 * 
 * 
 * 
 */

// @lc code=start
/*
 * 速度慢，可能是集合操作复杂度高些？不清楚TwT。
 * 0. 应先分析一下这个文法，
 * 1. 先确定递归粒度。
 * 2. 把递归重点情况写好，运算写好
 * 注. 不知道怎么就对了，发现和自己最初想的不一样TwT
 * 这个代码很弱。
 */
class Solution {
public:
    int end;

    string get_word(string& expression, int& pos) {
        string result;
        while('a' <= expression[pos] && expression[pos] <= 'z') {
            result += expression[pos++];
        }
        return result;
    }

    void set_union(set<string>& set1, set<string> set2){ // insert into set1
        for(auto& s : set2) {
            set1.insert(s);
        }
    }

    void set_multiply(set<string>& set1, set<string> set2) {
        set<string> set;
        string s;
        for(auto& s1: set1) {
            for (auto& s2: set2) {
                s = s1 + s2;
                set.insert(s);
            }
        }
        swap(set1, set);
    }

    // 计算一次 笛卡尔积所在的优先级 
    // 对于 {a, {b,c}{d,e}}，a是在{b,c}{d,e}上两层（递归层数）的
    set<string> get_set(string& expression, int& pos) { 
        set<string> s = {""}; // 用于记录最终的set
        while(pos<end && expression[pos]!='}') { // 遇到紧邻的右括号，到达递归终点
            switch (expression[pos]) {
            case '{': // 如果计算完的部分的后面，紧跟着 '{'，需要计算笛卡尔积（递归），运算结果与算完的部分做笛卡尔积。这里没有优先级的问题
                pos++;
                set_multiply(s, get_set(expression, pos));
                pos++; // 算完了，跳过 '}'，要lookahead一位
                break;
            case ',': // 对于',' 递归计算（）后，取交集
                pos++;
                set_union(s, get_set(expression, pos)); //这里的get_set() 体现了优先级，先算笛卡尔积。
                break;
            default:
                set_multiply(s, set<string>({get_word(expression, pos)}));
                break;
            }
        }
        cout << "** set " << endl;
        cout << "pos: " << pos << " expr[pos]: " << expression[pos] << endl;
        for(auto& str:s) cout << str << " ";
        cout << "\n** end \n";
        return s;
    }

    vector<string> braceExpansionII(string expression) { // 本题目，实际相当于额外隐藏了一对 {}， 即应是在解析 '{' + expression + '}'
        int pos = 0;
        end = expression.length(); // 最右侧 " 所在位置 
        set<string> res_set = {""};
        set_multiply(res_set, get_set(expression, pos));
        return vector<string>(res_set.begin(), res_set.end());
    }
};
// @lc code=end
// {{a,z},a{b,c},{ab,z}}
"{a,{b,c}{d,e},f}"