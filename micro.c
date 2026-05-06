#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_MEM_SIZE 1024
#define PROG_MEM_SIZE 256
#define MAX_INSTR_LEN 64

int data_memory[DATA_MEM_SIZE / 4];
int regs[32];
int PC;
int PSW;

char program_memory[PROG_MEM_SIZE][MAX_INSTR_LEN];
int program_size;

int reg_num(char *name) {
    while (*name == '$') name++;
    if (*name >= '0' && *name <= '9') return atoi(name);
    if (strcmp(name, "zero") == 0) return 0;
    if (strcmp(name, "at") == 0)   return 1;
    if (strcmp(name, "v0") == 0)   return 2;
    if (strcmp(name, "v1") == 0)   return 3;
    if (strcmp(name, "a0") == 0)   return 4;
    if (strcmp(name, "a1") == 0)   return 5;
    if (strcmp(name, "a2") == 0)   return 6;
    if (strcmp(name, "a3") == 0)   return 7;
    if (strcmp(name, "t0") == 0)   return 8;
    if (strcmp(name, "t1") == 0)   return 9;
    if (strcmp(name, "t2") == 0)   return 10;
    if (strcmp(name, "t3") == 0)   return 11;
    if (strcmp(name, "s0") == 0)   return 16;
    if (strcmp(name, "s1") == 0)   return 17;
    if (strcmp(name, "s2") == 0)   return 18;
    if (strcmp(name, "s3") == 0)   return 19;
    if (strcmp(name, "s4") == 0)   return 20;
    if (strcmp(name, "s5") == 0)   return 21;
    if (strcmp(name, "gp") == 0)   return 28;
    if (strcmp(name, "sp") == 0)   return 29;
    if (strcmp(name, "fp") == 0)   return 30;
    if (strcmp(name, "ra") == 0)   return 31;
    return 0;
}

int mem_read(int addr) {
    int idx = addr / 4;
    if (idx < 0 || idx >= DATA_MEM_SIZE / 4) {
        printf("Error: lectura fuera de rango en %d\n", addr);
        exit(1);
    }
    return data_memory[idx];
}

void mem_write(int addr, int value) {
    int idx = addr / 4;
    if (idx < 0 || idx >= DATA_MEM_SIZE / 4) {
        printf("Error: escritura fuera de rango en %d\n", addr);
        exit(1);
    }
    data_memory[idx] = value;
}

void load_program(char instrs[][MAX_INSTR_LEN], int n) {
    program_size = n;
    for (int i = 0; i < n; i++) {
        strncpy(program_memory[i], instrs[i], MAX_INSTR_LEN);
    }
}

char *fetch() {
    if (PC >= program_size) return NULL;
    return program_memory[PC++];
}

void decode_execute(char *instr) {
    char buf[MAX_INSTR_LEN];
    strncpy(buf, instr, MAX_INSTR_LEN);

    char *op = strtok(buf, " ,");
    if (!op) return;

    if (strcmp(op, "add") == 0) {
        char *rd_s = strtok(NULL, " ,");
        char *rs_s = strtok(NULL, " ,");
        char *rt_s = strtok(NULL, " ,");
        int rd = reg_num(rd_s);
        int rs = reg_num(rs_s);
        int rt = reg_num(rt_s);
        regs[rd] = regs[rs] + regs[rt];
        PSW = (regs[rd] == 0) ? 1 : 0;

    } else if (strcmp(op, "lw") == 0) {
        char *rt_s = strtok(NULL, " ,");
        char *addr_s = strtok(NULL, " ,");
        int rt = reg_num(rt_s);
        int offset = 0, base = 0;
        char *paren = strchr(addr_s, '(');
        if (paren) {
            *paren = '\0';
            offset = atoi(addr_s);
            char *base_s = paren + 1;
            base_s[strlen(base_s) - 1] = '\0';
            base = regs[reg_num(base_s)];
        } else {
            offset = atoi(addr_s);
        }
        regs[rt] = mem_read(base + offset);
    }
}

void run() {
    PC = 0;
    char *instr;
    while ((instr = fetch()) != NULL) {
        decode_execute(instr);
    }
}

void dump_regs() {
    char *names[] = {
        "zero","at","v0","v1","a0","a1","a2","a3",
        "t0","t1","t2","t3","t4","t5","t6","t7",
        "s0","s1","s2","s3","s4","s5","s6","s7",
        "t8","t9","k0","k1","gp","sp","fp","ra"
    };
    for (int i = 0; i < 32; i++) {
        if (regs[i] != 0)
            printf("  $%s (r%d) = %d\n", names[i], i, regs[i]);
    }
    printf("  PC = %d, PSW = %d\n", PC, PSW);
}

int main() {
    memset(regs, 0, sizeof(regs));
    memset(data_memory, 0, sizeof(data_memory));
    PC = 0;
    PSW = 0;

    mem_write(0, 10);
    mem_write(4, 20);

    char prog[][MAX_INSTR_LEN] = {
        "lw $t0, 0($zero)",
        "lw $t1, 4($zero)",
        "add $t2, $t0, $t1",
    };

    load_program(prog, 3);
    run();
    dump_regs();

    return 0;
}