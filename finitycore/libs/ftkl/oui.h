

#ifndef _OUI_H_
#define _OUT_H


#ifndef OUI_EXPORT
#define OUI_EXPORT
#endif

enum {
    // Max size in bytes of a single UI data buffer
    UI_MAX_DATASIZE = 4096,
    // Max depth of a nested ui component
    UI_MAX_DEPTH = 64,
    // Max no of buffered input events
    UI_MAX_INPUT_EVENTS = 64,
    // Consecutive click threshold in ms
    UI_CLICK_THRESHOLD = 250,
};

typedef unsigned int UIuint;
typedef struct UIContext UIContext;
typedef enum UIItemState {
    UI_COLD = 0,
    UI_HOT,
    UI_ACTIVE,
    UI_FROZEN,
} UIItemState;

typedef enum UIBoxFlags {
    UI_ROW = 0x002,
    UI_COL = 0x003,
    UI_LAYOUT = 0x000,
    UI_FLEX = 0x002,
    UI_NOWRAP = 0x000,
    UI_WRAP = 0x004,
    UI_START = 0x008,
    UI_MIDDLE = 0x000,
    UI_END = 0x010,
    UI_JUSTIFY = 0x018,
} UIBoxFlags;

typedef enum UIlayoutFlags {
    // attachments (bit 5-8)
    // fully valid when parent uses UI_LAYOUT model
    // partially valid when in UI_FLEX model

    // anchor to left item or left side of parent
    UI_LEFT = 0x020,
    // anchor to top item or top side of parent
    UI_TOP = 0x040,
    // anchor to right item or right side of parent
    UI_RIGHT = 0x080,
    // anchor to bottom item or bottom side of parent
    UI_DOWN = 0x100,
    // anchor to both left and right item or parent borders
    UI_HFILL = 0x0a0,
    // anchor to both top and bottom item or parent borders
    UI_VFILL = 0x140,
    // center horizontally, with left margin as offset
    UI_HCENTER = 0x000,
    // center vertically, with top margin as offset
    UI_VCENTER = 0x000,
    // center in both directions, with left/top margin as offset
    UI_CENTER = 0x000,
    // anchor to all four directions
    UI_FILL = 0x1e0,
    // when wrapping, put this element on a new line
    // wrapping layout code auto-inserts UI_BREAK flags,
    // drawing routines can read them with uiGetLayout()
    UI_BREAK = 0x200
} UIlayoutFlags;

#endif