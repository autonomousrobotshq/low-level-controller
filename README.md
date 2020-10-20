# low-level-controller
Everything coding related to the low-level-controller (Arduino).

A word from Stalin himself:
- follow existing naming convention when creating branches.
- follow existing name/access/setting/etc styling.
- every class that reads from an input should have an 'update' function in which data is polled/retreived. Getter functions only serve to access variables.
- when using code from a remote source make sure to comply to their licensing (include license if necessary).
- run 'clang-format -style=webkit -i [FILENAME]' before pushing.
- don't push code that doesn't compile ('git stash' is for that).

Trespassers will be met with resistance.
