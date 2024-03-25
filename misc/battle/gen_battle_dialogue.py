import json 

nullchr = b'\x00'


def dump(name, obj): 
    bin_dump = open("{0}.bin".format(name), "wb")


    faces = [] 
    for pair in obj:
        text = pair["text"].encode('utf-8')
        faces.append(pair["face"])
        bin_dump.write(text)
        bin_dump.write(nullchr)

    bin_dump.close()

    print("{0} dialogue exported to {0}.bin".format(name))

    print("Add this to your source code:")
    print("const u8 faces[{0}] = ".format(len(faces)), end = None)
    print("{")
    for face in faces:
        print("{0}, ".format(face), end = None)

    print("};")


    
with open("battle_dialogue.json", "r") as dialogue:
    precomp_defs = [] 
    data = json.load(dialogue)

    for name in data:
        if not isinstance(data[name], list):
            continue 

        obj = data[name]
        dump(name, obj) 

        for i in range(len(obj)):
            sum = 0 
            for j in range(i): 
                sum += len(obj[j]["text"]) + 1


            precomp_defs.append("#define {0} {1}".format(obj[i]["tag"], sum))
    
    header_dump = open(data["export"], "w")
    
    header_dump.write("#ifndef {0}\n".format(data["header"]))
    header_dump.write("#define {0}\n\n".format(data["header"]))
    for define in precomp_defs: 
        header_dump.write(define)
        header_dump.write('\n')
    header_dump.write("#endif\n")

    print("Header file written to {0}".format(data["export"]))
    
