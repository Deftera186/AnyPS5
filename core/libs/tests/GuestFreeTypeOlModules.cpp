#include "prx/libSceFreeTypeOl/libSceFreeTypeOl.hpp"
#include "prx/libSceFreeType/include/GuestObjects.hpp"
#include "FreeTypeFontFixture.hpp"

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
    GuestLibrary* library = nullptr;
    REQUIRE(FT_Init_FreeType_nid_postfix(&library) == 0);
    REQUIRE(library != nullptr && library->host != nullptr);
    FT_Library native = library->host;

    auto* autofitter = static_cast<FT_Module_Class*>(sceFreeTypeOlFtaExportModuleAutofitter_nid_postfix());
    REQUIRE(autofitter != nullptr);
    REQUIRE(autofitter->module_name != nullptr);
    REQUIRE(sceFreeTypeOlAddModule_nid_postfix(nullptr, autofitter) == 0x21);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix(nullptr) == 0x21);
    REQUIRE(sceFreeTypeOlGetModuleInterface_nid_postfix(nullptr, "truetype") == nullptr);
    REQUIRE(FT_Get_Module(native, "autofitter") != nullptr);
    REQUIRE(sceFreeTypeOlAddModule_nid_postfix(library, autofitter) == 5);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix(library) == 0);
    REQUIRE(FT_Get_Module(native, "autofitter") == nullptr);
    sceFreeTypeOlFtaAddModuleAutofitter_nid_postfix(library);
    REQUIRE(FT_Get_Module(native, "autofitter") != nullptr);

    sceFreeTypeOlFtaAddModuleGxvalid_nid_postfix(library);
    REQUIRE(FT_Get_Module(native, "gxvalid") != nullptr);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleGxvalid_nid_postfix(library) == 0);
    sceFreeTypeOlFtaAddModuleOtvalid_nid_postfix(library);
    REQUIRE(FT_Get_Module(native, "otvalid") != nullptr);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleOtvalid_nid_postfix(library) == 0);

    REQUIRE(sceFreeTypeOlFtaSupportFormatBdf_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportRendererSmooth_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlGetModuleInterface_nid_postfix(library, "truetype") ==
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

    const auto font = SquareGlyphFont('A', 700, true);
    GuestFaceRec* face = nullptr;
    REQUIRE(FT_New_Memory_Face_nid_postfix(library, font.data(), font.size(), 0, &face) == 0);
    REQUIRE(face != nullptr && face->glyph != nullptr);
    sceFreeTypeOlDoneGlyphSlot_nid_postfix(nullptr);
    sceFreeTypeOlDoneGlyphSlot_nid_postfix(face->glyph);
    REQUIRE(face->glyph == nullptr);
    REQUIRE(FT_Done_Face_nid_postfix(face) == 0);

    REQUIRE(FT_Done_FreeType_nid_postfix(library) == 0);
}
