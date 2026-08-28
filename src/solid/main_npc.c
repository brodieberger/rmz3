#include "ap.h"
#include "collision.h"
#include "entity.h"
#include "game.h"
#include "global.h"
#include "solid.h"
#include "stagerun.h"
#include "story.h"
#include "text.h"
#include "zero.h"

static void MainNPC_Init(struct Solid* p);
static void MainNPC_Update(struct Solid* p);
static void MainNPC_Die(struct Solid* p);

// clang-format off
/*
  xx nn nn nn
  work[0]:
    0: ??
    1: Ciel
    2: Cerveau
    3: Hazard Colbor (until Player go to cerveru room for the first time)
    4: Search console at Sunken Library
    5: ?? (『メンテナンス・ルーム』という文字列を表示している ゼロ2の名残？)
*/
const SolidRoutine gMainNPCRoutine = {
    [ENTITY_INIT] =      MainNPC_Init,
    [ENTITY_UPDATE] =    MainNPC_Update,
    [ENTITY_DIE] =       MainNPC_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

static void initMainNPC(struct Solid* p);

static void MainNPC_Init(struct Solid* p) {
  // clang-format off
  static SolidFunc const sInitializers[] = {
    initMainNPC,
    initMainNPC,
    initMainNPC,
    initMainNPC,
    initMainNPC,
    initMainNPC,
  };
  // clang-format on
  (sInitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

static void FUN_080daee8(struct Solid* p);
static void UpdateCiel(struct Solid* p);
void UpdateCerveau(struct Solid* p);
void UpdateBlockingColbor(struct Solid* p);
static void UpdateSearchConsole(Object* p);
static void FUN_080db930(Object* p);

static void MainNPC_Update(struct Solid* p) {
  // clang-format off
  static SolidFunc const sUpdates[] = {
    (SolidFunc)FUN_080daee8,
    (SolidFunc)UpdateCiel,
    (SolidFunc)UpdateCerveau,
    (SolidFunc)UpdateBlockingColbor,
    (SolidFunc)UpdateSearchConsole,
    (SolidFunc)FUN_080db930,
  };
  // clang-format on
  (sUpdates[(p->s).work[0]])(p);
}

// --------------------------------------------

static void deleteMainNPC(struct Solid* p);

void MainNPC_Die(struct Solid* p) {
  // clang-format off
    static SolidFunc const sDeinitializers[] = {
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
  };
  // clang-format on
  (sDeinitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

static void initMainNPC(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  MainNPC_Update(p);
}

static void FUN_080daee8(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  MainNPC_Die(p);
}

static void deleteMainNPC(struct Solid* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  (p->s).flags2 &= ~ENTI_PHYSICS;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

NAKED static void UpdateCiel(struct Solid* p) { INCCODE("asm/wip/UpdateCiel.inc"); }

extern const struct Collision Collision_ARRAY_083713b0[2];

NON_MATCH_AP void UpdateCerveau(struct Solid* p) {
#if MODERN || AP
#if !AP
  struct ZeroStatus* status;  // only the vanilla grant path uses this
#endif

#if AP
  /*
    New NPC in Cerveau's room when he isnt there (he leaves after being given two story progression items)
  */
  if (ApCerveauGuideUpdate(p)) {
    return;
  }
#endif

  switch ((p->s).mode[1]) {
    case 0: {
      if ((gCurStory.s.gameflags[2] & ((1 << (FLAG_LATER4_DONE & 7)) | (1 << (FLAG_BRAIN_CONTROL & 7)))) == (1 << (FLAG_LATER4_DONE & 7))) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
        break;
      }
      (p->s).flags |= DISPLAY;
      (p->s).flags |= FLIPABLE;
      InitNonAffineMotion(&p->s);
      SET_XFLIP(p, TRUE);
      INIT_BODY(p, Collision_ARRAY_083713b0, 0, NULL);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      SetMotion(&p->s, MOTION(SM194_CERVEAU, 0));
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateEntityAnim(&p->s);
      if (!((p->body).status & BODY_STATUS_CHAT)) {
        break;
      }
      if (!gInChat) {
        break;
      }
      if (gCollisionManager.talkTo != &p->body) {
        break;
      }
      SET_XFLIP(p, FALSE);
      if (!FLAG(gCurStory.s.gameflags, FLAG_9)) {
        gCurStory.s.gameflags[1] |= (1 << (FLAG_9 & 7));
        PrintNormalMessage(0x1307);  // シミュレーションの結果が出るまで...
        FUN_08021cb4(&gStageRun.vm, gStageScriptList[STAGE_BASE][5], &p->s);
        (p->s).mode[1] = 3;
        break;
      }
      SetGameMode(&gGameState, GAMEMODE(MAINGAME, OVERWORLD, 3, 0));
      (p->s).mode[1]++;
      break;
    }
    case 2: {
      UpdateEntityAnim(&p->s);
      if (gGameState.mode[2] != 0) {
        break;
      }
      gInChat = FALSE;
      SET_XFLIP(p, TRUE);
      (p->s).mode[1] = 1;
      break;
    }
    case 3: {
      UpdateEntityAnim(&p->s);
      if ((&gTextWindow.text)->mode != 0) {
        break;
      }
#if AP
      ApMarkLocationChecked(AP_LOC_ROD);
      ApMarkLocationChecked(AP_LOC_SHIELD);
#else
      // Unlock the rod and shield
      (&pZero2->unk_b4)->status.unlockedWeapon |= (1 << WEAPON_ROD);
      (&pZero2->unk_b4)->status.unlockedWeapon |= (1 << WEAPON_SHIELD);
      status = &(gGameState.save).status;
      status->unlockedWeapon |= (1 << WEAPON_ROD);
      status->unlockedWeapon |= (1 << WEAPON_SHIELD);
#endif
      SetMotion(&p->s, MOTION(SM194_CERVEAU, 1));
      (p->s).work[2] = 8;
      (p->s).mode[1]++;
      break;
    }
    case 4: {
      UpdateEntityAnim(&p->s);
      if (--(p->s).work[2] != 0) {
        break;
      }
      SetMotion(&p->s, MOTION(SM194_CERVEAU, 2));
      (p->s).work[2] = 30;
      (p->s).mode[1]++;
      break;
    }
    case 5: {
      UpdateEntityAnim(&p->s);
      if (--(p->s).work[2] != 0) {
        break;
      }
      SetMotion(&p->s, MOTION(SM194_CERVEAU, 1));
      (p->s).work[2] = 8;
      (p->s).mode[1]++;
      break;
    }
    case 6: {
      UpdateEntityAnim(&p->s);
      if (--(p->s).work[2] != 0) {
        break;
      }
      SetMotion(&p->s, MOTION(SM194_CERVEAU, 0));
      (p->s).mode[1]++;
      break;
    }
    case 7: {
      UpdateEntityAnim(&p->s);
      if ((gStageRun.vm).active & VM_ACTIVE) {
        break;
      }
      SET_XFLIP(p, TRUE);
      (p->s).mode[1] = 1;
      break;
    }
    default: {
      break;
    }
  }
#else
  INCCODE("asm/wip/UpdateCerveau.inc");
#endif
}

INCASM("asm/solid/main_npc.inc");

const struct Collision Collision_ARRAY_08371380[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(32), PIXEL(0), PIXEL(16), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

const struct Collision Collision_ARRAY_083713b0[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(32), PIXEL(0), PIXEL(16), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

const struct Collision Collision_ARRAY_083713e0[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(80), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

// --------------------------------------------

static const struct Collision Collision_ARRAY_08371410[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(24), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

static void UpdateSearchConsole(Object* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      (p->s).flags |= FLIPABLE;
      INIT_BODY(p, Collision_ARRAY_08371410, 64, NULL);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      if (((p->body).status & BODY_STATUS_CHAT) && gInChat && (gCollisionManager.talkTo == &p->body)) {
        PlaySound(SE_ARCADIA_RINGTONE);
        SetGameMode(&gGameState, GAMEMODE(MAINGAME, OVERWORLD, 7, 0));
        (p->s).mode[1]++;
      }
      break;
    }
    case 2: {
      if (gGameState.mode[2] != 0) {
        return;
      }
      gInChat = FALSE;
      (p->s).mode[1] = 1;
      break;
    }
    default: {
      break;
    }
  }
}

static void FUN_080db930(Object* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      if (FLAG(gCurStory.s.gameflags, FLAG_LATER4_DONE) || !FLAG(gCurStory.s.gameflags, FLAG_MISSILE_DONE)) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
        break;
      }
      (p->s).flags |= FLIPABLE;
      INIT_BODY(p, Collision_ARRAY_08371410, 64, NULL);
      (p->s).coord.x += PIXEL(8);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      if (((p->body).status & BODY_STATUS_CHAT) && gInChat && (gCollisionManager.talkTo == &p->body)) {
        PrintNormalMessage(0x1333);  // メンテナンス・ルーム 使用中…
        (p->s).mode[1]++;
      }
      break;
    }
    case 2: {
      if ((&gTextWindow.text)->mode != 0) {
        return;
      }
      gInChat = FALSE;
      (p->s).mode[1] = 1;
      break;
    }
    default: {
      break;
    }
  }
}
