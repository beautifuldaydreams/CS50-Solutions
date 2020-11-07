import sys
import csv
import re

def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()
    
    count = 0
    seq_lst = []
    
    with open(sys.argv[1], 'r') as data_base, open(sys.argv[2], 'r') as dna:
        db_r = csv.reader(data_base)
        dna_r = csv.reader(dna)
    
        for line in db_r:
            for dna_seq in dna_r:
                for i in range(1, len(line)):
                    groups = re.findall(rf"(?:{line[i]})+", dna_seq[0])
                    
                    largest = len(max(groups, key=len)) // len(line[i])
                    seq_lst.append(largest)
                    
    with open(sys.argv[1], 'r') as data_base, open(sys.argv[2], 'r') as dna:
        db_r = csv.reader(data_base)
        index = 0
        
        for line in db_r:
            copy = []
            if index == 0:
                next(db_r)
                index += 1
            else:
                for ele in range(1, len(line)):
                    copy.append(int(line[ele]))

            if copy == seq_lst:
                print(f"{line[0]}")
                return
        
        print("No match")

main()
