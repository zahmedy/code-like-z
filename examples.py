def most_common(nums: list[int]) -> int:
    count = {}
    for num in nums:
        if num not in count:
            count[num] = 1
        else:
            count[num] += 1

    most_common = 0
    max_count = 0

    for num in count:
        if count[num] > max_count:
            max_count = count[num]
            most_common = num

    return most_common


def first_duplicate(nums: list[int]) -> int:
    seen = set()

    for num in nums:
        if num in seen:
            return num

        seen.add(num)

    return -1

def two_sum(nums: list[int], target: int) -> list[int]:
    seen = {}

    for i in range(len(nums)):
        needed = target - nums[i]
        
        if needed in seen:
            return [i, seen[needed]]

        seen[nums[i]] = i

    return [-1, -1]

def contains_nearby_duplicate(nums: list[int], k: int) -> bool:
    seen = {}

    for i in range(len(nums)):
        num = nums[i]

        if num in seen and  i - seen[num] <= k:
            return True

        seen[num] = i

    return False

def longest_consecutive(nums: list[int]) -> int:
    num_set = set(nums)
    longest = 0 

    for num in nums:
        if num - 1 not in num_set:
            current_seq_len = 0
            tmp_num = num
            while tmp_num in num_set:
                tmp_num += 1
                current_seq_len += 1

            longest = max(longest, current_seq_len)

    return longest


def group_anagrams(words: list[str]) -> list[list[str]]:
    anamap = {}

    for word in words:
        key = "".join(sorted(word))
        if key not in anamap:
            anamap[key] = [word]
        else:
            anamap[key].append(word)

    return list(anamap.values())

from collections import Counter

def top_k_frequentc(nums: list[int], k: int) -> list[int]:
    count = Counter(nums)
    top_ks = count.most_common(k)
    return [top[0] for top in top_ks]

import heapq

def top_k_frequent(nums: list[int], k: int) -> list[int]:
    min_heap = []
    counts = Counter(nums)

    for num, count in counts.items():
        heapq.heappush(min_heap, (count, num))

        if len(min_heap) > k:
            heapq.heappop(min_heap)

    return [num for _, num in min_heap]

def product_except_self(nums: list[int]) -> list[int]:
    n = len(nums)
    r_to_l = [0] * n
    r_to_l[-1] = 1

    for i in range(n - 2, -1, -1):
        r_to_l[i] = r_to_l[i + 1] * nums[i + 1]

    l_to_r = [0] * n
    l_to_r[0] = 1
    for i in range(1, n):
        l_to_r[i] = l_to_r[i - 1] * nums[i - 1]

    for i in range(n):
        nums[i] = l_to_r[i] * r_to_l[i]

    return nums

