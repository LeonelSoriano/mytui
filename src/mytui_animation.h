/** @file mytui_animation.h
 *  @ingroup Animation
 *  @brief funcionalidades pequeñas de animacion basicas
 *  @date 04-02-2019
 *  @author leonelsoriano3@gmail.com
 */
#ifndef __MYTUI_ANIMATION_H__
#define __MYTUI_ANIMATION_H__

#include "mytui_widget.h"


/**
 * @brief enumeración de tipos de animacionesa en el core.
 *
 * Enum que posee los tipos de animaciones.
 */
typedef enum {
    mytuiAnimationBox = 1, /**< anima una caja de widget MytuiAnimationTypes#mytuiAnimationBox */
} MytuiAnimationTypes;

typedef struct MytuiAnimation {
    struct MiTuiWidget *widget;
    struct mytuiStepAnimation *listAnimationsStep;
} MytuiAnimation;

typedef struct mytuiStepAnimation {
    MytuiAnimationTypes typeAnimation;
    double value;
    uint32_t step_time;
    struct mytuiStepAnimation *next;
} MytuiStepAnimation;

/**
 *  @brief inicia na aimacion
 *  @param el widget que se ejercera las animaciones
 *  @return una MytuiAnimation inicializada
 */
MytuiAnimation* init_MytuiAnimation(struct MiTuiWidget *widget);


/**
 *  @brief agrega un step a la animacion
 *  @param la animacion que se le agregara una animacion
 *  @param el step que sera agregado al componente
 */
void add_step_MytuiAnimation(struct MytuiAnimation** animation, MytuiAnimationTypes typeAnimation,
        double value, uint32_t step_time);


/**
 *  @brief libera la memoria de una mytui animation
 *  @param el widget que se ejercera las animaciones
 */
void free_MytuiAnimation(MytuiAnimation** animation);


void updata_mytuiAnimation(struct MytuiAnimation** animation);


#endif
