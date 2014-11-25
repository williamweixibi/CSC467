Report:
Zaara Syeda - 998199765
Ghulam Umar - 998513988

Approach:
-Our approach to semantic checking was to first build the AST and symbol table
-Once these data structures were built, we had all the data required for semantic checking
-We allocate an AST node for the rules in parser.y
-Each AST node has a kind which gives info about the type of node this is and it has children nodes which point to either other AST nodes or other types such as strings/ints.
-We build the symbol table recursively by walking the AST and creating a symbol table entry for all declarations
-We then recursively do semantic checking by walking the AST and looking up the symbol table to get type information

Breakdown of work:
-Both: Build AST, build symbol table, semantic checking
-Zaara: AST print
-Umar: AST free

Challenges faced/Novelties:
-We faced challenges with implementing the predefined variables. We thought these needed to be added to both scanner and parser but realized that would be too much effort. We we novel in our implementation of these by adding them our symbol table with information regarding access control of these variables in the symbol table, i.e read-only, write-only. 
-Another challenge we faced was how we implemented semantic error checking. Since this was implemented recursively, the error return code is propagated up the recursive calls leading to multiple error messages for one line. We solved this by calling exit after printing the first and most relevant error rather than calling return. This causes our compiler to stop after printing the errors.

Bonus:
-Semantic error messages with line numbers

