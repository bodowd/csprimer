import time


def get_duration(func, nums, i):
    start = time.time()
    func(nums, i)
    end = time.time()
    us = (end - start) * 1000000
    print("{}: {} μs".format(i, us))


def sum(nums, n):
    total = 0
    for i in range(n):
        total += i
    return total


def faster_sum(nums, n):
    t1 = 0
    t2 = 0
    t3 = 0
    t4 = 0
    for i in range(0, n, 4):
        t1 += nums[i]
        t2 += nums[i + 1]
        t3 += nums[i + 2]
        t4 += nums[i + 3]

    return t1 + t2 + t3 + t4


if __name__ == "__main__":
    nums = [i for i in range(1 << 20)]
    get_duration(sum, nums, 4096)
    get_duration(sum, nums, 16384)
    get_duration(sum, nums, 65536)
    get_duration(sum, nums, 262144)
    get_duration(sum, nums, 1048576)

    print("Faster sum")
    get_duration(faster_sum, nums, 4096)
    get_duration(faster_sum, nums, 16384)
    get_duration(faster_sum, nums, 65536)
    get_duration(faster_sum, nums, 262144)
    get_duration(faster_sum, nums, 1048576)
