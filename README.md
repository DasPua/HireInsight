# HireInsight — Resume Parser

A C++ resume parser that extracts and structures information from **PDF, DOCX, and TXT** documents.

## Features

* PDF, DOCX, and TXT parsing
* Text preprocessing
* Resume section classification
* Entity extraction
* Modular C++ architecture
* CMake-based build system

## Architecture

```text
Resume Document
      │
      ▼
Document Parser
      │
      ▼
Preprocessor
      │
      ▼
Section Classifier
      │
      ▼
Entity Extractor
      │
      ▼
Structured Resume
```

## Project Structure

```text
.
├── CMakeLists.txt
├── include/
│   └── ResumeParser/
│       ├── Core/
│       ├── DocumentParser/
│       ├── EntityExtractor/
│       ├── Preprocessor/
│       ├── ResumeParserPipeline/
│       └── SectionClassifier/
├── src/
│   ├── DocumentParser/
│   ├── EntityExtractor/
│   ├── Preprocessor/
│   ├── ResumeParserPipeline/
│   ├── SectionClassifier/
│   └── main.cpp
├── tests/
└── data/
```

`data/` contains local/sample resume documents and is excluded from version control.

## Requirements

* C++ compiler
* CMake
* Make or Ninja

## Build

Clone the repository:

```bash
git clone git@github.com:DasPua/HireInsight.git
cd HireInsight
```

Create a build directory:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Run:

```bash
./resume_parser
```

## Components

### Document Parser

Handles different input formats through dedicated parsers:

* `PdfParser`
* `DocxParser`
* `TxtParser`

`DocumentParserFactory` selects the appropriate parser.

### Preprocessor

Cleans and prepares extracted text for further processing.

### Section Classifier

Identifies logical resume sections such as:

* Education
* Experience
* Skills
* Projects
* Certifications

### Entity Extractor

Extracts structured information from the processed resume.

### Resume Parser Pipeline

Coordinates the complete parsing process from document input to structured resume data.

## Development

Generated build files and local resume data are excluded from Git:

```text
build/
data/
```

## Version

**Build 1.0**
