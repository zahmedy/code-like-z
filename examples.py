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
