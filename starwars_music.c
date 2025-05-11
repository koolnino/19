#include <furi.h>
#include <gui/gui.h>
#include <gui/view_port.h>
#include <furi_hal.h>

// Notes definition
#define NOTE_A4 440
#define NOTE_F4 349
#define NOTE_C5 523
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_GS4 415
#define NOTE_A5 880

int melody[] = {
    NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5,
    NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5,
    NOTE_C5, NOTE_GS4, NOTE_F4, NOTE_C5,
    NOTE_A4
};

int durations[] = {
    500, 500, 350, 150,
    500, 350, 150, 650,
    500, 500, 500, 350,
    150, 500, 350, 150,
    650
};

static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);
    canvas_draw_str(canvas, 10, 30, "Playing Star Wars...");
}

int32_t starwars_music_app(void* p) {
    UNUSED(p);

    Gui* gui = furi_record_open("gui");
    ViewPort* vp = view_port_alloc();
    view_port_draw_callback_set(vp, draw_callback, NULL);
    gui_add_view_port(gui, vp, GuiLayerFullscreen);

    for (int i = 0; i < sizeof(melody)/sizeof(int); i++) {
        int duration = durations[i];
        furi_hal_pwm_start(melody[i], 50);
        furi_delay_ms(duration);
        furi_hal_pwm_stop();
        furi_delay_ms(duration * 0.3);
    }

    furi_delay_ms(500);
    gui_remove_view_port(gui, vp);
    view_port_free(vp);
    furi_record_close("gui");

    return 0;
}