# Coding Standards

Enforced coding rules for the SWM Desk codebase:

- **SOLID Principles**: Maintain clean classes with single responsibilities.
- **Strict Clean Code**: Code must be self-documenting through semantic naming.
- **Absolute Zero Comments**: No comments of any kind (//, /* */, #) are permitted in code files.
- **Memory Safety**: Avoid raw pointers. Use `std::unique_ptr` and `std::shared_ptr`.
- **RAII**: Resource acquisition is initialization. Manage file and connection lifecycles via scope guards.
