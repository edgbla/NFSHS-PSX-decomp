/* frontend/common/femenudefs.cpp -- RECONSTRUCTED (menu-command callbacks + menu-defs ctor; C++ TU)
 *   66 fns: free MenuExtended_* command callbacks + tGlobalMenuDefs ctor/dtor (menu-defs init)
 *   + TransitionIsFinished button methods. Free fns in ns nfs4::FRONTEND::COMMON::FEMenuDefs.
 */
#include "femenudefs.h"

/* retail: this object's read-only data opens with the unreferenced "SimpleMem" tag (0x800114C8): the unused inline of the
 * SimpleMem class header leaves it behind in every object that saw the header (tools/psyq_pipe/simplemem_apply.py). */
static inline int Tournament_CurrentTrack(tTournamentManager &tm) { return tm.fCurrentTrack; }
static inline bool Dialog_FullyOpen(tDialogBase *dialog) { return (dialog->fFullyOpen ^ 1) == 0; }
static inline tDialogYesNo *Dialog_AsYesNo(tDialogMessageString *dialog) { return (tDialogYesNo *)dialog; }
static inline void Dialog_SetText(tDialogMessageString *dialog, char *text) { dialog->string = text; }
static inline bool MenuItem_IsDisabled(tMenuItem &item) { return (item.fFlags & 1) != 0; }
static inline Car_tStats *Cars_NewCarStatsList(void) { return Cars_gNewCarStatsList; }
static inline const char *SimpleMem_ClassName(void) { return "SimpleMem"; }

inline void tFEApplication::DisplayMessage(int word)
{
  tDialogMessageString *dialog = &messagePopup;
  dialog->SetString(TextSys_Word(word))->tDialogBase::Display();
}

/* ---- FEMenuDefs.obj-OWNED globals -- DEFINED here (self-contained; .data=real EXE bytes) ---- */
/* tBlankMenuItemGoToMenuNFS4Button_vtable @0x800114d8 + tBlankMenuItemNFS4LeftRightChoice_vtable @0x80011530:
   real __vtbl_ptr_type[11] defs live in game/common/vtables_tmenu.cpp; declared extern via femenudefs_externs.h. */
short        SelectListNull[2] = { 0, 0 };   /* @0x80051970: precedes the initialized SelectList*
                                             tables in retail .data, so it is emitted at its
                                             definition (initialized), not deferred */
short        SelectListOffOn[3] = { 103, 102, 0 };   /* @0x80051974 */
short        SelectListNormal[3] = { 227, 225, 0 };   /* @0x8005197c */
short        SelectListOpponentUpgrades[3] = { 271, 272, 0 };   /* @0x80051984 */
short        SelectListTrackDirection[3] = { 228, 229, 0 };   /* @0x8005198c */
short        SelectListTransmission[3] = { 276, 275, 0 };   /* @0x80051994 */
short        SelectListDisplaySpeed[5] = { 500, 498, 499, 103, 0 };   /* @0x8005199c */
short        SelectListDisplayMap[4] = { 103, 488, 489, 0 };   /* @0x800519a8 */
short        SelectListDisplayOpponentID[4] = { 103, 501, 502, 0 };   /* @0x800519b0 */
short        SelectListSplitTime[4] = { 103, 490, 491, 0 };   /* @0x800519b8 */
short        SelectListSplitDisplay[3] = { 492, 493, 0 };   /* @0x800519c0 */
short        SelectListUpgrades[4] = { 150, 151, 152, 0 };   /* @0x800519c8 */
short        SelectListControllerConfig[4] = { 539, 540, 541, 0 };   /* @0x800519d0 */
short        SelectListAudioMode[4] = { 466, 467, 468, 0 };   /* @0x800519d8 */
static tCarModels gCarActivation[6][5] = { 25, 25, 25, 25, 25, 24, 24, 24, 24, 24, 26, 26, 26, 27, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28 };   /* @0x800519e0; SYM STAT */
/* P872: native SYM 5ba0c1 is a scalar PTR tGlobalMenuDefs (4 B).
   Frontend -G0 preserves the original addressing without an array carrier. */
tGlobalMenuDefs *menuDefs;   /* @0x80051a58 base VA */


/* ---- MenuExtended_SetOnePlayer__FR12tMenuCommand  [FEMENUDEFS.CPP:145-153] ---- */

/* Decoded Phase 83: MenuExtended_SetOnePlayer__FR12tMenuCommand(tMenuCommand&) - set numPlayers=1 (76 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_SetOnePlayer(tMenuCommand &command)

{
  if (FEApp->fInputPlayer == '\x01') {
    command.type = kMenu_Command_None;
  }
  else {
    frontEnd.gameMode = '\0';
    screenMain->SwapBackground(-1);
  }
  return;
}



/* ---- MenuExtended_SetTwoPlayer__FR12tMenuCommand  [FEMENUDEFS.CPP:158-167] ---- */

/* Decoded Phase 83: MenuExtended_SetTwoPlayer__FR12tMenuCommand(tMenuCommand&) - set numPlayers=2 (split-screen) (80
   B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_SetTwoPlayer(tMenuCommand &command)

{
  if (gPadinfo.buf[4].nopad != '\0') {
    command.type = kMenu_Command_None;
  }
  else {
    frontEnd.gameMode = '\x01';
    frontEnd.oppNumber = '\0';
    screenMain->SwapBackground(-1);
  }
  return;
}



/* ---- MenuExtended_SetTestDrive__FR12tMenuCommand  [FEMENUDEFS.CPP:172-176] ---- */

/* Decoded Phase 83: MenuExtended_SetTestDrive__FR12tMenuCommand(tMenuCommand&) - set mode=TestDrive (free-roam, no
   race) (28 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetTestDrive__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetTestDrive(tMenuCommand &)

{
  frontEnd.carListType = '\0';
  frontEnd.oppNumber = '\0';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = RaceType_SingleRace;
  return;
}



/* ---- MenuExtended_SetSingleRace__FR12tMenuCommand  [FEMENUDEFS.CPP:180-184] ---- */

/* Decoded Phase 83: MenuExtended_SetSingleRace__FR12tMenuCommand(tMenuCommand&) - set raceType=SingleRace (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetSingleRace__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetSingleRace(tMenuCommand &)

{
  frontEnd.carListType = '\x01';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = RaceType_SingleRace;
  screenMain->SwapBackground(-1);
  return;
}



/* ---- MenuExtended_SetTournament__FR12tMenuCommand  [FEMENUDEFS.CPP:195-200] ---- */

/* Decoded Phase 83: MenuExtended_SetTournament__FR12tMenuCommand(tMenuCommand&) - set raceType=Tournament (72 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetTournament__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetTournament(tMenuCommand &)

{
  frontEnd.carListType = '\x01';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.tier = '\0';
  frontEnd.raceType = RaceType_Tournament;
  screenMain->SwapBackground(-1);
  return;
}



/* ---- MenuExtended_SetSpecialEvent__FR12tMenuCommand  [FEMENUDEFS.CPP:204-209] ---- */

/* Decoded Phase 83: MenuExtended_SetSpecialEvent__FR12tMenuCommand(tMenuCommand&) - set raceType=SpecialEvent (72 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetSpecialEvent__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetSpecialEvent(tMenuCommand &)

{
  frontEnd.carListType = '\x01';
  frontEnd.tier = '\x01';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = RaceType_Tournament;
  screenMain->SwapBackground(-1);
  return;
}



/* ---- MenuExtended_SetSoloRace__FR12tMenuCommand  [FEMENUDEFS.CPP:213-217] ---- */

/* Decoded Phase 83: MenuExtended_SetSoloRace__FR12tMenuCommand(tMenuCommand&) - set raceType=Solo (no opponents) (32
   B)
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name + (body or
   100%-caller-consensus) agree. Generic param names; types int/void* default - refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetSoloRace__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetSoloRace(tMenuCommand &)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  frontEnd.oppNumber = '\0';
  frontEnd.carListType = '\x01';
  return;
}



/* ---- MenuExtended_GoToTwoPlayerSingleRace__FR12tMenuCommand  [FEMENUDEFS.CPP:221-245] ---- */

/* Decoded Phase 83: MenuExtended_GoToTwoPlayerSingleRace__FR12tMenuCommand(tMenuCommand&) - enter 2P single-race flow(276 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [BUG FIX 2026-07-27, 45->34 diffs] Same DOUBLE-DESTRUCTION bug as PinkSlipsPreSave/
   MenuExtended_LoadGame: a manual `tScreen_dtor((tScreen*)&YesNoDialog,2);` at the shared exit
   was firing IN ADDITION to `YesNoDialog`'s own real `tDialogYesNoTri::~tDialogYesNoTri()`
   auto-invoked at scope exit (objdump showed `jal tScreen_dtor` then `jal ___15tDialogYesNoTri`
   back to back). Dropped the manual call -- insn count now matches the oracle EXACTLY (69==69).
   Residual (34 diffs) = a field-store addressing floor: oracle materializes `a0=s0` once (right
   after `jal TextSys_Word`) and stores the string/yesnowords/fDefault fields via `a0`
   displacement; our build keeps the SAME field values but addresses them sp-relative directly
   (never re-derives an `a0`/`s0` copy for that block) -- same value, same byte offset from the
   frame, purely a scratch-register/CSE tie-break (§3.15 family); the dead `dlgThis` local doesn't
   change it. Not source-reachable without a pin (forbidden); accept. */

/* [W57-A1 2026-08-09, 34->6] THREE levers: (1) the inline tDialogYesNoTri
   constructor owns the _vf store, while `dlgThis = &YesNoDialog` anchors the
   string / yesnowords / fDefault stores (retail addresses them off s0/a0);
   (2) `ptVar1 = menuDefs[0]` moved INSIDE the `sVar3 == 1` arm (oracle materializes %hi AFTER the
   bne, ours hoisted a `lui s0` above the Run result test); (3) the else-arm's menuDefs pointer
   made a BLOCK-LOCAL `defs` (a fresh block pseudo lands in v0 self-temp like the oracle; the
   fn-scope ptVar1 was colored into the arg reg a0 = separate-temp).

   SOURCE-ONLY PASS 2026-08-26, 5 -> 0 at 69/69: after removal of the historical
   post-cc1 text moves, the late state boundary produced the retail v1 screen
   pointer but blocked the command.nextMenu store from SetState's delay slot.
   Stage that value in a block-local `nextMenu`, and put one zero-byte identity
   boundary on `screenState` before the screen pointer plus one after the two
   address computations.  The first emits `li a1,2` before the screen %hi; the
   second preserves the retail v1 ownership, while the store remains free to
   fill the call slot.  Both asm templates are empty and emit no instructions;
   there is no post-compilation modification.  Detailed source-only gate PASS.
   Folding the car-select pointer into the final call is FAIL8 at 71/69 and
   reloads screenCarSelect[0] instead of preserving retail's v1 pointer. */

void MenuExtended_GoToTwoPlayerSingleRace(tMenuCommand &command)

{
  /* Reliable SYM names only command, YesNoDialog, and the nested dialog
     receiver. P879 removes both menuDefinitions declarations using the
     corrected scalar global. The existing inline dialog operations also
     remove the extra caller receiver without introducing new local names.
     SYM-CODEGEN-CARRIER: carSelectScreen */
  tScreenCarSelect *carSelectScreen;
  int screenState;
  tDialogYesNoTri YesNoDialog;

  if ((short)carManager.GetNumOwnedCars(0) < 1) {
    /* P879: existing inferred inline names, not newly recovered spellings.
       Separate setup/call statements preserve the native SLD 225/229 groups. */
    YesNoDialog.SetString(TextSys_Word(0x42));
    YesNoDialog.SetChoices(0x321,0x322,0);
    if (YesNoDialog.Run() == 1) {
      /* SYM-CODEGEN-CARRIER: nextMenu
         SYM-CODEGEN-CARRIER: screenState -- neither name is present in retail
         SYM; together they carry the measured source-only lifetime described
         in the receipt above. */
      tMenu *nextMenu;

      frontEnd.raceType = '\0';
      command.type = kMenu_Command_GoToMenu;
      menuDefs->iteratorDealerCar.Decrement(kPlayerBoth);
      menuDefs->iteratorDealerCar.Increment(kPlayerBoth);
      screenState = 2;
      __asm__("" : "+r" (screenState));
      carSelectScreen = screenCarSelect;
      nextMenu = (tMenu *)(tMenu*)&menuDefs->menuCarDealer;
      /* W83-A20: the A5-4 loop-note ref dial (do{}while(0) on the fenced statement)
         was added here as a substitute for the `"+r"(screenState)` launder.
         🔴 W85-S3 CORRECTION: the substitution is NOT exact and the launder above was
         never actually deleted -- both are live.  Re-measured this wave (whole-TU gate):
         removing the launder while keeping this dial = 4 diffs @69/69, the residual being
         retail's `li a1,2` issued BEFORE the nextMenu address group with the
         `sw v0,4(s1)` store moved into the jal delay slot (ours emits them the other way
         round).  Also measured, all 4 unless noted: screenState=2 hoisted to the top of
         the block 4, placed after the carSelectScreen load 4, after nextMenu 4, wrapped
         in its own do{}while(0) 4, dial moved to the SetState call 4, dial doubled on the
         store 4; plain store with no dial 6, literal `SetState(2)` 6, nextMenu inlined at
         the store 6, store hoisted above the carSelectScreen load 9, and the whole block
         reordered with screenState+carSelectScreen first 30.  The launder is therefore
         KEPT under the W85 iron rule (sched2 tie, no source form reaches it). */
      do { command.nextMenu = nextMenu; } while (0);
      carSelectScreen->SetState(screenState);
    }
  }
  else {
    MenuExtended_SetSoloRace(command);
    command.type = kMenu_Command_GoToMenu;
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuSingleTrackSelect;
  }
  return;
}



/* ---- MenuExtended_SetDuelRace__FR12tMenuCommand  [FEMENUDEFS.CPP:247-251] ---- */

/* Decoded Phase 83: MenuExtended_SetDuelRace__FR12tMenuCommand(tMenuCommand&) - set raceType=Duel (1v1) (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetDuelRace__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetDuelRace(tMenuCommand &)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  frontEnd.oppNumber = '\x01';
  screenMain->SwapBackground(-1);
  return;
}



/* ---- MenuExtended_SetFullGrid__FR12tMenuCommand  [FEMENUDEFS.CPP:255-259] ---- */

/* Decoded Phase 83: MenuExtended_SetFullGrid__FR12tMenuCommand(tMenuCommand&) - set grid size to maximum opponents(64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetFullGrid__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetFullGrid(tMenuCommand &)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  frontEnd.oppNumber = '\x02';
  screenMain->SwapBackground(-1);
  return;
}



/* ---- AskTheUserToSaveTheGame  [FEMENUDEFS.CPP:274-290] ---- */

/* Decoded Phase 86: FE-AskTheUserToSaveTheGame (120 B): show "Save game?" Yes/No prompt.
   
   [ghidra-meta] section: front.text
   
   [Locals 2026-05-08] Locals renamed via deep-body inspection. FE-MenuDefs::AskTheUserToSaveTheGame
   - 'Save game?' Yes/No prompt. is_cheater = FECheat_IsTheUserACryBabyCheater (= block save if
   cheater detected); on cheater: return 0 (= No-saving-allowed). Else: build YesNoDialog on stack(168 B); set string=TextSys_Word(0x331)='Save game?'; yesnowords[0]=0x321='YES', [1]=0x322='NO';
   fDefault=0 (= No is default). Run shows the modal dialog and returns user_choice. Destructor on
   dialog. Returns user_choice (1=Yes, 0=No). */

int AskTheUserToSaveTheGame(void)
{
  if ((FECheat_IsTheUserACryBabyCheater() ^ 1) != 0) {
    tDialogYesNo YesNoDialog;
    int answer;
    tDialogYesNo *const dialog = Dialog_AsYesNo(YesNoDialog.SetString(TextSys_Word(0x331)));
    dialog->yesnowords[0] = 0x321;
    dialog->yesnowords[1] = 0x322;
    dialog->fDefault = 0;
    answer = (short)((tDialogInteractive *)dialog)->Run();
    return answer;
  }
  return 0;
}



/* ---- MenuExtended_TransitionFromPostGameToMainMenu__FR12tMenuCommand  [FEMENUDEFS.CPP:295-297] ---- */

/* Decoded Phase 83: MenuExtended_TransitionFromPostGameToMainMenu__FR12tMenuCommand(tMenuCommand&) - return to main
   menu without saving (28 B)
   
   [ghidra-meta] section: front.text */

/* P874: native SYM 5b47bd records only command. With scalar menuDefs,
   the two original statements need no menuDefsBase carrier. SLD296 assigns
   nextMenu before SLD297 assigns type: PASS7/exact-g, all line groups exact. */
void MenuExtended_TransitionFromPostGameToMainMenu(tMenuCommand &command)

{
  command.nextMenu = &menuDefs->menuMain;
  command.type = kMenu_Command_GoToMenuOneWay;
}



/* ---- MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame__FR12tMenuCommand  [FEMENUDEFS.CPP:301-308] ---- */

/* Decoded Phase 83: MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame__FR12tMenuCommand(tMenuCommand&) -
   auto-save then return to main menu (76 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [SYM/SLD 2026-08-25] Retail records only `command`.  Calling the predicate
   directly removes the former iVar2 without code change.  Spelling nextMenu
   before type makes GCC load menuDefs before the independent type store and is
   exact PASS 19/19; the opposite source order is FAIL 5 (20/19). */

void MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame(tMenuCommand &command)

{
  if (AskTheUserToSaveTheGame() != 0) {
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuPostGameSave;
    command.type = kMenu_Command_GoToMenuOneWay;
  }
  else {
    MenuExtended_TransitionFromPostGameToMainMenu(command);
  }
  return;
}



/* ---- MenuExtended_GoToCarSelect__FR12tMenuCommand  [FEMENUDEFS.CPP:313-420] ---- */

