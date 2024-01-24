#ifndef PROVIDER_TO_STRING_H
#define PROVIDER_TO_STRING_H

#include "Response/ISBNProviders.h"
#include <string>

std::string providerToString(Provider provider) {
  switch (provider) {
  case Provider::CBL:
    return "cbl";
  case Provider::MercadoEditorial:
    return "mercado-editorial";
  case Provider::OpenLibrary:
    return "open-library";
  case Provider::GoogleBooks:
    return "google-books";
  default:
    return "";
  }
}

#endif // PROVIDER_TO_STRING_H