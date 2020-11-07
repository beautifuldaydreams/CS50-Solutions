import math

def main():
    letters = 0
    words = 1
    sentences = 0

    text = input("TEXT: ")
    n = len(text)
    for i in range(0, n):
        if 64 < ord(text[i]) < 91 or 96 < ord(text[i]) < 123:
            letters += 1
        if ord(text[i]) == 32:
            words += 1
        if ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63:
            sentences += 1
            
    print(f"sentences: {sentences}")
    print(f"words: {words}")
    print(f"letters: {letters}")
            
    L = (letters / words) * 100;
    S = (sentences / words) * 100;
    
    print(f"L: {L}")
    print(f"S: {S}")
    
    index = round((0.0588 * L) - (0.296 * S) - 15.8)
    
    if index > 16:
        print("Grade 16+")
    if index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")
        
main()
