#include "ap.h"

#undef ApCerveauGuideUpdate

#include "anim_loader.h"
#include "collision.h"
#include "constants/motion/static.h"
#include "entity.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"
#include "solid.h"
#include "story.h"
#include "text_window.h"

#if AP

/*
  New NPC in Cerveau's room when he isnt there (he leaves after being given two story progression items).
  Tells the player to go check on the maintenence room, then leaves as soon as the cutscene plays (brain control flag set true)
*/

#define AP_CERVEAU_GUIDE_IDLE 8
#define AP_CERVEAU_GUIDE_TALK 9

extern const struct Collision Collision_ARRAY_083713b0[2];

static bool32 cerveauIsAway(void) {
  if (!FLAG(gCurStory.s.gameflags, FLAG_LATER4_DONE)) {
    return FALSE;
  }
  return !FLAG(gCurStory.s.gameflags, FLAG_BRAIN_CONTROL);
}

static void becomeGuide(struct Solid* p) {
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  SET_XFLIP(p, TRUE);
  INIT_BODY(p, Collision_ARRAY_083713b0, 0, NULL);
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);

  /*
    load graphics
  */
  wStaticGraphicTilenums[SM130_PROLOGUE_RESISTANCE] = AP_CERVEAU_GUIDE_TILE;
  wStaticMotionPalIDs[SM130_PROLOGUE_RESISTANCE] = AP_CERVEAU_GUIDE_PAL;
  LOAD_STATIC_GRAPHIC(SM130_PROLOGUE_RESISTANCE);

  SetMotion(&p->s, MOTION(SM130_PROLOGUE_RESISTANCE, 0));
  (p->s).mode[1] = AP_CERVEAU_GUIDE_IDLE;
}

/*
  Returns TRUE for the AP guide character, FALSE after the cutscene played and Cerveau should be there.
*/
bool32 ApCerveauGuideUpdate(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      if (!cerveauIsAway()) {
        return FALSE;
      }
      becomeGuide(p);
      return TRUE;
    }

    case AP_CERVEAU_GUIDE_IDLE: {
      UpdateEntityAnim(&p->s);
      if (!cerveauIsAway()) {
        (p->s).mode[1] = 0;
        return TRUE;
      }
      if (!((p->body).status & BODY_STATUS_CHAT)) {
        return TRUE;
      }
      if (!gInChat) {
        return TRUE;
      }
      if (gCollisionManager.talkTo != &p->body) {
        return TRUE;
      }
      SET_XFLIP(p, FALSE);
      PrintNormalMessagePtr(gApCerveauAwayText);
      (p->s).mode[1] = AP_CERVEAU_GUIDE_TALK;
      return TRUE;
    }

    case AP_CERVEAU_GUIDE_TALK: {
      UpdateEntityAnim(&p->s);
      if ((&gTextWindow.text)->mode != 0) {
        return TRUE;
      }
      gInChat = FALSE;
      SET_XFLIP(p, TRUE);
      (p->s).mode[1] = AP_CERVEAU_GUIDE_IDLE;
      return TRUE;
    }

    default: {
      return FALSE;
    }
  }
}

bool32 (*const gApCerveauGuideUpdateFn)(struct Solid* p) = ApCerveauGuideUpdate;

#endif /* AP */
