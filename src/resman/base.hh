/**
 * @file base.hh
 * @brief Generic resource management structs
 * @note We are rolling our own resource management solution. I know that
 * entt::resource_cache exists but I don't like the way it expects me to use it;
 * maybe I'm not familiar with it enough. Might switch to this later if it
 * proves more efficient / cleaner.
 */

#pragma once
#include "common/static_string.hh"
#include "spdlog/spdlog.h"
#include <concepts>
#include <unordered_map>
namespace yumeami {


  /**
   * @brief Enforces a class to be derived from ResourceLoader
   * @tparam T Target type
   * @tparam Resource Handled resource type
   */
  template <class T, class Resource>
  concept IsLoader = requires(T f) {
    { f() } -> std::convertible_to<std::optional<Resource>>;
  };


  /**
   * @brief Generic resource cache template. Does not check validity; it's a
   * good idea to implement validation in your loader.
   * @tparam Resource resource class
   * @tparam Loader load functor
   * @tparam Validator validation functor. The default validator does not
   * perform validations and always return true.
   */
  template <StaticString CacheName, class Key, class Resource, class Loader>
    requires IsLoader<Loader, Resource>
  struct ResourceCache {
  private:
    std::unordered_map<Key, Resource> pool = {};

  public:
    bool contains(Key key) const { return pool.contains(key); }


    bool load(Key key, const Loader &loader) {
      std::optional<Resource> res = loader();
      if (!res) {
        spdlog::info("[{}] could not load resource: resource is not valid",
                     std::string(CacheName));
        return false;
      }
      // NOTE: pretty flimsy i think
      pool.try_emplace(key, std::move(res.value()));
      spdlog::info("[{}] loaded resource ({})", std::string(CacheName), key);
      return true;
    }


    bool unload(Key key) {
      if (!contains(key)) {
        spdlog::error("[{}] could not unload resource: key {} not found",
                      std::string(CacheName), key);
        return false;
      }
      pool.erase(key);
      spdlog::info("[{}] unloaded resource ({})", std::string(CacheName), key);
      return true;
    }


    void clear() {
      pool.clear();
      spdlog::info("[{}] unloaded all resources", std::string(CacheName));
    }


    Resource *get(Key key) {
      if (!contains(key)) {
        spdlog::error("[{}] could not get resource: key {} not found",
                      std::string(CacheName), key);
        return nullptr;
      }
      return &pool.at(key);
    }


    const Resource *get(Key key) const {
      if (!contains(key)) {
        spdlog::error("[{}] could not get resource: key {} not found",
                      std::string(CacheName), key);
        return nullptr;
      }
      return &pool.at(key);
    }
  };


} // namespace yumeami
