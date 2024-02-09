import ctypes

print("const u16 lookup_table[123] = {")

for i in range(123):
    x = 15
    y = 7

    if i >= 65 and i <= 90:                     # A-Z
        x = i - 65
        y = 4

    elif i >= 97 and i <= 122:                  # a-z
        x = i - 97 
        y = 1

    elif i >= 48 and i <= 57:                   # 0-9
        x = i - 48
        y = 7

    elif i == 32:                               # Space
        x = 0
        y = 0

    elif i == 46:                               # .
        x = 9
        y = 7
    elif i == 44:                               # ,
        x = 10
        y = 7
    elif i == 40:                               # (
        x = 11
        y = 7
    elif i == 41:                               # )
        x = 12
        y = 7
    elif i == 58:                               # :
        x = 13
        y = 7
    elif i == 33:                               # !
        x = 14
        y = 7
    elif i == 63:                               # ?
        x = 15
        y = 7
    elif i == 39:                               # '
        x = 16
        y = 7
    elif i == 34:                               # "
        x = 17
        y = 7
    elif i == 45:                               # -
        x = 18
        y = 7
    elif i == 91:                               # [
        x = 19
        y = 7
    elif i == 93:                               # ]
        x = 20
        y = 7

    print("{},".format(hex(x << 8 | y)))

print("};")