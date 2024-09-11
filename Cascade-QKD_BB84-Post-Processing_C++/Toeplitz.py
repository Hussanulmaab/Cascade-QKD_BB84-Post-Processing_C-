def Func_Toeplitz():
    # For Privacy Amplification, I am using Cryptomite Library of Quantinuum

    import os
    import pickle
    import shutil
    import time
    import cryptomite
    from random import randint, sample
    from math import floor, log2
    from collections import Counter

    print(" -------------------------------------------------------------------------------------------------Toeplitz")
    T_RA_File_Path = "T_EC_Bits.txt"
    with open(T_RA_File_Path, 'r') as file:
        Corrected_Transmitter_Bits = file.read()

    R_RA_File_Path = "R_EC_Bits.txt"
    with open(R_RA_File_Path, 'r') as file:
        Corrected_Receiver_Bits = file.read()

    # For Toeplitz n2 = n1 + m - 1
    len_T = len(Corrected_Transmitter_Bits)
    n1_T = len_T
    k1_T = int(n1_T / 2)
    epsilon = 10 ** (-10)
    error = int(log2(epsilon))
    n2_T = int((n1_T + (k1_T / 6) - (n1_T / 6) + ((8 / 6) * error) + ((4 / 6) * log2(4 / 3)) + 1 / 6) / 0.85)
    k2_T = int(0.9 * n2_T)
    m_T = n2_T - n1_T + 1
    T_Input_List = [int(char) for char in Corrected_Transmitter_Bits[:n1_T]]
    seed_T = [randint(0, 1) for _ in range(n2_T)]
    toeplitz_T = cryptomite.Toeplitz(n1_T, m_T)
    T_Output = toeplitz_T.extract(T_Input_List, seed_T)

    # For dodis n2 = n1 + m - 1
    len_R = len(Corrected_Receiver_Bits)
    n1_R = len_R
    k1_R = int(n1_R / 2)
    epsilon = 10 ** (-10)
    error = int(log2(epsilon))
    n2_R = int((n1_R + (k1_R / 6) - (n1_R / 6) + ((8 / 6) * error) + ((4 / 6) * log2(4 / 3)) + 1 / 6) / 0.85)
    k2_R = int(0.9 * n2_R)
    m_R = n2_R - n1_R + 1
    R_Input_List = [int(char) for char in Corrected_Receiver_Bits[:n1_R]]
    seed_R = seed_T
    toeplitz_R = cryptomite.Toeplitz(n1_R, m_R)
    R_Output = toeplitz_R.extract(R_Input_List, seed_R)

    bit_string = ''.join(map(str, T_Input_List))
    with open('T_EC_Bits.txt', 'w') as file:
        file.write(bit_string)

    bit_string = ''.join(map(str, R_Input_List))
    with open('R_EC_Bits.txt', 'w') as file:
        file.write(bit_string)

    with open("Seed_Size.txt", "w") as file:
        file.write(str(n2_T))

    with open('T_RA_Public_Check_A.txt', 'w') as file:
        file.write(''.join(map(str, T_Output)))

    with open('R_RA_Public_Check_A.txt', 'w') as file:
        file.write(''.join(map(str, R_Output)))

