project(Can-I-Haz-Warnings-Fuzzing CXX)

find_package(Threads REQUIRED)

# Fuzzers
function(define_fuzzer name source)
  add_executable(${name} ${source})
  target_link_libraries(${name} PRIVATE Threads::Threads -fsanitize=fuzzer Can-I-Haz-Warnings-lib)
  target_compile_options(${name} PRIVATE -fsanitize=fuzzer)
  target_include_directories(${name} PRIVATE "include")
  set_property(TARGET ${name} PROPERTY CXX_STANDARD 17)
endfunction()

define_fuzzer(fuzz_parser "src/Parser.fuzz.cpp")

define_fuzzer(fuzz_application_args "src/ApplicationArgs.fuzz.cpp")
