#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Instruction:
// ABCDE
// 01234
// 01002
// 34 - two-digit opcode,      02 == opcode 2
//  2 - mode of 1st parameter,  0 == position mode
//  1 - mode of 2nd parameter,  1 == immediate mode
//  0 - mode of 3rd parameter,  0 == position mode,
//                                   omitted due to being a leading zero
// 0 1 or 2 = left-to-right position after 2 digit opcode
// p i or r = position, immediate or relative mode
// r or w = read or write

typedef struct Intcode {
    int input;
    int output;
    int phase;
    int pointer;
    int memory[523];
    int isStopped;
    int doesRecur;
} anIntcode;

int const offsetC = 1;
int const offsetB = 2;
int const offsetA = 3;

int memoryConstant[523] = {3, 8, 1001, 8, 10, 8, 105, 1, 0, 0, 21, 38, 55, 72, 93, 118, 199, 280, 361, 442, 99999, 3, 9, 1001, 9, 2, 9, 1002, 9, 5, 9, 101, 4, 9, 9, 4, 9, 99, 3, 9, 1002, 9, 3, 9, 1001, 9, 5, 9, 1002, 9, 4, 9, 4, 9, 99, 3, 9, 101, 4, 9, 9, 1002, 9, 3, 9, 1001, 9, 4, 9, 4, 9, 99, 3, 9, 1002, 9, 4, 9, 1001, 9, 4, 9, 102, 5, 9, 9, 1001, 9, 4, 9, 4, 9, 99, 3, 9, 101, 3, 9, 9, 1002, 9, 3, 9, 1001, 9, 3, 9, 102, 5, 9, 9, 101, 4, 9, 9, 4, 9, 99, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 99, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 99, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 99, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 99, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 99};

void addAPerm(int perm[5]);
void swap(int *x, int *y);
void permutations(int k, int A[]);
int *pad5(int op, int *instruction);
int opcode(anIntcode *icP, int *instruction);
int pass(const int *candidate, int *instruction);
int pass2(const int *candidate, int *instruction);
int *passes(int *instruction);
int *passes2(int *instruction);
int comp(const void *a, const void *b);

int candidates[120][5];
int candidates2[120][5];
int currentPerm = 0;

int main(void) {
    int phases[] = {0, 1, 2, 3, 4};
    permutations(5, phases);

    int *instruction = malloc(5 * sizeof(int));
    if (instruction == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }
    for (int i = 0; i < 5; ++i) {
        instruction[i] = 0;
    }

    int *answer = passes(instruction);
    qsort(answer, 120, sizeof(int), comp);
    printf("Part A answer = %d. Correct = 368584\n", answer[119]);

    int phases2[] = {5, 6, 7, 8, 9};
    currentPerm = 0;
    permutations(5, phases2);
    for (int i = 0; i < 5; ++i) {
        instruction[i] = 0;
    }
    answer = passes2(instruction);
    qsort(answer, 120, sizeof(int), comp);
    printf("Part B answer = %d. Correct = 35993240\n", answer[119]);

    free(instruction);

    exit(0);
}

void addAPerm(int perm[5]) {
    memcpy(candidates[currentPerm], perm, 5 * sizeof(int));
    currentPerm++;
}

void swap(int *x, int *y) {
    const int temp = *x;
    *x = *y;
    *y = temp;
}

void permutations(const int k, int A[]) {// NOLINT(*-no-recursion)
    if (k == 1) {
        addAPerm(A);
    } else {
        for (int i = 0; i < k - 1; i++) {
            permutations(k - 1, A);
            if (k % 2 == 0) {
                swap(&A[i], &A[k - 1]);
            } else {
                swap(&A[0], &A[k - 1]);
            }
        }
        permutations(k - 1, A);
    }
}

int aParam(const anIntcode *icP, const int *instruction) {
    switch (instruction[0]) {
        case 0:// a-p-w
            return icP->memory[icP->pointer + offsetA];
        default:
            return 99;
    }
}

int bParam(const anIntcode *icP, const int *instruction) {
    switch (instruction[1]) {
        case 0:// b-p-r
            return icP->memory[icP->memory[icP->pointer + offsetB]];
        case 1:// b-i-r
            return icP->memory[icP->pointer + offsetB];
        default:
            return 99;
    }
}

