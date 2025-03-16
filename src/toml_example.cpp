#include <iostream>
#include <string>

#include "toml.hpp"

// TOML的基本结构是键值对（key-value pair）。
// 键是不区分大小写的字符串
// 值可以是以下类型之一：字符串、整数、浮点数、布尔值、日期时间、数组和嵌套表（table）。

// 数组
// fruits = ["apple", "banana", "cherry"]

// 嵌套表
// [fruit]
// name = "apple"
// color = "red"

using namespace toml::literals::toml_literals;

void Init() {
  try {
    toml::value data = toml::parse("/mnt/workspace/cgz_workspace/Exercise/config_parse_example/config/toml_example.toml");

    toml::value data2 = "b = 42"_toml;

    std::ifstream ifs("/mnt/workspace/cgz_workspace/Exercise/config_parse_example/config/toml_example.toml");
    toml::value data3 = toml::parse(ifs);

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void Parse() {
  toml::value data = toml::parse("/mnt/workspace/cgz_workspace/Exercise/config_parse_example/config/toml_example.toml");

  toml::value perception_parameters = toml::find(data, "perception_parameters");
  std::string obstacle_model_path = toml::find<std::string>(perception_parameters, "obstacle_model_path");
  std::cout << "obstacle_model_path: " << obstacle_model_path << std::endl;
  
  // 多层嵌套
  int pid = toml::find<int>(data, "perception_parameters", "param", "pid");
  std::cout << "pid: " << pid << std::endl; 

  // 数组得话可以指定解析第几个
  toml::value param = toml::find(data, "perception_parameters", "param");
  std::string ret = toml::find<std::string>(param, "shuzu", 1);
  std::cout << "ret: " << ret << std::endl;

  // check if key exists
  bool has_key = data.contains("perception_parameters");
  if(has_key) {
    std::cout << "perception_parameters exists" << std::endl;
  } else {
    std::cout << "perception_parameters not exists" << std::endl;
  }
  toml::value perception_parameters1 = data.at("perception_parameters");
  std::uint32_t count = perception_parameters1.count("obstacle_model_path");
  std::cout << "count: " << count << std::endl;

  // Get a toml value: toml::table
  const toml::value value1 = toml::get<toml::table>(data).at("perception_parameters");
  std::string path = toml::find<std::string>(value1, "obstacle_model_path");
  std::cout << "path: " << path << std::endl;

  // Get a toml value: toml::string
  toml::value value2 = toml::get<toml::table>(data).at("perception_parameters");
  toml::value value3 = toml::get<toml::table>(value2).at("backbone_model_path");
  toml::string path1 = toml::get<toml::string>(value3);
  std::cout << "path1: " << path1 << std::endl;

  // at 和 operator[]
  toml::value value4 = toml::get<toml::table>(data).at("perception_parameters").at("param").at("shuzu");
  std::string str = value4.at(1).as_string();
  std::cout << "str: " << str << std::endl;
  str = value4[1].as_string();
  std::cout << "str: " << str << std::endl;
}

void Write() {
  toml::value v1(true);     // boolean
  toml::value v2(42);       // integer
  toml::value v3(3.14);     // floating
  toml::value v4("foobar"); // string
  toml::value v5(toml::local_date(2019, toml::month_t::Apr, 1)); // date
  toml::value v6{1, 2, 3, 4, 5};                                 // array
  toml::value v7{{"foo", 42}, {"bar", 3.14}, {"baz", "qux"}};    // table
  toml::value v8 = toml::table{{"foo", 42}, {"bar", 3.14}, {"baz", "qux"}};

  std::string str = toml::format(v8);

  std::ofstream ofs("./toml.toml");
  ofs << str;
  ofs.close();

}

int main() {
  std::cout << "===============Init===============" << std::endl;
  Init();
  std::cout << "===============Parse===============" << std::endl;
  Parse();
  std::cout << "===============Write===============" << std::endl;
  Write();
  return 0;
}