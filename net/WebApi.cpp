#include <curl/curl.h>

#include <iostream>
#include <string>

size_t callBackFunk(char* ptr, size_t size, size_t nmemb, std::string* stream) {
  int realsize = size * nmemb;
  stream->append(ptr, realsize);
  return realsize;
}

// ex. url_get_proc("sample.com/get")
// g++ filename -lcurl
std::string url_get_proc(const char url[]) {
  CURL* curl;
  CURLcode res;
  curl = curl_easy_init();
  std::string chunk;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (std::string*)&chunk);
    curl_easy_setopt(curl, CURLOPT_PROXY, "");
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  if (res != CURLE_OK) {
    return static_cast<std::string>("curl error");
  }

  return chunk;
}

std::string url_get_proc(const std::string url) {
  return url_get_proc(url.c_str());
}