/* Decoded Phase 83: MenuExtended_GoToCarSelect__FR12tMenuCommand(tMenuCommand&) - transition to car-select screen;
   sets up garage car list (916 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToCarSelect(tMenuCommand &command)

{
  /* SYM-CODEGEN-CARRIER: dialog
     SYM-CODEGEN-CARRIER: nextMenu
     SYM-CODEGEN-CARRIER: screen
     SYM-CODEGEN-CARRIER: state
     Retail SYM exposes only `trackInfo` plus an inlined tFEApplication
     receiver.  These four aliases are therefore not claimed as recovered
     source locals; they preserve optimizer decisions proven by the exact
     oracle.  Removing `dialog` and spelling the popup chain directly is 42
     diffs and two instructions short.  Replacing the three car-select merge
     carriers with direct branch statements is 24 diffs and two instructions
     long; retaining only screen/state or nextMenu/state is 15 diffs, and
     retaining nextMenu/screen is nine.  All four together remain PASS
     (229/229), so their unknowable source names are explicitly receipted. */
  tDialogMessageString *dialog = &FEApp->messagePopup;
  tMenu *nextMenu;
  tScreenCarSelect *screen;
  uint state;
  tTrackInformation trackInfo;
  
  trackManager.GetTrack((ushort)(byte)frontEnd.track[(byte)frontEnd.pinkSlipsTrackIndex],
             trackInfo);
  if (trackInfo.fAvailable == '\0') {
    dialog->string = TextSys_Word(0xeb);
    ((tDialogBase *)dialog)->Display();
    return;
  }
  if (frontEnd.gameMode == '\x01') {
    command.type = kMenu_Command_GoToMenuTwoPlayer;
    if (frontEnd.raceType != RaceType_PinkSlips) {
      if (frontEnd.carListType == '\0') {
        command.nextMenu = (tMenu *)&menuDefs->menuPlayerOneCarSelect;
      }
      else {
        command.nextMenu = (tMenu *)&menuDefs->menuPlayerOneGarage;
      }
    }
    else {
      command.nextMenu = (tMenu *)&menuDefs->menuPlayerOnePinkSlipCarSelect;
    }
  }
  else {
    if (frontEnd.oppNumber == '\x01') {
      command.type = kMenu_Command_GoToMenu;
      if (frontEnd.raceType == RaceType_HotPursuit) {
        command.nextMenu = (tMenu*)&menuDefs->menuHPDuelCarSelect;
      }
      else {
        command.nextMenu = (tMenu*)&menuDefs->menuDuelCarSelect;
      }
      ((tScreenCarSelect *)screenCarSelectDuel)->SetState(7);
    }
    else {
      command.type = kMenu_Command_GoToMenu;
      if (frontEnd.carListType == '\0') {
        nextMenu = (tMenu*)&menuDefs->menuSingleCarSelect;
        screen = screenCarSelect;
        state = 0;
      }
      else {
        nextMenu = (tMenu*)&menuDefs->menuCarGarage;
        screen = screenCarSelect;
        state = 1;
      }
      command.nextMenu = nextMenu;
      screen->SetState(state);
    }
  }
  switch (frontEnd.raceType) {
  case '\x01':
    if ((frontEnd.oppNumber == '\0') || (frontEnd.gameMode == '\x01')) {
      (menuDefs->iteratorCar1).fCarListFilter = 9;
    }
    else {
      (menuDefs->iteratorCar1).fCarListFilter = 1;
    }
    break;
  case '\x06':
    (menuDefs->iteratorPinkSlipsCar).fCarListFilter = 0x20;
    break;
  default:
    if (frontEnd.carListType == '\0') {
      (menuDefs->iteratorCar1).fCarListFilter = 1;
    }
    else if (frontEnd.raceType == RaceType_Tournament) {
      (menuDefs->iteratorGarageCar).fCarListFilter = 0x40;
    }
    else {
      (menuDefs->iteratorGarageCar).fCarListFilter = 2;
    }
    break;
  }
  if (frontEnd.carListType == '\0') {
    menuDefs->iteratorCar1.Decrement(kPlayerOne);
    menuDefs->iteratorCar1.Increment(kPlayerOne);
    menuDefs->iteratorCar1.Decrement(kPlayerTwo);
    menuDefs->iteratorCar1.Increment(kPlayerTwo);
  }
  else {
    if ((int)((uint)carManager.GetNumOwnedCars(0) << 0x10) < 1) {
      if (frontEnd.raceType == RaceType_HotPursuit) {
        if (frontEnd.oppNumber == '\x01') goto MX_GoToCar_oppFilterSetup;
        goto MX_GoToCar_garageIter;
      }
    }
    else {
MX_GoToCar_garageIter:
      menuDefs->iteratorGarageCar.Decrement(kPlayerOne);
      menuDefs->iteratorGarageCar.Increment(kPlayerOne);
      if (frontEnd.gameMode == '\x01') {
        menuDefs->iteratorGarageCar.Decrement(kPlayerTwo);
        menuDefs->iteratorGarageCar.Increment(kPlayerTwo);
      }
    }
  }
  if (frontEnd.oppNumber != '\x01') {
    return;
  }
MX_GoToCar_oppFilterSetup:
  if (frontEnd.raceType != RaceType_Tournament) {
    menuDefs->iteratorOpponentCar.Decrement(kPlayerBoth);
    menuDefs->iteratorOpponentCar.Increment(kPlayerBoth);
    (menuDefs->iteratorOpponentCar).fCarListFilter = 1;
  }
  return;
}



/* ---- MenuExtended_GoToDealer__FR12tMenuCommand  [FEMENUDEFS.CPP:423-428] ---- */

/* Decoded Phase 83: MenuExtended_GoToDealer__FR12tMenuCommand(tMenuCommand&) - transition to buy-car dealer screen(104 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [NEAR-MISS 2026-07-06/07, 10 diffs, WALL] `command->type=1` (a v1-const) and
   `command->nextMenu=&ptVar1->menuCarDealer` (a v0-computed ptr) swap which of {v0,v1} each
   lands in vs the oracle (oracle: const->v1, ptr->v0; ours: const->v0, ptr->v1); count matches
   (26 insns both sides), so it's pure register-coloring, not structural. IDENTICAL shape/residual
   on sibling GoToSeller. Tried and REJECTED (all revert to the 10-diff form): swap the two
   command-> statement order; swap ptVar1/dlgThis declaration+assignment order (regresses to 12);
   materialize the pointer into a fresh named local before the stores (no change); compute dlgThis
   last, right before SetState (regresses to 11, drops an insn); inline screenCarSelect[0] at the
   SetState call site instead of caching dlgThis (regresses to 11); named kMenu_Command_GoToMenu
   enum vs literal 1 (no change, confirmed codegen-neutral). PERMUTER (2 re-seeded basins, ~220
   iterations total, decomp-permuter via tools/run_permuter.py) plateaus at the SAME 10-diff shape
   (internal score 30) from every mutation path tried -- multi-basin re-seed did not find a
   downhill path below it either. Conclusion: GENUINE gcc scratch-register tie-break floor (same
   family as the documented §3.15 v0-vs-scratch tie-break in the methodology doc) -- accept, do
   NOT pin (`register T x asm("$N")` forbidden). Compare GoToGarage (sibling shape, SAME v0/v1-
   swap family) which WAS fixable because it had a genuine double pointer-derivation to collapse;
   this fn has no such redundancy to remove. */

/* [W57-A1 2026-08-09, 10->8] The v0/v1 const-vs-pointer swap declared a "genuine gcc scratch tie
   -> accept" above is NOT a floor -- it is a local-alloc QTY PRIORITY tie and the dial is the
   constant's LIVE RANGE.  QTY_CMP_PRI = floor_log2(refs)*refs*size/(death-birth): with `1`
   materialized at its store its range is ~2 insns -> priority 10000 -> it wins the numeric scan
   and takes v0; the menuDefs pointer (range ~4) gets v1.  Naming the constant and holding it from
   the top of the fn behind a 0-insn opacity fence (a bare `cmdType = 1;` is folded straight back
   into the store by cse and changes nothing -- measured) lengthens its range, drops its priority
   below the pointer's, and the whole {v0,v1} pair flips to the oracle's assignment.  The remaining
   four independent setup operations are restored to retail order by the scoped build recipe.
   [2026-08-25] Re-gating disproved the stale MATCH claim: that form was eight
   diffs.  A second named call-state value and ONE combined two-output opacity
   fence preserve both allocation decisions together and reduce the residual
   to two (26/26 instructions); only `li v1,1` is scheduled early. */

/* P872 supersedes the historical allocation recipes above: native SYM
   5b4c92 records only command (REGPARM a2), no locals. Restoring scalar
   menuDefs and the five retail statements removes all five source carriers
   and both absorption inflators, with PASS26/exact-g and SLD423-428 groups.
   P872 needed a scalar-equivalent screenCarSelect load because its extern
   still used an array view. P873 corrects that complete declaration graph
   to native SYM 64b0d0 PTR tScreenCarSelect, permitting the ordinary receiver.
   With the old array extern, [0] gave FAIL11 and staged scalar code FAIL14.
   No helper, new local, asm, volatile, or postcompile rewrite is involved. */
static void MenuExtended_GoToDealer(tMenuCommand &command)

{
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = &menuDefs->menuCarDealer;
  screenCarSelect->SetState(2);
  menuDefs->iteratorDealerCar.Decrement(kPlayerBoth);
  menuDefs->iteratorDealerCar.Increment(kPlayerBoth);
}



/* ---- MenuExtended_GoToSeller__FR12tMenuCommand  [FEMENUDEFS.CPP:432-437] ---- */

/* Decoded Phase 83: MenuExtended_GoToSeller__FR12tMenuCommand(tMenuCommand&) - transition to sell-car screen (104 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [NEAR-MISS 2026-07-06/07, 10 diffs, WALL] IDENTICAL residual/shape to sibling GoToDealer (same
   v0/v1 const-vs-pointer coloring swap on the command->type / command->nextMenu pair; count
   matches, 26 insns both sides). See GoToDealer's near-miss note above for the full list of
   rejected levers (statement/decl reorders, fresh-local materialization, inline-call-arg,
   named-enum-vs-literal) and the 2-basin permuter run (~220 iterations, plateaus at the same
   shape, internal score 30). Same conclusion: genuine gcc scratch-register tie-break floor,
   accept, do not pin. */

/* [W57-A1 2026-08-09, 10->8; corrected 2026-08-25] Same allocation family as
   GoToDealer.  The old PASS receipt was stale; the combined state/cmdType
   fence below reduces the authoritative residual to two at 26/26 instructions. */

/* P872: the same scalar-source repair as GoToDealer gives PASS26/exact-g,
   zero locals/inflators, and the native SLD432-437 statement groups.
   P873 also replaces its scalar-punning view with the native declaration. */
static void MenuExtended_GoToSeller(tMenuCommand &command)

{
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = &menuDefs->menuCarSeller;
  screenCarSelect->SetState(3);
  menuDefs->iteratorSellerCar.Decrement(kPlayerBoth);
  menuDefs->iteratorSellerCar.Increment(kPlayerBoth);
}



/* ---- MenuExtended_GoToUpgrades__FR12tMenuCommand  [FEMENUDEFS.CPP:441-444] ---- */

/* Decoded Phase 83: MenuExtended_GoToUpgrades__FR12tMenuCommand(tMenuCommand&) - transition to upgrades-purchase
   screen (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* P874: scalar menuDefs/screenCarSelect make the old FAIL7 array-view receipt
   obsolete. Native SYM records only command, so retain the three statements
   and no menuDefsBase alias. PASS16/exact-g; every SLD441-444 group matches.
   GoToShowroom and GoToDealerShowroom use the same source shape below. */
static void MenuExtended_GoToUpgrades(tMenuCommand &command)

{
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = &menuDefs->menuCarUpgrades;
  screenCarSelect->SetState(4);
}



/* ---- GenericMenuSaveGame  [FEMENUDEFS.CPP:448-478] ---- */

/* Decoded Phase 86: FE-GenericMenuSaveGame (284 B): execute generic save-game flow from
   menu.
   
   [ghidra-meta] section: front.text */

/* [W57-A1 2026-08-09, 24->PASS] The stale "%hi(FEApp) reload tie-break, not source-reachable"
   verdict above is FALSIFIED.  Two levers: (1) `noInput = &FEApp->NoInputMemCardDialog` ANCHOR
   for the string store while the Display arg stays a FRESH `&FEApp->NoInputMemCardDialog` read
   (oracle: `addiu s0,s0,720` held + a separate `lw a0,0(s1); addiu a0,a0,720` for the call);
   (2) EXIT-IN-THE-MIDDLE loop `while(1){ app = FEApp; if((app->...fFullyOpen ^ 1)==0) break;
   app->Redraw(); }` + the post-loop `Redraw(app)` REUSING the loop's last-loaded app -- that kills
   gcc's duplicate_loop_exit_test rotation (ours had the guard AND a bottom re-test = 6 extra
   insns) and reproduces the oracle's a0-reuse after the loop. */

/* [SYM 2026-08-16] retail `Def class EXT type FCN BOOL` @0x8002c9a0 -> bool, not void*.
   The result temp only stays a plain move (`addu s0,v0,zero`, not a `sltu` bool
   normalisation) because SaveGame is ALSO BOOL in the SYM (@0x80034988) -- the
   femenudefs_externs.h decl was corrected in the same pass. */
bool GenericMenuSaveGame(int showdialog)

{
  bool successful;
  bool uninitafter;   /* SYM: REG BOOL uninitafter */

  /* SYM-CODEGEN-CARRIER: app -- the exit-in-the-middle loop must reuse its
     last FEApp value for the post-loop Redraw; direct global spelling rotates
     the exit test and adds a bottom re-test. */
  tFEApplication *app;

  /* SYM restoration 2026-08-26, PASS 71/71: reliable SYM names the SaveGame
     result `successful` in s0 and the temporary initialization flag
     `uninitafter` in s2.  The old source had those roles reversed, carried a
     decompiler `ret`, and left the real SYM local unused.  The two SetMessage
     calls restore the nested tScreenMemcard receivers, and SetString restores
     the nested tDialogMessageString receiver. */
  /* SYM-INLINE-THIS: SetMessage */
  screenMemcard->SetMessage(0x27e);
  FEApp->Redraw();
  uninitafter = false;
  if ((MEMCARD_INITIALIZED == 0) || (showdialog != 0)) {
    /* SYM-CODEGEN-CARRIER: noInput -- retail forms and holds this receiver in
       s0 across TextSys_Word while Display uses a fresh FEApp dereference. */
    tDialogNoInputMessage *const noInput = &FEApp->NoInputMemCardDialog;

    /* SYM-INLINE-THIS: SetString */
    noInput->SetString(TextSys_Word(0x282));
    ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Display();
    while (1) {
      app = FEApp;
      if (Dialog_FullyOpen((tDialogBase *)&app->NoInputMemCardDialog)) break;
      app->Redraw();
    }
    app->Redraw();
    if (MEMCARD_INITIALIZED == 0) {
      uninitafter = true;
      Init_Memcard(true,0);
    }
  }
  successful = SaveGame(0);
  /* SYM-INLINE-THIS: SetMessage */
  screenMemcard->SetMessage(-1);
  if (uninitafter) {
    DeInit_Memcard();
  }
  ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Hide();
  return successful;
}



/* ---- PinkSlipsPreSave  [FEMENUDEFS.CPP:484-504] ---- */

/* Decoded Phase 86: FE-PinkSlipsPreSave (200 B): pre-save hook for Pink Slips mode.
   
   [ghidra-meta] section: front.text */

/* [SYM 2026-08-16] retail `Def class EXT type FCN BOOL` @0x8002cabc;
   the SYM also names the result local `REG BOOL ret`. */
bool PinkSlipsPreSave(void)

{
  /* SYM-CODEGEN-CARRIER: dlgThis -- SYM records the inlined derived-constructor
     `this` in $s0, not a caller local.  The restored inline constructor owns
     the vptr store, but direct-object spelling for the later fields is still
     count-exact FAIL 8 (50/50), with all four stores using $sp instead of $s0.
     Carrying that optimized receiver lifetime remains exact PASS 50/50. */
  tDialogYesNoTri *dlgThis;

  /* Keep the default result outside the dialog's lifetime but assign it before
     entering the nested scope. GCC then fills the cheater branch delay with
     `li s1,1`; the automatic destructor handles both exits. */
  if ((FECheat_IsTheUserACryBabyCheater() ^ 1) != 0) {
    bool ret;
    int answer;

    ret = true;
    {
      tDialogYesNoTri YesNoDialog;

      dlgThis = &YesNoDialog;
      dlgThis->string =
           TextSys_Word(0x273);
      dlgThis->yesnowords[0] = 0x321;
      dlgThis->yesnowords[1] = 0x322;
      dlgThis->fDefault = 0;
      answer = ((tDialogInteractive *)dlgThis)->Run();
      if (answer == 1) {
        ret = GenericMenuSaveGame(1);
      }
      else if (answer == -1) {
        return false;
      }
    }
    return ret;
  }
  return true;
}



/* ---- MenuExtended_GoToBestOfOne__FR12tMenuCommand  [FEMENUDEFS.CPP:508-519] ---- */

/* Decoded Phase 83: MenuExtended_GoToBestOfOne__FR12tMenuCommand(tMenuCommand&) - set tournament length to best-of-1
   (92 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* SYM/SLD family receipt (One/Three/Five): retail records only `command`.
   Calling PinkSlipsPreSave directly removes pvVar2, while spelling nextMenu
   before type lets GCC load menuDefs before the independent command store.
   This local-free shape is exact PASS 23/23 in all three clones. */

void MenuExtended_GoToBestOfOne(tMenuCommand &command)

{
  if (PinkSlipsPreSave()) {
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuSingleTrackSelect;
    command.type = kMenu_Command_GoToMenu;
  }
  else {
    command.type = kMenu_Command_None;
  }
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.pinkSlipsNumTracks = '\x01';
  return;
}



/* ---- MenuExtended_GoToBestOfThree__FR12tMenuCommand  [FEMENUDEFS.CPP:523-533] ---- */

/* Decoded Phase 83: MenuExtended_GoToBestOfThree__FR12tMenuCommand(tMenuCommand&) - set tournament length to
   best-of-3 (92 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToBestOfThree(tMenuCommand &command)

{
  if (PinkSlipsPreSave()) {
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuPinkSlipsBestOfThree;
    command.type = kMenu_Command_GoToMenu;
  }
  else {
    command.type = kMenu_Command_None;
  }
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.pinkSlipsNumTracks = '\x03';
  return;
}



/* ---- MenuExtended_GoToBestOfFive__FR12tMenuCommand  [FEMENUDEFS.CPP:537-547] ---- */

/* Decoded Phase 83: MenuExtended_GoToBestOfFive__FR12tMenuCommand(tMenuCommand&) - set tournament length to best-of-5
   (92 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToBestOfFive(tMenuCommand &command)

{
  if (PinkSlipsPreSave()) {
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuPinkSlipsBestOfFive;
    command.type = kMenu_Command_GoToMenu;
  }
  else {
    command.type = kMenu_Command_None;
  }
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.pinkSlipsNumTracks = '\x05';
  return;
}



/* ---- MenuExtended_GoToRace__FR12tMenuCommand  [FEMENUDEFS.CPP:551-607] ---- */

/* Decoded Phase 83: MenuExtended_GoToRace__FR12tMenuCommand(tMenuCommand&) - commit settings and transition into race(calls Front_BuildStream) (348 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToRace(tMenuCommand &command)

{
  tDialogMessageString *popUp;
  tCarInfo carInfo;

  /* [W57-A1 rewrite] The oracle materializes the word id STRAIGHT INTO $a0 in each guard's
     branch delay slot (`li a0,170/241/242/243`) and cross-jump-merges four IDENTICAL
     `string = TextSys_Word(K); Display(popUp); command.type = 0; return;` tails -- so retail
     duplicated that tail per branch instead of funnelling one `wordnum` local (which forces a
     callee-saved reg because the pseudo crosses the other guards' calls: ours was 6 s-regs /
     frame 256 vs the oracle's 4 / 248).  Plus the 08D messagePopup ANCHOR: `popUp = &FEApp->
     messagePopup` materialized EARLY (the oracle puts `addiu s1,v1,44` in the first guard's
     delay slot) and reused for both the store and the Display arg. */
  /* [SYM restoration 2026-08-26, PASS 87/87] Reliable SYM names only
     command/popUp/carInfo in the caller.  MessagePopup restores the initial
     tFEApplication receiver and the four SetString calls restore its four
     nested dialog receivers.  Direct call-result tests eliminate uVar2;
     dlgThis, ptVar1, pcVar3, and wordnum were decompiler residue.  Optimized
     SYM does not preserve the private MessagePopup identifier. */
  command.type = kMenu_Command_StartRace;
  /* SYM-INLINE-THIS: MessagePopup */
  popUp = FEApp->MessagePopup();
  if (((frontEnd.carListType == '\x01') &&
      ((int)((uint)carManager.GetNumOwnedCars(0) << 0x10) <= 0)) &&
     ((frontEnd.raceType != RaceType_HotPursuit) && (frontEnd.raceType != RaceType_PinkSlips))) {
    /* SYM-INLINE-THIS: SetString */
    popUp->SetString(TextSys_Word(0xaa));
    ((tDialogBase *)popUp)->Display();
    command.type = kMenu_Command_None;
    return;
  }
  if ((frontEnd.raceType == RaceType_Tournament) &&
     ((int)((uint)carManager.GetNumTourneyCars(0) << 0x10) < 1)) {
    /* SYM-INLINE-THIS: SetString */
    popUp->SetString(TextSys_Word(0xf1));
    ((tDialogBase *)popUp)->Display();
    command.type = kMenu_Command_None;
    return;
  }
  if ((frontEnd.raceType == RaceType_HotPursuit) &&
     (carManager.GetStockCar((ushort)(byte)frontEnd.playerCar[0],carInfo),
      carInfo.fPursuitAvailable == '\x00')) {
    /* SYM-INLINE-THIS: SetString */
    popUp->SetString(TextSys_Word(0xf2));
    ((tDialogBase *)popUp)->Display();
    command.type = kMenu_Command_None;
    return;
  }
  if (frontEnd.carListType != '\x00') {
    return;
  }
  carManager.GetStockCar((ushort)(byte)frontEnd.playerCar[0],carInfo);
  if (carInfo.fAvailable != '\x00') {
    return;
  }
  /* SYM-INLINE-THIS: SetString */
  popUp->SetString(TextSys_Word(0xf3));
  ((tDialogBase *)popUp)->Display();
  command.type = kMenu_Command_None;
  return;
}



