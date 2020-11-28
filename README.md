# low-level-controller
Everything coding related to the low-level-controller (Arduino).

A word from Stalin himself:
1. naming convention : https://guiquanz.gitbooks.io/google-cc-style-guide/content/ebook/Naming.html
2. general styleguide: https://google.github.io/styleguide/cppguide.html
3. follow existing naming convention when creating branches.
4. follow existing name/access/setting/etc styling.
5. libraries which are not important for including a header should not be included in the header but in the .cpp file.
6. every class that reads from an input should have an 'update' function in which data is polled/retreived. Getter functions only serve to access variables.
7. external libraries must be appended by their version number.
8. when using code from a remote source make sure to comply to their licensing (include license if necessary).
9. run 'clang-format -style=webkit -i [FILENAME]' before pushing.
10. don't push code that doesn't compile ('git stash' is for that).
11. commit messages should convey clearly what has changed and should contain relevant filenames.

Trespassers will be met with resistance.
