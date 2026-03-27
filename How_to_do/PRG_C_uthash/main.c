/**
 * Test uthash
 * Refer guide: [1] https://troydhanson.github.io/uthash/userguide.html
 */


/*
#include "uthash.h"
struct my_struct {
    int id;                    // KEY type integer
    char name[10];             //   + (or) KEY type array
    UT_hash_handle hh;         // makes this structure hashable
};

- uthash using above structure and a hash table `htable` manage them.
    + When a `my_struct` add into `htable` 

    a. KEY
    " As with any hash, every item must have a `unique key`. 
    Your application must enforce key uniqueness. 
    `Before you add` an item to the [hash table], you must first know 
    (if in doubt, check!) that the key is not already in use. 
    You can `check whether a key already exists` in the hash table using 
    `HASH_FIND()`. 
    ". From cite [1].

    b. Hash handle
    " The [UT_hash_handle] field must be present `in your structure`. 
    It is used for the internal bookkeeping that makes the hash work. 
    It does `not require initialization`. It can be named anything, but you 
    can simplify matters by naming it `hh`. This allows you to use the easier 
    "convenience" macros to add, find and delete items.
    " . From cite [1].

    c. How clean up occurs
    " Some have asked how uthash cleans up its internal memory. 
    The answer is simple: when you delete the final item from a hash table, 
    uthash releases all the internal memory associated with that hash table, 
    and sets its pointer to NULL.
    " . From cite [1].

    d. A hash is also a `doubly-linked list`
    "
    Iterating backward and forward through the items in the hash is possible 
    because of the hh.prev and hh.next fields. All the items in the hash can 
    be reached by repeatedly following these pointers, thus the hash is also 
    a doubly-linked list.
    " . From cite [1].

    e. Built-in hash functions
    "
    Internally, a hash function transforms a key into a bucket number. You 
    don’t have to take any action to use the default hash function, 
    currently Jenkins.
    " . From cite [1].

    f. Hash table expansion: [find in uthash.h]
        - find HASH_ADD_TO_BKT in uthash, point that hash table manage buckets by
                an dynamic array with linear expansion by HASH_BKT_CAPACITY_THRESH


        typedef struct UT_hash_bucket {
        struct UT_hash_handle *hh_head;
        unsigned count;

            * expand_mult is normally set to 0. In this situation, the max chain length
            * threshold is enforced at its default value, HASH_BKT_CAPACITY_THRESH. (If
            * the bucket's chain exceeds this length, bucket expansion is triggered).
            * However, setting expand_mult to a non-zero value delays bucket expansion
            * (that would be triggered by additions to this particular bucket)
            * until its chain length reaches a *multiple* of HASH_BKT_CAPACITY_THRESH.
            * (The multiplier is simply expand_mult+1). The whole idea of this
            * multiplier is to reduce bucket expansions, since they are expensive, in
            * situations where we know that a particular bucket tends to be overused.
            * It is better to let its chain length grow to a longer yet-still-bounded
            * value, than to do an O(n) bucket expansion too often.

        unsigned expand_mult;

        } UT_hash_bucket;



        // add an item to a bucket
        #define HASH_ADD_TO_BKT(head,hh,addhh,oomed)                                     \
        do {                                                                             \
        UT_hash_bucket *_ha_head = &(head);                                            \
        _ha_head->count++;                                                             \
        (addhh)->hh_next = _ha_head->hh_head;                                          \
        (addhh)->hh_prev = NULL;                                                       \
        if (_ha_head->hh_head != NULL) {                                               \
            _ha_head->hh_head->hh_prev = (addhh);                                        \
        }                                                                              \
        _ha_head->hh_head = (addhh);                                                   \
        if ((_ha_head->count >= ((_ha_head->expand_mult + 1U) * HASH_BKT_CAPACITY_THRESH)) \
            && !(addhh)->tbl->noexpand) {                                              \
            HASH_EXPAND_BUCKETS(addhh,(addhh)->tbl, oomed);                              \
            IF_HASH_NONFATAL_OOM(                                                        \
            if (oomed) {                                                               \
                HASH_DEL_IN_BKT(head,addhh);                                             \
            }                                                                          \
            )                                                                            \
        }                                                                              \
        } while (0)


    g. Sorting

    "
    The items in the hash are visited in "insertion order" when you follow the hh.next pointer. 
    You can sort the items into a new order using HASH_SORT.
    
    HASH_SORT(users, name_sort);
    
    The second argument is a pointer to a comparison function. It must accept two pointer arguments 
    (the items to compare), and must return an int which is less than zero, zero, or greater than zero,
    if the first item sorts before, equal to, or after the second item, respectively. 
    (This is the same convention used by strcmp or qsort in the standard C library).

        int sort_function(void *a, void *b) {
        // * compare a to b (cast a and b appropriately)
        // * return (int) -1 if (a < b)
        // * return (int)  0 if (a == b)
        // * return (int)  1 if (a > b)
        // *
        }


*/

