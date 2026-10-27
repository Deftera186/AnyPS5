#pragma once

#include "SceTypes.hpp"

extern "C" {

int APS5_VABI sceNpAsmClientExtAbortRequest();
int APS5_VABI sceNpAsmClientExtCreateRequest();
int APS5_VABI sceNpAsmClientExtDeleteRequest();
int APS5_VABI sceNpAsmClientExtGetPlayingTitleNpTitleToken();
int APS5_VABI sceNpAsmClientExtInitialize();
int APS5_VABI sceNpAsmClientExtTerminate();

}
