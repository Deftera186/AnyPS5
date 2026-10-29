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
using FreeType::GuestLibrary;
using FreeType::GuestFaceRec;

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

    struct ModuleCase {
        void* (APS5_VABI* exportClass)();
        void (APS5_VABI* add)(void*);
        int (APS5_VABI* remove)(void*);
    };
    const ModuleCase cases[] = {
        {sceFreeTypeOlFtaExportModuleAutofitter_nid_postfix, sceFreeTypeOlFtaAddModuleAutofitter_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix},
        {sceFreeTypeOlFtaExportModuleBdf_nid_postfix, sceFreeTypeOlFtaAddModuleBdf_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleBdf_nid_postfix},
        {sceFreeTypeOlFtaExportModuleCff_nid_postfix, sceFreeTypeOlFtaAddModuleCff_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleCff_nid_postfix},
        {sceFreeTypeOlFtaExportModulePcf_nid_postfix, sceFreeTypeOlFtaAddModulePcf_nid_postfix,
         sceFreeTypeOlFtaRemoveModulePcf_nid_postfix},
        {sceFreeTypeOlFtaExportModulePfr_nid_postfix, sceFreeTypeOlFtaAddModulePfr_nid_postfix,
         sceFreeTypeOlFtaRemoveModulePfr_nid_postfix},
        {sceFreeTypeOlFtaExportModulePsaux_nid_postfix, sceFreeTypeOlFtaAddModulePsaux_nid_postfix,
         sceFreeTypeOlFtaRemoveModulePsaux_nid_postfix},
        {sceFreeTypeOlFtaExportModulePshinter_nid_postfix, sceFreeTypeOlFtaAddModulePshinter_nid_postfix,
         sceFreeTypeOlFtaRemoveModulePshinter_nid_postfix},
        {sceFreeTypeOlFtaExportModulePsnames_nid_postfix, sceFreeTypeOlFtaAddModulePsnames_nid_postfix,
         sceFreeTypeOlFtaRemoveModulePsnames_nid_postfix},
        {sceFreeTypeOlFtaExportModuleRaster1_nid_postfix, sceFreeTypeOlFtaAddModuleRaster1_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleRaster1_nid_postfix},
        {sceFreeTypeOlFtaExportModuleSfnt_nid_postfix, sceFreeTypeOlFtaAddModuleSfnt_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleSfnt_nid_postfix},
        {sceFreeTypeOlFtaExportModuleSmooth_nid_postfix, sceFreeTypeOlFtaAddModuleSmooth_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleSmooth_nid_postfix},
        {sceFreeTypeOlFtaExportModuleT1cid_nid_postfix, sceFreeTypeOlFtaAddModuleT1cid_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleT1cid_nid_postfix},
        {sceFreeTypeOlFtaExportModuleTruetype_nid_postfix, sceFreeTypeOlFtaAddModuleTruetype_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleTruetype_nid_postfix},
        {sceFreeTypeOlFtaExportModuleType1_nid_postfix, sceFreeTypeOlFtaAddModuleType1_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleType1_nid_postfix},
        {sceFreeTypeOlFtaExportModuleType42_nid_postfix, sceFreeTypeOlFtaAddModuleType42_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleType42_nid_postfix},
        {sceFreeTypeOlFtaExportModuleWinfonts_nid_postfix, sceFreeTypeOlFtaAddModuleWinfonts_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleWinfonts_nid_postfix},
        {sceFreeTypeOlFtaExportModuleGxvalid_nid_postfix, sceFreeTypeOlFtaAddModuleGxvalid_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleGxvalid_nid_postfix},
        {sceFreeTypeOlFtaExportModuleOtvalid_nid_postfix, sceFreeTypeOlFtaAddModuleOtvalid_nid_postfix,
         sceFreeTypeOlFtaRemoveModuleOtvalid_nid_postfix},
    };

    GuestLibrary invalidLibrary{};
    REQUIRE(sceFreeTypeOlFtaAddModule_nid_postfix(&invalidLibrary, nullptr) == 0x21);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix(&invalidLibrary) == 0x21);
    REQUIRE(sceFreeTypeOlGetModuleInterface_nid_postfix(&invalidLibrary, "truetype") == nullptr);
    REQUIRE(sceFreeTypeOlAddModule_nid_postfix(library, nullptr) == 6);
    REQUIRE(sceFreeTypeOlGetModuleInterface_nid_postfix(library, nullptr) == nullptr);
    REQUIRE(sceFreeTypeOlAddModule_nid_postfix(nullptr, nullptr) == 0x21);
    REQUIRE(sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix(nullptr) == 0x21);
    REQUIRE(sceFreeTypeOlGetModuleInterface_nid_postfix(nullptr, "truetype") == nullptr);

    for (const auto& entry : cases) {
        auto* module = static_cast<FT_Module_Class*>(entry.exportClass());
        REQUIRE(module != nullptr && module->module_name != nullptr);
        REQUIRE(entry.remove(library) == 0);
        REQUIRE(FT_Get_Module(native, module->module_name) == nullptr);
        entry.add(library);
        REQUIRE(FT_Get_Module(native, module->module_name) != nullptr);
        REQUIRE(sceFreeTypeOlAddModule_nid_postfix(library, module) == 5);
        REQUIRE(sceFreeTypeOlFtaAddModule_nid_postfix(library, module) == 5);
        REQUIRE(sceFreeTypeOlFtaAddModule_nid_postfix(library, nullptr) == 6);
        REQUIRE(sceFreeTypeOlGetModuleInterface_nid_postfix(library, module->module_name) ==
            FT_Get_Module_Interface(native, module->module_name));
    }

    REQUIRE(sceFreeTypeOlFtaSupportFormatBdf_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportFormatPcf_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportFormatPfr_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportFormatWinFonts_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportHinterAutoFitter_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportRendererRaster1_nid_postfix(library) == 0);
    REQUIRE(sceFreeTypeOlFtaSupportRendererSmooth_nid_postfix(library) == 0);

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
    REQUIRE(FT_Select_Charmap_nid_postfix(face, FT_ENCODING_UNICODE) == 0);
    REQUIRE(FT_Get_Char_Index_nid_postfix(face, 'A') != 0);
    sceFreeTypeOlDoneGlyphSlot_nid_postfix(nullptr);
    sceFreeTypeOlDoneGlyphSlot_nid_postfix(face->glyph);
    REQUIRE(face->glyph == nullptr);
    REQUIRE(FT_Done_Face_nid_postfix(face) == 0);

    REQUIRE(FT_Done_FreeType_nid_postfix(library) == 0);
}
