// make web request using curl

#include "request.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class request {

  

    std::ifstream file("data.json");
    json data = json::parse(file);
 




}