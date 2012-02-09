#include <gtk/gtk.h> 
#include "BrailleMusicEditor.h"

/**
 * \file color.c
 * \author Team BMC editor 
 */

/**
 * \fn void change_color(GtkButton *widget, BrailleMusicEditor *editor)
 * \brief This function is called when selecting change color button.
 * \param widget The button trigerring the function.
 * \param editor The structure holding the data.
 * 
 * This function will color the text in green. It still has to change to be able to color paterns so that the seing end user can see time signatures for example.
 */
void change_color(GtkButton *widget, BrailleMusicEditor *editor)
{	
    static int clik=0;
    GdkColor color;
    gdk_color_parse ("green", &color);
    if(clik%2 == 0)
        gdk_color_parse ("green", &color);
    else
        gdk_color_parse ("black", &color);
    clik ++;
    gtk_widget_modify_text (editor->textview, GTK_STATE_NORMAL, &color);
}
