#ifndef GZ_H
#define GZ_H
#include <stdint.h>
#include <vector/vector.h>
#include <n64.h>
#include "settings.h"
#include "z64.h"
#include "zu.h"

enum cmdact
{
  CMDACT_HOLD,
  CMDACT_PRESS,
  CMDACT_PRESS_ONCE,
};

struct command_info
{
  const char           *name;
  void                (*proc)(void);
  enum cmdact           activation_type;
};

enum col_view_state
{
  COLVIEW_INACTIVE,
  COLVIEW_START,
  COLVIEW_ACTIVE,
  COLVIEW_STOP,
  COLVIEW_STOPPING,
  COLVIEW_RESTART,
  COLVIEW_RESTARTING,
};

enum hit_view_state
{
  HITVIEW_INACTIVE,
  HITVIEW_START,
  HITVIEW_ACTIVE,
  HITVIEW_STOP,
  HITVIEW_STOPPING,
};

enum cull_view_state
{
  CULLVIEW_INACTIVE,
  CULLVIEW_START,
  CULLVIEW_ACTIVE,
  CULLVIEW_STOP,
  CULLVIEW_STOPPING,
};

enum holl_view_state
{
  HOLLVIEW_INACTIVE,
  HOLLVIEW_START,
  HOLLVIEW_ACTIVE,
  HOLLVIEW_BEGIN_STOP,
  HOLLVIEW_STOP,
};

enum path_view_state
{
  PATHVIEW_INACTIVE,
  PATHVIEW_START,
  PATHVIEW_ACTIVE,
  PATHVIEW_STOP,
  PATHVIEW_STOPPING,
  PATHVIEW_RESTART,
  PATHVIEW_RESTARTING,
};

enum cam_mode
{
  CAMMODE_CAMERA,
  CAMMODE_VIEW,
};

enum cam_bhv
{
  CAMBHV_MANUAL,
  CAMBHV_BIRDSEYE,
  CAMBHV_RADIAL,
};

struct memory_file
{
  z64_file_t            z_file;
  _Bool                 entrance_override;
  int32_t               next_entrance;
  uint16_t              scene_index;
  uint32_t              scene_flags[9];
  qs510_t               start_icon_dd;
  uint16_t              pause_screen;
  int16_t               item_screen_cursor;
  int16_t               quest_screen_cursor;
  int16_t               equip_screen_cursor;
  int16_t               map_screen_cursor;
  int16_t               item_screen_x;
  int16_t               equipment_screen_x;
  int16_t               item_screen_y;
  int16_t               equipment_screen_y;
  int16_t               pause_screen_cursor;
  int16_t               quest_screen_item;
  int16_t               quest_screen_hilite;
  int16_t               quest_screen_song;
};

enum movie_state
{
  MOVIE_IDLE,
  MOVIE_RECORDING,
  MOVIE_PLAYING,
};

struct movie_input
{
  z64_controller_t      raw;            /* 0x0000 */
  uint16_t              pad_delta;      /* 0x0004 */
                                        /* 0x0006 */
};

struct movie_seed
{
  int                   frame_idx;
  uint32_t              old_seed;
  uint32_t              new_seed;
};

struct movie_oca_input
{
  int32_t               frame_idx;
  uint16_t              pad;
  int8_t                adjusted_x;
  int8_t                adjusted_y;
};

struct movie_oca_sync
{
  int32_t               frame_idx;
  int32_t               audio_frames;
};

struct movie_room_load
{
  int32_t               frame_idx;
};

struct log_entry
{
  char                 *msg;
  int                   age;
};

struct selected_actor
{
  z64_actor_t          *ptr;
  int32_t               id;
  int32_t               type;
};

