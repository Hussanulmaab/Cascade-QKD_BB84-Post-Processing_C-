def Cryptomite_Priv_Amp():
    # For Privacy Amplification, I am using Cryptomite Library of Quantinuum

    import cryptomite

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
    with open('Bob_Error_Reconciliated.txt', 'r') as file:
        input_bits = [int(bit) for bit in file.read().strip()]

    # Read the seed bits from the Seed file
    with open('Seed.txt', 'r') as seed_file:
        seed_bits = [int(bit) for bit in seed_file.read().strip()]

    n = len(input_bits)
    m = n

    # Perform privacy amplification
    final = privacy_amplification(input_bits, seed_bits, n, m)

    # Write final to "Bob_Final_Key.txt"
    with open('Bob_Final_Key.txt', 'w') as final_key_file:
        final_key_file.write(''.join(map(str, final)))

    print(input_bits)
    print(seed_bits)
    print(final)