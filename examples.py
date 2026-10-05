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