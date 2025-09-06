# Conventions

Most of the formatting is specified in `.clang-format`. Additional style guidelines will
be specified below.

## Naming

| thing | case | notes |
|-------|------|-------|
| file | snake_case | |
| folder | snake_case | |
| define | ALL_CAPS | |
| macro | ALL_CAPS | |
| constant | snake_case | |
| variable | snake_case | |
| function | snake_case | |
| struct | TitleCase | |
| struct member | snake_case | |
| primitive type alias or extension of primitive type | snake_case | |
| enum | TitleCase | |

- File names can be plural; directory names should never be plural.
- File extensions for implementation and header files are respectively `.cc` and `.hh`.
- Most of the time a directory should correspond to a library, and should contain a `CMakeLists.txt` file.
- Function names must be preceded by a verb-like category:
    - `draw` for drawing functions
    - `calc` for pure functions
    - `update` for `void`-returning functions with side-effects (except drawing functions)
    - `handle` for event handling
    - `create / load` if creation involves construction / addition / manual allocation
    - `delete / unload` for deletion / removal / manual deallocation

## Coding style

- `structs` should almost never be any more than data containers. That means all members should be public, default constructors only, and member functions must only be defined if they provide functionalities that are intrinsic to the struct. If you need to define a specific way a `struct` should be constructed, consider doing so in a `create_...()` function or in a `load_...()` function instead.

## Namespaces

- Exposed interfaces should be in the `yumeami` namespace.
- Implementation details and non-exposed functions/structs should be in the `yumeami::impl` namespace.
- Test/debug functions/structs should be in the `yumeami::test` namespace.

## More formatting

- In implementation files, function blocks should be separated by 2 blank lines.
- In implementation files, header comments should separate `yumeami::impl` and `yumeami` functions.

```cpp
/* IMPL **********************************************************************/
/* PUBL **********************************************************************/
```
