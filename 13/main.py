def bin_to_dec(num: str) -> int:
    result = 0
    for char in num:
        result <<= 1
        if char == "1":
            result += 1

    return result


print(bin_to_dec(bin(120)[2:]), 120)
print(bin_to_dec(bin(31234)[2:]), 31234)