int cParam(const anIntcode *icP, const int *instruction) {
    if (instruction[4] == 3) {
        switch (instruction[2]) {
            case 0:// c-p-w
                return icP->memory[icP->pointer + offsetC];
            default:
                return 99;
        }
    }
    switch (instruction[2]) {
        case 0:// c-p-r
            return icP->memory[icP->memory[icP->pointer + offsetC]];
        case 1:// c-i-r
            return icP->memory[icP->pointer + offsetC];
        default:
            return 99;
    }
}

int *pad5(const int op, int *instruction) {
    char buffer[6];
    snprintf(buffer, 6, "%05d", op);
    for (int i = 0; i < 5; i++) {
        instruction[i] = buffer[i] - 48;
    }
    return instruction;
}

int opcode(anIntcode *icP, int *instruction) {
    if (icP->isStopped == 1) {
        return 0;
    }
    instruction = pad5(icP->memory[icP->pointer], instruction);
    if (instruction[3] == 9) {
        icP->isStopped = 1;
        return 0;
    }
    switch (instruction[4]) {
        case 1:
            icP->memory[aParam(icP, instruction)] =
                    cParam(icP, instruction) +
                    bParam(icP, instruction);
            icP->pointer += 4;
            return 1;
        case 2:
            icP->memory[aParam(icP, instruction)] =
                    cParam(icP, instruction) *
                    bParam(icP, instruction);
            icP->pointer += 4;
            return 1;
        case 3:
            if (icP->phase == -1) {
                icP->memory[cParam(icP, instruction)] = icP->input;
            } else {
                if (icP->pointer == 0) {
                    icP->memory[cParam(icP, instruction)] = icP->phase;
                } else {
                    icP->memory[cParam(icP, instruction)] = icP->input;
                }
            }
            icP->pointer += 2;
            return 1;
        case 4: {
            if (icP->doesRecur == 1) {
                icP->output = cParam(icP, instruction);
                icP->pointer += 2;
                return 1;
            }
            icP->output = cParam(icP, instruction);
            icP->pointer += 2;
            return 0;
        }
        case 5:
            if (cParam(icP, instruction) != 0) {
                icP->pointer = bParam(icP, instruction);
            } else {
                icP->pointer += 3;
            }
            return 1;
        case 6:
            if (cParam(icP, instruction) == 0) {
                icP->pointer = bParam(icP, instruction);
            } else {
                icP->pointer += 3;
            }
            return 1;
        case 7:
            if (cParam(icP, instruction) < bParam(icP, instruction)) {
                icP->memory[aParam(icP, instruction)] = 1;
            } else {
                icP->memory[aParam(icP, instruction)] = 0;
            }
            icP->pointer += 4;
            return 1;
        case 8:
            if (cParam(icP, instruction) == bParam(icP, instruction)) {
                icP->memory[aParam(icP, instruction)] = 1;
            } else {
                icP->memory[aParam(icP, instruction)] = 0;
            }
            icP->pointer += 4;
            return 1;
        default:
            return 0;
    }
}

