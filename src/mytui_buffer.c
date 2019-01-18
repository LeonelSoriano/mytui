#include "mytui_buffer.h"

static bool ANY_CHANGES_BUFFER;

void init_buffer(NodeBufer** nodeBufer)
{
    struct InfoTerm infoTerm = get_info_term();
    int max_buffer = (infoTerm.height) * (infoTerm.width );
    if (*nodeBufer != NULL) {
        print_error("init_bufffer: error no puede ser null el nodebuffer");
    }
    for (int i = 0; i < max_buffer ; i++) {
        if (*nodeBufer == NULL) {
            *nodeBufer = (NodeBufer*)malloc(sizeof(NodeBufer));
            (*nodeBufer)->next = NULL;
            (*nodeBufer)->update = true;
            (*nodeBufer)->bg = MYTUI_COLOR_DEFAULT;
            (*nodeBufer)->fg = MYTUI_COLOR_DEFAULT;
            ( *nodeBufer)->ch = ' ';
        } else {
            NodeBufer* tmp_buffer = (NodeBufer*)malloc(sizeof(NodeBufer));

            NodeBufer** tmp = nodeBufer;
            tmp_buffer->next = *tmp;
            tmp_buffer->update = true;
            tmp_buffer->bg = MYTUI_COLOR_DEFAULT;
            tmp_buffer->fg = MYTUI_COLOR_DEFAULT;
            tmp_buffer->ch = ' ';
            (*nodeBufer) = tmp_buffer;
        }
    }
}

void free_buffer(NodeBufer** nodeBufer)
{
    if (*nodeBufer == NULL) {
        print_error("free_buffer: no puede ser null el nodebufer");
        exit(EXIT_FAILURE);
    }
    while ((*nodeBufer)->next != NULL) {
        NodeBufer* tmp_buffer = (*nodeBufer)->next;
        free(*nodeBufer);
        (*nodeBufer) = tmp_buffer;
    }
    if ((*nodeBufer) != NULL) {
        free(*nodeBufer);
    }
}
void screen_manager(NodeBufer** nodeBufer)
{
    unsigned int x = 0, y = 0;
    NodeBufer* initPosBuffer = *nodeBufer;
    struct InfoTerm infoTerm = get_info_term();
    if (*nodeBufer != NULL) {
        do {
            if (x >= infoTerm.width - 1) {
                if((*nodeBufer)->update == true){
                    tb_change_cell(x, y, (*nodeBufer)->ch, (*nodeBufer)->bg, (*nodeBufer)->fg);
                    (*nodeBufer)->update = false;
                    ANY_CHANGES_BUFFER = true;
                }
                y++;
                x = 0;
            } else {
                if((*nodeBufer)->update == true){
                    tb_change_cell(x, y, (*nodeBufer)->ch, (*nodeBufer)->bg, (*nodeBufer)->fg);
                    (*nodeBufer)->update = false;
                    ANY_CHANGES_BUFFER = true;
                }
                x++;
            }
            (*nodeBufer) = (*nodeBufer)->next;
        } while ((*nodeBufer) != NULL);
    }
    *nodeBufer = initPosBuffer;

    if(ANY_CHANGES_BUFFER == true){
        tb_present();
        ANY_CHANGES_BUFFER = false;
    }
}

void init_screen_manager(NodeBufer** nodeBufer)
{
    if(*(nodeBufer) !=  NULL){
	free_buffer(nodeBufer);
    }

    init_buffer(nodeBufer);
    screen_manager(nodeBufer);
}

void nodeTranformation_init(NodeTranformation** nodeTranformation)
{
    *nodeTranformation = NULL;
}

void nodeTranformation_add(NodeTranformation** nodeTranformation, int x, int y,
    int fg, int bg,uint32_t ch)
{
    if (*nodeTranformation == NULL) {
        *nodeTranformation = (NodeTranformation*)malloc(sizeof(NodeTranformation));
        (*nodeTranformation)->bg = bg;
        (*nodeTranformation)->fg = fg;
        (*nodeTranformation)->x = x;
        (*nodeTranformation)->y = y;
        (*nodeTranformation)->ch = ch;
        (*nodeTranformation)->next = NULL;
    } else {
        NodeTranformation* tmp_old = (*nodeTranformation);
        NodeTranformation* tmp_tranformation =
            (NodeTranformation*)malloc(sizeof(NodeTranformation));
        tmp_tranformation->bg = bg;
        tmp_tranformation->fg = fg;
        tmp_tranformation->x = x;
        tmp_tranformation->ch = ch;
        tmp_tranformation->y = y;
        (*nodeTranformation) = tmp_tranformation;
        (*nodeTranformation)->next = tmp_old;
    }
}


void nodeTranformation_free(NodeTranformation** nodeTranformation)
{
    if (*nodeTranformation == NULL) {
        print_error("nodeTranformation_free nodeTranformation(param) no puede ser NULL");
        return;
    }
    for (;;) {
        if (*nodeTranformation == NULL) {
            return;
        } else {
            NodeTranformation* next_node = (*nodeTranformation)->next;
            free(*nodeTranformation);
            (*nodeTranformation) = next_node;
        }
    }
}

void node_bufffer_vs_tranformator(NodeBufer** nodeBufer, NodeTranformation* nodeTranformation)
{
    if (*nodeBufer == NULL) {
        print_error("node_bufffer_vs_tranformator: *nodeBuffer is Null");
        return;
    }
    if (nodeTranformation == NULL) {
        print_error("node_bufffer_vs_tranformator: *nodeTranformation");
    }

    struct InfoTerm infoTerm = get_info_term();

    NodeTranformation* tmp_tranformation = nodeTranformation;
    while (tmp_tranformation != NULL) {

        NodeBufer* tmp_nodeBuffer = *nodeBufer;

        int index_find = (tmp_tranformation->y * infoTerm.width) + tmp_tranformation->x;
        int index = 0;

        while ((*nodeBufer)->next != NULL) {
            if (index == index_find) {
                (*nodeBufer)->bg = tmp_tranformation->bg;
                (*nodeBufer)->fg = tmp_tranformation->fg;
                (*nodeBufer)->ch = tmp_tranformation->ch;
                (*nodeBufer)->update = true;
                index = -1;
                break;
            }
            (*nodeBufer) = (*nodeBufer)->next;
            index++;
        }
        if ((*nodeBufer) != NULL && index != -1) {
            index++;
            (*nodeBufer)->bg = tmp_tranformation->bg;
            (*nodeBufer)->fg = tmp_tranformation->fg;
            (*nodeBufer)->ch = tmp_tranformation->ch;
            (*nodeBufer)->update = true;
        }
        tmp_tranformation = tmp_tranformation->next;
        (*nodeBufer) = tmp_nodeBuffer;
    }
}
