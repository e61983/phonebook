#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#include <sys/types.h>
#include <limits.h>
#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
typedef struct detail {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail, *p_detail;

typedef struct entry {
    char lastName[MAX_LAST_NAME_SIZE];
    p_detail detailInfo;
    struct entry *pNext;
} entry, *p_entry;

typedef uint hashIndex;
typedef struct hash_table {
    uint size;
    p_entry *list;
} hash_table, *p_hash_table;

#if defined(OPT)
entry *findName(char lastname[], p_hash_table table);
int append(char lastName[], p_hash_table table);
#else
entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);
#endif

p_hash_table create_hash_table(uint size);
hashIndex hash(char *key, p_hash_table table);

#endif
