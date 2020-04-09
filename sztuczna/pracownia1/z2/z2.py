# coding: utf-8

dict = set()
max_word_len = 0

with open("words_for_ai1.txt", encoding='utf-8') as f:
    for line in f:
        if len(line) - 1 > max_word_len:
            max_word_len = len(line) - 1
        dict.add(line[:-1]) 

# mem to słownik, gdzie klucze to numer litery w tekście, a wartości to 
# oddzielone spacją słowa i suma długości kwadratów tych słów
def find_longest_words(line, pos_in_text, mem):
    if not line:
        return(("", 0, mem))
    max_line_val = -1
    max_tail_words = ""
    word_indx = 0
    for i in range(1, min(len(line), max_word_len) + 1):
        if line[:i] in dict:
            if pos_in_text + i in mem:
                tail, tailVal = mem[pos_in_text + i]
            else:
                tail, tailVal, new_mem = find_longest_words(line[i:], pos_in_text + i, mem)
                mem = new_mem
            # Nie znaleziono słów w ogonie
            if tailVal == -1:
                continue 
            cur_line_val = tailVal + i**2
            if max_line_val < cur_line_val:
                max_line_val = cur_line_val
                max_tail_words = tail
                word_indx = i
    # Nie znaleziono pasujacego ułożenia słów
    if max_line_val == -1:
        return(("", -1, mem))
    if max_tail_words:
        mem[pos_in_text] = (line[:word_indx] + " " + max_tail_words, max_line_val)
        return((line[:word_indx] + " " + max_tail_words, max_line_val, mem))
    else:
        mem[pos_in_text] = (line[:word_indx], max_line_val)
        return((line[:word_indx], max_line_val, mem))

with open("zad2_output.txt", "w", encoding='utf-8') as w:
    with open("zad2_input.txt", "r", encoding='utf-8') as r:
        for line in r:
            words, _, _ = find_longest_words(line[:-1], 0, {})
            w.write(words + "\n")

