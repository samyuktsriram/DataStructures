1. How to run this
    Just run the hash_table.c file. main() calls all the relevant testing functions. I ran into some strange errors with some functions on testing the code, but it runs perfectly on https://www.onlinegdb.com/ . If there is any trouble, please just run it there.
    You should see some output from the testing function that roughly tells you what is going on.

2. Implementation details
    This is a hash table implementation. Separate chaining is used to handle collisions.
    Reference: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus#putting-it-all-together

    Following the broad structure of the reference, but trying to do a few things differently:
    1. Implementing a more complex hash function -> using function pointers to switch and test
    2. Table doubling - did not work so commented out
    3. More comprehensive testing protocol

    I'm writing each function myself based on the reference, especially insert, delete and search.
    The basic hash function initially will create collisions in the testing module, which are handled using overflow buckets and separate chaining. This has been implemented with linked lists.
    The complex hash function does not create collisions. the testing functions

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
    Elements outside the table
        returns not found
    3. Delete
    Elements that are not in the table
        should return not in the table
    Elements in the table:
        ->in items
        ->head item of overflow chain
        ->item somewhere in the overfull chain
        ->different key but same hash value
    4. Hash Function
    Pass in a different hash function to the testing modules