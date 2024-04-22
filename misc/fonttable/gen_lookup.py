import pandas as pd 
import ctypes

tbl = pd.read_excel("misc/lookup_table.xlsx")
'''
    Bitpacking method (this is messy, don't overthink). 

    Assumptions:

    vflip only ever happens on the top tile. 
    Every tile at minimum as one free bit. 
    The top tiles at minimum have two free bits. 

    Solution:

    Top tile: 0 = hflip, 1 = vflip 
    Middle, Bottom tile: 0 = hflip 

    We have not yet added unioned alphabets with letters that have tails, this should not be a problem and can be extended with this system. 

'''



switch = []


print("const u8 lookup_table[" + str(tbl.shape[0]) + "][8] = {")
for i, row in tbl.iterrows(): 
    print("{")
    
    t_hflip = (1 << 7) if row['Top_hflip'] else 0 
    m_hflip = (1 << 7) if row['Middle_hflip'] else 0 
    b_hflip = (1 << 7) if row['Bottom_hflip'] else 0 

    t_vflip = (1 << 6) if row['Top_vflip'] else 0 

    q_hflip = (1 << 7) if row['q_hflip'] else 0 

    x = row['Letter'][0]

    print("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}".format(
        hex(row['Top']    | t_hflip | t_vflip),
        hex(row['Middle'] | m_hflip),
        hex(row['Bottom'] | b_hflip),
        hex(row['g_union']),
        hex(row['p_union']),
        hex(row['q_union'] | q_hflip), 
        hex(row['Q_union']),
        hex(row['comma_union'])
    ))
    print("}, // " + x)


    
    
    switch.append(ord(x))

print("};")


# We are relying on the compiler to produce a lookup table from the switch statement in order to make it more optimized. 


print("switch(c){")
for i,v in enumerate(switch):
    print("case '{0}':".format(chr(v)))
    print("\t return lookup_table[{0}];".format(i)) 
    print("\t break;")
print("default:")
print("\t return lookup_table[0];")
print("\t break;")
print("}")



