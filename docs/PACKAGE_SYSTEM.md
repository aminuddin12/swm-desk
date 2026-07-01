# Package System

SWM Desk supports templates and asset distribution via a dedicated package system.

## Specifications

- Extensions, assets, and premium templates are packed into a single compressed package file.
- Every package contains a metadata manifest file (`manifest.json`) specifying details, version, and dependencies.
- The `PackageValidator` validates checksums and licenses.
- The `PackageExtractor` extracts assets to the user storage directories.
