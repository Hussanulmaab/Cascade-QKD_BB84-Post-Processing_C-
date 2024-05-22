def Cryptomite_Priv_Amp():
    # For Privacy Amplification, I am using Cryptomite Library of Quantinuum

    import cryptomite
    from random import randint

    def privacy_amplification(raw_key_bits: list, seed_bits: list, n_1, m):
        """ Perform privacy amplification for the QKD protocol.
        Parameters
        ----------
        raw_key_bits : list of bits, derived from the measurement
        outcomes (after sifting, error correction and parameter
        estimation).
        seed_bits : list of bits, generated independently.
        n_1: integer, the length of the raw key bit string.
        m: integer, the length of the output secret key bit string.
        Returns
        ---------
        list of bits,
        the extracted output (i.e. the shared secret key).
        """
        # Initialise the Toeplitz extractor with the appropriate parameters:
        dodis = cryptomite.Dodis(n_1, m)
        # Perform Toeplitz extraction and return the output
        return dodis.extract(raw_key_bits, seed_bits)

    # Read the file and generate the input_bits list
    with open('Alice_Error_Reconciliated.txt', 'r') as file:
        input_bits = [int(bit) for bit in file.read().strip()]

    n = len(input_bits)
    m = n

    seed_bits = [randint(0, 1) for _ in range(n)]

    # Perform privacy amplification
    final = privacy_amplification(input_bits, seed_bits, n, m)

    # Write seed_bits to "Seed.txt"
    with open('Seed.txt', 'w') as seed_file:
        seed_file.write(''.join(map(str, seed_bits)))

    # Write final to "Alice_Final_Key.txt"
    with open('Alice_Final_Key.txt', 'w') as final_key_file:
        final_key_file.write(''.join(map(str, final)))

    print(input_bits)
    print(seed_bits)
    print(final)