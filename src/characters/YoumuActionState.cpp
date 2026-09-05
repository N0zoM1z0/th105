#include <stddef.h>

namespace th105 {

// Transitional full-root source recovered from the current 1.06a action CFG.
// The raw byte view keeps target-backed Fighter offsets explicit while the
// giant action families are progressively replaced by named typed overlays.
// Do not split this authored root into regional exact-byte claims: the ledger
// unit remains the complete vslot +0x28 callable.

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;

int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32(void);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);

class YoumuActionStateView;
float __fastcall stage_surface_height_at_x(YoumuActionStateView *fighter);
int __fastcall is_y_at_or_below_stage_surface(void *fighter);

struct FighterActionScratchView { void reset(); };
struct FighterPeerActionStateView { void zero_velocity_acceleration(); };

class YoumuActionStateView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);
    virtual void set_sequence(int sequence);
    virtual void slot_10();
    virtual void slot_14();

    unsigned char resolve_stage_surface_landing_transition();
    unsigned char advance_frame_and_dispatch();
    int has_crossed_stage_surface_while_descending();
    void zero_velocity_acceleration();
    void set_oriented_components_f0_f4(float angle, float magnitude);
    void emit_fighter_effect_433cc0(int effect_code, float x, float y, int direction, int trailing_value);
    void publish_battle_layout_scalar(float value);
    void dispatch_indexed_event_member(unsigned index);
    void dispatch_character_wave_handle(unsigned index);
    void finalize_sequence_entry(int outcome);
    void dispatch_indexed_sequence_window_45c8b0(signed char relative_index, int outcome, int source_token);
    int configure_render_history(int countdown, signed char period, int color_mask);
    void publish_texture_state(signed char texture_index, short duration);
    int spawn_owned_object_via_manager(int object_id, float x, float y, int direction, unsigned char arg5, int arg6, int arg7);
    void adjust_counter_482(short amount, int floor_value);
    void advance_secondary_event_effect_cycle();
    int add_phase_scaled_counter_558(int value);
    void face_opponent_and_flip_horizontal_velocity();
    unsigned char try_dispatch_directional_action_208_210(int option);
    void copy_action_word_176_to_174();
    void update_common_action_state();

    void dispatch_action_state_vslot28();
};

extern int g_match_identifier;