// usr
#include "main.h"

/**
 * ***************************************************
 * Definition
 * ***************************************************
 */


typedef struct
{
    // User data fields
    int random_value;


    // UT HASH structure
    const char* key_str;       /* key type is string */
    UT_hash_handle hh;  /* makes this structure hashable */
} ut_hash_tb_t;


#define S_ARR_SIZE(arr)  sizeof(arr)/sizeof(arr[0]) 

/**
 * ***************************************************
 * Variables
 * ***************************************************
 */


/**
 * ***************************************************
 * Prototypes
 * ***************************************************
 */

        // int sort_function(void *a, void *b) {
        // // * compare a to b (cast a and b appropriately)
        // // * return (int) -1 if (a < b)
        // // * return (int)  0 if (a == b)
        // // * return (int)  1 if (a > b)
        // // *
        // }

// sort by string asc
// strcmp inside:
// <0	the first character that does not match has a lower value in a than in b
// 0	the contents of both strings are equal
// >0	the first character that does not match has a greater value in a than in b
static inline int uh_sort_key_type_string_asc(void *a, void *b);

// sort by string desc
static inline int uh_sort_key_type_string_desc(void *a, void *b);


// Print all nodes
void print_hash_table(ut_hash_tb_t* tb_root) {
    ut_hash_tb_t *elem, *tmp;
    HASH_ITER(hh, tb_root, elem, tmp) {
        printf("Key [%s], Ran [%d]\n", elem->key_str, elem->random_value);
    }
}


/**
 * ***************************************************
 * Code
 * 
 * A. Add node to table
 * - HASH_ADD_INT(head, intfield,add);    // hash by int value
 * - HASH_ADD_STR(head, strfield,add);   // hash by string
 *      + `strfield` and `intfield` is field name in struct, not value
 *          "
 *              Wait.. the parameter is a field name? 
 *              If you find it strange that id, which is the name of a field 
 *              in the structure, can be passed as a parameter… welcome to the 
 *              world of macros. Don’t worry; the C preprocessor expands this 
 *              to valid C code.
 *          ". From cite [1].
 *      
 * 
 * B. Check key duplicated before add node
 * - HASH_FIND_INT(head,findint,out)
 * - HASH_FIND_STR(head,findstr,out)
 * 
 *      + `out` is a temporary node keep return searched node
 *          + NULL if not exist
 *      
 * C. Replace (check duplicated before replace, return old value, user need free it)
 * - HASH_REPLACE_INT(head,intfield,add,replaced)
 * - HASH_REPLACE_STR(head,strfield,add,replaced)
 *      + `intfield`, `strfield` is field name in struct
 * 
 * D. Remove node out of hash table
 * - HASH_DEL(head,delptr)
 *      + caller need free `delptr` after that
 *      + because HASH_DEL not return success, using (B) HASH_FIND_... before and (optinal) 
 *          after HASH_DEL
 *      + using with HASH_ITER(hh,head,el,tmp) if delete and free (by caller) multiple node.
 *          becaue uthash not only hash table but also a doubly linked list
 *          + hh is name of `UT_hash_handle` field in defined structure
 * 
 * - (warn) HASH_CLEAR(hh, users);
 *      + Clean hash table but don't care free node.
 *      + Memory leak after that if caller miss node pointer need to be freed.
 * 
 * E. Sorting node with a comparasion fuction by caller
 * - HASH_SORT(head,cmpfcn)
 *      + `head` is root node of table
 *      + HASH_ADD... simple add a struture node in to `doubly linked list` and
 *          add into a bucket (doubly linked list) 
 *          in hash table (dynamic array of buckets (like vector) / ReHash).
 * 
 * 
 * F. Count
 * - HASH_COUNT(head)
 * 
 * => Searching: uthash using hash table:
 *      + HASH_ADD_..., HASH_REPLACE_..., HASH_DEL, HASH_COUNT (Update bucket)
 *      + HASH_FIND_...
 * => Iterating and Sorting: uthash using doubly linked list
 *      + HASH_ADD_..., HASH_REPLACE_..., HASH_DEL, HASH_COUNT (Update list)
 *      + HASH_ITER
 *      + HASH_SORT
 * ***********************************************************
 */

