def Func_Circulant():
    # For Privacy Amplification, I am using Cryptomite Library of Quantinuum

    import os
    import pickle
    import shutil
    import time
    import cryptomite
    from random import randint, sample
    from math import floor, log2
    from collections import Counter

    def is_prime(n):
        """Check if a number is prime."""
        if n <= 1:
            return False
        if n <= 3:
            return True
        if n % 2 == 0 or n % 3 == 0:
            return False
        i = 5
        while i * i <= n:
            if n % i == 0 or n % (i + 2) == 0:
                return False
            i += 6
        return True

    def closest_prime_less_than(target):
        """Find the closest prime number less than the given target."""
        for num in range(target - 1, 1, -1):
            if is_prime(num):
                return num
        return None


    print(" -------------------------------------------------------------------------------------------------Circulant")
    T_RA_File_Path = "T_EC_Bits.txt"
    with open(T_RA_File_Path, 'r') as file:
        Corrected_Transmitter_Bits = file.read()

    R_RA_File_Path = "R_EC_Bits.txt"
    with open(R_RA_File_Path, 'r') as file:
        Corrected_Receiver_Bits = file.read()

    # For Circulant n2 = n1+1 and n2 is prime
    len_T = len(Corrected_Transmitter_Bits)
    n2_T = closest_prime_less_than(len_T)
    n1_T = n2_T - 1
    k1_T = n1_T / 2
    k2_T = floor(0.9 * (n2_T))
    epsilon = 10 ** (-10)
    log2_error = log2(epsilon)
    T_Seed = [randint(0, 1) for _ in range(n2_T)]
    T_Input_List = [int(char) for char in Corrected_Transmitter_Bits[:n1_T]]
    markov_q_proof = True
    Verbose = False
    circulant = cryptomite.Circulant.from_params(k1_T,
                                         k2_T,
                                         log2_error,
                                         n1_T,
                                         n2_T,
                                         markov_q_proof,
                                         Verbose)
    circulant = cryptomite.Circulant(n1_T, circulant.m)
    T_Output = circulant.extract(T_Input_List, T_Seed)

    # For Circulant n2 = n1+1 and n2 is prime
    len_R = len(Corrected_Receiver_Bits)
    n2_R = closest_prime_less_than(len_R)
    n1_R = n2_R - 1
    k1_R = n1_R / 2
    k2_R = floor(0.9 * (n2_R))
    epsilon = 10 ** (-10)
    log2_error = log2(epsilon)
    R_Seed = T_Seed
    R_Input_List = [int(char) for char in Corrected_Receiver_Bits[:n1_R]]
    markov_q_proof = True
    Verbose = False
    circulant = cryptomite.Circulant.from_params(k1_R,
                                         k2_R,
                                         log2_error,
                                         n1_R,
                                         n2_R,
                                         markov_q_proof,
                                         Verbose)
    circulant = cryptomite.Circulant(n1_R, circulant.m)
    R_Output = circulant.extract(R_Input_List, R_Seed)

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
