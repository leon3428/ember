#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <memory>
#include <functional>
#include <unordered_map>
#include <concepts>

#include "utils.hpp"

namespace ember {
    class EventBus {
        public:
            template<typename T, typename Fn> requires std::is_pointer_v<decltype(&T::idn)>
            void subscribe(Fn &&fn) {
                if(!m_callbacks.contains(T::idn)) {
                    m_callbacks[T::idn] = { new m_CallbackList<T>{}, [](void* p){
                        delete static_cast<m_CallbackList<T>*>(p);
                    }};
                }   
                auto p = static_cast<m_CallbackList<T>* >(m_callbacks[T::idn].get());
                p -> emplace_back(std::forward<Fn>(fn));
            }

            template<typename T, typename Fn, typename Obj> requires std::is_pointer_v<decltype(&T::idn)>
            void subscribe(Fn fn, Obj &obj) {
                subscribe<T>([&obj, fn](T t){ (obj.*fn)(t); });
            }

            template<typename T> requires std::is_pointer_v<decltype(&T::idn)>
            void fire(const T&& data) const {
                m_CallbackList<T> const *p = nullptr;

                if(m_callbacks.contains(T::idn))
                    p = static_cast<m_CallbackList<T> const* >(m_callbacks.at(T::idn).get());
                

                if(p) {
                    for(const auto& callback : *p)
                        callback(data);
                }
            }

        private:
            template<typename T>
            using m_CallbackList = std::vector<std::function<void(const T&)>>;

            template <typename T>
            void m_deleter(void* p) {
                delete static_cast<T*>(p);
            }

            std::unordered_map<
                Identifier, 
                std::unique_ptr<void, std::function<void(void*)>>, 
                IdentifierHash
            > m_callbacks;
    };
}

#endif // EVENT_BUS_HPP