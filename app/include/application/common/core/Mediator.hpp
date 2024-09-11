#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include <memory>
#include <unordered_map>
#include <functional>
#include <stdexcept>

// Clase Mediator
class Mediator {
public:
    // Método para registrar un handler para un tipo de solicitud
    template<typename TRequest, typename TResponse>
    void register_handler(std::function<TResponse(const TRequest&)> handler) {
        auto key = typeid(TRequest).name();
        handlers[key] = [handler](void* req) -> void* {
            return new TResponse(handler(*static_cast<TRequest*>(req)));
        };
    }

    // Método para enviar una solicitud y obtener la respuesta
    template<typename TRequest, typename TResponse>
    TResponse send(const TRequest& request) {
        auto key = typeid(TRequest).name();
        auto it = handlers.find(key);
        if (it != handlers.end()) {
            auto handler = it->second;
            std::unique_ptr<void, std::function<void(void*)>> response(
                handler((void*)&request), [](void* ptr) { delete static_cast<TResponse*>(ptr); });
            return *static_cast<TResponse*>(response.get());
        } else {
            throw std::runtime_error("No handler registered for this request type.");
        }
    }

private:
    std::unordered_map<const char*, std::function<void*(void*)>> handlers;
};

#endif  // MEDIATOR_HPP