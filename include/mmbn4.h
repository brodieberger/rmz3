#ifndef GUARD_RMZ3_MMBN4_H
#define GUARD_RMZ3_MMBN4_H

// カードeもここかも？

#include "constants/constants.h"
#include "gba/gba.h"
#include "types.h"

// 0x02000db0, 0x02000dc0
struct Unk_02000db0 {
  u32 magic;
  u16 field1_0x4;
};
static_assert(sizeof(struct Unk_02000db0) == 8);

// SIO（シリアルI/O）制御構造体
// 0x02000d50
struct Unk_02000d50 {
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  u8 unk_04;
  u8 unk_05;
  u8 shouldAdvanceLinkState;  // 0x06, (LinkMain1 の第1引数であることから) pret/pokefirered の gShouldAdvanceLinkState に相当
  u8 unk_07;
  u8 unk_08;
  u8 unk_09;
  u16 unk_0a;
  u16 unk_0c;
  u16 unk_0e;
  u16 unk_10[6];
  u32 unk_1c;
  u32 unk_20;
  u32 unk_24;
  u32 unk_28;
  u32 unk_2c;
  u32 unk_30;
  u32 unk_34;
  u32 unk_38;
  u32 unk_3c;
  u32 unk_40;
  u32 unk_44;
  u32 linkStatus;  // 0x48, LinkMain1 の戻り値, pret/pokefirered の gLinkStatus に相当
  u32 unk_4c;
  u32 unk_50;
  u32 unk_54;
};

struct Unk_080006c8 {
  void* a;
  void* b;
  void* c;
  u8 d;
  u8 _[3];
};

extern u32 gUnkMmbn4;
extern struct Unk_02000d50 gUnk02000d50;

void SioLink_SendDisconnect(void);
void EReader_SioInitHandshake(void);
u8 EReader_SioWaitForConnect(void);
u8 EReader_SioHandshakePoll(void);
u8 EReader_SioConfirmReceipt(void);
u8 EReader_SioReadCardType(void);
void EReader_SioBeginCardRead(void);
u16 EReader_SioGetCardId(void);
void EReader_SioInitDataReceive(void);
u8 EReader_SioVerifyCardData(void);
u8 EReader_SioCheckAllPlayersConnected(void);
void EReader_SioAbortSession(void);
void FUN_08000eac(u16 recvCmd, u32 playerIdx, u32 recvCmdIndex);

#endif  // GUARD_RMZ3_MMBN4_H
