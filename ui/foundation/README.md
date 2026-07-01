# SWM Foundation

The lowest layer of the UI framework. This module contains absolutely pure, context-free, decoupled primitives.

## Dependency Rules
- Foundation modules **CANNOT** import `SWM.Theme`, `SWM.Components`, or anything else.
- Components **SHOULD NOT** use Foundation Colors directly (use Theme Engine).
- Components *may* use Foundation Spacing, Radius, and Motion directly.
