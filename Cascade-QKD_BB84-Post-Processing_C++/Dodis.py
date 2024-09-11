def Func_Dodis():
    # For Privacy Amplification, I am using Cryptomite Library of Quantinuum

    import os
    import pickle
    import shutil
    import time
    import cryptomite
    from random import randint, sample
    from math import floor, log2
    from collections import Counter

    print(" -------------------------------------------------------------------------------------------------Dodis")
    T_RA_File_Path = "T_EC_Bits.txt"
    with open(T_RA_File_Path, 'r') as file:
        Corrected_Transmitter_Bits = file.read()

    R_RA_File_Path = "R_EC_Bits.txt"
    with open(R_RA_File_Path, 'r') as file:
        Corrected_Receiver_Bits = file.read()

    # For dodis n1 and n2 both equal and primitive root of 2
    len_T = len(Corrected_Transmitter_Bits)
    with open('na_set.txt', 'r') as file:
        content = file.read()
        numbers = list(map(int, content.split(',')))
    target = len_T
    filtered_numbers = [num for num in numbers if num < target]
    if filtered_numbers:
        Closest_Prim_Root2 = max(filtered_numbers, key=lambda x: x)
        print(f"The closest number less than {target} is {Closest_Prim_Root2}.")
    else:
        print(f"There are no numbers less than {target} in the list.")
    n1_T = n2_T = Closest_Prim_Root2
    k1_T = n1_T / 2
    k2_T = floor(0.9*(n2_T))
    epsilon = 10 ** (-10)
    log2_error = log2(epsilon)
    T_Seed = [randint(0,1)for _ in range(n2_T)]
    T_Input_List = [int(char) for char in Corrected_Transmitter_Bits[:n1_T]]
    markov_q_proof = True
    Verbose = False
    dodis = cryptomite.Dodis.from_params(k1_T,
                                         k2_T,
                                         log2_error,
                                         n1_T,
                                         n2_T,
                                         markov_q_proof,
                                         Verbose)
    T_Output = dodis.extract(T_Input_List, T_Seed)

    # For dodis n1 and n2 both equal and primitive root of 2
    len_R = len(Corrected_Receiver_Bits)
    with open('na_set.txt', 'r') as file:
        content = file.read()
        numbers = list(map(int, content.split(',')))
    target = len_R
    filtered_numbers = [num for num in numbers if num < target]
    if filtered_numbers:
        Closest_Prim_Root2 = max(filtered_numbers, key=lambda x: x)
        print(f"The closest number less than {target} is {Closest_Prim_Root2}.")
    else:
        print(f"There are no numbers less than {target} in the list.")
    n1_R = n2_R = Closest_Prim_Root2
    k1_R = n1_R / 2
    k2_R = floor(0.9*(n2_R))
    epsilon = 10 ** (-10)
    log2_error = log2(epsilon)
    R_Seed = T_Seed
    R_Input_List = [int(char) for char in Corrected_Receiver_Bits[:n1_R]]
    markov_q_proof = True
    Verbose = False
    dodis = cryptomite.Dodis.from_params(k1_R,
                                         k2_R,
                                         log2_error,
                                         n1_R,
                                         n2_R,
                                         markov_q_proof,
                                         Verbose)
    R_Output = dodis.extract(R_Input_List, R_Seed)

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

