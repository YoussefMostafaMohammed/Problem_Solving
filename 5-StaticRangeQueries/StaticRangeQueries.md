# Static Range Queries Techniques
## جدول المحتويات
1. [مقدمة](#مقدمة)
2. [ايه هي ال Static Range Queries](#static-range-queries-هي-ايه)
3. [ايه هو ال Frequency Array](#frequency-array)
4. [ايه هو ال Prefix Array](#prefix-array)
5. [ايه هو ال Suffix Array](#suffix-array)
6. [ال Prefix Sum على الماتريس 2D](#prefix-sum-على-الماتريس-2d)
7. [متى نستخدم كل technique؟](#متى-نستخدم-كل-technique)
8. [نصائح إضافية](#نصائح-إضافية)

---
## مقدمة

 ال **Techniques** مش algorithms! الفرق هنا مهم جداً:
- ال **Algorithm** هو حل كامل لمشكلة معينة (زي Dijkstra, Binary Search)
- ال **Technique** هو pattern أو snippet صغير من كود بتستخدمه كجزء من حل أكبر. زي prefix sum مثلاً - مش حل كامل، لكن خطوة واحدة من خطوات الحل

المسائل اللي هنتكلم عنها هي **Static Range Queries** - أسهل نوع في عائلة range queries.

---

## ايه هي ال Static Range Queries

لو عندك array زي: `[1,2,1,3,4,5]` وعايز تجاوب على أسئلة (queries) من النوع:
- "هاتلي أكبر رقم من index L لـ R"
- "هاتلي مجموع الأرقام من index L لـ R"
- "هاتلي أقل رقم ظهر في المدة دي"

كل دا اسمه **range query**. والـ "Static" هنا معناها إن ال array بتاعتك **مبتتغيرش** أثناء ال queries. يعني كل ال queries بتحصل على نفس ال dataset.

لو ال array كانت بتتغير (add, remove, update) -> ده اسمه **Dynamic Range Queries** وبيحتاج حلول تقيلة زي **Segment Tree** أو **Fenwick Tree**.

لكن احنا هنا بنتكلم عن ال static بس - اللي ممكن تحله بـ techniques بسيطة.

---

## ال Frequency Array

### المشكلة
عندك array من الأرقام، عايز تعرف كل رقم ظهر كام مرة.

### الحل البدائي (n²)
```c++
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 2, 3, 1, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    bool visited[n] = {false};

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                visited[j] = true;
                count++;
            }
        }
        cout << arr[i] << " occurs " << count << " times\n";
    }
}
```
**عيبه**: O(n²) - بطيء جداً لو n كبير!

### الحل الأمثل: Frequency Array

الفكرة اننا نشوف ال array من منظور تاني:
- ال index نفسه بيعبر عن ال value
- محتوى ال cell بيكون عدد مرات تكرار ال value دي

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int arr[] = {1, 2, 2, 3, 1, 4, 2, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 1. نجيب أكبر قيمة عشان نعرف حجم الـ frequency array
    int maxVal = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // 2. نعمل Frequency Array بحجم maxVal + 1
    vector<int> freq(maxVal + 1, 0);

    // 3. نعد التكرارات
    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    // 4. نطبع الترددات
    for (int value = 0; value <= maxVal; value++) {
        if (freq[value] > 0) {
            cout << value << " occurs " << freq[value] << " times\n";
        }
    }
}
```
**الوقت**: O(n + maxVal)، **المعقدية**: O(maxVal)

### الحل الثاني : Hash Maps

لو ال range كبير جداً (مثلاً من 1 لـ 10⁹) مش هتقدر تحجز array بالحجم دا!

الحل؟ **map** (أو لو عندك أرقام سالبة أو عشرية)

```c++
#include <iostream>
#include <map>
using namespace std;

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    map<int, int> freq;

    for (int x : arr) freq[x]++;

    cout << "Numbers with even frequency:\n";
    for (auto &p : freq) {
        if (p.second % 2 == 0)
            cout << p.first << " ";
    }
}
```

**ملاحظات مهمة:**

| الحل          | Time Complexity | Space Complexity | ملاحظات                          |
| ------------- | --------------- | ---------------- | -------------------------------- |
| Array         | O(maxVal)       | O(maxVal)        | سريع بس محتاج space كبير         |
| unordered_map | O(n)            | O(n)             | أحسن في space لكن O(1) مش مضمونة |
| map           | O(n log n)      | O(n)             | مضمونة لكن أبطأ                  |

**رد على نقطة مهمة:** `خلي بالك ان ال time لكل query بتاع ال array هو O(1) والتايم بتاع ال map هو O(log(n)) لكل عمليه insert فصحيح انك لو استخدمت map هتوفر size بس التايم اكبر طب احنا ممكن نستخدم unordered map وبكدة هنعمل insert في O(1) الكلام دا صحيح بس خطر علشان ال unordered map مش شغاله في O(1) لا دي شغاله في amortized O(1) يعني هو في معظم الوقت هيشتغل معاك O(1) بس هييجي في مرة وهيضرب معاك O(n) دا لان ال unordered map شغال بحاجة اسمها Hashing ودا بيعمل collison ودا عبارة عن اكتر من value بيعملوا access لنفس ال position فهو بيبدأ يحطهم في linked list أو tree جوه نفس الـ bucket ولو عدد ال collisions كتر جدًا -> البحث/الإضافة ممكن تبقى O(n)`.

**نصيحة**: لو عندك أرقام سالبة أو عشرية أو ال range بعيد جداً، استخدم **map** بدل ما تعمل optimize من الأول.

---

## ال Prefix Array

### الفكرة الأساسية
بدل ما نبص لل array من البداية كل مرة، نبني array ثانية كل cell فيها بيشيل معلومة متراكمة من أول ال array لحد ال index ده.

### ال Prefix Sum
```c++
array = [0, 2, 1, 3, 0, 2, 4, 1, 3, 6, 7]
prefix[i] = مجموع من 0 لـ i
```

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {0,2,1,3,0,2,4,1,3,6,7};
    int n = arr.size();
    vector<int> prefix(n);

    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    cout << "Prefix Sum Array:\n";
    for (int x : prefix) cout << x << " ";
    cout << "\n";
}
```

الناتج: `[0, 2, 3, 6, 6, 8, 12, 13, 16, 22, 29]`

### إيه اللي استفدناه؟

**السؤال**: لو عايز مجموع الأرقام من index L لـ R؟
**الإجابة**: 
```
sum(L..R) = prefix[R] - prefix[L-1]
```
لو L = 0: `sum(0..R) = prefix[R]`

**مثال**: مجموع من 5 لـ 8
```
prefix[8] - prefix[4] = 16 - 6 = 10
```
(2 + 4 + 1 + 3 = 10)

**الوقت**: O(1) لكل query!

### ال Prefix Min
```c++
arr = [5, 3, 7, 2, 9]
prefix_min[i] = أقل قيمة من 0 لـ i
```

```c++
prefix_min[0] = 5
prefix_min[1] = min(5, 3) = 3
prefix_min[2] = min(3, 7) = 3
prefix_min[3] = min(3, 2) = 2
prefix_min[4] = min(2, 9) = 2

prefix_min = [5, 3, 3, 2, 2]
```

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {5, 3, 7, 2, 9};
    int n = arr.size();
    vector<int> prefixMin(n);

    prefixMin[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefixMin[i] = min(prefixMin[i - 1], arr[i]);
    }

    cout << "Prefix Min Array:\n";
    for (int x : prefixMin) cout << x << " ";
    cout << endl;
}
```

---

## ال Suffix Array

### الفكرة الأساسية
نفس prefix بس بالعكس! بنبني من النهاية للبداية.

### ال Suffix Sum
```c++
array = [0, 2, 1, 3, 0, 2, 4, 1, 3, 6, 7]
suffix[i] = مجموع من i لـ n-1
```

```c++
suffix[10] = 7
suffix[9] = 6 + 7 = 13
suffix[8] = 3 + 6 + 7 = 16
...
suffix = [29, 29, 27, 26, 23, 23, 21, 17, 16, 13, 7]
```

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {0,2,1,3,0,2,4,1,3,6,7};
    int n = arr.size();
    vector<int> suffix(n);

    suffix[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suffix[i] = arr[i] + suffix[i + 1];
    }

    cout << "Suffix Sum Array:\n";
    for (int x : suffix) cout << x << " ";
    cout << endl;
}
```

### ال Suffix Min
```c++
arr = [5, 3, 7, 2, 9]
suffix_min[i] = أقل قيمة من i لـ n-1
suffix_min = [2, 2, 2, 2, 9]
```

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {5, 3, 7, 2, 9};
    int n = arr.size();
    vector<int> suffixMin(n);

    suffixMin[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suffixMin[i] = min(suffixMin[i + 1], arr[i]);
    }

    cout << "Suffix Min Array:\n";
    for (int x : suffixMin) cout << x << " ";
    cout << endl;
}
```

### نقطتين مهمتين جداً

1. ال **Prefix Min**: ماينفعش تسأله "أقل قيمة من 2 لـ 5". بيجاوب بس على أسئلة "من البداية لـ X" محتاج تستخدم Sparse Table
2. ال **Suffix Min**: ماينفعش تسأله "أقل قيمة من 5 لـ 7". بيجاوب بس على أسئلة "من X لـ الآخر" محتاج تستخدم Sparse Table

لو محتاج **random range queries** (تبدأ وتنتهي في أي مكان) → لازم **Segment Tree**!

---

## ال Prefix Sum على matrix 2D

### المشكلة
عندك ماتريس عددية، عايز تجاوب على queries من النوع:
- "هاتلي مجموع الأرقام في مستطيل من (x1,y1) لـ (x2,y2)"

### الفكرة
نفس فكرة prefix sum بس في بعدين!

```c++
matrix =  1 2 3
          4 5 6
          7 8 9
```

نبني **2D prefix sum matrix** كل cell فيها بيكون:
```
prefix[i][j] = sum of all cells from (0,0) to (i,j)
```

### الطريقة
1. **الخطوة 1**: حسب prefix لكل صف على حدة (horizontal prefix)
2. **الخطوة 2**: اجمع النواتج عمودياً (vertical prefix)

**الصيغة النهائية**:
```
prefix[i][j] = matrix[i][j] 
             + prefix[i-1][j]   // الجزء اللي فوق
             + prefix[i][j-1]   // الجزء اللي على الشمال
             - prefix[i-1][j-1] // الجزء اللي اتضاعف
```

### مثال عملي
```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // نبني prefix 2D
    vector<vector<int>> prefix(rows, vector<int>(cols, 0));
    
    prefix[0][0] = matrix[0][0];
    
    // أول صف
    for (int j = 1; j < cols; j++) {
        prefix[0][j] = prefix[0][j-1] + matrix[0][j];
    }
    
    // أول عمود
    for (int i = 1; i < rows; i++) {
        prefix[i][0] = prefix[i-1][0] + matrix[i][0];
    }
    
    // باقي الماتريس
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            prefix[i][j] = matrix[i][j] 
                         + prefix[i-1][j] 
                         + prefix[i][j-1] 
                         - prefix[i-1][j-1];
        }
    }
    
    // طباعة prefix matrix
    cout << "2D Prefix Sum Matrix:\n";
    for (auto &row : prefix) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    
    // مثال query: مجموع المستطيل من (1,1) لـ (2,2)
    // أي: 5+6+8+9 = 28
    int x1 = 1, y1 = 1, x2 = 2, y2 = 2;
    
    int total = prefix[x2][y2];
    int above = (x1 > 0) ? prefix[x1-1][y2] : 0;
    int left = (y1 > 0) ? prefix[x2][y1-1] : 0;
    int diagonal = (x1 > 0 && y1 > 0) ? prefix[x1-1][y1-1] : 0;
    
    int sum = total - above - left + diagonal;
    
    cout << "\nSum from (" << x1 << "," << y1 << ") to (" 
         << x2 << "," << y2 << ") = " << sum << endl;
    
    return 0;
}
```

الناتج:
```
2D Prefix Sum Matrix:
1  3  6
5 12 21
12 27 45

Sum from (1,1) to (2,2) = 28
```

### الصيغة العامة لأي query
```
sum(x1..x2, y1..y2) = 
    prefix[x2][y2] 
  - prefix[x1-1][y2] 
  - prefix[x2][y1-1] 
  + prefix[x1-1][y1-1]
```

**ملاحظة**: لازم تتأكد إن x1>0 و y1>0 قبل ما تطرح!

### متى تستخدم 2D Prefix Sum؟
- صورة (pixel values)
- لوحة ألعاب (grid-based games)
- أي مشكلة فيها بيانات على شكل مصفوفة وعايز تعمل sum queries بسرعة

---

## متى نستخدم كل technique؟

| Technique | Static/Dynamic | Query Type | Time/Query | Build Time | Limitations |
|-----------|----------------|------------|------------|------------|-------------|
| Frequency Array | Static | Counting | O(1) | O(n) | Range محدود |
| Prefix Sum | Static | Sum from start | O(1) | O(n) | لازم يبدأ من أول ال array |
| Suffix Sum | Static | Sum to end | O(1) | O(n) | لازم ينتهي في آخر ال array |
| Prefix Min | Static | Min from start | O(1) | O(n) | مينفعش range يبدأ من النص |
| Suffix Min | Static | Min to end | O(1) | O(n) | مينفعش range ينتهي في النص |
| 2D Prefix Sum | Static | Rectangle sum | O(1) | O(rows*cols) | بس على مصفوفات |
| Segment Tree | Dynamic | أي range query | O(log n) | O(n) | معقد شوية لكن مرن جداً |

---

## نصائح إضافية

1. ال **Prefix vs Frequency**: مثلاً لو عايز تعرف "كم مرة ظهر العدد 5 من index 0 لـ 10؟" - ده prefix على frequency array!

2. ال **Combo**: ممكن تجمع techniques. مثلاً:
   - اعمل frequency array
   - اعمل prefix عليه
   - دلوقت عندك ability تحسب تكرار أي رقم في أي range!

1. ال **Overflow**: لو كانت الأعداد كبيرة، استخدم long long بدل int في ال prefix sums.

2. ال **Edge Cases**: دايماً فكر في:
   - ال L = 0
   - ال R = n-1
   - ال array فاضية

خليك دايماً فاكر: **الـ technique مش هيحل المسألة كاملة لكن هيخليك تقدر تعمل جزء من الحل بسرعة!. غالبا بيكون خطوة من خطوات الحل بتاع المسأله** 