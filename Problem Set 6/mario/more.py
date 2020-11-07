invalid = True

while invalid:
    try:
        height = int(input("Height:"))
    except ValueError:
        continue
    else: 
        if 0 < height < 9:
            invalid = False

for x in range(height):
    print(" " * (height - x - 1), end = "")
    print("#" * (x + 1), end = "")
    print(" ", end = "")
    print("#" * (x + 1))
