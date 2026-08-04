class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {

        int mn = nums[0];
        int mx = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < mn)
                mn = nums[i];

            if (nums[i] > mx)
                mx = nums[i];
        }

        vector<int> ans;

        for (int i = mn + 1; i < mx; i++) {

            bool found = false;

            for (int j = 0; j < nums.size(); j++) {
                if (nums[j] == i) {
                    found = true;
                    break;
                }
            }

            if (!found)
                ans.push_back(i);
        }

        return ans;
    }
};