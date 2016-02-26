#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead, p_hash_table table)
{
    if (lastname == NULL) return NULL;
    if (strcasecmp(lastname, table->list[hash(lastname,table)]->lastName) == 0)
    {
        return table->list[hash(lastname,table)];
    }
    return NULL;
}

entry *append(char lastName[], entry *e, p_hash_table table)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    memcpy(e->lastName, lastName,strlen(lastName)+1);
    e->pNext = NULL;
    hashIndex index = hash(e->lastName,table);
    table->list[index] = e;
 
    return e;
}

p_hash_table create_hash_table(uint size){
    if(size <1) return NULL;

    p_hash_table table=NULL;

    if((table=malloc(sizeof(hash_table)))==NULL) return NULL;

    if((table->list = malloc(sizeof(p_entry)*size))==NULL) return NULL;

    table->size=size;

    for(uint i =0; i < table->size; i++){
        table->list[i]=NULL;
    }

    return table;
}

hashIndex hash(char *key, p_hash_table table){
    hashIndex index = 0;
    for(;*key!='\0';key++){
        index += (index <<7)+*key;
    }
    return index % table->size;
}
