import sys
def rd(binary):
    rd = binary[20:25]
    return 'x'+str(int(rd,2))

def rs1(binary):
    rs1 = binary[12:17]
    return 'x'+str(int(rs1,2))

def rs2(binary):
    rs2 = binary[7:12]
    return 'x'+str(int(rs2,2))

def Rformat(binary):
    funct7 = binary[:7]
    funct3 = binary[17:20]
    
    if funct7 == '0000000':
        if funct3 == '000':
            print('add ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        elif funct3 == '001':
            print('sll ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        elif funct3 == '010':
            print('slt ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        elif funct3 == '011':
            print('sltu ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        elif funct3 == '100':
            print('xor ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        elif funct3 == '101':
            print('srl ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        elif funct3 == '110':
            print('or ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        elif funct3 == '111':
            print('and ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
    
    elif funct7 == '0100000':
        if funct3 == '000':
            print('sub ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
        if funct3 == '101':
            print('sra ' + rd(binary) + ', ' + rs1(binary) + ', ' + rs2(binary))
            
def Iformat(binary):
    immed = binary[:12]
    shamt = binary[7:12]
    funct3 = binary[17:20]
    
    if funct3 == '001' and immed[:7] == '0000000':
        print('slli '+ rd(binary) + ', ' + rs1(binary) + ', ' + str(int(shamt,2)))
    elif funct3 == '101' and immed[:7] == '0000000':
        print('srli '+ rd(binary) + ', ' + rs1(binary) + ', ' + str(int(shamt,2)))
    elif funct3 == '101'and immed[:7] == '0100000':
        print('srai '+ rd(binary) + ', ' + rs1(binary) + ', ' + str(int(shamt,2)))
    
    elif funct3 == '000':
        if immed[0] == '1':
            immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
        else:
            immediate = int(immed,2)
        print('addi ' + rd(binary) + ', ' + rs1(binary) + ', ' + str(immediate))
    
    elif funct3 == '010':
        if immed[0] == '1':
            immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
        else:
            immediate = int(immed,2)
        print('slti ' + rd(binary) + ', ' + rs1(binary) + ', ' + str(immediate))
    
    elif funct3 == '011':
        if immed[0] == '1':
            immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
        else:
            immediate = int(immed,2)
        print('sltiu ' + rd(binary) + ', ' + rs1(binary) + ', ' + str(immediate))
    
    elif funct3 == '100':
        if immed[0] == '1':
            immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
        else:
            immediate = int(immed,2)
        print('xori ' + rd(binary) + ', ' + rs1(binary) + ', ' + str(immediate))
    
    elif funct3 == '110':
        if immed[0] == '1':
            immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
        else:
            immediate = int(immed,2)
        print('ori ' + rd(binary) + ', ' + rs1(binary) + ', ' + str(immediate))

    elif funct3 == '111':
        if immed[0] == '1':
            immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
        else:
            immediate = int(immed,2)
        print('andi ' + rd(binary) + ', ' + rs1(binary) + ', ' + str(immediate))

def load(binary):
    funct3 = binary[17:20]
    immed = binary[:12]

    if immed[0] == '1':
        immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
    else:
        immediate = int(immed,2)

    if funct3 == '000':
        print('lb ' + rd(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')
    if funct3 == '001':
        print('lh ' + rd(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')
    if funct3 == '010':
        print('lw ' + rd(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')
    if funct3 == '100':
        print('lbu ' + rd(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')
    if funct3 == '101':
        print('lhu ' + rd(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')

def store(binary):
    funct3 = binary[17:20]
    immed = binary[:7] + binary[20:25]

    if immed[0] == '1':
        immediate = ((~(int(immed,2)) & 0xff)+1) * -1
    else:
        immediate = int(immed,2)


    if funct3 == '000':
        print('sb ' + rs2(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')
    if funct3 == '001':
        print('sh ' + rs2(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')
    if funct3 == '010':
        print('sw ' + rs2(binary) + ', ' + str(immediate) + '(' + rs1(binary) + ')')

def branch(binary):
    funct3 = binary[17:20]
    
    imm1_4 = binary[20:24]
    imm5_10 = binary[1:7]
    imm11 = binary[24]
    imm12 = binary[0]
    immed = imm12+imm11+imm5_10+imm1_4+'0'

    if immed[0] == '1':
        immediate = ((~(int(immed,2)) & 0xff)+1) * -1
    else:
        immediate = int(immed,2)

    if funct3 == '000':
        print('beq ' + rs1(binary) + ', ' + rs2(binary) + ', ' + str(immediate))
    if funct3 == '001':
        print('bne ' + rs1(binary) + ', ' + rs2(binary) + ', ' + str(immediate))
    if funct3 == '100':
        print('blt ' + rs1(binary) + ', ' + rs2(binary) + ', ' + str(immediate))
    if funct3 == '101':
        print('bge ' + rs1(binary) + ', ' + rs2(binary) + ', ' + str(immediate))
    if funct3 == '110':
        print('bltu ' + rs1(binary) + ', ' + rs2(binary) + ', ' + str(immediate))
    if funct3 == '111':
        print('bgeu ' + rs1(binary) + ', ' + rs2(binary) + ', ' + str(immediate))

def jal(binary):
    imm20 = binary[0]
    imm1_10 = binary[1:11]
    imm11 = binary[11]
    imm12_19 = binary[12:20]
    immed = imm20 + imm12_19 + imm11 + imm1_10 +'0'

    if immed[0] == '1': 
        immediate = ((~(int(immed,2)) & 0xfffff)+1) * -1
        print('jal ' + rd(binary) + ', ' + str(immediate))
    else:
        immediate = int(immed,2)
        print('jal ' + rd(binary) + ', ' + str(immediate))
    
def jalr(binary):
    immed = binary[:12]
    
    if immed[0] == '1':
        immediate = ((~(int(immed,2)) & 0xfff)+1) * -1
        print('jalr ' + rd(binary) +', ' + str(immediate) + '(' + rs1(binary) +')')
    else:
        immediate = int(immed,2)
        print('jalr ' + rd(binary) +', ' + str(immediate) + '(' + rs1(binary) +')')
            
def lui(binary):
    immed = binary[:20]+'000000000000'

    if immed[0] == '1':
        immediate = ((~(int(immed,2)) & 0xffffffff)+1) * -1
        print('lui '+ rd(binary) + ', ' + str(immediate))
    else:
        immediate = int(immed,2)
        print('lui '+ rd(binary) + ', ' + str(immediate))

def auipc(binary):
    immed = binary[:20]+'000000000000'
    if immed[0] == '1':
        immediate = ((~(int(immed,2)) & 0xffffffff)+1) * -1
        print('auipc '+ rd(binary) + ', ' + str(immediate))
    else:
        immediate = int(immed,2)
        print('auipc '+ rd(binary) + ', ' + str(immediate))

        
            
            
            
    
    

input_file = sys.argv[1]
with open(input_file, 'rb') as f:
    buffer = []
    count = 0
    while True:
        byte = f.read(1)
        if byte == b'':
            break

        buffer.insert(0, format(ord(byte), '02x'))
        max = len(buffer)
        if not max % 4:
            print(f"inst {count}:", end= ' ')
            hex_ = ''.join(buffer[:4])
            print(hex_, end=' ')
            count += 1
            hex_ = '0x'+ hex_
            hex_ = int(hex_, 16)
            bin_ = format(hex_,'b').zfill(32)
            #print(bin_)
            
            opcode = bin_[len(bin_)-7:]
            if opcode == '0110011':
                Rformat(bin_)
            elif opcode == '0010011':
                Iformat(bin_)
            elif opcode == '0000011':
                load(bin_)
            elif opcode == '0100011':
                store(bin_)
            elif opcode == '1100011':
                branch(bin_)
            elif opcode == '1101111':
                 jal(bin_)
            elif opcode == '1100111':
                jalr(bin_)
            elif opcode == '0110111':
                lui(bin_)
            elif opcode == '0010111':
                auipc(bin_)
            else:
                print('unknown instruction')
            
        
    
    
            
            
        
      


        


        
        
       

    
    
