#ifndef Q2_H
#define Q2_H

#include "DS.h"

// Θ(n^2) Algorithm[cite: 7, 8]
int CircleList1(Node* L) {
    if (!L) return 0;
    
    int count = 1;
    while (true) {
        L->key = 1;
        
        // צועדים קדימה כמספר הצעדים הנוכחי
        for (int i = 0; i < count; i++) {
            L = L->next;
        }
        
        // מסמנים באפס
        if (L->key == 1) {
            L->key = 0;
        }
        
        // חוזרים חזרה לנקודת ההתחלה
        for (int i = 0; i < count; i++) {
            L = L->prev;
        }
        
        // אם ערך ההתחלה השתנה לאפס - סימן שהקפנו את כל הרשימה
        if (L->key == 0) {
            L->key = 1; // מחזירים למצב תקין כפי שהיה
            return count;
        }
        
        count++;
    }
}

// Θ(n log n) Algorithm[cite: 7, 8]
// Strategy: Divide and conquer using marking patterns[cite: 7]
// Similar to merge sort - divide into halves recursively[cite: 7]
int CircleList2(Node* L) {
    if (!L) return 0;
    
    // טיפול ידני ומהיר במקרי קצה של רשימות קצרות 
    // כדי שנוכל להתחיל בבטחה את הכפולות והחיפוש הבינארי
    L->key = 1;
    L->next->key = 0;
    if (L->key == 0) return 1;
    
    L->next->next->key = 0;
    if (L->key == 0) return 2;
    
    int k = 2;
    
    // שלב ראשון: מציאת החסם העליון של אורך הרשימה (בקפיצות כפולות)
    while (true) {
        // הולכים קדימה לסוף הטווח שמוכר לנו כאפסים
        for (int i = 0; i < k; i++) L = L->next;
        
        // מאפסים את הבלוק הבא בגודל k
        for (int i = 0; i < k; i++) {
            L = L->next;
            L->key = 0;
        }
        
        // חוזרים חזרה להתחלה (2k צעדים סך הכל)
        for (int i = 0; i < 2 * k; i++) L = L->prev;
        
        // אם דרסנו את עצמנו, אנחנו יודעים שהאורך נמצא בטווח בין k ל-2k
        if (L->key == 0) {
            L->key = 1;
            break;
        }
        k *= 2;
    }
    
    // שלב שני: חיפוש בינארי בתוך הטווח [k, 2k]
    int confirmed_zeros = k;
    int high = 2 * k;
    
    while (confirmed_zeros + 1 < high) {
        int mid = confirmed_zeros + (high - confirmed_zeros) / 2;
        
        // הולכים קדימה לאזור שטרם וידאנו
        for (int i = 0; i < confirmed_zeros; i++) L = L->next;
        
        // מאפסים עד לנקודת האמצע שניחשנו
        for (int i = confirmed_zeros; i < mid; i++) {
            L = L->next;
            L->key = 0;
        }
        
        // חוזרים להתחלה 
        for (int i = 0; i < mid; i++) L = L->prev;
        
        if (L->key == 0) {
            // הניחוש מספיק ארוך כדי לדרוס את ההתחלה -> האורך קטן או שווה לאמצע
            L->key = 1;
            high = mid;
        } else {
            // הניחוש קצר מידי -> האורך גדול מהאמצע
            confirmed_zeros = mid;
        }
    }
    
    return high;
}

#endif // Q2_H