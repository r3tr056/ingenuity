#include "./nanovg/nanovg.h"
#include "./nanovg/nanovg_gl.h"
#include "./nanovg/nanovg_gl_utils.h"

#include <string_view>

#ifndef FTKL_EXPORT
#define FTKL_EXPORT
#endif

#ifndef FTKL_NO_NVG_TYPEDEFS
typedef struct NVGcontext NVGcontext;
typedef struct NVGcolor NVGcolor;
typedef struct NVGglyphPosition NVGglyphPosition;
#endif

// Build and icon ID from the two coordinates into the icon sheet, where
// (0,0) refers to upper-leftmost icon and (1,0) the icon right next to it
#define FTKL_ICONID(x, y) ((x) | ((y) << 8))
// Alpha value used for disabled UI components
#define FTKL_DISABLED_ALPHA = 0.5

typedef struct ftklWidgetTheme {
    NVGcolor outlineColor;
    NVGcolor itemColor;
    NVGcolor innerColor;
    NVGcolor innterSelectedColor;
    NVGcolor textColor;
    NVGcolor textSelectedColor;
    int shadeTop;
    int shadeDown;
} ftklWidgetTheme;

typedef struct ftklNodeTheme
{
    NVGcolor nodeSelectedColor;
    NVGcolor wiresColor;
    NVGcolor textSelectedColor;
    NVGcolor activeNodeColor;
    NVGcolor wireSelectColor;
    NVGcolor nodeBackdropColor;
    int noodleCurving;
} ftklNodeTheme;

typedef struct ftklTheme
{
    NVGcolor bgColor;
    ftklWidgetTheme regularTheme;
    ftklWidgetTheme toolTheme;
    ftklWidgetTheme radioTheme;
    ftklWidgetTheme textFieldTheme;
    ftklWidgetTheme optionTheme;
    ftklWidgetTheme choiceTheme;
    ftklWidgetTheme numberFieldTheme;
    ftklWidgetTheme sliderTheme;
    ftklWidgetTheme scrollbarTheme;
    ftklWidgetTheme tooltipTheme;
    ftklWidgetTheme menuTheme;
    ftklWidgetTheme menuItemTheme;
    ftklNodeTheme nodeTheme;
} ftklTheme;

typedef enum ftklTextAlign {
    FTKL_LEFT = 0,
    FTKL_CENTER,
    FTKL_RIGHT
} ftklTextAlign;

typedef enum ftklWidgetState {
    FTKL_DEFAULT = 0,
    FTKL_HOVER,
    FTKL_ACTIVE,
} ftklWidgetState;

typedef enum ftklCornerFlags {
    FTKL_CORNER_NONE = 0,
    FTKL_CORNER_TOP_LEFT,
    FTKL_CORNER_TOP_RIGHT,
    FTKL_CORNER_BOTTOM_LEFT,
    FTKL_CORNER_BOTTOM_RIGHT,
    FTKL_CORNER_ALL,
    FTKL_CORNER_TOP,
    FTKL_CORNER_BOTTOM,
    FTKL_CORNER_LEFT,
    FTKL_CORNER_RIGHT,
} ftklCornerFlags;

enum {
    FTKL_WIDGET_HEIGHT = 21,
    FTKL_TOOL_WIDTH = 20,
    FTKL_NODE_PORT_RADIUS = 5,
    FTKL_NODE_MARGIN_TOP = 25,
    FTKL_NODE_MARGIN_DOWN = 5,
    FTKL_NODE_MARGIN_SIDE = 10,
    FTKL_NODE_TITLE_HEIGHT = 20,
    FTKL_NODE_ARROW_AREA_WIDTH = 20,
    FTKL_SPLITTER_AREA_SIZE = 12,
    FTKL_SCROLLBAR_WIDTH = 13,
    FTKL_SCROLLBAR_HEIGHT = 14,
    FTKL_VSPACING = 1,
    FTKL_VSPACING_GROUP = 8,
    FTKL_HSPACING = 8,
};

typedef enum ftklIcon {
    FTKL_ICON_HOME = FTKL_ICONID(0, 29),
    FTKL_ICON_QUESTION = FTKL_ICONID(1, 29),
    FTKL_ICON_ERROR = FTKL_ICONID(2, 29),
    FTKL_ICON_CANCEL = FTKL_ICONID(3, 29),
    FTKL_ICON_TRIA_RIGHT = FTKL_ICONID(4, 29),
    FTKL_ICON_TRIA_DOWN = FTKL_ICONID(5, 29),
    FTKL_ICON_TRIA_LEFT = FTKL_ICONID(6, 29),
    FTKL_ICON_TRIA_UP = FTKL_ICONID(7, 29),
    FTKL_ICON_ARROW_LEFTRIGHT = FTKL_ICONID(8, 29),
    FTKL_ICON_PLUS = FTKL_ICONID(9, 29),
    FTKL_ICON_DISCLOSURE_TRI_DOWN = FTKL_ICONID(10, 29),
    FTKL_ICON_DISCLOSURE_TRI_RIGHT = FTKL_ICONID(11, 29),
} ftklIcon;

class FTKLTheme {
public:
    void ftklSetTheme(ftklTheme theme);
    const ftklTheme *ftklGetTheme();
    void ftklSetIconImage(int image);
    void ftklSetFont(int fontface);
};