void YoumuActionStateView::dispatch_action_state_vslot28()
{
  unsigned char *raw = reinterpret_cast<unsigned char *>(this);
__int16 v2; // ax
double v3; // st7
__int16 v4; // ax
int v5; // eax
double v6; // st7
double v7; // st7
double v8; // st7
bool v9; // zf
bool v10; // cc
float v11; // target loads/stores single-precision field values
bool v12; // cc
bool v13; // cc
void (__thiscall *v14)(void *, int); // edx
__int16 v15; // ax
void (__thiscall *v16)(void *, int); // edx
float v17; // target loads/stores single-precision field values
__int16 v18; // ax
void (__thiscall *v19)(void *, int); // eax
void (__thiscall *v20)(void *, int); // edx
__int16 v21; // ax
__int16 v22; // ax
double v23; // st7
double v24; // st7
float v25; // target loads/stores single-precision field values
float v26; // target loads/stores single-precision field values
int v27; // eax
int v28; // ecx
bool v29; // sf
int v30; // eax
int v31; // eax
int v32; // eax
int v33; // eax
__int16 v34; // ax
__int16 v35; // ax
__int16 v36; // cx
__int16 v37; // ax
bool v38; // sf
double v39; // st5
double v40; // st5
double v41; // st7
double v42; // st7
int v43; // eax
__int16 v44; // ax
char v45; // cl
double v46; // st7
void (__thiscall *v47)(void *, int); // eax
__int16 v48; // ax
char v49; // cl
double v50; // st7
void (__thiscall *v51)(void *, int); // eax
void (__thiscall *v52)(void *, int); // edx
__int16 v53; // ax
__int16 v54; // ax
__int16 v55; // ax
double v56; // st7
bool v57; // cc
double v58; // st7
int v59; // eax
bool v60; // cc
double v61; // st7
bool v62; // cc
int v63; // eax
double v64; // st7
__int16 v65; // ax
bool v66; // cc
int v67; // eax
int v68; // eax
int v69; // eax
int v70; // eax
int v71; // ebp
bool v72; // cc
int v73; // eax
__int16 v74; // ax
bool v75; // cc
double v76; // st7
double v77; // st7
__int16 v78; // ax
bool v79; // zf
int v80; // eax
__int16 v81; // ax
__int16 v82; // ax
__int16 v83; // ax
__int16 v84; // ax
int v85; // eax
__int16 v86; // ax
__int16 v87; // ax
__int16 v88; // ax
int v89; // ecx
__int16 v90; // ax
int v91; // eax
__int16 v92; // ax
int v93; // ecx
__int16 v94; // ax
int v95; // eax
unsigned __int16 v96; // ax
double v97; // st7
int v98; // eax
__int16 v99; // ax
__int16 v100; // ax
int v101; // eax
int v102; // eax
__int16 v103; // ax
int v104; // eax
double v105; // st7
double v106; // st6
double v107; // rt0
double v108; // st6
double v109; // st7
int v110; // eax
double v111; // st7
double v112; // st7
__int16 v113; // ax
__int16 v114; // ax
__int16 v115; // ax
int v116; // eax
double v117; // st6
double v118; // st7
int v119; // eax
__int16 v120; // ax
__int16 v121; // ax
__int16 v122; // ax
__int16 v123; // ax
__int16 v124; // ax
__int16 v125; // ax
__int16 v126; // ax
__int16 v127; // ax
__int16 v128; // ax
int v129; // eax
double v130; // st7
__int16 v131; // ax
__int16 v132; // ax
bool v133; // zf
int v134; // eax
int v135; // eax
int v136; // eax
int v137; // eax
double v138; // st7
__int16 v139; // ax
int v140; // eax
int v141; // eax
double v142; // st7
double v143; // st6
double v144; // rt2
double v145; // st6
double v146; // st7
float v147; // [esp+8h] [ebp-258h]
float v148; // [esp+8h] [ebp-258h]
float v149; // [esp+8h] [ebp-258h]
float v150; // [esp+8h] [ebp-258h]
float v151; // [esp+8h] [ebp-258h]
float v152; // [esp+8h] [ebp-258h]
float v153; // [esp+Ch] [ebp-254h]
float v154; // [esp+Ch] [ebp-254h]
float v155; // [esp+Ch] [ebp-254h]
float v156; // [esp+Ch] [ebp-254h]
float v157; // [esp+Ch] [ebp-254h]
float v158; // [esp+Ch] [ebp-254h]
float v159; // [esp+Ch] [ebp-254h]
float v160; // [esp+Ch] [ebp-254h]
float v161; // [esp+Ch] [ebp-254h]
float v162; // [esp+Ch] [ebp-254h]
float v163; // [esp+Ch] [ebp-254h]
float v164; // [esp+Ch] [ebp-254h]
float v165; // [esp+Ch] [ebp-254h]
float v166; // [esp+Ch] [ebp-254h]
float v167; // [esp+Ch] [ebp-254h]
float v168; // [esp+Ch] [ebp-254h]
float v169; // [esp+Ch] [ebp-254h]
float v170; // [esp+Ch] [ebp-254h]
float v171; // [esp+Ch] [ebp-254h]
float v172; // [esp+Ch] [ebp-254h]
float v173; // [esp+Ch] [ebp-254h]
int v174; // [esp+10h] [ebp-250h]
int v175; // [esp+10h] [ebp-250h]
int v176; // [esp+10h] [ebp-250h]
int v177; // [esp+10h] [ebp-250h]
int v178; // [esp+10h] [ebp-250h]
int v179; // [esp+10h] [ebp-250h]
int v180; // [esp+10h] [ebp-250h]
int v181; // [esp+10h] [ebp-250h]
int v182; // [esp+10h] [ebp-250h]
int v183; // [esp+10h] [ebp-250h]
int v184; // [esp+10h] [ebp-250h]
int v185; // [esp+10h] [ebp-250h]
float v186; // [esp+14h] [ebp-24Ch]
float v187; // [esp+14h] [ebp-24Ch]
float v188; // [esp+14h] [ebp-24Ch]
float v189; // [esp+14h] [ebp-24Ch]
float v190; // [esp+14h] [ebp-24Ch]
float v191; // [esp+14h] [ebp-24Ch]
float v192; // [esp+14h] [ebp-24Ch]
float v193; // [esp+14h] [ebp-24Ch]
float v194; // [esp+14h] [ebp-24Ch]
float v195; // [esp+14h] [ebp-24Ch]
float v196; // [esp+14h] [ebp-24Ch]
float v197; // [esp+14h] [ebp-24Ch]
float v198; // [esp+14h] [ebp-24Ch]
float v199; // [esp+14h] [ebp-24Ch]
float v200; // [esp+14h] [ebp-24Ch]
float v201; // [esp+14h] [ebp-24Ch]
float v202; // [esp+14h] [ebp-24Ch]
int v203; // [esp+14h] [ebp-24Ch]
float v204; // [esp+14h] [ebp-24Ch]
float v205; // [esp+14h] [ebp-24Ch]
int v206; // [esp+14h] [ebp-24Ch]
int v207; // [esp+14h] [ebp-24Ch]
float v208; // [esp+14h] [ebp-24Ch]
int v209; // [esp+14h] [ebp-24Ch]
int v210; // [esp+18h] [ebp-248h]
int v211; // [esp+18h] [ebp-248h]
int v212; // [esp+18h] [ebp-248h]
int v213; // [esp+18h] [ebp-248h]
int v214; // [esp+18h] [ebp-248h]
int v215; // [esp+18h] [ebp-248h]
int v216; // [esp+18h] [ebp-248h]
int v217; // [esp+18h] [ebp-248h]
int v218; // [esp+18h] [ebp-248h]
int v219; // [esp+18h] [ebp-248h]
int v220; // [esp+18h] [ebp-248h]
int v221; // [esp+18h] [ebp-248h]
int v222; // [esp+18h] [ebp-248h]
int v223; // [esp+18h] [ebp-248h]
int *v224; // [esp+18h] [ebp-248h]
int *v225; // [esp+18h] [ebp-248h]
int v226; // [esp+18h] [ebp-248h]
unsigned int v227; // [esp+1Ch] [ebp-244h]
float v228; // [esp+30h] [ebp-230h]
float v229; // [esp+30h] [ebp-230h]
float v230; // [esp+30h] [ebp-230h]
float v231; // [esp+30h] [ebp-230h]
float v232; // [esp+30h] [ebp-230h]
float v233; // [esp+30h] [ebp-230h]
float v234; // [esp+30h] [ebp-230h]
float v235; // [esp+30h] [ebp-230h]
float v236; // [esp+30h] [ebp-230h]
float v237; // [esp+30h] [ebp-230h]
float v238; // [esp+30h] [ebp-230h]
float v239; // [esp+30h] [ebp-230h]
float v240; // [esp+30h] [ebp-230h]
float v241; // [esp+30h] [ebp-230h]
float v242; // [esp+30h] [ebp-230h]
float v243; // [esp+30h] [ebp-230h]
float v244; // [esp+30h] [ebp-230h]
float v245; // [esp+30h] [ebp-230h]
float v246; // [esp+30h] [ebp-230h]
float v247; // [esp+30h] [ebp-230h]
float v248; // [esp+30h] [ebp-230h]
float v249; // [esp+30h] [ebp-230h]
float v250; // [esp+30h] [ebp-230h]
float v251; // [esp+30h] [ebp-230h]
float v252; // [esp+30h] [ebp-230h]
float v253; // [esp+30h] [ebp-230h]
float v254; // [esp+30h] [ebp-230h]
float v255; // [esp+30h] [ebp-230h]
float v256; // [esp+30h] [ebp-230h]
float v257; // [esp+30h] [ebp-230h]
float v258; // [esp+30h] [ebp-230h]
float v259; // [esp+30h] [ebp-230h]
float v260; // [esp+30h] [ebp-230h]
float v261; // [esp+30h] [ebp-230h]
float v262; // [esp+30h] [ebp-230h]
float v263; // [esp+30h] [ebp-230h]
float v264; // [esp+30h] [ebp-230h]
float v265; // [esp+30h] [ebp-230h]
float v266; // [esp+30h] [ebp-230h]
float v267; // [esp+30h] [ebp-230h]
float v268; // [esp+30h] [ebp-230h]
float v269; // [esp+30h] [ebp-230h]
float v270; // [esp+30h] [ebp-230h]
float v271; // [esp+30h] [ebp-230h]
float v272; // [esp+30h] [ebp-230h]
float v273; // [esp+30h] [ebp-230h]
float v274; // [esp+30h] [ebp-230h]
float v275; // [esp+30h] [ebp-230h]
float v276; // [esp+30h] [ebp-230h]
float v277; // [esp+30h] [ebp-230h]
float v278; // [esp+30h] [ebp-230h]
float v279; // [esp+30h] [ebp-230h]
float v280; // [esp+30h] [ebp-230h]
float v281; // [esp+30h] [ebp-230h]
float v282; // [esp+30h] [ebp-230h]
float v283; // [esp+30h] [ebp-230h]
float v284; // [esp+30h] [ebp-230h]
float v285; // [esp+30h] [ebp-230h]
float v286; // [esp+30h] [ebp-230h]
float v287; // [esp+30h] [ebp-230h]
float v288; // [esp+30h] [ebp-230h]
float v289; // [esp+30h] [ebp-230h]
float v290; // [esp+30h] [ebp-230h]
float v291; // [esp+30h] [ebp-230h]
float v292; // [esp+30h] [ebp-230h]
float v293; // [esp+30h] [ebp-230h]
float v294; // [esp+30h] [ebp-230h]
float v295; // [esp+30h] [ebp-230h]
float v296; // [esp+30h] [ebp-230h]
float v297; // [esp+30h] [ebp-230h]
float v298; // [esp+30h] [ebp-230h]
float v299; // [esp+30h] [ebp-230h]
float v300; // [esp+30h] [ebp-230h]
float v301; // [esp+30h] [ebp-230h]
float v302; // [esp+30h] [ebp-230h]
float v303; // [esp+30h] [ebp-230h]
float v304; // [esp+30h] [ebp-230h]
float v305; // [esp+30h] [ebp-230h]
float v306; // [esp+30h] [ebp-230h]
float v307; // [esp+30h] [ebp-230h]
float v308; // [esp+30h] [ebp-230h]
float v309; // [esp+30h] [ebp-230h]
float v310; // [esp+30h] [ebp-230h]
float v311; // [esp+30h] [ebp-230h]
float v312; // [esp+30h] [ebp-230h]
float v313; // [esp+30h] [ebp-230h]
float v314; // [esp+30h] [ebp-230h]
float v315; // [esp+30h] [ebp-230h]
float v316; // [esp+30h] [ebp-230h]
float v317; // [esp+30h] [ebp-230h]
float v318; // [esp+30h] [ebp-230h]
float v319; // [esp+30h] [ebp-230h]
float v320; // [esp+30h] [ebp-230h]
float v321; // [esp+30h] [ebp-230h]
float v322; // [esp+30h] [ebp-230h]
float v323; // [esp+30h] [ebp-230h]
float v324; // [esp+30h] [ebp-230h]
float v325; // [esp+30h] [ebp-230h]
float v326; // [esp+30h] [ebp-230h]
float v327; // [esp+30h] [ebp-230h]
float v328; // [esp+30h] [ebp-230h]
float v329; // [esp+30h] [ebp-230h]
float v330; // [esp+30h] [ebp-230h]
float v331; // [esp+30h] [ebp-230h]
float v332; // [esp+30h] [ebp-230h]
float v333; // [esp+30h] [ebp-230h]
float v334; // [esp+30h] [ebp-230h]
float v335; // [esp+30h] [ebp-230h]
float v336; // [esp+30h] [ebp-230h]
float v337; // [esp+30h] [ebp-230h]
float v338; // [esp+30h] [ebp-230h]
float v339; // [esp+30h] [ebp-230h]
float v340; // [esp+30h] [ebp-230h]
float v341; // [esp+30h] [ebp-230h]
float v342; // [esp+30h] [ebp-230h]
float v343; // [esp+30h] [ebp-230h]
float v344; // [esp+30h] [ebp-230h]
float v345; // [esp+30h] [ebp-230h]
float v346; // [esp+30h] [ebp-230h]
float v347; // [esp+30h] [ebp-230h]
float v348; // [esp+30h] [ebp-230h]
float v349; // [esp+30h] [ebp-230h]
float v350; // [esp+30h] [ebp-230h]
float v351; // [esp+30h] [ebp-230h]
float v352; // [esp+30h] [ebp-230h]
float v353; // [esp+30h] [ebp-230h]
float v354; // [esp+30h] [ebp-230h]
float v355; // [esp+30h] [ebp-230h]
float v356; // [esp+30h] [ebp-230h]
float v357; // [esp+30h] [ebp-230h]
float v358; // [esp+30h] [ebp-230h]
float v359; // [esp+30h] [ebp-230h]
float v360; // [esp+30h] [ebp-230h]
float v361; // [esp+30h] [ebp-230h]
float v362; // [esp+30h] [ebp-230h]
float v363; // [esp+30h] [ebp-230h]
double v364; // [esp+30h] [ebp-230h]
float v365; // [esp+30h] [ebp-230h]
float v366; // [esp+30h] [ebp-230h]
float v367; // [esp+30h] [ebp-230h]
float v368; // [esp+30h] [ebp-230h]
float v369; // [esp+30h] [ebp-230h]
float v370; // [esp+30h] [ebp-230h]
float v371; // [esp+30h] [ebp-230h]
float v372; // [esp+30h] [ebp-230h]
float v373; // [esp+30h] [ebp-230h]
float v374; // [esp+30h] [ebp-230h]
float v375; // [esp+30h] [ebp-230h]
float v376; // [esp+30h] [ebp-230h]
float v377; // [esp+30h] [ebp-230h]
float v378; // [esp+3Ch] [ebp-224h]
float v379; // [esp+3Ch] [ebp-224h]
float v380; // [esp+3Ch] [ebp-224h]
float v381; // [esp+3Ch] [ebp-224h]
float v382; // [esp+3Ch] [ebp-224h]
float v383; // [esp+3Ch] [ebp-224h]
float v384; // [esp+3Ch] [ebp-224h]
float v385; // [esp+3Ch] [ebp-224h]
float v386; // [esp+3Ch] [ebp-224h]
float v387; // [esp+3Ch] [ebp-224h]
float v388; // [esp+3Ch] [ebp-224h]
float v389; // [esp+3Ch] [ebp-224h]
float v390; // [esp+3Ch] [ebp-224h]
float v391; // [esp+3Ch] [ebp-224h]
float v392; // [esp+3Ch] [ebp-224h]
float v393; // [esp+3Ch] [ebp-224h]
float v394; // [esp+3Ch] [ebp-224h]
float v395; // [esp+3Ch] [ebp-224h]
float v396; // [esp+3Ch] [ebp-224h]
float v397; // [esp+3Ch] [ebp-224h]
float v398; // [esp+3Ch] [ebp-224h]
float v399; // [esp+3Ch] [ebp-224h]
float v400; // [esp+3Ch] [ebp-224h]
float v401; // [esp+3Ch] [ebp-224h]
float v402; // [esp+3Ch] [ebp-224h]
float v403; // [esp+3Ch] [ebp-224h]
float v404; // [esp+3Ch] [ebp-224h]
float v405; // [esp+3Ch] [ebp-224h]
float v406; // [esp+3Ch] [ebp-224h]
float v407; // [esp+3Ch] [ebp-224h]
float v408; // [esp+3Ch] [ebp-224h]
float v409; // [esp+3Ch] [ebp-224h]
float v410; // [esp+3Ch] [ebp-224h]
float v411; // [esp+3Ch] [ebp-224h]
float v412; // [esp+3Ch] [ebp-224h]
float v413; // [esp+3Ch] [ebp-224h]
float v414; // [esp+3Ch] [ebp-224h]
float v415; // [esp+3Ch] [ebp-224h]
float v416; // [esp+3Ch] [ebp-224h]
float v417; // [esp+3Ch] [ebp-224h]
float v418; // [esp+3Ch] [ebp-224h]
float v419; // [esp+3Ch] [ebp-224h]
float v420; // [esp+3Ch] [ebp-224h]
float v421; // [esp+3Ch] [ebp-224h]
float v422; // [esp+3Ch] [ebp-224h]
float v423; // [esp+3Ch] [ebp-224h]
float v424; // [esp+3Ch] [ebp-224h]
float v425; // [esp+3Ch] [ebp-224h]
float v426; // [esp+3Ch] [ebp-224h]
float v427; // [esp+3Ch] [ebp-224h]
float v428; // [esp+3Ch] [ebp-224h]
float v429; // [esp+3Ch] [ebp-224h]
float v430; // [esp+3Ch] [ebp-224h]
float v431; // [esp+3Ch] [ebp-224h]
float v432; // [esp+3Ch] [ebp-224h]
double v433; // [esp+40h] [ebp-220h]
double v434; // [esp+40h] [ebp-220h]
double v435; // [esp+40h] [ebp-220h]
double v436; // [esp+40h] [ebp-220h]
double v437; // [esp+40h] [ebp-220h]
double v438; // [esp+40h] [ebp-220h]
double v439; // [esp+40h] [ebp-220h]
double v440; // [esp+40h] [ebp-220h]
double v441; // [esp+40h] [ebp-220h]
double v442; // [esp+40h] [ebp-220h]
double v443; // [esp+40h] [ebp-220h]
int v444[2]; // [esp+48h] [ebp-218h] BYREF
float v445; // [esp+50h] [ebp-210h]
float payload_446[3]; // target contiguous +54/+58/+5C BYREF
float payload_449[3]; // target contiguous +60/+64/+68 BYREF
float payload_452[3]; // target contiguous +6C/+70/+74 BYREF
float payload_455[3]; // target contiguous +78/+7C/+80 BYREF
int v458[3]; // [esp+84h] [ebp-1DCh] BYREF
int v459[3]; // [esp+90h] [ebp-1D0h] BYREF
int v460[3]; // [esp+9Ch] [ebp-1C4h] BYREF
float v461; // [esp+A8h] [ebp-1B8h] BYREF
int v462; // [esp+ACh] [ebp-1B4h] BYREF
float payload_463[3]; // target contiguous +B0/+B4/+B8 BYREF
float payload_465[3]; // target contiguous +BC/+C0/+C4 BYREF
int v467[3]; // [esp+C8h] [ebp-198h] BYREF
int v468[3]; // [esp+D4h] [ebp-18Ch] BYREF
int v469[3]; // [esp+E0h] [ebp-180h] BYREF
int v470[3]; // [esp+ECh] [ebp-174h] BYREF
float v471[3]; // [esp+F8h] [ebp-168h] BYREF
int v472[3]; // [esp+104h] [ebp-15Ch] BYREF
int v473[3]; // [esp+110h] [ebp-150h] BYREF
int v474[3]; // [esp+11Ch] [ebp-144h] BYREF
int v475[3]; // [esp+128h] [ebp-138h] BYREF
int v476[3]; // [esp+134h] [ebp-12Ch] BYREF
int v477[3]; // [esp+140h] [ebp-120h] BYREF
int v478[3]; // [esp+14Ch] [ebp-114h] BYREF
int v479[3]; // [esp+158h] [ebp-108h] BYREF
int v480[3]; // [esp+164h] [ebp-FCh] BYREF
int v481[3]; // [esp+170h] [ebp-F0h] BYREF
float v482[3]; // [esp+17Ch] [ebp-E4h] BYREF
int v483[3]; // [esp+188h] [ebp-D8h] BYREF
int v484[3]; // [esp+194h] [ebp-CCh] BYREF
int v485[3]; // [esp+1A0h] [ebp-C0h] BYREF
int v486[3]; // [esp+1ACh] [ebp-B4h] BYREF
int v487[3]; // [esp+1B8h] [ebp-A8h] BYREF
int v488[3]; // [esp+1C4h] [ebp-9Ch] BYREF
int v489[3]; // [esp+1D0h] [ebp-90h] BYREF
int v490[4]; // [esp+1DCh] [ebp-84h] BYREF
int v491[4]; // [esp+1ECh] [ebp-74h] BYREF
int v492[5]; // [esp+1FCh] [ebp-64h] BYREF
int v493[5]; // [esp+210h] [ebp-50h] BYREF
int v494[5]; // [esp+224h] [ebp-3Ch] BYREF
int v495[5]; // [esp+238h] [ebp-28h] BYREF
int v496[5]; // [esp+24Ch] [ebp-14h] BYREF

*(_WORD *)(raw + 1952) = 0;
*(_WORD *)(raw + 1954) = 90;
v2 = *(_WORD *)(raw + 2024);
if (v2 >= 1)
  *(_WORD *)(raw + 2024) = v2 - 1;
v3 = 0.0;
if (*(__int16 *)(raw + 2026) > 0)
{
  if (*(__int16 *)(raw + 2028) > 0)
    *(float *)(raw + 1232) = 0.0;
  --*(__int16 *)(raw + 2026);
  if (*(__int16 *)(raw + 372) <= 0 || *(__int16 *)(*(_DWORD *)(raw + 368) + 372) <= 0)
    *(_WORD *)(raw + 2026) = 0;
  if (*(__int16 *)(raw + 316) >= 600)
  {
    if (*(__int16 *)(raw + 316) <= 699)
    {
      if (*(__int16 *)(raw + 316) == 602 || *(__int16 *)(raw + 316) == 605)
      {
        if (!*(_WORD *)(raw + 318))
          *(_WORD *)(raw + 2026) = 0;
      }
      else
      {
        *(_WORD *)(raw + 2026) = 0;
      }
    }
  }
}
else
{
  *(_WORD *)(raw + 2028) = 0;
}
if (!*(_WORD *)(raw + 390) && !*(_WORD *)(*(_DWORD *)(raw + 368) + 1164))
{
  v5 = *(__int16 *)(raw + 316);
if (v5 <= 300)
{
  if (v5 != 300)
  {
switch ( v5 )
{
case 0:
resolve_stage_surface_landing_transition();
if ( !*(float *)(raw + 244) )
  *(_BYTE *)(raw + 1150) = 0;
if ( !*(_BYTE *)(raw + 1150) )
{
  zero_velocity_acceleration();
  advance_frame_and_dispatch();
  return;
}
if ( *(float *)(raw + 244) > 0.0f )
{
  v228 = *(float *)(raw + 244) - 0.5f;
  *(float *)(raw + 244) = v228;
  if ( v228 < 0.0f )
  {
    zero_velocity_acceleration();
    *(_BYTE *)(raw + 1150) = 0;
  }
}
if ( !(*(float *)(raw + 244) < 0.0f)
  || (v229 = *(float *)(raw + 244) + 0.5f,
      *(float *)(raw + 244) = v229,
      !(v229 > 0.0f)) )
{
  goto LABEL_101;
}
zero_velocity_acceleration();
*(_BYTE *)(raw + 1150) = 0;
advance_frame_and_dispatch();
return;
case 1:
resolve_stage_surface_landing_transition();
if ( *(_BYTE *)(raw +  1150) )
{
v7 = 0.0;
if ( *(float *)(raw +  244) > 0.0 )
{
v230 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v230;
if ( v230 < 0.0 )
{
zero_velocity_acceleration();
v7 = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( v7 > *(float *)(raw +  244) )
{
v231 = *(float *)(raw +  244) + 0.5;
*(float *)(raw +  244) = v231;
if ( v231 > v7 )
{
zero_velocity_acceleration();
*(_BYTE *)(raw +  1150) = 0;
}
}
}
else
{
zero_velocity_acceleration();
}
if ( (unsigned __int8)advance_frame_and_dispatch() && !*(_WORD *)(raw +  320) )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 2);
return;
case 2:
resolve_stage_surface_landing_transition();
if ( !*(_BYTE *)(raw + 1150) )
{
  zero_velocity_acceleration();
  advance_frame_and_dispatch();
  return;
}
if ( *(float *)(raw + 244) > 0.0f )
{
  v228 = *(float *)(raw + 244) - 0.5f;
  *(float *)(raw + 244) = v228;
  if ( v228 < 0.0f )
  {
    zero_velocity_acceleration();
    *(_BYTE *)(raw + 1150) = 0;
  }
}
if ( !(*(float *)(raw + 244) < 0.0f)
  || (v229 = *(float *)(raw + 244) + 0.5f,
      *(float *)(raw + 244) = v229,
      !(v229 > 0.0f)) )
{
  goto LABEL_101;
}
zero_velocity_acceleration();
*(_BYTE *)(raw + 1150) = 0;
advance_frame_and_dispatch();
return;
case 3:
resolve_stage_surface_landing_transition();
if ( *(_BYTE *)(raw +  1150) )
{
v8 = 0.0;
if ( *(float *)(raw +  244) > 0.0 )
{
v232 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v232;
if ( v232 < 0.0 )
{
zero_velocity_acceleration();
v8 = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( v8 > *(float *)(raw +  244) )
{
v233 = *(float *)(raw +  244) + 0.5;
*(float *)(raw +  244) = v233;
if ( v233 > v8 )
{
zero_velocity_acceleration();
*(_BYTE *)(raw +  1150) = 0;
}
}
}
else
{
zero_velocity_acceleration();
}
if ( !(unsigned __int8)advance_frame_and_dispatch() )
return;
if ( *(_WORD *)(raw +  320) )
return;
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
case 4:
resolve_stage_surface_landing_transition();
*(float *)(raw +  244) = 4.0;
advance_frame_and_dispatch();
return;
case 5:
resolve_stage_surface_landing_transition();
*(float *)(raw +  244) = -4.0;
advance_frame_and_dispatch();
return;
case 6:
v10 = *(_WORD *)(raw +  318) <= 0;
if ( !*(_WORD *)(raw +  318) )
{
resolve_stage_surface_landing_transition();
v10 = *(_WORD *)(raw +  318) <= 0;
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_BYTE *)(raw +  1150) )
zero_velocity_acceleration();
v10 = *(_WORD *)(raw +  318) <= 0;
}
}
if ( !v10 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
goto LABEL_99;
}
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v11 = 0.0;
goto LABEL_71;
case 7:
v12 = *(_WORD *)(raw +  318) <= 0;
if ( !*(_WORD *)(raw +  318) )
{
resolve_stage_surface_landing_transition();
v12 = *(_WORD *)(raw +  318) <= 0;
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_BYTE *)(raw +  1150) )
zero_velocity_acceleration();
v12 = *(_WORD *)(raw +  318) <= 0;
}
}
if ( !v12 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
goto LABEL_99;
}
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v11 = 6.5f;
goto LABEL_71;
case 8:
v13 = *(_WORD *)(raw +  318) <= 0;
if ( !*(_WORD *)(raw +  318) )
{
resolve_stage_surface_landing_transition();
v13 = *(_WORD *)(raw +  318) <= 0;
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_BYTE *)(raw +  1150) )
zero_velocity_acceleration();
v13 = *(_WORD *)(raw +  318) <= 0;
}
}
if ( !v13 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
goto LABEL_99;
}
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v11 = -6.5f;
LABEL_71:
*(float *)(raw +  244) = v11;
*(float *)(raw +  248) = 16.0;
*(float *)(raw +  256) = 0.8f;
*(_BYTE *)(raw +  1150) = 0;
return;
case 9:
if ( 0.0 == *(float *)(raw +  256) )
*(float *)(raw +  256) = 0.60000002;
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
goto LABEL_99;
LABEL_101:
advance_frame_and_dispatch();
return;
case 0xA:
resolve_stage_surface_landing_transition();
zero_velocity_acceleration();
if ( (unsigned __int8)advance_frame_and_dispatch() )
{
v14 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8);
if ( *(_DWORD *)(raw +  1720) )
v14(raw, 2);
else
v14(raw, 0);
}
return;
case 0xC5:
v15 = *(_WORD *)(raw +  318);
if ( !v15 || v15 == 3 )
resolve_stage_surface_landing_transition();
if ( *(__int16 *)(raw +  318) < 3 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
return;
}
}
if ( !(unsigned __int8)advance_frame_and_dispatch() )
goto LABEL_117;
v16 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8);
if ( *(_BYTE *)(raw +  1836) == 2 )
{
v16(raw, 700);
*(_WORD *)(raw +  1192) = 3;
*(_WORD *)(raw +  1196) = 3;
return;
}
v16(raw, 0);
if ( *(int *)(raw +  1720) > 0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 1);
LABEL_117:
if ( *(_WORD *)(raw +  318) == 3 && *(_WORD *)(raw +  320) == 2 && !*(_WORD *)(raw +  322) )
{
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) < (double)*(float *)(raw +  236) )
*(_BYTE *)(raw +  260) = -1;
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) > (double)*(float *)(raw +  236) )
*(_BYTE *)(raw +  260) = 1;
}
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
*(float *)(raw +  248) = 8.0;
v17 = 13.5f;
*(float *)(raw +  244) = v17;
*(float *)(raw +  256) = 0.5;
return;
case 0xC6:
v18 = *(_WORD *)(raw +  318);
if ( !v18 || v18 == 3 )
resolve_stage_surface_landing_transition();
if ( *(__int16 *)(raw +  318) < 3 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
return;
}
}
if ( !(unsigned __int8)advance_frame_and_dispatch() )
goto LABEL_140;
v19 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8);
if ( *(_BYTE *)(raw +  1836) == 2 )
{
v19(raw, 700);
*(_WORD *)(raw +  1192) = 3;
*(_WORD *)(raw +  1196) = 3;
}
else
{
v19(raw, 0);
if ( *(int *)(raw +  1720) > 0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 1);
LABEL_140:
if ( *(_WORD *)(raw +  318) == 3 && *(_WORD *)(raw +  320) == 2 && !*(_WORD *)(raw +  322) )
{
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) < (double)*(float *)(raw +  236) )
*(_BYTE *)(raw +  260) = -1;
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) > (double)*(float *)(raw +  236) )
*(_BYTE *)(raw +  260) = 1;
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  248) = 8.0;
v17 = -13.5f;
*(float *)(raw +  244) = v17;
*(float *)(raw +  256) = 0.5;
}
}
return;
case 0xC7:
resolve_stage_surface_landing_transition();
if ( !(unsigned __int8)advance_frame_and_dispatch() )
goto LABEL_156;
v16 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8);
if ( *(_BYTE *)(raw +  1836) == 2 )
{
v16(raw, 700);
*(_WORD *)(raw +  1192) = 3;
*(_WORD *)(raw +  1196) = 3;
}
else
{
v16(raw, 0);
if ( *(int *)(raw +  1720) > 0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 1);
LABEL_156:
if ( !*(_WORD *)(raw +  318) && *(_WORD *)(raw +  320) == 6 && !*(_WORD *)(raw +  322) )
{
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) < (double)*(float *)(raw +  236) )
*(_BYTE *)(raw +  260) = -1;
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) > (double)*(float *)(raw +  236) )
*(_BYTE *)(raw +  260) = 1;
}
}
return;
case 0xC8:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  1150) = 1;
configure_render_history(3, 4, 16776960);
advance_frame_and_dispatch();
if ( *(_WORD *)(raw +  318) != 1 )
goto LABEL_174;
if ( !(*(_DWORD *)(raw +  324) % 5) )
{
v210 = *(unsigned __int8 *)(raw +  260);
v433 = *(float *)(raw +  236) + 50.0;
v234 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v186 = v234;
v235 = v433 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v235, v186, v210, 1);
}
if ( *(int *)(raw +  1720) >= 0 )
{
v21 = ++*(_WORD *)(raw +  1840);
if ( (*(_DWORD *)(raw +  1716) * *(char *)(raw +  260) > 0 || v21 <= 5) && v21 <= 60 )
{
LABEL_174:
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  244) = 15.0;
v211 = *(unsigned __int8 *)(raw +  260);
v236 = *(float *)(raw +  240) + 80.0;
v187 = v236;
v237 = (double)(30 * (char)v211) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(125, v237, v187, v211, 1);
v238 = *(float *)(raw +  240) + 80.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v238, *(unsigned __int8 *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
}
else
{
LABEL_173:
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 204);
}
}
else
{
v20 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8);
if ( *(_DWORD *)(raw +  1716) * *(char *)(raw +  260) <= 0 )
v20(raw, 211);
else
v20(raw, 212);
}
return;
case 0xC9:
resolve_stage_surface_landing_transition();
v239 = *(float *)(raw +  244) + 1.75;
*(float *)(raw +  244) = v239;
if ( v239 > 0.0 )
*(float *)(raw +  244) = 0.0;
if ( !(*(_DWORD *)(raw +  324) % 5) )
{
v434 = *(float *)(raw +  236) + 50.0;
v212 = (unsigned __int8)-*(_BYTE *)(raw +  260);
v240 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v188 = v240;
v241 = v434 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v241, v188, v212, 1);
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
*(float *)(raw +  244) = 0.0;
return;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 1 )
{
*(float *)(raw +  244) = -25.0;
v242 = *(float *)(raw +  240) + 80.0;
emit_fighter_effect_433cc0(125, *(float *)(raw +  236), v242, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
v243 = *(float *)(raw +  240) + 80.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v243, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
return;
case 0xCA:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 10);
return;
}
v22 = *(_WORD *)(raw +  318);
if ( (v22 == 1 || v22 == 2) && !(*(_DWORD *)(raw +  324) % 5) )
{
v213 = *(unsigned __int8 *)(raw +  260);
v435 = *(float *)(raw +  236) + 50.0;
v244 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v189 = v244;
v245 = v435 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v245, v189, v213, 1);
}
advance_frame_and_dispatch();
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 1 )
{
*(float *)(raw +  244) = 10.0;
*(float *)(raw +  248) = 5.0;
*(float *)(raw +  256) = 0.5;
v214 = *(unsigned __int8 *)(raw +  260);
v246 = *(float *)(raw +  240) + 110.0;
v190 = v246;
v247 = (double)(80 * (char)v214) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(125, v247, v190, v214, 1);
v248 = *(float *)(raw +  240) + 110.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v248, *(unsigned __int8 *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 2 )
{
face_opponent_and_flip_horizontal_velocity();
}
return;
case 0xCB:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 10);
return;
}
if ( *(__int16 *)(raw +  318) < 3 && !(*(_DWORD *)(raw +  324) % 5) )
{
v436 = *(float *)(raw +  236) + 50.0;
v215 = (unsigned __int8)-*(_BYTE *)(raw +  260);
v249 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v191 = v249;
v250 = v436 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v250, v191, v215, 1);
}
advance_frame_and_dispatch();
if ( !*(_DWORD *)(raw +  324) )
{
if ( !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  244) = -10.0;
*(float *)(raw +  248) = 5.0;
*(float *)(raw +  256) = 0.5;
v251 = *(float *)(raw +  240) + 120.0;
emit_fighter_effect_433cc0(125, *(float *)(raw +  236), v251, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
v252 = *(float *)(raw +  240) + 120.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v252, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 2 )
{
face_opponent_and_flip_horizontal_velocity();
}
}
return;
case 0xCC:
resolve_stage_surface_landing_transition();
v253 = *(float *)(raw +  244) - 0.75;
*(float *)(raw +  244) = v253;
if ( v253 < 0.0 )
{
*(float *)(raw +  244) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
*(_BYTE *)(raw +  1150) = 0;
}
return;
case 0xD0:
if ( !*(_WORD *)(raw +  318) )
resolve_stage_surface_landing_transition();
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( is_y_at_or_below_stage_surface(this) || *(float *)(raw +  248) > 0.0 )
*(_WORD *)(raw +  1198) = 2;
if ( *(__int16 *)(raw +  318) > 0 )
{
v254 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v254;
if ( v254 < -20.0 )
*(float *)(raw +  248) = -20.0;
}
if ( *(_WORD *)(raw +  318) == 1 && *(float *)(raw +  248) < 4.0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v23 = 0.0;
*(float *)(raw +  244) = v23;
*(float *)(raw +  248) = 23.0;
v24 = 0.75;
*(float *)(raw +  256) = v24;
*(_BYTE *)(raw +  1150) = 0;
v216 = *(unsigned __int8 *)(raw +  260);
{
emit_fighter_effect_433cc0(63, *(float *)(raw +  236), *(float *)(raw +  240), v216, 1);
return;
}
return;
case 0xD1:
if ( !*(_WORD *)(raw +  318) )
resolve_stage_surface_landing_transition();
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( is_y_at_or_below_stage_surface(this) || *(float *)(raw +  248) > 0.0 )
*(_WORD *)(raw +  1198) = 2;
if ( *(__int16 *)(raw +  318) > 0 )
{
v255 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v255;
if ( v255 < -20.0 )
*(float *)(raw +  248) = -20.0;
}
if ( *(_WORD *)(raw +  318) == 1 && *(float *)(raw +  248) < 4.0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v25 = 11.0f;
*(float *)(raw +  244) = v25;
*(float *)(raw +  248) = 17.5;
*(float *)(raw +  256) = 0.8f;
*(_BYTE *)(raw +  1150) = 0;
emit_fighter_effect_433cc0(63,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1);
return;
case 0xD2:
if ( !*(_WORD *)(raw +  318) )
resolve_stage_surface_landing_transition();
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( is_y_at_or_below_stage_surface(this) || *(float *)(raw +  248) > 0.0 )
*(_WORD *)(raw +  1198) = 2;
if ( *(__int16 *)(raw +  318) > 0 )
{
v256 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v256;
if ( v256 < -20.0 )
*(float *)(raw +  248) = -20.0;
}
if ( *(_WORD *)(raw +  318) == 1 && *(float *)(raw +  248) < 4.0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v25 = -11.0f;
{
*(float *)(raw +  244) = v25;
*(float *)(raw +  248) = 17.5;
*(float *)(raw +  256) = 0.8f;
*(_BYTE *)(raw +  1150) = 0;
emit_fighter_effect_433cc0(63,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1);
return;
}
case 0xD3:
if ( !*(_WORD *)(raw +  318) )
resolve_stage_surface_landing_transition();
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( is_y_at_or_below_stage_surface(this) || *(float *)(raw +  248) > 0.0 )
*(_WORD *)(raw +  1198) = 2;
if ( *(__int16 *)(raw +  318) > 0 )
{
v257 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v257;
if ( v257 < -20.0 )
*(float *)(raw +  248) = -20.0;
}
if ( *(_WORD *)(raw +  318) == 1 && *(float *)(raw +  248) < 4.0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v23 = 3.0;
{
*(float *)(raw +  244) = v23;
*(float *)(raw +  248) = 23.0;
v24 = 0.75;
*(float *)(raw +  256) = v24;
*(_BYTE *)(raw +  1150) = 0;
v216 = *(unsigned __int8 *)(raw +  260);
emit_fighter_effect_433cc0(63, *(float *)(raw +  236), *(float *)(raw +  240), v216, 1);
return;
}
case 0xD4:
case 0xDD:
if ( !*(_WORD *)(raw +  318) )
resolve_stage_surface_landing_transition();
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( is_y_at_or_below_stage_surface(this) || *(float *)(raw +  248) > 0.0 )
*(_WORD *)(raw +  1198) = 2;
if ( *(__int16 *)(raw +  318) > 0 )
{
v258 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v258;
if ( v258 < -20.0 )
*(float *)(raw +  248) = -20.0;
}
if ( *(_WORD *)(raw +  318) == 1 && *(float *)(raw +  248) < 4.0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v26 = 11.0f;
*(float *)(raw +  244) = v26;
*(float *)(raw +  248) = 17.5;
v24 = 0.8f;
{
*(float *)(raw +  256) = v24;
*(_BYTE *)(raw +  1150) = 0;
v216 = *(unsigned __int8 *)(raw +  260);
emit_fighter_effect_433cc0(63, *(float *)(raw +  236), *(float *)(raw +  240), v216, 1);
return;
}
case 0xD6:
if ( (unsigned __int8)advance_frame_and_dispatch() )
goto LABEL_933_A;
if ( !*(_DWORD *)(raw +  324) )
{
if ( !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
dispatch_indexed_event_member(0x1Fu);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 6 )
{
goto LABEL_933_A;
}
}
v27 = *(_DWORD *)(raw +  1720);
v28 = *(char *)(raw +  260);
v29 = v27 < 0;
v10 = v27 <= 0;
v30 = *(_DWORD *)(raw +  1716);
if ( v10 )
{
if ( v29 )
{
v32 = v28 * v30;
if ( v32 <= 0 )
*(_WORD *)(raw +  1842) = v32 >= 0 ? 90 : 135;
else
*(_WORD *)(raw +  1842) = 45;
}
else
{
v33 = v28 * v30;
if ( v33 <= 0 )
{
if ( v33 < 0 )
*(_WORD *)(raw +  1842) = 180;
}
else
{
*(_WORD *)(raw +  1842) = 0;
}
}
}
else
{
v31 = v28 * v30;
if ( v31 <= 0 )
*(_WORD *)(raw +  1842) = v31 >= 0 ? -90 : -135;
else
*(_WORD *)(raw +  1842) = -45;
}
v34 = *(_WORD *)(raw +  318);
if ( v34 == 5 || v34 == 6 )
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
v35 = *(_WORD *)(raw +  318);
if ( v35 <= 0 || v35 >= 5 )
goto LABEL_1771;
++*(_WORD *)(raw +  1846);
v36 = *(_WORD *)(raw +  1842) - (int)*(float *)(raw +  1856);
*(_WORD *)(raw +  1844) = v36;
if ( v36 > 180 )
*(_WORD *)(raw +  1844) = v36 - 360;
v37 = *(_WORD *)(raw +  1844);
if ( v37 < -180 )
*(_WORD *)(raw +  1844) = v37 + 360;
v38 = *(__int16 *)(raw +  1844) < 0;
if ( *(__int16 *)(raw +  1844) > 0 )
{
v39 = *(float *)(raw +  1856);
if ( *(_DWORD *)(raw +  1208) )
v40 = v39 + 0.25;
else
v40 = v39 + 1.0;
*(float *)(raw +  1856) = v40;
v38 = *(__int16 *)(raw +  1844) < 0;
}
if ( v38 )
{
if ( *(_DWORD *)(raw +  1208) )
v41 = *(float *)(raw +  1856) - 0.25;
else
v41 = *(float *)(raw +  1856) - 1.0;
*(float *)(raw +  1856) = v41;
}
*(float *)(raw +  244) = lookup_orientation_cosine_quantized_abs(*(float *)(raw +  1856)) * *(float *)(raw +  1852);
v259 = lookup_orientation_sine_quantized_abs(*(float *)(raw +  1856)) * *(float *)(raw +  1852);
*(float *)(raw +  248) = v259;
if ( *(float *)(raw +  240) > 680.0 && v259 > 0.0 )
*(float *)(raw +  248) = 0.0;
if ( *(_DWORD *)(raw +  1208) )
adjust_counter_482(12, 1);
else
adjust_counter_482(6, 1);
*(float *)(raw +  300) = -*(float *)(raw +  1856);
v42 = 0.0;
if ( *(float *)(raw +  244) < 0.0 )
*(float *)(raw +  300) = 180.0 - *(float *)(raw +  1856);
if ( *(float *)(raw +  244) < 0.0 && *(_WORD *)(raw +  318) == 1 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
v42 = 0.0;
}
if ( v42 <= *(float *)(raw +  244) && *(_WORD *)(raw +  318) == 3 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 1);
v42 = 0.0;
}
if ( v42 > *(float *)(raw +  244) && *(_WORD *)(raw +  318) == 2 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 4);
v42 = 0.0;
}
if ( v42 <= *(float *)(raw +  244) && *(_WORD *)(raw +  318) == 4 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
if ( *(_DWORD *)(raw +  324) % 5 == 1 )
{
v217 = *(unsigned __int8 *)(raw +  260);
v260 = lookup_orientation_sine_quantized_abs(*(float *)(raw +  1856)) * 100.0 + *(float *)(raw +  240) + 100.0;
v192 = v260;
v261 = lookup_orientation_cosine_quantized_abs(*(float *)(raw +  1856)) * 100.0 * (double)*(char *)(raw +  260) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(125, v261, v192, v217, 1);
}
if ( ((v43 = *(_DWORD *)(raw +  1736)) != 0 || *(__int16 *)(raw +  1846) <= 10)
&& *(__int16 *)(raw +  1154) > 0
|| (v43 || *(__int16 *)(raw +  1846) <= 10) && *(__int16 *)(raw +  1154) > 0 )
{
LABEL_1771:
if ( has_crossed_stage_surface_while_descending() )
{
*(float *)(raw +  240) = stage_surface_height_at_x(this);
*(float *)(raw +  256) = 0.0;
*(float *)(raw +  248) = 0.0;
if ( *(__int16 *)(raw +  318) >= 5 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 10);
zero_velocity_acceleration();
}
else
{
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 215);
}
}
return;
}
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
v44 = *(_WORD *)(raw +  318);
if ( v44 != 1 && v44 != 2 )
goto LABEL_392;
v45 = *(_BYTE *)(raw +  260);
v46 = *(float *)(raw +  236);
if ( v45 == 1 )
{
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) < v46 )
{
*(_BYTE *)(raw +  260) = -1;
v47 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12);
*(float *)(raw +  244) = -*(float *)(raw +  244);
v47(raw, 6);
goto LABEL_392;
}
}
else if ( *(float *)(*(_DWORD *)(raw +  368) + 236) > v46 )
{
*(_BYTE *)(raw +  260) = -v45;
*(float *)(raw +  244) = -*(float *)(raw +  244);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 6);
goto LABEL_392;
}
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 5);
LABEL_392:
v48 = *(_WORD *)(raw +  318);
if ( v48 == 3 || v48 == 4 )
{
v49 = *(_BYTE *)(raw +  260);
v50 = *(float *)(raw +  236);
if ( v49 == 1 )
{
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) < v50 )
{
*(_BYTE *)(raw +  260) = -1;
v51 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12);
*(float *)(raw +  244) = -*(float *)(raw +  244);
v51(raw, 5);
return;
}
goto LABEL_397;
}
if ( *(float *)(*(_DWORD *)(raw +  368) + 236) <= v50 )
{
LABEL_397:
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 6);
return;
}
*(_BYTE *)(raw +  260) = -v49;
v52 = *(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12);
*(float *)(raw +  244) = -*(float *)(raw +  244);
v52(raw, 5);
}
break;
case 0xD7:
resolve_stage_surface_landing_transition();
if ( *(float *)(raw +  244) > 0.0 )
{
v262 = *(float *)(raw +  244) - 0.75;
*(float *)(raw +  244) = v262;
if ( v262 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( *(float *)(raw +  244) < 0.0 )
{
v263 = *(float *)(raw +  244) + 0.75;
*(float *)(raw +  244) = v263;
if ( v263 > 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
goto LABEL_1755;
return;
case 0xDC:
if ( !*(_WORD *)(raw +  318) )
resolve_stage_surface_landing_transition();
if ( has_crossed_stage_surface_while_descending() )
{
LABEL_99:
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
goto LABEL_100;
}
if ( is_y_at_or_below_stage_surface(this) || *(float *)(raw +  248) > 0.0 )
*(_WORD *)(raw +  1198) = 2;
if ( *(__int16 *)(raw +  318) > 0 )
{
v264 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v264;
if ( v264 < -20.0 )
*(float *)(raw +  248) = -20.0;
}
if ( *(_WORD *)(raw +  318) == 1 && *(float *)(raw +  248) < 4.0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
advance_frame_and_dispatch();
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  244) = 0.0;
*(float *)(raw +  248) = 23.0;
*(float *)(raw +  256) = 0.75;
*(_BYTE *)(raw +  1150) = 0;
v216 = *(unsigned __int8 *)(raw +  260);
emit_fighter_effect_433cc0(63, *(float *)(raw +  236), *(float *)(raw +  240), v216, 1);
}
return;
case 0xDE:
if ( !*(_WORD *)(raw +  318) )
resolve_stage_surface_landing_transition();
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( is_y_at_or_below_stage_surface(this) || *(float *)(raw +  248) > 0.0 )
*(_WORD *)(raw +  1198) = 2;
if ( *(__int16 *)(raw +  318) > 0 )
{
v265 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v265;
if ( v265 < -20.0 )
*(float *)(raw +  248) = -20.0;
}
if ( *(_WORD *)(raw +  318) == 1 && *(float *)(raw +  248) < 4.0 )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
advance_frame_and_dispatch();
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 1 )
{
return;
}
v26 = -11.0f;
{
*(float *)(raw +  244) = v26;
*(float *)(raw +  248) = 17.5;
v24 = 0.8f;
*(float *)(raw +  256) = v24;
*(_BYTE *)(raw +  1150) = 0;
v216 = *(unsigned __int8 *)(raw +  260);
emit_fighter_effect_433cc0(63, *(float *)(raw +  236), *(float *)(raw +  240), v216, 1);
return;
}
case 0xDF:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  1150) = 1;
advance_frame_and_dispatch();
if ( *(_WORD *)(raw +  318) == 1 )
{
if ( !(*(_DWORD *)(raw +  324) % 5) )
{
v218 = *(unsigned __int8 *)(raw +  260);
v437 = *(float *)(raw +  236) + 50.0;
v266 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v193 = v266;
v267 = v437 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v267, v193, v218, 1);
}
v53 = ++*(_WORD *)(raw +  1840);
if ( *(_DWORD *)(raw +  1716) * *(char *)(raw +  260) <= 0 && v53 > 15 )
goto LABEL_173;
if ( v53 > 60 )
goto LABEL_173;
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  244) = 7.5;
v219 = *(unsigned __int8 *)(raw +  260);
v268 = *(float *)(raw +  240) + 80.0;
v194 = v268;
v269 = (double)(30 * (char)v219) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(125, v269, v194, v219, 1);
v270 = *(float *)(raw +  240) + 80.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v270, *(unsigned __int8 *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
return;
case 0xE0:
v54 = *(_WORD *)(raw +  318);
if ( !v54 || v54 == 3 )
{
resolve_stage_surface_landing_transition();
v3 = 0.0;
}
if ( *(_WORD *)(raw +  318) == 3 )
{
v271 = *(float *)(raw +  244) + 2.0;
*(float *)(raw +  244) = v271;
if ( v271 > v3 )
*(float *)(raw +  244) = v3;
}
if ( !is_y_at_or_below_stage_surface(this) && !(*(_DWORD *)(raw +  324) % 5) )
{
v438 = *(float *)(raw +  236) + 50.0;
v220 = (unsigned __int8)-*(_BYTE *)(raw +  260);
v272 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v195 = v272;
v273 = v438 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v273, v195, v220, 1);
}
if ( *(__int16 *)(raw +  318) < 3
&& (*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256), has_crossed_stage_surface_while_descending()) )
{
*(float *)(raw +  248) = 0.0;
*(float *)(raw +  256) = 0.0;
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
}
else if ( (unsigned __int8)advance_frame_and_dispatch() )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
*(float *)(raw +  244) = 0.0;
}
else if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  244) = -15.0;
*(float *)(raw +  248) = 5.0;
*(float *)(raw +  256) = 0.75;
v274 = *(float *)(raw +  240) + 80.0;
emit_fighter_effect_433cc0(125, *(float *)(raw +  236), v274, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
v275 = *(float *)(raw +  240) + 80.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v275, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
return;
case 0xE2:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 10);
return;
}
else
{
v55 = *(_WORD *)(raw +  318);
if ( (v55 == 1 || v55 == 2) && !(*(_DWORD *)(raw +  324) % 5) )
{
v221 = *(unsigned __int8 *)(raw +  260);
v439 = *(float *)(raw +  236) + 50.0;
v276 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v196 = v276;
v277 = v439 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v277, v196, v221, 1);
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 1 )
{
*(_WORD *)(raw +  1840) = 0;
*(float *)(raw +  244) = 10.0;
*(float *)(raw +  248) = 5.0;
*(float *)(raw +  256) = 0.5;
v222 = *(unsigned __int8 *)(raw +  260);
v278 = *(float *)(raw +  240) + 110.0;
v197 = v278;
v279 = (double)(80 * (char)v222) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(125, v279, v197, v222, 1);
v280 = *(float *)(raw +  240) + 110.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v280, *(unsigned __int8 *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 2 )
{
face_opponent_and_flip_horizontal_velocity();
}
}
return;
case 0xE1:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 10);
return;
}
if ( *(__int16 *)(raw +  318) < 3 && !(*(_DWORD *)(raw +  324) % 5) )
{
v440 = *(float *)(raw +  236) + 50.0;
v223 = (unsigned __int8)-*(_BYTE *)(raw +  260);
v281 = (float)(mt19937_next_u32() % 0xC8) + *(float *)(raw +  240);
v198 = v281;
v282 = v440 - (float)(mt19937_next_u32() % 0x64);
emit_fighter_effect_433cc0(124, v282, v198, v223, 1);
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
if ( !*(_DWORD *)(raw +  324) )
{
if ( !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  244) = -10.0;
*(float *)(raw +  248) = 5.0;
*(float *)(raw +  256) = 0.5;
v283 = *(float *)(raw +  240) + 120.0;
emit_fighter_effect_433cc0(125, *(float *)(raw +  236), v283, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
v284 = *(float *)(raw +  240) + 120.0;
emit_fighter_effect_433cc0(126, *(float *)(raw +  236), v284, (unsigned __int8)-*(_BYTE *)(raw +  260), 1);
dispatch_indexed_event_member(0x1Fu);
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 2 )
{
face_opponent_and_flip_horizontal_velocity();
}
}
return;
default:
goto LABEL_1766;
}
  }
  else
  {
resolve_stage_surface_landing_transition();
if ( !(unsigned __int8)try_dispatch_directional_action_208_210(0) )
{
if ( *(_BYTE *)(raw +  1150) )
{
v285 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v285;
if ( v285 < 0.0 )
{
*(float *)(raw +  244) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
dispatch_indexed_event_member(0x1Cu);
*(_BYTE *)(raw +  1150) = 0;
}
}
  }
}
else
{
  if (v5 <= 561)
  {
    if (v5 < 560)
    {
switch ( v5 )
{
case 0x12D:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)try_dispatch_directional_action_208_210(0) )
return;
if ( *(_BYTE *)(raw +  1150) )
{
v286 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v286;
v56 = 0.0;
if ( v286 < 0.0 )
{
*(float *)(raw +  244) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
else
{
v56 = 0.0;
}
if ( *(__int16 *)(raw +  320) >= 4 )
{
v287 = *(float *)(raw +  244) - 1.5;
*(float *)(raw +  244) = v287;
if ( v287 < v56 )
*(float *)(raw +  244) = v56;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
*(float *)(raw +  244) = 5.0;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
{
*(float *)(raw +  244) = 10.0;
dispatch_indexed_event_member(0x1Bu);
*(_BYTE *)(raw +  1150) = 0;
}
if ( *(_WORD *)(raw +  320) <= 3 )
return;
v288 = *(float *)(raw +  244) - 1.0;
v58 = v288;
*(float *)(raw +  244) = v58;
if ( v58 < 0.0 )
*(float *)(raw +  244) = 0.0;
return;
case 0x12E:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)try_dispatch_directional_action_208_210(1) )
return;
if ( !*(_DWORD *)(raw +  1724) )
*(_BYTE *)(raw +  1872) = 0;
if ( *(_BYTE *)(raw +  1150) )
{
v289 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v289;
if ( v289 < 0.0 )
{
*(float *)(raw +  244) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch()
|| !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
goto LABEL_1755;
}
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
if ( *(_BYTE *)(raw +  1872) == 1 )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
v59 = *(unsigned __int8 *)(raw +  260);
v290 = *(float *)(raw +  240) + 106.0;
v199 = v290;
v291 = (double)(70 * (char)v59) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(62, v291, v199, v59, 1);
}
else
{
*(float *)(raw +  244) = 20.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
dispatch_indexed_event_member(0x1Du);
*(float *)v475 = 0.0;
*(float *)&v475[1] = 0.0;
*(float *)&v475[2] = 0.0;
spawn_owned_object_via_manager(848,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v475,
3);
}
if ( *(__int16 *)(raw +  320) >= 5 )
{
v292 = *(float *)(raw +  244) - 2.0;
*(float *)(raw +  244) = v292;
if ( v292 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
}
v61 = 0.0;
if ( *(_WORD *)(raw +  318) != 1 )
return;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
*(float *)(raw +  244) = 30.0;
*(_BYTE *)(raw +  1150) = 0;
dispatch_indexed_event_member(0x1Du);
*(float *)v469 = 0.0;
*(float *)&v469[1] = 0.0;
*(float *)&v469[2] = 0.0;
spawn_owned_object_via_manager(848,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v469,
3);
}
if ( *(__int16 *)(raw +  320) >= 2 )
{
v293 = *(float *)(raw +  244) - 2.0;
*(float *)(raw +  244) = v293;
if ( v293 < v61 )
*(float *)(raw +  244) = v61;
}
return;
case 0x12F:
resolve_stage_surface_landing_transition();
if ( !(unsigned __int8)try_dispatch_directional_action_208_210(0) )
{
if ( *(char *)(raw +  1150) > 0 )
{
v294 = *(float *)(raw +  244) - 0.6000000238418579;
*(float *)(raw +  244) = v294;
if ( v294 < 0.0 )
{
*(float *)(raw +  244) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 2);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 1 )
dispatch_indexed_event_member(0x1Cu);
}
return;
case 0x130:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)try_dispatch_directional_action_208_210(1) )
return;
if ( !*(_DWORD *)(raw +  1724) )
*(_BYTE *)(raw +  1872) = 0;
if ( *(_BYTE *)(raw +  1150) )
{
v295 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v295;
if ( v295 < 0.0 )
{
*(float *)(raw +  244) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
if ( *(_BYTE *)(raw +  1872) == 1 )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
v63 = *(unsigned __int8 *)(raw +  260);
v296 = *(float *)(raw +  240) + 118.0;
v200 = v296;
v297 = *(float *)(raw +  236) - 95 * (char)v63;
emit_fighter_effect_433cc0(62, v297, v200, v63, 1);
}
else
{
*(float *)(raw +  244) = 10.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 6 )
{
dispatch_indexed_event_member(0x1Du);
*(float *)v483 = 0.0;
*(float *)&v483[1] = 0.0;
*(float *)&v483[2] = 1.0;
spawn_owned_object_via_manager(848,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v483,
3);
}
if ( *(__int16 *)(raw +  320) >= 5 )
{
v298 = *(float *)(raw +  244) - 2.0;
*(float *)(raw +  244) = v298;
if ( v298 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
}
v61 = 0.0;
if ( *(_WORD *)(raw +  318) != 1 )
return;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 1 )
{
*(float *)(raw +  244) = 15.0;
*(_BYTE *)(raw +  1150) = 0;
dispatch_indexed_event_member(0x1Du);
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
v471[0] = v61;
v471[1] = v61;
v471[2] = 1.0;
spawn_owned_object_via_manager(848,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v471,
3);
}
if ( *(__int16 *)(raw +  320) >= 2 )
{
v293 = *(float *)(raw +  244) - 2.0;
*(float *)(raw +  244) = v293;
if ( v293 < v61 )
*(float *)(raw +  244) = v61;
}
return;
case 0x131:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)try_dispatch_directional_action_208_210(1) )
return;
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& !*(_WORD *)(raw +  318) )
{
*(float *)(raw +  248) = 0.0;
*(float *)(raw +  244) = 12.5;
*(float *)(raw +  256) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
goto LABEL_1755;
}
if ( *(_WORD *)(raw +  318) )
goto LABEL_636;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
dispatch_indexed_event_member(0x1Cu);
if ( *(__int16 *)(raw +  320) < 4 )
{
LABEL_636:
v64 = 0.0;
}
else
{
v299 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v299;
v64 = 0.0;
if ( v299 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( *(_WORD *)(raw +  318) == 1 )
{
v300 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v300;
if ( v300 < v64 )
*(float *)(raw +  244) = v64;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
*(float *)(raw +  244) = 20.0;
dispatch_indexed_event_member(0x1Bu);
}
}
return;
case 0x132:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
dispatch_indexed_event_member(0x1Bu);
return;
case 0x133:
if ( *(_WORD *)(raw +  318) == 1 )
{
resolve_stage_surface_landing_transition();
v301 = *(float *)(raw +  244) - 0.699999988079071;
*(float *)(raw +  244) = v301;
if ( v301 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( *(_WORD *)(raw +  318)
|| (*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256), !has_crossed_stage_surface_while_descending()) )
{
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
}
if ( !*(_WORD *)(raw +  318) )
{
v65 = *(_WORD *)(raw +  320);
if ( v65 >= 3 && v65 <= 5 )
{
set_oriented_components_f0_f4(15.0, *(float *)(raw +  1852));
v302 = *(float *)(raw +  1852) - 2.5;
*(float *)(raw +  1852) = v302;
if ( v302 <= 2.0 )
*(float *)(raw +  1852) = 2.0;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
dispatch_indexed_event_member(0x1Du);
*(float *)(raw +  1852) = 30.0;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 6 )
*(float *)(raw +  256) = 0.40000001;
}
}
}
else
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 1);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
*(float *)(raw +  248) = 0.0;
*(float *)(raw +  256) = 0.0;
*(float *)(raw +  244) = *(float *)(raw +  244) * 0.5;
}
return;
case 0x134:
if ( !*(_WORD *)(raw +  318) )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 10);
goto LABEL_100;
}
}
if ( *(_WORD *)(raw +  318) == 1 && has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  12))(2);
{
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
dispatch_indexed_event_member(0x1Du);
*(float *)(raw +  248) = -40.0;
*(float *)(raw +  244) = 0.0;
}
return;
case 0x135:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  8))(10);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
{
dispatch_indexed_event_member(0x1Du);
*(float *)(raw +  248) = 16.0;
*(float *)(raw +  244) = 3.0;
*(float *)(raw +  256) = 0.75;
}
if ( *(_WORD *)(raw +  318) == 1 && *(int *)(raw +  324) >= 15 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
return;
}
return;
case 0x136:
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& !*(_WORD *)(raw +  318) )
{
*(float *)(raw +  244) = 0.0;
*(float *)(raw +  248) = 0.0;
*(float *)(raw +  256) = 0.5;
*(_WORD *)(raw +  1840) = 0;
*(_BYTE *)(raw +  388) = 99;
*(_DWORD *)(raw +  384) = 0;
}
if ( *(_DWORD *)(raw +  384) )
{
if ( (__int16)++*(_WORD *)(raw +  1840) > 5 )
{
*(_DWORD *)(raw +  384) = 0;
*(_WORD *)(raw +  1840) = 0;
}
}
if ( *(_WORD *)(raw +  318) == 1 )
{
if ( !*(_DWORD *)(raw +  324) )
*(float *)(raw +  244) = 17.5;
if ( !(*(_DWORD *)(raw +  324) % 8) )
dispatch_indexed_event_member(0x1Bu);
if ( *(_DWORD *)(raw +  384) )
{
if ( (__int16)++*(_WORD *)(raw +  1840) > 5 )
{
*(_DWORD *)(raw +  384) = 0;
*(_WORD *)(raw +  1840) = 0;
}
}
if ( *(int *)(raw +  324) > 30 )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
*(float *)(raw +  248) = 6.0;
*(float *)(raw +  244) = *(float *)(raw +  244) * 0.5;
}
}
if ( *(_WORD *)(raw +  318) == 2 )
{
v303 = *(float *)(raw +  248) - *(float *)(raw +  256);
*(float *)(raw +  248) = v303;
v441 = v303 + *(float *)(raw +  240);
if ( stage_surface_height_at_x(this) >= v441 )
{
*(float *)(raw +  248) = 0.0;
*(float *)(raw +  240) = stage_surface_height_at_x(this);
LABEL_933_A:
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
return;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
return;
}
return;
case 0x137:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)try_dispatch_directional_action_208_210(0) )
return;
if ( *(char *)(raw +  1150) > 0 )
{
v304 = *(float *)(raw +  244) - 0.6000000238418579;
*(float *)(raw +  244) = v304;
if ( v304 < 0.0 )
{
*(float *)(raw +  244) = 0.0;
*(_BYTE *)(raw +  1150) = 0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 2);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
dispatch_indexed_event_member(0x1Du);
*(float *)(raw +  244) = 10.0;
}
v66 = *(_WORD *)(raw +  320) < 3;
goto LABEL_728;
case 0x140:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)try_dispatch_directional_action_208_210(0) )
return;
if ( *(__int16 *)(raw +  320) > 1 )
{
v306 = *(float *)(raw +  244) - 2.0;
*(float *)(raw +  244) = v306;
if ( v306 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
dispatch_indexed_event_member(0x1Cu);
*(_BYTE *)(raw +  1150) = 0;
}
case 0x141:
resolve_stage_surface_landing_transition();
if ( !(unsigned __int8)try_dispatch_directional_action_208_210(1) )
{
if ( *(__int16 *)(raw +  320) > 3 )
{
v307 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v307;
if ( v307 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
{
dispatch_indexed_event_member(0x1Cu);
*(float *)(raw +  244) = 7.5;
*(_BYTE *)(raw +  1150) = 0;
}
}
return;
case 0x142:
resolve_stage_surface_landing_transition();
if ( !(unsigned __int8)try_dispatch_directional_action_208_210(1) )
{
if ( *(__int16 *)(raw +  320) > 5 )
{
v308 = *(float *)(raw +  244) - 3.0;
*(float *)(raw +  244) = v308;
if ( v308 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 5 )
*(float *)(raw +  244) = 15.0;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 6 )
{
dispatch_indexed_event_member(0x1Du);
*(_BYTE *)(raw +  1150) = 0;
}
}
}
return;
case 0x143:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)try_dispatch_directional_action_208_210(1) )
return;
if ( *(__int16 *)(raw +  320) > 3 )
{
v309 = *(float *)(raw +  244) - 3.0;
*(float *)(raw +  244) = v309;
if ( v309 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_WORD *)(raw +  322) )
return;
if ( *(_WORD *)(raw +  320) == 3 )
*(float *)(raw +  244) = 15.0;
if ( *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) != 2 )
return;
dispatch_indexed_event_member(0x1Du);
*(_BYTE *)(raw +  1150) = 0;
case 0x190:
resolve_stage_surface_landing_transition();
if ( *(__int16 *)(raw +  318) < 2 && !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_DWORD *)(raw +  324) )
goto LABEL_778;
if ( *(_WORD *)(raw +  322) )
return;
if ( !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
goto LABEL_1755;
LABEL_778:
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
{
adjust_counter_482(200, 45);
add_phase_scaled_counter_558(50);
*(float *)v495 = 35.0;
*(float *)&v495[1] = 40.0;
*(float *)&v495[2] = 0.0;
*(float *)&v495[3] = 5.0;
*(float *)&v495[4] = 0.0;
v174 = *(unsigned __int8 *)(raw +  260);
v310 = *(float *)(raw +  240) + 210.0;
v153 = v310;
v311 = *(float *)(raw +  236) - (double)(80 * (char)v174);
spawn_owned_object_via_manager(800, v311, v153, v174, 1, (int)v495, 5);
}
return;
case 0x191:
resolve_stage_surface_landing_transition();
if ( *(__int16 *)(raw +  318) < 2 && !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_DWORD *)(raw +  324) )
goto LABEL_790;
if ( *(_WORD *)(raw +  322) )
return;
if ( !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
LABEL_790:
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
adjust_counter_482(200, 45);
add_phase_scaled_counter_558(50);
*(float *)v492 = -35.0;
*(float *)&v492[1] = 40.0;
*(float *)&v492[2] = 0.0;
*(float *)&v492[3] = 5.0;
*(float *)&v492[4] = 0.0;
v67 = *(unsigned __int8 *)(raw +  260);
v312 = *(float *)(raw +  240) + 25.0;
v154 = v312;
v313 = *(float *)(raw +  236) - (double)(150 * (char)v67);
spawn_owned_object_via_manager(800, v313, v154, v67, 1, (int)v492, 5);
}
return;
case 0x192:
resolve_stage_surface_landing_transition();
if ( *(__int16 *)(raw +  318) < 2 && !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 2);
if ( *(_DWORD *)(raw +  324) )
goto LABEL_802;
if ( *(_WORD *)(raw +  322) )
return;
if ( !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
LABEL_802:
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
adjust_counter_482(200, 45);
add_phase_scaled_counter_558(50);
*(float *)v493 = -120.0;
*(float *)&v493[1] = 30.0;
*(float *)&v493[2] = 0.0;
*(float *)&v493[3] = 5.0;
*(float *)&v493[4] = -25.0;
v68 = *(unsigned __int8 *)(raw +  260);
v314 = *(float *)(raw +  240) + 25.0;
v155 = v314;
v315 = (double)(170 * (char)v68) + *(float *)(raw +  236);
spawn_owned_object_via_manager(800, v315, v155, v68, 1, (int)v493, 5);
}
return;
case 0x194:
if ( *(_WORD *)(raw +  318) == 1 )
resolve_stage_surface_landing_transition();
if ( !*(_WORD *)(raw +  318) )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
*(_BYTE *)(raw +  1151) = 0;
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
goto LABEL_933_B;
}
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
adjust_counter_482(200, 45);
add_phase_scaled_counter_558(50);
*(float *)v494 = 70.0;
*(float *)&v494[1] = 30.0;
*(float *)&v494[2] = 0.0;
*(float *)&v494[3] = 5.0;
*(float *)&v494[4] = 10.0;
v69 = *(unsigned __int8 *)(raw +  260);
v316 = *(float *)(raw +  240) + 225.0;
v156 = v316;
v317 = *(float *)(raw +  236) - (double)(45 * (char)v69);
spawn_owned_object_via_manager(800, v317, v156, v69, 1, (int)v494, 5);
}
return;
case 0x196:
if ( *(_WORD *)(raw +  318) == 1 )
resolve_stage_surface_landing_transition();
if ( !*(_WORD *)(raw +  318) )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
*(_BYTE *)(raw +  1151) = 0;
{
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
goto LABEL_933_B;
}
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
adjust_counter_482(200, 45);
add_phase_scaled_counter_558(50);
*(float *)v496 = 70.0;
*(float *)&v496[1] = 30.0;
*(float *)&v496[2] = 0.0;
*(float *)&v496[3] = 5.0;
*(float *)&v496[4] = 60.0;
v70 = *(unsigned __int8 *)(raw +  260);
v318 = *(float *)(raw +  240) + 225.0;
v157 = v318;
v319 = *(float *)(raw +  236) - (double)(45 * (char)v70);
spawn_owned_object_via_manager(800, v319, v157, v70, 1, (int)v496, 5);
}
return;
case 0x198:
resolve_stage_surface_landing_transition();
v320 = *(float *)(raw +  244) - 0.75;
*(float *)(raw +  244) = v320;
if ( v320 < 0.0 )
*(float *)(raw +  244) = 0.0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 4 )
*(float *)(raw +  244) = 25.5;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
goto LABEL_843;
}
return;
case 0x199:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 10);
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
return;
}
if ( !(unsigned __int8)advance_frame_and_dispatch() )
return;
LABEL_933_B:
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
return;
case 0x19A:
resolve_stage_surface_landing_transition();
if ( *(_WORD *)(raw +  318) == 2 && *(int *)(raw +  324) >= 24 )
goto LABEL_898;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
add_phase_scaled_counter_558(50);
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 1;
adjust_counter_482(200, 60);
}
return;
case 0x19B:
resolve_stage_surface_landing_transition();
if ( *(_WORD *)(raw +  318) == 1 && *(int *)(raw +  324) >= 15 )
goto LABEL_898;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
add_phase_scaled_counter_558(50);
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 2;
adjust_counter_482(200, 60);
}
return;
case 0x19C:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
add_phase_scaled_counter_558(50);
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 3;
adjust_counter_482(200, 60);
}
return;
case 0x19E:
v71 = 4;
v72 = *(_WORD *)(raw +  318) < 4;
if ( *(_WORD *)(raw +  318) == 4 )
{
resolve_stage_surface_landing_transition();
v72 = *(_WORD *)(raw +  318) < 4;
}
if ( v72 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
goto LABEL_875;
}
if ( *(__int16 *)(raw +  318) < 2 && !*(_DWORD *)(raw +  1732) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
add_phase_scaled_counter_558(50);
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 1;
adjust_counter_482(200, 60);
}
v73 = *(_DWORD *)(raw +  324);
if ( v73 || *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) || *(_WORD *)(raw +  318) != 4 )
{
if ( *(_WORD *)(raw +  318) == 2 && v73 >= 24 )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
*(float *)(raw +  256) = 0.60000002;
}
return;
}
goto LABEL_933_B;
case 0x19F:
v71 = 3;
if ( *(_WORD *)(raw +  318) == 3 )
resolve_stage_surface_landing_transition();
v74 = *(_WORD *)(raw +  318);
if ( v74 == 1 && *(int *)(raw +  324) >= 15 )
{
*(float *)(raw +  256) = 0.60000002;
goto LABEL_898;
}
if ( v74 < 3 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
LABEL_875:
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, v71);
*(_BYTE *)(raw +  1151) = 0;
{
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
}
}
}
if ( *(__int16 *)(raw +  318) < 2 && !*(_DWORD *)(raw +  1732) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
add_phase_scaled_counter_558(50);
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 2;
adjust_counter_482(200, 60);
}
if ( *(_DWORD *)(raw +  324)
|| *(_WORD *)(raw +  322)
|| *(_WORD *)(raw +  320)
|| *(_WORD *)(raw +  318) != 3 )
{
return;
}
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
return;
}
case 0x1A0:
v71 = 4;
v75 = *(_WORD *)(raw +  318) < 4;
if ( *(_WORD *)(raw +  318) == 4 )
{
resolve_stage_surface_landing_transition();
v75 = *(_WORD *)(raw +  318) < 4;
}
if ( v75 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
goto LABEL_875;
}
if ( *(__int16 *)(raw +  318) < 2 && !*(_DWORD *)(raw +  1732) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
add_phase_scaled_counter_558(50);
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 3;
adjust_counter_482(200, 60);
}
v73 = *(_DWORD *)(raw +  324);
if ( !v73 && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 4 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 9);
return;
}
if ( *(_WORD *)(raw +  318) == 2 && v73 >= 24 )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
*(float *)(raw +  256) = 0.60000002;
}
return;
case 0x1A2:
resolve_stage_surface_landing_transition();
if ( *(__int16 *)(raw +  320) >= 8 )
{
v321 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v321;
if ( v321 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 6 )
LABEL_843:
dispatch_indexed_event_member(0x1Du);
return;
case 0x1F4:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) != 3 )
return;
*(float *)&v462 = 0.0;
v224 = &v462;
v175 = *(unsigned __int8 *)(raw +  260);
v322 = *(float *)(raw +  240) + 150.0;
v158 = v322;
v323 = (double)(30 * (char)v175) + *(float *)(raw +  236);
v76 = v323;
v147 = v76;
spawn_owned_object_via_manager(810, v147, v158, v175, 1, (int)v224, 1);
*(_DWORD *)(raw +  384) = 1;
dispatch_character_wave_handle(3);
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
return;
case 0x1F5:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) != 3 )
return;
v461 = 0.0;
v224 = (int *)&v461;
v175 = *(unsigned __int8 *)(raw +  260);
v324 = *(float *)(raw +  240) + 150.0;
v158 = v324;
v325 = (double)(30 * (char)v175) + *(float *)(raw +  236);
v76 = v325;
v147 = v76;
spawn_owned_object_via_manager(810, v147, v158, v175, 1, (int)v224, 1);
*(_DWORD *)(raw +  384) = 1;
dispatch_character_wave_handle(3);
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
return;
case 0x1F9:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 4;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) != 6 )
return;
payload_463[0] = 15.0;
payload_463[1] = 0.0;
payload_463[2] = 0.0;
if ( *(char *)(raw +  1544) >= 2 )
payload_463[2] = 3.0;
v225 = (int *)payload_463;
v176 = *(unsigned __int8 *)(raw +  260);
v159 = *(float *)(raw +  240);
v326 = (double)(80 * (char)v176) + *(float *)(raw +  236);
v77 = v326;
v148 = v77;
spawn_owned_object_via_manager(815, v148, v159, v176, 1, (int)v225, 3);
*(_DWORD *)(raw +  384) = 1;
dispatch_character_wave_handle(7);
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
return;
case 0x1FA:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 4;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) != 6 )
return;
payload_465[0] = 25.0;
payload_465[1] = 0.0;
payload_465[2] = 0.0;
if ( *(char *)(raw +  1544) >= 2 )
payload_465[2] = 3.0;
v225 = (int *)payload_465;
v176 = *(unsigned __int8 *)(raw +  260);
v159 = *(float *)(raw +  240);
v327 = (double)(80 * (char)v176) + *(float *)(raw +  236);
v77 = v327;
v148 = v77;
spawn_owned_object_via_manager(815, v148, v159, v176, 1, (int)v225, 3);
*(_DWORD *)(raw +  384) = 1;
dispatch_character_wave_handle(7);
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
return;
case 0x1FE:
case 0x1FF:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 8;
v78 = *(_WORD *)(raw +  318);
if ( v78 == 1 || v78 == 2 )
{
if ( !*(_WORD *)(raw +  1840) )
adjust_counter_482(200, 120);
if ( *(__int16 *)(raw +  1840) % 4 == 0 )
{
dispatch_character_wave_handle(0xDu);
*(float *)v489 = 0.0;
*(float *)&v489[1] = (double)*(__int16 *)(raw +  1840) + 30.0;
*(float *)&v489[2] = 0.0;
v80 = *(unsigned __int8 *)(raw +  260);
v328 = *(float *)(raw +  240) + 74.0;
v160 = v328;
v329 = (double)(170 * (char)v80) + *(float *)(raw +  236);
spawn_owned_object_via_manager(820, v329, v160, v80, 1, (int)v489, 2);
}
++*(_WORD *)(raw +  1840);
}
v81 = *(_WORD *)(raw +  318);
if ( v81 == 1 && *(int *)(raw +  324) >= 16 || v81 == 2 && *(int *)(raw +  324) >= 16 )
goto LABEL_898;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 4 )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
return;
case 0x208:
v82 = *(_WORD *)(raw +  318);
if ( !v82 || v82 == 3 )
{
resolve_stage_surface_landing_transition();
v3 = 0.0;
}
*(_BYTE *)(raw +  380) = 1;
if ( !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
v83 = *(_WORD *)(raw +  318);
if ( v83 == 1 || v83 == 2 )
{
v330 = *(float *)(raw +  244) - 0.4000000059604645;
*(float *)(raw +  244) = v330;
if ( v330 < v3 )
*(float *)(raw +  244) = v3;
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
return;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
{
*(float *)v473 = 0.0;
*(float *)&v473[1] = 0.0;
*(float *)&v473[2] = 0.0;
spawn_owned_object_via_manager(811,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v473,
3);
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
dispatch_character_wave_handle(4u);
*(float *)(raw +  244) = 15.0;
*(float *)(raw +  248) = 15.0;
*(float *)(raw +  256) = 0.75;
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
}
return;
case 0x209:
v84 = *(_WORD *)(raw +  318);
if ( !v84 || v84 == 3 )
{
resolve_stage_surface_landing_transition();
v3 = 0.0;
}
*(_BYTE *)(raw +  380) = 1;
if ( !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
if ( *(_DWORD *)(raw +  324) || *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) )
goto LABEL_1020;
if ( !*(_WORD *)(raw +  318) )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
*(float *)(raw +  244) = 15.0;
v85 = *(unsigned __int8 *)(raw +  260);
v331 = (double)(200 * (char)v85) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(128, v331, *(float *)(raw +  240), v85, -1);
v3 = 0.0;
LABEL_1020:
if ( !*(_WORD *)(raw +  318) )
{
v332 = *(float *)(raw +  244) - 0.75;
*(float *)(raw +  244) = v332;
if ( v332 < v3 )
*(float *)(raw +  244) = v3;
}
}
v86 = *(_WORD *)(raw +  318);
if ( v86 != 1 && v86 != 2 )
goto LABEL_1770;
v333 = *(float *)(raw +  244) - 0.4000000059604645;
*(float *)(raw +  244) = v333;
if ( v333 < v3 )
*(float *)(raw +  244) = v3;
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
}
else
{
LABEL_1770:
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
dispatch_character_wave_handle(4u);
*(float *)v488 = 0.0;
*(float *)&v488[1] = 0.0;
*(float *)&v488[2] = 1.0;
spawn_owned_object_via_manager(811,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v488,
3);
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 14 )
{
*(float *)v467 = 0.0;
*(float *)&v467[1] = 0.0;
*(float *)&v467[2] = 0.0;
spawn_owned_object_via_manager(811,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v467,
3);
}
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
dispatch_character_wave_handle(4u);
*(_DWORD *)(raw +  384) = 0;
*(_BYTE *)(raw +  388) = 1;
*(_BYTE *)(raw +  1997) = 1;
*(float *)(raw +  244) = 15.0;
*(float *)(raw +  248) = 17.5;
*(float *)(raw +  256) = 0.75;
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
}
}
return;
case 0x20D:
v87 = *(_WORD *)(raw +  318);
if ( !v87 || v87 == 2 || v87 == 3 || v87 == 4 || v87 == 1 && *(__int16 *)(raw +  320) >= 6 )
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 5;
if ( !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch()
|| !*(_DWORD *)(raw +  324)
&& (!*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1
|| !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 2
|| !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 3
|| !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 4) )
{
goto LABEL_1755;
}
v88 = *(_WORD *)(raw +  318);
if ( !v88 || v88 == 2 || v88 == 3 || v88 == 4 )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(25);
if ( !is_y_at_or_below_stage_surface(reinterpret_cast<void *>(*(_DWORD *)(raw + 368))) )
*(_BYTE *)(raw +  388) = 0;
}
if ( *(_DWORD *)(raw +  384) == 1 )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
(*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)(raw +  368) + 8))(*(_DWORD *)(raw +  368), 100);
reinterpret_cast<FighterPeerActionStateView *>(*(_DWORD *)(raw + 368))->zero_velocity_acceleration();
*(_BYTE *)(*(_DWORD *)(raw +  368) + 260) = -*(_BYTE *)(raw +  260);
v334 = (double)(95 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v334;
*(float *)(*(_DWORD *)(raw +  368) + 240) = *(float *)(raw +  240);
}
}
if ( *(_WORD *)(raw +  318) == 1 && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 1 )
{
(*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)(raw +  368) + 8))(*(_DWORD *)(raw +  368), 102);
v335 = (double)(55 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v335;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 2 )
{
v336 = (double)(25 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v336;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
v337 = (double)(20 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v337;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 4 )
{
(*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)(raw +  368) + 8))(
*(_DWORD *)(raw +  368),
100);
v338 = (double)(25 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v338;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 5 )
{
v89 = *(_DWORD *)(raw +  368);
if ( *(__int16 *)(v89 + 372) > 0 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)v89 + 8))((void *)v89, 53);
v339 = (double)(45 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v339;
}
else
{
*(float *)(v89 + 236) = (double)(45 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 396) = -10.0;
*(float *)(*(_DWORD *)(raw +  368) + 400) = 7.5;
(*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)(raw +  368) + 8))(
*(_DWORD *)(raw +  368),
71);
*(_BYTE *)(*(_DWORD *)(raw +  368) + 260) = -*(_BYTE *)(raw +  260);
}
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 && *(_BYTE *)(raw +  1872) )
{
face_opponent_and_flip_horizontal_velocity();
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 529);
}
}
}
}
}
}
return;
case 0x20E:
v90 = *(_WORD *)(raw +  318);
if ( !v90 || v90 == 1 && *(__int16 *)(raw +  320) >= 6 )
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 5;
if ( !*(_DWORD *)(raw +  1732) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
v91 = *(_DWORD *)(raw +  324);
if ( !v91 && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
if ( !v91 && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 2 )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
if ( !v91 && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 3
|| !v91 && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 4 )
{
goto LABEL_1755;
}
v92 = *(_WORD *)(raw +  318);
if ( !v92 || v92 == 2 || v92 == 3 || v92 == 4 )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(25);
if ( !is_y_at_or_below_stage_surface(reinterpret_cast<void *>(*(_DWORD *)(raw + 368))) )
*(_BYTE *)(raw +  388) = 0;
}
if ( *(_DWORD *)(raw +  384) == 1 )
{
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
(*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)(raw +  368) + 8))(*(_DWORD *)(raw +  368), 100);
reinterpret_cast<FighterPeerActionStateView *>(*(_DWORD *)(raw + 368))->zero_velocity_acceleration();
*(_BYTE *)(*(_DWORD *)(raw +  368) + 260) = -*(_BYTE *)(raw +  260);
v340 = (double)(95 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v340;
*(float *)(*(_DWORD *)(raw +  368) + 240) = *(float *)(raw +  240);
}
}
if ( *(_WORD *)(raw +  318) == 1 && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 1 )
{
(*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)(raw +  368) + 8))(*(_DWORD *)(raw +  368), 102);
v341 = (double)(55 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v341;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 2 )
{
v342 = (double)(25 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v342;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
v343 = (double)(20 * *(char *)(raw +  260)) + *(float *)(raw +  236);
*(float *)(*(_DWORD *)(raw +  368) + 236) = v343;
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 4 )
{
v344 = *(float *)(raw +  236) - (double)(5 * *(char *)(raw +  260));
*(float *)(*(_DWORD *)(raw +  368) + 236) = v344;
*(_BYTE *)(*(_DWORD *)(raw +  368) + 260) = *(_BYTE *)(raw +  260);
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 5 )
{
v93 = *(_DWORD *)(raw +  368);
if ( *(__int16 *)(v93 + 372) > 0 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)v93 + 8))((void *)v93, 53);
v345 = *(float *)(raw +  236) - (double)(25 * *(char *)(raw +  260));
*(float *)(*(_DWORD *)(raw +  368) + 236) = v345;
}
else
{
*(float *)(v93 + 236) = *(float *)(raw +  236) - (double)(25 * *(char *)(raw +  260));
*(float *)(*(_DWORD *)(raw +  368) + 396) = -10.0;
*(float *)(*(_DWORD *)(raw +  368) + 400) = 7.5;
(*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)(raw +  368) + 8))(
*(_DWORD *)(raw +  368),
71);
*(_BYTE *)(*(_DWORD *)(raw +  368) + 260) = *(_BYTE *)(raw +  260);
}
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 && *(_BYTE *)(raw +  1872) )
{
face_opponent_and_flip_horizontal_velocity();
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 529);
}
}
}
}
}
}
return;
case 0x211:
v94 = *(_WORD *)(raw +  318);
if ( !v94 || v94 == 2 )
{
resolve_stage_surface_landing_transition();
v3 = 0.0;
}
if ( v3 < *(float *)(raw +  244) )
{
v346 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v346;
if ( v346 < v3 )
*(float *)(raw +  244) = v3;
}
if ( *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
*(float *)(raw +  240) = stage_surface_height_at_x(this);
*(float *)(raw +  244) = *(float *)(raw +  244) * 0.5;
*(float *)(raw +  248) = 0.0;
goto LABEL_1162;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_DWORD *)(raw +  324) )
goto LABEL_1174;
if ( !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
*(float *)(raw +  244) = 25.0;
*(float *)(raw +  248) = 8.5;
*(float *)(raw +  256) = 0.85000002;
dispatch_indexed_event_member(0x1Du);
}
if ( *(_DWORD *)(raw +  324) )
goto LABEL_1174;
if ( !*(_WORD *)(raw +  322) )
{
if ( !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 2 )
goto LABEL_933_A;
LABEL_1174:
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
dispatch_indexed_event_member(0x1Cu);
}
return;
case 0x212:
case 0x213:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 9;
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 2 )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(30);
dispatch_character_wave_handle(0xAu);
}
if ( *(_DWORD *)(raw +  384) == 3 )
{
*(_BYTE *)(raw +  388) = 1;
*(_DWORD *)(raw +  384) = 0;
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
dispatch_character_wave_handle(0xBu);
return;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_DWORD *)(raw +  324) || *(_WORD *)(raw +  322) || *(_WORD *)(raw +  320) )
{
if ( *(_WORD *)(raw +  318) == 1 && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 10 )
*(float *)(raw +  244) = 20.0;
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 11 )
{
*(float *)(raw +  244) = 0.0;
dispatch_character_wave_handle(0xCu);
*(_DWORD *)(raw +  384) = 0;
*(_BYTE *)(raw +  388) = 1;
*(_BYTE *)(raw +  1997) = 1;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 12 )
{
*(float *)v486 = 60.0;
*(float *)&v486[1] = 0.0;
*(float *)&v486[2] = 0.0;
v95 = *(unsigned __int8 *)(raw +  260);
v347 = *(float *)(raw +  240) + 115.0;
v161 = v347;
v348 = (double)(150 * (char)v95) + *(float *)(raw +  236);
spawn_owned_object_via_manager(821, v348, v161, v95, 1, (int)v486, 3);
}
}
}
return;
}
if ( *(_WORD *)(raw +  318) != 1 )
return;
goto LABEL_1755;
case 0x21C:
v96 = *(_WORD *)(raw +  318);
if ( v96 < 2u || v96 == 2 && *(__int16 *)(raw +  320) <= 2 || v96 == 4 )
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 2;
if ( !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& (!*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1
|| !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 2
|| !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 5) )
{
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
}
if ( *(_WORD *)(raw +  318) )
goto LABEL_1227;
if ( *(__int16 *)(raw +  320) >= 6 )
*(float *)(raw +  244) = *(float *)(raw +  244) - 0.5;
v97 = 0.0;
if ( *(float *)(raw +  244) < 0.0 )
*(float *)(raw +  244) = 0.0;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(25);
*(float *)v477 = 0.0;
*(float *)&v477[1] = 0.0;
*(float *)&v477[2] = 0.0;
spawn_owned_object_via_manager(812,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v477,
3);
*(float *)(raw +  244) = 12.5;
v98 = *(unsigned __int8 *)(raw +  260);
v349 = (double)(100 * (char)v98) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(128, v349, *(float *)(raw +  240), v98, -1);
dispatch_character_wave_handle(5u);
LABEL_1227:
v97 = 0.0;
}
if ( *(_WORD *)(raw +  318) == 1 )
{
if ( *(__int16 *)(raw +  320) >= 3 )
*(float *)(raw +  244) = *(float *)(raw +  244) - 1.0;
if ( v97 > *(float *)(raw +  244) )
*(float *)(raw +  244) = v97;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 3 )
{
*(float *)v484 = v97;
*(float *)&v484[1] = v97;
*(float *)&v484[2] = 1.0;
spawn_owned_object_via_manager(812,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v484,
3);
*(float *)(raw +  244) = 12.5;
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
add_phase_scaled_counter_558(25);
dispatch_character_wave_handle(5u);
}
}
v99 = *(_WORD *)(raw +  318);
if ( v99 != 2 && v99 != 3 && v99 != 4 )
goto LABEL_1250;
if ( v99 < 4 )
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  12))(4);
}
else
{
if ( *(_WORD *)(raw +  318) == 2 && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
*(float *)(raw +  244) = 12.5;
*(float *)(raw +  248) = 10.0;
*(float *)(raw +  256) = 0.75;
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 )
{
dispatch_character_wave_handle(6u);
add_phase_scaled_counter_558(25);
*(float *)v479 = 0.0;
*(float *)&v479[1] = 0.0;
*(float *)&v479[2] = 2.0;
spawn_owned_object_via_manager(812,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v479,
3);
}
}
LABEL_1250:
v100 = *(_WORD *)(raw +  318);
if ( v100 == 6 )
goto LABEL_1254;
if ( v100 != 7 && v100 != 8 )
return;
if ( v100 == 7 )
LABEL_1254:
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( !has_crossed_stage_surface_while_descending() )
{
if ( *(_WORD *)(raw +  318) == 6 && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
*(float *)(raw +  244) = 5.0;
*(float *)(raw +  248) = 21.0;
*(float *)(raw +  256) = 1.5;
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 )
{
dispatch_character_wave_handle(6u);
add_phase_scaled_counter_558(25);
*(float *)v485 = 0.0;
*(float *)&v485[1] = 0.0;
*(float *)&v485[2] = 2.0;
spawn_owned_object_via_manager(812,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v485,
3);
}
}
return;
}
(*(void (__stdcall **)(int))(*(_DWORD *)raw +  12))(8);
}
LABEL_100:
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
return;
case 0x221:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 6;
if ( !*(_DWORD *)(raw +  1728) )
*(_BYTE *)(raw +  1872) = 0;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
v101 = *(_DWORD *)(raw +  324);
if ( !v101 && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
if ( !*(_WORD *)(raw +  318) )
{
if ( *(__int16 *)(raw +  320) <= 7 && !(v101 % 5) && *(float *)(raw +  244) > 0.0 )
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
if ( *(__int16 *)(raw +  320) > 6 )
*(float *)(raw +  244) = *(float *)(raw +  244) - 1.0;
if ( *(float *)(raw +  244) < 0.0 )
*(float *)(raw +  244) = 0.0;
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 5 )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
*(float *)(raw +  244) = 30.0;
dispatch_character_wave_handle(9u);
*(float *)v490 = 0.0;
*(float *)&v490[1] = 0.0;
*(float *)&v490[2] = 0.0;
*(float *)&v490[3] = 1.0;
spawn_owned_object_via_manager(817,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v490,
4);
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 )
*(float *)(raw +  244) = *(float *)(raw +  244) * 0.5;
}
}
return;
case 0x222:
resolve_stage_surface_landing_transition();
*(_BYTE *)(raw +  380) = 6;
if ( *(_WORD *)(raw +  320) == 6 )
{
if ( *(_DWORD *)(raw +  384) )
{
if ( *(char *)(raw +  388) > 0 && (__int16)++*(_WORD *)(raw +  1840) >= 6 )
{
*(_DWORD *)(raw +  384) = 0;
*(_WORD *)(raw +  1840) = 0;
}
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
v102 = *(_DWORD *)(raw +  324);
if ( !v102 && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
goto LABEL_1755;
if ( !*(_WORD *)(raw +  318) )
{
if ( *(__int16 *)(raw +  320) <= 7 && !(v102 % 5) && *(float *)(raw +  244) > 0.0 )
emit_fighter_effect_433cc0(127,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
if ( *(__int16 *)(raw +  320) > 6 )
*(float *)(raw +  244) = *(float *)(raw +  244) - 1.0;
if ( *(float *)(raw +  244) < 0.0 )
*(float *)(raw +  244) = 0.0;
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 5 )
{
adjust_counter_482(200, 120);
add_phase_scaled_counter_558(50);
*(float *)(raw +  244) = 30.0;
dispatch_character_wave_handle(9u);
*(float *)v491 = 0.0;
*(float *)&v491[1] = 0.0;
*(float *)&v491[2] = 0.0;
*(float *)&v491[3] = 1.5;
spawn_owned_object_via_manager(817,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v491,
4);
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 )
*(float *)(raw +  244) = *(float *)(raw +  244) * 0.5;
}
}
return;
default:
goto LABEL_1766;
}
    }
