#include "inverted_search.h"

int main(int argc, char **argv){
    Flist *head = NULL;
    Hash_t hashTable[27];

    for(int i = 0; i < 27; i++){
        hashTable[i].index = i;
        hashTable[i].link = NULL;
    }

    if(read_and_validation(argc, argv, &head) == SUCCESS){
        printf("INFO: Read and validation is successful\n");
        
        int database_created = 0;
        int choice;
        while (1)
        {
            printf("\n1. Create Database\n2. Display Database\n3. Search Database\n4. Update Database\n5. Save Database\n6. Exit\n");
            printf("Enter your choice: ");
            if(scanf("%d", &choice) != 1){
                printf("Invalid input. Please enter a number.\n");
                while(getchar() != '\n');
                continue;
            }

            switch(choice){

                case 1:
                    if(database_created){
                        printf("ERROR: Database already created\n");
                        break;
                    }

                    if(create_database(head, hashTable) == FAILURE)
                    {
                        printf("ERROR: Failed to create database\n");
                        return FAILURE;
                    }

                    database_created = 1;
                    printf("INFO: Created database successfully\n");
                    break;

                case 2:
                    if(!database_created){
                        printf("ERROR: Create database first\n");
                        break;
                    }

                    if(display_database(hashTable) == FAILURE)
                    {
                        printf("ERROR: Failed to display database\n");
                        return FAILURE;
                    }
                    break;

                case 3:
                    if(!database_created)
                    {
                        printf("ERROR: Create database first\n");
                        break;
                    }

                    if(search_database(hashTable) == FAILURE)
                    {
                        printf("ERROR: Failed to search database\n");
                        return FAILURE;
                    }
                    break;

                case 4:
                {
                    if(!database_created)
                    {
                        printf("ERROR: Create database first\n");
                        break;
                    }

                    int result = update_database(hashTable, &head);
                    if(result == FILE_EXISTS)
                    {
                        printf("ERROR: File already exists in database\n");
                        break;
                    }
                    if(result == FAILURE)
                    {
                        printf("ERROR: Failed to update database\n");
                        return FAILURE;
                    }
                    break;
                }

                case 5:
                    if(!database_created)
                    {
                        printf("ERROR: Create database first\n");
                        break;
                    }

                    if(save_database(hashTable) == FAILURE)
                    {
                        printf("ERROR: Failed to save database\n");
                        return FAILURE;
                    }
                    break;

                case 6:
                    free_database(hashTable);
                    free_flist(&head);
                    printf("Exiting...Done!\n");
                    return 0;

                default:
                    printf("Invalid choice\n");
            }
        }
    }

    else{
        printf("ERROR: Read and validation failed\n");
    }

    return 0;
}