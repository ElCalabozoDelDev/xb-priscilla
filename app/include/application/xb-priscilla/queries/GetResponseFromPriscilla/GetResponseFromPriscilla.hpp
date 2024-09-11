#ifndef GETRESPONSEFROMPRISCILLA_HPP
#define GETRESPONSEFROMPRISCILLA_HPP

#include <string>
#include "application/common/interfaces/IRequestHandler.hpp"

struct GetResponseFromPriscillaQuery {
    std::string request;
};

struct GetResponseFromPriscillaResponse {
    std::string response;
};

class GetResponseFromPriscilla : public IRequestHandler<GetResponseFromPriscillaQuery, GetResponseFromPriscillaResponse> {
public:
    GetResponseFromPriscillaResponse handle(const GetResponseFromPriscillaQuery& request) override;
};

#endif  // GETRESPONSEFROMPRISCILLA_HPP