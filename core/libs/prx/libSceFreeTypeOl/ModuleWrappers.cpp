#include "prx/libSceFreeType/include/Api.hpp"
#include "prx/libSceFreeType/include/GuestObjects.hpp"
#include "prx/libc/include/General.hpp"

#include <ft2build.h>
#include FT_MODULE_H
#include <freetype/internal/ftdrv.h>
#include <freetype/internal/ftobjs.h>

#include <cstdint>

using namespace FreeType;

extern "C" {
extern const FT_Module_Class gxv_module_class;
extern const FT_Module_Class otv_module_class;
extern const FT_Module_Class autofit_module_class;
extern const FT_Driver_ClassRec bdf_driver_class;
extern const FT_Driver_ClassRec cff_driver_class;
extern const FT_Driver_ClassRec pcf_driver_class;
extern const FT_Driver_ClassRec pfr_driver_class;
extern const FT_Module_Class psaux_module_class;
extern const FT_Module_Class pshinter_module_class;
extern const FT_Module_Class psnames_module_class;
extern const FT_Renderer_Class ft_raster1_renderer_class;
extern const FT_Module_Class sfnt_module_class;
extern const FT_Renderer_Class ft_smooth_renderer_class;
extern const FT_Driver_ClassRec t1cid_driver_class;
extern const FT_Driver_ClassRec tt_driver_class;
extern const FT_Driver_ClassRec t1_driver_class;
extern const FT_Driver_ClassRec t42_driver_class;
extern const FT_Driver_ClassRec winfnt_driver_class;
}

namespace {
template <typename T>
const FT_Module_Class* ModuleClass(const T& value) {
    return reinterpret_cast<const FT_Module_Class*>(&value);
}

int AddModule(void* library, const FT_Module_Class* module) {
    const auto host = library ? static_cast<GuestLibrary*>(library)->host : nullptr;
    if (!host) return 0x21;
    if (!module) return 6;
    const auto existing = FT_Get_Module(host, module->module_name);
    if (existing && module->module_version <= existing->clazz->module_version) return 5;
    return FT_Add_Module(host, module);
}

int SupportModule(void* library, const FT_Module_Class* module) {
    const int error = AddModule(library, module);
    return error == 5 ? 0 : error;
}

int RemoveModule(void* library, const char* name) {
    const auto host = library ? static_cast<GuestLibrary*>(library)->host : nullptr;
    if (!host) return 0x21;
    FT_Module module = FT_Get_Module(host, name);
    if (!module) return 0;
    FT_Remove_Module(host, module);
    return 0;
}
}

