#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], p_hash_table table)
{
    if (lastname == NULL) return NULL;
    hashIndex index = hash(lastname,table);
    for(p_entry e = table->list[index]; e !=NULL;e=e->pNext){
        if (strcasecmp(lastname, e->lastName) == 0)
        {
            return e;
        }
    }
    return NULL;
}

int append(char lastName[], p_hash_table table)
{
    /* allocate memory for the new entry and put lastName */
    hashIndex index = hash(lastName,table);
    p_entry e;
    if ((e = malloc(sizeof(entry)))==NULL)return 1;
    e->pNext=table->list[index];
    table->list[index]=e;
    memcpy(e->lastName, lastName,strlen(lastName)+1);
    return 0;
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
