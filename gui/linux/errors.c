#include <gtk/gtk.h>

//Display un dialog on file selection window when file == NULL 
//message_format must contain only one "%s" with is the path of the file
void open_error(GtkWidget *file_selection, FILE *file, const gchar * message_format, const gchar* path)
{
	if(file == NULL)
		{
			GtkWidget *dialog;
			
			dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, message_format, g_locale_to_utf8(path, -1, NULL, NULL, NULL));
			
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			return;
		}

}
