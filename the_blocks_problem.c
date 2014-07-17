/* @JUDGE_ID: 21929EL 101 C "Linked Lists" */ 
/******************************************************************************
   Author: Oktay Sancak
   Date: 22.08.2006
 ******************************************************************************/

#include <stdio.h>
#include <string.h>

struct block {
    int id;
    struct block* up;
    struct block* down;
    int index;
};

void move_onto(struct block* a, struct block* b) {
    if (b->up != NULL) {
        b->up->down = a;
        a->up = b->up;
    }
    
    b->up = a;
    a->down = b;
    a->index = b->index;
}

void move_over(struct block* a, struct block* b) {
    if (a->down != NULL) {
        a->down->up = NULL;
    } 
     
    while (b->up != NULL) {
        b = b->up;
    }
    
    b->up = a;
    a->up = NULL;
    a->down = b;
    a->index = b->index;
}

void pile_onto(struct block* a, struct block* b) {
    struct block* top_block = a; 
 
    if (a->down != NULL) {
        a->down->up = NULL;
    } 
     
    do {
        top_block->index = b->index;
        top_block = top_block->up;
    } while (top_block != NULL);
    
    if (b->up != NULL) {
        b->up->down = top_block;
        top_block->up = b->up;
    }
    
    b->up = a;
    a->down = b;
}

void pile_over(struct block* a, struct block* b) {
    if (a->down != NULL) {
        a->down->up = NULL;
    } 
     
    while (b->up != NULL) {
        b = b->up;
    }
    
    a->down = b;
    b->up = a;
     
    do {
        a->index = b->index;
        a = a->up;
    } while (a != NULL);
}

int main() {
    int i, j, block_count, a, b;
    char move_or_pile[5];
    char onto_or_over[5];
    FILE* file = fopen("data.in", "r");
    fscanf(file, "%d\n", &block_count); // %c !!
    struct block* block_pointer = NULL;
    struct block* blocks = (struct block*) malloc(block_count * sizeof(struct block));
    
    for (i = 0; i < block_count; i++) {
        blocks[i].id = i;
        blocks[i].up = NULL;
        blocks[i].down = NULL;
        blocks[i].index = i;
    }
    
    while (fscanf(file, "%s %d %s %d\n", &move_or_pile, &a, &onto_or_over, &b) == 4) {
        if ((a != b) && (blocks[a].index != blocks[b].index)) {
            if (strcmp(move_or_pile, "move") == 0) {
                if (strcmp(onto_or_over, "onto") == 0) {
                    move_onto(&blocks[a], &blocks[b]);
                }
                else {
                    move_over(&blocks[a], &blocks[b]);
                }
            } 
            else {       
                if (strcmp(onto_or_over, "onto") == 0) {
                    pile_onto(&blocks[a], &blocks[b]);
                }
                else {
                    pile_over(&blocks[a], &blocks[b]);
                }
            }
        } 
    }
    
    for (i = 0; i < block_count; i++) {
        printf("%d:", i);
        
        for (j = 0; j < block_count; j++) {
            if ((blocks[j].index == i) && (blocks[j].down == NULL))
            {
                block_pointer = &blocks[j];
                
                while (block_pointer != NULL)
                {
                    printf(" %d", block_pointer->id);
                    block_pointer = block_pointer->up;
                }

                break;
            }
        }
        
        printf("\n");
    }
    
    free(blocks);
    fclose(file);
    
    getch();
    return 0;
}
