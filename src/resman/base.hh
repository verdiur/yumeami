/**
 * @file base.hh
 * @brief Generic resource management structs
 * @note We are rolling our own resource management solution. I know that
 * entt::resource_cache exists but I don't like the way it expects me to use it;
 * maybe I'm not familiar with it enough. For now I'm not familiar with it
 * enough. Might switch to this later if it proves more efficient / cleaner.
 */

#pragma once
#include "spdlog/spdlog.h"
#include <concepts>
#include <unordered_map>
namespace yumeami {


  /**
   * @brief Requires class to be callable, returning an optional to a resource.
   *
   * @tparam F target functor
   * @tparam Resource return resource type
   */
  template <class F, class Resource>
  concept IsLoader = requires(F f) {
    { f() } -> std::same_as<std::optional<Resource>>;
  };


  /**
   * @brief Generic resource cache template
   *
   * @tparam Resource resource class
   * @tparam Loader load functor
   * @param key
   * @return
   */
  template <class Resource, class Loader>
    requires IsLoader<Loader, Resource>
  struct ResourceCache {
  private:
    std::unordered_map<int, Resource> pool = {};

  public:
    bool contains(int key) const { return pool.contains(key); }


    bool load(int key, const Loader &loader) {
      std::optional<Resource> res = loader();
      if (!res) {
        spdlog::info("[] could not load resource");
        return false;
      }

      pool.try_emplace(key, std::move(res.value()));
      spdlog::info("[] loaded resource ({})", key);
      return true;
    }


    bool unload(int key) {
      if (!contains(key)) {
        spdlog::error("[] could not unload: key {} not found", key);
        return false;
      }
      pool.erase(key);
      spdlog::info("[] unloaded resource ({})", key);
      return true;
    }


    void clear() {
      pool.clear();
      spdlog::info("[] unloaded all resources");
    }


    Resource *get(int key) {
      if (!contains(key)) {
        spdlog::error("[] could not get: key {} not found", key);
        return nullptr;
      }
      return &pool.at(key);
    }


    const Resource *get(int key) const { return get(key); }
  };


} // namespace yumeami
