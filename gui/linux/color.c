#include <stdlib.h>
#include <gtk/gtk.h> 

extern GtkWidget *text_view;
extern GtkTextBuffer *colored_buffer;
extern int clik;

void change_color(GtkButton *button, gpointer data){
    GdkColor color;
    if(clik%2 == 0)
        gdk_color_parse ("green", &color);
    else
        gdk_color_parse ("black", &color);
    clik ++;
    gtk_widget_modify_text (text_view, GTK_STATE_NORMAL, &color);
}
