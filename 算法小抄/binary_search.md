## 基本二分搜索

对于基本二分搜索，最终搜索停止的位置，就是对应元素理应存在于的位置。

```java
int binarySearch(int[] nums, int target) {
    int left = 0;
    int right = nums.length;
    while(left < right) {
        int mid = left + (right - left) / 2；
        if(nums[mid] == target) {
            return mid;
        } else if(nums[mid] < target) {
            left = mid + 1;
        } else if(nums[mid] > target) {
            right = mid;
        }
    }
    return -1;
}
```

## 寻找左边界的二分搜索

对于边界二分搜索，最终搜索停止的位置，就是对应元素最左侧边界理应存在的位置（因为是逐渐紧缩右边界，不会出现左边界小于0的情况。）。所以在搜索结束后，检查一下对应处是不是我们要的元素即可；注意，有可能超过右边界，即比所有元素都大。

```java
int binarySearch(int[] nums, int target) {
    int left = 0;
    int right = nums.length;
    while(left < right) {
        int mid = left + (right - left) / 2；
        if(nums[mid] == target) {
            right = mid;  // 只改了这里
        } else if(nums[mid] < target) {
            left = mid + 1;
        } else if(nums[mid] > target) {
            right = mid;
        }
    }
    if(left == num.length) return -1;
    return  nums[left] == target?(left):-1;
    // 如果找不到
}
```
