#include <json.hpp>         // nlohman/json
#include <json-schema.hpp>  // pboettch/json-schema-validator
#include <fstream>
#include <string>

using nlohmann::json;
using nlohmann::json_schema_draft4::json_validator;

json load_json(const std::string& filename) {
  std::ifstream json_file(filename);
  json document;
  json_file >> document;
  return document;
}

json_validator load_validator(const std::string& schema_filename) {
  json schema = load_json(schema_filename);
  json_validator validator;
  validator.set_root_schema(schema);
  return validator;
}
