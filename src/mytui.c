#include "mytui.h"
/**
 * inicia terbox
 * @see init_mytui
 */
static void _init_termbox();

/**
 * termina y librera termbox
 * @see end_mytui
 */
static void _free_termbox();

static void _init_termbox()
{
    int ret = tb_init();
    if (ret) {
        print_error("_init_termbox: errror al iniciar terbox ");
        exit(EXIT_FAILURE);
    }
    tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
    tb_select_output_mode(TB_OUTPUT_256);
}

static void _free_termbox() { tb_shutdown(); }

/*inicia todo*/
void init_mytui()
{
    nodeBufer = NULL;
    // hash_conf = NULL;
    ini_conf_file();
    load_conf_map(&_confMap);

    // print_info("resolve value que es:
    // %s",resolve_value(_confMap,"entry.bg",NULL) );

    init_mytui_logger();
    init_buffer(&nodeBufer);
    _init_termbox();
    screen_manager(&nodeBufer);
}

void end_mytui()
{
    _free_termbox();
    free_conf_map(&_confMap);
    free_mytui_logger();
    free_buffer(&nodeBufer);
    delete_active_miTuiWidget();
    delete_mytui_listener_all();
}

static void holaEvent(){
    //print_line_log(MytuiLoggerTypeError, "hola Desde evento");
}

void update_termbox()
{
    MytuiContainer *mytuiContainer = NULL;
    INIT_MYTUI_CONTAINER(paramContainer);
    paramContainer.type = MYTUI_CONTAINER_ROOT;
    paramContainer.decoration = true;
    mytui_inicialize_container(&mytuiContainer, paramContainer);
    add_ChildContainer(&mytuiContainer);


    MiTuiWidget *label = init_MyTuiWidgetLabel("leonelsoriano", 0, 0, -1, 1, -1, -1);
    add_childContainerWidget(&mytuiContainer, 2, 1, 0, 1, &label);

    // el update
    update_MytuiContainer_childContainer(mytuiContainer);
    //add_mytui_event_listener(holaEvent, mytuiEventClickPrincipal, label);


    // init btn
    // test
    MiTuiWidget *btn = init_MyTuiWidgetButton("BTN", 10, 10, 10, 2, -1, -1, -1);


    update_MyTuiWidget(btn);
    add_mytui_event_listener(holaEvent, mytuiEventClickPrincipal, btn);


    MiTuiWidget *btn2 = init_MyTuiWidgetButton("BTN2", 40, 10, 10, 2, -1, -1, -1);

    add_mytui_event_listener(holaEvent, mytuiEventClickPrincipal, btn2);
    update_MyTuiWidget(btn2);


    MiTuiWidget *textBox = init_MyTuiWidgetTextBox(30, 30, 20, 1, -1, -1, "hola");
    update_MyTuiWidget(textBox);
    // test


    // prueba animacion
/*    MytuiAnimation *animation = init_MytuiAnimation(btn);
    add_step_MytuiAnimation(&animation, mytuiAnimationMove, (double[]){-1, -1, 3, 4},
                            0.2);
    add_step_MytuiAnimation(&animation, mytuiAnimationMove, (double[]){1, 1, 3, 4},
                            0.2);

    update_mytuiAnimation(&animation);
    free_MytuiAnimation(&animation);
*/

    screen_manager(&nodeBufer);


    struct tb_event ev;
    while (tb_poll_event(&ev)) {
        switch (ev.type) {

        case TB_EVENT_MOUSE:
            if (ev.key == TB_KEY_MOUSE_LEFT) {
                //				mx = ev.x;
                //				my = ev.y;

                mouse_manager_event_fire(ev.x, ev.y);

                screen_manager(&nodeBufer);
            }
            break;
        case TB_EVENT_KEY:
            switch (ev.key) {
                case TB_KEY_ESC:
                    free_mytui_container(&mytuiContainer);
                    goto OUT_EVENT_POOL;

                case TB_KEY_CTRL_A: {

//                    print_line_log(MytuiLoggerTypeError, "hola Desde eventWidget %c",ev.key);
                    break;
                }
            }
            print_line_log(MytuiLoggerTypeError, "hola Desde eventWidget %d",ev.key);
            action_active_miTuiWidget(ev.ch, ev.key);
            screen_manager(&nodeBufer);

            break;
        case TB_EVENT_RESIZE:
            //init_screen_manager(&nodeBufer);
            break;
        }

    }


OUT_EVENT_POOL:

    delete_mytui_listener(label, mytuiEventClickPrincipal);
    free_MyTuiWidget(&btn);
    free_MyTuiWidget(&btn2);
    free_MyTuiWidget(&textBox);
    return;

}
