#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <jws/json_with_schema.hpp>
#include <iostream>

using namespace std;

TEST_CASE("Loads and validates JSON against schema", "[test_jws]" ) {
  GIVEN("a simple schema") {
    auto validator = load_validator("examples/schemas/example_schema.json");
    WHEN("a document that satisfies the schema is provided") {
      auto document = load_json("examples/documents/example_document.json");
      THEN("the validator does not throw an exception") {
        REQUIRE_NOTHROW(validator.validate(document));
      }
    }
    WHEN("a document that does not satisfy the schema is provided") {
      auto document = load_json("examples/documents/example_document_bad.json");
      THEN("the validator throws an exception") {
        REQUIRE_THROWS(validator.validate(document));
      }
    }
  }
  GIVEN("a schema with references") {
    auto validator = load_validator("examples/schemas/example_schema_with_refs.json");
    WHEN("a document that satisfies the schema is provided") {
      auto document = load_json("examples/documents/example_document_address.json");
      THEN("the validator does not throw an exception") {
        REQUIRE_NOTHROW(validator.validate(document));
      }
    }
    WHEN("a document that does not satisfy the schema is provided") {
      auto document = load_json("examples/documents/example_document_bad.json");
      THEN("the validator throws an exception") {
        REQUIRE_THROWS(validator.validate(document));
      }
    }
  }
}

// Override main so that we can add the --working_dir option
// https://github.com/catchorg/Catch2/blob/master/docs/own-main.md#adding-your-own-command-line-options
#ifdef WIN32
#include "direct.h" // chdir
#else
#include "unistd.h" // chdir
#endif
int main(int argc, char* argv[])
{
  Catch::Session session; // There must be exactly one instance

  string working_dir;

  // Build a new parser on top of Catch's
  using namespace Catch::clara;
  auto cli
    = session.cli() // Get Catch's composite command line parser
    | Opt(working_dir, "working_dir" ) // bind variable to a new option, with a hint string
        ["-wd"]["--working_dir"]    // the option names it will respond to
        ("Working directory when running test");        // description string for the help output

  // Now pass the new composite back to Catch so it uses that
  session.cli(cli);

  // Let Catch (using Clara) parse the command line
  int return_code = session.applyCommandLine(argc, argv);
  if (return_code != 0) { // Indicates a command line error
  	return return_code;
  }

  cout  << working_dir << endl;
  if (!working_dir.empty()) {
    int return_code = chdir(working_dir.c_str());
    if (return_code != 0) {
      cerr << "Error setting working_dir: " << working_dir << endl;
      return return_code;
    }
  }

  return session.run();
}

