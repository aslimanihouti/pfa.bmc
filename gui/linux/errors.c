#include <gtk/gtk.h>

/**
 * \file errors.c
 * \author Team BMC editor 
 */

//Display un dialog on file selection window when file == NULL 
//message_format must contain only one "%s" with is the path of the file

/** 
 * \fn void open_error(GtkWidget *file_selection, FILE *file, const gchar * message_format, const gchar* path)
 * \param file_selection
 * \param file The pointer to the file.
 * \param message_format The message diplayed in the dialog box.
 * \param path The path to the file.
 */
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
