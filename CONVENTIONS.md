# Conventions

Most formatting conventions are specified in the `.clang-format` file.

## Naming

| Thing | Convention |
| ----- | ---------- |
| Variable | snake_case |
| Constant | ALL_CAPS |
| Function | snake_case |
| Class/Struct| TitleCase |
| Class member | snake_case, no prefix |
| Enum member | ALL_CAPS |

Additionally :

- Setup functions should preferably be prefixed with `setup_`: for example, `setup_connect_move_events`.
- Prefer Verb-Object naming for functions.
- Prefer Adverb-Subject naming for classes/structs.

## Namespaces

- Everything should be contained in the `yumeami` namespace.
- All functions that involve manipulation of an `entt::registry` are under the `yumeami::sys` namespace.
- All classes/structs that are attached to entities as components are under the `yumeami::comp` namespace.
- All specialized event are under the `yumeami::event` namespace. Since event queues are attached to entities, they are under the `yumeami::comp` namespace.
- All base classes should be in the `yumeami` namespace.

## Miscellaneous

- If a parameter of a function is an `entt::registry`, then that parameter should be the first one in the function's parameter list.