struct gz
{
  /* 0x0000 */  _Bool                 ready;
  /* 0x0001 */  uint8_t               profile;
  /* 0x0004 */  struct menu          *menu_global;
  /* 0x0008 */  struct menu          *menu_main;
  /* 0x000C */  struct menu          *menu_explorer;
  /* 0x0010 */  struct menu          *menu_watches;
  /* 0x0014 */  struct menu          *menu_mem;
  /* 0x0018 */  struct menu_item     *menu_watchlist;
  /* 0x001C */  _Bool                 menu_active;
  /* 0x0020 */  struct log_entry      log[SETTINGS_LOG_MAX];
  /* 0x0040 */  _Bool                 entrance_override_once;
  /* 0x0041 */  _Bool                 entrance_override_next;
  /* 0x0044 */  int32_t               next_entrance;
  /* 0x0048 */  uint16_t              day_time_prev;
  /* 0x004C */  int                   target_day_time;
  /* 0x0050 */  int32_t               frames_queued;
  /* 0x0054 */  struct zu_disp_p      z_disp_p;
  /* 0x0074 */  uint32_t              disp_hook_size[4];
  /* 0x0084 */  uint32_t              disp_hook_p[4];
  /* 0x0094 */  uint32_t              disp_hook_d[4];
  /* 0x00A4 */  _Bool                 angle_enable;
  /* 0x00A6 */  z64_angle_t           angle_desired;
  /* 0x00A8 */  z64_angle_t           angle_best_matching;
  /* 0x00AA */  int16_t               angle_x;
  /* 0x00AE */  int16_t               angle_y;
  /* 0x00B0 */  _Bool                 angle_use_min;
  /* 0x00B2 */  uint16_t              angle_r_min;
  /* 0x00B4 */  _Bool                 angle_use_input;
  /* 0x00B8 */  enum movie_state      movie_state;
  /* 0x00BC */  z64_controller_t      movie_input_start;
  /* 0x00C0 */  struct vector         movie_input;
  /* 0x00DC */  struct vector         movie_seed;
  /* 0x00F8 */  struct vector         movie_oca_input;
  /* 0x0114 */  struct vector         movie_oca_sync;
  /* 0x0130 */  struct vector         movie_room_load;
  /* 0x014C */  int                   movie_frame;
  /* 0x0150 */  int                   movie_seed_pos;
  /* 0x0154 */  int                   movie_oca_input_pos;
  /* 0x0158 */  int                   movie_oca_sync_pos;
  /* 0x015C */  int                   movie_room_load_pos;
  /* 0x0160 */  int                   movie_last_recorded_frame;
  /* 0x0164 */  int                   movie_rerecords;
  /* 0x0168 */  _Bool                 oca_input_flag;
  /* 0x0169 */  _Bool                 oca_sync_flag;
  /* 0x016A */  _Bool                 room_load_flag;
  /* 0x016C */  z64_controller_t      z_input_mask;
  /* 0x0170 */  _Bool                 vcont_enabled[4];
  /* 0x0174 */  z64_input_t           vcont_input[4];
  /* 0x01D4 */  int32_t               frame_counter;
  /* 0x01D8 */  int32_t               lag_vi_offset;
  /* 0x01DC */  int64_t               cpu_counter;
  /* 0x01E0 */  int32_t               cpu_counter_freq;
  /* 0x01E4 */  _Bool                 timer_active;
  /* 0x01E8 */  int64_t               timer_counter_offset;
  /* 0x01F0 */  int64_t               timer_counter_prev;
  /* 0x01F8 */  enum col_view_state   col_view_state;
  /* 0x01FC */  enum hit_view_state   hit_view_state;
  /* 0x0200 */  enum cull_view_state  cull_view_state;
  /* 0x0204 */  enum path_view_state  path_view_state;
  /* 0x0208 */  enum holl_view_state  holl_view_state;
  /* 0x020C */  _Bool                 noclip_on;
  /* 0x020D */  _Bool                 hide_rooms;
  /* 0x020E */  _Bool                 hide_actors;
  /* 0x020F */  _Bool                 free_cam;
  /* 0x0210 */  _Bool                 lock_cam;
  /* 0x0214 */  enum cam_mode         cam_mode;
  /* 0x0218 */  enum cam_bhv          cam_bhv;
  /* 0x021C */  int16_t               cam_dist_min;
  /* 0x021E */  int16_t               cam_dist_max;
  /* 0x0220 */  float                 cam_pitch;
  /* 0x0224 */  float                 cam_yaw;
  /* 0x0228 */  z64_xyzf_t            cam_pos;
  /* 0x0234 */  void                 *state_buf[SETTINGS_STATE_MAX];
  /* 0x0240 */  uint8_t               state_slot;
  /* 0x0241 */  _Bool                 reset_flag;
  /* 0x0242 */  _Bool                 frame_flag;
  /* 0x0244 */  struct selected_actor selected_actor;
  /* 0x0250 */
};

void          gz_apply_settings();
void          gz_show_menu(void);
void          gz_hide_menu(void);
void          gz_log(const char *fmt, ...);
void          gz_warp(int16_t entrance_index,
                      uint16_t cutscene_index, int age);
void          gz_set_input_mask(uint16_t pad, uint8_t x, uint8_t y);

void          command_break(void);
void          command_levitate(void);
void          command_fall(void);
void          command_turbo(void);
void          command_noclip(void);
void          command_fileselect(void);
void          command_reload(void);
void          command_void(void);
void          command_age(void);
void          command_savestate(void);
void          command_loadstate(void);
void          command_savepos(void);
void          command_loadpos(void);
void          command_prevstate(void);
void          command_nextstate(void);
void          command_prevpos(void);
void          command_nextpos(void);
void          command_pause(void);
void          command_advance(void);
void          command_recordmacro(void);
void          command_playmacro(void);
void          command_colview(void);
void          command_hitview(void);
void          command_pathview(void);
void          command_resetlag(void);
void          command_togglewatches(void);
void          command_timer(void);
void          command_resettimer(void);
void          command_starttimer(void);
void          command_stoptimer(void);
void          command_reset(void);

void          z_to_movie(int movie_frame, z64_input_t *zi, _Bool reset);
void          movie_to_z(int movie_frame, z64_input_t *zi, _Bool *reset);
void          gz_movie_rewind(void);
void          gz_movie_seek(int frame);

void          gz_vcont_set(int port, _Bool plugged, z64_controller_t *cont);
void          gz_vcont_get(int port, z64_input_t *input);

void          gz_angle_finder(void);
void          gz_angle_input_get(z64_input_t *input);

void          gz_col_view(void);
void          gz_hit_view(void);
void          gz_cull_view(void);
void          gz_path_view(void);
void          gz_holl_view(void);

void          gz_update_cam(void);
void          gz_free_view(void);

void          gz_noclip_start(void);
void          gz_noclip_stop(void);

struct menu  *gz_warps_menu(void);
struct menu  *gz_scene_menu(void);
struct menu  *gz_cheats_menu(void);
struct menu  *gz_inventory_menu(void);
struct menu  *gz_equips_menu(void);
struct menu  *gz_file_menu(void);
struct menu  *gz_macro_menu(void);
struct menu  *gz_debug_menu(void);
struct menu  *gz_settings_menu(void);

extern struct gz            gz;
extern struct command_info  command_info[COMMAND_MAX];

#endif
