#include <iostream>
#include <chrono>
#include "DS.h"
#include "Q2.h"

using namespace std;
using namespace std::chrono;

// Measure execution time in nanoseconds
template<typename Func>
long long measureTime(Func func, Node* head) {
    auto start = high_resolution_clock::now();
    
    volatile int result = func(head);
    
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

int main() {
    int totalDeduction = 0;
    
    // Test 1: Small list for correctness
    CircularList* list1 = CircularList::createRandomSize(10);
    int expected1 = list1->getActualLength();
    Node* head1 = list1->getHead();
    
    int result1 = CircleList1(head1);
    if (result1 != expected1) {
        printf("CircleList1 returned wrong result on small list: expected %d, got %d (-15)\n", 
               expected1, result1);
    }
    
    // Verify list integrity wasn't broken
    if (!list1->verifyIntegrity()) {
        printf("CircleList1 corrupted the list structure (-15)\n");
    }
    
    delete list1;
    
    // Test 2: Medium list for CircleList2
    CircularList* list2 = CircularList::createRandomSize(50);
    int expected2 = list2->getActualLength();
    Node* head2 = list2->getHead();
    
    int result2 = CircleList2(head2);
    if (result2 != expected2) {
        printf("CircleList2 returned wrong result on medium list: expected %d, got %d (-15)\n", 
               expected2, result2);
    }
    
    if (!list2->verifyIntegrity()) {
        printf("CircleList2 corrupted the list structure (-15\n");
    }
    
    delete list2;
    
    // Test 3: Large list for complexity testing
    CircularList* list3 = CircularList::createRandomSize(1000);
    int expected3 = list3->getActualLength();
    Node* head3 = list3->getHead();
    
    // Test CircleList1 complexity
    long long time1 = measureTime(CircleList1, head3);
    
    // Restore list for CircleList2 test
    delete list3;
    list3 = CircularList::createRandomSize(1000);
    head3 = list3->getHead();
    
    long long time2 = measureTime(CircleList2, head3);
    
    // CircleList2 should be significantly faster than CircleList1 for large n
    // Θ(n log n) vs Θ(n^2): for n=1000, log(1000)≈10, so n*log(n) ≈ 10,000 vs n^2 = 1,000,000
    // CircleList2 should be ~100x faster
    if (time2 > time1 * 0.2) {  // If not at least 5x faster, likely wrong complexity
        printf("CircleList2 complexity appears incorrect - not significantly faster than CircleList1 (-20)\n");
    }
    
    delete list3;
    
    // Test 4: Very large list to stress test complexity
    CircularList* list4 = CircularList::createRandomSize(5000);
    head3 = list4->getHead();
    
    long long time2Large = measureTime(CircleList2, head3);
    
    // For CircleList2: if we go from n=1000 to n=5000 (5x increase)
    // Time should increase by roughly 5 * log(5000)/log(1000) ≈ 5 * 1.3 ≈ 6.5x
    // If it increases by 25x (5²), it's likely Θ(n²)
    if (time2Large > time2 * 15) {
        printf("CircleList2 shows quadratic behavior on large input - likely Θ(n^2) instead of Θ(n log n) (-20)\n");
    }
    
    delete list4;
    
    printf("done\n");
    
    return 0;
}