extern "C" {
int APS5_VABI sceFreeTypeOlFtaAddModule_nid_postfix(void* library, void* module) {
    return AddModule(library, static_cast<const FT_Module_Class*>(module));
}
APS5_EXPORT("mCIXittfvrw", sceFreeTypeOlFtaAddModule_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleAutofitter_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(autofit_module_class));
}
APS5_EXPORT("r2C1PcTDYxk", sceFreeTypeOlFtaAddModuleAutofitter_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleBdf_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(bdf_driver_class));
}
APS5_EXPORT("1gAJb1uKyGo", sceFreeTypeOlFtaAddModuleBdf_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleCff_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(cff_driver_class));
}
APS5_EXPORT("IjquEAbfizc", sceFreeTypeOlFtaAddModuleCff_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModulePcf_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(pcf_driver_class));
}
APS5_EXPORT("bAbUJvsiVdI", sceFreeTypeOlFtaAddModulePcf_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModulePfr_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(pfr_driver_class));
}
APS5_EXPORT("1GYsjUC-HLM", sceFreeTypeOlFtaAddModulePfr_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModulePsaux_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(psaux_module_class));
}
APS5_EXPORT("KLaWCpRxYWo", sceFreeTypeOlFtaAddModulePsaux_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModulePshinter_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(pshinter_module_class));
}
APS5_EXPORT("qodr9TJuFds", sceFreeTypeOlFtaAddModulePshinter_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModulePsnames_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(psnames_module_class));
}
APS5_EXPORT("Ic8JMhUFe88", sceFreeTypeOlFtaAddModulePsnames_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleRaster1_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(ft_raster1_renderer_class));
}
APS5_EXPORT("CIrV8Sq2Uic", sceFreeTypeOlFtaAddModuleRaster1_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleSfnt_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(sfnt_module_class));
}
APS5_EXPORT("eS+4GhL28gs", sceFreeTypeOlFtaAddModuleSfnt_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleSmooth_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(ft_smooth_renderer_class));
}
APS5_EXPORT("XpA3dnvjl8w", sceFreeTypeOlFtaAddModuleSmooth_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleT1cid_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(t1cid_driver_class));
}
APS5_EXPORT("oKG-LjaBzzs", sceFreeTypeOlFtaAddModuleT1cid_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleTruetype_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(tt_driver_class));
}
APS5_EXPORT("zxsyxyiLthM", sceFreeTypeOlFtaAddModuleTruetype_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleType1_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(t1_driver_class));
}
APS5_EXPORT("+v66TBg7tzA", sceFreeTypeOlFtaAddModuleType1_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleType42_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(t42_driver_class));
}
APS5_EXPORT("ZYpIYZg3Jf4", sceFreeTypeOlFtaAddModuleType42_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleWinfonts_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(winfnt_driver_class));
}
APS5_EXPORT("JSi+hWkA9pI", sceFreeTypeOlFtaAddModuleWinfonts_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleAutofitter_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(autofit_module_class));
}
APS5_EXPORT("bZYqFlUVPCY", sceFreeTypeOlFtaExportModuleAutofitter_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleBdf_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(bdf_driver_class));
}
APS5_EXPORT("ZhVdSRyrpUI", sceFreeTypeOlFtaExportModuleBdf_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleCff_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(cff_driver_class));
}
APS5_EXPORT("phi4au-2t04", sceFreeTypeOlFtaExportModuleCff_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModulePcf_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(pcf_driver_class));
}
APS5_EXPORT("-qwk1RxUuDA", sceFreeTypeOlFtaExportModulePcf_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModulePfr_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(pfr_driver_class));
}
APS5_EXPORT("mQYQAi8B0Yo", sceFreeTypeOlFtaExportModulePfr_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModulePsaux_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(psaux_module_class));
}
APS5_EXPORT("4TJ1qJGXAV8", sceFreeTypeOlFtaExportModulePsaux_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModulePshinter_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(pshinter_module_class));
}
APS5_EXPORT("IewcaRR3F8I", sceFreeTypeOlFtaExportModulePshinter_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModulePsnames_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(psnames_module_class));
}
APS5_EXPORT("vuuFugcw5ss", sceFreeTypeOlFtaExportModulePsnames_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleRaster1_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(ft_raster1_renderer_class));
}
APS5_EXPORT("xaswa+ndZS0", sceFreeTypeOlFtaExportModuleRaster1_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleSfnt_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(sfnt_module_class));
}
APS5_EXPORT("5-z1quqcDYo", sceFreeTypeOlFtaExportModuleSfnt_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleSmooth_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(ft_smooth_renderer_class));
}
APS5_EXPORT("VVfxa65sWF0", sceFreeTypeOlFtaExportModuleSmooth_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleT1cid_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(t1cid_driver_class));
}
APS5_EXPORT("aX8PI-h3+dE", sceFreeTypeOlFtaExportModuleT1cid_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleTruetype_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(tt_driver_class));
}
APS5_EXPORT("KIKL0rz6o-A", sceFreeTypeOlFtaExportModuleTruetype_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleType1_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(t1_driver_class));
}
APS5_EXPORT("QPh+yb2Y8AQ", sceFreeTypeOlFtaExportModuleType1_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleType42_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(t42_driver_class));
}
APS5_EXPORT("u36SHyuWQCA", sceFreeTypeOlFtaExportModuleType42_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleWinfonts_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(winfnt_driver_class));
}
APS5_EXPORT("ZHsmiChQLTk", sceFreeTypeOlFtaExportModuleWinfonts_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix(void* library) {
    return RemoveModule(library, "autofitter");
}
APS5_EXPORT("q2ESpjCIk7w", sceFreeTypeOlFtaRemoveModuleAutofitter_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleBdf_nid_postfix(void* library) {
    return RemoveModule(library, "bdf");
}
APS5_EXPORT("C0nVvG6+x-s", sceFreeTypeOlFtaRemoveModuleBdf_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleCff_nid_postfix(void* library) {
    return RemoveModule(library, "cff");
}
APS5_EXPORT("DIIRFBxRfMQ", sceFreeTypeOlFtaRemoveModuleCff_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModulePcf_nid_postfix(void* library) {
    return RemoveModule(library, "pcf");
}
APS5_EXPORT("E9y7-AmuziU", sceFreeTypeOlFtaRemoveModulePcf_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModulePfr_nid_postfix(void* library) {
    return RemoveModule(library, "pfr");
}
APS5_EXPORT("-whG27+m+C0", sceFreeTypeOlFtaRemoveModulePfr_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModulePsaux_nid_postfix(void* library) {
    return RemoveModule(library, "psaux");
}
APS5_EXPORT("wGGhfabJAbs", sceFreeTypeOlFtaRemoveModulePsaux_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModulePshinter_nid_postfix(void* library) {
    return RemoveModule(library, "pshinter");
}
APS5_EXPORT("KuJkc0qDvOQ", sceFreeTypeOlFtaRemoveModulePshinter_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModulePsnames_nid_postfix(void* library) {
    return RemoveModule(library, "psnames");
}
APS5_EXPORT("jqMurvieLBk", sceFreeTypeOlFtaRemoveModulePsnames_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleRaster1_nid_postfix(void* library) {
    return RemoveModule(library, "raster1");
}
APS5_EXPORT("z9YQIyuTMV4", sceFreeTypeOlFtaRemoveModuleRaster1_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleSfnt_nid_postfix(void* library) {
    return RemoveModule(library, "sfnt");
}
APS5_EXPORT("50HTRXvbW-k", sceFreeTypeOlFtaRemoveModuleSfnt_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleSmooth_nid_postfix(void* library) {
    return RemoveModule(library, "smooth");
}
APS5_EXPORT("M5dtVv0ln5Q", sceFreeTypeOlFtaRemoveModuleSmooth_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleT1cid_nid_postfix(void* library) {
    return RemoveModule(library, "t1cid");
}
APS5_EXPORT("MJVrwM6aTTk", sceFreeTypeOlFtaRemoveModuleT1cid_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleTruetype_nid_postfix(void* library) {
    return RemoveModule(library, "truetype");
}
APS5_EXPORT("EveUtaCYQgk", sceFreeTypeOlFtaRemoveModuleTruetype_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleType1_nid_postfix(void* library) {
    return RemoveModule(library, "type1");
}
APS5_EXPORT("B7Sw-iUs7e4", sceFreeTypeOlFtaRemoveModuleType1_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleType42_nid_postfix(void* library) {
    return RemoveModule(library, "type42");
}
APS5_EXPORT("RM21Fgm0ZvQ", sceFreeTypeOlFtaRemoveModuleType42_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleWinfonts_nid_postfix(void* library) {
    return RemoveModule(library, "winfonts");
}
APS5_EXPORT("OmxJF0FvwWc", sceFreeTypeOlFtaRemoveModuleWinfonts_nid_postfix);

int APS5_VABI sceFreeTypeOlAddModule_nid_postfix(void* library, void* module) {
    return AddModule(library, static_cast<const FT_Module_Class*>(module));
}
APS5_EXPORT("LonHHN98tMI", sceFreeTypeOlAddModule_nid_postfix);

int APS5_VABI sceFreeTypeOlAlloc_nid_postfix(GuestMemoryRec* memory, std::int64_t size, void** output) {
    if (output) *output = nullptr;
    if (!memory || !memory->alloc || !output || size < 0) return 6;
    if (size == 0) return 0;
    *output = memory->alloc(memory, size);
    return *output ? 0 : 64;
}
APS5_EXPORT("Uw+BZJpflxk", sceFreeTypeOlAlloc_nid_postfix);

void APS5_VABI sceFreeTypeOlFree_nid_postfix(GuestMemoryRec* memory, void** block) {
    if (!memory || !memory->free || !block || !*block) return;
    memory->free(memory, *block);
    *block = nullptr;
}
APS5_EXPORT("fHMsRluEMfI", sceFreeTypeOlFree_nid_postfix);

const void* APS5_VABI sceFreeTypeOlGetModuleInterface_nid_postfix(void* library, const char* name) {
    const auto host = library ? static_cast<GuestLibrary*>(library)->host : nullptr;
    return host && name ? FT_Get_Module_Interface(host, name) : nullptr;
}
APS5_EXPORT("5NYsP564wwY", sceFreeTypeOlGetModuleInterface_nid_postfix);


void APS5_VABI sceFreeTypeOlFtaAddModuleGxvalid_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(gxv_module_class));
}
APS5_EXPORT("L-qInx9Dldk", sceFreeTypeOlFtaAddModuleGxvalid_nid_postfix);

void APS5_VABI sceFreeTypeOlFtaAddModuleOtvalid_nid_postfix(void* library) {
    (void)AddModule(library, ModuleClass(otv_module_class));
}
APS5_EXPORT("mhK+E1i3VuE", sceFreeTypeOlFtaAddModuleOtvalid_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleGxvalid_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(gxv_module_class));
}
APS5_EXPORT("qC+tiGwcW7E", sceFreeTypeOlFtaExportModuleGxvalid_nid_postfix);

void* APS5_VABI sceFreeTypeOlFtaExportModuleOtvalid_nid_postfix() {
    return const_cast<FT_Module_Class*>(ModuleClass(otv_module_class));
}
APS5_EXPORT("rl7aW17qQb8", sceFreeTypeOlFtaExportModuleOtvalid_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleGxvalid_nid_postfix(void* library) {
    return RemoveModule(library, "gxvalid");
}
APS5_EXPORT("s3qCnsS3ATE", sceFreeTypeOlFtaRemoveModuleGxvalid_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaRemoveModuleOtvalid_nid_postfix(void* library) {
    return RemoveModule(library, "otvalid");
}
APS5_EXPORT("OutzOzZp6-w", sceFreeTypeOlFtaRemoveModuleOtvalid_nid_postfix);


int APS5_VABI sceFreeTypeOlFtaSupportFormatBdf_nid_postfix(void* library) {
    return SupportModule(library, ModuleClass(bdf_driver_class));
}
APS5_EXPORT("4to3tThESn0", sceFreeTypeOlFtaSupportFormatBdf_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaSupportFormatPcf_nid_postfix(void* library) {
    return SupportModule(library, ModuleClass(pcf_driver_class));
}
APS5_EXPORT("2D3H+1nhwqQ", sceFreeTypeOlFtaSupportFormatPcf_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaSupportFormatPfr_nid_postfix(void* library) {
    return SupportModule(library, ModuleClass(pfr_driver_class));
}
APS5_EXPORT("upeKra1FaQk", sceFreeTypeOlFtaSupportFormatPfr_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaSupportFormatWinFonts_nid_postfix(void* library) {
    return SupportModule(library, ModuleClass(winfnt_driver_class));
}
APS5_EXPORT("Yu7mmGCjSYM", sceFreeTypeOlFtaSupportFormatWinFonts_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaSupportHinterAutoFitter_nid_postfix(void* library) {
    return SupportModule(library, ModuleClass(autofit_module_class));
}
APS5_EXPORT("SDPzjFN7y4E", sceFreeTypeOlFtaSupportHinterAutoFitter_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaSupportRendererRaster1_nid_postfix(void* library) {
    return SupportModule(library, ModuleClass(ft_raster1_renderer_class));
}
APS5_EXPORT("3dTNNBoujn0", sceFreeTypeOlFtaSupportRendererRaster1_nid_postfix);

int APS5_VABI sceFreeTypeOlFtaSupportRendererSmooth_nid_postfix(void* library) {
    return SupportModule(library, ModuleClass(ft_smooth_renderer_class));
}
APS5_EXPORT("b7S96aD8dkE", sceFreeTypeOlFtaSupportRendererSmooth_nid_postfix);


void APS5_VABI sceFreeTypeOlDoneGlyphSlot_nid_postfix(GuestGlyphSlotRec* slot) {
    if (!slot) return;
    auto* owner = static_cast<GuestFace*>(slot->internal);
    if (!owner || slot != &owner->slot || !owner->host) return;
    if (owner->host->glyph) FT_Done_GlyphSlot(owner->host->glyph);
}
APS5_EXPORT("oJm1lThZ3iQ", sceFreeTypeOlDoneGlyphSlot_nid_postfix);

}
