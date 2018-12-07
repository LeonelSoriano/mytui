#include "mytui_buffer.h"

void init_buffer(NodeBufer **nodeBufer){
    struct InfoTerm infoTerm = get_info_term();
    int max_buffer = (infoTerm.height)  * (infoTerm.width + 1) ;
    if(*nodeBufer != NULL){
        print_error("init_bufffer: error no puede ser null el nodebuffer");
    }

    for (int i = 0; i <= (int)(max_buffer); i++) {
        if(i == 0){
            *nodeBufer = (NodeBufer *)malloc(sizeof(NodeBufer));
            (*nodeBufer)->next = NULL;
            (*nodeBufer)->update = true;
        }else{
            NodeBufer *tmp_buffer = (NodeBufer *)malloc(sizeof(NodeBufer));
            tmp_buffer->next = (*nodeBufer);
            tmp_buffer->update = true;
            (*nodeBufer) = tmp_buffer;
        }
    }
}

void free_buffer(NodeBufer **nodeBufer){
    if(*nodeBufer == NULL){
        print_error("free_buffer: no puede ser null el nodebufer");
        exit(EXIT_FAILURE);
    }
    while((*nodeBufer)->next != NULL){
        NodeBufer *tmp_buffer = (*nodeBufer)->next;
        free(*nodeBufer);
        (*nodeBufer) = tmp_buffer;
    }
    if((*nodeBufer) != NULL){
        free(*nodeBufer);
    }
}

void screen_manager(NodeBufer **nodeBufer){
    unsigned int x = 0,y =0;
    NodeBufer *initPosBuffer = *nodeBufer;
    struct InfoTerm infoTerm = get_info_term();
    if(*nodeBufer != NULL){
        do{
            if(x  >= infoTerm.width ){
                tb_change_cell(x , y , 'x', 100, 10);
                y++;
                x= 0;
            }else{
                tb_change_cell(x , y , '0', 100, 1);
                x++;
            }
            (*nodeBufer) = (*nodeBufer)->next;
        }while((*nodeBufer)->next != NULL);

    }
    *nodeBufer = initPosBuffer;

    tb_present();
}

void init_screen_manager(NodeBufer **nodeBufer){
    free_buffer(nodeBufer);
    init_buffer(nodeBufer);
    screen_manager(nodeBufer);
}

void nodeTranformation_init(NodeTranformation **nodeTranformation){
    *nodeTranformation = NULL;
}

void nodeTranformation_add(NodeTranformation **nodeTranformation, int x, int y, int fg, int bg){
    if(*nodeTranformation == NULL){
        *nodeTranformation = (NodeTranformation *)malloc(sizeof(NodeTranformation));
        (*nodeTranformation)->bg = bg;
        (*nodeTranformation)->fg = fg;
        (*nodeTranformation)->x = x;
        (*nodeTranformation)->y = y;
        (*nodeTranformation)->next = NULL;
    }else{
        NodeTranformation *tmp_old = (*nodeTranformation);
        NodeTranformation *tmp_tranformation =
            (NodeTranformation *)malloc(sizeof(NodeTranformation));
        tmp_tranformation->bg = bg;
        tmp_tranformation->fg = fg;
        tmp_tranformation->x = x;
        tmp_tranformation->y = y;

        (*nodeTranformation) = tmp_tranformation;
        (*nodeTranformation)->next = tmp_old;
    }
}

void nodeTranformation_free(NodeTranformation **nodeTranformation){
    if(*nodeTranformation == NULL){
        print_error("nodeTranformation_free nodeTranformation(param) no puede ser NULL");
        return;
    }
    for(;;){
        if(*nodeTranformation == NULL){
            return;
        }else{
            NodeTranformation *next_node = (*nodeTranformation)->next;
            free(*nodeTranformation);
            (*nodeTranformation) = next_node;
        }
    }
}

void node_bufffer_vs_tranformator(NodeBufer **nodeBufer, NodeTranformation *nodeTranformation){
    print_info("hola");
    if(*nodeBufer == NULL){
        print_error("node_bufffer_vs_tranformator: *nodeBuffer is Null");
        return;
    }
    if(nodeTranformation == NULL){
        print_error("node_bufffer_vs_tranformator: *nodeTranformation");
    }

    struct InfoTerm infoTerm = get_info_term();

    NodeTranformation *tmp_tranformation = nodeTranformation;
    while(tmp_tranformation != NULL){
        NodeBufer *tmp_nodeBuffer = *nodeBufer;

        int index_find = (tmp_tranformation->y * infoTerm.width)  + tmp_tranformation->x;
        int index = 0;

        if(index_find == 0){
            (*nodeBufer)->bg = tmp_tranformation->bg;
            (*nodeBufer)->fg = tmp_tranformation->fg;
            (*nodeBufer)->update = true;
            printf("lotengo 1");
        }else{
            index = 1;
            while((*nodeBufer)->next){
                if(index == index_find){
                    (*nodeBufer)->bg = tmp_tranformation->bg;
                    (*nodeBufer)->fg = tmp_tranformation->fg;
                    (*nodeBufer)->update = true;
                    index = -1;

            printf("lotengo 2");
                    break;
                }
                (*nodeBufer) = (*nodeBufer)->next;
                index++;
            }
            if((*nodeBufer) != NULL && index != -1){
                index++;
                (*nodeBufer)->bg = tmp_tranformation->bg;
                (*nodeBufer)->fg = tmp_tranformation->fg;
                (*nodeBufer)->update = true;

            printf("lotengo 3");
            }
        }
        tmp_tranformation = tmp_tranformation->next;
        (*nodeBufer) = tmp_nodeBuffer;
    }



}
