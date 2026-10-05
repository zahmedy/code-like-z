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