class Components {
public:
    void ftklLabel(NVGcontext *ctx, float x, float y, float w, float h, int icoID, std::string_view label);
    void ftklToolButton(NVGcontext *ctx, float x, float y, float w, float h, int flags, ftklWidgetState state, int icoID, std::string_view label);
    void ftklRadioButton(NVGcontext *ctx, float x, float y, float w, float h, int flags, ftklWidgetState state, int icoID, std::string_view label);
    void ftklTextFieldTextPos(NVGcontext *ctx, float x, float y, float w, float h, int icoID, std::string_view label, int px, int py);
    void ftklTextField(NVGcontext *ctx, float x, float y, float w, float h, int flags, ftklWidgetState stat, int icoID, std::string_view text, int cbegin, int cend);
    void ftklOptionButton(NVGcontext *ctx, float x, float y, float w, float h, ftklWidgetState state, std::string_view label);
    void ftklChoiceButton(NVGcontext *ctx, float x, float y, float w, float h, int flags, ftklWidgetState state, int icoID, std::string_view label);
    void ftklColorButton(NVGcontext *ctx, float x, float y, float w, float h, int flags, NVGcolor color);
    void ftklNumberField(NVGcontext *ctx, float x, float y, float w, float h, int flags, ftklWidgetState state, std::string_view label, std::string_view value);
    void ftklSlider(NVGcontext *ctx, float x, float y, float w, float h, int flags, ftklWidgetState state, float progress, std::string_view label, std::string_view value);
};

// IMPLEMENTATION

#include <memory>
#include <math.h>

#ifdef _MSC_VER
    // Supress security warinings
    #pragma warning (disable: 4996)
    #pragma warning (disable: 4100)
    #pragma warning (disable: 4244)
    #pragma warning (disable: 4305)
    
    #ifdef __cplusplus
    #define FTKL_INLINE inline
    #else
    #define FTKL_INLINE
    #endif

#include <float.h>
static float ftkl_fminf(float a, float b) {
    return _isnan(a) ? b : (_isnan(b) ? a : ((a < b) ? a : b));
}

#endif

#define FTKL_LABEL_FONT_SIZE 13

// default text padding in inner box
#define FTKL_PAD_LEFT 8
#define FTKL_PAD_RIGHT 8

// label: value separator string
#define FTKL_LABEL_SEPARATOR ": "

// alpha intensity of transparent items (0xa4)
#define FTKL_TRANSPARENT_ALPHA 0.643

// shade intensity of beveled panels
#define FTKL_BEVEL_SHADE 30
// shade intensity of beveled insets
#define FTKL_INSET_BEVEL_SHADE 30
// shade intensity of hovered inner boxes
#define FTKL_HOVER_SHADE 15
// shade intensity of splitter bevels
#define FTKL_SPLITTER_SHADE 100

// width of icon sheet
#define FTKL_ICON_SHEET_WIDTH 602
// height of icon sheet
#define FTKL_ICON_SHEET_HEIGHT 640
// gridsize of icon sheet in both dimensions
#define FTKL_ICON_SHEET_GRID 21
// offset of first icon tile relative to left border
#define FTKL_ICON_SHEET_OFFSET_X 5
// offset of first icon tile relative to top border
#define FTKL_ICON_SHEET_OFFSET_Y 10
// resolution of single icon
#define FTKL_ICON_SHEET_RES 16

// size of number field arrow
#define FTKL_NUMBER_ARROW_SIZE 4

// default text color
#define FTKL_COLOR_TEXT {{{ 0,0,0,1 }}}
// default highlighted text color
#define FTKL_COLOR_TEXT_SELECTED {{{ 1,1,1,1 }}}

// radius of tool button
#define FTKL_TOOL_RADIUS 4

// radius of option button
#define FTKL_OPTION_RADIUS 4
// width of option button checkbox
#define FTKL_OPTION_WIDTH 14
// height of option button checkbox
#define FTKL_OPTION_HEIGHT 15

// radius of text field
#define _TEXT_RADIUS 4

// radius of number button
#define FTKL_NUMBER_RADIUS 10

// radius of menu popup
#define FTKL_MENU_RADIUS 3
// feather of menu popup shadow
#define FTKL_SHADOW_FEATHER 12
// alpha of menu popup shadow
#define FTKL_SHADOW_ALPHA 0.5

// radius of scrollbar
#define FTKL_SCROLLBAR_RADIUS 7
// shade intensity of active scrollbar
#define FTKL_SCROLLBAR_ACTIVE_SHADE 15

// max glyphs for position testing
#define FTKL_MAX_GLYPHS 1024

// max rows for position testing
#define FTKL_MAX_ROWS 32

// text distance from bottom
#define FTKL_TEXT_PAD_DOWN 7

// stroke width of wire outline
#define FTKL_NODE_WIRE_OUTLINE_WIDTH 4
// stroke width of wire
#define FTKL_NODE_WIRE_WIDTH 2
// radius of node box
#define FTKL_NODE_RADIUS 8
// feather of node title text
#define FTKL_NODE_TITLE_FEATHER 1
// size of node title arrow
#define FTKL_NODE_ARROW_SIZE 9
