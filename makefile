CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = inverted_search

SRC = main.c create_database.c display_database.c search_database.c save_database.c update_database.c validation.c cleanup.c

$(TARGET): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "Build successful: $(TARGET)"
	@echo "Run using: ./inverted_search file1.txt file2.txt file3.txt"

clean:
	@rm -f $(TARGET)
	@echo "Clean successful"