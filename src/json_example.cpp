#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

#include <nlohmann/json.hpp>

// json是key-value的形式，可以是任意的数据类型
// json的key是string类型，value可以是任意的数据类型
// json的value可以是json对象，也可以是json数组
// json的数组是一个有序的集合，可以包含任意的数据类型
// json的对象是一个无序的集合，可以包含任意的数据类型

void SimpleExample() {
  // 1. 创建一个json对象
  nlohmann::json j;
  j["pi"] = 3.141;
  j["happy"] = true;
  j["name"] = "Niels";
  j["nothing"] = nullptr;
  j["answer"]["everything"] = 42;
  j["list"] = {1, 0, 2}; // an array
  j["object"] = {{"currency", "USD"}, {"value", 42.99}}; // an object

  // 2. 访问json对象
  float pi = j["pi"];
  std::cout << "pi: " << pi << std::endl;
  std::string name = j.at("name");
  std::cout << "name: " << name << std::endl;
  std::vector<int> list = j["list"];
  for(auto& item : list) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  std::string currency = j["object"]["currency"];
  std::cout << "currency: " << currency << std::endl;
  double value = j.at("object").at("value");
  std::cout << "value: " << value << std::endl;

  // 3. 写入json对象到文件
  std::string filename1 = "example1.json";
  std::ofstream ofs(filename1);
  ofs << j.dump(4) << std::endl; // 人类可读的格式
  ofs.close();
  std::string filename2 = "example2.json";
  ofs.open(filename2);
  ofs << j << std::endl; // 紧凑的格式
  ofs.close();

  // 4. 从文件中读取json对象
  std::string filename = "/mnt/workspace/cgz_workspace/Exercise/config_parse_example/config/lidar_ego.json";
  std::ifstream ifs(filename);
  if(!ifs.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return;
  }
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  ifs.close();
  std::string str = buffer.str();
  nlohmann::json j2 = nlohmann::json::parse(str);
  double translation_x = j2["transform"]["translation"]["x"];
  std::cout << "translation_x: " << translation_x << std::endl;
}

void StringToJSON() {
  // 1. 从字符串中解析json对象
  std::string str = R"(
  {
    "pi": 3.141,
    "happy": true,
    "name": "Niels"
  })";
  nlohmann::json j = nlohmann::json::parse(str);
  double pi = j["pi"];
  std::cout << "pi: " << pi << std::endl;
  std::string name = j.at("name");
  std::cout << "name: " << name << std::endl;

  // 2.1 _json操作符重载
  nlohmann::json j2 = "{\"happy\": true, \"pi\": 3.141}"_json;
  double pi2 = j2["pi"];
  std::cout << "pi2: " << pi2 << std::endl;
  bool happy = j2.at("happy");
  std::cout << "happy: " << happy << std::endl;
  // 2.2 _json操作符重载
  nlohmann::json j3 = R"(
  {
    "happy": true,
    "pi": 3.141
  })"_json;
  double pi3 = j3["pi"];
  std::cout << "pi3: " << pi3 << std::endl;
  bool happy3 = j3.at("happy");
  std::cout << "happy3: " << happy3 << std::endl;

  // 3.1 json转换为字符串
  std::stringstream ss;
  ss << j.dump(4) << std::endl;
  std::string str2 = ss.str();
  std::cout << str2 << std::endl;

  // 3.2 json转换为字符串
  std::string str3 = j.dump();
  std::cout << str3 << std::endl;
}

int main() {
  std::cout << "==================== Simple Example ====================" << std::endl;
  SimpleExample();
  std::cout << "==================== String to JSON ====================" << std::endl;
  StringToJSON();
  return 0;  
}