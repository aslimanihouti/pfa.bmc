#include <gtk/gtk.h>


void collect_path(GtkWidget *button, GtkWidget *file_selection)
{
	const gchar* path;
	GtkWidget *dialog;
	path = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );

	dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
	                                GTK_DIALOG_MODAL,
	                                GTK_MESSAGE_INFO,
	                                GTK_BUTTONS_OK,
	                                "You selected :\n%s", path);

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	gtk_widget_destroy(file_selection);
} 

void create_file_selection(GCallback c_handler, const gchar* title)
{
	GtkWidget *selection;

	selection = gtk_file_selection_new(title);
	gtk_widget_show(selection);

	//banning use of other window
	gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(c_handler), selection);

	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}
