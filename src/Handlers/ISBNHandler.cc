#include "ISBNHandler.h"
#include <Utils/BrasilAPIException.h>
#include <Utils/ProviderToString.h>

void ISBNHandler::getLivrosBrasil(const std::string &isbn, const std::optional<std::vector<Provider>> &providers,
    std::function<void(std::variant<BookInfo, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  std::stringstream pathStream;
  std::stringstream queryStream;
  pathStream << "/api/isbn/v1/" + isbn;

  if (providers.has_value() && !providers->empty()) {
    queryStream << "?providers=";
    for (size_t i = 0; i < providers->size(); ++i) {
      if (i > 0) {
        queryStream << ",";
      }
      queryStream << providerToString((*providers)[i]);
    }
  }

  req->setPath(pathStream.str() + queryStream.str());
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, fullUrl);
      std::string responseBody = std::string(response->getBody());

      BookInfo bookInfo;
      bookInfo.calledURL = fullUrl;
      bookInfo.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        bookInfo.setIsbn(jsonResponse["isbn"].asString());
        bookInfo.setTitle(jsonResponse["title"].asString());
        bookInfo.setSubtitle(jsonResponse["subtitle"].asString());
        std::vector<std::string> authors;
        for (const auto &author : jsonResponse["authors"]) {
          authors.push_back(author.asString());
        }
        bookInfo.setAuthors(authors);
        bookInfo.setPublisher(jsonResponse["publisher"].asString());
        bookInfo.setSynopsis(jsonResponse["synopsis"].asString());
        Dimension dim;
        dim.width = jsonResponse["dimensions"]["width"].asDouble();
        dim.height = jsonResponse["dimensions"]["height"].asDouble();
        dim.unit = jsonResponse["dimensions"]["unit"].asString();
        bookInfo.setDimensions(dim);
        bookInfo.setYear(jsonResponse["year"].asInt());
        bookInfo.setFormat(jsonResponse["format"].asString());
        bookInfo.setPageCount(jsonResponse["page_count"].asInt());

        std::vector<std::string> subjects;
        for (const auto &subject : jsonResponse["subjects"]) {
          subjects.push_back(subject.asString());
        }
        bookInfo.setSubjects(subjects);
        bookInfo.setLocation(jsonResponse["location"].asString());
        bookInfo.setRetailPrice(jsonResponse["retail_price"].asString());
        bookInfo.setCoverUrl(jsonResponse["cover_url"].asString());
        bookInfo.setProvider(jsonResponse["provider"].asString());

        callback(bookInfo);
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
    } catch (const BrasilAPIException &e) {
      ErrorResponse errorResponse;
      errorResponse.errorCode = e.getStatusCode();
      errorResponse.errorMessage = e.what();

      callback(errorResponse);
    }
  });
}