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
  // 解析toml文件
  toml::value data = toml::parse("/mnt/workspace/cgz_workspace/Exercise/config_parse_example/config/toml_example.toml");

  /****************************title***********************************/
  bool title_exists = data.contains("title");
  if (title_exists) {
    std::cout << "title exists" << std::endl;
  } else {
    std::cout << "title not exists" << std::endl;
  }
  toml::value title = toml::find(data, "title");
  if(title.is_string()) {
    std::cout << "title is string" << std::endl;
  } else {
    std::cout << "title is not string" << std::endl;
  }
  if(title.is_integer()) {
    std::cout << "title is integer" << std::endl;
  } else {
    std::cout << "title is not integer" << std::endl;
  }
  if(title.is_floating()) {
    std::cout << "title is floating" << std::endl;
  } else {
    std::cout << "title is not floating" << std::endl;
  }
  if(title.is_boolean()) {
    std::cout << "title is boolean" << std::endl;
  } else {
    std::cout << "title is not boolean" << std::endl;
  }
  if(title.is_table()) {
    std::cout << "title is table" << std::endl;
  } else {
    std::cout << "title is not table" << std::endl;
  }
  std::string title_str_0 = data.at("title").as_string();
  std::cout << "title: " << title_str_0 << std::endl;

  std::string title_str_1 = toml::find<std::string>(data, "title");
  std::cout << "title: " << title_str_1 << std::endl;

  std::string title_str_2 = data["title"].as_string();
  std::cout << "title: " << title_str_2 << std::endl;
#if 0
  // count只用于table类型
  std::size_t title_count = title.count("title");
  std::cout << "title count: " << title_count << std::endl;
#endif

  /****************************servers***********************************/
  bool servers_exists = data.contains("servers");
  if (servers_exists) {
    std::cout << "servers exists" << std::endl;
  } else {
    std::cout << "servers not exists" << std::endl;
  }
  toml::value servers = toml::find(data, "servers");
  if(servers.is_array()) {
    std::cout << "servers is array" << std::endl;
  } else {
    std::cout << "servers is not array" << std::endl;
  }
  if(servers.is_table()) {
    std::cout << "servers is table" << std::endl;
  } else {
    std::cout << "servers is not table" << std::endl;
  }
  std::size_t servers_count = servers.count("servers");
  std::cout << "servers count: " << servers_count << std::endl;
  std::size_t servers_size = servers.size();
  std::cout << "servers size: " << servers_size << std::endl;
  toml::value servers_0 = servers.at("alpha");
  std::string servers_0_ip = toml::find<std::string>(servers_0, "ip");
  std::cout << "servers_0 ip: " << servers_0_ip << std::endl;
  std::string servers_0_dc = toml::find<std::string>(servers_0, "dc");
  std::cout << "servers_0 dc: " << servers_0_dc << std::endl;
  
  // 多层嵌套
  std::string owner_name = toml::find<std::string>(data, "owner", "name");
  std::cout << "owner_name: " << owner_name << std::endl; 

  // 数组得话可以指定解析第几个
  toml::value ports = toml::find(data, "database", "ports");
  if(ports.is_array()) {
    std::cout << "ports is array" << std::endl;
  } else {
    std::cout << "ports is not array" << std::endl;
  }
  int ret_0 = toml::find<int>(ports, 0);
  std::cout << "ret_0: " << ret_0 << std::endl;
  int ret_1 = ports.at(1).as_integer();
  std::cout << "ret_1: " << ret_1 << std::endl;
  int ret_2 = ports[2].as_integer();
  std::cout << "ret_2: " << ret_2 << std::endl;

  // Get a toml value: toml::table
  const toml::value value1 = toml::get<toml::table>(data).at("servers").at("alpha");
  toml::value value2 = toml::get<toml::table>(value1).at("ip");
  std::string ip = toml::get<toml::string>(value2);
  std::cout << "ip: " << ip << std::endl;
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
  toml::table v9_0;
  v9_0["weight"] = 1.0;
  v9_0["height"] = 2.0;
  toml::table v9_1;
  v9_1["fruit"]["apple"] = v9_0;
  toml::value v9 = v9_1;

  std::string str_1 = toml::format(v1);
  std::string str_2 = toml::format(v2);
  std::string str_3 = toml::format(v3);
  std::string str_4 = toml::format(v4);
  std::string str_5 = toml::format(v5);
  std::string str_6 = toml::format(v6);
  std::string str_7 = toml::format(v7);
  std::string str_8 = toml::format(v8);
  std::string str_9 = toml::format(v9);

  std::ofstream ofs("/mnt/workspace/cgz_workspace/Exercise/config_parse_example/output/toml.toml");
  if(!ofs.is_open()) {
    std::cerr << "Failed to open file for writing" << std::endl;
    return;
  }
  ofs << str_1 << "\n";
  ofs << str_2 << "\n";
  ofs << str_3 << "\n";
  ofs << str_4 << "\n";
  ofs << str_5 << "\n";
  ofs << str_6 << "\n";
  ofs << str_7 << "\n";
  ofs << str_8 << "\n";
  ofs << str_9 << "\n";
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