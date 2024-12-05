CC=gcc
FLAGS=-pedantic -Wall -g -fprofile-arcs -ftest-coverage

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

hash_table_tests: hash_table_test.c hash_table.o linked_list.o common.o iterator.o
	$(CC) $(FLAGS) $^ -lcunit -o $@

linked_list_tests: linked_list_test.c linked_list.o common.o iterator.o
	$(CC) $(FLAGS) $^ -lcunit -o $@

iterator_tests: iterator_test.c linked_list.o iterator.o common.o
	$(CC) $(FLAGS) $^ -lcunit -o $@
	
freq_count: freq-count.c hash_table.o linked_list.o iterator.o common.o
	$(CC) $(FLAGS) $^ -o $@
	
clean:
	rm *.gcda *.gcno *.gcov *.o hash_table_tests linked_list_tests iterator_tests freq_count
	
.PHONY: clean