int pass(const int *candidate, int *instruction) {
    anIntcode icpA;
    icpA.input = 0;
    icpA.output = 0;
    icpA.phase = candidate[0];
    icpA.pointer = 0;
    memcpy(icpA.memory, memoryConstant, sizeof(memoryConstant));
    icpA.isStopped = 0;
    icpA.doesRecur = 1;

    int icReturn = 1;
    while (icReturn == 1) {
        icReturn = opcode(&icpA, instruction);
    }

    anIntcode icpB;
    icpB.input = icpA.output;
    icpB.output = 0;
    icpB.phase = candidate[1];
    icpB.pointer = 0;
    memcpy(icpB.memory, memoryConstant, sizeof(memoryConstant));
    icpB.isStopped = 0;
    icpB.doesRecur = 1;

    icReturn = 1;
    while (icReturn == 1) {
        icReturn = opcode(&icpB, instruction);
    }

    anIntcode icpC;
    icpC.input = icpB.output;
    icpC.output = 0;
    icpC.phase = candidate[2];
    icpC.pointer = 0;
    memcpy(icpC.memory, memoryConstant, sizeof(memoryConstant));
    icpC.isStopped = 0;
    icpC.doesRecur = 1;

    icReturn = 1;
    while (icReturn == 1) {
        icReturn = opcode(&icpC, instruction);
    }

    anIntcode icpD;
    icpD.input = icpC.output;
    icpD.output = 0;
    icpD.phase = candidate[3];
    icpD.pointer = 0;
    memcpy(icpD.memory, memoryConstant, sizeof(memoryConstant));
    icpD.isStopped = 0;
    icpD.doesRecur = 1;

    icReturn = 1;
    while (icReturn == 1) {
        icReturn = opcode(&icpD, instruction);
    }

    anIntcode icpE;
    icpE.input = icpD.output;
    icpE.output = 0;
    icpE.phase = candidate[4];
    icpE.pointer = 0;
    memcpy(icpE.memory, memoryConstant, sizeof(memoryConstant));
    icpE.isStopped = 0;
    icpE.doesRecur = 1;

    icReturn = 1;
    while (icReturn == 1) {
        icReturn = opcode(&icpE, instruction);
    }

    return icpE.output;
}

int *passes(int *instruction) {
    static int vcm[120];
    for (int i = 0; i < 120; i++) {
        vcm[i] = pass(candidates[i], instruction);
    }
    return vcm;
}

int comp(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int pass2(const int *candidate, int *instruction) {
    int eOutput = 0;
    int allStopped = 0;

    anIntcode icpA;
    icpA.input = 0;
    icpA.output = 0;
    icpA.phase = candidate[0];
    icpA.pointer = 0;
    memcpy(icpA.memory, memoryConstant, sizeof(memoryConstant));
    icpA.isStopped = 0;
    icpA.doesRecur = 0;

    anIntcode icpB;
    icpB.input = icpA.output;
    icpB.output = 0;
    icpB.phase = candidate[1];
    icpB.pointer = 0;
    memcpy(icpB.memory, memoryConstant, sizeof(memoryConstant));
    icpB.isStopped = 0;
    icpB.doesRecur = 0;

    anIntcode icpC;
    icpC.input = icpB.output;
    icpC.output = 0;
    icpC.phase = candidate[2];
    icpC.pointer = 0;
    memcpy(icpC.memory, memoryConstant, sizeof(memoryConstant));
    icpC.isStopped = 0;
    icpC.doesRecur = 0;

    anIntcode icpD;
    icpD.input = icpC.output;
    icpD.output = 0;
    icpD.phase = candidate[3];
    icpD.pointer = 0;
    memcpy(icpD.memory, memoryConstant, sizeof(memoryConstant));
    icpD.isStopped = 0;
    icpD.doesRecur = 0;

    anIntcode icpE;
    icpE.input = icpD.output;
    icpE.output = 0;
    icpE.phase = candidate[4];
    icpE.pointer = 0;
    memcpy(icpE.memory, memoryConstant, sizeof(memoryConstant));
    icpE.isStopped = 0;
    icpE.doesRecur = 0;

    while (allStopped == 0) {
        int icReturn = 1;
        while (icReturn == 1) {
            icReturn = opcode(&icpA, instruction);
        }
        icpB.input = icpA.output;
        icReturn = 1;
        while (icReturn == 1) {
            icReturn = opcode(&icpB, instruction);
        }
        icpC.input = icpB.output;
        icReturn = 1;
        while (icReturn == 1) {
            icReturn = opcode(&icpC, instruction);
        }
        icpD.input = icpC.output;
        icReturn = 1;
        while (icReturn == 1) {
            icReturn = opcode(&icpD, instruction);
        }
        icpE.input = icpD.output;
        icReturn = 1;
        while (icReturn == 1) {
            icReturn = opcode(&icpE, instruction);
        }
        icpA.input = icpE.output;

        eOutput = icpE.output;
        allStopped = icpE.isStopped;
    }
    return eOutput;
}

int *passes2(int *instruction) {
    static int vcm[120];
    for (int i = 0; i < 120; i++) {
        vcm[i] = pass2(candidates[i], instruction);
    }
    return vcm;
}
