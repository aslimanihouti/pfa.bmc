#include <stdlib.h>
#include <gtk/gtk.h>
#include "window.h"
#include "toolbar.h"
#include "menubar.h"


GtkWidget *text_view;
const gchar *current_file_path=NULL;
	
int main(int argc, char **argv)
{
	GtkWidget *mainWindow;
	GtkWidget *vBox;
	GtkWidget *toolbar;
	GtkWidget *scrollbar;
	GtkWidget *menubar;
	gtk_init(&argc, &argv);

	// Creation of the main window 
	mainWindow = createWindow("BMC",600,400);
	
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(mainWindow), vBox);
	
	//Creation of the menubar
	menubar = createMenubar(mainWindow);
	gtk_box_pack_start(GTK_BOX(vBox), menubar, FALSE, FALSE, 0);

	// Creation of the toolbar 
	toolbar = createToolbar();
	gtk_box_pack_start(GTK_BOX(vBox), toolbar, FALSE, FALSE, 2);
	
	//Creation of th text view with scrollbar
	scrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(vBox), scrollbar, TRUE, TRUE, 5);

	text_view=gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrollbar),text_view);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	gtk_widget_grab_focus(text_view);

	
	gtk_widget_show_all(mainWindow);

	gtk_main();

	return EXIT_SUCCESS;
}


