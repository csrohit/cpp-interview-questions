#include <cstdint>
#include <iostream>
#include <list>
#include <unordered_map>
#include <cstring>

/**
 * @brief Represents the data record to be cached.
 * * Nuance: In a real-world scenario, this object might be large. 
 * The cache should store pointers or smart pointers to avoid expensive copies.
 */
class Student {
public:
    uint64_t roll;
    char firstname[16];
    char lastname[16];

    Student(uint32_t r, const char* first) : roll(r) {
        std::strncpy(firstname, first, sizeof(firstname) - 1);
        firstname[sizeof(firstname) - 1] = '\0';
    }
};

/**
 * @brief A Least Recently Used (LRU) Cache for Student records.
 * * Data Structure Choice:
 * 1. std::list: Maintains the order of access. Front is Most Recently Used (MRU), 
 * Back is Least Recently Used (LRU). Provides O(1) reordering.
 * 2. std::unordered_map: Maps the unique Key (roll) to the list iterator. 
 * Provides O(1) average lookup time.
 */
class StudentCache {
private:
    const size_t capacity;

    // Map: Roll Number -> Iterator pointing to the node in studentList
    std::unordered_map<uint32_t, std::list<Student*>::iterator> studentMap;
    
    // List: Stores the actual pointers in order of use
    std::list<Student*> studentList;

public:
    /**
     * @brief Construct a new Student Cache object
     * @param _capacity Maximum number of students the cache can hold.
     */
    explicit StudentCache(uint32_t _capacity) : capacity(_capacity) {}

    /**
     * @brief Adds a student to the cache or updates their position if they exist.
     * Complexity: O(1) average.
     */
    void put(Student& student) {
        auto it = studentMap.find(student.roll);

        if (it != studentMap.end()) {
            /* Case 1: Student exists. Update position to MRU (front). */
            // Nuance: splice() moves the node without destroying/re-creating it.
            studentList.splice(studentList.begin(), studentList, it->second);
            
            // Nuance: Optional. it->second still points to the moved node.
            it->second = studentList.begin(); 
            return;
        }

        if (studentMap.size() >= capacity) {
            /* Case 2: Cache is full. Evict the LRU (back of list). */
            uint32_t lru_roll = studentList.back()->roll;
            std::cout << "Evicting " << studentList.back()->firstname << " to make room.\n";
            
            studentMap.erase(lru_roll);
            studentList.pop_back();
        }

        /* Case 3: New entry. Insert at front (MRU). */
        std::cout << "Adding " << student.firstname << " to cache.\n";
        studentList.push_front(&student);
        studentMap[student.roll] = studentList.begin();
    }

    /**
     * @brief Retrieves a student from cache and marks them as MRU.
     * @return Student* Pointer to the student, or nullptr if not found.
     * Complexity: O(1) average.
     */
    Student* get(uint32_t roll) {
        auto it = studentMap.find(roll);

        if (it == studentMap.end()) {
            return nullptr; // Cache Miss
        }

        /* Cache Hit: Move accessed node to front (MRU) */
        studentList.splice(studentList.begin(), studentList, it->second);
        return *it->second;
    }

    // Overload for printing the current state of the cache
    friend std::ostream& operator<<(std::ostream& ostr, const StudentCache& cache);
};

std::ostream& operator<<(std::ostream& ostr, const StudentCache& cache) {
    ostr << "--- Cache State (MRU -> LRU) ---\n";
    for (const auto& s : cache.studentList) {
        ostr << "[" << s->roll << ": " << s->firstname << "] ";
    }
    return ostr << "\n-------------------------------\n";
}

int main() {
    Student rohit(1, "Rohit"), nehal(2, "Nehal"), vinit(3, "Vinit"), vidit(4, "Vidit");

    StudentCache cache(2);

    cache.put(rohit);
    cache.put(nehal);
    std::cout << cache; // Shows Nehal, Rohit

    cache.put(vidit);   // Evicts Rohit
    std::cout << cache; // Shows Vidit, Nehal

    cache.get(2);       // Accesses Nehal, makes her MRU
    std::cout << cache; // Shows Nehal, Vidit

    return 0;
}
