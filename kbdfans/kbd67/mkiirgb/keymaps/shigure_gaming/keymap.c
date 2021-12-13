/* Copyright 2019 dnsnrk
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

void matrix_init_user(void) {
  rgb_matrix_sethsv(0, 0, 0); // set default RGB color
};

enum custom_keycodes
{
  TSK_MGR,
  CTL_APP,
  RSFT_L3,
};

typedef enum
{ // quad function tap-dance
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP
} td_state_t;

typedef struct
{
  bool is_press_action;
  td_state_t state;
} td_tap_t;

enum custom_tap_dance
{
  CAPS_LAYR,
  RSFT_LAY3,
  KCFN_L2,
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void caps_finished(qk_tap_dance_state_t *state, void *user_data);
void caps_reset(qk_tap_dance_state_t *state, void *user_data);
void fn_finished(qk_tap_dance_state_t *state, void *user_data);
void fn_reset(qk_tap_dance_state_t *state, void *user_data);
void sft_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_reset(qk_tap_dance_state_t *state, void *user_data);

#define CAP_LYR TD(CAPS_LAYR)
#define FN_L2   TD(KCFN_L2)
#define RSFT_L3 TD(RSFT_LAY3)
#define DC_MUTE C(S(KC_M)) // used for mute/unmute
#define TSK_MGR C(S(KC_ESC))
#define CTL_APP CTL_T(KC_APP)
#define SERACH G(S(KC_N))

enum
{
  _L0 = 0,
  _L1,
  _L2,
  _L3,
  _L4,
};

/* 
  * ,--------------------------------------------------------------------------------------------------.
  * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  Backspace  | `    |
  * |-------------------------------------------------------------------------------------------+------+
  * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \     | Del  |
  * |-------------------------------------------------------------------------------------------+------+
  * | KC_CAPS  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter    | PgUp |
  * |-------------------------------------------------------------------------------------------+------+
  * | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   Shift    | Up  | PgDn |
  * +-------------------------------------------------------------------------┬---┬-------------+------+
  * | LCtrl | LAlt | LGUI |               Space                 | RGUI | RAlt |   | Left  | Dn  | Rght |
  * `-------------------------------------------------------------------------┘   └-------------+------´
  */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_65_ansi_blocker( /* Base Layer */
                                      KC_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   KC_HOME,
                                      KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLASH, KC_PGUP,
                                      CAP_LYR, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,    KC_PGDN,
                                      KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            RSFT_L3,  KC_UP,     KC_END,
                                      KC_LCTL, KC_LGUI,  KC_LALT,                   KC_SPC,                    FN_L2,            KC_RCTL,            KC_LEFT,  KC_DOWN,   KC_RGHT),
    [_L1] = LAYOUT_65_ansi_blocker( /* FN */
                                      KC_GRV,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL,    KC_INS,
                                      _______, KC_HOME,  KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,   KC_PSCR,
                                      _______, KC_LEFT,  KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, _______, _______, _______, _______,  _______,            _______,   _______,
                                      _______, _______,  _______, KC_CALC, _______, _______, SERACH,  TSK_MGR, _______, _______, _______,            _______,  _______,   _______,
                                      _______, _______,  _______,                   KC_DEL,                    _______,          CTL_APP,            _______,  _______,   _______),
    [_L2] = LAYOUT_65_ansi_blocker( /* Numpad */
                                      KC_GRV,  _______,  _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______,  KC_PMNS,  KC_PPLS,  _______,   KC_SLEP,
                                      _______, KC_HOME,  KC_UP,   KC_END,  KC_PGUP, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______,  KC_PAST,  KC_PSLS,  _______,   _______,
                                      _______, KC_LEFT,  KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______,  _______,            _______,   _______,
                                      _______, _______,  _______, KC_CALC, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_NLCK,            _______,  _______,   _______,
                                      _______, GUI_TOG,  _______,                   _______,                   _______,          _______,            _______,  _______,   _______),
    [_L3] = LAYOUT_65_ansi_blocker( /* Media and RGB */
                                      RGB_TOG, RGB_M_P,  _______, _______, NK_TOGG, KC_VOLD, KC_VOLU, KC_MPLY, KC_MUTE, _______, _______,  _______,  _______,  _______,   RGB_SAI,
                                      _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  RESET,     RGB_SAD,
                                      _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            EEP_RST,   RGB_HUI,
                                      _______, _______,  _______, _______, _______, _______, _______, DC_MUTE, _______, _______, _______,            _______,  RGB_MOD,   RGB_HUD,
                                      _______, _______,  _______,                   _______,                   TO(0),            TO(4),              RGB_VAD,  RGB_RMOD,  RGB_VAI),
	  [_L4] = LAYOUT_65_ansi_blocker( /* Gaming */
                                      KC_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   DC_MUTE,
                                      KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLASH, KC_PGUP,
                                      KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,    KC_PGDN,
                                      KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            KC_RSFT,  KC_UP,     KC_LGUI,
                                      KC_LCTL, KC_NO,    KC_LALT,                   KC_SPC,                    TO(0),            KC_RCTL,            KC_LEFT,  KC_DOWN,   KC_RGHT)                                     
}; 

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
  switch (get_highest_layer(layer_state))
  {
  case _L1:
    {
      rgb_matrix_set_color(61, 0xaa, 0xcc, 0x11);
    }
    break;
  case _L2:
    {
      rgb_matrix_set_color(61, 0xff, 0x99, 0x00);
    }
    break;
  case _L3:
    {
      rgb_matrix_set_color(61, 0xee, 0x00, 0x77);
    }
    break;
  case _L4:
	{
      rgb_matrix_set_color(59, 0xee, 0x33, 0x33);	  
      rgb_matrix_set_color(61, 0xee, 0x33, 0x33);
	}
	break;
  default:
    break;
  }
}


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state)
{
  if (state->count == 1)
  {
    if (!state->pressed)
      return TD_SINGLE_TAP;
    else
      return TD_SINGLE_HOLD;
  }
  else if (state->count == 2)
    return TD_DOUBLE_TAP;
  else
    return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t caps_tap_state = {
    .is_press_action = true,
    .state = TD_NONE};

static td_tap_t fn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE};

