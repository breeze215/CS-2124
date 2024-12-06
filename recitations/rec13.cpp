// rec13
// Uvindu Salgado

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

void printListIter(const list<int>& l){
    for(list<int>::const_iterator iter = l.begin(); iter != l.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
}

void printListFor(const list<int>& l){
    for(int val : l){
        cout << val <<  " ";
    }
    cout << endl;
}

void printListAuto(const list<int>& l){
    for(auto iter = l.begin(); iter != l.end(); ++++iter){
        cout << *iter << " ";
    }
    cout << endl;
}

list<int>::const_iterator findList(const list<int>& l, int val){
    for(list<int>::const_iterator iter = l.begin(); iter != l.end(); ++iter){
        if(*iter == val) return iter;
    }
    return l.end();
}

auto findListAuto(const list<int>& l, int val){
    for(auto iter = l.begin(); iter != l.end(); ++iter){
        if(*iter == val) return iter;
    }
    return l.end();
}

bool predicate1(int val) { return (val & 1) == 0; }

class Predicate1{
public:
    bool operator()(int val) { return (val & 1) == 0; }
};

template <typename a, typename b>
a ourFind(a start, a end, b target){
    for(a p = start; p != end; ++p){
        if(*p == target) return p;
    }
    return end;
}

void countDistinctWordVec(const string& filename){
    ifstream ifs(filename);
    string currWord;
    vector<string> collection;
    while(ifs >> currWord){
        if(find(collection.begin(), collection.end(), currWord) == collection.end()){
            collection.push_back(currWord);
        }
    }
    ifs.close();
    cout << "Number of distinct words in the vector = " << collection.size() << endl;
    //for(const string& word : collection){
        //cout << word << " ";
    //}
}

void countDistinctWordSet(const string& filename){
    ifstream ifs(filename);
    string currWord;
    set<string> collection;
    while(ifs >> currWord){
        if(find(collection.begin(), collection.end(), currWord) == collection.end()){
            collection.insert(currWord);
        }
    }
    ifs.close();
    cout << "Number of distinct words in the vector = " << collection.size() << endl;
    //for(const string& word : collection){
        //cout << word << " ";
    //}
}

void countDistinctWordMap(const string& filename) {
    ifstream ifs(filename);
    string curr_word;
    map<string, vector<int>> collection;
    int position = 0;
    while (ifs >> curr_word) {
        ++position;
        collection[curr_word].push_back(position);
    }
    ifs.close();
    cout << "Number of Distinct Words: " << collection.size() << endl;
    //for(auto entry: collection){
        //cout << entry.first << ": ";
        //for(int val: entry.second){
            //cout << val << " ";
        //}
    //}
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v{1,2,3,4,5,6};
    for(int val : v){
        cout << val << " ";
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> l(v.begin(), v.end());
    for( int val : l){
        cout << val << " ";
    }

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v.begin(), v.end());
    for(int val : v){
        cout << val << " ";
    }
    for( int val : l){
        cout << val << " ";
    }
    
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for(size_t i = 0; i < v.size(); i+= 2){
        cout << v[i] << " ";
    }
    
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    //for(size_t i = 0; i < l.size(); i+= 2){
        //cout << l[i] << " ";
    //}

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for(vector<int>::iterator iter = v.begin(); iter != v.end(); iter += 2){
        cout << *iter  << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for(list<int>::iterator iter = l.begin(); iter != l.end(); ++++iter){
        cout << *iter  << " ";
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    l.sort();
    for(int val : l){
        cout << val << " ";
    }

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printListIter(l);

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListFor(l);

    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printListAuto(l);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << *findList(l, 4);

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *findListAuto(l, 4);

    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *find(l.begin(), l.end(), 4);
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << *find_if(l.begin(), l.end(), predicate1);
    
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    cout << *find_if(l.begin(), l.end(), Predicate1());
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    cout << *find_if(l.begin(), l.end(), [] (int val) { return (val & 1) == 0;});
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* Da = new int[6];
    copy(l.begin(), l.end(), Da);
    for(size_t i = 0; i < 6; ++i){
        cout << Da[i] << " ";
    }
    delete[] Da;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(l.begin(), l.end(), 4);

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFind(l.begin(), l.end(), 4);
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    countDistinctWordVec("pooh-nopunc.txt");
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    countDistinctWordSet("pooh-nopunc.txt");
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    countDistinctWordMap("pooh-nopunc.txt");
    cout << "=======\n";
}

