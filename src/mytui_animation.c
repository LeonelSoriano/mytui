#include "mytui_animation.h"

MytuiAnimation* init_MytuiAnimation(MiTuiWidget *widget)
{

    if (widget == NULL) {
        print_error(
            "MytuiAnimation init_mytuiAnimation no puede ser inicializada con un widget NULL");
    }

    MytuiAnimation* animation = (MytuiAnimation*) malloc(sizeof(MytuiAnimation));
    animation->listAnimationsStep = NULL;
    animation->widget = widget;
    return animation;
}



void add_step_MytuiAnimation(MytuiAnimation** animation, MytuiAnimationTypes typeAnimation,
        double value, uint32_t step_time){
    if (*animation == NULL) {
        print_error("add_step_MytuiAnimation: MytuiAnimation* no pueden ser NULL");
    }
    MytuiStepAnimation *stepAnimation = (MytuiStepAnimation *)malloc(sizeof(MytuiStepAnimation));
    stepAnimation->step_time = step_time;
    stepAnimation->typeAnimation = typeAnimation;
    stepAnimation->value = value;

    if((*animation)->listAnimationsStep == NULL){
        stepAnimation->next = NULL;
        (*animation)->listAnimationsStep = stepAnimation;
    }else{
        struct mytuiStepAnimation *tmpAniamtion = (*animation)->listAnimationsStep;
        stepAnimation->next = tmpAniamtion;
        (*animation)->listAnimationsStep = stepAnimation;
    }
}


void free_MytuiAnimation(MytuiAnimation** animation){


    if(*animation == NULL){
        print_error("free_MytuiAnimation: MytuiAnimation** no puede ser NULL");
        return;
    }


    if((*animation)->listAnimationsStep != NULL){

        while((*animation)->listAnimationsStep != NULL){

            struct mytuiStepAnimation* tmpStepAnimation = (*animation)->listAnimationsStep->next;
            free((*animation)->listAnimationsStep);
            (*animation)->listAnimationsStep = tmpStepAnimation;
        }
    }

    free(*animation);
}