int main()
{
    const char k_arr[][10]= // max key size = 9 + 1 NULL
    {
        "key_num00","key_num01","key_num02","key_num03","key_num04",
        "key_num05","key_num06","key_num07","key_num08","key_num09",
    };

    const int k_arr_size = S_ARR_SIZE(k_arr);
    
    // First initial root node of hash table with NULL pointer
        // hash table pointer
    ut_hash_tb_t* tb_root = NULL;

        // Then some node need add to table
    ut_hash_tb_t* tb_node_i[S_ARR_SIZE(k_arr)] = {0};

        // Initial some node before add to hash table
    srand(time(NULL)); // using current time as a seed for random function

    fprintf(stderr,"Initializing node list:\n");

    {
        for(int i = 0 ; i < k_arr_size; ++ i )
        {
            tb_node_i[i] = (ut_hash_tb_t*)malloc(sizeof(ut_hash_tb_t));
            if(tb_node_i[i] == NULL) return UTH_ER_MALLOC_FAIL;

            // random value for structure
            tb_node_i[i]->random_value = rand()%1000; // 0 to RANDMAX (>=32767)

            // point to designed key
            tb_node_i[i]->key_str = k_arr[i];

            // Print result
            fprintf(stderr,"Key [%s], Ran [%d]\n", tb_node_i[i]->key_str, tb_node_i[i]->random_value);
        }

    }

    // 1. Add node to table
    fprintf(stderr,"\nAdding node list to table...\n");

    {
        ut_hash_tb_t* tmp_node;
        for(int i = 0 ; i < k_arr_size; ++ i )
        {
            // check duplicated key value before add to table
            HASH_FIND_STR(tb_root, tb_node_i[i]->key_str, tmp_node);
                // note check existed
            if(tmp_node != NULL)
                return UTH_ER_DUPLICATED_KEY_DETECTED;

            // then add to table
            HASH_ADD_STR(tb_root, key_str, tb_node_i[i]);
        }
    }

    // 2. Find node
    fprintf(stderr,"\nFinding node exist in hash table:\n");

    {
        ut_hash_tb_t* tmp_node;
        for(int i = 0 ; i < k_arr_size ; ++i)
        {
            // 
            HASH_FIND_STR(tb_root, tb_node_i[i]->key_str, tmp_node);

            // found, print node value
            if(tmp_node!=NULL)
            {
                fprintf(stderr, "Found key [%s], Ran [%d]\n", tmp_node->key_str, tmp_node->random_value);
            }
            else
            {
                fprintf(stderr, "Not Found key [%s]\n", tb_node_i[i]->key_str);
            }
        }
    }


    // 3. Sorting doubly linked list
    fprintf(stderr,"\n============== SORTING ================\n");

    // 3.1 ASC Ascending
    fprintf(stderr,"\nDoubly linked list sort ASC\n");
    HASH_SORT(tb_root, uh_sort_key_type_string_asc);

    {
        ut_hash_tb_t *elem, *tmp;
        HASH_ITER(hh,tb_root, elem, tmp)
        {
            fprintf(stderr, "Key [%s], Ran [%d]\n", elem->key_str, elem->random_value);
        }
    }

    // 3.2 DESC Descending
    fprintf(stderr,"\n============== SORTING ================\n");
    
    fprintf(stderr,"\nDoubly linked list sort DESC\n");
    HASH_SORT(tb_root, uh_sort_key_type_string_desc);

    {
        ut_hash_tb_t *elem, *tmp;
        HASH_ITER(hh,tb_root, elem, tmp)
        {
            fprintf(stderr, "Key [%s], Ran [%d]\n", elem->key_str, elem->random_value);
        }
    }


    // 4. Delete and clean

    // Delete odd nodes (key index 1,3,5,...)
    printf("\nDeleting odd nodes:\n");
    for(int i = 1; i < k_arr_size; i += 2) {
        ut_hash_tb_t* tmp;
        HASH_FIND_STR(tb_root, k_arr[i], tmp);
        if(tmp) {
            HASH_DEL(tb_root, tmp);
            printf("Deleted key [%s]\n", tmp->key_str);
            free(tmp);
        }
    }

    printf("\nRemaining nodes after deleting odd:\n");
    print_hash_table(tb_root);

    // Delete even nodes (key index 0,2,4,...)
    printf("\nDeleting even nodes:\n");
    for(int i = 0; i < k_arr_size; i += 2) {
        ut_hash_tb_t* tmp;
        HASH_FIND_STR(tb_root, k_arr[i], tmp);
        if(tmp) {
            HASH_DEL(tb_root, tmp);
            printf("Deleted key [%s]\n", tmp->key_str);
            free(tmp);
        }
    }

    printf("\nRemaining nodes after deleting even:\n");
    print_hash_table(tb_root);

    // Final clean-up (just in case)
    HASH_CLEAR(hh, tb_root);

    return 0;
}



// sort by string asc
// strcmp inside:
// <0	the first character that does not match has a lower value in a than in b
// 0	the contents of both strings are equal
// >0	the first character that does not match has a greater value in a than in b
static inline int uh_sort_key_type_string_asc(void *a, void *b)
{
    return strcmp( ((ut_hash_tb_t*)a)->key_str, ((ut_hash_tb_t*)b)->key_str );
}

// sort by string desc
static inline int uh_sort_key_type_string_desc(void *a, void *b)
{
    return -strcmp( ((ut_hash_tb_t*)a)->key_str, ((ut_hash_tb_t*)b)->key_str );
}