/* ---- MenuExtended_GoTo2PlayerRace__FR12tMenuCommand  [FEMENUDEFS.CPP:610-655] ---- */

/* Decoded Phase 83: MenuExtended_GoTo2PlayerRace__FR12tMenuCommand(tMenuCommand&) - enter 2-player split-screen race
   setup flow (332 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoTo2PlayerRace(tMenuCommand &command)

{
  tDialogMessageString *popUp;
  tCarInfo carInfo;

  /* [W57-A1 rewrite] Same shape as the twin GoToRace: the oracle drops the `wordnum` funnel
     (which needed 2 extra callee-saved regs -- ours 6 s-regs/frame 256 vs 4/248) and instead
     materializes `li a0,K` in each guard's delay slot, cross-jump-merging four identical
     `TextSys_Word/Display/type=0` tails; + the 08D messagePopup anchor materialized early
     (oracle `addiu s2,v0,44` in the raceType==6 guard's delay slot). */
  /* [SYM restoration 2026-08-26, PASS 83/83] Reliable caller locals are only
     command/popUp/carInfo.  MessagePopup, three SetString calls, and two
     CurrentPlayer reads account for every nested receiver; direct call-result
     testing removes uVar2 and the remaining four decompiler identities.  The
     two inferred tFEApplication helper names are descriptive, not token-exact. */
  command.type = kMenu_Command_Start2PlayerRace;
  /* SYM-INLINE-THIS: MessagePopup */
  popUp = FEApp->MessagePopup();
  if (frontEnd.raceType == RaceType_PinkSlips) {
    return;
  }
  if (((frontEnd.carListType == '\x01') &&
      ((int)((uint)carManager.GetNumOwnedCars(0) << 0x10) <= 0)) &&
     (frontEnd.raceType != RaceType_HotPursuit)) {
    /* SYM-INLINE-THIS: SetString */
    popUp->SetString(TextSys_Word(0xaa));
    ((tDialogBase *)popUp)->Display();
    command.type = kMenu_Command_None;
    return;
  }
  /* SYM-INLINE-THIS: CurrentPlayer */
  if ((frontEnd.carListType == '\x00') &&
     (carManager.GetStockCar(
          (ushort)(byte)frontEnd.playerCar[(byte)FEApp->CurrentPlayer()],carInfo),
      carInfo.fAvailable == '\x00')) {
    /* SYM-INLINE-THIS: SetString */
    popUp->SetString(TextSys_Word(0xf3));
    ((tDialogBase *)popUp)->Display();
    command.type = kMenu_Command_None;
    return;
  }
  if (frontEnd.raceType != RaceType_HotPursuit) {
    return;
  }
  /* SYM-INLINE-THIS: CurrentPlayer */
  carManager.GetStockCar(
      (ushort)(byte)frontEnd.playerCar[(byte)FEApp->CurrentPlayer()],carInfo);
  if (carInfo.fPursuitAvailable != '\x00') {
    return;
  }
  /* SYM-INLINE-THIS: SetString */
  popUp->SetString(TextSys_Word(0xf2));
  ((tDialogBase *)popUp)->Display();
  command.type = kMenu_Command_None;
  return;
}



/* ---- MenuExtended_GoToTournTrackInfo__FR12tMenuCommand  [FEMENUDEFS.CPP:658-693] ---- */

/* Decoded Phase 83: MenuExtended_GoToTournTrackInfo__FR12tMenuCommand(tMenuCommand&) - transition to tournament-round
   track info screen (360 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* MATCH/SYM (2026-08-26): exact PASS 90/90.  Reliable records identify
   command in s3, tourn in s2, amount in v1, stack popUp, and the receivers
   inlined from DisplayMessage/SetString.  Restoring those member calls removes
   ptVar1, this_00, pcVar5, pp, and sVar4; direct expressions remove ptVar3,
   iVar6, and the duplicate iVar7 amount carrier.  The four explicitly marked
   source-only webs retain the exact allocation/schedule with measured proof. */
/* P878: the corrected scalar menuDefs declaration makes the ordinary final
   command stores exact; no additional menus alias is needed. Other marked
   webs, fences and nested inline-local ownership remain review work. */
/* P879: amount belongs to the nested post-sound debit, not the initial guard.
   The success-first Run arm restores its native REG3/collapsed-PC placement.
   One native inline-body scope and its original helper spelling remain open. */

void MenuExtended_GoToTournTrackInfo(tMenuCommand &command)

{
  tTourneyInfo *tourn;
  /* SYM-CODEGEN-CARRIER: selectedTourney -- folding into the SYM `tourn`
     web is count-exact FAIL 6; fencing `tourn` directly is FAIL 22. */
  tTourneyInfo *selectedTourney;
  /* SYM-CODEGEN-CARRIER: manager -- direct global access is count-exact FAIL 18. */
  tTournamentManager *manager;
  /* SYM-CODEGEN-CARRIER: frontEndBase -- initializing only the use carrier
     directly from frontEnd is count-exact FAIL 18. */
  tfrontEnd *const frontEndBase = &frontEnd;
  /* SYM-CODEGEN-CARRIER: frontEndState -- folding this copy into frontEndBase
     is count-exact FAIL 2, moving one address completion. */
  tfrontEnd *frontEndState;

  manager = &tournamentManager;
  frontEndState = frontEndBase;
  __asm__("" : : "r"(manager), "r"(manager), "r"(manager), "r"(manager),
          "r"(manager), "r"(manager));
  frontEndState->tier = '\0';
  tourn = &manager->fDefinition->fTournaments[
      (uint)manager->fDefinition->fTiers[0].fTournOffset +
      (uint)(byte)frontEndState->tournament];
  if (0 < tourn->fEntranceFee) {
    selectedTourney = tourn;

    __asm__("" : "+r" (selectedTourney));
    if (manager->fMoney < tourn->fEntranceFee) {
      /* SYM-INLINE-THIS: DisplayMessage */
      FEApp->DisplayMessage(0xf6);
      return;
    }
    {
      tDialogYesNo popUp;

      /* SYM-INLINE-THIS: SetString */
      popUp.SetString(TextSys_Word(0xf7));
      popUp.SetChoices(0x322,0x321,0);
      if (popUp.Run() != 0) {
        AudioCmn_PlayFESFX(0x1a);
        {
          long amount = selectedTourney->fEntranceFee;
          manager->fMoney -= amount;
        }
      } else {
        return;
      }
    }
  }
  tournamentManager.StartNewTournament(0,frontEnd.tournament);
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = (tMenu *)&menuDefs->menuTrackInfo;
  return;
}



/* ---- MenuExtended_GoToSpecialEventTrackInfo__FR12tMenuCommand  [FEMENUDEFS.CPP:696-731] ---- */

/* Decoded Phase 83: MenuExtended_GoToSpecialEventTrackInfo__FR12tMenuCommand(tMenuCommand&) - transition to
   special-event track info screen (364 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* MATCH/SYM (2026-08-26): exact PASS 91/91.  Reliable records identify
   command in s3, tourn in s2, amount in v1, stack popUp, and the receivers
   inlined from DisplayMessage/SetString.  Restored member calls and direct
   expressions remove eight decompiler identities; the three marked source-only
   webs retain retail allocation/scheduling with measured proof. */
/* P878: ordinary final command stores now match with the corrected scalar
   menuDefs interface. The former menus carrier and its obsolete failure
   receipt are removed; other source-shape/inline ownership debt remains. */
/* P879: the nested amount and success-first Run arm recover the native LONG
   REG3 and collapsed cancellation-PC scope. The lost inline-body shell/name
   and other source-only carriers are still explicit restoration work. */

void MenuExtended_GoToSpecialEventTrackInfo(tMenuCommand &command)

{
  tTourneyInfo *tourn;
  /* SYM-CODEGEN-CARRIER: selectedTourney -- folding into the SYM `tourn`
     web is count-exact FAIL 6. */
  tTourneyInfo *selectedTourney;
  /* SYM-CODEGEN-CARRIER: manager -- direct global access is count-exact FAIL 18. */
  tTournamentManager *manager;
  /* SYM-CODEGEN-CARRIER: frontEndState -- direct frontEnd fields are
     count-exact FAIL 4, moving the address pair. */
  tfrontEnd *frontEndState;

  frontEndState = &frontEnd;
  manager = &tournamentManager;
  __asm__("" : : "r"(frontEndState), "r"(manager), "r"(manager), "r"(manager),
          "r"(manager), "r"(manager), "r"(manager));
  frontEndState->tier = '\x01';
  tourn = &manager->fDefinition->fTournaments[
      (uint)manager->fDefinition->fTiers[1].fTournOffset +
      (uint)(byte)frontEndState->specialevent];
  if (0 < tourn->fEntranceFee) {
    selectedTourney = tourn;
    __asm__("" : "+r" (selectedTourney));
    if (manager->fMoney < tourn->fEntranceFee) {
      /* SYM-INLINE-THIS: DisplayMessage */
      FEApp->DisplayMessage(0xf6);
      return;
    }
    {
      tDialogYesNo popUp;

      /* SYM-INLINE-THIS: SetString */
      popUp.SetString(TextSys_Word(0xf7));
      popUp.SetChoices(0x321,0x322,0);
      if (popUp.Run() != 0) {
        AudioCmn_PlayFESFX(0x1a);
        {
          long amount = selectedTourney->fEntranceFee;
          manager->fMoney -= amount;
        }
      } else {
        return;
      }
    }
  }
  tournamentManager.StartNewTournament(1,frontEnd.specialevent);
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = (tMenu *)&menuDefs->menuTrackInfo;
  return;
}



/* ---- MenuExtended_EnterUserName__FR12tMenuCommand  [FEMENUDEFS.CPP:734-739] ---- */

/* Prompt initial-profile user-name entry (100 B).

   [SYM restoration 2026-08-26, PASS 25/25] Retail records only caller parameter
   `command`.  Its two nested line-2 scopes are exact inline receipts:
   tUserNameMenuItem `this` in a1 with `data` in v1, then tScreenUserName `this`
   in v0 with `m` in a2.  The reconstructed member operations reproduce those
   scopes and the complete retail instruction stream.  Their private inline
   identifiers are absent from the optimized SYM, so the descriptive names in
   nfs4_types.h are explicitly inferred rather than claimed as recovered text.

   P879 supersedes the former player/defs workaround: direct arguments and
   the corrected scalar menuDefs interface preserve both byte loads and all 25
   instructions without either caller local or the volatile read. Native
   command/inline-this/data/m records and statement grouping are retained;
   the private inline identifiers remain inferred, not recovered spellings. */

void MenuExtended_EnterUserName(tMenuCommand &command)

{
  /* SYM-INLINE-THIS: SetUserNameData
     SYM-INLINE-LOCAL: data = SetUserNameData */
  menuDefs->menuItemUserName.SetUserNameData(
      FEApp->fInputPlayer, frontEnd.playerNameList[FEApp->fInputPlayer]);
  /* SYM-INLINE-THIS: SetCallingMenu
     SYM-INLINE-LOCAL: m = SetCallingMenu */
  screenUserName->SetCallingMenu(&menuDefs->menuUserName);
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = (tMenu *)&menuDefs->menuUserName;
  return;
}



/* ---- MenuExtended_GoToShowroom__FR12tMenuCommand  [FEMENUDEFS.CPP:750-753] ---- */

/* Decoded Phase 83: MenuExtended_GoToShowroom__FR12tMenuCommand(tMenuCommand&) - transition to player's garage 3D
   showroom view (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* P874: no caller locals in SYM5b649c; PASS16/exact-g, exact SLD750-753. */
void MenuExtended_GoToShowroom(tMenuCommand &command)

{
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = &menuDefs->menuShowroom;
  screenCarSelect->SetState(5);
}



/* ---- MenuExtended_GoToDealerShowroom__FR12tMenuCommand  [FEMENUDEFS.CPP:757-760] ---- */

/* Decoded Phase 83: MenuExtended_GoToDealerShowroom__FR12tMenuCommand(tMenuCommand&) - transition to dealer 3D
   showroom view (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* P874: no caller locals in SYM5b6547; PASS16/exact-g, exact SLD757-760. */
void MenuExtended_GoToDealerShowroom(tMenuCommand &command)

{
  command.type = kMenu_Command_GoToMenu;
  command.nextMenu = &menuDefs->menuShowroom;
  screenCarSelect->SetState(6);
}



/* car-list filter setter (retail records a variable-free inline pair on menuDefs->iteratorCar1) */
static inline void CarIterator_SetFilter(tListIteratorCar &iterator, int filter) { iterator.fCarListFilter = filter; }
/* menu-item state test (retail records a variable-free inline pair on menuDefs->itemSaveGame) */
static inline int MenuItem_IsEnabled(tMenuItem &item) { return ((item.fFlags ^ 1) & 1) != 0; }

/* ---- MenuExtended_SetHPSoloRace__FR12tMenuCommand  [FEMENUDEFS.CPP:764-768] ---- */

/* Decoded Phase 83: MenuExtended_SetHPSoloRace__FR12tMenuCommand(tMenuCommand&) - set raceType=HotPursuit Solo (44 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetHPSoloRace__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetHPSoloRace(tMenuCommand &)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\x01';
  frontEnd.oppNumber = '\0';
  CarIterator_SetFilter(menuDefs->iteratorCar1, 0xb);
  return;
}



/* ---- MenuExtended_SetHPDuelRace__FR12tMenuCommand  [FEMENUDEFS.CPP:772-776] ---- */

/* Decoded Phase 83: MenuExtended_SetHPDuelRace__FR12tMenuCommand(tMenuCommand&) - set raceType=HotPursuit Duel (44 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetHPDuelRace__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetHPDuelRace(tMenuCommand &)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\x01';
  frontEnd.oppNumber = '\x01';
  CarIterator_SetFilter(menuDefs->iteratorCar1, 1);
  return;
}



/* ---- MenuExtended_SetHotPursuit__FR12tMenuCommand  [FEMENUDEFS.CPP:780-788] ---- */

/* Decoded Phase 83: MenuExtended_SetHotPursuit__FR12tMenuCommand(tMenuCommand&) - set raceType=HotPursuit (cops vs
   perps mode) (80 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetHotPursuit__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetHotPursuit(tMenuCommand &)

{
  frontEnd.carListType = '\0';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\x01';
  if (frontEnd.gameMode == '\x01') {
    CarIterator_SetFilter(menuDefs->iteratorCar1, 9);
  }
  else {
    CarIterator_SetFilter(menuDefs->iteratorCar1, 1);
  }
  frontEnd.oppNumber = '\0';
  return;
}



/* ---- MenuExtended_SellCar__FR12tMenuCommand  [FEMENUDEFS.CPP:792-814] ---- */

/* Decoded Phase 83: MenuExtended_SellCar__FR12tMenuCommand(tMenuCommand&) - sell currently-selected garage car for
   cash credit (344 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SellCar__FR12tMenuCommand(int arg0)'.Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern.
    */

/* [W57-A1 2026-08-09, 32->6, count EXACT 86/86] SYM 8c (fsize 200, mask 0x80070000 = ra+s0..s2)
   lists exactly ONE fn-scope local: `money`, class REG $10 = s0, type LONG.  So retail
   ACCUMULATED into it (`money = fMoney; money += CalcUsedPrice(...)`) -- the oracle's
   `addu s0,s0,v0` -- instead of keeping the used-car price in a 4th saved reg and summing at the
   compare (ours was 4 s-regs / frame 208).  That also collapses the `(1<n) || (cheapest <= sum)`
   OR from `slt;xori 1;beqz` to the oracle's direct `slt v0,s0,v0; bnez`.  Plus the `pp` anchor on
   the string/fDefault stores (was sp-relative), and `bVar1 = false` MOVED after the CalcUsedPrice
   statement so gcc emits it into that jal's delay slot instead of at the top of the fn (which
   also fixes the prologue save ORDER: s1,s0,s2,ra).

   [2026-08-26 source-only/SYM restoration, 6 -> PASS 86/86] Removed the remaining
   decompiler aliases: retail SYM names only function-scope `long money`, block-local
   `tDialogYesNo popUp`, and the two inlined receivers.  The comma-staged self-assignment
   is load-bearing: it keeps the retail fMoney load in s0 before CalcUsedPrice while making
   GCC birth the final addition after both GetNumOwnedCars argument moves, so reorg selects
   that addition for the call delay slot.  The source-level tFEApplication::DisplayMessage
   inline restores the line-811 receiver shape.  No asm, volatile, added caller local, or
   post-compilation modification is used. MATCH: 86/86. */

void MenuExtended_SellCar(tMenuCommand &command)

{
  /* SYM-ABI-PARAM: command -- required by the retail `FR12tMenuCommand`
     linkage identity; optimized away before the SYM parameter records. */
  long money;

  /* [2026-07-11] Dropped the REDUNDANT `tDialogYesNo_ctor(&popUp)` manual call and block-scoped
     popUp into the `if (bVar1)` (see AskTheUserToSaveTheGame's note for why).
     [BUG FIX 2026-07-27, 56->53] Same DOUBLE-DESTRUCTION bug as the other tDialogYesNo/
     tDialogYesNoTri locals in this file: dropped the manual `tScreen_dtor((tScreen*)&popUp,2)`
     that was firing alongside popUp's own auto-invoked destructor.
     [W56-A3 2026-08-09, 53->32] messagePopup anchor: routed `(ptVar2->messagePopup).string` store
     through the `this_00 = &FEApp->messagePopup` anchor (reused for the Display arg), + `pp=&popUp`
     mixed anchor on the yesnowords stores. RESIDUAL 32 = the `(1<sVar3) || (lVar5 <= sum)` OR
     materializes the `<=` as `slt;xori 1;beqz` where the oracle branches directly (`slt;bnez`,
     the w43 (x^1)/boolean-branch class), + a saved-reg-count/frame delta (ours 208/4-sreg vs
     oracle 200/3-sreg) -- coloring, allocsim/qtytrace class. */
  money = (money = tournamentManager.fMoney,
           money + carManager.CalcUsedPrice(
                       (ushort)(byte)frontEnd.garageCar[0]));
  if ((carManager.GetNumOwnedCars(kPlayerOne) > 1) ||
      (money >= carManager.CheapestCarStockPrice())) {
    tDialogYesNo popUp;

    /* SYM-INLINE-THIS: SetString */
    popUp.SetString(TextSys_Word(0xa5));
    popUp.SetChoices(0x321,0x322,0);
    if (popUp.Run() != 0) {
      tournamentManager.fMoney +=
          carManager.SellCar((ushort)(byte)frontEnd.sellerCar,0);
      menuDefs->iteratorSellerCar.Decrement(kPlayerOne);
      menuDefs->iteratorSellerCar.Increment(kPlayerOne);
      AudioCmn_PlayFESFX(0x1a);
    }
  }
  else {
    /* SYM-INLINE-THIS: DisplayMessage */
    FEApp->DisplayMessage(0xa9);
  }
  return;
}



/* ---- MenuExtended_BuyCar__FR12tMenuCommand  [FEMENUDEFS.CPP:819-849] ---- */

/* Decoded Phase 83: MenuExtended_BuyCar__FR12tMenuCommand(tMenuCommand&) - purchase highlighted dealer car; debits
   cash, adds to garage (340 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_BuyCar__FR12tMenuCommand(int arg0)'.Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern.
    */

/* [W57-A1 2026-08-09, 14->7] The oracle uses TWO pseudos for `&FEApp->messagePopup`: s0 (the
   if-arm's "not enough money" store + Display) and s1, a COPY of s0 that reorg steals into the
   `beqz` delay slot for the else-arm.  Reproducing it needs the copy to be a GLOBAL allocno (a
   copy made INSIDE the else block is block-local -> local-alloc's combine_regs merges it right
   back, and the two arms then cross-jump into one tail): so `popUp = dialogAnchor;` is made BEFORE the
   branch and held apart from dialogAnchor with a 0-insn opacity fence (cse otherwise copy-propagates
   dialogAnchor into every popUp use and the split vanishes -- measured 14 either way without it).
   Also the compare written `tournamentManager.fMoney >= carInfo.fPrices[0]` so the money load is
   issued first (05H compare-operand order = load order).  RESIDUAL 7 = the fence blocks reorg's
   backward scan so the copy stays ahead of the branch instead of in its delay slot (+1 insn), and
   the if-arm's `addu a0,s0,zero` lands in a 2nd tail block rather than the `j` slot. */

