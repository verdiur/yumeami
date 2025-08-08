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
| enum | TitleCase | |

- File names can be plural; directory names should never be plural.
- Most of the time a directory should correspond to a library, and should contain a `CMakeLists.txt` file.

## Namespaces

- Exposed interfaces should be in the `yumeami` namespace.
- Implementation details and non-exposed functions/structs should be in the `yumeami::impl` namespace.
- Debug functions/structs should be in the `yumeami::debug` namespace.
