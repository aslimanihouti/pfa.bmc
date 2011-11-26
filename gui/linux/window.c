#include <stdlib.h>
#include <gtk/gtk.h> 


//Create a width X height window with the title
GtkWidget * createWindow(const gchar* title, gint width , gint height)
{
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	return window;
}
