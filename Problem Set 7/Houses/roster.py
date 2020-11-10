from cs50 import SQL
import csv
import sys

def main():
    if len(sys.argv)!= 2:
        print("Usage: python roaster.py house")
        sys.exit()
        
    db = SQL("sqlite:///students.db")
            
    data = db.execute("SELECT first, middle, last, birth FROM students WHERE students.house =? ORDER BY last ASC, first ASC", (sys.argv[1]))
    for row in data:
        print(row["first"], end=" ")
        if row["middle"] != None:
            print(row["middle"], end=" ")
        print(row["last"] + ", born " + str(row["birth"]))
        
        
main()
