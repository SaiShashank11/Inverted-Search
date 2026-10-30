#include "inverted_search.h"

int file_exists(Flist *head, char *fileName)
{
    while(head)
    {
        if(strcmp(head->arr, fileName) == 0)
            return 1;

        head = head->link;
    }
    return 0;
}



int update_database(Hash_t *hashTable, Flist **head){

    char fileName[100];

    printf("Enter the file name to be updated: ");
    scanf("%99s", fileName);

    /* Check extension */
    char *ext = strrchr(fileName, '.');

    if(ext == NULL || strcmp(ext, ".txt") != 0)
    {
        printf("%s is not a .txt file\n", fileName);
        return FAILURE;
    }

    FILE *fptr = fopen(fileName, "r");

    if(fptr == NULL)
    {
        printf("ERROR: Failed to open file\n");
        return FAILURE;
    }

    fseek(fptr, 0 , SEEK_END);

    if(ftell(fptr) == 0)
    {
        printf("%s is empty\n", fileName);
        fclose(fptr);
        return FAILURE;
    }

    fclose(fptr);

    if(file_exists(*head, fileName)) return FILE_EXISTS;
    

    if(insert_fileName(fileName, head) == FAILURE)
        return FAILURE;

    Flist *temp = *head;

    while(temp->link != NULL)
        temp = temp->link;

    /* Update database using only the new file */
    if(create_database(temp, hashTable) == FAILURE)
    {
        printf("ERROR: Failed to update database\n");
        return FAILURE;
     }

    printf("INFO: Update is successful\n");

    return SUCCESS;
}