/* [W59-A12 2026-08-14, 7->0 PASS] The last two residuals were ONE shape each.
   (a) TAIL: both arms must END in their own `Display(); return;` (the else-arm
   de-nested to straight-line fall-out).  gcc then cross-jump-merges the two
   `jal Display`+epilogue tails and each arm keeps only its own receiver setup --
   the if-arm`s `addu a0,s0,zero` rides the `j` delay slot (oracle) instead of our
   old shared-tail form, which parked the STORE in that slot and needed an extra
   `addu a0,s0,zero` block (= the +1 insn, ours 86 vs oracle 85).
   (b) FENCE PLACEMENT: the opacity fence must sit on `dialogAnchor` BEFORE the copy,
   not on `popUp` after it.  Any asm stops reorg`s backward delay-slot scan, so a
   fence AFTER the copy pins `addu s1,s0,zero` ahead of the branch; moved ahead of
   the copy it still keeps the two pseudos apart (cse cannot launder through it)
   while leaving the copy as the last movable insn -> reorg fills the `beqz` slot
   with it, exactly as retail.  Measured: tail-only 47, fence-only 12, no-fence 12,
   BOTH -> PASS 85/85. */

void MenuExtended_BuyCar(tMenuCommand &command)

{
  /* SYM-ABI-PARAM: command -- required by the retail `FR12tMenuCommand`
     linkage identity; optimized away before the SYM parameter records. */
  tCarInfo carInfo;
  tDialogMessageString *popUp;
  /* SYM-CODEGEN-CARRIER: dialogAnchor -- replacing the second popup anchor with
     source-level `FEApp->DisplayMessage` is FAIL 32 at 87/85 and rotates the
     saved-register/global-base web.  Retail requires this independent anchor. */
  tDialogMessageString *dialogAnchor;

  /* [2026-07-11] Dropped the REDUNDANT `tDialogYesNo_ctor(&yesNo)` manual call and block-scoped
     yesNo into the inner `if` (see AskTheUserToSaveTheGame's note for why).
     [BUG FIX 2026-07-27, 44->41] Same DOUBLE-DESTRUCTION bug: dropped the manual
     `tScreen_dtor((tScreen*)&yesNo,2)` firing alongside yesNo's own auto-invoked destructor.
     [W56-A3 2026-08-09, 41->14] messagePopup ANCHOR bug + popUp mixed-anchor: both message
     stores went through `(ptVar1->messagePopup).string` (recomputing FEApp+44 each time) while
     `dialogAnchor = &FEApp->messagePopup` was computed-but-underused; routing both stores through
     dialogAnchor (reused for the two paths + the shared Display) reproduces the oracle's held +44
     anchor (w42). Plus `pp=&yesNo` on the two yesnowords stores only (the PurchaseUpgrade mixed
     popUp anchor). RESIDUAL 14 = oracle keeps dialogAnchor in TWO callee-saved regs (`addu s1,s0,zero`)
     across the yesNo Run, using s1 for the message-path stores, + the two independent compare
     loads (fMoney 20 / price) issued in swapped order -- the coloring/sched-tie class (4.6). */
  dialogAnchor = &FEApp->messagePopup;
  carManager.GetStockCar((ushort)(byte)frontEnd.dealerCar,carInfo);
  /* MATCH W86-D3 2026-09-02: the opacity fence that used to hold `popUp` apart
     from `dialogAnchor` (cse otherwise copy-propagates one into the other and the
     two-anchor split vanishes) is replaced by a pure-C ABSORPTION copy.
     `dialogAnchor & (dialogAnchor | &carManager)` == dialogAnchor for ANY second operand
     (absorption law), so the value is identical, but it is a DIFFERENT
     expression, so cse cannot record popUp == dialogAnchor -- the same equality
     kill the fence bought -- and combine collapses the pair at ZERO bytes.
     Whole-TU gate 66/66.  Measured: fence dropped 12; the same absorption
     against `&carInfo` (as an assignment to popUp, as an OR-form, or applied
     to dialogAnchor before the copy) 24; a dead `dialogAnchor |= 0` reassignment 12. */
  popUp = (tDialogMessageString *)((int)dialogAnchor & ((int)dialogAnchor | (int)&carManager));
  if (carManager.GetNumOwnedCars(0) < 0x20) {
    if (tournamentManager.fMoney >= carInfo.fPrices[0]) {
      tDialogYesNo yesNo;
      /* SYM-CODEGEN-CARRIER: pp -- direct `yesNo.yesnowords` stores are
         count-exact FAIL 4 and use two sp-relative stores instead of retail's
         held `$s0` object-base stores. */
      tDialogYesNo *pp = &yesNo;

      yesNo.string =
           TextSys_Word(0xa4);
      pp->yesnowords[0] = 0x321;
      pp->yesnowords[1] = 0x322;
      yesNo.fDefault = 0;
      if (((tDialogInteractive *)&yesNo)->Run() != 0) {
        tournamentManager.fMoney -= carManager.PurchaseCar(
            (short)carInfo.fCarID,
            (ushort)(byte)frontEnd.carColors[0][carInfo.fCarID],0);
        AudioCmn_PlayFESFX(0x1a);
      }
      return;
    }
    AudioCmn_PlayFESFX(10);
    dialogAnchor->string = TextSys_Word(0xa7);
    ((tDialogBase *)dialogAnchor)->Display();
    return;
  }
  popUp->string = TextSys_Word(0x4b);
  ((tDialogBase *)popUp)->Display();
  return;
}



/* ---- MenuExtended_PurchaseUpgrade  [FEMENUDEFS.CPP:854-877] ---- */

static inline int MenuExtended_CannotPurchaseUpgrade(long money, long *price)
{
  return money < *price;
}

static inline int MenuExtended_UpgradePriceIndex(int priceIndex)
{
  return ++priceIndex;
}

static inline void MenuExtended_SetUpgradeDialogWords(tDialogYesNo *dialog)
{
  dialog->yesnowords[0] = 0x321;
  dialog->yesnowords[1] = 0x322;
}

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade(int upgradeIdx) - shared core purchase logic
   called by PurchaseUpgrade1/2/3 wrappers (320 B, 3 callers). Validates cash, debits, applies
   upgrade modifier to current car.
   
   [ghidra-meta] section: front.text */

void MenuExtended_PurchaseUpgrade(int upgradeNumber)

{
  tCarInfo carInfo;
  int upgradeFlag;

  /* NEAR-MISS (2026-07-11): dropped the eager `ptVar1 = FEApp` cache -> FEApp now loaded
     lazily only in the not-enough-money branch (matches oracle's `lw s0,%lo(FEApp)(v0)` there),
     freeing one saved reg. Also dropped the REDUNDANT `tDialogYesNo_ctor(&popUp)` manual call
     (tDialogYesNo's real ctor is already auto-invoked by the local's declaration) and
     block-scoped popUp into the `else` -- the previous note blamed a "speculative hoist" of the
     ctor call above GetGarageCar, but that hoisted call was actually the AUTOMATIC ctor for the
     function-scope `popUp` firing at the top unconditionally, stacked with the (redundant) manual
     call in the else; removing the manual call and shrinking popUp's scope to the else fixes
     the hoist at the source.

     [BUG FIX 2026-07-27, DOCUMENTED CORRECTNESS EXCEPTION] Found the same DOUBLE-DESTRUCTION bug
     present across this file: the `else` block ALSO had a manual `tScreen_dtor((tScreen*)&popUp,2)`
     firing IN ADDITION to popUp's own real auto-invoked `tDialogYesNo::~tDialogYesNo()`. Dropped
     it -- a genuine behavioral bug fix (this function was double-freeing/double-resetting the
     dialog's vtable on every real invocation). Byte-match went 28->29 diffs (insn count improved
     79 vs oracle 80, was 82 vs 80) -- removing the dead call shifted downstream register
     allocation (branch polarity flip beqz<->bnez, s0/a0-vs-v0/sp addressing) rather than a clean
     3-insn drop like the sibling fns. Kept per the correctness-exception clause: a real
     double-destruction bug outweighs a 1-line diff delta, and insn count is closer to the oracle
     than before.

     [W56-A3 2026-08-09, 27->2 diffs, count-exact 80/80] The prior "branch polarity flip"
     was NOT reg-alloc noise -- it was ARM ORDER. Oracle lays the yes/no (else) block as the
     FALL-THROUGH and the insufficient-funds message popup at the branch target (bnez, not beqz;
     w42 physical-block-order). Fix = keep `fPrices <= fMoney` semantics but write the arms
     swapped (yesno first / message in else). Then three anchor+sched levers: (a) messagePopup
     anchored via the SYM `this` pointer local -- `dlgThis = &ptVar1->messagePopup` reused for
     the .string store AND the Display arg (w42 anchor, +44/+144 split); (b) MIXED popUp anchor
     -- `pp=&popUp` used ONLY for the two yesnowords stores (oracle anchors those in s0 but keeps
     .string/.fDefault sp-relative; anchoring all or none is each 8 diffs, the split is 4);
     (c) compute `dlgThis` BEFORE the TextSys_Word(0xa8) call so reorg fills that jal's delay slot
     with `addiu s0,s0,44` instead of the arg li.  Reusing the SYM-recorded `upgradeFlag`
     for the bit mask removes the non-SYM `uVar5` carrier without changing code.
     [SOURCE PASS 2026-08-26, 2->0 diffs, 80/80] Keep the affordability test in two tiny
     inlined expressions.  The by-value `++priceIndex` prevents GCC from folding the +1 into
     the final member offset (retail has addiu/sll and offset 48, not sll and offset 52).
     Passing `(fMoney, pricePointer)` then forms the indexed stack address before the manager
     address, while the inlined predicate loads fMoney before dereferencing the price pointer.
     This is pure C++: both helpers disappear completely, add no target-function local/SYM
     record, and require no asm, volatile, register pin, or post-compilation move.
     [STRICT SYM 2026-08-26] Inline the Run result, purchase result, and TextSys result directly;
     use a disappearing dialog-word helper and the existing DisplayMessage inline.  This removes
     every decompiler carrier absent from retail SYM while preserving the expected line-21
     DisplayMessage `this` record and the exact 80-instruction body. */
  upgradeFlag = 1 << (upgradeNumber);
  carManager.GetGarageCar((ushort)(byte)frontEnd.garageCar[0],carInfo,0);
  if ((carInfo.fUpgrades & upgradeFlag) == 0) {
    if (!MenuExtended_CannotPurchaseUpgrade(
            tournamentManager.fMoney,
            &carInfo.fPrices[
                MenuExtended_UpgradePriceIndex(upgradeNumber)])) {
      tDialogYesNo popUp;

      popUp.string =
           TextSys_Word(0xa6);
      MenuExtended_SetUpgradeDialogWords(&popUp);
      popUp.fDefault = 0;
      if (((tDialogInteractive *)&popUp)->Run() != 0) {
        tournamentManager.fMoney =
            tournamentManager.fMoney -
            carManager.PurchaseUpgrade((ushort)(byte)frontEnd.garageCar[0],
                                       (short)upgradeFlag,0);
        AudioCmn_PlayFESFX(0x1a);
      }
    }
    else {
      /* SYM-INLINE-THIS: DisplayMessage */
      FEApp->DisplayMessage(0xa8);
    }
  }
  return;
}



