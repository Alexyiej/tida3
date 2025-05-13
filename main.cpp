#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <cassert>


std::vector<int> longest_increasing_subsequence(const std::vector<int>& nums) {
    std::vector<int> dp(nums.size(), 1);
    std::vector<int> prev(nums.size(), -1);
    int max_len = 0, last_index = -1;

    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            last_index = i;
        }
    }

    std::vector<int> lis;
    while (last_index != -1) {
        lis.push_back(nums[last_index]);
        last_index = prev[last_index];
    }

    std::reverse(lis.begin(), lis.end());
    return lis;
}


std::vector<int> max_subarray(const std::vector<int>& nums) {
    int max_sum = nums[0], current_sum = nums[0];
    int start = 0, end = 0, temp_start = 0;

    for (size_t i = 1; i < nums.size(); ++i) {
        if (current_sum < 0) {
            current_sum = nums[i];
            temp_start = i;
        } else {
            current_sum += nums[i];
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
    }

    return std::vector<int>(nums.begin() + start, nums.begin() + end + 1);
}


void generate_partitions(int n, int start, std::vector<int>& current) {
    if (n == 0) {
        for (int x : current) std::cout << x << ' ';
        std::cout << '\n';
        return;
    }

    for (int i = start; i <= n; ++i) {
        current.push_back(i);
        generate_partitions(n - i, i, current);
        current.pop_back();
    }
}


void generate_lex_permutations(int n) {
    std::string s;
    for (int i = 0; i < n; ++i) s += ('a' + i);
    std::sort(s.begin(), s.end());
    do std::cout << s << '\n';
    while (std::next_permutation(s.begin(), s.end()));
}


void run_tests() {
    std::vector<int> input1 = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    std::vector<int> expected_lis = {10, 22, 33, 50, 60, 80};
    assert(longest_increasing_subsequence(input1) == expected_lis);

    std::vector<int> input2 = {2, -4, 6, 8, -10, 100, -6, 5};
    std::vector<int> expected_max_sub = {6, 8, -10, 100};
    assert(max_subarray(input2) == expected_max_sub);
}


int main() {
    run_tests();

    std::vector<int> input1 = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    auto lis = longest_increasing_subsequence(input1);
    for (int x : lis) std::cout << x << ' '; std::cout << "\n";

    std::vector<int> input2 = {2, -4, 6, 8, -10, 100, -6, 5};
    auto max_sub = max_subarray(input2);
    for (int x : max_sub) std::cout << x << ' '; std::cout << "\n";

    std::vector<int> partition;
    generate_partitions(5, 1, partition);

    generate_lex_permutations(3);
    return 0;
}
