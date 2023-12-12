#include "bits/stdc++.h"
using namespace std;

enum CollisionMethod
{
    SeparateChaining,
    DoubleHashing,
    CustomProbing
};
enum HashFunction
{
    Hash1,
    Hash2
};

int isPrime(int n)
{
    if (n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
int findNextPrime(int n)
{
    int ans;
    for (int i = n;; i++)
    {
        if (isPrime(i) == true)
        {
            ans = i;
            break;
        }
    }
    return ans;
}
class HashTable
{
private:
    int siz;
    int collisioncnt;
    int value;
    int c1, c2;
    int elementsCount;
    vector<vector<pair<string, int>>> table;
    CollisionMethod method;
    HashFunction hashfunction;
    void ReSize()
    {
        vector<pair<string, int>> temp;
        for (auto x : table)
        {
            for (auto y : x)
            {
                temp.push_back(y);
            }
        }
        int newSize = findNextPrime(2 * siz);
        siz = newSize;
        table.assign(newSize, vector<pair<string, int>>());
        collisioncnt = 0;
        value = 1;
        elementsCount = 0;
        for (auto word : temp)
        {
            Insert(word.first);
        }
    }

public:
    vector<vector<pair<string, int>>> getTable() { return table; }
    HashTable(int tableSize, CollisionMethod collisionMethod, HashFunction hashfnc, int c1_n = 0, int c2_n = 0)
    {
        method = collisionMethod;
        hashfunction = hashfnc;
        siz = findNextPrime(tableSize);
        table.resize(siz);
        collisioncnt = 0;
        value = 1;
        c1 = c1_n;
        c2 = c2_n;
        elementsCount = 0;
    }
    int Hash1(string key)
    {
        const int p = 31; // A prime number for better distribution
        long long hashValue = 0;
        long long pPow = 1;
        for (char c : key)
        {
            hashValue = (hashValue + (c - 'a' + 1) * pPow) % siz;
            pPow = (pPow * p) % siz;
        }
        return hashValue;
    }
    int Hash2(string key)
    {
        const int p = 53; // Another prime number for diversity
        long long hashValue = 0;
        long long pPow = 1;
        for (char c : key)
        {
            hashValue = (hashValue + (c - 'a' + 1) * pPow) % siz;
            pPow = (pPow * p) % siz;
        }
        return (hashValue) % siz; // Adding 1 to avoid hash value of 0
    }

    int AuxHash(string key)
    {
        int hash = 0;
        for (char c : key)
        {
            hash += (c - 'a' + 1);
        }
        return (1 + (hash % (siz - 1))) % siz;
    }
    void Insert(string key)
    {
        if ((double)elementsCount * 1.0 / siz >= .5)
        {
            ReSize();
        }
        int index;
        if (method == SeparateChaining)
        {
            if (hashfunction == HashFunction::Hash1)
                index = Hash1(key);
            else
                index = Hash2(key);
            bool already_inserted = false;
            for (auto entry : table[index])
            {
                if (entry.first == key)
                {
                    already_inserted = true;
                    break;
                }
            }
            if (!already_inserted)
            {
                if (table[index].size() != 0)
                {
                    collisioncnt++;
                    // cout << collisioncnt << endl;
                }
                table[index].push_back({key, value});
                value++;
                elementsCount++;
            }
        }
        else if (method == DoubleHashing)
        {
            bool already_in = false;
            int i = 0;
            if (hashfunction == HashFunction::Hash1)
                index = (Hash1(key) + i * AuxHash(key)) % siz;
            else
                index = (Hash2(key) + i * AuxHash(key)) % siz;
            i++;
            while (table[index].size() != 0)
            {
                if (table[index][0].first == key)
                {
                    already_in = true;
                    break;
                }
                if (hashfunction == HashFunction::Hash1)
                    index = (Hash1(key) + i * AuxHash(key)) % siz;
                else
                    index = (Hash2(key) + i * AuxHash(key)) % siz;
                i++;
            }
            if (!already_in)
            {
                if (hashfunction == HashFunction::Hash1)
                    index = (Hash1(key)) % siz;
                else
                    index = (Hash2(key)) % siz;
                i = 1;
                while (table[index].size() != 0)
                {
                    collisioncnt++;
                    if (hashfunction == HashFunction::Hash1)
                        index = (Hash1(key) + i * AuxHash(key)) % siz;
                    else
                        index = (Hash2(key) + i * AuxHash(key)) % siz;
                    i++;
                }
                table[index].push_back({key, value});
                value++;
                elementsCount++;
            }
        }
        else if (method == CustomProbing)
        {
            bool already_in = false;
            int i = 0;
            index = CustomHash(key, i);
            i++;
            while (table[index].size() != 0)
            {
                if (table[index][0].first == key)
                {
                    already_in = true;
                    break;
                }
                index = CustomHash(key, i);
                i++;
            }
            if (!already_in)
            {
                index = CustomHash(key, 0);
                i = 1;
                while (table[index].size() != 0)
                {
                    collisioncnt++;
                    // cout << collisioncnt << endl;
                    //  cout<<index<<endl;
                    index = CustomHash(key, i);
                    i++;
                }
                table[index].push_back({key, value});
                value++;
                elementsCount++;
            }
        }
    }

    int CustomHash(string &key, int i)
    {
        if (hashfunction == HashFunction::Hash1)
            return (Hash1(key) + c1 * i * AuxHash(key) + c2 * i * i) % siz;
        return (Hash2(key) + c1 * i * AuxHash(key) + c2 * i * i) % siz;
    }
    int getCollision() { return this->collisioncnt; }
    pair<int, bool> Search(string key)
    {
        int hashValue = (hashfunction == HashFunction::Hash1) ? Hash1(key) : Hash2(key);
        int probes = 1;
        if (method == SeparateChaining)
        {
            for (auto pair : table[hashValue])
            {
                if (pair.first == key)
                {
                    return {probes, 1};
                }
                probes++;
            }
        }
        else if (method == DoubleHashing)
        {
            int i = 1;
            while (table[hashValue].size() != 0)
            {
                if (table[hashValue][0].first == key)
                {
                    return {probes, 1};
                }
                if (hashfunction == HashFunction::Hash1)
                    hashValue = (Hash1(key) + i * AuxHash(key)) % siz;
                else
                    hashValue = (Hash2(key) + i * AuxHash(key)) % siz;
                i++;
                probes++;
            }
        }
        else if (method == CustomProbing)
        {
            int i = 1;
            while (table[hashValue].size() != 0)
            {
                if (table[hashValue][0].first == key)
                {
                    return {probes, 1};
                }
                hashValue = CustomHash(key, i);
                i++;
                probes++;
            }
        }
        return {probes, 0};
    }
    void Delete(string key)
    {
        int hashValue = (hashfunction == HashFunction::Hash1) ? Hash1(key) : Hash2(key);
        if (method == SeparateChaining)
        {
            for (auto it = table[hashValue].begin(); it != table[hashValue].end(); it++)
            {
                auto x = *it;
                if (x.first == key)
                {
                    table[hashValue].erase(it);
                    break;
                }
            }
        }
        else if (method == DoubleHashing)
        {
            int i = 1;
            while (table[hashValue].size() != 0)
            {
                if (table[hashValue][0].first == key)
                {
                    auto it = table[hashValue].begin();
                    table[hashValue].erase(it);
                    break;
                }
                if (hashfunction == HashFunction::Hash1)
                    hashValue = (Hash1(key) + i * AuxHash(key)) % siz;
                else
                    hashValue = (Hash2(key) + i * AuxHash(key)) % siz;
                i++;
            }
        }
        else if (method == CustomProbing)
        {
            int i = 1;
            while (table[hashValue].size() != 0)
            {
                if (table[hashValue][0].first == key)
                {
                    auto it = table[hashValue].begin();
                    table[hashValue].erase(it);
                    break;
                }
                hashValue = CustomHash(key, i);
                i++;
            }
        }
    }
};

string GenerateRandomWord(int minLength, int maxLength)
{
    char charset[] = "abcdefghijklmnopqrstuvwxyz";
    int charsetSize = sizeof(charset) - 1;
    int length = minLength + rand() % (maxLength - minLength + 1);
    string randomWord;
    for (int i = 0; i < length; ++i)
    {
        int randomIndex = rand() % charsetSize;
        randomWord += charset[randomIndex];
    }
    return randomWord;
}
vector<string> SelectRandomWords(vector<string> &words, int numToSelect)
{
    vector<string> selectedWords = words;
    random_shuffle(selectedWords.begin(), selectedWords.end());
    if (numToSelect < selectedWords.size())
    {
        selectedWords.resize(numToSelect);
    }
    return selectedWords;
}
int main()
{
    freopen("output.txt", "w", stdout);
    srand(static_cast<unsigned int>(time(0)));
    vector<string> random_words;
    int numWords = 10000;
    int minLength = 5;
    int maxLength = 10;
    for (int i = 0; i < numWords; ++i)
    {
        string randomWord = GenerateRandomWord(minLength, maxLength);
        random_words.push_back(randomWord);
    }
    vector<string> selectedWords = SelectRandomWords(random_words, 1000);
    int tablesize = 20000;
    HashTable ChainTable1(tablesize, SeparateChaining, Hash1);
    HashTable ChainTable2(tablesize, SeparateChaining, Hash2);
    HashTable DoubleHashingTable1(tablesize, DoubleHashing, Hash1);
    HashTable DoubleHashingTable2(tablesize, DoubleHashing, Hash2);
    HashTable CustomHashTable1(tablesize, CustomProbing, Hash1, 5, 13);
    HashTable CustomHashTable2(tablesize, CustomProbing, Hash2, 5, 13);
    for (auto it = random_words.begin(); it != random_words.end(); it++)
    {
        string word = *it;
        ChainTable1.Insert(word);
        ChainTable2.Insert(word);
        DoubleHashingTable1.Insert(word);
        DoubleHashingTable2.Insert(word);
        CustomHashTable1.Insert(word);
        CustomHashTable2.Insert(word);
    }
    int c1, c2, d1, d2, e1, e2;
    c1 = c2 = d1 = d2 = e1 = e2 = 0;
    for (auto it = selectedWords.begin(); it != selectedWords.end(); it++)
    {
        string word = *it;
        c1 += ChainTable1.Search(word).first;
        c2 += ChainTable2.Search(word).first;
        d1 += DoubleHashingTable1.Search(word).first;
        d2 += DoubleHashingTable2.Search(word).first;
        e1 += CustomHashTable1.Search(word).first;
        e2 += CustomHashTable2.Search(word).first;
    }
    cout << "\n \t \t \t FOR N' = " << tablesize << ":-\n";
    cout << "\t\t\t\t\t   Hash 1"
         << "\t\t\t\t\t\t  "
         << "Hash 2" << endl
         << "\t\t\t\tCollision Count \t"
         << "Average Probes\t\t"
         << "Collision Count\t\t"
         << "Average Probes" << endl;
    cout << "Chain Linking\t\t\t" << ChainTable1.getCollision() << "\t\t\t" << (double)c1 * 1.0 / selectedWords.size() << "\t\t\t\t" << ChainTable2.getCollision() << "\t\t\t" << (double)c2 * 1.0 / 1000 << endl;
    cout << "Double Hashing\t\t\t" << DoubleHashingTable1.getCollision() << "\t\t\t" << (double)d1 * 1.0 / selectedWords.size() << "\t\t\t\t" << DoubleHashingTable2.getCollision() << "\t\t\t" << (double)d2 * 1.0 / 1000 << endl;
    cout << "Custom Probing\t\t\t" << CustomHashTable1.getCollision() << "\t\t\t" << (double)e1 * 1.0 / selectedWords.size() << "\t\t\t\t" << CustomHashTable2.getCollision() << "\t\t\t" << (double)e2 * 1.0 / 1000 << endl;
    return 0;
}
