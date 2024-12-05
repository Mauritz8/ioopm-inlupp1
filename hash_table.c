#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "hash_table.h"
#include "common.h"
#include "linked_list.h"

// an entry in a bucket in a hash table
struct entry
{
  elem_t key;      // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  // an array of buckets used to store the data
  // each bucket is a linked list
  entry_t buckets[No_Buckets];
  // a pointer to a function that checks if two keys in the hash table are the same
  ioopm_eq_function *eq_func_keys;
  // a pointer to a function that checks if two values in the hash table are the same
  ioopm_eq_function *eq_func_values;
  // The hash function the hash table will use
  ioopm_hash_function *hash_func;
};

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function *eq_func_keys, ioopm_eq_function *eq_func_values, ioopm_hash_function *hash_function)
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  result->eq_func_keys = eq_func_keys;
  result->eq_func_values = eq_func_values;
  result->hash_func = hash_function;
  return result;
}

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *return_entry = malloc(sizeof(entry_t));
  return_entry->key = key;
  return_entry->value = value;
  return_entry->next = next;
  return return_entry;
}

static void entry_destroy(entry_t *entry)
{
  assert(entry != NULL);
  free(entry);
}

/* void hash_table_destroy_bucket2(entry_t *bucket)
{
  if (bucket == NULL)
  {
    return;
  }
  
  entry_t *next_entry = bucket->next;
  free(bucket);
  hash_table_destroy_bucket2(next_entry);
}

void ioopm_hash_table_clear2(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; i++)
  {
    hash_table_destroy_bucket2(ht->buckets[i].next);
    ht->buckets[i].next = NULL;
  }
} */

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int bucket = 0; bucket < No_Buckets; bucket++)
  {
    entry_t *current_bucket = ht->buckets[bucket].next;
    entry_t *bucket_tmp = current_bucket;

    while (current_bucket != NULL)
    {
      current_bucket = current_bucket->next;
      entry_destroy(bucket_tmp);
      bucket_tmp = current_bucket;
    }

    ht->buckets[bucket].next = NULL;
  }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);

  ioopm_hash_table_clear(ht);
  free(ht);
}

// Returns a pointer to the entry before the one we are looking for
static entry_t *find_previous_entry_for_key(entry_t *bucket, elem_t key, ioopm_eq_function *eq_func_keys)
{
  assert(bucket != NULL);

  entry_t *current_bucket = bucket;

  while (current_bucket->next != NULL)
  {
    if (eq_func_keys(current_bucket->next->key, key))
    {
      return current_bucket;
    }
    
    current_bucket = current_bucket->next;
  }
  
  return current_bucket;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  assert(ht != NULL);

  int bucket = abs(ht->hash_func(key)) % No_Buckets;
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->eq_func_keys);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && ht->eq_func_keys(next->key, key))
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}


elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  assert(ht != NULL);

  int bucket = abs(ht->hash_func(key)) % No_Buckets;
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->eq_func_keys);
  entry_t *next = tmp->next;

  if (next && ht->eq_func_keys(next->key, key))
  {
    return &next->value;
  }
  else
  {
    return NULL;
  }
}

void ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  assert(ht != NULL);

  int bucket = abs(ht->hash_func(key)) % No_Buckets;
  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->eq_func_keys);
  entry_t *next_entry = prev->next;

  if (next_entry != NULL || ht->eq_func_keys(next_entry->key, key))
  {
    prev->next = next_entry->next;
    entry_destroy(next_entry);
  }
}

static size_t bucket_size(entry_t *bucket)
{
  return bucket == NULL ? 0 : 1 + bucket_size(bucket->next);
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  size_t size = 0;

  for (int bucket = 0; bucket < No_Buckets; bucket++)
  {
    // subtract 1 because of sentinel
    size += bucket_size(&ht->buckets[bucket]) - 1;
  }
  return size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);
  return ioopm_hash_table_size(ht) == 0;
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);

  ioopm_list_t *keys = ioopm_linked_list_create(ht->eq_func_keys);

  for (int bucket = 0; bucket < No_Buckets; bucket++)
  {
    entry_t *current_bucket = ht->buckets[bucket].next;
    
    while (current_bucket != NULL)
    {
      ioopm_linked_list_append(keys, current_bucket->key);
      current_bucket = current_bucket->next;
    }
  }

  return keys;
}

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  assert(ht != NULL);

  ioopm_list_t *values = ioopm_linked_list_create(ht->eq_func_values);

  for (int bucket = 0; bucket < No_Buckets; bucket++)
  {
    entry_t *current_bucket = ht->buckets[bucket].next;
    
    while (current_bucket != NULL)
    {
      ioopm_linked_list_append(values, current_bucket->value);
      current_bucket = current_bucket->next;
    }
  }

  return values;
}

struct elem_equal_data
{
  elem_t element;
  ioopm_eq_function *func;
};

static bool key_equal(elem_t key, elem_t value, void *extra)
{
  struct elem_equal_data *key_data = (struct elem_equal_data *) extra;
  return key_data->func(key_data->element, key);
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  assert(ht != NULL);

  struct elem_equal_data key_data = {
    .element = key,
    .func = ht->eq_func_keys,
  };
  return ioopm_hash_table_any(ht, key_equal, &key_data);
}

static bool value_equal(elem_t key, elem_t value, void *extra)
{
  struct elem_equal_data *value_data = (struct elem_equal_data *) extra;
  return value_data->func(value_data->element, value);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  assert(ht != NULL);

  struct elem_equal_data key_data = {
    .element = value,
    .func = ht->eq_func_values,
  };
  
  return ioopm_hash_table_any(ht, value_equal, &key_data);
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_ht_predicate *pred, void *arg)
{
  assert(ht != NULL && pred != NULL);

  for (int bucket = 0; bucket < No_Buckets; bucket++)
  {
    entry_t *current_bucket = ht->buckets[bucket].next;

    while (current_bucket != NULL)
    {
      if (!pred(current_bucket->key, current_bucket->value, arg))
      {
        return false;
      }
      
      current_bucket = current_bucket->next;
    }
  }
  return true;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_ht_predicate *pred, void *arg)
{
  assert(ht != NULL && pred != NULL);

  for (int bucket = 0; bucket < No_Buckets; bucket++)
  {
    entry_t *current_bucket = ht->buckets[bucket].next;

    while (current_bucket != NULL)
    {
      if (pred(current_bucket->key, current_bucket->value, arg))
      {
        return true;
      }

      current_bucket = current_bucket->next;
    }
  }
  return false;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_ht_apply_function *apply_fun, void *arg)
{
  assert(ht != NULL && apply_fun != NULL);

  for (int bucket = 0; bucket < No_Buckets; bucket++)
  {
    entry_t *current_bucket = ht->buckets[bucket].next;

    while (current_bucket != NULL)
    {
      apply_fun(current_bucket->key, &current_bucket->value, arg);
      current_bucket = current_bucket->next;
    }
  }
}

bool ioopm_hash_table_keys_equal(ioopm_hash_table_t *ht, elem_t a, elem_t b)
{
  assert(ht != NULL);
  return ht->eq_func_keys(a, b);  
}

bool ioopm_hash_table_values_equal(ioopm_hash_table_t *ht, elem_t a, elem_t b)
{
  assert(ht != NULL);
  return ht->eq_func_values(a, b);  
}

