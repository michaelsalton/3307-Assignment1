// make web request using curl

#include "request.h"
#include <curl/curl.h>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::ifstream f("example.json");
json data = json::parse(f);

class request {

    private:
        std::string url_;
        CURL *curl_handle_;
        struct MemoryStruct chunk_;

        static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
            size_t realsize = size * nmemb;
            struct MemoryStruct *mem = (struct MemoryStruct
        }

    public:
    // constructor: initalizes a CURL handle and sets the URL to fetch
        request(std::string url) {
            // Initialize CURL handle
            curl_handle = curl_easy_init();
            // Set URL to fetch
            curl_easy_setopt(curl_handle_, CURLOPT_URL, url.c_str());
            // callback function to handle the data received from the server
            curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, (void *)&chunk_);
            curl_easy_setopt(curl_handle_, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        }

        // destructor: cleans up the handle and frees the memory allocated for the result
        ~request() {
            curl_easy_cleanup(curl_handle_);
            free(chunk_.memory);
        }        

        // performs the request and returns a boolean indicating whether the request was successful or not
        bool execute() {
            CURLcode res = curl_easy_perform(curl_handle_);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                return false;
            }
            return true;
        }

        // returns a string containing the result of the request
        std::string result() {
            return std::string(chunk_.memory);
        }

        // parsing the data
        std::vector<std::string> parse_data(std::string json_str) {
            std::vector<std::string> parsed_data;
            json j = json::parse(json_str);
            for (json::iterator it = j.begin(); it != j.end(); ++it) {
                std::string home_team = it.value()["teams"]["home"]["team"]["name"];
                std::string away_team = it.value()["teams"]["away"]["team"]["name"];
                int home_score = it.value()["teams"]["home"]["score"];
                int away_score = it.value()["teams"]["away"]["score"];
            }
            parsed_data.push_back(home_team + " vs. " + away_team + ": " + std::to_string(home_score) + " - " + std::to_)
            return parsed_data;
        }
};