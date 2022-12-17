1. How to run this
    Just run the hash_table.c file. main() calls all the relevant testing functions. I ran into some strange errors with some functions on testing the code, but it runs perfectly on https://www.onlinegdb.com/ . If there is any trouble, please just run it there.
    You should see some output from the testing function that roughly tells you what is going on. The entire table is printed after insertion, after the relevant deletions. Searches and deletions are logged with print statements.
    More info on the testing protocols can be found below.

2. Implementation details
    This is a hash table implementation. Separate chaining is used to handle collisions.
    Reference: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus#putting-it-all-together

    Following the broad structure of the reference, but trying to do a few things differently:
    1. Implementing a more complex hash function (based on djb2) -> using function pointers to switch and test
    2. Attempted to do table doubling, but I ran out of time and couldn't make it work
    3. More comprehensive testing protocols, with functions to test all the cases.

    Operations supported:
    1. Create item, overflow bucket, hashtable
    2. Insert
    3. Search
    4. Delete
    5. Print the entire table
    6. Pass in custom hash functions for each of the above (as an argument in the functions)
    7. Free (ran into issues running this locally, works on online compiler)

    I'm writing each function myself (especially insert, delete, search, print, and supporting hash function switching). Some setup of the data structures is based on the reference.
    The basic hash function initially will create collisions in the testing module, which are handled using overflow buckets and separate chaining. This has been implemented with linked lists. The testing module is run on the basic and complex hash function, you can compare the outputs and see that the complex function does not create overflows.

3. Testing modules
    The insert_delete_test and size_test functions tests all the following situations:
    1. Insert
    Adding elements over capacity
        Should return "The table is full"
    Same key, different value
        should add and update the value
    Different key, using overflow box
    2. Search
    Elements in the table
        -> in the items slot
        -> in the overflow slot
    Elements not in the table
        returns not found
    3. Delete
    Elements that are not in the table:
        should return not in the table
    Elements in the table:
        ->in items
        ->head item of overflow chain
        ->item somewhere in the overfull chain
        ->different key but same hash value index
    4. Hash Function
    Pass in a different hash function to the testing modules