#ifndef PROVIDER_VALIDATION_H
#define PROVIDER_VALIDATION_H

#include <optional>
#include <set>
#include <string>
#include <vector> // Include vector here

bool isValidProvider(const std::string &provider);
bool isValidISBNProvider(const std::string &provider);
bool validateProviders(const std::optional<std::string> &providers);
bool validateISBNProviders(const std::optional<std::vector<std::string>> &providers);

#endif // PROVIDER_VALIDATION_H