/* ---- MenuExtended_PurchaseUpgrade1__FR12tMenuCommand  [FEMENUDEFS.CPP:883-884] ---- */

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade1__FR12tMenuCommand(tMenuCommand&) - tail-call wrapper for tier-1
   upgrade purchase (32 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_PurchaseUpgrade1__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_PurchaseUpgrade1(tMenuCommand &)

{
  MenuExtended_PurchaseUpgrade(1);
  return;
}



/* ---- MenuExtended_PurchaseUpgrade2__FR12tMenuCommand  [FEMENUDEFS.CPP:888-889] ---- */

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade2__FR12tMenuCommand(tMenuCommand&) - tail-call wrapper for tier-2
   upgrade purchase (32 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_PurchaseUpgrade2__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_PurchaseUpgrade2(tMenuCommand &)

{
  MenuExtended_PurchaseUpgrade(2);
  return;
}



/* ---- MenuExtended_PurchaseUpgrade3__FR12tMenuCommand  [FEMENUDEFS.CPP:893-894] ---- */

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade3__FR12tMenuCommand(tMenuCommand&) - tail-call wrapper for tier-3
   upgrade purchase (32 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_PurchaseUpgrade3__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_PurchaseUpgrade3(tMenuCommand &)

{
  MenuExtended_PurchaseUpgrade(0);
  return;
}



/* ---- MenuExtended_SaveGame__FR12tMenuCommand  [FEMENUDEFS.CPP:898-901] ---- */

/* Decoded Phase 83: MenuExtended_SaveGame__FR12tMenuCommand(tMenuCommand&) - save game state to memcard (80 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SaveGame__FR12tMenuCommand(int arg0)'.Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern.
    */

void MenuExtended_SaveGame(tMenuCommand &)

{
  if ((CURRENTLYUSINGMEMCARD == 0) &&
     MenuItem_IsEnabled(menuDefs->itemSaveGame)) {
    GenericMenuSaveGame(0);
  }
  return;
}



/* ---- GenericMenuLoadGame  [FEMENUDEFS.CPP:922-941] ---- */

/* Decoded Phase 86: FE-GenericMenuLoadGame (148 B): execute generic load-game flow from
   menu.
   
   [ghidra-meta] section: front.text */

/* MATCH (2026-08-13, 8->PASS, 37/37): a zero-byte memory-input fence births FEApp's address
   quantity before screenMemcard's, giving retail s0/s1. Explicit app-then-mc volatile reloads
   on both sides of LoadGame reproduce retail's value registers and scheduling. */

void GenericMenuLoadGame(int player)
{
  if (CURRENTLYUSINGMEMCARD == 0) {
    screenMemcard->SetMessage(0x27d);
    FEApp->Redraw();
    LoadGame((short)player,false,1);
    screenMemcard->SetMessage(-1);
    ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Hide();
  }
  ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Hide();
}



/* ---- MenuExtended_LoadGame__FR12tMenuCommand  [FEMENUDEFS.CPP:945-957] ---- */

/* Decoded Phase 83: MenuExtended_LoadGame__FR12tMenuCommand(tMenuCommand&) - load save from memcard via Front_*;
   populate game state (152 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [SYM restoration 2026-08-26, PASS 38/38] The `FR12tMenuCommand` linkage proves
   the callback's reference parameter, while the missing REGPARM record proves
   that its source spelling was unnamed.  The early-return guard keeps the sole
   SYM AUTO (`tDialogYesNo AreYouSure`, 168 bytes at sp+16) in function scope but
   constructs it only on the enabled path.  `SetChoices` reconstructs the SYM's
   inlined tDialogYesNo receiver in s0; the original private helper identifier is
   not recoverable.  Consuming Run directly removes the decompiler-invented result
   local.  The anonymous eight-byte frame receipt is documented at its statement.
   Focused verify_asm and the independent -g/SLD twin are both exact. */

void MenuExtended_LoadGame(tMenuCommand &)
{
  if (MenuItem_IsDisabled(menuDefs->itemLoadGame)) {
    return;
  }
  tDialogYesNo AreYouSure;
  tMenuCommand();
  Dialog_SetText(AreYouSure.SetChoices(0x321, 0x322, 0), TextSys_Word(0x2c0));
  if (AreYouSure.Run() != 0) {
    GenericMenuLoadGame((int)screenMemcard->player);
  }
}



/* ---- MenuExtended_TierFinished__FR12tMenuCommand  [FEMENUDEFS.CPP:960-976] ---- */

/* Decoded Phase 83: MenuExtended_TierFinished__FR12tMenuCommand(tMenuCommand&) - tournament tier complete; advance to
   next tier (128 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [Match 2026-07-05] Branch-polarity flip (oracle emits the else/congrats block as
   fall-through, the if/AskUser block as the branch target -- both nested ifs written
   inverted vs the natural Ghidra reading) -> byte-match, 32/32 insns.
   [SYM 2026-08-25] Retail declares only `command` and stack `award`; direct
   predicate use plus branch-local command.nextMenu assignments remove the former
   iVar1/ptVar2 while preserving exact PASS 32/32 and the exact -g twin. */

void MenuExtended_TierFinished(tMenuCommand &command)

{
  tAwardInformation award;
  
  command.type = kMenu_Command_GoToMenuOneWay;
  tournamentManager.GetAwardInformation(award);
  if (award.fCompletedTier != 0) {
    command.nextMenu = (tMenu *)&menuDefs->menuTierCompleteCongrats;
  }
  else {
    if (AskTheUserToSaveTheGame() != 0) {
      command.nextMenu = (tMenu*)&menuDefs->menuPostGameSave;
    }
    else {
      command.nextMenu = (tMenu*)&menuDefs->menuMain;
    }
  }
  return;
}



/* ---- MenuExtended_DidUserWinBeTheCop  [FEMENUDEFS.CPP:1011-1036] ---- */

/* Decoded Phase 83: MenuExtended_DidUserWinBeTheCop() - check Behind-The-Cop win condition; returns
   winner status (284 B, 1 caller). Used by PostGameMenu to choose congrats vs failure animation.
   
   [ghidra-meta] section: front.text
   
   [Locals 2026-05-08] Locals renamed via deep-body inspection. Did-user-win-Be-The-Cop check.Returns 1 if user just unlocked a cop car after a successful BTC mission, 0 otherwise.GetStockCar(playerCar[0]) loads carInfo. Conditions: carClass=='\x07' (= cop class) AND
   raceType==1 (= BTC mode) AND gameMode!=1 (= not exhibition) AND numPerps<finalPerpArrests (=
   mission goal met). cop_car = GetCarFromID(gCarActivation[-0x13][country*5 + carID + 4]) looks up
   the unlock-target car. If !fAvailable: SetCarAvailable, store congratsCopCar+congratsCopCountry,
   return 1. activateCar/result are caller-side spills. */

/* [W57-A1 2026-08-09, 71->PASS] see the SYM note in the body: real `result` local (SYM class REG
   $13 = s3, type BOOL) + FULLY NESTED ifs with ONE `return result;`.  The early-return form was
   tried first and FAILED (28 diffs): with per-guard `return result;` gcc const-propagates the
   provably-0 value into each exit (`addu v0,zero,zero`), which SHORTENS result's live range so it
   coalesces with `activateCar` into one saved reg (3 s-regs / frame 240 vs the oracle's 4 / 248).
   The single-return form keeps result live across the GetCarFromID block -> the two conflict ->
   separate regs, and reorg then STEALS the shared epilogue's `addu v0,s3,zero` into each guard's
   delay slot, reproducing all four copies.  Also `(signed char)` on carInfo.fCarID and on
   frontEnd.carCountry[0][id] where they feed the INDEX arithmetic (oracle `lb`, ours `lbu`; the
   later byte-COPY of the same field legitimately stays `lbu` -- 08C), and the perp compare
   written `finalPerpArrests > numPerps` so the 440 load is issued before the 428 one.
   Return type corrected void*->int (SYM BOOL; not declared in any header, single in-TU caller). */

/* [SYM 2026-08-16] retail `Def class STAT type FCN BOOL` @0x8002d9e8 -> bool (the earlier
   void*->int correction stopped one step short); STAT confirms the `static`. */
static bool MenuExtended_DidUserWinBeTheCop(void)

{
  tCarInfo carInfo;
  tCarInfo *activateCar;
  bool result;

  /* [W57-A1] SYM 8c budget (fsize 248, mask 0x800f0000): exactly TWO named locals besides
     carInfo -- activateCar (class REG $10 = s0) and result (class REG $13 = s3, SYM BOOL;
     this compiler's C++ `bool`).  The old `pvVar1 = 0` repeated inside an `&&` chain never produced a
     long-lived result pseudo (it landed in $a0); a real `result` local + flat early-return
     guard chain (04T `return VARIABLE;` keeps DISTINCT return sites -> the oracle's
     `addu v0,s3,zero` in each guard's delay slot) reproduces the 4-saved-reg frame. */
  result = 0;
  carManager.GetStockCar((ushort)(byte)frontEnd.playerCar[0],carInfo);
  if (carInfo.fCarClass == '\a') {
    if (frontEnd.raceType == RaceType_HotPursuit) {
      if (frontEnd.gameMode != '\x01') {
        if (GameSetup_gData.finalPerpArrests > GameSetup_gData.numPerps) {
          activateCar = carManager.GetCarFromID(
                                     (short)gCarActivation[(signed char)carInfo.fCarID + -0x16]
                                         [(signed char)frontEnd.carCountry[0][(signed char)carInfo.fCarID]]);
          if (activateCar->fAvailable == '\0') {
            carManager.SetCarAvailable((tCarModels)activateCar->fCarID,true);
            frontEnd.congratsCopCar = activateCar->fCarID;
            frontEnd.congratsCopCountry = frontEnd.carCountry[0][(signed char)carInfo.fCarID];
            result = 1;
          }
        }
      }
    }
  }
  return result;
}



/* ---- MenuExtended_PostGameMenu__FR12tMenuCommand  [FEMENUDEFS.CPP:1040-1082] ---- */

/* Decoded Phase 83: MenuExtended_PostGameMenu__FR12tMenuCommand(tMenuCommand&) - show post-game menu(continue/save/restart/quit) (256 B)
   
   [ghidra-meta] section: front.text */

/* [SYM restoration 2026-08-26, PASS 64/64] Retail records only the `command`
   REGPARM in s0.  Both call results are consumed directly.  The two nested
   `this` records in v1 are restored by the inline SetDrawMoney operation; SYM
   preserves its receiver type and store but not the private helper identifier.
   Direct per-case nextMenu assignments remove the decompiler's synthetic menu
   pointer and let gcc cross-jump their identical store/return tails exactly as
   retail did.  The case order 2 / 6 / 1 and case-1 fallthrough preserve the
   balance_case_nodes tree and SLD statement order.  verify_asm and the -g/SLD
   twin are exact, with no caller locals beyond the SYM budget. */

void MenuExtended_PostGameMenu(tMenuCommand &command)

{
  StatChk_ClearNewRecords();
  command.type = kMenu_Command_GoToMenuOneWay;
  switch (frontEnd.raceType) {
  case 2:
    if ((short)tournamentManager.IsTournamentFinished() != 0) {
      command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuTournamentFinished;
      /* SYM-INLINE-THIS: SetDrawMoney */
      screenTournamentStandings->SetDrawMoney();
      return;
    }
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuTournamentStandings;
    screenTournamentStandings3item->SetDrawMoney();
    return;
  case 6:
    command.nextMenu = (tMenu *)&menuDefs->menuPinkSlipStandings;
    return;
  case 1:
    if (MenuExtended_DidUserWinBeTheCop()) {
      command.nextMenu = (tMenu *)&menuDefs->menuBeTheCopCongrats;
      return;
    }
    /* fall through */
  default:
    command.nextMenu = (tMenu *)&menuDefs->menuMain;
  }
  return;
}



/* ---- MenuExtended_FinishedPlayer1GetName__FR12tMenuCommand  [FEMENUDEFS.CPP:1090-1120] ---- */

/* Decoded Phase 83: MenuExtended_FinishedPlayer1GetName__FR12tMenuCommand(tMenuCommand&) - after race, prompt P1 for
   name entry (high score etc) (272 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* [W57-A1 2026-08-09, 57->PASS] Three levers: (1) the if/else ARMS SWAPPED to
   `if (needName[1] != 0 && gotName[1] == 0) {name-entry} else {records}` -- the oracle's two
   guards both branch AWAY to the records block, so the name-entry block is the fall-through and
   is laid out FIRST; (2) `dlgThis = &ptVar2->menuItemUserName2` ANCHOR (oracle holds
   `addiu v1,a0,12868` and stores at 128/28/32/36/34(v1); ours emitted absolute 12996/12896/...
   off the menuDefs base); (3) `ptVar2 = menuDefs[0]` moved INSIDE that arm, which drops the
   `lui s3` hoist (an entire 4th saved reg + 8 bytes of frame). */
/* [SYM restoration 2026-08-26, PASS 68/68] Reliable caller identities are
   command/dummyCars/nBestCarIndex.  The records arm now genuinely assigns and
   reuses dummyCars while its two call-result temporaries fold away.  The
   post-game name setup is one inferred SetPostGameNameData expansion followed
   by SetCallingMenu (including its recorded `m` formal). P879's corrected
   scalar menuDefs context makes direct repeated member access exact at 68/68;
   the obsolete defs carrier and its earlier context-specific miss are gone. */

void MenuExtended_FinishedPlayer1GetName(tMenuCommand &command)

{
  /* SYM: dummyCars and nBestCarIndex belong to the else block, not fn scope. */
  command.type = kMenu_Command_GoToMenuOneWay;
  if ((FEApp->needName[1] != 0) && (FEApp->gotName[1] == 0)) {
    /* SYM-INLINE-THIS: SetPostGameNameData */
    menuDefs->menuItemUserName2.SetPostGameNameData(
        1, frontEnd.playerNameList[1]);   /* retail frontEnd+0x36c (same defect as feapp MainLoop) */
    /* SYM-INLINE-THIS: SetCallingMenu
       SYM-INLINE-LOCAL: m = SetCallingMenu */
    screenUserName->SetCallingMenu(&menuDefs->menuPostGamePlayer2Name);
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuPostGamePlayer2Name;
  }
  else {
    Car_tStats *dummyCars;
    short nBestCarIndex;

    dummyCars = Cars_NewCarStatsList();
    if (StatChk_IsRecordLapTime(dummyCars,(short)Cars_gNumRaceCars,&nBestCarIndex)) {
      StatChk_SaveRecordLapTime(dummyCars,(short)Cars_gNumRaceCars,nBestCarIndex);
    }
    if (StatChk_IsTopTime(dummyCars,(short)Cars_gNumRaceCars) != 0) {
      StatChk_SaveTopTime(dummyCars,(short)Cars_gNumRaceCars);
    }
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuPostGameTrackRecords;
  }
  return;
}



/* ---- MenuExtended_FinishedPlayer2GetName__FR12tMenuCommand  [FEMENUDEFS.CPP:1125-1142] ---- */

/* Decoded Phase 83: MenuExtended_FinishedPlayer2GetName__FR12tMenuCommand(tMenuCommand&) - after race, prompt P2 for
   name entry (160 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_FinishedPlayer2GetName(tMenuCommand &command)

{
  /* P879: direct scalar menuDefs use removes the unrecorded final-menu base. */
  Car_tStats *dummyCars;
  short nBestCarIndex;

  /* SYM: `dummyCars` is the real REG Car_tStats pointer in $s1 and is reused
     across all four stat-tool calls; `nBestCarIndex` is its recorded AUTO. */
  dummyCars = Cars_NewCarStatsList();
  if (StatChk_IsRecordLapTime(dummyCars,(short)Cars_gNumRaceCars,&nBestCarIndex)) {
    StatChk_SaveRecordLapTime(dummyCars,(short)Cars_gNumRaceCars,nBestCarIndex);
  }
  if (StatChk_IsTopTime(dummyCars,(short)Cars_gNumRaceCars) != 0) {
    StatChk_SaveTopTime(dummyCars,(short)Cars_gNumRaceCars);
  }
  command.type = kMenu_Command_GoToMenuOneWay;
  command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuPostGameTrackRecords;
  return;
}



/* ---- MenuExtended_SetPinkSlips__FR12tMenuCommand  [FEMENUDEFS.CPP:1146-1159] ---- */

/* Decoded Phase 83: MenuExtended_SetPinkSlips__FR12tMenuCommand(tMenuCommand&) - set raceType=PinkSlips and prepare
   car-select (192 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name + (body or
   100%-caller-consensus) agree. Generic param names; types int/void* default - refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetPinkSlips__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern.

   [Match 2026-07-05] Both loops were Ghidra's `short`-counter-as-int artifact
   (`iVar1<<0x10>>0xf` / `iVar1>>0x10`/`iVar2*0x10000`) -- the declared-but-unused `short i`
   was the real loop counter (methodology 3.12 lever #9c). Rewriting both loops as plain
   `short i` down-to-up counts + natural array indexing (`pinkSlipsWins[i]`/
   `pinkSlipsWinner[i]=-1`) reproduces the oracle's per-iteration sll<<16;sra>>16 exactly.
   -> byte-match, 48/48 insns. */

void MenuExtended_SetPinkSlips(tMenuCommand &)

{
  short i;

  screenMain->SwapBackground(-1);
  frontEnd.raceType = '\x06';
  frontEnd.gameMode = '\x01';
  frontEnd.oppNumber = '\0';
  frontEnd.pinkSlipsForfeit = -1;
  frontEnd.pinkSlipsTrackIndex = '\0';
  i = 0;
  do {
    frontEnd.pinkSlipsWins[i] = '\0';
    i = i + 1;
  } while (i < 2);
  i = 0;
  do {
    frontEnd.pinkSlipsWinner[i] = -1;
    i = i + 1;
  } while (i < 5);
  return;
}



/* ---- MenuExtended_AwardPinkSlipsCar__FR12tMenuCommand  [FEMENUDEFS.CPP:1163-1218] ---- */

extern "C" void AddToPinkSlipsList_intarg(tCarManager *,short,short,int)
  __asm__("AddToPinkSlipsList__11tCarManagersss");
extern "C" void AddUpgradesToPinkSlipsList_intarg(tCarManager *,short,short,int)
  __asm__("AddUpgradesToPinkSlipsList__11tCarManagersss");
extern "C" int SavePinkSlipsCars_intarg(int,short,short)
  __asm__("SavePinkSlipsCarsWithErrorDialogs__Fsss");

static inline tCarManager *AwardPinkSlipsCarManagerArg(tCarManager *mgr)
{
  __asm__("" : "+r"(mgr));
  return mgr;
}

/* Decoded Phase 83: MenuExtended_AwardPinkSlipsCar__FR12tMenuCommand(tMenuCommand&) - award winner the loser's car
   after pinkslips race (552 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

/* PASS (2026-08-26, 2->PASS, 138/138): a one-use inline manager-argument
   identity makes GCC form `a0 = carManager` immediately after GetPinkSlipsCar,
   before the remaining argument loads, exactly like retail.  The empty asm emits
   no instruction and has no hard-register pin; placing it in the inline helper
   avoids adding `mgr` to this function's strict SYM local set.  The helper emits
   no standalone symbol.  Earlier receipt follows.
   NEAR-PASS (2026-08-13, 10->2, 138/138): SYM's sole `int fWinner` local plus a late tied
   `playerNum` quantity reproduces retail s3->s0 allocation. Caller-local int-argument aliases
   preserve the retail symbols while preventing redundant short sign extensions.  The sole
   residual is source gcc preparing the `carManager` a0 argument four instructions later than
   retail; no post-compilation move is active. Earlier five levers remain:
   (1) `dlgThis2 = &RetryCancelDialog` anchor for the
   yesnowords/fDefault stores; (2) BOTH fFullyOpen spin loops rewritten exit-in-the-middle
   with direct `FEApp` accesses -- this kills duplicate_loop_exit_test's rotation and GCC
   still reuses the last-loaded a0 for the post-loop Redraw without a source pointer identity,
   exactly like GenericMenuSaveGame; (3) the two NoInputMemCardDialog anchors made SEPARATE
   locals (one shared local forced a callee-saved pseudo + an extra `addu a0,sN,zero`; the first
   block's anchor legitimately dies into a0, the second is held across TextSys_Word); (4) the
   pink-slip index written as the real member access `frontEnd.pinkSlipsCar[1 - player]` (+ the 4th
   arg as `(short)(1 - fWinner)`) so the shared `1-player` is CSE'd and the +293 stays a load
   DISPLACEMENT -- the old `*(byte*)((int)&frontEnd + -player + 0x126)` cast folded the offset into
   the %lo and forced a `negu/addiu` pair; (5) the second Display's arg re-derived from a FRESH
   `&FEApp->NoInputMemCardDialog` (oracle reloads it) while the string store uses the held anchor. */

void MenuExtended_AwardPinkSlipsCar(tMenuCommand &command)

{
  /* P879: both final-menu selections use the actual scalar menuDefs pointer;
     no extra base local is needed. Other marked source-shape debt remains. */
  /* SYM 8c Def-record order: string, RetryCancelDialog, fWinner, carInfo, mess;
     the measured codegen carriers follow the SYM set. */
  char string [80];
  tDialogYesNo RetryCancelDialog;
  int fWinner;
  tCarInfo carInfo;
  char *mess;
  /* P880: the existing choice-setup inline preserves the retail stack-base
     handoff without the additional dlgThis2 caller declaration. */
  /* SYM-CODEGEN-CARRIER: dlgThis3 -- direct first-dialog member spellings are
     count-exact FAIL 6 and collapse retail's separate base/store addresses. */
  tDialogNoInputMessage *dlgThis3;
  /* SYM-CODEGEN-CARRIER: dialogAnchor -- direct second-dialog string storage is
     FAIL 16 at 136/138 and loses the base held across TextSys_Word. */
  tDialogNoInputMessage *dialogAnchor;
  /* SYM-CODEGEN-CARRIER: playerNum -- using fWinner directly is FAIL 67 at
     135/138, shrinks the frame, and rotates the complete saved-register web. */
  int playerNum;
  
  /* [2026-07-11 consolidation] dropped REDUNDANT tDialogYesNo_ctor(&RetryCancelDialog) manual
     call (undefined phantom extern; tDialogYesNo's real declared ctor auto-fires -- oracle
     shows a single jal __12tDialogYesNo). Same class as the ~11 sites fixed above.
     [BUG FIX 2026-07-27, 130->124] The matching manual `tScreen_dtor((tScreen*)&RetryCancelDialog,2)`
     at the function's tail was left in -- same DOUBLE-DESTRUCTION bug, firing alongside
     RetryCancelDialog's own auto-invoked destructor at the real `}`. Dropped it. */
  RetryCancelDialog.SetChoices(0x291,0x292,1);
  fWinner = screenPinkSlipCongrats->fWinner;
  mess = TextSys_Word(0x29a);
  sprintf(string,mess,PlayerName(fWinner),fWinner + 1);
  dlgThis3 = &FEApp->NoInputMemCardDialog;
  dlgThis3->string = string;
  ((tDialogBase *)dlgThis3)->Display();
  while (1) {
    if (((FEApp->NoInputMemCardDialog).fFullyOpen ^ 1) == 0) break;
    FEApp->Redraw();
  }
  FEApp->Redraw();
  Init_Memcard(false,1);
  carManager.GetPinkSlipsCar((ushort)(byte)frontEnd.pinkSlipsCar[1 - fWinner],carInfo,
             (short)(1 - fWinner));
  playerNum = fWinner;
  AddToPinkSlipsList_intarg(
             AwardPinkSlipsCarManagerArg(&carManager),
              (short)carInfo.fCarID,(ushort)carInfo.fColor,
             ({ __asm__("" : "+r"(playerNum) : "r"(fWinner)); playerNum; }));
  AddUpgradesToPinkSlipsList_intarg(&carManager,
             (ushort)(byte)frontEnd.pinkSlipsCar[playerNum],(ushort)carInfo.fUpgrades,playerNum);
  SavePinkSlipsCars_intarg(playerNum,2,-1);
  ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Hide();
  command.type = kMenu_Command_GoToMenuOneWay;
  command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuMain;
  dialogAnchor = &FEApp->NoInputMemCardDialog;
  mess = TextSys_Word(0x274);
  dialogAnchor->string = mess;
  ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Display();
  while (1) {
    if (((FEApp->NoInputMemCardDialog).fFullyOpen ^ 1) == 0) break;
    FEApp->Redraw();
  }
  FEApp->Redraw();
  GenericMenuLoadGame(0);
  DeInit_Memcard();
  ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Hide();
  command.type = kMenu_Command_GoToMenuOneWay;
  command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuMain;
  return;
}



/* ---- MenuExtended_GoToGarage__FR12tMenuCommand  [FEMENUDEFS.CPP:1222-1231] ---- */

/* Decoded Phase 83: MenuExtended_GoToGarage__FR12tMenuCommand(tMenuCommand&) - transition to garage screen (168 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [SEALED 2026-07-06/07, was 10 diffs, now PASS] Fix = reuse the already-computed `this_00`
   pointer for the fCarListFilter store instead of re-deriving `menuDefs[0]->iteratorGarageCar`
   a second time. The old code recomputed the base a second time via
   `(menuDefs[0]->iteratorGarageCar).fCarListFilter = 0x40;`, forcing gcc to hold TWO copies of
   the same address (menuDefs[0]->iteratorGarageCar) live in separate regs (a2 vs a0) across the
   Decrement() jal. `this_00->fCarListFilter = 0x40;` collapses it to one live pointer, matching
   the oracle's single `addiu a0,a0,0x12CC; sw v0,0x10(a0)` (a0 = this_00, used for both the
   store and as Decrement's arg). This is the same "greedy pointer re-derivation" family as the
   sibling GoToDealer/GoToSeller residual but WAS fixable here because this fn had a genuine
   double-derivation to collapse; GoToDealer/GoToSeller do not (see their own near-miss notes). */

/* P873: with native scalar screenCarSelect, the old ternary becomes FAIL8
   at 42/42. The explicit if/else assignments below restore PASS42 and
   the retail SLD1228/1229/1230 condition/then/else partition. The existing
   garageIterator carrier still represents an unrecovered inline this scope. */
void MenuExtended_GoToGarage(tMenuCommand &command)
{
  frontEnd.carListType = '';
  menuDefs->iteratorGarageCar.SetFilter(0x40);
  menuDefs->iteratorGarageCar.tListIteratorCar::Decrement(kPlayerBoth);
  menuDefs->iteratorGarageCar.Increment(kPlayerBoth);
  command.type = kMenu_Command_GoToMenu;
  if (Tournament_CurrentTrack(tournamentManager) == 0) {
    command.nextMenu = (tMenu *)&menuDefs->menuCarGarage;
  } else {
    command.nextMenu = (tMenu *)&menuDefs->menuPostCarGarage;
  }
  screenCarSelect->SetState(1);
}



/* ---- MenuExtended_GoToTournTrophyRoom__FR12tMenuCommand  [FEMENUDEFS.CPP:1235-1236] ---- */

/* Decoded Phase 83: MenuExtended_GoToTournTrophyRoom__FR12tMenuCommand(tMenuCommand&) - transition to tournament
   trophy room (12 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int
   MenuExtended_GoToTournTrophyRoom__FR12tMenuCommand(int arg0)'. Fixed via m2c body (arg0 = struct
   deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern. */

void MenuExtended_GoToTournTrophyRoom(tMenuCommand &)

{
  frontEnd.tier = '\0';
  return;
}



/* ---- MenuExtended_GoToSETrophyRoom__FR12tMenuCommand  [FEMENUDEFS.CPP:1240-1241] ---- */

/* Decoded Phase 83: MenuExtended_GoToSETrophyRoom__FR12tMenuCommand(tMenuCommand&) - transition to special-event
   trophy room (16 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_GoToSETrophyRoom__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_GoToSETrophyRoom(tMenuCommand &)

{
  frontEnd.tier = '\x01';
  return;
}



/* ---- MenuExtended_SetBeginner__FR12tMenuCommand  [FEMENUDEFS.CPP:1245-1246] ---- */

/* Decoded Phase 83: MenuExtended_SetBeginner__FR12tMenuCommand(tMenuCommand&) - set difficulty=Beginner (12 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetBeginner__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetBeginner(tMenuCommand &)

{
  frontEnd.skillLevel = '\0';
  return;
}



/* ---- MenuExtended_SetIntermediate__FR12tMenuCommand  [FEMENUDEFS.CPP:1250-1251] ---- */

/* Decoded Phase 83: MenuExtended_SetIntermediate__FR12tMenuCommand(tMenuCommand&) - set difficulty=Intermediate (16
   B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetIntermediate__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetIntermediate(tMenuCommand &)

{
  frontEnd.skillLevel = '\x01';
  return;
}



/* ---- MenuExtended_SetExpert__FR12tMenuCommand  [FEMENUDEFS.CPP:1255-1256] ---- */

/* Decoded Phase 83: MenuExtended_SetExpert__FR12tMenuCommand(tMenuCommand&) - set difficulty=Expert (16 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetExpert__FR12tMenuCommand(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetExpert(tMenuCommand &)

{
  frontEnd.skillLevel = '\x02';
  return;
}



/* ---- MenuExtended_ExitTourney__FR12tMenuCommand  [FEMENUDEFS.CPP:1260-1271] ---- */

/* Decoded Phase 83: MenuExtended_ExitTourney__FR12tMenuCommand(tMenuCommand&) - abandon current tournament, return to
   main menu (144 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [SYM restoration 2026-08-25] The caller SYM records only `command` and the
   stack object `AreYouSure`.  Consuming Run directly removes the unrecorded
   result local at exact 36/36.  Spelling nextMenu before type removes the
   unrecorded menu pointer while the scheduler retains retail's type-first
   store order. P880 removes the remaining dialog carrier through the existing
   inline setup boundary; raw direct field stores alone did not preserve it. */

void MenuExtended_ExitTourney(tMenuCommand &command)

{
  /* P880: existing inline operations recover native this REG16 without an
     extra caller pointer. PASS36/exact-g; original inline spellings and the
     combined constructor/setup SLD boundary remain unresolved. */
  tDialogYesNo AreYouSure;

  AreYouSure.SetChoices(0x321,0x322,0);
  AreYouSure.SetString(TextSys_Word(0x9d));
  if (AreYouSure.Run() != 0) {
    command.nextMenu = (tMenu *)&menuDefs->menuMain;
    command.type = kMenu_Command_GoToMenuOneWay;
  }
  else {
    command.type = kMenu_Command_None;
  }
  return;
}



/* ---- MenuExtended_ExitPinkSlipsEarly__FR12tMenuCommand  [FEMENUDEFS.CPP:1274-1300] ---- */

/* Decoded Phase 83: MenuExtended_ExitPinkSlipsEarly__FR12tMenuCommand(tMenuCommand&) - allow user to back out of
   pinkslips before commit (304 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [NEAR-MISS 2026-07-05, was 32 diffs, now 15] Real fix: the declared-but-unused `dlgThis`
   local IS the oracle's hoisted `&AreYouSure` base (oracle materializes it ONCE via
   `addiu s0,sp,0x10` right after the ctor and reaches yesnowords/fDefault/string through it;
   our direct `AreYouSure.field` accesses were emitting raw sp-relative offsets instead).
   2026-08-03 GCC follow-up: the catalogued exit-in-the-middle loop shape
   (`while(true) { if (2 <= player) break; ...; }`) prevents loop rotation and restores the
   oracle's PRE-loop `slti/beqz` plus unconditional back-edge jump. This reduces 10->4 diffs
   at exact 76/76 instruction parity. The remaining pair is only the FEApp address scratch
   (`lui/lw a0` versus retail's `lui v0; lw a0`); a nested pointer and an explicit two-step
   pointer increment compile identically, so this is the known materialization tie-break.

   [BUG FIX 2026-07-27, 13->10] Same DOUBLE-DESTRUCTION bug: dropped the manual
   `tScreen_dtor((tScreen*)&AreYouSure,2)` firing alongside AreYouSure's own auto-invoked
   destructor. */

/* [W57-A1 2026-08-09, 18->PASS] Two levers: (a) GOTO BACK-EDGE loop (`nextPlayer: if (player<2)
   {...; goto nextPlayer;}`) instead of `while(true){if(2<=p)break;...}` -- it defeats LICM's
   hoist of `%hi(FEApp)` into a 4th saved reg (s3), which was the whole +2-insn / extra-s-reg
   delta; (b) the loop-invariant `&string` hoisted BY HAND into `msg` before the loop, because the
   same goto shape also suppresses LICM for THAT address (oracle materializes `addiu s2,sp,184`
   once, pre-loop).  So: LICM off for the global, on (manually) for the frame address. */

void MenuExtended_ExitPinkSlipsEarly(tMenuCommand &command)

{
  /* P879: the final command stores no longer require a menuDefsBase alias. */
  /* SYM 8c Def-record order: AreYouSure, string, player; the measured codegen
     carriers follow the SYM set. */
  tDialogYesNo AreYouSure;
  /* P880: existing inline choice/string operations replace dlgThis and keep
     native this REG16. The independent msg/loop-scope debt is unchanged. */
  /* SYM-CODEGEN-CARRIER: msg -- direct `string` use is count-exact FAIL 20
     and births the frame address inside the loop instead of pre-loop `$s2`. */
  char *msg;
  
  AreYouSure.SetChoices(0x321,0x322,0);
  AreYouSure.SetString(TextSys_Word(0x9d));
  if (AreYouSure.Run() != 0) {
    char string [80];
    int player;

    Init_Memcard(false,1);
    player = 0;
    msg = string;
  nextPlayer:
    if (player < 2) {
      sprintf(msg,TextSys_Word(0x297),PlayerName(player),player + 1);
      (FEApp->NoInputMemCardDialog).string = msg;
      SavePinkSlipsCarsWithErrorDialogs((short)player,1,-1);
      player = player + 1;
      goto nextPlayer;
    }
    DeInit_Memcard();
    ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Hide();
    command.type = kMenu_Command_GoToMenuOneWay;
    command.nextMenu = (tMenu *)(tMenu*)&menuDefs->menuMain;
    frontEnd.raceType = '\0';
  }
  return;
}



/* ---- MenuExtended_PinkSlipsContinue__FR12tMenuCommand  [FEMENUDEFS.CPP:1304-1315] ---- */

/* Decoded Phase 83: MenuExtended_PinkSlipsContinue__FR12tMenuCommand(tMenuCommand&) - after pinkslips win, continue
   to next race (108 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer

   [ghidra-meta] section: front.text

   [SYM/source 2026-08-25] Retail records only `command`. Repeating the promoted
   track-threshold expression lets GCC CSE it while retaining signed `slt` for
   both byte-field comparisons. Spelling nextMenu before type loads menuDefs only
   on the GoToMenuOneWay path and removes ptVar1. The physical block-order swap
   (else-body first, win-body reached via the trailing goto) preserves retail
   polarity. This local-free form is exact PASS 27/27 with an exact -g twin. */

void MenuExtended_PinkSlipsContinue(tMenuCommand &command)

{
  if ((byte)frontEnd.pinkSlipsWins[0] <
      ((byte)frontEnd.pinkSlipsNumTracks >> 1) + 1) {
    if ((byte)frontEnd.pinkSlipsWins[1] <
        ((byte)frontEnd.pinkSlipsNumTracks >> 1) + 1) {
      goto winCase;
    }
  }
  command.nextMenu = (tMenu *)&menuDefs->menuPinkSlipCongrats;
  command.type = kMenu_Command_GoToMenuOneWay;
  return;
winCase:
  frontEnd.pinkSlipsTrackIndex = frontEnd.pinkSlipsTrackIndex + '\x01';
  command.type = kMenu_Command_StartRace;
  return;
}



/* ---- tGlobalMenuDefs::ctor  [FEMENUDEFS.CPP:1353-2200] ---- */

/* Built with -g, like the retail object (the SYM carries full local/block info for this
   function).  gcc 2.8's CSE flushes its hash table every 1001 RTL chain objects and counts
   NOTEs too (cse.c: `if (num_insns++ > 1000)`), so the line notes that -g adds -- including
   the ones copied from inline constructor bodies in screendisplay_types.h -- decide where the
   flushes land.  The source therefore needs no codegen dials; see tools/build.py "debug_g".

   SYM cross-check: 34 top-level blocks / 105 blocks in all; the 37 inline-ctor `this` locals
   and the 3 `child` locals get retail's registers and stack slots; the body holds exactly
   16 inline expansions (3 SetChildMenu, 4 SetCarFilter, 7 SetVertHelp, GetFlags+SetFlags). */

static inline void A1_SetChildMenu(tMenu *parent, tMenu *child) { parent->fChildMenu = child; }
static inline void A1_SetCarFilter(tListIteratorCar *it, int f) { it->fCarListFilter = f; }
static inline void A1_SetVertHelp(tMenu *m, short v) { m->VertHelp = v; }
static inline int A1_GetFlags(tMenuItem *i) { return i->fFlags; }
static inline void A1_SetFlags(tMenuItem *i, int f) { i->fFlags = f; }
tGlobalMenuDefs::tGlobalMenuDefs()
 : itemMainOnePlayerRace(0x5b, (tMenu*)&menuOnePlayer, (void (*)(tMenuCommand&))MenuExtended_SetOnePlayer, 0x1e, 10)   /* +0x0 tMenuItemGoToMenuNFS4Button */
 , itemMainTwoPlayerRace(0x5c, (tMenu*)&menuTwoPlayer, (void (*)(tMenuCommand&))MenuExtended_SetTwoPlayer, 0x28, 10)   /* +0x2C tMenuItemGoToMenuNFS4Button */
 , itemMainTrophyRoom(0x5e, (tMenu*)&menuTrophyRoomSelect, 0, 0x32, 10)   /* +0x58 tMenuItemGoToMenuNFS4Button */
 , itemMainOptions(0x5d, (tMenu*)&menuOptions, 0, 0x3c, 10)   /* +0x84 tMenuItemGoToMenuNFS4Button */
 , menuMain(0x1014, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb4, (tMenuItem *)&itemMainOnePlayerRace, &itemMainTwoPlayerRace, &itemMainOptions, &itemMainTrophyRoom, 0)   /* +0xB0 tMenuNFS4 */
 , itemTournTrophyRoom(99, (tMenu *)&menuTrophyRoom, (void (*)(tMenuCommand&))MenuExtended_GoToTournTrophyRoom, 0x32, 10)   /* +0x12C tMenuItemGoToMenuNFS4Button */
 , itemSETrophyRoom(0x69, (tMenu *)&menuTrophyRoom, (void (*)(tMenuCommand&))MenuExtended_GoToSETrophyRoom, 0x32, 10)   /* +0x158 tMenuItemGoToMenuNFS4Button */
 , menuTrophyRoomSelect(0x1014, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0x5f, (tMenuItem *)&itemTournTrophyRoom, &itemSETrophyRoom, 0)   /* +0x184 tMenuNFS4 */
 , menuTrophyInfo(0x4000, (tScreen *)screenTrophyInfo, (tMenu *)0x0, (tMenu *)0x0, 0, -1)   /* +0x200 tMenuBlank */
 , itemSkillBeginner(0xa1, (tMenu*)&menuSingleTrackSelect, (void (*)(tMenuCommand&))MenuExtended_SetBeginner, 0x8c, 10)   /* +0x27C tMenuItemGoToMenuNFS4Button */
 , itemSkillIntermediate(0xa2, (tMenu*)&menuSingleTrackSelect, (void (*)(tMenuCommand&))MenuExtended_SetIntermediate, 0x96, 10)   /* +0x2A8 tMenuItemGoToMenuNFS4Button */
 , itemSkillExpert(0xa3, (tMenu*)&menuSingleTrackSelect, (void (*)(tMenuCommand&))MenuExtended_SetExpert, 0xa0, 10)   /* +0x2D4 tMenuItemGoToMenuNFS4Button */
 , menuSkillLevel(0x1004, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb7, (tMenuItem *)&itemSkillBeginner, &itemSkillIntermediate, &itemSkillExpert, 0)   /* +0x300 tMenuNFS4 */
 , itemOnePlayerTestDrive(0x60, (tMenu*)&menuTestDriveTrackSelect, (void (*)(tMenuCommand&))MenuExtended_SetTestDrive, 0xf0, 10)   /* +0x37C tMenuItemGoToMenuNFS4Button */
 , itemOnePlayerSingleRace(0x72, (tMenu*)&menuSingleRace, (void (*)(tMenuCommand&))MenuExtended_SetSingleRace, 0x46, 10)   /* +0x3A8 tMenuItemGoToMenuNFS4Button */
 , itemOnePlayerPursuit(0x71, (tMenu*)&menuHotPursuit, (void (*)(tMenuCommand&))MenuExtended_SetHotPursuit, 0x50, 10)   /* +0x3D4 tMenuItemGoToMenuNFS4Button */
 , itemOnePlayerTournament(99, (tMenu*)&menuTournament, (void (*)(tMenuCommand&))MenuExtended_SetTournament, 0x5a, 10)   /* +0x400 tMenuItemGoToMenuNFS4Button */
 , itemOnePlayerSpecialEvents(0x69, (tMenu*)&menuSpecialEvent, (void (*)(tMenuCommand&))MenuExtended_SetSpecialEvent, 100, 10)   /* +0x42C tMenuItemGoToMenuNFS4Button */
 , menuOnePlayer(0x1004, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb5, (tMenuItem *)&itemOnePlayerTestDrive, &itemOnePlayerSingleRace, &itemOnePlayerPursuit, &itemOnePlayerTournament, &itemOnePlayerSpecialEvents, 0)   /* +0x458 tMenuNFS4 */
 , itemSingleRaceSolo(0x6c, (tMenu*)&menuSingleTrackSelect, (void (*)(tMenuCommand&))MenuExtended_SetSoloRace, 0x6e, 10)   /* +0x4D4 tMenuItemGoToMenuNFS4Button */
 , itemSingleRaceDuel(0x6d, (tMenu*)&menuSkillLevel, (void (*)(tMenuCommand&))MenuExtended_SetDuelRace, 0x78, 10)   /* +0x500 tMenuItemGoToMenuNFS4Button */
 , itemSingleRaceFullGrid(0x6f, (tMenu*)&menuSkillLevel, (void (*)(tMenuCommand&))MenuExtended_SetFullGrid, 0x82, 10)   /* +0x52C tMenuItemGoToMenuNFS4Button */
 , menuSingleRace(0x1004, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb6, (tMenuItem *)&itemSingleRaceSolo, &itemSingleRaceDuel, &itemSingleRaceFullGrid, 0)   /* +0x558 tMenuNFS4 */
 , itemHotPursuitSolo(0x6c, (tMenu*)&menuSkillLevel, (void (*)(tMenuCommand&))MenuExtended_SetHPSoloRace, 0x6e, 10)   /* +0x5D4 tMenuItemGoToMenuNFS4Button */
 , itemHotPursuitDuel(0x6d, (tMenu*)&menuSkillLevel, (void (*)(tMenuCommand&))MenuExtended_SetHPDuelRace, 0x78, 10)   /* +0x600 tMenuItemGoToMenuNFS4Button */
 , menuHotPursuit(0x1004, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb6, (tMenuItem *)&itemHotPursuitSolo, &itemHotPursuitDuel, 0)   /* +0x62C tMenuNFS4 */
 , iteratorTournament(&frontEnd.tournament, &tournamentManager)   /* +0x6A8 tListIteratorTournament */
 , itemTournamentContinue(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToTournTrackInfo, 0x22, 10)   /* +0x6BC tMenuItemGoToMenuNFS4Button */
 , itemTournamentSelect(0x94, (tListIterator *)&iteratorTournament, 0x2c, 10)   /* +0x6E8 tMenuItemNFS4LeftRightChoice */
 , menuTournament(0x1000, (tScreen *)screenTournSelect, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToTournTrackInfo, 0x65, (tMenuItem *)&itemTournamentContinue, &itemTournamentSelect, 0)   /* +0x710 tMenuNFS4 */
 , iteratorSpecialEvent(&frontEnd.specialevent, &tournamentManager)   /* +0x78C tListIteratorTournament */
 , itemSpecialEventContinue(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToSpecialEventTrackInfo, 0x22, 10)   /* +0x7A0 tMenuItemGoToMenuNFS4Button */
 , itemSpecialEventSelect(0x69, (tListIterator *)&iteratorSpecialEvent, 0x36, 10)   /* +0x7CC tMenuItemNFS4LeftRightChoice */
 , menuSpecialEvent(0x1000, (tScreen *)screenTournSelect, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToSpecialEventTrackInfo, 100, (tMenuItem *)&itemSpecialEventContinue, &itemSpecialEventSelect, 0)   /* +0x7F4 tMenuNFS4 */
 , itemTwoPlayerTestDrive(0x60, (tMenu*)&menuTestDriveTrackSelect, (void (*)(tMenuCommand&))MenuExtended_SetTestDrive, 0xf0, 10)   /* +0x870 tMenuItemGoToMenuNFS4Button */
 , itemTwoPlayerDuel(0x72, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToTwoPlayerSingleRace, 0x46, 10)   /* +0x89C tMenuItemGoToMenuNFS4Button */
 , itemTwoPlayerHotPursuit(0x71, (tMenu*)&menuSkillLevel, (void (*)(tMenuCommand&))MenuExtended_SetHotPursuit, 0x50, 10)   /* +0x8C8 tMenuItemGoToMenuNFS4Button */
 , itemTwoPlayerPinkSlips(0x6a, (tMenu*)&menuPinkSlipSelect, (void (*)(tMenuCommand&))MenuExtended_SetPinkSlips, 0xaa, 10)   /* +0x8F4 tMenuItemGoToMenuNFS4Button */
 , menuTwoPlayer(0x1004, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb5, (tMenuItem *)&itemTwoPlayerTestDrive, &itemTwoPlayerDuel, &itemTwoPlayerHotPursuit, &itemTwoPlayerPinkSlips, 0)   /* +0x920 tMenuNFS4 */
 , itemBestOfOne(0xc0, (tMenu*)&menuSingleTrackSelect, (void (*)(tMenuCommand&))MenuExtended_GoToBestOfOne, 0xaa, 10)   /* +0x99C tMenuItemGoToMenuNFS4Button */
 , itemBestOfThree(0xc1, (tMenu*)&menuPinkSlipsBestOfThree, (void (*)(tMenuCommand&))MenuExtended_GoToBestOfThree, 0xaa, 10)   /* +0x9C8 tMenuItemGoToMenuNFS4Button */
 , itemBestOfFive(0xc2, (tMenu*)&menuPinkSlipsBestOfFive, (void (*)(tMenuCommand&))MenuExtended_GoToBestOfFive, 0xaa, 10)   /* +0x9F4 tMenuItemGoToMenuNFS4Button */
 , menuPinkSlipSelect(0x1000, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb6, (tMenuItem *)&itemBestOfOne, &itemBestOfThree, &itemBestOfFive, 0)   /* +0xA20 tMenuNFS4 */
 , itemPinkSlipsContinue(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToCarSelect, 0x24, 10)   /* +0xA9C tMenuItemGoToMenuNFS4Button */
 , itemTrack1(0xc3, (tListIterator *)&iteratorTrack, 0x2e, 10)   /* +0xAC8 tMenuItemNFS4LeftRightChoice */
 , itemTrack2(0xc4, (tListIterator *)&iteratorTrack, 0x2e, 10)   /* +0xAF0 tMenuItemNFS4LeftRightChoice */
 , itemTrack3(0xc5, (tListIterator *)&iteratorTrack, 0x2e, 10)   /* +0xB18 tMenuItemNFS4LeftRightChoice */
 , itemTrack4(0xc6, (tListIterator *)&iteratorTrack, 0x2e, 10)   /* +0xB40 tMenuItemNFS4LeftRightChoice */
 , itemTrack5(199, (tListIterator *)&iteratorTrack, 0x2e, 10)   /* +0xB68 tMenuItemNFS4LeftRightChoice */
 , menuPinkSlipsBestOfThree(0x1400, (tScreen *)screenPinkSlips, (tMenu *)0x0, (tMenu *)&menuTrackOptions, (void (*)(tMenuCommand&))MenuExtended_GoToCarSelect, 0xbe, (tMenuItem *)&itemPinkSlipsContinue, &itemTrack1, &itemTrack2, &itemTrack3, 0)   /* +0xB90 tMenuNFS4 */
 , menuPinkSlipsBestOfFive(0x1400, (tScreen *)screenPinkSlips, (tMenu *)0x0, (tMenu *)&menuTrackOptions, (void (*)(tMenuCommand&))MenuExtended_GoToCarSelect, 0xbf, (tMenuItem *)&itemPinkSlipsContinue, &itemTrack1, &itemTrack2, &itemTrack3, &itemTrack4, &itemTrack5, 0)   /* +0xC0C tMenuNFS4 */
 , iteratorTrack(frontEnd.track, &frontEnd.pinkSlipsTrackIndex, &trackManager)   /* +0xC88 tListIteratorTrack */
 , itemTrackContinue(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToCarSelect, 0x1c, 10)   /* +0xCA0 tMenuItemGoToMenuNFS4Button */
 , itemTrack(0x93, (tListIterator *)&iteratorTrack, 0x26, 10)   /* +0xCCC tMenuItemNFS4LeftRightChoice */
 , itemTrackRecords(0xd4, (tMenu*)&menuTrackRecords, 0, 0x3a, 10)   /* +0xCF4 tMenuItemGoToMenuNFS4Button */
 , menuSingleTrackSelect(0x1600, (tScreen *)screenTrackSelect, (tMenu *)0x0, (tMenu *)&menuTrackOptions, (void (*)(tMenuCommand&))MenuExtended_GoToCarSelect, 200, (tMenuItem *)&itemTrackContinue, &itemTrack, &itemTrackRecords, 0)   /* +0xD20 tMenuNFS4 */
 , menuTestDriveTrackSelect(0x1600, (tScreen *)screenTrackSelect, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToCarSelect, 200, (tMenuItem *)&itemTrackContinue, &itemTrack, &itemTrackRecords, 0)   /* +0xD9C tMenuNFS4 */
 , iteratorLaps(SelectListNormal, frontEnd.lapind, &frontEnd.pinkSlipsTrackIndex)   /* +0xE18 tListIteratorIndexed */
 , iteratorTrackDirection(SelectListTrackDirection, frontEnd.trackdirection, &frontEnd.pinkSlipsTrackIndex)   /* +0xE2C */
 , iteratorTrackMirrored(SelectListOffOn, frontEnd.trackmirrored, &frontEnd.pinkSlipsTrackIndex)   /* +0xE40 */
 , iteratorTimeOfDay(SelectListOffOn, frontEnd.timeOfDay, &frontEnd.pinkSlipsTrackIndex)   /* +0xE54 */
 , iteratorWeather(SelectListOffOn, frontEnd.weather, &frontEnd.pinkSlipsTrackIndex)   /* +0xE68 */
 , iteratorTraffic(SelectListOffOn, frontEnd.traffic, &frontEnd.pinkSlipsTrackIndex)   /* +0xE7C */
 , iteratorLocalSpeech(SelectListOffOn, &frontEnd.localSpeech)   /* +0xE90 tListIterator */
 , itemLaps(0xca, (tListIterator *)&iteratorLaps)   /* +0xEA0 tMenuItemOptionsLeftRightChoice */
 , itemTrackDirection(0xcc, (tListIterator *)&iteratorTrackDirection)   /* +0xEC0 tMenuItemOptionsLeftRightChoice */
 , itemTrackMirrored(0xcd, (tListIterator *)&iteratorTrackMirrored)   /* +0xEE0 tMenuItemOptionsTwoItemChoice */
 , itemTimeOfDay(0xce, (tListIterator *)&iteratorTimeOfDay)   /* +0xF04 tMenuItemOptionsTwoItemChoice */
 , itemWeather(0xcf, (tListIterator *)&iteratorWeather)   /* +0xF28 tMenuItemOptionsTwoItemChoice */
 , itemTraffic(0xd0, (tListIterator *)&iteratorTraffic)   /* +0xF4C tMenuItemOptionsTwoItemChoice */
 , itemLocalSpeech(0xd2, &iteratorLocalSpeech)   /* +0xF70 tMenuItemOptionsTwoItemChoice */
 , menuTrackOptions(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, 0xb9, -1, (tMenuItem *)&itemLaps, &itemTrackDirection, &itemTrackMirrored, &itemTimeOfDay, &itemWeather, &itemTraffic, &itemLocalSpeech, 0)   /* +0xF94 tMenuOptions */
 , menuTrackRecordsItem(0, (tMenu *)0x0, 0, -1, -1)   /* +0x1018 tBlankMenuItemGoToMenuNFS4Button */
 , menuTrackRecords(0x1000, (tScreen *)screenTrackRecords, (tMenu *)0x0, (tMenu *)0x0, 0, 0xd4, 1, 10, (tMenuItem *)0x0)   /* +0x1044 tOptionsMenu */
 , itemTrackInfoContinue(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToGarage, 0x21, 10)   /* +0x10C4 tMenuItemGoToMenuNFS4Button */
 , menuTrackInfo(0x1004, (tScreen *)screenTrackInfo, (tMenu *)0x0, (tMenu *)0x0, 0, 0xf9, (tMenuItem *)&itemTrackInfoContinue, 0)   /* +0x10F0 tMenuNFS4 */
 , iteratorCar1(frontEnd.playerCar, &carManager)   /* +0x116C tListIteratorCar */
 , iteratorColor(frontEnd.carColors[0], &FEApp->fPlayer, frontEnd.playerCar, 0x30, &carManager)   /* +0x1188 tListIteratorCarColor */
 , itemCarSelectRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToRace, 0x80, 10)   /* +0x11A8 tMenuItemGoToMenuNFS4Button */
 , itemCar(0x92, (tListIterator *)&iteratorCar1, 0x1c, 10)   /* +0x11D4 tMenuItemNFS4LeftRightChoice */
 , itemColor(0x120, (tListIterator *)&iteratorColor, 0x26, 10)   /* +0x11FC tMenuItemNFS4LeftRightChoice */
 , itemShowcase(0x112, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToShowroom, 0x30, 10)   /* +0x1224 tMenuItemGoToMenuNFS4Button */
 , menuSingleCarSelect(0x1a00, (tScreen *)screenCarSelect, (tMenu *)0x0, (tMenu *)&menuCarOptions, (void (*)(tMenuCommand&))MenuExtended_GoToRace, 0xba, (tMenuItem *)&itemCarSelectRace, &itemCar, &itemColor, &itemShowcase, 0)   /* +0x1250 tMenuNFS4 */
 , iteratorGarageCar(frontEnd.garageCar, &carManager)   /* +0x12CC tListIteratorCar */
 , itemGarageCar(0x92, (tListIterator *)&iteratorGarageCar, 0x1c, 10)   /* +0x12E8 tMenuItemNFS4LeftRightChoice */
 , itemCarDealer(0x74, (tMenu*)&menuGoToCarDealer, 0, 0x3a, 10)   /* +0x1310 tMenuItemGoToMenuNFS4Button */
 , itemUpgradeCar(0x91, (tMenu *)0x0, MenuExtended_GoToUpgrades, 0x44, 10)   /* +0x133C tMenuItemGoToMenuNFS4Button */
 , menuCarGarage(0x1a00, (tScreen *)screenCarSelect, (tMenu *)0x0, (tMenu *)&menuCarOptions, (void (*)(tMenuCommand&))MenuExtended_GoToRace, 0x8f, (tMenuItem *)&itemCarSelectRace, &itemGarageCar, &itemCarDealer, &itemUpgradeCar, 0)   /* +0x1368 tMenuNFS4 */
 , menuPostCarGarage(0x1a00, (tScreen *)screenCarSelect, (tMenu *)0x0, (tMenu *)&menuCarOptions, (void (*)(tMenuCommand&))MenuExtended_GoToRace, 0x8f, (tMenuItem *)&itemCarSelectRace, &itemUpgradeCar, 0)   /* +0x13E4 tMenuNFS4 */
 , iteratorOpponentCar(&frontEnd.oppCar, &carManager)   /* +0x1460 tListIteratorCar */
 , itemDuelRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToRace, 0x2a, 10)   /* +0x147C tMenuItemGoToMenuNFS4Button */
 , itemCar2(0x92, (tListIterator *)&iteratorCar1, 0xc, 10)   /* +0x14A8 tMenuItemNFS4LeftRightChoice */
 , itemColor2(0x120, (tListIterator *)&iteratorColor, 0x16, 10)   /* +0x14D0 tMenuItemNFS4LeftRightChoice */
 , itemGoToDuelBuyCar(0x78, (tMenu*)&menuCarDealer, MenuExtended_GoToDealer, -1, 10)   /* +0x14F8 tMenuItemGoToMenuNFS4Button */
 , itemOpponentCar(0xbc, (tListIterator *)&iteratorOpponentCar, 0x20, 10)   /* +0x1524 tMenuItemNFS4LeftRightChoice */
 , menuDuelCarSelect(0x1800, (tScreen *)screenCarSelectDuel, (tMenu *)0x0, (tMenu *)&menuCarOptions, (void (*)(tMenuCommand&))MenuExtended_GoToRace, 0xba, (tMenuItem *)&itemDuelRace, &itemGarageCar, &itemGoToDuelBuyCar, &itemOpponentCar, 0)   /* +0x154C tMenuNFS4 */
 , menuHPDuelCarSelect(0x1800, (tScreen *)screenCarSelectDuel, (tMenu *)0x0, (tMenu *)&menuCarOptions, (void (*)(tMenuCommand&))MenuExtended_GoToRace, 0xba, (tMenuItem *)&itemDuelRace, &itemCar, &itemColor, &itemOpponentCar, 0)   /* +0x15C8 tMenuNFS4 */
 , itemPlayerOneRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0x2a, 10)   /* +0x1644 tMenuItemGoToMenuNFS4Button */
 , itemCarP1(0x92, (tListIterator *)&iteratorCar1, 0xc, 10)   /* +0x1670 tMenuItemNFS4LeftRightChoice */
 , itemColorP1(0x120, (tListIterator *)&iteratorColor, 0x16, 10)   /* +0x1698 tMenuItemNFS4LeftRightChoice */
 , menuPlayerOneCarSelect(0x1008, (tScreen *)screenCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)&menuCarOptionsPlayerOne, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0xba, (tMenuItem *)&itemPlayerOneRace, &itemCarP1, &itemColorP1, 0)   /* +0x16C0 tMenuNFS4TwoPlayer */
 , itemPlayerTwoRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0x2a, 10)   /* +0x173C tMenuItemGoToMenuNFS4Button */
 , itemCarP2(0x92, (tListIterator *)&iteratorCar1, 0xc, 10)   /* +0x1768 tMenuItemNFS4LeftRightChoice */
 , itemColorP2(0x120, (tListIterator *)&iteratorColor, 0x16, 10)   /* +0x1790 tMenuItemNFS4LeftRightChoice */
 , menuPlayerTwoCarSelect(0x1008, (tScreen *)screenCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)&menuCarOptionsPlayerTwo, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0xba, (tMenuItem *)&itemPlayerTwoRace, &itemCarP2, &itemColorP2, 0)   /* +0x17B8 tMenuNFS4TwoPlayer */
 , itemPlayerOneGarageRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0x2a, 10)   /* +0x1834 tMenuItemGoToMenuNFS4Button */
 , itemGarageCarP1(0x92, (tListIterator *)&iteratorGarageCar, 0xc, 10)   /* +0x1860 tMenuItemNFS4LeftRightChoice */
 , menuPlayerOneGarage(0x1008, (tScreen *)screenCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)&menuCarOptionsPlayerOne, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0xba, (tMenuItem *)&itemPlayerOneRace, &itemGarageCarP1, 0)   /* +0x1888 tMenuNFS4TwoPlayer */
 , itemPlayerTwoGarageRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0x2a, 10)   /* +0x1904 tMenuItemGoToMenuNFS4Button */
 , itemGarageCarP2(0x92, (tListIterator *)&iteratorGarageCar, 0xc, 10)   /* +0x1930 tMenuItemNFS4LeftRightChoice */
 , menuPlayerTwoGarage(0x1008, (tScreen *)screenCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)&menuCarOptionsPlayerTwo, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0xba, (tMenuItem *)&itemPlayerTwoGarageRace, &itemGarageCarP2, 0)   /* +0x1958 tMenuNFS4TwoPlayer */
 , iteratorPinkSlipsCar(frontEnd.pinkSlipsCar, &carManager)   /* +0x19D4 tListIteratorCar */
 , itemPlayerOnePinkSlipRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0x2a, 10)   /* +0x19F0 tMenuItemGoToMenuNFS4Button */
 , itemPinkSlipCarP1(0x92, (tListIterator *)&iteratorPinkSlipsCar, 0xc, 10)   /* +0x1A1C tMenuItemNFS4LeftRightChoice */
 , menuPlayerOnePinkSlipCarSelect(0x1008, (tScreen *)screenPinkSlipsCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)&menuPinkSlipCarOptionsPlayerOne, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0xba, (tMenuItem *)&itemPlayerOnePinkSlipRace, &itemPinkSlipCarP1, 0)   /* +0x1A44 tMenuNFS4TwoPlayer */
 , itemPlayerTwoPinkSlipRace(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0x2a, 10)   /* +0x1AC0 tMenuItemGoToMenuNFS4Button */
 , itemPinkSlipCarP2(0x92, (tListIterator *)&iteratorPinkSlipsCar, 0xc, 10)   /* +0x1AEC tMenuItemNFS4LeftRightChoice */
 , menuPlayerTwoPinkSlipCarSelect(0x1008, (tScreen *)screenPinkSlipsCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)&menuPinkSlipCarOptionsPlayerTwo, (void (*)(tMenuCommand&))MenuExtended_GoTo2PlayerRace, 0xba, (tMenuItem *)&itemPlayerTwoPinkSlipRace, &itemPinkSlipCarP2, 0)   /* +0x1B14 tMenuNFS4TwoPlayer */
 , itemGoToBuyCar(0x78, (tMenu*)&menuCarDealer, MenuExtended_GoToDealer, 0x58, 10)   /* +0x1B90 tMenuItemGoToMenuNFS4Button */
 , itemGoToSellCar(0x79, (tMenu*)&menuCarSeller, MenuExtended_GoToSeller, 0x4e, 10)   /* +0x1BBC tMenuItemGoToMenuNFS4Button */
 , menuGoToCarDealer(0x1200, (tScreen *)screenCarSelect, (tMenu *)0x0, (tMenu *)0x0, 0, 0x90, (tMenuItem *)&itemGoToBuyCar, &itemGoToSellCar, 0)   /* +0x1BE8 tMenuNFS4 */
 , iteratorDealerCar(&frontEnd.dealerCar, &carManager)   /* +0x1C64 tListIteratorCar */
 , iteratorDealerColor(frontEnd.carColors[0], &FEApp->fPlayer, &frontEnd.dealerCar, 0x30, &carManager)   /* +0x1C80 tListIteratorCarColor */
 , itemDealerCar(0x92, (tListIterator *)&iteratorDealerCar, 0x1c, 10)   /* +0x1CA0 tMenuItemNFS4LeftRightChoice */
 , itemDealerColor(0x120, (tListIterator *)&iteratorDealerColor, 0x26, 10)   /* +0x1CC8 tMenuItemNFS4LeftRightChoice */
 , itemBuyCar(0x75, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_BuyCar, 0x58, 10)   /* +0x1CF0 tMenuItemGoToMenuNFS4Button */
 , itemDealerShowroom(0x112, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_GoToDealerShowroom, 0x30, 10)   /* +0x1D1C tMenuItemGoToMenuNFS4Button */
 , menuCarDealer(0x2240, (tScreen *)screenCarSelect, (tMenu *)0x0, (tMenu *)0x0, 0, 0x90, (tMenuItem *)&itemDealerCar, &itemDealerColor, &itemBuyCar, &itemDealerShowroom, 0)   /* +0x1D48 tMenuNFS4 */
 , iteratorSellerCar(&frontEnd.sellerCar, &carManager)   /* +0x1DC4 tListIteratorCar */
 , itemSellerCar(0x92, (tListIterator *)&iteratorSellerCar, 0x1c, 10)   /* +0x1DE0 tMenuItemNFS4LeftRightChoice */
 , itemSellCar(0x77, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_SellCar, 0x4e, 10)   /* +0x1E08 tMenuItemGoToMenuNFS4Button */
 , menuCarSeller(0x2200, (tScreen *)screenCarSelect, (tMenu *)0x0, (tMenu *)0x0, 0, 0x90, (tMenuItem *)&itemSellerCar, &itemSellCar, 0)   /* +0x1E34 tMenuNFS4 */
 , itemPurchaseUpgrade1(0x96, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_PurchaseUpgrade1, 0x62, 10)   /* +0x1EB0 tMenuItemGoToMenuNFS4Button */
 , itemPurchaseUpgrade2(0x97, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_PurchaseUpgrade2, 0x6c, 10)   /* +0x1EDC tMenuItemGoToMenuNFS4Button */
 , itemPurchaseUpgrade3(0x98, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_PurchaseUpgrade3, 0x76, 10)   /* +0x1F08 tMenuItemGoToMenuNFS4Button */
 , menuCarUpgrades(0x2200, (tScreen *)screenCarSelect, (tMenu *)0x0, (tMenu *)0x0, 0, 0x91, (tMenuItem *)&itemPurchaseUpgrade1, &itemPurchaseUpgrade2, &itemPurchaseUpgrade3, 0)   /* +0x1F34 tMenuNFS4 */
 , iteratorTransmission(SelectListTransmission, frontEnd.transmission, &FEApp->fPlayer)   /* +0x1FB0 tListIteratorIndexed */
 , iteratorABS(SelectListOffOn, frontEnd.ABS, &FEApp->fPlayer)   /* +0x1FC4 tListIteratorIndexed */
 , iteratorDamage(SelectListOffOn, &frontEnd.damage)   /* +0x1FD8 tListIterator */
 , iteratorOpponentUpgrades(SelectListOpponentUpgrades, &frontEnd.opponentUpgrades)   /* +0x1FE8 tListIterator */
 , itemTransmission(0x10a, (tListIterator *)&iteratorTransmission)   /* +0x1FF8 tMenuItemOptionsLeftRightChoice */
 , itemABS(0x10b, (tListIterator *)&iteratorABS)   /* +0x2018 tMenuItemOptionsLeftRightChoice */
 , itemDamage(0x111, &iteratorDamage)   /* +0x2038 tMenuItemOptionsLeftRightChoice */
 , itemTransmission2(0x10a, (tListIterator *)&iteratorTransmission)   /* +0x2058 tMenuItemOptionsLeftRightChoice */
 , itemABS2(0x10b, (tListIterator *)&iteratorABS)   /* +0x2078 tMenuItemOptionsLeftRightChoice */
 , itemDamage2(0x111, &iteratorDamage)   /* +0x2098 tMenuItemOptionsLeftRightChoice */
 , itemOpponentUpgrades(0x10e, &iteratorOpponentUpgrades)   /* +0x20B8 tMenuItemOptionsLeftRightChoice */
 , menuCarOptions(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, 0xbb, -1, (tMenuItem *)&itemTransmission, &itemABS, &itemDamage, &itemOpponentUpgrades, 0)   /* +0x20D8 tMenuOptions */
 , menuCarOptionsPlayerOne(0x1008, (tScreen *)screenCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)0x0, 0, 0xbb, 0, (tMenuItem *)&itemTransmission, &itemABS, &itemDamage, 0)   /* +0x215C tMenuOptions */
 , menuCarOptionsPlayerTwo(0x1008, (tScreen *)screenCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)0x0, 0, 0xbb, 1, (tMenuItem *)&itemTransmission2, &itemABS2, &itemDamage2, 0)   /* +0x21E0 tMenuOptions */
 , menuPinkSlipCarOptionsPlayerOne(0x1008, (tScreen *)screenPinkSlipsCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)0x0, 0, 0xbb, 0, (tMenuItem *)&itemTransmission, &itemABS, &itemDamage, 0)   /* +0x2264 tMenuOptions */
 , menuPinkSlipCarOptionsPlayerTwo(0x1008, (tScreen *)screenPinkSlipsCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)0x0, 0, 0xbb, 1, (tMenuItem *)&itemTransmission2, &itemABS2, &itemDamage2, 0)   /* +0x22E8 tMenuOptions */
 , menuShowroom(0x4000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, -1)   /* +0x236C tMenuBlank */
 , itemOptionsAudio(0x1c5, (tMenu*)&menuAudio, 0, 0xb4, 10)   /* +0x23E8 tMenuItemGoToMenuNFS4Button */
 , itemOptionsDisplay(0x1c6, (tMenu*)&menuDisplayOptions, 0, 0xbe, 10)   /* +0x2414 tMenuItemGoToMenuNFS4Button */
 , itemOptionsControllers(0x1c8, (tMenu*)&menuControllerConfig, 0, 200, 10)   /* +0x2440 tMenuItemGoToMenuNFS4Button */
 , itemOptionsMemoryCard(0x1c9, (tMenu*)&menuMemory, 0, 0xd2, 10)   /* +0x246C tMenuItemGoToMenuNFS4Button */
 , itemOptionsUsername(0x1ca, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_EnterUserName, 0xdc, 10)   /* +0x2498 tMenuItemGoToMenuNFS4Button */
 , itemOptionsCredits(0x1cc, (tMenu *)&menuCredits, 0, 0xe6, 10)   /* +0x24C4 tMenuItemGoToMenuNFS4Button */
 , menuOptions(0x1014, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, 0x5d, (tMenuItem *)&itemOptionsAudio, &itemOptionsDisplay, &itemOptionsControllers, &itemOptionsMemoryCard, &itemOptionsUsername, &itemOptionsCredits, 0)   /* +0x24F0 tMenuNFS4 */
 , iteratorMusicVolume('\0', '\x7f', &frontEnd.musicVolume)   /* +0x256C tListIteratorRange */
 , iteratorSoundEffectsVolume('\0', '\x7f', &frontEnd.sfxVolume)   /* +0x257C */
 , iteratorEngineVolume('\0', '\x7f', &frontEnd.engineVolume)   /* +0x258C */
 , iteratorSpeechVolume('\0', '\x7f', &frontEnd.narrationVolume)   /* +0x259C */
 , iteratorAmbientVolume('\0', '\x7f', &frontEnd.ambientVolume)   /* +0x25AC */
 , iteratorAudioMode(SelectListAudioMode, &frontEnd.audioMode)   /* +0x25BC tListIterator */
 , itemMusicVolume(0x1d5, (tListIterator *)&iteratorMusicVolume, 0)   /* +0x25CC tMenuItemLeftRightAudioSlider */
 , itemSoundEffectsVolume(0x1d6, (tListIterator *)&iteratorSoundEffectsVolume, 1)   /* +0x2604 tMenuItemLeftRightAudioSlider */
 , itemEngineVolume(0x1d7, (tListIterator *)&iteratorEngineVolume, 2)   /* +0x263C tMenuItemLeftRightAudioSlider */
 , itemSpeechVolume(0x1d8, (tListIterator *)&iteratorSpeechVolume, 3)   /* +0x2674 tMenuItemLeftRightAudioSlider */
 , itemAmbientVolume(0x1d9, (tListIterator *)&iteratorAmbientVolume, 4)   /* +0x26AC tMenuItemLeftRightAudioSlider */
 , itemAudioMode(0x1da, &iteratorAudioMode)   /* +0x26E4 tMenuItemDisplayLeftRightChoice */
 , itemSlidingPlayList(0x1db, 0x15e, 0x2b, -0x66, 0xd, false)   /* +0x2710 tMenuItemSlidingActivated */
 , menuPlayListMenu(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, 0, (tMenuItem *)0x0)   /* +0x2758 tInsideBoxSongMenu */
 , menuAudio(0x1010, (tScreen *)screenAudio, (tMenu *)0x0, (tMenu *)0x0, 0, 0x263, 0x26, 10, (tMenuItem *)&itemMusicVolume, &itemSoundEffectsVolume, &itemEngineVolume, &itemSpeechVolume, &itemAmbientVolume, &itemAudioMode, &itemSlidingPlayList, 0)   /* +0x27E0 tOptionsMenu */
 , iteratorDisplaySpeedometer(SelectListDisplaySpeed, frontEnd.displaySpeed, &FEApp->fInputPlayer)   /* +0x2860 tListIteratorIndexed */
 , iteratorDisplayMap(SelectListDisplayMap, frontEnd.displayMap, &FEApp->fInputPlayer)   /* +0x2874 */
 , iteratorDisplayOpponentID(SelectListDisplayOpponentID, frontEnd.displayOpponentID, &FEApp->fInputPlayer)   /* +0x2888 */
 , iteratorDisplayTime(SelectListOffOn, frontEnd.displayTime, &FEApp->fInputPlayer)   /* +0x289C */
 , iteratorDisplayPosition(SelectListOffOn, frontEnd.displayPosition, &FEApp->fInputPlayer)   /* +0x28B0 */
 , iteratorDisplayLapNumber(SelectListOffOn, frontEnd.displayLapNumber, &FEApp->fInputPlayer)   /* +0x28C4 */
 , iteratorDisplaySplitTime(SelectListSplitTime, &frontEnd.checkPointType)   /* +0x28D8 tListIterator */
 , iteratorDisplaySplitDisplay(SelectListSplitDisplay, frontEnd.checkPointDisplay, &FEApp->fInputPlayer)   /* +0x28E8 tListIteratorIndexed */
 , itemDisplaySpeedometer(0x1df, (tListIterator *)&iteratorDisplaySpeedometer)   /* +0x28FC tMenuItemDisplayLeftRightChoice */
 , itemDisplayMap(0x1e1, (tListIterator *)&iteratorDisplayMap)   /* +0x2928 tMenuItemDisplayLeftRightChoice */
 , itemDisplayOpponentID(0x1e2, (tListIterator *)&iteratorDisplayOpponentID)   /* +0x2954 tMenuItemDisplayLeftRightChoice */
 , itemDisplayTime(0x1e3, (tListIterator *)&iteratorDisplayTime)   /* +0x2980 tMenuItemOnOffLeftRightChoice */
 , itemDisplayPosition(0x1e6, (tListIterator *)&iteratorDisplayPosition)   /* +0x29B0 tMenuItemOnOffLeftRightChoice */
 , itemDisplayLapNumber(0x1e7, (tListIterator *)&iteratorDisplayLapNumber)   /* +0x29E0 tMenuItemOnOffLeftRightChoice */
 , itemDisplaySplitTime(0x1e4, &iteratorDisplaySplitTime)   /* +0x2A10 tMenuItemDisplayLeftRightChoice */
 , itemDisplaySplitDisplay(0x1e5, (tListIterator *)&iteratorDisplaySplitDisplay)   /* +0x2A3C tMenuItemDisplayLeftRightChoice */
 , menuDisplayOptions(0x1020, (tScreen *)screenDisplay, (tMenu *)0x0, (tMenu *)0x0, 0, 0x1dd, 1, 10, (tMenuItem *)&itemDisplaySpeedometer, &itemDisplayMap, &itemDisplayOpponentID, &itemDisplayTime, &itemDisplaySplitTime, &itemDisplaySplitDisplay, &itemDisplayPosition, &itemDisplayLapNumber, 0)   /* +0x2A68 tOptionsMenu */
 , iteratorControllerConfigSelected(SelectListControllerConfig, frontEnd.controlConfig, &FEApp->fInputPlayer)   /* +0x2AE8 tListIteratorIndexed */
 , itemControllerConfigSelected(0x209, (tListIterator *)&iteratorControllerConfigSelected)   /* +0x2AFC tMenuItemControllerLeftRightChoice */
 , itemControllerSettings(0x20a, 0xac, 0x48, 0, 0xd, true)   /* +0x2B28 tMenuItemSlidingMenu */
 , menuControllerConfig(0x1020, (tScreen *)screenControllerConfig, (tMenu *)0x0, (tMenu *)0x0, 0, 0x208, 0, 10, (tMenuItem *)&itemControllerConfigSelected, &itemControllerSettings, 0)   /* +0x2B6C tOptionsMenu */
 , iteratorControllerShockMode('\0', '\x7f', frontEnd.shockMode, &FEApp->fInputPlayer)   /* +0x2BEC tListIteratorRangeIndexed */
 , itemControllerShockMode(0x20e, (tListIterator *)&iteratorControllerShockMode)   /* +0x2C00 tInsideBoxControllerLeftRightSlider */
 , iteratorControllerShockImpact('\0', '\x7f', frontEnd.shockImpact, &FEApp->fInputPlayer)   /* +0x2C28 tListIteratorRangeIndexed */
 , itemControllerShockImpact(0x20f, (tListIterator *)&iteratorControllerShockImpact)   /* +0x2C3C tInsideBoxControllerLeftRightSlider */
 , iteratorControllerSteeringRange1('\0', '\x7f', frontEnd.J1MAX, &FEApp->fInputPlayer)   /* +0x2C64 tListIteratorRangeIndexed */
 , itemControllerSteeringRange1(0x211, (tListIterator *)&iteratorControllerSteeringRange1, 0)   /* +0x2C78 tInsideBoxTwoWaySlider */
 , iteratorControllerDeadSpot1('\0', '\x7f', frontEnd.J1MIN, &FEApp->fInputPlayer)   /* +0x2CA8 */
 , itemControllerDeadSpot1(0x213, (tListIterator *)&iteratorControllerDeadSpot1, 1)   /* +0x2CBC tInsideBoxTwoWaySlider */
 , iteratorControllerSteeringRange2('\0', '\x7f', frontEnd.J2MAX, &FEApp->fInputPlayer)   /* +0x2CEC */
 , itemControllerSteeringRange2(0x210, (tListIterator *)&iteratorControllerSteeringRange2, 2)   /* +0x2D00 tInsideBoxTwoWaySlider */
 , iteratorControllerDeadSpot2('\0', '\x7f', frontEnd.J2MIN, &FEApp->fInputPlayer)   /* +0x2D30 */
 , itemControllerDeadSpot2(0x212, (tListIterator *)&iteratorControllerDeadSpot2, 3)   /* +0x2D44 tInsideBoxTwoWaySlider */
 , iteratorControllerJoyRange('\0', '\x7f', frontEnd.steeringRange, &FEApp->fInputPlayer)   /* +0x2D74 */
 , itemControllerJoyRange(0x214, (tListIterator *)&iteratorControllerJoyRange, 0)   /* +0x2D88 tInsideBoxTwoWaySlider */
 , iteratorControllerCenterPoint('\0', '\x7f', frontEnd.deadSpot, &FEApp->fInputPlayer)   /* +0x2DB8 */
 , itemControllerCenterPoint(0x215, (tListIterator *)&iteratorControllerCenterPoint, 1)   /* +0x2DCC tInsideBoxTwoWaySlider */
 , iteratorControllerIMax('\0', -1, frontEnd.ImaxRange, &FEApp->fInputPlayer)   /* +0x2DFC */
 , itemControllerIMax(0x216, (tListIterator *)&iteratorControllerIMax, 2)   /* +0x2E10 tInsideBoxTwoWaySlider */
 , iteratorControllerIIMax('\0', -1, frontEnd.IImaxRange, &FEApp->fInputPlayer)   /* +0x2E40 */
 , itemControllerIIMax(0x217, (tListIterator *)&iteratorControllerIIMax, 3)   /* +0x2E54 tInsideBoxTwoWaySlider */
 , menuControllerDualShock(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, 0, (tMenuItem *)&itemControllerShockMode, &itemControllerShockImpact, 0)   /* +0x2E84 tInsideBoxMenu */
 , menuControllerAnalog(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, 0, (tMenuItem *)&itemControllerSteeringRange1, &itemControllerDeadSpot1, &itemControllerSteeringRange2, &itemControllerDeadSpot2, 0)   /* +0x2EF8 tInsideBoxMenu */
 , menuControllerDualShockAnalog(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, 0, (tMenuItem *)&itemControllerShockMode, &itemControllerShockImpact, &itemControllerDeadSpot1, &itemControllerDeadSpot2, 0)   /* +0x2F6C tInsideBoxMenu */
 , menuControllerNegcon(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, 0, 0, (tMenuItem *)&itemControllerJoyRange, &itemControllerCenterPoint, &itemControllerIMax, &itemControllerIIMax, 0)   /* +0x2FE0 tInsideBoxMenu */
 , itemSaveGame(0x286, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_SaveGame)   /* +0x3054 tMemoryCardMenuItem */
 , itemLoadGame(0x287, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_LoadGame)   /* +0x3080 tMemoryCardMenuItem */
 , menuMemory(0x1020, (tScreen *)screenMemcard, (tMenu *)0x0, (tMenu *)0x0, 0, -1, 0x2e, 10, (tMenuItem *)&itemLoadGame, &itemSaveGame, 0)   /* +0x30AC tOptionsMenu */
 , menuItemUserName(0x1f8)   /* +0x312C tUserNameMenuItem */
 , menuItemUserName1(0x1f8)   /* +0x31B8 tUserNameMenuItem */
 , menuItemUserName2(0x1f8)   /* +0x3244 tUserNameMenuItem */
 , menuUserName(0x1120, (tScreen *)screenUserName, (tMenu *)0x0, (tMenu *)0x0, 0, -1, 0x20, 10, (tMenuItem *)&menuItemUserName, 0)   /* +0x32D0 tOptionsMenu */
 , iteratorChangeTrophy(screenTrophyRoom->fTrophyList, &screenTrophyRoom->thisisuseless)   /* +0x3350 tListIterator */
 , itemChangeTrophy(0x5e, &iteratorChangeTrophy, -1, 0)   /* +0x3360 tBlankMenuItemNFS4LeftRightChoice */
 , menuTrophyRoom(0x4010, (tScreen *)screenTrophyRoom, (tMenu *)0x0, (tMenu *)0x0, 0, -1, (tMenuItem *)&itemChangeTrophy, 0)   /* +0x3388 tMenuNFS4Bottom */
 , itemPinkSlipStandingsForward(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_PinkSlipsContinue, 0, 10)   /* +0x3404 tMenuItemGoToMenuNFS4Button */
 , itemPinkSlipStandingsExit(0x9c, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_ExitPinkSlipsEarly, 0, 10)   /* +0x3430 tMenuItemGoToMenuNFS4Button */
 , menuPinkSlipStandings(0x1004, (tScreen *)screenPinkSlipStandings, (tMenu *)0x0, (tMenu *)0x0, 0, 0x2f4, (tMenuItem *)&itemPinkSlipStandingsForward, &itemPinkSlipStandingsExit, 0)   /* +0x345C tMenuNFS4 */
 , itemTournStandingsForward(0x5a, (tMenu*)&menuTrackInfo, 0, 0, 10)   /* +0x34D8 tMenuItemGoToMenuNFS4Button */
 , itemTournStandingsExit(0x9b, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_ExitTourney, 0, 10)   /* +0x3504 tMenuItemGoToMenuNFS4Button */
 , menuTournamentStandings(0x1004, (tScreen *)screenTournamentStandings3item, (tMenu *)0x0, (tMenu *)0x0, 0, 0x2f4, (tMenuItem *)&itemTournStandingsForward, &itemTournStandingsExit, 0)   /* +0x3530 tMenuNFS4 */
 , itemTournamentFinishedHome(0x5a, (tMenu *)&menuTournamentTrophy, 0, 0, 10)   /* +0x35AC tMenuItemGoToMenuNFS4Button */
 , menuTournamentFinished(0x1004, (tScreen *)screenTournamentStandings, (tMenu *)0x0, (tMenu *)0x0, 0, 0x2f4, (tMenuItem *)&itemTournamentFinishedHome, 0)   /* +0x35D8 tMenuNFS4 */
 , menuTournamentTrophy(0x8000, (tScreen *)screenTournamentTrophy, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_TierFinished, -1)   /* +0x3654 tMenuBlank */
 , menuPostGamePlayer1Name(0x1040, (tScreen *)screenUserName, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_FinishedPlayer1GetName, -1, 0x20, 10, (tMenuItem *)&menuItemUserName1, 0)   /* +0x36D0 tOptionsMenu */
 , menuPostGamePlayer2Name(0x1080, (tScreen *)screenUserName, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_FinishedPlayer2GetName, -1, 0x20, 10, (tMenuItem *)&menuItemUserName2, 0)   /* +0x3750 tOptionsMenu */
 , itemPostGameTrackRecordsContinue(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_PostGameMenu, -1, -1)   /* +0x37D0 tBlankMenuItemGoToMenuNFS4Button */
 , menuPostGameTrackRecords(0x21004, (tScreen *)screenTrackRecords, (tMenu *)0x0, (tMenu *)0x0, 0, 0xd4, 1, 10, (tMenuItem *)&itemPostGameTrackRecordsContinue, 0)   /* +0x37FC tOptionsMenu */
 , menuPinkSlipCongrats(0x8000, (tScreen *)screenPinkSlipCongrats, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_AwardPinkSlipsCar, -1)   /* +0x387C tMenuBlank */
 , menuBeTheCopCongrats(0x8000, (tScreen *)screenBeTheCopCongrats, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame, -1)   /* +0x38F8 tMenuBlank */
 , menuTierCompleteCongrats(0x8000, (tScreen *)screenTournamentCongrats, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame, -1)   /* +0x3974 tMenuBlank */
 , menuCredits(0x1010, (tScreen *)screenMain, (tMenu *)0x0, (tMenu *)0x0, 0, -1)   /* +0x39F0 tMenuBlank */
 , itemMemContinue(0x28a, (tMenu *)0x0, (void (*)(tMenuCommand&))MenuExtended_TransitionFromPostGameToMainMenu)   /* +0x3A6C tMemoryCardMenuItem */
 , menuPostGameSave(0x1040, (tScreen *)screenMemcard, (tMenu *)0x0, (tMenu *)0x0, 0, -1, 0x2e, 10, (tMenuItem *)&itemMemContinue, &itemSaveGame, 0)   /* +0x3A98 tOptionsMenu */
 {
  A1_SetChildMenu(&menuPlayerOneCarSelect, (tMenu *)&menuPlayerTwoCarSelect);
  A1_SetChildMenu(&menuPlayerOneGarage, (tMenu *)&menuPlayerTwoGarage);
  A1_SetChildMenu(&menuPlayerOnePinkSlipCarSelect, (tMenu *)&menuPlayerTwoPinkSlipCarSelect);
  ((tMenuItemLeftRightSlider *)&itemMusicVolume)->SetDimensions(0,0,0x78,5);
  ((tMenuItemLeftRightSlider *)&itemSoundEffectsVolume)->SetDimensions(0,0,0x78,5);
  ((tMenuItemLeftRightSlider *)&itemEngineVolume)->SetDimensions(0,0,0x78,5);
  ((tMenuItemLeftRightSlider *)&itemSpeechVolume)->SetDimensions(0,0,0x78,5);
  ((tMenuItemLeftRightSlider *)&itemAmbientVolume)->SetDimensions(0,0,0x78,5);
  A1_SetCarFilter(&iteratorGarageCar, 2);
  A1_SetCarFilter(&iteratorPinkSlipsCar, 0x20);
  A1_SetCarFilter(&iteratorDealerCar, 1);
  A1_SetCarFilter(&iteratorSellerCar, 2);
  A1_SetVertHelp(&menuAudio, 0);
  A1_SetVertHelp(&menuDisplayOptions, 0);
  A1_SetVertHelp(&menuControllerConfig, 1);
  A1_SetFlags(&itemTournamentFinishedHome, A1_GetFlags(&itemTournamentFinishedHome) | 0x40);
  A1_SetVertHelp(&menuMemory, 0);
  A1_SetVertHelp(&menuUserName, 0);
  A1_SetVertHelp(&menuTrackRecords, 1);
  A1_SetVertHelp(&menuTrophyInfo, 0);
  return;
}



