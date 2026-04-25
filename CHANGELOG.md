# CHANGELOG

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased] 

## [0.9.1] - 2026-4-25

### Added

- Introduced this Changelog
- Incorporated a GitHub Action to [validate](https://github.com/arduino/arduino-lint-action) Arduino Library packaging

### Fixed
- Fixed memory overrun bug in retained data management

### Changed
- Adopted /examples and /src subfolder structure in order to conform
to the [Arduino Library Specification](https://arduino.github.io/arduino-cli/1.4/library-specification/)

## [0.9.0] - 2025-1-17

### Added
- Initial packaging as an Arduino Library
- Implemented retained data storage

### Changed
- Restructured as an .hpp file to enable C++ template usage
