//
//  offsetcache.h
//  An offset cache that can be stored in kernel memory
//
//  Created by Sam Bingner on 03/28/2019.
//  Copyright © 2019 Sam Bingner. All rights reserved.
//

#ifndef _OFFSETCACHE_H
#define _OFFSETCACHE_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/queue.h>

typedef struct offset_entry {
    TAILQ_ENTRY(offset_entry) entries;
    uint64_t addr;
    char name[];
} offset_entry_t;

TAILQ_HEAD(offset_cache, offset_entry);

struct cache_blob {
    size_t size;
    struct offset_cache cache;
    offset_entry_t entries[];
};

void init_cache(void);
void destroy_cache(void);
void import_cache_blob(struct cache_blob *blob);
size_t export_cache_blob(struct cache_blob **newblob);
bool compare_cache_blob(struct cache_blob *blob);

bool remove_offset(const char *name);
void set_offset(const char *name, uint64_t addr);
uint64_t get_offset(const char *name);
size_t get_cache_blob_size(void);
struct cache_blob *create_cache_blob(size_t size);
size_t copy_cache_blob(struct cache_blob *blob);
void blob_rebase(struct cache_blob *blob, uint64_t old_base, uint64_t new_base);

void print_cache(void);

#endif
