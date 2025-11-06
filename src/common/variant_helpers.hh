#pragma once
namespace yumeami {

  template <class... Ts> struct Match : Ts... {
    using Ts::operator()...;
  };
  template <class... Ts> Match(Ts...) -> Match<Ts...>;

} // namespace yumeami
