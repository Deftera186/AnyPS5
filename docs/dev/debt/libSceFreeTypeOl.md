# libSceFreeTypeOl technical debt

### Silent stubs requiring Sony-specific or shared-state behavior

The PS5 3.20 export inventory and verified NID-name database identify 92 exports in this library. The decrypted local PS5 13.60 `libSceFreeTypeOl.sprx` (SHA-256 `61E0CDB1628968A9D26790D8F6C2874C0CBF86193DC1762BA83E434CF229BADA`) was analyzed locally with Ghidra; no binary or decompilation is included in this repository. The analysis confirmed the FreeType wrapper signatures and the shared-library module lifecycle.

Seventy exports now forward to the bundled FreeType implementation: add/export/remove helpers for the 18 available module classes, the basic module support helpers, allocator/free, module-interface lookup, module registration, stream attachment, charmap lifecycle, and glyph-slot destruction. The implementation uses the matching FreeType 2.13 internal APIs and preserves the PS5 duplicate-module result behavior. Focused coverage is in `GuestFreeTypeOlModules.cpp`.

The remaining 22 exports deliberately retain `NotImplemented_nid_no_patch` because their behavior cannot be represented by the currently bundled FreeType modules or its per-library state:

- Raster5 add/export/remove/support (`wbyY8kfNfaI`, `6zDeyzjWz-8`, `SKUldaN3e2A`, `Tzm-z36UYKg`): the Sony Raster5 module is absent from the bundled FreeType sources.
- Smooth LCD and LCD vertical add/export/remove/support (`NLA7bmDS1jc`, `xcJCXHqBrjE`, `+bRRhPeBqZI`, `q7kTOFaQrW4`, `xtb9fOR6ilA`, `6z2P2V2XCiI`, `M94SjXo-UVA`, `Ns9a-LjOcDw`): Sony exports distinct renderer descriptors; the bundled library has one smooth renderer, so aliasing these descriptors would give incorrect add/remove behavior.
- Composite format/module configuration (`JuzrPZClLew`, `sylevnx-fqk`, `0RSuGozMl9o`, `J3HnvW8FJV8`, `YpxR8CqGMIM`, `83qtpn8+XnA`, `g2p7fkJpuC0`, `xqjAbn8VNGo`, `oM0zMNCfXKM`): these routines combine module registration with Sony-specific support-mask state. Implementing registration alone would omit observable state updates.
- `FT_Done_Memory` (`UTumVjeIQtg`): the export has no parameter and operates on a Sony-owned global memory manager; the host FreeType library exposes a separate manager for each library.

Each remaining export keeps its original NID alias and throws through `NotImplemented_nid_no_patch` until its required implementation or state mapping is available.
