/*
/ File name: hashtable_separate_chaining.h
/ Project number: CSCE 221 Lab 6, Spring 2022
/ Date file was created: April 1, 2022
/ Section: 511
/ email address: vuthuynhi@tamu.edu
/ This header file is the implementation of the functions in class HashTable Separate Chaining, implement the HashTable, insert and remove the value from the hash table, use separte chaining method
/ to prevent collision from happening, accessing the value from a linked lists if there is collision and insert the value at the front of the linked list, return the load factor,
/ and rehash the HashTable if the total number of buckets has changed
*/

#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <stdexcept>
#include <functional>
#include <iostream>
using std::list;
using std::vector;

template <class Key, class Hash = std::hash<Key> >
class HashTable
{
public:
    // Member Types - do not modify
    using key_type = Key;
    using value_type = Key;
    using hash = Hash;
    using size_type = size_t;
    // you can write your code below this

private:
    // TODO: student implementation
    vector<list<Key> > table;
    float load;
    float elements = 0;

public:
    // name: constructor
    // precondition: Hastable has not been initialized
    // postcondition: Hashtable has been initialized
    HashTable() : table(11), load(1) {}

    // name: copy constructor
    // precondition: the HashTable does not have a copied version of it
    // postcondition: the HashTable has a copied version of it
    HashTable(const HashTable &other) : table(other.table), load(other.load) {}

    // name: destructor
    // precondition: Hashtable has not been destroyed
    // postcondition: Hashtable has been destroyed
    ~HashTable() { make_empty(); }

    // name: copy assignment operator
    // precondition: the HashTable did not copied to the copy version of it
    // postcondition: the HashTable has copied to the copy version of it
    HashTable &operator=(const HashTable &other)
    {
        if (&other != this)
        {
            table = other.table;
            load = other.load;
        }
        return *this;
    }

    // name: constructor
    // precondition: the HashTable has not been constructed by passing in the number of buckets
    // postcondition: the HashTable has been initialized with the number of buckets assigned with the max_load_factor assigned to 1
    HashTable(size_type buckets) : table(buckets), load(1)
    {
        max_load_factor(1);
    }

    // name: is_empty
    // precondition: Do not know if the Hashtable is empty or not
    // postcondition: return true if the Hashtable is empty and false otherwise
    bool is_empty() const
    {
        if (elements != 0)
        {
            return false;
        }
        return true;
    }

    // name: size_t
    // precondition: The size of the Hashtable is unknown
    // postcondition: return the size of the Hashtable
    size_t size() const { return elements; }

    // name: make_empty
    // precondition: The HashTable is not empty
    // postcondition: Delete all value in the hash table
    void make_empty()
    {
        elements = 0;
        for (auto &thisList : table)
        {
            thisList.clear();
        }
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

    // name: my_hash
    // precondition: the Hashfunction has not been implemented
    // postcondition: the Hashfunction has been implemented
    size_t my_hash(const key_type &value) const
    {
        size_t hash_value = Hash{}(value);
        return hash_value % bucket_count();
    }

    // name: insert
    // precondition: do not know if the value has not been inserted into the Hashtable
    // postcondition: return true if the value has been inserted successfully into the HashTable and false otherwise
    bool insert(const value_type &value)
    {
        auto &thisList = table[my_hash(value)];

        auto first = thisList.begin();
        auto last = thisList.end();

        while (first != last)
        {
            if (*first == value)
            {
                return false;
            }
            first++;
        }

        thisList.push_front(value);
        elements++;

        if (load_factor() > load)
        {
            rehash(next_prime(2 * bucket_count()));
        }
        return true;
    }

    // name: remove
    // precondition: the key has not been removed from the HashTable
    // postcondition: remove the specified value from the table, return number of elements removed (0 or 1).
    size_t remove(const key_type &key)
    {
        auto &thisList = table[my_hash(key)];

        auto first = thisList.begin();
        auto last = thisList.end();
        auto temp = first;

        while (first != last)
        {
            if (*first == key)
            {
                temp = first;
            }
            first++;
        }

        if (temp == thisList.end())
        {
            return 0;
        }

        thisList.erase(temp);
        elements--;
        return 1;
    }

    // name: contains
    // precondition: do not know if the HashTable contains the given value
    // postcondition: return true if the HashTable contains the given value and false otherwise
    bool contains(const key_type &key)
    {
        auto &thisList = table[my_hash(key)];
        if (std::find(thisList.begin(), thisList.end(), key) != thisList.end())
        {
            return true;
        }
        return false;
    }

    // name: bucket_count
    // precondition: do not know the HashTable bucket count
    // postcondition: return the number of bucket in HashTable
    size_t bucket_count() const { return table.size(); }

    // name: bucket_size
    // precondition: do not know the HashTable bucket size
    // postcondition: return the number of values in the specified bucket
    size_t bucket_size(size_t n) const
    {
        if (n >= table.capacity() || n < 0)
        {
            throw std::out_of_range("The bucket index is out of bounds");
        }
        auto &thisList = table[n];
        return thisList.size();
    }

    // name: bucket
    // precondition: do not know the index of the bucket that contains the given value
    // postcondition: return the the index of the bucket that contains the given value
    size_t bucket(const key_type &key) const
    {
        return my_hash(key);
    }

    // name: load_factor
    // precondition: do not know the the load factor the of Hash function
    // postcondition: return the the load factor
    float load_factor() const
    {
        return elements / bucket_count();
    }

    // name: max_load_factor
    // precondition: do not know the max load factor the of HashTable
    // postcondition: return the the max load factor of the HashTable
    float max_load_factor() const { return load; }

    // name: max_load_factor
    // precondition: the max load factor is not set
    // postcondition: set the maximum load factor of the HashTable, forced a rehash if the new maximum is less than the current load factor
    void max_load_factor(float mlf)
    {
        if (mlf <= 0)
        {
            throw std::invalid_argument("invalid load factor");
        }

        if (mlf < load)
        {
            load = mlf;
            rehash(bucket_count());
        }
        load = mlf;
    }

    // name: rehash
    // precondition: the HashTable has not been rehash
    // postcondition: the new number of buckets has been changed and the HashTable has been rehashed
    void rehash(size_type count)
    {
        vector<list<Key> > temp = table;
        for (auto &thisList : table)
        {
            thisList.clear();
        }

        table.resize(count);
        elements = 0;

        for (auto &thisList : temp)
        {
            for (auto &value : thisList)
            {
                insert(value);
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
            // print the vector list first in order from 0 to tablesize - 1
            for (auto &thisList : table)
            {
                os << i << " ";
                i++;

                // print the key, value pair
                for (auto &value : thisList)
                {
                    os << value << ", ";
                }
                os << "\n";
            }
        }
    }

    // Optional
    // HashTable(HashTable&& other);
    // HashTable& operator=(HashTable&& other);
    // bool insert(value_type&& value);
};

#endif // HASHTABLE_SEPARATE_CHAINING_H
