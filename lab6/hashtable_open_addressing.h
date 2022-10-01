/*
/ File name: hashtable_open_addressing.h
/ Project number: CSCE 221 Lab 6, Spring 2022
/ Date file was created: April 1, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This header file is the implementation of the functions in class HashTable Open Address, implement the HashTable, insert and remove the value from the hash table, use open addressing method
/ to prevent collision from happening, returns the number of active elements in the table and the table size as well as return the position of a given value in the table
/ to help with searching and inserting keys to prevent collision.
*/

#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <functional>
#include <iostream>
#include <vector>
using std::vector;

template <class Key, class Hash = std::hash<Key> >
class HashTable
{
    enum entryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

public:
    // Member Types - do not modify
    using key_type = Key;
    using value_type = Key;
    using hash = Hash;
    using size_type = size_t;
    // you can write your code below this

private:
    // TODO: student implementation
    float elements = 0;
    float load = 0.5;

    struct Entry
    {
        Key element;
        entryType data;

        Entry(const Key &key = Key{}, entryType i = EMPTY) : element(key), data(i) {}
    };

    vector<Entry> table;

public:
    // name: constructor
    // precondition: the HashTable has not been initialized
    // postcondition: the HashTable has been initialized
    HashTable() : table(11) {}

    // name: copy constructor
    // precondition: the copy version of the HashTable has not been created
    // postcondition: the copy version of the HashTable has been created
    HashTable(const HashTable &other) : table(other.table) {}

    // name: destructor
    // precondition: the HashTable has not been destroyed
    // postcondition: the HashTable has been destroyed
    ~HashTable() { make_empty(); }

    // name: copy assignment operator
    // precondition: the HashTable has not been copied to the copy version
    // postcondition: the HashTable has been copied to the copy version
    HashTable &operator=(const HashTable &other)
    {
        if (this == &other)
        {
            return *this;
        }

        make_empty();
        table = other.table;
        return *this;
    }

    // name: constructor
    // precondition: the HashTable has not been initialized to the given size_type cells
    // postcondition: the HashTable make an empty table with the specified number of cells
    HashTable(size_type cells) : table(cells) { make_empty(); }

    // name: is_empty
    // precondition: do not know if the HashTable is empty or not
    // postcondition: return true if the HashTable is empty and false otherwise
    bool is_empty() const
    {
        if (elements != 0)
        {
            return false;
        }
        return true;
    }

    // name: size
    // precondition: do not know the number of active values in the table
    // postcondition: return the number of active values in the table
    size_t size() const { return elements; }

    // name: table_size
    // precondition: do not know the number of cells in the table
    // postcondition: return the number of cells in the table
    size_t table_size() const { return table.capacity(); }

    // name: make_empty
    // precondition: All the values in the HashTable has not been destroyed
    // postcondition: All the values in the HashTable has been destroyed
    void make_empty()
    {
        elements = 0;
        for (auto &entry : table)
        {
            entry.data = EMPTY;
        }
    }

    // name: my_hash
    // precondition: the Hashfunction has not been implemented
    // postcondition: the Hashfunction has been implemented
    size_t my_hash(const key_type &value) const
    {
        size_t hash_value = Hash{}(value);
        return hash_value % table.capacity();
    }

    // name: pow
    // precondition: the tableSize has not been altered to become prime number
    // postcondition: the returns the result of the pow operation from passing in 3 arguments that helps calculate the next prime number
    size_t pow(size_t x, size_t y, size_t z)
    {
        size_t result = 1;
        x = x % z;

        while (y > 0)
        {
            if (y & 1)
            {
                result = (result * x) % z;
            }
            // shift the value right by 1 bit
            y = y >> 1;
            x = (x * x) % z;
        }
        return result;
    }

    // name: next_prime
    // precondition: The Tablesize is not a prime number
    // postcondition: returns the next prime number of the Tablesize
    size_t next_prime(size_t value)
    {
        size_t is_prime = 0;
        while (value > 0)
        {
            // if it is a prime number
            if (pow(2, value - 1, value) == 1)
            {
                is_prime = value;
                break;
            }
            else
            {
                value++;
            }
        }
        return is_prime;
    }

    // name: insert
    // precondition: do not know if the value has been inserted into the HashTable or not
    // postcondition: return true if the insert was successful and false otherwise
    bool insert(const value_type &value)
    {
        size_t pos = position(value);

        if (is_active(pos))
        {
            return false;
        }

        table[pos].element = value;
        table[pos].data = ACTIVE;
        elements++;

        if ((elements / table.capacity()) > load)
        {
            rehash(next_prime(2 * table.capacity()));
        }

        return true;
    }

    // name: remove
    // precondition: the key has not been removed from the HashTable
    // postcondition: return 1 if the key was successfully removed from the HashTable and 0 otherwise
    size_t remove(const key_type &key)
    {
        size_t pos = position(key);

        if (!is_active(pos))
        {
            return 0;
        }

        table[pos].data = DELETED;
        elements--;
        return 1;
    }

    // name: is_active
    // precondition: do not know if the value in the table is present
    // postposition: return true if the value in the HashTable is present and false otherwise
    bool is_active(int x) const
    {
        return table[x].data == ACTIVE;
    }

    // name: contains
    // precondition: do not know if the HashTable contains the given key
    // postposition: return true if the HashTable contains the given key and false otherwise
    bool contains(const key_type &key)
    {
        return is_active(position(key));
    }

    // name: position
    // precondition: the position of the key is unknown
    // postcondition: return the index of the cell that would contain the specified value in the HashTable
    size_t position(const key_type &key) const
    {
        int offset = 1;
        size_t pos = my_hash(key);

        while (table[pos].data != EMPTY && table[pos].element != key)
        {
            pos += offset;
            offset += 2;
            if (pos >= table.size())
            {
                pos -= table.size();
            }
        }
        return pos;
    }

    // name: rehash
    // precondition: the HashTable has not been rehash
    // postcondition: the new number of buckets has been changed and the HashTable has been rehashed
    void rehash(size_type count)
    {
        vector<Entry> temp = table;
        table.resize(count);
        for (auto &entry : table)
        {
            entry.data = EMPTY;
        }

        elements = 0;
        for (auto &entry : temp)
        {
            if (entry.data == ACTIVE)
            {
                insert(entry.element);
            }
        }
    }

    // name: print_table
    // precondition: the HashTable has not been output to the console
    // postcondition: the HashTable has been pretty print to the console
    void print_table(std::ostream &os = std::cout) const
    {
        if (elements == 0)
        {
            os << "<empty>\n";
        }
        else
        {
            int i = 0;
            for (auto &entry : table)
            {
                if (entry.data == ACTIVE)
                {
                    os << i << " " << entry.element << "\n";
                    i++;
                }
                else
                {
                    i++;
                    os << i << "\n";
                }
            }
        }
    }

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};

#endif // HASHTABLE_OPEN_ADDRESSING_H
