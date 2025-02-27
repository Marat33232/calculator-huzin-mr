# calculator-huzin-mr

## What has been done?
A calculator app written in C that supports integer and float modes. Unit tests are implemented using Google Test framework. Integration tests (optional) are written in Python.

## How to run/use it?
1. Compile the project: `make all`
2. Run in integer mode: `make run-int`
3. Run in float mode: `make run-float`
4. Run unit tests: `make run-unit-test`
5. Run integration tests: `make venv && make run-integration-tests`

## How it's made?
The program uses a stack-based approach for parsing and evaluating arithmetic expressions. It supports operators `+`, `-`, `*`, `/`, `(`, and `)`.

### Build System
- `Makefile` manages dependencies carefully.
- Artifacts: `app.exe` and `unit-tests.exe`.
- Rules:
  - `make all`: Builds both artifacts.
  - `make clean`: Cleans the repository.
  - `make clang-format`: Formats source files using ClangFormat.# Calculator
A simple calculator program in C.
