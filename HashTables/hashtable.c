#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hashtable.h"
#include "kvp_list.h"

struct hashtable
{
    size_t len;
    
    size_t bucket_count;
    kvp_node *bucket_heads[];
};

uint64_t string_hash(const char *key) {
    // Shamelessly stolen from https://stackoverflow.com/a/2624210,
    // which is itself a variation on Java's String hash.
    // That's discussed nicely here:
    // https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/

    uint64_t hash = 7;
    for (size_t i = 0; i < strlen(key); i++) {
        hash = hash * 31 + key[i];
    }

    return hash;
}

hashtable *ht_make(size_t bucket_count)
{
    // bucket_heads is a flexible array member, so we have
    // to explicitly calculate the space we need for its
    // elements. Just using calloc here for the side-effect
    // of it zeroing the memory.
    hashtable *ht = calloc(1, sizeof(hashtable) + sizeof(kvp_node *) * bucket_count);
    ht->bucket_count = bucket_count;

    return ht;
}

size_t ht_len(const hashtable *ht) {
    return ht->len;
}

// Returns the index to use in the bucket_heads array for a given
// key in the given hashtable.
size_t ht_get_bucket_idx(const hashtable *ht, const char *key) {
    // The hash could be anything a uint64_t can handle, so we
    // mod down by the bucket count of the given table to get
    // a valid array index.
    return string_hash(key) % ht->bucket_count;
}

void ht_dump(const hashtable *ht) {
    printf("Hash table @ %p – %zu buckets, %zu entries\n", ht, ht->bucket_count, ht->len);
    if(ht->len == 0) {
        printf("Non-empty buckets:\n");
        for(size_t i = 0; i < ht->bucket_count; i++) {
            kvp_node *bucket_head = ht->bucket_heads[i];
            if(bucket_head) {
                printf("[%zu]: ", i);
                kvp_list_print(bucket_head);
            }
        }
    }

    printf("\n");
}

void ht_set(hashtable *ht, const char *key, int val){
    size_t bucket = ht_get_bucket_idx(ht, key);
    if (ht->bucket_heads[bucket] == NULL){
        ht->bucket_heads[bucket] = kvp_node_make(key, val);
        ht->len++;
    }else{
        kvp_node *n = kvp_list_find(ht->bucket_heads[bucket],key);
        if(n != NULL){
            n->value = val;
        }else{
            kvp_list_insert(ht->bucket_heads[bucket],key,val);
            ht->len++;
        }
    }
}

bool ht_get(const hashtable *ht, const char *key, int *value){
    size_t bucket = ht_get_bucket_idx(ht,key);
    if(ht->bucket_heads[bucket] == NULL){
        return false;
    }
    kvp_node* node = kvp_list_find(ht->bucket_heads[bucket],key);
    if(node != NULL){
        *value = node->value;
        return true;
    }
    return false;
}

bool ht_remove(hashtable *ht, const char *key){
    size_t bucket = ht_get_bucket_idx(ht,key);
    kvp_node *n = kvp_list_find(ht->bucket_heads[bucket],key);
    if(n == NULL){
        return false;
    }
    if(n->prev == NULL){
        ht->bucket_heads[bucket] = n->next;
    }
    kvp_list_remove(n);
    ht->len--;
    return true;
}

void ht_free(hashtable *ht){
    for(size_t i = 0; i < ht->bucket_count; i++){
        if(ht->bucket_heads[i] != NULL){
            kvp_list_free(ht->bucket_heads[i]);
        }
    }
    free(ht);
}
