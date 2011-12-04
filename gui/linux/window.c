#include <stdlib.h>
#include <gtk/gtk.h> 
#include "BrailleMusicEditor.h"
#include "window.h"

/** 
 * Create a width X height window with the title 
 */

void create_window(const gchar* title, gint width , gint height, BrailleMusicEditor *editor)
{
	editor->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(editor->window), title);
	gtk_window_set_default_size(GTK_WINDOW(editor->window), width, height);
	gtk_window_set_position(GTK_WINDOW(editor->window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(editor->window), "destroy", G_CALLBACK(on_window_destroy), NULL);
	
}

/** 
 * Destroy the window by calling gtk_main_quit().
 */

void on_window_destroy (GtkObject *object, BrailleMusicEditor *editor)
{
	gtk_main_quit();
}
