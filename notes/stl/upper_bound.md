注意`upper_bound`用法，传入lambda很方便；注意lambda的参数顺序，以及语义（我们要用这个函数找strict upper bound）
```c++
class TimeMap {
public:
    unordered_map<string, vector<pair<int, string>>> store;
    /** Initialize your data structure here. */
    TimeMap() {}
    
    void set(string key, string value, int timestamp) {
        store[key].emplace_back(make_pair(timestamp, value));
    }
    
    string get(string key, int timestamp) {
        auto& targetVec = store[key];
        auto upper = upper_bound(targetVec.begin(), targetVec.end(), timestamp, // `value` is the target upper bound we want to find 
            [](int value, const pair<int, string>& pr){  // cmp: return true if `value` is smaller that `pr`, iterator will move right if lambda is false.
                // use `<` to get strict upper bound
                // not `<=`, or we have to judge whether the element is equal or larger than the timestamp when we adjust the iterator
                return value < pr.first;  
            });
        if(upper == targetVec.begin()) return "";
        return (upper-1)->second;
    }
};
```