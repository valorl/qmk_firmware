// https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
#undef TAPPING_TERM
#define TAPPING_TERM 100

#define TAPPING_TERM_PER_KEY

// https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#ignore-mod-tap-interrupt
// #undef IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT
// https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
//#define PERMISSIVE_HOLD

// Must be plugged as defined here
#undef MASTER_RIGHT
#undef MASTER_LEFT
#define MASTER_LEFT

#define PREVENT_STUCK_MODIFIERS

