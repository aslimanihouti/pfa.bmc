#include <gtk/gtk.h>
#include "open.h"
#include "save.h"

GtkWidget * createToolbar()
{
	GtkWidget *toolbar = gtk_toolbar_new();
	
	/* Addition of buttons in the toolbar */

	GtkToolItem *new, *open,*save, *sep, *quit;
	
	new = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new, -1);
	gtk_tool_item_set_tooltip_text(new, "Create a new file");

	open = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open, -1);
	g_signal_connect(G_OBJECT(open),"clicked",G_CALLBACK(open_file),NULL);
	gtk_tool_item_set_tooltip_text(open, "Open a file");

	save = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save, -1);
	gtk_tool_item_set_tooltip_text(save, "Save");
		g_signal_connect(G_OBJECT(save),"clicked",G_CALLBACK(save_file),NULL);

	sep = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1); 

	quit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), quit, -1);
	g_signal_connect(G_OBJECT(quit), "clicked", 
	                 G_CALLBACK(gtk_main_quit), NULL);
	gtk_tool_item_set_tooltip_text(quit, "Quit");

	
	/* Settings of the icons' size */
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolbar),
	                          GTK_ICON_SIZE_BUTTON);
	/* Only show icons */
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),
	                      GTK_TOOLBAR_ICONS);
	
	/*Settings of the toolbar's orientation */
	gtk_toolbar_set_orientation(GTK_TOOLBAR(toolbar),GTK_ORIENTATION_HORIZONTAL);
   
	return toolbar;
}
