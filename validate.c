#include "inverted_search.h"

int read_and_validation(int argc, char **argv, Flist **head)
{
    for (int i = 1; i < argc; i++)
    {
        /* Check argv[i] extension is .txt or not */
        char *ext = strrchr(argv[i], '.');
        if(ext != NULL && strcmp(ext,".txt") == 0)
        {
            printf("%s is valid .txt file\n", argv[i]);

            /* Check the file is present or not */ 
            FILE *fptr = fopen(argv[i], "r");
            if(fptr != NULL)
            {
                /* Check the file is empty or not */
                fseek(fptr, 0, SEEK_END);
                if(ftell(fptr) == 0)
                    printf("%s is empty\n", argv[i]);
                
                /* Insert filename into Flist */
                else if(insert_fileName(argv[i], head) == FAILURE){
                    fclose(fptr);
                    return FAILURE;
                }
                fclose(fptr);
            }
            else
                printf("ERROR: File is not present\n");
        }
        else
            printf("%s is not a .txt file\n", argv[i]);
    }

    return SUCCESS;
}



int insert_fileName(char *fileName, Flist **head)
{
    Flist *newNode = malloc(sizeof(Flist));

    if(newNode == NULL)
        return FAILURE;

    newNode->arr = malloc(strlen(fileName) + 1);

    if(newNode->arr == NULL)
    {
        free(newNode);
        return FAILURE;
    }

    strcpy(newNode->arr, fileName);

    newNode->link = NULL;

    // If list is empty
    if(*head == NULL)
        *head = newNode;
    else
    {
        Flist *temp = *head;

        /* Go to last node */
        while (temp->link != NULL)
            temp = temp->link;

        temp->link = newNode;
    }

    return SUCCESS;
}