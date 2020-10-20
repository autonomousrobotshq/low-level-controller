# low-level-controller
Everything coding related to the low-level-controller (Arduino).

A word from Stalin himself:
- follow existing naming convention when creating branches.
- follow existing name/access/setting/etc styling.
- libraries which are not important for including a header should not be included in the header but in the .cpp file.
- every class that reads from an input should have an 'update' function in which data is polled/retreived. Getter functions only serve to access variables.
- external libraries must be appended by their version number.
- when using code from a remote source make sure to comply to their licensing (include license if necessary).
- run 'clang-format -style=webkit -i [FILENAME]' before pushing.
- don't push code that doesn't compile ('git stash' is for that).
- commit messages should convey clearly what has changed and should contain relevant filenames.

Trespassers will be met with resistance.
