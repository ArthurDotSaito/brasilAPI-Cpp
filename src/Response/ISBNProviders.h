#ifndef ISBN_PROVIDERS_H
#define ISBN_PROVIDERS_H

enum class Provider { CBL, MercadoEditorial, OpenLibrary, GoogleBooks };

const std::unordered_map<std::string, Provider> providerMap = {{"cbl", Provider::CBL},
    {"mercado-editorial", Provider::MercadoEditorial}, {"open-library", Provider::OpenLibrary},
    {"google-books", Provider::GoogleBooks}};

bool isValidProvider(const std::string &providerStr);

#endif // ISBN_PROVIDERS_H