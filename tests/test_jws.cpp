#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <jws/json_with_schema.hpp>
#include <iostream>

#ifdef WIN32
#include "direct.h" // chdir
#else
#include "unistd.h" // chdir
#endif

using namespace std;

TEST_CASE("Can load and validate JSON", "[test_jws]" ) {
  SECTION("Can validate example schema") {
    auto validator = load_validator("examples/schemas/example_schema.json");
    SECTION("Good document passes") {
      auto document = load_json("examples/documents/example_document.json");
      REQUIRE_NOTHROW(validator.validate(document));
    }
    SECTION("Bad document fails") {
      auto document = load_json("examples/documents/example_document_bad.json");
      REQUIRE_THROWS(validator.validate(document));
    }
  }
  SECTION("Can validate example schema with references") {
    auto validator = load_validator("examples/schemas/example_schema_with_refs.json");
    SECTION("Good document passes") {
      auto document = load_json("examples/documents/example_document_address.json");
      REQUIRE_NOTHROW(validator.validate(document));
    }
    SECTION("Bad document fails") {
      auto document = load_json("examples/documents/example_document_bad.json");
      REQUIRE_THROWS(validator.validate(document));
    }
  }
}

int main( int argc, char* argv[] )
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
