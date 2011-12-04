#include <gtk/gtk.h> 
#include "BrailleMusicEditor.h"


void change_color(GtkButton *widget, BrailleMusicEditor *editor){
	
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
