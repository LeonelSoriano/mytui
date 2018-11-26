#include "mytui_config.h"


/** #define CONF_FOLDER .config
  * #define TUI_FOLDER_CONF mytui
  * #define CONF_FILE_NAME init.conf */

void ini_conf_file(){
    print_info("ini_con_file");
    verification_init_file();
    print_info("terminada verificacion de existencia de archivos de configuracion");

//bool exist_file(const char* path);
}


static void verification_init_file(){
    const char* folder_home = get_home_folder();

    char conf_folder_resolution[ strlen(folder_home) + (strlen(SEPARATOR_FOLDER) * 3) +
        strlen(CONF_FONDER) + strlen(TUI_FOLDER_CONF) + strlen(CONF_FILE_NAME)];

    strcpy(conf_folder_resolution, folder_home);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FONDER);

    if(exist_file(conf_folder_resolution) == false){
        print_error("No se consigue archivo .conf");
        exit(0);
    }

    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_CONF);

    if(exist_file(conf_folder_resolution) == false){
        char cmd_create_folder_mitui_conf[(strlen(MKDIR) + strlen(conf_folder_resolution))];
        strcpy(cmd_create_folder_mitui_conf, MKDIR);
        strcat(cmd_create_folder_mitui_conf, conf_folder_resolution);
        run_cmd_silent(cmd_create_folder_mitui_conf);
    }

    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FILE_NAME);

    if(exist_file(conf_folder_resolution) == false){
        char cmd_create_folder_mitui_conf[(strlen(TOUCH) + strlen(conf_folder_resolution))];
        strcpy(cmd_create_folder_mitui_conf, TOUCH);
        strcat(cmd_create_folder_mitui_conf, conf_folder_resolution);
        run_cmd_silent(cmd_create_folder_mitui_conf);
    }
}
