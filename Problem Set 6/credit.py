import math

valid = True
credit = 0

def get_num():
    global credit
    try:
        credit = int(input("Enter credit card number:"))
        if credit <= 0:
            raise ValueError
    except ValueError:
        get_num()
    else:
        return credit

def check_validity(x):
    global validity
    tot = 0
    for i in range(2, length + 1, 2):
        temp = 2*(math.floor((x % (10**i))/ 10**(i-1)))
        if temp > 9:
            temp = temp % 10 + 1
        tot += temp
        
    for i in range(1, length + 1, 2):
        temp = math.floor((x % (10**i))/ 10**(i-1))
        tot += temp
        
    if tot % 10 == 0 and length == 15:
        print("AMEX")
    elif tot % 10 == 0 and length == 14 or (tot % 10 == 0 and length == 16 and math.floor(credit / 1000000000000000) == 4):
        print("VISA")
    elif tot % 10 == 0 and length == 16 and math.floor(credit / 1000000000000000) == 5:
        print("MASTERCARD")
    else:
        print("INVALID")
    
    valid = False
    
def find_length(x):
    if 1000000000000 <= x < 10000000000000 or 10000000000000 <= x < 1000000000000000 or 1000000000000000 <= x < 100000000000000000: 
        return len(str(x))
    else:
        print("INVALID")
        global valid
        valid = False

while valid:
    get_num()
    length = find_length(credit)
    check_validity(credit)
