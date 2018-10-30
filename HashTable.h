/*
 * Robin Park
 * Hash Table Header File
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
using namespace std;

typedef string   KeyType;

typedef string   ValueType;

class HashTable
{
        public:
            	HashTable();
            	~HashTable();

            	void insert(KeyType key, ValueType value);
                bool contains(KeyType key);
                ValueType get_value(KeyType key);

        private:

                struct ChainNode {
                    KeyType    key;
                    ValueType  value;
                    ChainNode *next;
                };

            	static const int INITIAL_TABLE_SIZE = 23;
                    int currentTableSize;
                    int numItemsInTable;

            	ChainNode  **chainedTable;

            	void expand();
                ChainNode *createNode(KeyType key, ValueType value);
                ChainNode *getChainNode(ChainNode *nodep, KeyType key);
                void deleteList(ChainNode *node);
                void checkCapacity();
};
#endif
