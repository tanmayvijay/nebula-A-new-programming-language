# nebula-A programming language in CPP
 This is a programming language I created using C++.

**I am creating this language to sharpen my core Computer Science understanding. It can also be considered as my take on the subject of "Compiler Design", which I have for this semester.
At this point, when I start, I have no idea how compilers or interpreters work. But, let's just hit it.**
<b>

### Edit-1: Done with the phase-1 : Tokenizer (Lexical Analyzer).

### Edit-2: Tested Partially comepleted Parser for 3 types of program elements:
* Simple Expression Statements
* Variable Declaration Statements
* Variable Assignment Statements


### Edit-3: Added all types of expressions:
* Arithmetic
* Relational
* Logical


### Edit-4: Changed entire expression and program_element architecture to support Symbol Table:
* Each block has its own symbol table.
* Symbol Table is now updated everytime a Variable Declaration Statement or Variable Assignment Statement is encountered.
* Variables are searched in the most closely nested block.
