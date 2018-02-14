#include <jws/json_with_schema.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

  if (argc != 3) {
    cout << "usage: validate_json <schema.json> <document.json>" << endl;
    return 1;
  }

  cout << "  schema: " << argv[1] << endl;
  cout << "document: " << argv[2] << endl;

  auto validator = jws::load_validator(argv[1]);
  auto document = jws::load_json(argv[2]);
  validator.validate(document); // throws on error

  cout << "document validated" << endl;

  return 0;
}
