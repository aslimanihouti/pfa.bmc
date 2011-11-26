#include <stdlib.h>
#include <gtk/gtk.h>
#include "window.h"
#include "toolbar.h"




int main(int argc, char **argv)
{
	GtkWidget *mainWindow;
	GtkWidget *vBox;
	GtkWidget *toolbar;
	
	gtk_init(&argc, &argv);

	/* Creation of the main window */
	mainWindow = createWindow("BMC",600,600);
	
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(mainWindow), vBox);
	
	/* Creation of the toolbar  */
	toolbar = createToolbar();
	gtk_box_pack_start(GTK_BOX(vBox), toolbar, FALSE, FALSE, 0);
	
	gtk_widget_show_all(mainWindow);

	gtk_main();

	return EXIT_SUCCESS;
}


