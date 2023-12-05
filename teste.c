#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define TILE_SIZE 92

char textoDebug[2000];

void must_init(bool inicializacao_bem_sucedida, const char* description) {
    if (inicializacao_bem_sucedida) return;
    printf("Erro ao inicializar %s.", description);
    exit(1);
}

void exibir_mensagem(ALLEGRO_FONT* font, const char* mensagem) {
    al_draw_textf(font, al_map_rgb(255, 255, 255), 640, 50, ALLEGRO_ALIGN_CENTER, "%s\n", mensagem);
    al_flip_display();
    al_rest(1.0);
}

void tooltip(ALLEGRO_FONT* font, const char* texto, int mouse_x, int mouse_y) {
    int largura = 220;
    int altura = 100;
    al_draw_filled_rectangle(mouse_x, mouse_y, mouse_x + largura, mouse_y + altura, al_map_rgb(3, 181, 24));
    al_draw_textf(font, al_map_rgb(0, 0, 0), mouse_x + 15, mouse_y + 10, 20, "%s", texto);
}

typedef struct {
    int x, y;
    ALLEGRO_BITMAP* abob;
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR hover_color;
    int is_hovered;
} Abobora;

int isMouseOverPumpkim(Abobora* abob, int mouse_x, int mouse_y) {
    return (mouse_x >= abob->x &&
        mouse_x <= abob->x + al_get_bitmap_width(abob->abob) &&
        mouse_y >= abob->y &&
        mouse_y <= abob->y + al_get_bitmap_height(abob->abob));
}

void checaClickAbobora(int matriz[3][14], int inicio_x, int fim_y, int mouse_x, int mouse_y) {
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 14; coluna++) {

            int x = inicio_x + coluna * TILE_SIZE;
            int y = fim_y + linha * TILE_SIZE;

            if (mouse_x > x &&
                mouse_y > y &&
                mouse_x < x + TILE_SIZE &&
                mouse_y < y + TILE_SIZE) {
                printf("Clicando em cima do quadrado x = %d y = %d\n", linha, coluna);
            }
        }
    }
}

void desenharMatriz(int matriz[3][14], int inicio_x, int fim_y, int mouse_x, int mouse_y, Abobora* aboboras, ALLEGRO_EVENT_QUEUE* queue) {
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 14; coluna++) {

            int x = inicio_x + coluna * TILE_SIZE;
            int y = fim_y + linha * TILE_SIZE;

            if (matriz[linha][coluna] == 1) {
                al_draw_filled_rectangle(x, y, x + TILE_SIZE, y + TILE_SIZE, al_map_rgb(163, 210, 119));
            }
            else if (matriz[linha][coluna] == 2) {
                al_draw_filled_rectangle(x, y, x + TILE_SIZE, y + TILE_SIZE, al_map_rgb(125, 86, 64));
                for (int i = 0; i < 4; i++) {
                    // Verifica se o mouse está sobre a abóbora
                    if (isMouseOverPumpkim(&aboboras[i], mouse_x, mouse_y)) {
                        // Atualiza a cor para a cor de destaque
                        aboboras[i].is_hovered = 1;
                    }
                    else {
                        // Restaura a cor original
                        aboboras[i].is_hovered = 0;
                    }

                    // Desenha a abóbora com a cor apropriada
                    al_draw_tinted_bitmap(aboboras[i].abob, aboboras[i].is_hovered ? aboboras[i].hover_color : aboboras[i].color, aboboras[i].x, aboboras[i].y, 0);
                }
            }
            else if (matriz[linha][coluna] == 3) {
                al_draw_filled_rectangle(x, y, x + TILE_SIZE, y + TILE_SIZE, al_map_rgb(112, 83, 57));
            }
        }
    }
}

int main() {
    must_init(al_init(), "Allegro");
    must_init(al_init_font_addon(), "addons de fonte");
    must_init(al_init_ttf_addon(), "addons do Allegro");
    ALLEGRO_FONT* font = al_load_ttf_font("goethe\\GoetheBold.ttf", 28, 0);
    must_init(font, "fonte");
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    must_init(display, "display");
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "fila de eventos");
    must_init(al_init_image_addon(), "addons de imagem");
    ALLEGRO_BITMAP* abob = al_load_bitmap("abob.png");
    must_init(abob, "abob");
    must_init(al_init_primitives_addon(), "primitives addon");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");
    must_init(al_install_keyboard(), "teclado");
    must_init(al_install_mouse(), "mouse");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;

    bool done = false;
    bool redraw = true;

    int mouse_x = 0;
    int mouse_y = 0;

    bool mostrar_tooltip = false;
    bool arrastando = false;
    bool hover = false;

    int matriz[3][14] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 1},
        {1, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 1}
    };

    // Inicializando array de abóboras
    Abobora aboboras[4];

    for (int i = 0; i < 4; i++) {
        aboboras[i].abob = al_load_bitmap("abob.png");
        aboboras[i].color = al_map_rgb(255, 255, 255);
        aboboras[i].hover_color = al_map_rgb(255, 0, 0);
        aboboras[i].is_hovered = 0;

        // Definindo as posições iniciais para as quatro abóboras
        aboboras[i].x = 200 + i * 150;  // Ajuste esses valores conforme necessário
        aboboras[i].y = 200;
    }

    while (1) {
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(255, 255, 255));
        desenharMatriz(matriz, 0, 444, mouse_x, mouse_y, aboboras, queue);

        switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
            if ((mouse_x >= 960 && mouse_x <= 1920) && (mouse_y >= 520 && mouse_y <= 720)) {
                mostrar_tooltip = true;
                al_start_timer(timer);
            }
            else {
                mostrar_tooltip = false;
                al_stop_timer(timer);
            }
            if (arrastando) {
                mouse_x += event.mouse.dx;
                mouse_y += event.mouse.dy;
            }
            if (hover) {
            }
            break;
        case ALLEGRO_EVENT_TIMER:
            if ((al_get_timer_started(timer)) && (mostrar_tooltip)) {
                tooltip(font, "Essa \u00e9 uma tooltip!", mouse_x, mouse_y);
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
            printf("x = %d\ny = %d\n\n", mouse_x, mouse_y);
            if (event.mouse.button & 1) {
                if ((event.mouse.x >= 480 && event.mouse.x <= 800) && (event.mouse.y >= 300 && event.mouse.y <= 600)) {
                    arrastando = true;
                }
            }
            checaClickAbobora(matriz, 0, 444, mouse_x, mouse_y);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            arrastando = false;
            break;
        }

        if (done) {
            break;
        }

        al_draw_text(font, al_map_rgb(0, 0, 0), 10, 10, 0, textoDebug);

        al_flip_display();

        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_set_target_bitmap(al_get_backbuffer(display));
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}
