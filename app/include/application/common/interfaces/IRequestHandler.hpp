#ifndef IREQUESTHANDLER_HPP
#define IREQUESTHANDLER_HPP

// Interfaz genérica para manejar una solicitud y devolver una respuesta
template<typename TRequest, typename TResponse>
class IRequestHandler {
public:
    virtual TResponse handle(const TRequest& request) = 0;
    virtual ~IRequestHandler() = default;
};

#endif  // IREQUESTHANDLER_HPP
