/**
 * @file hash_table.h
 * @author Mauritz Sjödin, Alvin Ljung Hallgren
 * @date 6 Oct 2024
 * @brief Simple hash table that maps keys to values.
 * Includes functions that operate on said hash table.
 * Error handling is done with `assert`; we check if the pointer to the hash table is not `NULL`.
 * The functions `ioopm_hash_table_apply_to_all`, `ioopm_hash_table_all` and `ioopm_hash_table_any` 
 * all requires the function argument to be a defined valid function.
 * 
 * Hash tables are stored on the heap, so they must be freed with `ioopm_hash_table_destroy`.
 */

#pragma once

#include <stdbool.h>
#include "common.h"

#define No_Buckets 17

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

typedef bool ioopm_ht_predicate(elem_t key, elem_t value, void *extra);
typedef void ioopm_ht_apply_function(elem_t key, elem_t *value, void *extra);
typedef int ioopm_hash_function(elem_t key);

/// @brief Create a new hash table
/// @param eq_func_keys Function for computing equality of keys
/// @param eq_func_values Function for computing equality of values
/// @param hash_function The hash function
/// @return A new empty hash tablehash_table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function *eq_func_keys, ioopm_eq_function *eq_func_values, ioopm_hash_function *hash_function);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key
elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
void ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief returns the number of key => value entries in the hash table
/// @param ht hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param ht hash table operated upon
/// @return true if the size is zero otherwise false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param ht hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param ht hash table operated upon
/// @return a pointer to a list of keys for hash table h
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param ht hash table operated upon
/// @return an array of values for hash table h
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param ht hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred, might not be needed
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_ht_predicate *pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred, might not be needed
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_ht_predicate *pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param ht hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun, might not be needed
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_ht_apply_function *apply_fun, void *arg);

/// @brief check if two keys are equal
/// @param ht hash table operated upon
/// @param a key 1
/// @param a key 2
/// @return true if they are equal otherwise false
bool ioopm_hash_table_keys_equal(ioopm_hash_table_t *ht, elem_t a, elem_t b);

/// @brief check if two values are equal
/// @param ht hash table operated upon
/// @param a value 1
/// @param a value 2
/// @return true if they are equal otherwise false
bool ioopm_hash_table_values_equal(ioopm_hash_table_t *ht, elem_t a, elem_t b);
