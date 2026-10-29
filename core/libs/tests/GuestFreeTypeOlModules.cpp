#include "prx/libSceFreeTypeOl/libSceFreeTypeOl.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H
#include <freetype/internal/ftobjs.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>

using FreeType::GuestMemoryRec;

static void Require(bool condition, int line) {
    if (!condition) {
        std::fprintf(stderr, "FreeTypeOl module check failed at line %d\n", line);
        std::abort();
    }
}

#define REQUIRE(condition) Require((condition), __LINE__)

static void* APS5_VABI Allocate(GuestMemoryRec*, std::int64_t size) {
    return std::malloc(static_cast<std::size_t>(size));
}

static void APS5_VABI Release(GuestMemoryRec*, void* block) {
    std::free(block);
}

int main() {
    FT_Library native = nullptr;
    REQUIRE(FT_Init_FreeType(&native) == 0);

    auto* autofitter = static_cast<FT_Module_Class*>(sceFreeTypeOlFtaExportModuleAutofitter_nid_postfix());
    REQUIRE(autofitter != nullptr);
    REQUIRE(autofitter->module_name != nullptr);
    REQUIRE(FT_Get_Module(native, "autofitter") != nullptr);
    REQUIRE(sceFreeTypeOlAddModule_nid_postfix(native, autofitter) == 5);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix(native) == 0);
    REQUIRE(FT_Get_Module(native, "autofitter") == nullptr);
    sceFreeTypeOlFtaAddModuleAutofitter_nid_postfix(native);
    REQUIRE(FT_Get_Module(native, "autofitter") != nullptr);

    sceFreeTypeOlFtaAddModuleGxvalid_nid_postfix(native);
    REQUIRE(FT_Get_Module(native, "gxvalid") != nullptr);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleGxvalid_nid_postfix(native) == 0);
    sceFreeTypeOlFtaAddModuleOtvalid_nid_postfix(native);
    REQUIRE(FT_Get_Module(native, "otvalid") != nullptr);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleOtvalid_nid_postfix(native) == 0);

    REQUIRE(sceFreeTypeOlFtaSupportFormatBdf_nid_postfix(native) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportRendererSmooth_nid_postfix(native) == 0);
    REQUIRE(sceFreeTypeOlGetModuleInterface_nid_postfix(native, "truetype") ==
        FT_Get_Module_Interface(native, "truetype"));

    GuestMemoryRec memory{};
    memory.alloc = Allocate;
    memory.free = Release;
    void* block = nullptr;
    REQUIRE(sceFreeTypeOlAlloc_nid_postfix(&memory, 24, &block) == 0);
    REQUIRE(block != nullptr);
    sceFreeTypeOlFree_nid_postfix(&memory, &block);
    REQUIRE(block == nullptr);
    REQUIRE(sceFreeTypeOlAlloc_nid_postfix(&memory, -1, &block) == 6);
    REQUIRE(block == nullptr);

    REQUIRE(FT_Done_FreeType(native) == 0);
}
