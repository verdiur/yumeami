# yumeami

A Yume Nikki inspired game where you can create your own collaborative dreamspace.

## Guidelines

- Always format with the provided `.clang-format` config.
- Setup functions should preferably be prefixed with `setup_`.
- All functions that involve manipulation of an `entt::registry` are under the `yumeami::sys` namespace.
- If a parameter of a function is an `entt::registry`, then that parameter should be the first one in the function's parameter list.
- All classes/structs that are attached to entities as components are under the `yumeami::comp` namespace.
- Prefer Verb-Object naming for functions.
- Prefer Adverb-Subject naming for classes/structs.

