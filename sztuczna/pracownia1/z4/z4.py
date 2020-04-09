# coding: utf-8

next_to_check = []

def check_if_done(bits, goal):
    if goal == 0:
        if bits.count(1) > 0:
            return False
        else:
            return True
    seek_zero = False
    ones_checked = 0
    for j in range(len(bits)):
        if seek_zero and bits[j] == 0:
            break
        if bits[j] == 1:
            seek_zero = True
            ones_checked += 1
            if ones_checked == goal:
                return True
    return False

def check_bit_changes(bits, goal):
    global next_to_check, checked
    for i in range(len(bits)):
        temp_bits = bits.copy()
        if temp_bits[i] == 1:
            temp_bits[i] = 0
        else:
            temp_bits[i] = 1
        # Check if current bits are searched result
        if temp_bits.count(1) == goal:
            if check_if_done(temp_bits, goal):
                return True
        if temp_bits not in next_to_check:
            next_to_check.append(temp_bits)
    return False

def min_bit_changes(start_bits, goal):
    global next_to_check, checked
    to_check = [start_bits]
    op_num = 1

    if start_bits.count(1) == goal:
        if check_if_done(start_bits, goal):
            return 0

    while True:
        for bits in to_check:
            if check_bit_changes(bits, goal):
                return op_num
        op_num += 1
        to_check = next_to_check.copy()
        next_to_check = []

with open("zad4_output.txt", "w",  encoding='utf-8') as w:
    with open("zad4_input.txt", "r",  encoding='utf-8') as r:
        for line in r:
            bits = line[:-3]
            goal = line[-2]
            bits_list = []
            for bit in bits:
                bits_list.append(int(bit))
            w.write(str(min_bit_changes(bits_list, int(goal))) + "\n")
            next_to_check = []
            checked = []