# systems-programming-bootcamp
Systems Engineering and Programming bootcamp | معسكر هندسة الأنظمة والبرمجة

Tuwaiq Academy | أكاديمية طويق
April 2026 - October 2026

## Projects

### Project 1: Football Match

Source code: [football-match.py](project/01/football-match.py)

Description: Protocol to "unpack" a 2-byte representation of a football match using binary masks and bit shifts.

Example:

```console
% ./football-match.py D420
As part of the Crown Prince league, Abha is scheduled to play against Ahli on Ahli's home.
The appointed referee is foreign.
Abha won!
```

### Project 2: Include in Include

Source code: [02](project/02)

Description: Conditionally `#include` toggles for executing outer/inner loops, in files that `#include` each other.

Example:

```console
% ./include-in-include         
y: 0
result = 0
result = 0
result = 0
y: 1
result = 0
result = 1
result = 2
y: 2
result = 0
result = 2
result = 4
```

### Project 3: Read into Heap

Source code: [read-into-heap.c](project/03/read-into-heap.c)

Description: Write binary data (initials and age) to a file, read into heap-allocated memory, and output the info.

Example:

```console
% ./read-into-heap 
Initials = OA, Age = 99
```

### Project 4: PDF Reader

Source code: [pdf-reader.c](project/04/pdf-reader.c)

Description: Read PDF version and page count as per the PDF specification into a struct and display the information.

Example:

```console
% ./pdf-reader 
Filename: Thompson_1984_ReflectionsonTrustingTrust.pdf
Magic code: %PDF-
PDF version: 1.3
Page count: 3

Filename: To the Budget Council concerning Haskell.pdf
Magic code: %PDF-
PDF version: 1.3
Page count: 2
````
