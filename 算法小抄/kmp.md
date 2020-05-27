## Partial Match Table

复杂度与使用：使用PMT匹配，最坏的复杂度是2*strlen(txt)，情况如aaaabaaaab与aaaaa. 对于txt串中任意str(pat)长度的子串，经过2\*strlen(pat)步骤一定匹配完。可以看朴素算法与KMP对待`aaaab`与`aaaaa`的差别，朴素算法在发现`b`与`a`失配时，两个串上的指针都会回溯，导致了平方级别的复杂度；对于KMP算法，在目标串上的指针不会回溯，导致最多2倍的匹配次数！

我们用的next数组，是PMT向后移1位的结果。我们令next[0] = -1,表示在首部失配，目标串需要前进（目标串仅在匹配成功 或 完全无法匹配时前进）。

```cpp
int strStr(string haystack, string needle) {
	int m=haystack.size(), n=needle.size();
	if(n == 0) return 0;
	if(m == 0) return -1;
	vector<int> next(n+1, 0);  // 这里+1，因为PMT大小为n，向右移动一位；这样子next求的方便
	
	gen_next(needle, next);  // next[0] = -1 
	
	int i=0, j=0;
	while(i<m && j<n) {
		// j==-1时，就是pat首位失配，因而目标串也后移
		if(j == -1 || haystack[i] == needle[j]) {
			i++;
			j++;
		} else {  // 其他时候的失配，目标串不动
			j = next[j];  // 移动的位置，实际是最大partial match的下一位，因为存的是它的长度
		}
	}
	if( j < n ) return -1;  
	return i-j;  // 直接相减即可，因为i是end，j是长度
}
```

那么如何求next数组呢：我们要算模式串的每个后缀与其前缀最长的相同子串。其实就是错位的pat串进行匹配。

```cpp
void gen_next(string& pat, vector<int>& next) {
	next[0] = -1;
	int i=-1, j=0; // j看作目标串，即后缀
	while( j < pat.size()){
		if(i == -1 || pat[i] == pat[j]) {
			i++; j++;
			// 如果i==-1，正好就赋值为0了；其他情况，正好对应PMT向后移1位
			// 前缀索引对应match的长度，后缀索引就是next数组的索引
			next[j] = i; 
		} else {
			i = next[i];
		}
	}
}
```

## DP

对于一个模式串pat，使用输入串txt匹配它，在输入i个字符后，pat匹配的状态是已经确定的，再来一个输入字符，去向的转移状态也是确定的。

算法就是：对于一个输入，经过确定的运算步骤，得到确定的输出————所有算法（内状态不变）都可以看成状态机。

KMP的回退，只是在pat串上的回退，在目标串上永远是前进的。

KMP算法的核心是“部分匹配表”，对于模式串的前n个字符构成的子串，计算它的最长的相同的匹配的前缀与后缀。比如对于abab，前缀ab 与 后缀ab匹配，是最长的情况，为2，也就是partial match的长度为2。

求next数组，就是在求前n个字符的partial match的长度。其实是pat与pat的匹配。

我们用i，j分别作为后缀与前缀串的索引，我们移动后缀串，然后不断更新partial match的长度。

a b a b c
  a b a b c


```c
void getNext(char * p, int * next)
{
	next[0] = -1;
	int i = 0, j = -1;

	while (i < strlen(p))
	{
		if (j == -1 || p[i] == p[j]) 
        // 如果匹配成功，则记录已匹配的长度（j是后缀串的索引，其实就是长度）
		// i++,j++; 其实是前缀串与后缀串各增加一位的含义，它实际是被累计着的
        {
			++i;
			++j;
			next[i] = j;
		}	
		else
			j = next[j];  // 如果没有匹配上，用kmp的方法回去。j一定是小于i的。
	}
}
```