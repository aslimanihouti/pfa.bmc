#include <stdlib.h>
#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"
#include "window.h"
#include "toolbar.h"
#include "menubar.h"
#include "color.h"

int main(int argc, char **argv)
{
	BrailleMusicEditor *editor;

	// allocate the memory needed by our BrailleMusicEditor struct 
	editor = g_slice_new (BrailleMusicEditor);

	//initialize GTK+ libraries
	gtk_init(&argc, &argv);

	
	// Creation of the main window 
	create_window("BMC",600,400, editor);
	
	editor->vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(editor->window), editor->vbox); 
	
	//Creation of the menubar
	create_menubar(editor);
	gtk_box_pack_start(GTK_BOX(editor->vbox), editor->menubar, FALSE, FALSE, 0);

	// Creation of the toolbar
	create_toolbar(editor);
	gtk_box_pack_start(GTK_BOX(editor->vbox), editor->toolbar, FALSE, FALSE, 2);
	
	//Creation of the two text views with scrollbars

	editor->hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(editor->vbox), editor->hbox); 
	
	editor->scrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(editor->hbox),editor->scrollbar, TRUE, TRUE, 5);

	editor->textview=gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(editor->scrollbar),editor->textview);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(editor->scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	
	editor->scrollbar2 = gtk_scrolled_window_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(editor->hbox),editor->scrollbar2, TRUE, TRUE, 5);

	editor->rightview = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(editor->scrollbar2),editor->rightview);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(editor->scrollbar2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	

	gtk_widget_grab_focus(editor->textview);

	// show the window
	gtk_widget_show_all(editor->window);

	// enter GTK+ main loop
	gtk_main();

	// free memory we allocated for BrailleMusicEditor struct 
	g_slice_free (BrailleMusicEditor, editor);

	return EXIT_SUCCESS;
}


