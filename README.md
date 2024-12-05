# Build Instructions
Compile and run tests:
Hash table tests: `make hash_table_tests && ./hash_table_tests` 
Linked list tests: `make linked_list_tests && ./linked_list_tests` 
Iterator tests: `make iterator_tests && ./iterator_tests` 

Compile and run word frequency count program: `make freq_count && ./freq_count {file_1} ... {file_n}`
Test files can be found in ./freq-count-test-files/

# Test coverage
We used gcov to obtain coverage statistics. These were the results:

## hash_table.c:
Line coverage: 98.58%
Branch coverage: 97.67%

## linked_list.c:
Line coverage: 90.97%
Branch coverage: 92.86%

## iterator.c:
Line coverage: 100.00%
Branch coverage: 100.00%

# Initial Profiling Results

## small.txt
top 3 functions: ioopm_hash_table_has_key, ioopm_hash_table_insert, strdup
strdup is library function

## 1k-long-words.txt
top 3 functions: ioopm_hash_table_has_key, ioopm_hash_table_insert, ioopm_hash_table_lookup
No library functions

## 10k-words.txt
top 3 functions: ioopm_hash_table_has_key, ioopm_hash_table_lookup, ioopm_hash_table_insert
No library functions

## 16k-words.txt
top 3 functions: ioopm_hash_table_has_key, ioopm_hash_table_insert, ioopm_hash_table_lookup
No library functions

## Q/A
- Are the top 3 functions in your code consistent across the inputs? Why? Why not?
Pretty much, but the ratio of how much time is spent in each is not.

- Is there some kind of trend? (Possibly several)
* The time spent in ioopm_hash_table_has_key grows significantly when the number of words increase.
* The time spent in ioopm_hash_table_insert and ioopm_hash_table_lookup is significantly more when words are long,
  meanwhile ioopm_hash_table_has_key is not impacted by it as much.

- Do the results correspond with your expectations?
That ioopm_hash_table_has_key takes longer when the number of words grow larger was expected,
since it loops through every bucket and also traverses through every element in every bucket,
so as more words are inserted into the hash table it will have to traverse through more elements.
The functions ioopm_hash_table_insert and ioopm_hash_table_lookup take significantly more time for
longer words, which we didn't foreshadow. The reason it that the hash functions for strings has O(n)
time complexity, where n is the length of the string.

- Based on these results, do you see a way to make your program go faster?
For ioopm_hash_table_has_key, Ii we use the hash function to determine which bucket the key has to be in,
then it only has to iterate through a singular bucket instead of all of them. Which would be quite a
significant improvement. 

Creating a hash function for strings that has O(1) time complexity would improve the performance
of insert and lookup in the hash table.

# Additional notes

- Error handling as done by `assert`. We check if the pointer to the list/hash table is not `NULL`.
- Error handling in iterators are the same, but with `ioopm_iterator_has_next` in some functions.
- Some functions require a valid defined function as argument.
- `ioopm_hash_table_remove` does not return the value that is removed.
