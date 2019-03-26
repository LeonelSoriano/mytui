/** @file mytui_widget_types.h
 *  @ingroup Widget
 *  @brief lista de tipos de mytuiWidGet
 *  @date 26-03-2019
 *  @author leonelsoriano3@gmail.com
 */
#ifndef __MYTUI_WIDGET_TYPES_H__
#define __MYTUI_WIDGET_TYPES_H__


/**
 * @brief enumeración de widget en el core.
 *
 * Enum que posee los distintos widget de core.
 */
typedef enum {
    mytuiEntry = 1, /**< Componente vació WidgetTypes#entry. */
    mytuiLabel = 2, /**< Componente label texto WidgetTypes#label. */
    mytuiButton = 3 /**< Componente label texto WidgetTypes#button. */
}WidgetTypes;

#endif
