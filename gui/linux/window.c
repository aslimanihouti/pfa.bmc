#include <stdlib.h>
#include <gtk/gtk.h> 
#include "BrailleMusicEditor.h"
#include "window.h"
#include "save.h"

/** 
 * Create a width X height window with the title 
 */

void create_window(const gchar* title, gint width , gint height, BrailleMusicEditor *editor)
{
	editor->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(editor->window), title);
	gtk_window_set_default_size(GTK_WINDOW(editor->window), width, height);
	gtk_window_set_position(GTK_WINDOW(editor->window), GTK_WIN_POS_CENTER);
	
	g_signal_connect(G_OBJECT(editor->window), "delete_event", G_CALLBACK(window_delete_event), editor);
	g_signal_connect(G_OBJECT(editor->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	
	
}

/** 
 * Check if there is un saved work and destroy the window after by
 * calling gtk_main_quit() (for menubar and toolbar) .
 */

void window_destroy (GtkWidget *widget, BrailleMusicEditor *editor)
{
	gint resp=check_for_save (editor);
	if (resp == 1)
		{
			save_file(widget, editor);
			gtk_main_quit();
		}			
	else if(resp == 0)
		gtk_main_quit();
  
}


/*
 * When the window is requested to be closed, we need to check if
 * there is unsaved work.  We use this callback to prompt the
 * user to save their work before they exit the application. With the
 * "delete-event" signal, we can choose to cancel the
 * close based on the value we return.
 */

gboolean window_delete_event (GtkWidget *widget, GdkEvent *event, 
	                        BrailleMusicEditor *editor)
{
	gint resp=check_for_save (editor);
	if (resp == 1)
		save_file(widget, editor);
	else if(resp == 2)
		return TRUE;
	
	return FALSE; //propogate event to destroy window		
}
