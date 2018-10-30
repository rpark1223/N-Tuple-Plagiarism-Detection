/*
 * Robin Park
 * Hash Table Implementation File
 */

#include <iostream>
#include <functional>
#include "HashTable.h"
#include <string>

// purpose: allocates/initializes empty table of INITIAL_TABLE_SIZE
// parameters: none
// returns: none
HashTable::HashTable()
{
        currentTableSize = INITIAL_TABLE_SIZE;
        numItemsInTable  = 0;

        chainedTable = new ChainNode *[currentTableSize];

        for (int i = 0; i < currentTableSize; i++)
                chainedTable[i] = NULL;
}

// purpose: delete all nodes in list starting with given node
// parameters: ChainNode pointer
// returns: void
void HashTable::deleteList(ChainNode *node)
{
        ChainNode *temp = node;
        while (temp != NULL) {
                temp = temp->next;
                delete node;
                node = temp;
        }
}

// purpose: destructor
// parameters: none
// returns: none
HashTable::~HashTable()
{
        for (int i = 0; i < currentTableSize; i++)
                deleteList(chainedTable[i]);
        delete [] chainedTable;
}

// purpose: converts a key to a hash value
// parameters: KeyType
// returns: static size_t
static size_t hashValue(KeyType key)
{
        return hash<string>{}(key);
}

// purpose: insert a key-value pair into the table
// parameters: KeyType, ValueType
// returns: void
void HashTable::insert(KeyType key, ValueType value)
{
      checkCapacity();
      size_t slot = hashValue(key) % currentTableSize;

      // create a new node in the given slot if no word already exists there
      if (chainedTable[slot] == NULL) {
                chainedTable[slot] = createNode(key, value);
      } else {
                ChainNode *temp = chainedTable[slot];
                while (temp->next != NULL) {
                        temp = temp->next;
                }
                temp->next = createNode(key, value);
      }
}

// purpose: returns whether not a key-value pair exists in the table
// parameters: Keytype
// returns: bool
bool HashTable::contains(KeyType key)
{
        size_t slot = hashValue(key) % currentTableSize;
        if (getChainNode(chainedTable[slot], key) != NULL)
                return true;
        return false;
}

// purpose: returns the value associated with a key
// parameters: Keytype
// returns: ValueType
ValueType HashTable::get_value(KeyType key)
{
        size_t slot = hashValue(key) % currentTableSize;
        ChainNode *temp = getChainNode(chainedTable[slot], key);
        if (temp != NULL)
                return temp->value;
        return "";
}

// purpose: creates and returns a pointer to a new ChainNode
// parameters: KeyType, ValueType
// returns: ChainNode pointer
HashTable::ChainNode *HashTable::createNode(KeyType key, ValueType value)
{
        ChainNode *newNode = new ChainNode;
        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;

        numItemsInTable++;
        return newNode;
}

// purpose: returns the node in a list that contains the same key if it exists;
//          returns NULL otherwise
// parameters: ChainNode pointer, KeyType
// returns: ChainNode pointer
HashTable::ChainNode *HashTable::getChainNode(ChainNode *nodep, KeyType key)
{
        ChainNode *temp = nodep;

        while (temp != NULL) {
                if (temp->key == key)
                        return temp;
                temp = temp->next;
        }

        return NULL;
}

// purpose: checks load factor and expands table if it exceeds threshold of 0.7
// parameters: none
// returns: void
void HashTable::checkCapacity()
{
      double loadFactor = numItemsInTable / currentTableSize;

      if (loadFactor >= 0.7)
        expand();
}

// purpose: expands the HashTable
// parameters: none
// returns: void
void HashTable::expand()
{
        int oldSize = currentTableSize;
        currentTableSize *= 2;

        // create pointer to the old table, then reallocate memory for the new
        // table
        ChainNode **oldTable = chainedTable;
        chainedTable = new ChainNode *[currentTableSize];

        for (int i = 0; i < currentTableSize; i++)
               chainedTable[i] = NULL;
        numItemsInTable = 0;

        // insert each node in the list of each nonempty slot of the old table
        // into the new table
        for (int i = 0; i < oldSize; i++) {
                if (oldTable[i] != NULL) {
                        ChainNode *oldNode;
                        ChainNode *node = oldTable[i];
                        while (node != NULL) {
                            insert(node->key, node->value);
                            oldNode = node;
                            node = node->next;
                            delete oldNode;
                        }
                }
        }
        
        delete [] oldTable;
}