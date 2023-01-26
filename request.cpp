// make web request using curl

#include "request.h"
#include <curl/curl.h>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


class request {

  

    std::ifstream f("example.json");
    json data = json::parse(f);
 




}