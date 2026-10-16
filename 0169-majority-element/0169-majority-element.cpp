class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0, ctr = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (ctr == 0)
                candidate = nums[i];
            if (nums[i] == candidate)
                ctr++;
            else
                ctr--;
        }
        return candidate;
    }
};