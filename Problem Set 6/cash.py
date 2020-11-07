while True:
    
    coin_count = 0
    
    try:
        cash = float(input("Enter amount of cash owed: "))
        
        if cash <= 0:
            raise ValueError
        
    except ValueError:
        continue
    else:
        if cash > 0:
            cash = round(cash, 2)
        
        while cash >= 0.25:
            cash -= 0.25
            coin_count += 1
        while cash >= 0.1:
            cash -= 0.1
            coin_count += 1
        while cash >= 0.05:
            cash -= 0.05
            coin_count += 1
        while cash >= 0.01:
            cash -= 0.01
            coin_count += 1
            
        print(f"{coin_count}")
        break