resolve_stage_surface_landing_transition();
if ( *(_WORD *)(raw +  318) == 1 && *(int *)(raw +  324) >= 15 )
{
LABEL_1162:
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
}
else
{
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 4;
adjust_counter_482(200, 120);
*(_DWORD *)(raw +  384) = 1;
add_phase_scaled_counter_558(50);
}
}
  }
  else
  {
switch ( v5 )
{
case 0x235:
case 0x236:
resolve_stage_surface_landing_transition();
if ( *(_WORD *)(raw +  318) == 2 && *(int *)(raw +  324) >= 24 )
goto LABEL_1162;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 5;
adjust_counter_482(200, 120);
*(_DWORD *)(raw +  384) = 1;
add_phase_scaled_counter_558(50);
}
return;
case 0x23A:
case 0x23B:
resolve_stage_surface_landing_transition();
if ( *(_WORD *)(raw +  318) == 2 && *(int *)(raw +  324) >= 24 )
goto LABEL_1162;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
*(_BYTE *)(raw +  2021) = 1;
*(_WORD *)(raw +  2022) = 6;
adjust_counter_482(200, 120);
*(_DWORD *)(raw +  384) = 1;
add_phase_scaled_counter_558(50);
}
return;
case 0x258:
v103 = *(_WORD *)(raw +  320);
if ( v103 <= 6 || v103 >= 11 )
resolve_stage_surface_landing_transition();
publish_texture_state(3, 2);
if ( *(_WORD *)(raw +  1840) )
goto LABEL_1769;
if ( *(_DWORD *)(raw +  384) == 1 )
{
*(_WORD *)(raw +  1840) = 1;
*(float *)v481 = 0.0;
*(float *)&v481[1] = 0.0;
*(float *)&v481[2] = 0.0;
v350 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(850,
*(float *)(raw +  236),
v350,
*(unsigned __int8 *)(raw +  260),
1,
(int)v481,
3);
dispatch_character_wave_handle(0x33u);
}
if ( *(_WORD *)(raw +  1840) || !*(_DWORD *)(raw +  384) )
{
LABEL_1769:
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v104 = *(unsigned __int8 *)(raw +  260);
v351 = *(float *)(raw +  240) + 107.0;
v201 = v351;
v352 = (double)(20 * (char)v104) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(115, v352, v201, v104, 1);
dispatch_indexed_sequence_window_45c8b0(0, 2, 0x3C);
advance_secondary_event_effect_cycle();
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  244) = 30.0;
v353 = (double)(200 * *(char *)(raw +  260)) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(128, v353, *(float *)(raw +  240), *(unsigned __int8 *)(raw +  260), -1);
*(float *)(raw +  264) = 35.0;
*(float *)(raw +  268) = 70.0;
dispatch_character_wave_handle(0x32u);
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 9 )
*(float *)(raw +  244) = 25.0;
v105 = 0.2f;
if ( *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) + 0.2f;
v354 = *(float *)(raw +  288) - 0.2f;
*(float *)(raw +  288) = v354;
v106 = 0.0;
if ( v354 < 0.0 )
*(float *)(raw +  288) = 0.0;
if ( *(float *)(raw +  284) > 3.0 )
*(float *)(raw +  284) = 3.0;
}
else
{
v106 = 0.0;
}
if ( *(_WORD *)(raw +  320) == 9 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) - v105;
v107 = v106;
v108 = v105 + *(float *)(raw +  288);
v109 = v107;
v355 = v108;
*(float *)(raw +  288) = v355;
if ( v355 > 1.0 )
*(float *)(raw +  288) = 1.0;
if ( *(float *)(raw +  284) < 1.0 )
*(float *)(raw +  284) = 1.0;
}
else
{
v109 = v106;
}
if ( *(__int16 *)(raw +  320) >= 9 )
{
v356 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v356;
if ( v356 < v109 )
*(float *)(raw +  244) = v109;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 10 )
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
}
}
else
{
*(_WORD *)(raw +  1840) = 1;
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  28))(raw, 9);
*(float *)(raw +  244) = 25.0;
}
return;
case 0x259:
resolve_stage_surface_landing_transition();
publish_texture_state(3, 2);
if ( *(_DWORD *)(raw +  384) )
{
if ( *(char *)(raw +  388) > 0 && (__int16)++*(_WORD *)(raw +  1840) >= 2 )
{
*(_WORD *)(raw +  1840) = 0;
*(_DWORD *)(raw +  384) = 0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 2 )
{
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v110 = *(unsigned __int8 *)(raw +  260);
v357 = *(float *)(raw +  240) + 87.0;
v202 = v357;
v358 = (double)(63 * (char)v110) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(115, v358, v202, v110, 1);
dispatch_indexed_sequence_window_45c8b0(0, 3, 0x3C);
advance_secondary_event_effect_cycle();
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
*(float *)v487 = 0.0;
*(float *)&v487[1] = 0.0;
*(float *)&v487[2] = 0.0;
spawn_owned_object_via_manager(851,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v487,
3);
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 10 )
dispatch_character_wave_handle(0x34u);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 11 )
{
v359 = 0.0;
do
{
*(float *)v458 = (double)selector_random_roll(0x12u) + v359 * 45.0 + 22.5;
*(float *)&v458[1] = 20.0;
*(float *)&v458[2] = 2.0;
if ( *(float *)v458 < 0.0 || *(float *)v458 > 180.0 )
{
v203 = -1;
v177 = *(unsigned __int8 *)(raw +  260);
v162 = *(float *)(raw +  240);
v379 = (double)(175 * (char)v177) + *(float *)(raw +  236);
v111 = v379;
}
else
{
v203 = 1;
v177 = *(unsigned __int8 *)(raw +  260);
v162 = *(float *)(raw +  240);
v378 = (double)(150 * (char)v177) + *(float *)(raw +  236);
v111 = v378;
}
v149 = v111;
spawn_owned_object_via_manager(821, v149, v162, v177, v203, (int)v458, 3);
v359 = v359 + 1.0;
}
while ( v359 < 8.0 );
}
}
}
}
return;
case 0x25A:
resolve_stage_surface_landing_transition();
publish_texture_state(3, 2);
if ( *(_WORD *)(raw +  318) == 1 && *(int *)(raw +  324) >= 40 )
goto LABEL_898;
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324) )
{
if ( !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
*(_DWORD *)(raw +  324) = 0;
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v380 = *(float *)(raw +  240) + 100.0;
emit_fighter_effect_433cc0(115, *(float *)(raw +  236), v380, *(unsigned __int8 *)(raw +  260), 1);
dispatch_indexed_sequence_window_45c8b0(0, 2, 0x3C);
advance_secondary_event_effect_cycle();
dispatch_character_wave_handle(0x36u);
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 3 )
{
*(_WORD *)(raw +  2026) = 240;
*(_WORD *)(raw +  2028) = 1;
payload_446[0] = 0.0;
payload_446[1] = 0.0;
payload_446[2] = 0.0;
v381 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(852,
*(float *)(raw +  236),
v381,
*(unsigned __int8 *)(raw +  260),
1,
(int)payload_446,
3);
payload_446[0] = (float)selector_random_roll(0x168u);
payload_446[2] = 1.0;
v382 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(852,
*(float *)(raw +  236),
v382,
*(unsigned __int8 *)(raw +  260),
1,
(int)payload_446,
3);
payload_446[0] = (float)selector_random_roll(0x168u);
v383 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(852,
*(float *)(raw +  236),
v383,
(unsigned __int8)-*(_BYTE *)(raw +  260),
1,
(int)payload_446,
3);
v360 = 0.0;
v112 = (float)0.0;
do
{
payload_446[0] = v112 * 60.0 + 30.0;
payload_446[1] = 15.0;
payload_446[2] = 2.0;
if ( payload_446[0] < 0.0 || payload_446[0] > 180.0 )
spawn_owned_object_via_manager(821,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1,
(int)payload_446,
3);
else
spawn_owned_object_via_manager(821,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)payload_446,
3);
v360 = v360 + 1.0;
v112 = v360;
}
while ( v360 < 6.0 );
}
}
return;
case 0x25B:
publish_texture_state(3, 2);
v113 = *(_WORD *)(raw +  318);
if ( v113 == 5 || !v113 && ((v114 = *(_WORD *)(raw +  320), v114 <= 6) || v114 >= 10) )
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)advance_frame_and_dispatch()
|| !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{
goto LABEL_1755;
}
if ( *(_WORD *)(raw +  318) )
goto LABEL_1470;
if ( *(_DWORD *)(raw +  384) == 1 )
{
*(float *)v468 = 0.0;
*(float *)&v468[1] = 0.0;
*(float *)&v468[2] = 0.0;
v384 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(853,
*(float *)(raw +  236),
v384,
*(unsigned __int8 *)(raw +  260),
1,
(int)v468,
3);
zero_velocity_acceleration();
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
*(float *)(raw +  236) = *(float *)(*(_DWORD *)(raw +  368) + 236);
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
*(_DWORD *)(raw +  384) = 0;
}
v115 = *(_WORD *)(raw +  320);
if ( v115 <= 8 && *(_DWORD *)(raw +  384) )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  28))(raw, 9);
*(float *)(raw +  244) = 25.0;
return;
}
if ( v115 <= 6 || v115 >= 11 )
resolve_stage_surface_landing_transition();
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 5 )
{
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v116 = *(unsigned __int8 *)(raw +  260);
v385 = *(float *)(raw +  240) + 107.0;
v204 = v385;
v386 = (double)(20 * (char)v116) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(115, v386, v204, v116, 1);
dispatch_indexed_sequence_window_45c8b0(0, 5, 0x3C);
advance_secondary_event_effect_cycle();
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  244) = 40.0;
v387 = (double)(200 * *(char *)(raw +  260)) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(128, v387, *(float *)(raw +  240), *(unsigned __int8 *)(raw +  260), -1);
*(float *)(raw +  264) = 35.0;
*(float *)(raw +  268) = 70.0;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 9 )
*(float *)(raw +  244) = 25.0;
}
}
if ( *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) + 0.2f;
v361 = *(float *)(raw +  288) - 0.2f;
*(float *)(raw +  288) = v361;
v117 = 0.0;
if ( v361 < 0.0 )
*(float *)(raw +  288) = 0.0;
if ( *(float *)(raw +  284) > 3.0 )
*(float *)(raw +  284) = 3.0;
}
else
{
v117 = 0.0;
}
if ( *(_WORD *)(raw +  320) == 9 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) - 0.2f;
v118 = v117;
v362 = *(float *)(raw +  288) + 0.2f;
*(float *)(raw +  288) = v362;
if ( v362 > 1.0 )
*(float *)(raw +  288) = 1.0;
if ( *(float *)(raw +  284) < 1.0 )
*(float *)(raw +  284) = 1.0;
}
else
{
v118 = v117;
}
if ( *(__int16 *)(raw +  320) >= 9 )
{
v363 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v363;
if ( v363 < v118 )
*(float *)(raw +  244) = v118;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 10 )
{
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
LABEL_1470:
v118 = 0.0;
}
if ( *(_WORD *)(raw +  318) != 2 )
goto LABEL_1501;
if ( *(_DWORD *)(raw +  324) % 5 )
goto LABEL_1499;
if ( *(__int16 *)(raw +  1840) >= 16 )
goto LABEL_1500;
*(float *)v444 = v118;
*(float *)&v444[1] = v118;
v445 = 2.0;
v119 = *(_DWORD *)(raw +  368);
v388 = *(float *)(v119 + 240) + 100.0;
spawn_owned_object_via_manager(853,
*(float *)(v119 + 236),
v388,
*(unsigned __int8 *)(raw +  260),
1,
(int)v444,
3);
v445 = 1.0;
v120 = *(_WORD *)(raw +  1840);
if ( !v120 || v120 == 8 )
*(float *)v444 = 0.0;
v121 = *(_WORD *)(raw +  1840);
if ( v121 == 1 || v121 == 9 )
*(float *)v444 = 180.0;
v122 = *(_WORD *)(raw +  1840);
if ( v122 == 2 || v122 == 10 )
*(float *)v444 = 90.0;
v123 = *(_WORD *)(raw +  1840);
if ( v123 == 3 || v123 == 11 )
*(float *)v444 = 270.0;
v124 = *(_WORD *)(raw +  1840);
if ( v124 == 4 || v124 == 12 )
*(float *)v444 = 45.0;
v125 = *(_WORD *)(raw +  1840);
if ( v125 == 5 || v125 == 13 )
*(float *)v444 = 225.0;
v126 = *(_WORD *)(raw +  1840);
if ( v126 == 6 || v126 == 14 )
*(float *)v444 = 135.0;
v127 = *(_WORD *)(raw +  1840);
if ( v127 == 7 || v127 == 15 )
*(float *)v444 = 315.0;
v389 = 90.0 - *(float *)v444;
v442 = lookup_orientation_sine_quantized_abs(v389) * 200.0 + *(float *)(*(_DWORD *)(raw +  368) + 240) + 100.0;
v390 = 90.0 - *(float *)v444;
v364 = lookup_orientation_cosine_quantized_abs(v390) * 200.0;
v178 = *(unsigned __int8 *)(raw +  260);
v163 = -*(float *)v444;
v391 = v442 - lookup_orientation_sine_quantized_abs(v163) * 150.0;
v164 = v391;
v150 = -*(float *)v444;
v392 = (v364 - lookup_orientation_cosine_quantized_abs(v150) * 150.0) * (double)*(char *)(raw +  260)
+ *(float *)(*(_DWORD *)(raw +  368) + 236);
spawn_owned_object_via_manager(853, v392, v164, v178, 1, (int)v444, 3);
v445 = 3.0;
v393 = 90.0 - *(float *)v444;
v179 = *(unsigned __int8 *)(raw +  260);
v394 = lookup_orientation_sine_quantized_abs(v393) * 250.0 + *(float *)(*(_DWORD *)(raw +  368) + 240) + 100.0;
v165 = v394;
v395 = 90.0 - *(float *)v444;
v396 = lookup_orientation_cosine_quantized_abs(v395) * 250.0 * (double)*(char *)(raw +  260) + *(float *)(*(_DWORD *)(raw +  368) + 236);
spawn_owned_object_via_manager(853, v396, v165, v179, 1, (int)v444, 3);
v118 = 0.0;
++*(_WORD *)(raw +  1840);
LABEL_1499:
if ( *(__int16 *)(raw +  1840) >= 16 )
{
LABEL_1500:
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
v118 = 0.0;
}
LABEL_1501:
if ( *(_WORD *)(raw +  318) == 3 )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 1 )
{
*(_BYTE *)(raw +  388) = 1;
*(_DWORD *)(raw +  384) = 0;
*(float *)(raw +  244) = v118;
*(float *)(raw +  248) = 60.0;
}
if ( *(_DWORD *)(raw +  384) == 1 )
{
*(float *)v470 = -90.0;
*(float *)&v470[1] = v118;
*(float *)&v470[2] = v118;
v397 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(853,
*(float *)(raw +  236),
v397,
*(unsigned __int8 *)(raw +  260),
1,
(int)v470,
3);
*(_DWORD *)(raw +  384) = 0;
*(_BYTE *)(raw +  388) = 0;
}
if ( *(__int16 *)(raw +  320) >= 3 )
*(float *)(raw +  248) = *(float *)(raw +  248) - 1.0;
}
if ( *(_WORD *)(raw +  318) == 4 )
*(float *)(raw +  248) = *(float *)(raw +  248) - 1.0;
v128 = *(_WORD *)(raw +  318);
if ( (v128 == 3 || v128 == 4) && has_crossed_stage_surface_while_descending() )
{
zero_velocity_acceleration();
*(float *)(raw +  240) = stage_surface_height_at_x(this);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 5);
}
return;
case 0x25C:
resolve_stage_surface_landing_transition();
publish_texture_state(3, 2);
if ( *(_DWORD *)(raw +  384) )
{
if ( *(char *)(raw +  388) > 0 && (__int16)++*(_WORD *)(raw +  1840) >= 2 )
{
*(_WORD *)(raw +  1840) = 0;
*(_DWORD *)(raw +  384) = 0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 2 )
{
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v129 = *(unsigned __int8 *)(raw +  260);
v398 = *(float *)(raw +  240) + 87.0;
v205 = v398;
v399 = (double)(63 * (char)v129) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(115, v399, v205, v129, 1);
dispatch_indexed_sequence_window_45c8b0(0, 4, 0x3C);
advance_secondary_event_effect_cycle();
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
*(float *)v472 = 0.0;
*(float *)&v472[1] = 0.0;
*(float *)&v472[2] = 0.0;
spawn_owned_object_via_manager(854,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v472,
3);
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 10 )
dispatch_character_wave_handle(0x35u);
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 11 )
{
v365 = 0.0;
do
{
*(float *)v459 = (double)selector_random_roll(0x12u) + v365 * 45.0 + 22.5;
*(float *)&v459[1] = 20.0;
*(float *)&v459[2] = 2.0;
if ( *(float *)v459 < 0.0 || *(float *)v459 > 180.0 )
{
v206 = -1;
v180 = *(unsigned __int8 *)(raw +  260);
v166 = *(float *)(raw +  240);
v401 = (double)(175 * (char)v180) + *(float *)(raw +  236);
v130 = v401;
}
else
{
v206 = 1;
v180 = *(unsigned __int8 *)(raw +  260);
v166 = *(float *)(raw +  240);
v400 = (double)(150 * (char)v180) + *(float *)(raw +  236);
v130 = v400;
}
v151 = v130;
spawn_owned_object_via_manager(821, v151, v166, v180, v206, (int)v459, 3);
v365 = v365 + 1.0;
}
while ( v365 < 8.0 );
}
}
}
}
return;
case 0x25D:
resolve_stage_surface_landing_transition();
publish_texture_state(3, 2);
if ( *(_WORD *)(raw +  318) == 1 && *(int *)(raw +  324) >= 16 )
{
LABEL_898:
(*(void (__thiscall **)(void *))(*(_DWORD *)raw +  20))(raw);
}
else
{
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_DWORD *)(raw +  324) )
{
if ( !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) && *(_WORD *)(raw +  318) == 1 )
{
*(_DWORD *)(raw +  324) = 0;
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v402 = *(float *)(raw +  240) + 100.0;
emit_fighter_effect_433cc0(115, *(float *)(raw +  236), v402, *(unsigned __int8 *)(raw +  260), 1);
dispatch_indexed_sequence_window_45c8b0(0, 2, 0x3C);
advance_secondary_event_effect_cycle();
dispatch_character_wave_handle(0x36u);
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 3 )
{
*(_WORD *)(raw +  2026) = 600;
payload_452[0] = 0.0;
payload_452[1] = 0.0;
payload_452[2] = 0.0;
v403 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(855,
*(float *)(raw +  236),
v403,
*(unsigned __int8 *)(raw +  260),
1,
(int)payload_452,
3);
payload_452[0] = (float)selector_random_roll(0x258u);
payload_452[2] = 1.0;
v404 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(855,
*(float *)(raw +  236),
v404,
*(unsigned __int8 *)(raw +  260),
1,
(int)payload_452,
3);
payload_452[0] = (float)selector_random_roll(0x168u);
v405 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(855,
*(float *)(raw +  236),
v405,
(unsigned __int8)-*(_BYTE *)(raw +  260),
1,
(int)payload_452,
3);
v366 = 0.0;
do
{
payload_452[0] = (float)selector_random_roll(0x168u);
payload_452[1] = 0.0;
payload_452[2] = 2.0;
v406 = *(float *)(raw +  240) + 100.0;
spawn_owned_object_via_manager(855,
*(float *)(raw +  236),
v406,
*(unsigned __int8 *)(raw +  260),
1,
(int)payload_452,
3);
v366 = v366 + 1.0;
}
while ( v366 < 6.0 );
}
}
}
return;
case 0x25E:
v131 = *(_WORD *)(raw +  320);
if ( v131 <= 6 || v131 >= 11 )
resolve_stage_surface_landing_transition();
publish_texture_state(3, 2);
v132 = *(_WORD *)(raw +  320);
if ( v132 >= 7 && v132 <= 10 )
{
v133 = (*(__int16 *)(raw +  1840) & 0x80000001) == 0;
if ( *(__int16 *)(raw +  1840) < 0 )
v133 = (((*(_BYTE *)(raw +  1840) & 1) - 1) | 0xFFFFFFFE) == -1;
if ( v133 )
{
payload_455[0] = 10.0 - (double)selector_random_roll(0x2Du);
payload_455[1] = 0.0;
payload_455[2] = 2.0;
v443 = *(float *)(raw +  240) + 20.0;
v407 = v443 - (double)selector_random_roll(0x28u);
*(float *)(raw +  1852) = v407;
v207 = (unsigned __int8)(2 * (*(float *)(raw +  240) >= (double)v407) - 1);
v181 = *(unsigned __int8 *)(raw +  260);
v167 = v407;
v408 = (double)selector_random_roll(0x64u) + *(float *)(raw +  236) - 50.0;
spawn_owned_object_via_manager(856, v408, v167, v181, v207, (int)payload_455, 3);
payload_455[0] = 0.0;
payload_455[1] = (double)*(__int16 *)(raw +  1840) * 0.0 + 45.0;
payload_455[2] = 5.0;
spawn_owned_object_via_manager(856,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)payload_455,
3);
}
++*(_WORD *)(raw +  1840);
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) )
{
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v134 = *(unsigned __int8 *)(raw +  260);
v409 = *(float *)(raw +  240) + 107.0;
v208 = v409;
v410 = (double)(20 * (char)v134) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(115, v410, v208, v134, 1);
dispatch_indexed_sequence_window_45c8b0(0, 3, 0x3C);
advance_secondary_event_effect_cycle();
}
if ( !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 7 )
{
dispatch_character_wave_handle(9u);
*(float *)(raw +  244) = 30.0;
v135 = *(unsigned __int8 *)(raw +  260);
v411 = (double)(200 * (char)v135) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(128, v411, *(float *)(raw +  240), v135, -1);
*(float *)(raw +  264) = 35.0;
*(float *)(raw +  268) = 70.0;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 9 )
*(float *)(raw +  244) = 25.0;
}
v105 = 0.2f;
if ( *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) + 0.2f;
v367 = *(float *)(raw +  288) - 0.2f;
*(float *)(raw +  288) = v367;
v106 = 0.0;
if ( v367 < 0.0 )
*(float *)(raw +  288) = 0.0;
if ( *(float *)(raw +  284) > 3.0 )
*(float *)(raw +  284) = 3.0;
}
else
{
v106 = 0.0;
}
if ( *(_WORD *)(raw +  320) == 9 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) - v105;
v107 = v106;
v108 = v105 + *(float *)(raw +  288);
v109 = v107;
v355 = v108;
*(float *)(raw +  288) = v355;
if ( v355 > 1.0 )
*(float *)(raw +  288) = 1.0;
if ( *(float *)(raw +  284) < 1.0 )
*(float *)(raw +  284) = 1.0;
}
else
{
v109 = v106;
}
if ( *(__int16 *)(raw +  320) >= 9 )
{
v356 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v356;
if ( v356 < v109 )
*(float *)(raw +  244) = v109;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 10 )
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
}
return;
case 0x25F:
resolve_stage_surface_landing_transition();
publish_texture_state(3, 2);
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) )
{
if ( *(_WORD *)(raw +  320) == 3 )
{
*(_WORD *)(raw +  1162) = 40;
dispatch_indexed_event_member(0x17u);
v412 = *(float *)(raw +  240) + 90.0;
emit_fighter_effect_433cc0(115, *(float *)(raw +  236), v412, *(unsigned __int8 *)(raw +  260), 1);
dispatch_indexed_sequence_window_45c8b0(0, 4, 0x3C);
advance_secondary_event_effect_cycle();
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 6 )
{
*(float *)v474 = 0.0;
*(float *)&v474[1] = 0.0;
*(float *)&v474[2] = 0.0;
v182 = *(unsigned __int8 *)(raw +  260);
v413 = *(float *)(raw +  240) - 20.0;
v168 = v413;
v414 = (double)(50 * (char)v182) + *(float *)(raw +  236);
spawn_owned_object_via_manager(857, v414, v168, v182, 1, (int)v474, 3);
dispatch_character_wave_handle(0x37u);
publish_battle_layout_scalar(10.0);
}
}
return;
case 0x2B7:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
dispatch_indexed_event_member(0x37u);
v415 = *(float *)(raw +  240) + 100.0;
emit_fighter_effect_433cc0(140, *(float *)(raw +  236), v415, *(unsigned __int8 *)(raw +  260), 1);
v416 = *(float *)(raw +  240) + 100.0;
emit_fighter_effect_433cc0(140, *(float *)(raw +  236), v416, *(unsigned __int8 *)(raw +  260), 1);
v417 = *(float *)(raw +  240) + 100.0;
emit_fighter_effect_433cc0(140, *(float *)(raw +  236), v417, *(unsigned __int8 *)(raw +  260), 1);
v418 = *(float *)(raw +  240) + 100.0;
emit_fighter_effect_433cc0(141, *(float *)(raw +  236), v418, *(unsigned __int8 *)(raw +  260), -1);
emit_fighter_effect_433cc0(142,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1);
}
return;
case 0x2B8:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)advance_frame_and_dispatch()
|| !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1 )
{

(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
}
if ( *(_WORD *)(raw +  318) )
return;
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 4 )
*(float *)(raw +  244) = 20.0;
if ( *(_WORD *)(raw +  322) )
goto LABEL_1612;
v66 = *(_WORD *)(raw +  320) < 5;
if ( *(_WORD *)(raw +  320) == 5 )
{
dispatch_indexed_event_member(0x1Du);
LABEL_1612:
v66 = *(_WORD *)(raw +  320) < 5;
}
LABEL_728:
if ( !v66 )
{
v305 = *(float *)(raw +  244) - 2.0;
v58 = v305;
*(float *)(raw +  244) = v58;
if ( v58 < 0.0 )
*(float *)(raw +  244) = 0.0;
}
return;
case 0x2C6:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 700);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 )
{
payload_449[0] = -120.0;
payload_449[1] = 0.0;
payload_449[2] = 0.0;
v136 = *(unsigned __int8 *)(raw +  260);
v419 = *(float *)(raw +  240) + 20.0;
v169 = v419;
v420 = (double)(140 * (char)v136) + *(float *)(raw +  236);
spawn_owned_object_via_manager(900, v420, v169, v136, 1, (int)payload_449, 3);
if ( g_match_identifier == 3 )
{
payload_449[0] = -95.0;
payload_449[1] = 0.0;
payload_449[2] = 0.0;
v137 = *(unsigned __int8 *)(raw +  260);
v421 = *(float *)(raw +  240) + 20.0;
v170 = v421;
v422 = (double)(140 * (char)v137) + *(float *)(raw +  236);
spawn_owned_object_via_manager(900, v422, v170, v137, 1, (int)payload_449, 3);
}
dispatch_character_wave_handle(0xCu);
v368 = 0.0;
do
{
payload_449[0] = (double)selector_random_roll(0x12u) + v368 * 45.0 + 22.5;
payload_449[1] = 20.0;
payload_449[2] = 5.0;
if ( payload_449[0] < 0.0 || payload_449[0] > 180.0 )
{
v209 = -1;
v183 = *(unsigned __int8 *)(raw +  260);
v171 = *(float *)(raw +  240);
v424 = (double)(140 * (char)v183) + *(float *)(raw +  236);
v138 = v424;
}
else
{
v209 = 1;
v183 = *(unsigned __int8 *)(raw +  260);
v171 = *(float *)(raw +  240);
v423 = (double)(140 * (char)v183) + *(float *)(raw +  236);
v138 = v423;
}
v152 = v138;
spawn_owned_object_via_manager(900, v152, v171, v183, v209, (int)payload_449, 3);
v368 = v368 + 1.0;
}
while ( v368 < 8.0 );
}
if ( *(_WORD *)(raw +  318) == 1 && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )
{
*(_WORD *)(raw +  1840) = 1;
dispatch_character_wave_handle(0xFu);
v369 = 0.0;
do
{
*(float *)v460 = (double)selector_random_roll(0x12u) + v369 * 45.0 + 22.5;
*(float *)&v460[1] = 20.0;
*(float *)&v460[2] = 5.0;
if ( *(float *)v460 < 0.0 || *(float *)v460 > 180.0 )
spawn_owned_object_via_manager(900,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
-1,
(int)v460,
3);
else
spawn_owned_object_via_manager(900,
*(float *)(raw +  236),
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v460,
3);
v369 = v369 + 1.0;
}
while ( v369 < 8.0 );
}
return;
case 0x2D0:
v139 = *(_WORD *)(raw +  318);
if ( !v139 && *(__int16 *)(raw +  320) <= 6 || v139 == 3 && *(__int16 *)(raw +  320) >= 1 )
{
resolve_stage_surface_landing_transition();
v3 = 0.0;
}
if ( *(_WORD *)(raw +  318) == 1 )
{
if ( *(_DWORD *)(raw +  324) == 30 )
{
*(float *)v476 = v3;
*(float *)&v476[1] = 20.0;
*(float *)&v476[2] = 6.0;
v140 = *(_DWORD *)(raw +  368);
v425 = *(float *)(v140 + 240) + 100.0;
spawn_owned_object_via_manager(901,
*(float *)(v140 + 236),
v425,
*(unsigned __int8 *)(raw +  260),
1,
(int)v476,
3);
v3 = 0.0;
}
v370 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v370;
if ( v370 < v3 )
*(float *)(raw +  244) = v3;
if ( *(int *)(raw +  324) >= 270 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
*(_BYTE *)(raw +  260) = -*(_BYTE *)(raw +  260);
*(float *)(raw +  244) = 25.0;
v3 = 0.0;
}
}
if ( *(_WORD *)(raw +  318) == 2 )
{
v141 = *(_DWORD *)(raw +  324);
if ( v141 >= 60
&& !(v141 % *(__int16 *)(raw +  1842))
&& *(_WORD *)(raw +  1840) < *(_WORD *)(raw +  1844) )
{
*(float *)v478 = (float)selector_random_roll(0x168u);
*(float *)&v478[1] = 20.0;
*(float *)&v478[2] = 8.0;
v184 = *(unsigned __int8 *)(raw +  260);
v426 = (double)selector_random_roll(0x280u) + 100.0;
v172 = v426;
v427 = (double)selector_random_roll(0x4B0u) + 40.0;
spawn_owned_object_via_manager(901, v427, v172, v184, 1, (int)v478, 3);
v3 = 0.0;
++*(_WORD *)(raw +  1840);
}
v371 = *(float *)(raw +  244) - 1.0;
*(float *)(raw +  244) = v371;
if ( v371 < v3 )
*(float *)(raw +  244) = v3;
if ( *(int *)(raw +  324) >= 270 )
{
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 3);
*(_BYTE *)(raw +  260) = -*(_BYTE *)(raw +  260);
*(float *)(raw +  244) = 25.0;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 700);
if ( *(_DWORD *)(raw +  324) )
goto LABEL_1674;
if ( !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 1
&& selector_random_roll(0x64u) <= 0x32 )
{
switch ( g_match_identifier )
{
case 0:
*(_WORD *)(raw +  1842) = 20;
*(_WORD *)(raw +  1844) = 10;
break;
case 1:
*(_WORD *)(raw +  1842) = 16;
*(_WORD *)(raw +  1844) = 12;
break;
case 2:
*(_WORD *)(raw +  1842) = 13;
*(_WORD *)(raw +  1844) = 15;
break;
case 3:
*(_WORD *)(raw +  1842) = 10;
*(_WORD *)(raw +  1844) = 20;
break;
default:
break;
}
*(_WORD *)(raw +  1842) = 10;
*(_WORD *)(raw +  1844) = 20;
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 2);
return;
}
if ( !*(_DWORD *)(raw +  324)
&& !*(_WORD *)(raw +  322)
&& !*(_WORD *)(raw +  320)
&& *(_WORD *)(raw +  318) == 4 )
{
goto LABEL_1765;
}
LABEL_1674:
v142 = 0.2f;
if ( *(_WORD *)(raw +  318) )
goto LABEL_1683;
if ( *(_WORD *)(raw +  322) )
goto LABEL_1678;
if ( *(_WORD *)(raw +  320) != 7 )
goto LABEL_1683;
*(float *)(raw +  244) = 30.0;
v428 = (double)(200 * *(char *)(raw +  260)) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(128, v428, *(float *)(raw +  240), *(unsigned __int8 *)(raw +  260), -1);
*(float *)(raw +  264) = 35.0;
*(float *)(raw +  268) = 70.0;
dispatch_character_wave_handle(0x32u);
v142 = 0.2f;
LABEL_1678:
if ( *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) + v142;
v372 = *(float *)(raw +  288) - v142;
*(float *)(raw +  288) = v372;
v143 = 0.0;
if ( v372 < 0.0 )
*(float *)(raw +  288) = 0.0;
if ( *(float *)(raw +  284) > 3.0 )
*(float *)(raw +  284) = 3.0;
}
else
{
LABEL_1683:
v143 = 0.0;
}
if ( *(_WORD *)(raw +  318) == 3 )
{
if ( *(_WORD *)(raw +  320) )
{
v146 = v143;
}
else
{
*(float *)(raw +  284) = *(float *)(raw +  284) - v142;
v144 = v143;
v145 = v142 + *(float *)(raw +  288);
v146 = v144;
v373 = v145;
*(float *)(raw +  288) = v373;
if ( v373 > 1.0 )
*(float *)(raw +  288) = 1.0;
if ( *(float *)(raw +  284) < 1.0 )
*(float *)(raw +  284) = 1.0;
}
if ( *(__int16 *)(raw +  320) >= 2 )
{
v374 = *(float *)(raw +  244) - 0.5;
*(float *)(raw +  244) = v374;
if ( v374 < v146 )
*(float *)(raw +  244) = v146;
}
if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 1 )
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
}
break;
case 0x2DA:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 700);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 11 )
{
*(float *)v480 = 0.0;
*(float *)&v480[1] = 10.0;
*(float *)&v480[2] = 5.0;
v429 = (double)(100 * *(char *)(raw +  260)) + *(float *)(raw +  236);
spawn_owned_object_via_manager(902,
v429,
*(float *)(raw +  240),
*(unsigned __int8 *)(raw +  260),
1,
(int)v480,
3);
dispatch_character_wave_handle(0x34u);
goto LABEL_1593;
}
return;
case 0x2DB:
resolve_stage_surface_landing_transition();
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 700);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 6 )
{
v482[0] = 0.0;
v482[1] = 120.0;
v482[2] = 6.0;
v185 = *(unsigned __int8 *)(raw +  260);
v430 = *(float *)(raw +  240) - 20.0;
v173 = v430;
v431 = (double)(100 * (char)v185) + *(float *)(raw +  236);
spawn_owned_object_via_manager(902, v431, v173, v185, 1, (int)v482, 3);
dispatch_character_wave_handle(0x37u);
LABEL_1593:
publish_battle_layout_scalar(10.0);
}
return;
case 0x2E4:
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
if ( *(_WORD *)(raw +  318) )
goto LABEL_1720;
if ( *(_WORD *)(raw +  322) )
goto LABEL_1715;
if ( *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  244) = 30.0;
v226 = *(unsigned __int8 *)(raw +  260);
v432 = (double)(200 * (char)v226) + *(float *)(raw +  236);
emit_fighter_effect_433cc0(128, v432, *(float *)(raw +  240), v226, -1);
*(float *)(raw +  264) = 35.0;
*(float *)(raw +  268) = 70.0;
dispatch_character_wave_handle(0x32u);
*(_WORD *)(raw +  2022) = 10;
LABEL_1715:
if ( *(_WORD *)(raw +  320) == 7 )
{
*(float *)(raw +  284) = *(float *)(raw +  284) + 0.2f;
v375 = *(float *)(raw +  288) - 0.2f;
*(float *)(raw +  288) = v375;
if ( v375 < 0.0 )
*(float *)(raw +  288) = 0.0;
if ( *(float *)(raw +  284) > 3.0 )
*(float *)(raw +  284) = 3.0;
}
}
LABEL_1720:
if ( *(_WORD *)(raw +  318) == 1 )
{
if ( !*(_DWORD *)(raw +  324) && !*(_WORD *)(raw +  322) && !*(_WORD *)(raw +  320) )
reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
*(float *)(raw +  244) = (640.0 - *(float *)(raw +  236)) / 30.0 * (double)*(char *)(raw +  260);
*(float *)(raw +  248) = (350.0 - *(float *)(raw +  240)) / 30.0;
if ( *(float *)(raw +  244) > 30.0 )
*(float *)(raw +  244) = 30.0;
if ( *(float *)(raw +  244) < -30.0 )
*(float *)(raw +  244) = -30.0;
if ( *(float *)(raw +  248) > 30.0 )
*(float *)(raw +  248) = 30.0;
if ( *(float *)(raw +  248) < -30.0 )
*(float *)(raw +  248) = -30.0;
if ( *(int *)(raw +  324) >= 120 )
goto LABEL_1162;
}
if ( *(_WORD *)(raw +  318) == 2 )
{
*(float *)(raw +  236) = 640.0;
*(float *)(raw +  240) = 350.0;
}
return;
case 0x302:
if ( (unsigned __int8)advance_frame_and_dispatch() )
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 700);
if ( !*(_WORD *)(raw +  318) && !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 7 )
{
*(_BYTE *)(raw +  1621) = 1;
finalize_sequence_entry(-1);
publish_texture_state(2, -1);
copy_action_word_176_to_174();
*(_DWORD *)(raw +  1898) = 1;
*(_WORD *)(raw +  1894) = 0;
*(_WORD *)(raw +  1896) = 0;
*(_WORD *)(raw +  1892) = 0;
dispatch_indexed_event_member(0x17u);
}
return;
case 0x31B:
if ( *(_WORD *)(raw +  318) )
goto LABEL_1764;
*(float *)(raw +  248) = *(float *)(raw +  248) - 0.3f;
if ( !has_crossed_stage_surface_while_descending() )
goto LABEL_1764;
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 1);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
zero_velocity_acceleration();
dispatch_indexed_event_member(0x1Eu);
return;
case 0x31D:
if ( !*(_WORD *)(raw +  318) )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
dispatch_indexed_event_member(0x1Eu);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 1);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
*(float *)(raw +  248) = 0.0;
return;
}
v3 = 0.0;
}
if ( *(_WORD *)(raw +  318) == 1 )
{
v376 = *(float *)(raw +  244) - 0.2f;
*(float *)(raw +  244) = v376;
if ( v376 < v3 )
*(float *)(raw +  244) = v3;
if ( *(float *)(raw +  236) > 480.0 )
{
*(float *)(raw +  236) = 480.0;
*(float *)(raw +  244) = v3;
}
}
if ( (unsigned __int8)advance_frame_and_dispatch() )
LABEL_1755:
(*(void (__thiscall **)(void *, _DWORD))(*(_DWORD *)raw +  8))(raw, 0);
return;
case 0x31E:
if ( !*(_WORD *)(raw +  318) )
{
*(float *)(raw +  248) = *(float *)(raw +  248) - *(float *)(raw +  256);
if ( has_crossed_stage_surface_while_descending() )
{
dispatch_indexed_event_member(0x1Eu);
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  12))(raw, 1);
*(float *)(raw +  240) = stage_surface_height_at_x(this);
*(float *)(raw +  248) = 0.0;
return;
}
v3 = 0.0;
}
if ( *(_WORD *)(raw +  318) == 1 )
{
v377 = *(float *)(raw +  244) - 0.2f;
*(float *)(raw +  244) = v377;
if ( v377 < v3 )
*(float *)(raw +  244) = v3;
if ( *(float *)(raw +  236) < 800.0 )
{
*(float *)(raw +  236) = 800.0;
*(float *)(raw +  244) = v3;
}
}
LABEL_1764:
if ( (unsigned __int8)advance_frame_and_dispatch() )
LABEL_1765:
(*(void (__thiscall **)(void *, int))(*(_DWORD *)raw +  8))(raw, 700);
return;
default:
LABEL_1766:
update_common_action_state();
return;
}
  }
}
}
}

} // namespace th105