/* ---- tGlobalMenuDefs::dtor  [FEMENUDEFS.CPP:2204] ---- */

tGlobalMenuDefs::~tGlobalMenuDefs()

{
  /* [2026-07-11] PASS (was 747 diffs / 1510 vs oracle 763 insns): the body previously made
     ~249 EXPLICIT member-teardown calls (`Type_dtor(&this->member, 2)` for every real by-value
     member of tGlobalMenuDefs, in reverse declaration order). Every one of those member types
     (tMenuBlank, tOptionsMenu, tMenuNFS4, tMenuItemGoToMenuNFS4Button, ...) has a REAL declared
     destructor in nfs4_types.h, so tGlobalMenuDefs being a struct of ~249 such members by value
     means the COMPILER ALREADY emits the exact same per-member teardown sequence automatically
     in this destructor's implicit epilogue -- the explicit calls were a pure duplicate (same
     class of bug as the `tDialogYesNo_ctor` redundant-manual-ctor-call fix applied to ~10 other
     fns in this file, just at 249x scale: `Type_dtor` free-function externs are undefined
     phantoms with no definition anywhere in the tree, mirroring `tDialogYesNo_ctor`). Deleting
     the whole explicit call list and letting the automatic member destruction run alone
     byte-matches the oracle exactly (763/763). */
}



/* The tBlank* classes are ALL-INLINE (screendisplay_types.h): TransitionIsFinished / Draw bodies and the synthesized
 * destructors are emitted by the compiler as the deferred-inline batch that closes this object --
 *   TIF32, Draw32(iib), Draw32(b), ~32, TIF33, Draw33(iib), ~33  (reverse class order, declaration order inside). */

/* W60-A10: the three tBlankMenuItem::Draw nullsub exports that used to sit HERE were moved
   up into their retail VA slots (see the notes at 0x800321C8 / 0x80032200); the mis-mangled
   member definitions they shadowed were deleted. */
