from cs50 import SQL
import csv
import sys

def main():
    if len(sys.argv)!= 2:
        print("Usage: python import.py characters.csv")
        sys.exit()
        
    db = SQL("sqlite:///students.db")
    
    with open("characters.csv", "r") as students:
        reader = csv.DictReader(students, delimiter=",")
        
        for row in reader:
            tmp_lst = []
            tmp_lst.append(row['name'])
            tmp_lst = tmp_lst[0].split()
            
            if len(tmp_lst) == 2:
                tmp_lst.insert(1, None)
            
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", tmp_lst[0], tmp_lst[1], tmp_lst[2], row["house"], row["birth"])
        
main()
