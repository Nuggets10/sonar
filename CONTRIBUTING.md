# Contributing
Thank you for your interest in contributing to this project!
Before submitting a contribution, please read the guidelines below.

## Issues
When opening an issue, provide a clear and detailed explanation of the problem or suggestion.

For bug reports, please include:
- Steps to reproduce the issue.
- Expected and actual behavior.
- Operating system and architecture.
- Relevant error messages or logs.

Screenshots may also be useful when applicable.

## Pull requests

#### Requirements
- C++ compiler supporting C++17
- CMake
- ncurses development library
- Git

#### Getting the source code
1) Fork the repository
2) Clone your fork
```bash
git clone https://github.com/<your username>/sonar.git
```
3) Navigate to the newly created directory
```bash
cd sonar
```
4) Add the original repository as the upstream remote
```bash
git remote add upstream https://github.com/Nuggets10/sonar.git
```

#### Making changes
After you've made changes, please run the compilation process to make sure no errors or warnings are returned.
```bash
make
```
Before pushing the changes, please run the auto formatter tool. Make sure you are in the root directory for this command to work properly.
```
./tools/format.sh
```
Once you are satisfied with your changes, you can open a pull request.
Make sure your pull request includes:
- A clear explanation of what you changed.
- The reason for the changes.
- Any relevant testing performed.

Please keep pull requests focused on a single feature or issue.
An automated GitHub Actions workflow will run to verify that your code compiles successfully.