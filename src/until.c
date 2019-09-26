#include "until.h"

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

struct InfoTerm get_info_term()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    struct InfoTerm infoTerm;
    infoTerm.width = w.ws_col;
    infoTerm.width = w.ws_col;
    infoTerm.height = w.ws_row;
    return infoTerm;
}

const char *get_file_mytui_path()
{
    const char *folder_home = get_home_folder();

    static char conf_folder_resolution[sizeof folder_home +
                                (sizeof SEPARATOR_FOLDER * 3) +
                                sizeof CONF_FONDER + sizeof TUI_FOLDER_CONF];

    strcpy(conf_folder_resolution, folder_home);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FONDER);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_CONF);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);

    return conf_folder_resolution;
}


void run_cmd_silent(const char *cmd)
{
    const char *cmd_silent = " >/dev/null 2>&1";
    // const char *cmd_silent = " ";
    int max_buffer_cmd = strlen(cmd_silent) + strlen(cmd);
    char result[max_buffer_cmd];
    strcpy(result, cmd);
    strcat(result, cmd_silent);
    int is_ok = system(result);
    if (is_ok != 0) {
        print_error("run_cmd_silent: code Error es: %d", is_ok);
    }
}

bool exist_file(const char *path)
{
    struct stat buffer;
    return (stat(path, &buffer) == 0) ? true : false;
}

const char *get_home_folder()
{
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        struct passwd *pw = getpwuid(getuid());
        homedir = pw->pw_dir;
    } else {
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

void print_error(const char *msg, ...)
{
    /*va_list args;
    va_start(args, msg);
    int msg_len = strlen(msg);
    int msg_len_red = strlen(MYTUI_COLOR_RED);
    int msg_len_nrm = strlen(MYTUI_COLOR_RNM);
    int msg_len_new_line = strlen("\n");
    char tmp_str[msg_len + msg_len_red + msg_len_nrm + msg_len_new_line];

    strcpy(tmp_str, MYTUI_COLOR_RED);
    strcat(tmp_str, msg);
    strcat(tmp_str, MYTUI_COLOR_RNM);
    strcat(tmp_str, "\n");
    vfprintf(stderr, tmp_str, args);
    va_end(args);*/
}


void print_info(const char *msg, ...)
{

  /*  time_t timer;
    char buffer[26];
    struct tm *tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    const char *msg_info = " INFO: ";
    va_list args;
    va_start(args, msg);
    int msg_len = strlen(msg);
    int msg_len_blue = strlen(MYTUI_COLOR_BLUE);
    int msg_len_nrm = strlen(MYTUI_COLOR_RNM);
    int msg_len_title = strlen(msg_info);
    int msg_len_new_line = strlen("\n");
    int msg_len_time = strlen(buffer);
    char tmp_str[msg_len + msg_len_blue + msg_len_nrm + msg_len_title +
                 msg_len_new_line + msg_len_time];

    strcpy(tmp_str, MYTUI_COLOR_BLUE);
    strcat(tmp_str, buffer);
    strcat(tmp_str, msg_info);
    strcat(tmp_str, MYTUI_COLOR_RNM);
    strcat(tmp_str, msg);
    strcat(tmp_str, "\n");
    vfprintf(stderr, tmp_str, args);
    va_end(args);
    */
}

bool strIsInt(const char *str)
{
    if (str == NULL) {
	    print_line_log(MytuiLoggerTypeError,
                "strIsInt: no se puede verficiar un string NULL");
        return false;
    }

    for (int i = 0; i < strlen(str); i++)
    {

        if (str[i] != '\n' && str[i] != '-' &&
            (isdigit(str[i]) == 0 || str[i] == '\0')) {
            return false;
        }

    }


    /*while (str[i] != '\0') {
        if (str[i] != '\n' && str[i] != '-' &&
            (isdigit(str[i]) == 0 || str[i] == '\0')) {
            return false;
        }
        i++;
    }*/

    return true;
}

/*GHashTable* read_file_conf(){
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    return NULL;
}*/



int dump(void *myStruct, long size)
{
    unsigned int i;
    const unsigned char *const px = (unsigned char *)myStruct;
    for (i = 0; i < size; ++i) {
        if (i % (sizeof(int) * 8) == 0) {
            printf("\n%08X ", i);
        } else if (i % 4 == 0) {
            printf(" ");
        }
        printf("%02X", px[i]);
    }

    printf("\n\n");
    return 0;
}

/* Function returns the index of str where word is found */
int search(char str[], char word[]){
    int l, i, j;

    /* finding length of word */
    for (l = 0; word[l] != '\0'; l++)
        ;

    for (i = 0, j = 0; str[i] != '\0' && word[j] != '\0'; i++) {
        if (str[i] == word[j]) {
            j++;
        } else {
            j = 0;
        }
    }

    if (j == l) {
        /* substring found */
        return (i - j);
    } else {
        return -1;
    }
}


int delete_word(char str[], char word[]){
    int index = search(str, word);
    if (index == -1) {
        return 0;
    }

    int i, l;
    /* finding length of word */
    for (l = 0; word[l] != '\0'; l++)
        ;

    for (i = index; str[i] != '\0'; i++) {
        str[i] = str[i + l];
    }
    return 1;
}


bool copy_file(const char* path_source_file, const char* path_new_file){

    FILE *file_source, *file_new;

    file_source = fopen(path_source_file, "r");

    if(file_source == NULL){
        printf("pass_file_info: archivo de origen no encontrado %s\n", path_source_file);
        return false;
    }

    file_new = fopen(path_new_file, "w");

    if(file_new == NULL){
        fclose(file_source);
        printf("pass_file_info: archivco de origen nuevo no encontrado\n");
        return false;
    }

    char line[525];

    while (fgets(line, sizeof(line), file_source)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        fputs(line, file_new);

    }

    /*while (c != EOF){
        printf("char %d", c);
        fputc(c, file_new);
        c = fgetc(file_source);
    }*/

    fclose(file_source);
    fclose(file_new);
    return true;
}


bool collide_rect_point(unsigned int x, unsigned int y, unsigned int w, unsigned int h,
        unsigned int px, unsigned int py) {
    return ( (px >= x && px <= x + w)  && ( py >= y && py <= y + h )) ? true : false;
}