static td_tap_t sft_tap_state = {
    .is_press_action = true,
    .state = TD_NONE};

// Functions that control what our tap dance key does
void caps_finished(qk_tap_dance_state_t *state, void *user_data)
{
  caps_tap_state.state = cur_dance(state);
  switch (caps_tap_state.state)
  {
  case TD_SINGLE_TAP:
    tap_code(KC_CAPS);
    break;
  case TD_SINGLE_HOLD:
    layer_on(_L1);
    break;
  case TD_DOUBLE_TAP:
    // Check to see if the layer is already set
    if (layer_state_is(_L1))
    {
      // If already set, then switch it off
      layer_off(_L1);
    }
    else
    {
      // If not already set, then switch the layer on
      layer_on(_L1);
    }
    break;
  default:
    break;
  }
};

void caps_reset(qk_tap_dance_state_t *state, void *user_data)
{
  // If the key was held down and now is released then switch off the layer
  if (caps_tap_state.state == TD_SINGLE_HOLD)
  {
    layer_off(_L1);
  }
  caps_tap_state.state = TD_NONE;
};

//tap dance for Fn
void fn_finished(qk_tap_dance_state_t *state, void*user_data)
{
  fn_tap_state.state = cur_dance(state);
  switch (fn_tap_state.state)
  {
    case TD_SINGLE_TAP:
      set_oneshot_layer(_L2, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case TD_SINGLE_HOLD:
      layer_on(_L2);
      break;
    case TD_DOUBLE_TAP:
      if (layer_state_is(_L2))
    {
      layer_off(_L2);
    }
    else
    {
      layer_on(_L2);
    }
      break;
    default:
      break;
  }
};

void fn_reset(qk_tap_dance_state_t *state, void*user_data)
{
  switch (fn_tap_state.state) 
  {
    case TD_SINGLE_HOLD:
      layer_off(_L2);
      break;
    default:
      break;
  }
};

void sft_finished(qk_tap_dance_state_t *state, void*user_data)
{
  sft_tap_state.state = cur_dance(state);
  switch (sft_tap_state.state)
  {
    case TD_SINGLE_TAP:
      // register_code(KC_RSFT);
      set_oneshot_layer(_L3, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case TD_SINGLE_HOLD:
      register_code(KC_RSFT);
      break;
    case TD_DOUBLE_TAP:
      if (layer_state_is(_L3))
    {
      layer_off(_L3);
    }
    else
    {
      layer_on(_L3);
    }
      break;
    default:
      break;
  }
};

void sft_reset(qk_tap_dance_state_t *state, void*user_data)
{
  switch (sft_tap_state.state) 
  {
    // case TD_SINGLE_TAP:
    //   unregister_code(KC_RSFT);
    case TD_SINGLE_HOLD:
      unregister_code(KC_RSFT);
      break;
    default:
      break;
  }
};

// Associate tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [CAPS_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_finished, caps_reset),
    [KCFN_L2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_finished, fn_reset),
    [RSFT_LAY3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset)
};

void keyboard_post_init_user(void)
{
  if (IS_HOST_LED_ON(USB_LED_NUM_LOCK))
  { // turn on Num lock by defautl
    tap_code(KC_NUMLOCK);
  }
}

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};