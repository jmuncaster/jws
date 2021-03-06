#pragma once
#include <nlohmann/json.hpp>         // nlohman/json
#include <nlohmann/json-schema.hpp>  // pboettch/json-schema-validator
#include <fstream>
#include <stdexcept>
#include <string>

namespace jws {
  using nlohmann::json;
  using nlohmann::json_uri;
  using nlohmann::json_schema::json_validator;

  inline json load_json(const std::string& filename) {
    std::ifstream json_file(filename);
    if (!json_file.good()) {
      throw std::invalid_argument(std::string("cannot open: ") + filename);
    }
    json document;
    json_file >> document;
    return document;
  }

  inline void loader(const json_uri& uri, json& schema) {
    auto path = uri.path();
    std::fstream s(uri.path().c_str());
    if (!s.good()) {
      // A bit of a hack here, to allow relative paths in the schema references.
      //
      // json_uri automatically prepends a '/' to relative paths. There is probably a good
      // reason for this. However, for backwards compatibilty we need to allow relative
      // paths.
      //
      // So we will try again to load the file, omitting the initial '/'.
      path = path.substr(1);
      s = std::fstream(path.c_str());
      if (!s.good()) {
        throw std::invalid_argument("could not open " + uri.url() + " for schema loading\n");
      }
    }

    try {
      s >> schema;
    }
    catch (std::exception &e) {
      throw e;
    }
  }

  inline json_validator load_validator(const json& schema) {
    json_validator validator(loader);
    validator.set_root_schema(schema);
    return validator;
  }

  inline json_validator load_validator(const std::string& schema_filename) {
    json schema = load_json(schema_filename);
    return load_validator(schema);
  }

  inline json_validator load_validator(const char* schema_filename) {
    return load_validator(std::string(schema_filename));
  }
}

