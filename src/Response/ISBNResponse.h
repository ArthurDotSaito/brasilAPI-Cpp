#ifndef BOOKINFO_RESPONSE_H
#define BOOKINFO_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>
#include <vector>

class Dimension {
  public:
  double width;
  double height;
  std::string unit;
};

class BookInfo : public BaseResponse, public JsonSerialize {
  private:
  std::string isbn;
  std::string title;
  std::string subtitle;
  std::vector<std::string> authors;
  std::string publisher;
  std::string synopsis;
  Dimension dimensions;
  int year;
  std::string format;
  int page_count;
  std::vector<std::string> subjects;
  std::string location;
  std::string retail_price;
  std::string cover_url;
  std::string provider;

  public:
  const std::string &getIsbn() const {
    return isbn;
  }
  const std::string &getTitle() const {
    return title;
  }
  const std::string &getSubtitle() const {
    return subtitle;
  }
  const std::vector<std::string> &getAuthors() const {
    return authors;
  }
  const std::string &getPublisher() const {
    return publisher;
  }
  const std::string &getSynopsis() const {
    return synopsis;
  }
  const Dimension &getDimensions() const {
    return dimensions;
  }
  int getYear() const {
    return year;
  }
  const std::string &getFormat() const {
    return format;
  }
  int getPageCount() const {
    return page_count;
  }
  const std::vector<std::string> &getSubjects() const {
    return subjects;
  }
  const std::string &getLocation() const {
    return location;
  }
  const std::string &getRetailPrice() const {
    return retail_price;
  }
  const std::string &getCoverUrl() const {
    return cover_url;
  }
  const std::string &getProvider() const {
    return provider;
  }

  void setIsbn(const std::string &i) {
    isbn = i;
  }
  void setTitle(const std::string &t) {
    title = t;
  }
  void setSubtitle(const std::string &s) {
    subtitle = s;
  }
  void setAuthors(const std::vector<std::string> &a) {
    authors = a;
  }
  void setPublisher(const std::string &p) {
    publisher = p;
  }
  void setSynopsis(const std::string &s) {
    synopsis = s;
  }
  void setDimensions(const Dimension &d) {
    dimensions = d;
  }
  void setYear(int y) {
    year = y;
  }
  void setFormat(const std::string &f) {
    format = f;
  }
  void setPageCount(int p) {
    page_count = p;
  }
  void setSubjects(const std::vector<std::string> &s) {
    subjects = s;
  }
  void setLocation(const std::string &l) {
    location = l;
  }
  void setRetailPrice(const std::string &r) {
    retail_price = r;
  }
  void setCoverUrl(const std::string &c) {
    cover_url = c;
  }
  void setProvider(const std::string &p) {
    provider = p;
  }

  Json::Value toJson() const override {
    Json::Value jsonValue;
    jsonValue["isbn"] = isbn;
    jsonValue["title"] = title;
    jsonValue["subtitle"] = subtitle;

    Json::Value jsonAuthors(Json::arrayValue);
    for (const auto &author : authors) {
      jsonAuthors.append(author);
    }
    jsonValue["authors"] = jsonAuthors;
    jsonValue["publisher"] = publisher;
    jsonValue["synopsis"] = synopsis;
    jsonValue["dimensions"]["width"] = dimensions.width;
    jsonValue["dimensions"]["height"] = dimensions.height;
    jsonValue["dimensions"]["unit"] = dimensions.unit;
    jsonValue["year"] = year;
    jsonValue["format"] = format;
    jsonValue["page_count"] = page_count;
    Json::Value jsonSubjects(Json::arrayValue);
    for (const auto &subject : subjects) {
      jsonSubjects.append(subject);
    }
    jsonValue["subjects"] = jsonSubjects;
    jsonValue["location"] = location;
    jsonValue["retail_price"] = retail_price;
    jsonValue["cover_url"] = cover_url;
    jsonValue["provider"] = provider;

    return jsonValue;
  }
};
#endif // BOOKINFO_RESPONSE_H