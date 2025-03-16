#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>

// YAML 支持以下几种数据类型：
// 1. 对象：键值对的集合，又称为映射（mapping）/ 哈希（hashes） / 字典（dictionary）
// 2. 数组：一组按次序排列的值，又称为序列（sequence） / 列表（list）
// 3. 纯量（scalars）：单个的、不可再分的值

// 纯量 中需要注意：
// 1. 日期必须使用ISO 8601格式，即yyyy-MM-dd，如2018-02-17
// 2. 时间使用ISO 8601格式，时间和日期之间使用T连接，最后使用+代表时区，如2018-02-17T15:02:31+08:00

template <typename T>
bool yamlRead(const YAML::Node& node, const std::string& key, T& value) {
  if(node[key]) {
    value = node[key].as<T>();
    return true;
  }
  return false;
}

void Init() {
  YAML::Node node;
  if(node.IsNull()) {
    std::cout << "node is null" << std::endl;
  }

  node = YAML::Node();
  if(node.IsNull()) {
    std::cout << "node is null" << std::endl;
  } else {
    std::cout << "node is not null" << std::endl;
  }

  YAML::Node node1 = YAML::Load("name: Hello, World");
  if(node1.IsNull()) {
    std::cout << "node1 is null" << std::endl;
  } else {
    std::cout << "node1 is not null" << std::endl;
  }
  std::cout << node1["name"].as<std::string>() << std::endl;
  
  std::string name;
  if(yamlRead(node1, "name", name)) {
    std::cout << "name: " << name << std::endl;
  }

  YAML::Node node2 = YAML::Load("foo");
  std::string ret = node2.as<std::string>();
  std::cout << "ret: " << ret << std::endl;

  try {
    YAML::Node node3 = YAML::Load("-128");
    std::uint32_t value = node3.as<std::uint32_t>();
  } catch(const YAML::Exception& e) {
    std::cout << "YAML::Exception: " << e.what() << std::endl;
  }
  
  YAML::Node node4 = YAML::LoadFile("/mnt/workspace/cgz_workspace/Exercise/config_parse_example/config/yaml_example.yaml");
  if(node4.IsNull()) {
    std::cout << "node4 is null" << std::endl;
  } else {
    std::cout << "node4 is not null" << std::endl;
  }
}

void ParseFile() {
  YAML::Node node = YAML::LoadFile("/mnt/workspace/cgz_workspace/Exercise/config_parse_example/config/yaml_example.yaml");
  if(node.IsNull()) {
    std::cout << "node is null" << std::endl;
  } else {
    std::cout << "node is not null" << std::endl;
  }

  YAML::Node vehicle_info = node["radar_node"]["ros__parameters"]["vehicle_info"];
  if(vehicle_info.IsNull()) {
    std::cout << "vehicle_info is null" << std::endl;
  } else {
    std::cout << "vehicle_info is not null" << std::endl;
  }

  std::string brand = vehicle_info["brand"].as<std::string>();
  std::cout << "brand: " << brand << std::endl;

  bool is_defined = node["radar_node"]["ros__parameters"]["vehicle_info"].IsDefined();
  std::cout << "is_defined: " << is_defined << std::endl;
  // 检查key是否存在
  is_defined = node["radar_node"]["ros__parameters"]["vehicle_in"].IsDefined();
  std::cout << "is_defined: " << is_defined << std::endl;
}

void WriteFile() {
  YAML::Node node;
  node["name"] = "Hello, World";
  node["age"] = 18;  
  node["num"].push_back(1);
  node["num"].push_back(2);
  node["num"].push_back(3);

  YAML::Node radar_info = YAML::Node(YAML::NodeType::Sequence);
  YAML::Node radar1;
  radar1["brand"] = "Benz";
  radar1["price"] = 100000;
  radar_info.push_back(radar1);

  node["radar_info"] = radar_info;

  std::ofstream fout("./yaml.yaml");
  fout << node << std::endl;
  fout.close();
}

int main() {
  std::cout << "=================Init=================" << std::endl;
  Init();
  std::cout << "=================ParseFile=================" << std::endl;
  ParseFile();
  std::cout << "=================WriteFile=================" << std::endl;
  WriteFile();
  return 0;
}