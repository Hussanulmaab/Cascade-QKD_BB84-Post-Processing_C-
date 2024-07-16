def RA_Toeplitz():
    # For Privacy Amplification, I am using Cryptomite Library of Quantinuum

    import os
    import pickle
    import shutil
    import time
    import cryptomite
    from random import randint, sample
    from math import floor, log2
    from collections import Counter

    def make_Toeplitz_Seed_Reversed(input_bits_list, m):
        n1 = len(input_bits_list)
        extended_bits = input_bits_list.copy()
        for i in range(m - 1):
            extended_bits.append(input_bits_list[i % n1])
        reversed_bits = extended_bits[::-1]
        return reversed_bits

    def make_Toeplitz_Seed_Flipped(input_bits_list, m):
        n1 = len(input_bits_list)
        extended_bits = input_bits_list.copy()
        for i in range(m - 1):
            extended_bits.append(input_bits_list[i % n1])
        flipped_bits = [1 - bit for bit in extended_bits]
        return flipped_bits

    def calculate_error_rate(final, final_2):
        errors = sum(1 for a, b in zip(final, final_2) if a != b)
        error_rate = (errors / len(final)) * 100
        return error_rate

    T_RA_File_Path = "T_RA_Public_Check_B.txt"
    with open(T_RA_File_Path, 'r') as file:
        Corrected_Transmitter_Bits = file.read()

    R_RA_File_Path = "R_RA_Public_Check_B.txt"
    with open(R_RA_File_Path, 'r') as file:
        Corrected_Receiver_Bits = file.read()


    n1_T = m_T = len(Corrected_Transmitter_Bits)
    T_list = list(Corrected_Transmitter_Bits)
    T_Input_List = [int(bit) for bit in T_list]
    T_Seed = make_Toeplitz_Seed_Flipped(T_Input_List, m_T)
    T_toeplitz_obj = cryptomite.Toeplitz(n1_T, m_T)
    T_Rand_Toeplitz = T_toeplitz_obj.extract(T_Input_List, T_Seed)

    n1_R = m_R = len(Corrected_Receiver_Bits)
    R_list = list(Corrected_Receiver_Bits)
    R_Input_List = [int(bit) for bit in R_list]
    R_Seed = make_Toeplitz_Seed_Flipped(R_Input_List, m_R)
    R_toeplitz_obj = cryptomite.Toeplitz(n1_R, m_R)
    R_Rand_Toeplitz = R_toeplitz_obj.extract(R_Input_List, R_Seed)

    with open('T_RA_Public_Check_A.txt', 'w') as file:
        file.write(''.join(map(str, T_Rand_Toeplitz)))

    with open('R_RA_Public_Check_A.txt', 'w') as file:
        file.write(''.join(map(str, R_Rand_Toeplitz)))

