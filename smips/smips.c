// COMP1521 assignment2

#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct instruction
{
    uint32_t s;
    uint32_t t;
    uint32_t d;
    int16_t I;
    uint32_t Ioperation;
    uint32_t operation;
};

// function
void translate(char *file);
void print(char *operation, int x, int y, int z, int imm);
struct instruction seperate(int hex);
void execute(char *file);

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "rb"); // read bytes from file
    if (f == NULL)
    {
        perror(argv[1]);
        return 1;
    }
    translate(argv[1]);
    execute(argv[1]);
    return 0;
}

void translate(char *file)
{
    int hex = 0;
    int i = 0;
    int imm = 0;
    FILE *f = fopen(file, "rb"); // read binary
    printf("Program\n");
    while (fscanf(f, "%x", &hex) == 1) // store 32 bits in hex
    {
        struct instruction s = seperate(hex);
        if (i < 10)
        {
            printf("  %d: ", i);
        }
        else
        {
            printf(" %d: ", i);
        }

        if (s.Ioperation == 0)
        {
            imm = 0;
            if (s.operation == 42) // slt
            {
                print("slt", s.d, s.s, s.t, imm);
            }
            else if (s.operation == 37) // or
            {
                print("or", s.d, s.s, s.t, imm);
            }
            else if (s.operation == 36) // and
            {
                print("and", s.d, s.s, s.t, imm);
            }
            else if (s.operation == 34) // sub
            {
                print("sub", s.d, s.s, s.t, imm);
            }
            else if (s.operation == 32) // add
            {
                print("add", s.d, s.s, s.t, imm);
            }
            else if (s.operation == 12) // syscall
            {
                print("syscall", 0, 0, 0, imm);
            }
            else
            {
                printf(" %s:%d: invalid struction code: %d\n", file, i, hex);
            }
        }
        else
        {
            if (s.operation == 2) // mul
            {
                imm = 0;
                print("mul", s.d, s.s, s.t, imm);
            }
            else if (s.Ioperation == 4) // beq
            {
                imm = 1;
                print("beq", s.s, s.t, s.I, imm);
            }
            else if (s.Ioperation == 5) // bne
            {
                imm = 1;
                print("bne", s.s, s.t, s.I, imm);
            }
            else if (s.Ioperation == 8) // addi
            {
                imm = 1;
                print("addi", s.t, s.s, s.I, imm);
            }
            else if (s.Ioperation == 10) // slti
            {
                imm = 1;
                print("slti", s.t, s.s, s.I, imm);
            }
            else if (s.Ioperation == 12) // andi
            {
                imm = 1;
                print("andi", s.t, s.s, s.I, imm);
            }
            else if (s.Ioperation == 13) // ori
            {
                imm = 1;
                print("ori", s.t, s.s, s.I, imm);
            }
            else if (s.Ioperation == 15) // lui
            {
                imm = 1;
                print("lui", s.t, s.s, s.I, imm);
            }
            else
            {
                printf(" %s:%d: invalid struction code: %d\n", file, i, hex);
            }
        }
        i++;
    }
    fclose(f);
}

struct instruction seperate(int hex)
{
    struct instruction s;
    s.s = (hex >> 21) & 0x1f;
    s.t = (hex >> 16) & 0x1f;
    s.d = (hex >> 11) & 0x1f;
    s.I = hex & 0xffff;
    s.Ioperation = (hex >> 26) & 0x3f;
    s.operation = hex & 0x7ff;
    return s;
}

void print(char *operation, int x, int y, int z, int imm)
{
    if (strcmp("lui", operation) == 0) // operation = lui
    {
        printf("%s  $%d, %d\n", operation, x, z);
    }
    else if (strcmp("syscall", operation) == 0)
    {
        printf("syscall\n");
    }
    // immediate operation
    else if (imm == 0)
    {
        printf("%s  $%d, $%d, $%d\n", operation, x, y, z);
    }
    else if (imm == 1)
    {
        if (strcmp("addi", operation) == 0)
        {
            printf("%s $%d, $%d, %d\n", operation, x, y, z);
        }
        else
        {
            printf("%s  $%d, $%d, %d\n", operation, x, y, z);
        }
    }
}

void execute(char *file)
{
    int instructions[1000] = {0}; // assume at most 1000 numbers
    int registers[32] = {0};      // total 32 registers
    int hex = 0;
    int i = 0; // total number of program
    int end = 0;
    FILE *f = fopen(file, "rb");
    while (fscanf(f, "%x", &hex) == 1)
    {
        instructions[i] = hex;
        i++;
    }
    printf("Output\n");
    int x = 0; // PC
    while ((x < i) && (end == 0))
    {
        struct instruction s = seperate(instructions[x]);
        if (s.Ioperation == 0)
        {
            if (s.operation == 42) // slt
            {
                if (registers[s.s] < registers[s.t])
                {
                    registers[s.d] = 1;
                }
                else
                {
                    registers[s.d] = 0;
                }
            }
            else if (s.operation == 37) // or
            {
                registers[s.d] = registers[s.s] | registers[s.t];
            }
            else if (s.operation == 36) // and
            {
                registers[s.d] = registers[s.s] & registers[s.t];
            }
            else if (s.operation == 34) // sub
            {
                registers[s.d] = registers[s.s] - registers[s.t];
            }
            else if (s.operation == 32) // add
            {
                registers[s.d] = registers[s.s] + registers[s.t];
            }
            else if (s.operation == 12) // syscall
            {
                if (registers[2] == 1)
                {                               // $v0 = 1
                    printf("%d", registers[4]); // printf("%d",$a0)
                }
                else if (registers[2] == 11)
                {
                    printf("%c", registers[4]); //  printf("%c",$a0)
                }
                else if (registers[2] == 10)
                {
                    end = 1;
                }
                else
                {
                    printf("Unknown system call: %d\n", registers[2]);
                    end = 1;
                }
            }
        }
        else
        {
            if (s.operation == 2) // mul
            {
                registers[s.d] = registers[s.s] * registers[s.t];
            }
            else if (s.Ioperation == 4) // beq
            {
                if (registers[s.s] == registers[s.t])
                {
                    x = x + s.I - 1;
                }
            }
            else if (s.Ioperation == 5) // bne
            {
                if (registers[s.s] != registers[s.t])
                {
                    x = x + s.I - 1;
                }
            }
            else if (s.Ioperation == 8) // addi
            {
                registers[s.t] = registers[s.s] + s.I;
            }
            else if (s.Ioperation == 10) // slti
            {
                if (registers[s.s] < s.I)
                {
                    registers[s.t] = 1;
                }
                else
                {
                    registers[s.t] = 0;
                }
            }
            else if (s.Ioperation == 12) // andi
            {
                registers[s.t] = registers[s.s] & s.I;
            }
            else if (s.Ioperation == 13) // ori
            {
                registers[s.t] = registers[s.s] | s.I;
            }
            else if (s.Ioperation == 15) // lui
            {
                registers[s.t] = s.I << 16;
            }
        }
        x++;
        registers[0] = 0;
    }

    printf("Registers After Execution\n");
    for (int k = 1; k < 32; k++)
    {
        if (registers[k] != 0)
        {
            if (k < 10)
            {
                printf("$%d  = %d\n", k, registers[k]);
            }
            else
            {
                printf("$%d = %d\n", k, registers[k]);
            }
        }
    }
}
