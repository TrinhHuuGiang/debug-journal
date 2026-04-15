// Refer: 
//  - https://github.com/davegamble/cjson?tab=readme-ov-file#welcome-to-cjson
//  - https://github.com/TrinhHuuGiang/project-esp32/blob/master/JSON/note.md

/** 
 * @brief cJSON
 * 
 * 1. JSON data types: 
 *  - number: double, int. Normally it's double :v
 *  - string: "abc"
 *  - bool: true, false
 *  - null: null
 *  - object: { "key":123 },  { "key":"abc" }, ... but key is string
 *  - array: ["abc", 123, null, true, {"key":null}] 
 * 
 * 
 * 
 * --------------------------------------------------------------
 * -------------------- INIT/ADD/DELETE -------------------------
 * --------------------------------------------------------------
 * 
 * 2. Every value in cJSON also an object:
 *  - cJSON_CreateNumber
 *  - cJSON_CreateString (deep copy) or cJSON_CreateStringReference (just copy pointer)
 *  - cJSON_CreateTrue, cJSON_CreateFalse or cJSON_CreateBool
 *  - cJSON_CreateNull
 *  - cJSON_CreateArray or cJSON_CreateArrayReference (refer to an existing array)
 *  - cJSON_CreateObject or cJSON_CreateObjectReference (refer to an existing object)
 * 
 * 3. Add item to `object` or `array`:
 *  - cJSON_AddItemToArray                  : append Item to array
 *      or cJSON_AddItemReferenceToArray    : create refer to Item existing, append to array
 *      or cJSON_InsertItemInArray          : insert Item by index in array
 * 
 *  - cJSON_GetArraySize                : get array size
 *  - cJSON_GetArrayItem                : get array item by index. Browse from head -> tail O(n)
 *  - cJSON_ArrayForEach                : Browse and handle each step before go to next node.
 * 
 *  - cJSON_DetachItemFromArray             : remove item/refer out of array. But don't delete that.
 *  - cJSON_DeleteItemFromArray             : remove item/refer out of array. Then delete that.
 *                                            + if item is an reference, only refer to main object is deleted
 *    ------------------------
 * 
 *  - cJSON_AddItemToObject             : deep copy `key`       -> strdup: allocate new memory, deep copy key
 *  - cJSON_AddItemToObjectCS           : just refer to `key`   -> static memory or user manage memory for key
 *  - cJSON_AddItemReferenceToObject    : deep copy `key`. `value` add refer to an existing item.
 * 
 *  - cJSON_GetObjectItem                   : Get object item by `key` search with case insensitive
 *  - cJSON_GetObjectItemCaseSensitive      : Get object item by `key` search with case sensitive
 *  - cJSON_ArrayForEach                    : Browse and handle each step before go to next node {key:value}.
 * 
 *  - cJSON_DetachItemFromObjectCaseSensitive   : remove item/refer out of `object`. But don't delete that.
 *  - cJSON_DeleteItemFromObjectCaseSensitive   : remove item/refer out of `object`. Then delete that.
 *                                                  + if item is an reference, only refer to main object is deleted
 * 
 * 4. Delete item:
 *  - cJSON_Delete
 *      * Note that:
 *          + if an object deleted, cJSON will delete all child items owned by it.
 *          
 *          + one cJSON item should only belong to one parent (`object` or `array`)  
 *            if the same item is added into multiple parents without using
 *            `cJSON_AddItemReferenceTo...()`, deleting one parent may corrupt tree
 *            or cause double free / crash.
 * 
 *          + if item is a reference item (`cJSON_IsReference` flag),
 *            `cJSON_Delete()` only deletes the wrapper node,
 *            referenced child/value memory will not be freed.
 * 
 * 
 * --------------------------------------------------------------
 * -------------------- PARSE           -------------------------
 * --------------------------------------------------------------
 * Prerequisite: get a JSON format string
 * 
 * 5. Parse
 * 
 * --------------- (Not recommend) No safe in multithread ----------
 * - cJSON_Parse() : parse for string
 *      + syntax: cJSON *json = cJSON_Parse(string); 
 *      + return: NULL if FAIL, else return json parsed.
 * - cJSON_ParseWithLength() : parse for array with size
 *      + syntax: cJSON *json = cJSON_ParseWithLength(string, buffer_length);
 *     
 * - cJSON_GetErrorPtr()
 *      + return pointer to position can't parse
 *      + (warn Multithread) the position save internal pointer. 
 *          Other task can clear before main task read.
 * 
 * 
 * 
 * --------------- Better in multi-thread -------
 * - cJSON_ParseWithOpts
 *      (const char *value, const char **return_parse_end, cJSON_bool require_null_terminated)
 * 
 *      + require_null_terminated = 1:
 *          parse only success if JSON ends exactly at '\0'
 * 
 *      + require_null_terminated = 0:
 *          parse success immediately after valid JSON.
 *          Remaining characters are ignored.
 * 
 * - cJSON_ParseWithLengthOpts
 *      (const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated)
 * 
 * 
 * 
 * ---------------- Check value type after parse ---------
 * - cJSON_IsString(item)
 * - cJSON_IsNumber(item)
 * - cJSON_IsBool(item)
 * - cJSON_IsNull(item)
 * - cJSON_IsArray(item)
 * - cJSON_IsObject(item)
 * 
 * 
 * --------------------------------------------------------------
 * -------------------- PRINT JSON      -------------------------
 * --------------------------------------------------------------
 *  - cJSON_Print: make json object into string
 *      + systax: 
 *          char *string = cJSON_Print(json);
 *          if (string == NULL)
 *          {
 *              fprintf(stderr, "Failed to print monitor.\n");
 *          }
 * 
 *  - cJSON_free: free string after use
 * 
*/


