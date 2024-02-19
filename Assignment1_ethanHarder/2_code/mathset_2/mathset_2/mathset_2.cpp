
#include <iostream>
#include <vector>
using namespace std;

class Set
{
private:
    vector<int> set;

public:
    void Add(int newValue)
    {
        if (!Contains(newValue))
        {
            set.push_back(newValue);
        }
    }

    bool Contains(int valueToCheck) const //trying to get in the habit of const-ing functions that don't modify.
    {
        for (int num : set) 
        {
            if (num == valueToCheck) 
            {
                return true;
            }
        }
        return false;
    }

    void Remove(int victim) //you didnt ask for this one, but I only realised that when I was done it. might as well keep it in.
    {
        for (auto search = set.begin(); search != set.end(); ++search) //probably the ugliest for loop I've seen. vectors are weird.
        {
            if (*search == victim)
            {
                set.erase(search);
                return;
            }
        }
    }

    void Union(Set s2)
    {
        for (auto scan = s2.set.begin(); scan != s2.set.end(); ++scan)
        {
            Add(*scan); //should add all the values that are not going to be duplicates, since the Contain check is in Add
        }
    }

    Set intersection(const Set& s2)
    {
        Set result;

        for (int compare : set) 
        {
            if (s2.Contains(compare)) 
            {
                result.Add(compare);
            }
        }

        return result;
    }

    bool SubsetCheck(const Set& s2) const 
    {
        for (int compare : s2.set) {
            if (!Contains(compare)) {
                return false; // If any element of s2 is not in this set, it's not a subset
            }
        }
        return true;
    }
};
