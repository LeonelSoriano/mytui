#include "until.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>


struct InfoTerm get_info_term(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    struct InfoTerm infoTerm;
    infoTerm.width = w.ws_col;
    infoTerm.width = w.ws_col;
    infoTerm.height = w.ws_row;
    return infoTerm;
}

void run_cmd_silent(const char *cmd){
    const char *cmd_silent = " >/dev/null 2>&1";
    //const char *cmd_silent = " ";
    int max_buffer_cmd = strlen(cmd_silent) + strlen(cmd);
    char result[max_buffer_cmd];
    strcpy(result, cmd);
    strcat(result, cmd_silent);
    int is_ok = system(result);
    if(is_ok != 0){
        print_error( "run_cmd_silent: code Error es: %d", is_ok);
    }
}


bool exist_file(const char* path){
    struct stat buffer;
    return (stat(path,&buffer) == 0)? true: false;
}

const char* get_home_folder(){
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        struct passwd *pw = getpwuid(getuid());
        homedir = pw->pw_dir;
    }else{
        homedir = getenv("HOME");
    }
    return homedir;
}

/** void sum(int numargs, ...) {
  *     int     total = 0;
  *     va_list ap;
  *
  *     printf("sum() called with %d params:", numargs);
  *     va_start(ap, numargs);
  *     while (numargs--)
  *         total += va_arg(ap, int);
  *     va_end(ap);
  *
  *     printf(" %d\n", total);
  *
  *     return;
  * } */

void print_error(const char *msg, ...){
    va_list args;
    va_start (args, msg);
    int msg_len = strlen(msg);
    int msg_len_red = strlen(MYTUI_COLOR_RED);
    int msg_len_nrm = strlen(MYTUI_COLOR_RNM);
    int msg_len_new_line = strlen("\n");
    char tmp_str[msg_len + msg_len_red + msg_len_nrm + msg_len_new_line];

    strcpy(tmp_str, MYTUI_COLOR_RED);
    strcat(tmp_str, msg);
    strcat(tmp_str, MYTUI_COLOR_RNM);
    strcat(tmp_str, "\n");
    vfprintf( stderr, tmp_str , args);
    va_end (args);
}

void print_info(const char *msg, ...){

    time_t timer;
    char buffer[26];
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    const char* msg_info = " INFO: ";
    va_list args;
    va_start (args, msg);
    int msg_len = strlen(msg);
    int msg_len_blue = strlen(MYTUI_COLOR_BLUE);
    int msg_len_nrm = strlen(MYTUI_COLOR_RNM);
    int msg_len_title = strlen(msg_info);
    int msg_len_new_line = strlen("\n");
    int msg_len_time = strlen(buffer);
    char tmp_str[msg_len + msg_len_blue + msg_len_nrm  + msg_len_title + msg_len_new_line +
       msg_len_time ];

    strcpy(tmp_str, MYTUI_COLOR_BLUE);
    strcat(tmp_str, buffer);
    strcat(tmp_str, msg_info);
    strcat(tmp_str, MYTUI_COLOR_RNM);
    strcat(tmp_str, msg);
    strcat(tmp_str, "\n");
    vfprintf( stderr, tmp_str , args);
    va_end (args);
}

bool strIsInt(const char *str){
    if(str == NULL){
        print_error("strIsInt: no se puede verficiar un string NULL");
        return false;
    }
    unsigned int i = 0;
    while (str[i] != '\0'){
        print_info("veo el valor: %d", str[i]);
        if(  str[i] != '-' && (isdigit(str[i]) == 0 || str[i] == '\0')){
            return false;
        }
        ++i;
    }
    return true;
}

/*GHashTable* read_file_conf(){
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    return NULL;
}*/


