#ifndef __W2U_TERRAIN_TEXTURE_H
#define __W2U_TERRAIN_TEXTURE_H

#include "swantypes.h"

struct G3DResource;

C_DECL_BEGIN

// Battle-server terrain code only publishes the desired state.  G3D work is
// deferred to the battle viewer's VBlank callback.
void W2U_TerrainTexture_Request(u32 terrain);

// Terrain expiry changes gameplay state before the queued battle text reaches
// the viewer.  Keep the current texture until the matching message starts.
void W2U_TerrainTexture_DeferResetUntilMessage(u32 msgID);
void W2U_TerrainTexture_OnSetMessageStart(u32 msgID);

// Prepare the requested Electric/Grassy/Misty/Psychic resource when its
// logical terrain move reaches the viewer, rather than loading it in VBlank.
void W2U_TerrainTexture_OnMoveAnimationStart(u32 moveID);

// A terrain set by an ability plays no move animation: prepare it when its
// start message (msgID) reaches the viewer and fade it in straight away.
void W2U_TerrainTexture_DeferStartUntilMessage(u32 msgID);

// Battle-view lifecycle callbacks installed in overlay 168.
void W2U_TerrainTexture_FieldInit(void* fieldWork, G3DResource* fieldResource, u32 battgraMember);
void W2U_TerrainTexture_ApplyPending();
void W2U_TerrainTexture_AdvanceAnimation();
void W2U_TerrainTexture_FieldExit();

C_DECL_END

#endif