#include <stdbool.h>
#include <stdio.h>
#include "cJSON.h"

bool JSON_parse_test();
bool JSON_encode_test();

int main(void)
{
    printf("----------------------- Parse\n");
 
    if(!JSON_parse_test()) return 1;

    printf("----------------------- Encode\n");

    if(!JSON_encode_test()) return 2;

    return 0;
}




bool JSON_parse_test()
{
    const char *text =
    "{"
    "\"uid\":123,"
    "\"name\":\"ESP32\","
    "\"enable\":true"
    "}";

    // const char *text =
    //     "{"
    //     "\"uid\":1-3,"
    //     "\"name\":\"ESP32\","
    //     "\"enable\":1"
    //     "}";


    // parse by cJSON_Parse or cJSON_ParseWithOpts
    cJSON *root = cJSON_Parse(text);
    if (root == NULL)
    {
        printf("Parse fail\n");
        return false;
    }

    // check is `object` or `array` or another data type
        // expect an `object`
    if( ! cJSON_IsObject(root) )
    {
        printf("JSON wrong format\n");
        return false;
    }

    // parse object field
    cJSON *uid    = cJSON_GetObjectItem(root, "uid");
    cJSON *name   = cJSON_GetObjectItem(root, "name");
    cJSON *enable = cJSON_GetObjectItem(root, "enable");

    if( !uid || !name || !enable)
    {
        printf("Object missing field\n\n");
    }

    if (cJSON_IsNumber(uid))
    {
        printf("uid = %d\n", uid->valueint);
    }
    else 
    {
        printf("\"uid\" not a number\n");
    }

    if (cJSON_IsString(name))
    {
        printf("name = %s\n", name->valuestring);
    }
    else 
    {
        printf("\"name\" not a string\n");
    }

    if (cJSON_IsBool(enable))
    {
        printf("enable = %s\n", cJSON_IsTrue(enable) ? "true" : "false");
    }
    else 
    {
        printf("\"enable\" not a boolean\n");
    }


    // delete after use , else leak
    cJSON_Delete(root);

    return true;
}



bool JSON_encode_test()
{
    // Create root object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        printf("Create root fail\n");
        return false;
    }

    // Add simple fields
    cJSON_AddNumberToObject(root, "uid", 60001);
    cJSON_AddStringToObject(root, "cmd", "info");
    cJSON_AddBoolToObject(root, "ok", 1);

    // Add nested object: data
    cJSON *data = cJSON_CreateObject();
    cJSON_AddStringToObject(data, "name", "ESP32");
    cJSON_AddNumberToObject(data, "version", 3);

    cJSON_AddItemToObject(root, "data", data);

    // Add array: values
    cJSON *values = cJSON_CreateArray();
    cJSON_AddItemToArray(values, cJSON_CreateNumber(10));
    cJSON_AddItemToArray(values, cJSON_CreateNumber(20));
    cJSON_AddItemToArray(values, cJSON_CreateNumber(30));

    cJSON_AddItemToObject(root, "values", values);

    // Convert cJSON tree -> JSON string
    char *json_text = cJSON_Print(root);
    if (json_text == NULL)
    {
        printf("Encode fail\n");
        cJSON_Delete(root);
        return false;
    }

    printf("%s\n", json_text);

    // Free memory
    cJSON_free(json_text);
    cJSON_Delete(root);

    return true;
    
}
